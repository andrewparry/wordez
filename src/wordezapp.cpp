#include <string>
#include <memory>
#include <iostream>
#include <algorithm>

#include "wordezapp.h"
#include "game.h"
#include "keyboard.h"

// wxWidgets APP
DECLARE_APP(WordezApp);
IMPLEMENT_APP(WordezApp);

// Main
bool WordezApp::OnInit()
{
    // create window with name and show it
    WordezFrame *wordezFrame = new WordezFrame();
    wordezFrame->SetBackgroundColour(wxColour(0xBBBBBB));
    wordezFrame->Show(true);

    return true;
}

// wxWidgets FRAME
WordezFrame::WordezFrame() : wxFrame(nullptr, wxID_ANY, wxString("Wordez"), wxDefaultPosition, wxDefaultSize)
{
    Centre();
    SetIcon(wxIcon("../icon.png"));
    // Create new game and provide a call back to reset the game
    _game = new Game(this, std::bind(&WordezFrame::ResetGame, this));
}

// Delete the game object and recreate to reset the game
void WordezFrame::ResetGame()
{
    // Reset the unique pointer to clean up the memory from the previous game
    delete _game;
    // Create new smart pointer to start new game
    _game = new Game(this, std::bind(&WordezFrame::ResetGame, this));
    //_game = std::make_unique<Game>(this, std::bind(&WordezFrame::ResetGame, this));
    // Refresh the Frame
    Layout();
}
