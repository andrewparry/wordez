#ifndef GAME_H_
#define GAME_H_
#include <vector>
#include <string>

#include <wx/wx.h>

#include "turn.h"
#include "keyboard.h"
#include "dictionary.h"

class WordezFrame;

enum TurnResult
{
    kBadSpelling,
    kNotCorrect,
    kCorrect
};

// Core Game class made up of Turns, a keyboard, and the game logic 
class Game 
{
public:
    using endgameCallbackName = std::function<void()>;  // Function wrapper for end game reset
    Game(wxWindow *_appwindow, endgameCallbackName cb); // Game constructor
    ~Game();                                            // Destructor

private:
    void GenerateTurns();                               // Populate vector of Turn objects
    void Display();                                     // Display wxWidgets for Game panel
    void DisplayTurns(wxWindow *panel);                 // Turn display function to display the grid of Letters

    void KeyboardCallback(int keycode);                 // Process keyboard key presses
    void ProcessEnter();                                // Process the Enter key being pressed at the end of a turn
    TurnResult EvaluateTurn();                          // Evaluate the outcome of a completed turn

    void InActiveCallback(int keycode){};               // Dummy keyboard callback to ignore key presses

    void OnCopyButtonClicked(wxCommandEvent &evt);      // Copy wxEvent function
    void OnRestartButtonClicked(wxCommandEvent &evt);   // Restart wxEvent function

    const int Totalturns = 6;                           // Total tunrns constant

    std::vector<Turn *> _turns;                         // Vector of Turn objects
    Turn *_activeturn;                                  // Current active turn
    std::unique_ptr<Dictionary> _dictionary;            // Dictionary object
    std::string _clipboard = "Wordez";                  // Used to form end of game clipboard message.

    wxWindow *_appwindow;                               
    wxPanel  *_gameboard;
    wxButton *_copyButton;
    wxButton *_restartButton;

    Keyboard *_keyboard;                                 
    endgameCallbackName _endgamecallback;               // End game call back
};

#endif /* GAME_H_ */