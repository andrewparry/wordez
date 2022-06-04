#ifndef TURN_H_
#define TURN_H_

#include <memory>
#include <vector>

#include <wx/wx.h>

#include "letter.h"
#include "dictionary.h"

// Turn class made up of letters
class Turn 
{
    public:
        Turn(int id);
        ~Turn();
        void DisplayTurn(wxWindow *panel);                  // Display the tiles of Letters
        void SetLetter(int l);                              // Set the current letter to char of l
        int GetTurnId() { return _turnid;};                 // Return the current turn
        void Backspace();                                   // Delete letter
        bool TurnCompleted();                               // Evaluate if turn has been completed
        void SetResultColor(const std::vector<int> &result);// Set the result colors for the turn
        void ShiftRightLeft();                              // Wobbles the turn if the word is not in the spell list
        std::string GetTurnWord();                          // Collate the letters in the word
        std::string GetTurnResult() {return _turnResult;};  // Evaluate the result of the turn

    private:
        void GenerateLetters(int letters);

        const int Turnlength = 5;                           // Number of letters in a turn

        int _turnid;                                        // This turns id in the game

        std::vector<Letter*> _letters;                      // Vector of Letter objects
        Letter *_activeletter;                              // Current Active letter

        std::string _turnResult = "⬜⬜⬜⬜⬜";             //Used in the clipbaord at the end of the game, default to all white squares.
};







#endif /* TURN_H_ */

