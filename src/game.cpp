#include <string>
#include <memory>
#include <functional>

#include <wx/wx.h>
#include "wx/msgdlg.h"
#include "wx/clipbrd.h"

#include "game.h"
#include "keyboard.h"
#include "dictionary.h"

// Setup the game
Game::Game(wxWindow *appwindow, endgameCallbackName cb)
{
    //std::cout << "\n***\nCreate Game Object " << this<< "\n***\n" << std::endl;
    _appwindow = appwindow;
    _endgamecallback = cb;

    // The Dictionary object contains all the word methods
    _dictionary = std::make_unique<Dictionary>();

    // Setup the turns and display
    GenerateTurns();
    _activeturn = _turns[0];
    Display();
}

// Clean up objects
Game::~Game()
{
    _gameboard->Destroy();
    _copyButton->Destroy();
    _restartButton->Destroy();
    _keyboard->Destroy();
    _appwindow = nullptr;
    _activeturn = nullptr;
    _endgamecallback = nullptr;
}

// Create vector of turns
void Game::GenerateTurns()
{
    for (int i = 0; i < Totalturns; i++)
    {
        _turns.emplace_back(new Turn(i));
    }
}

// Display the vector of turns
void Game::DisplayTurns(wxWindow *panel)
{
    for (auto turn : _turns)
    {
        turn->DisplayTurn(panel);
    }
}

// Display the panel of wxWidget game objects
void Game::Display()
{
    // Vertical sizer to hold the GUI objects
    wxBoxSizer *appsizer = new wxBoxSizer(wxVERTICAL);

    // The game board containing the turns
    _gameboard = new wxPanel(_appwindow, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    DisplayTurns(_gameboard);

    // Horizontal sizer of initially hidden Buttons to copy and restart the game
    wxBoxSizer *hiddensizer = new wxBoxSizer(wxHORIZONTAL);
    wxStaticText *dummytext = new wxStaticText(_appwindow, wxID_ANY, wxT(" "), wxDefaultPosition, wxSize(44, 44));
    _copyButton = new wxButton(_appwindow, wxID_ANY, wxT("Copy"), wxDefaultPosition, wxDefaultSize);
    _restartButton = new wxButton(_appwindow, wxID_ANY, wxT("Restart"), wxDefaultPosition, wxDefaultSize);
    _copyButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Game::OnCopyButtonClicked, this);
    _restartButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Game::OnRestartButtonClicked, this);
    hiddensizer->AddSpacer(64);
    hiddensizer->Add(_copyButton, 1, wxEXPAND);
    hiddensizer->Add(dummytext, 1, wxEXPAND);
    hiddensizer->Add(_restartButton, 1, wxEXPAND);
    hiddensizer->AddSpacer(64);
    _copyButton->Hide();
    _restartButton->Hide();

    // The Keyboard
    _keyboard = new Keyboard(_appwindow, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    _keyboard->SetCallback(std::bind(&Game::KeyboardCallback, this, std::placeholders::_1));

    // Populate the vertical sizer with all the game objects
    appsizer->Add(_gameboard, 1, wxEXPAND);
    appsizer->AddSpacer(10);
    appsizer->Add(hiddensizer, 0, wxEXPAND);
    appsizer->AddSpacer(10);
    appsizer->Add(_keyboard, 0, wxEXPAND);
    _appwindow->SetSizerAndFit(appsizer);
}

// Callback from the Keyboard, process the key
void Game::KeyboardCallback(int keycode)
{
    // Pressed an A-Z char
    if (keycode >= 65 && keycode <= 90)
    {
        // Call the activeturn to set the active letter
        _activeturn->SetLetter(keycode);
    }

    // Pressed ENTER
    if (keycode == 10 || keycode == 13)
    {
        // If last letter then evaluate the turn and execute the outcome
        if (_activeturn->TurnCompleted())
            ProcessEnter();
    }

    // Pressed BACKSPACE
    if (keycode == 8)
    {
        _activeturn->Backspace();
    }
}

// Process the Enter key being pressed at the end of the turn and generate subsequent actions
void Game::ProcessEnter()
{
    int turnid = _activeturn->GetTurnId();
    switch (EvaluateTurn())
    {
    // Do not roll over to next turn, shake the letters
    case TurnResult::kBadSpelling:
        _activeturn->ShiftRightLeft();
        break;

    // Guess was not correct, move to next turn or game over
    case TurnResult::kNotCorrect:
        if (turnid < Totalturns - 1)
        // Rollover to the next turn
        {
            _activeturn = std::move(_turns[turnid + 1]);
        }
        else
        // Game Over
        {
            // Clipboard will be called by the copy button
            _clipboard += " " + _dictionary->GetTargetWord() + " You Lost " + "X/6\n";

            // Change keyboard callback to dummy to disable processing keyboard events
            _keyboard->SetCallback(std::bind(&Game::InActiveCallback, this, std::placeholders::_1));

            // Dialog box to display the correct answer
            wxMessageDialog dialog(_appwindow, "\nGame Over: " + _dictionary->GetTargetWord() + "\n", "", wxOK_DEFAULT | wxOK | wxICON_NONE);
            dialog.SetTitle("Game Over");
            dialog.ShowModal();

            // Display the copy and restart buttons
            _copyButton->Show();
            _restartButton->Show();
            _appwindow->Layout();
        }
        break;

    // Guess was correct you win!
    case TurnResult::kCorrect:
        // Prepare clipboard for the copy button
        _clipboard += " " + _dictionary->GetTargetWord() + " You Win " + std::to_string(_activeturn->GetTurnId() + 1) + "/6\n";

        // Change keyboard callback to dummy to disable processing keyboard events
        _keyboard->SetCallback(std::bind(&Game::InActiveCallback, this, std::placeholders::_1));

        // Show copy and restart buttons
        _copyButton->Show();
        _restartButton->Show();
        _appwindow->Layout();
    }
}


// Evaluate the completed turn
TurnResult Game::EvaluateTurn()
{
    // Get the word from the completed turn
    std::string word = _activeturn->GetTurnWord();

    // Spell check
    if (_dictionary->ValidWord(word))
    {
        // result vector, an int result for each letter
        // 0 = Letter not in the word
        // 1 = Letter is in the word but in the wrong position
        // 2 = Letter is in the correct position
        std::vector<int> result = _dictionary->CompareWord(word);

        // Display the background colors in the word and keyboard tiles
        _activeturn->SetResultColor(result);
        _keyboard->SetKeys(word, result);

        // Return result enum to drive the outcome behavior
        if (result == std::vector<int>{2, 2, 2, 2, 2})
        {
            return TurnResult::kCorrect;
        }
        else
        {
            return TurnResult::kNotCorrect;
        }
    }
    return TurnResult::kBadSpelling;
}

// Fill clipboard when end game copy button is clicked. 
void Game::OnCopyButtonClicked(wxCommandEvent &evt)
{
    // Get the graphical result view of each turn
    for (auto &t : _turns)
    {
        _clipboard += t->GetTurnResult() + "\n";
    }

    // Fill the clipboard
    if (wxTheClipboard->Open())
    {
        wxTheClipboard->Clear();
        wxTheClipboard->SetData(new wxTextDataObject(wxString(_clipboard.c_str(), wxConvUTF8)));
        wxTheClipboard->Close();
    }
}

// Call parent object to reset and recreate the game object
void Game::OnRestartButtonClicked(wxCommandEvent &evt)
{
    _endgamecallback();
}