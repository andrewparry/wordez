
#include <string>
#include <memory>
#include <thread>
#include <chrono>

#include "turn.h"
#include "dictionary.h"

// Turn Constructor
Turn::Turn(const int &id) :_turnid(id)
{
    GenerateLetters(Turnlength);
    _activeletter = std::move(_letters[0]);
}
Turn::~Turn()
{   
}

// Display the turn of letter objects on the current panel
void Turn::DisplayTurn(wxWindow *panel)
{
    for(auto letter : _letters)
    {
        letter->DisplayLetter(panel);
    }
}

// Set the active letter with the char l
void Turn::SetLetter(const int &l)
{
    _activeletter->SetLetter(l);
    int letterposition = _activeletter->GetLetterPos();
    // Move to the next letter if not in the last position
    if(letterposition < Turnlength - 1)
    {
        // TODO Is this the best practice std::move???
        _activeletter = std::move(_letters[letterposition+1]);
    }
    
}

// Confirm the turn has been filled and completed
bool Turn::TurnCompleted()
{
    if(_activeletter->GetLetterPos()==Turnlength - 1 && _activeletter->HasValue())
    {
        return true;
    }
    return false;
}

// Concatenate the letters into a word
std::string Turn::GetTurnWord()
{
    std::string word = "";
    for(auto letter : _letters)
    {
        word += letter->GetLetter();
    }
    return word;
}

// Backspace logic
void Turn::Backspace()
{
    int pos = _activeletter->GetLetterPos();
    // We want to move the active letter back if not the first letter
    // or if the last letter contains no value
    if ((pos > 0 && pos < 4) || (pos==4 && !_activeletter->HasValue()))
        _activeletter = _letters[pos - 1];
    // Remove the value, SetLetter(0) will explicitly set the letter contents to ""
    _activeletter->SetLetter(0);
}


// Set the letter colors based on the turn result
// Also prepare for the clipboard at the end on the game
void Turn::SetResultColor(const std::vector<int> &result)
{
    // _turnResult will be used in the game result clipboard at the end of the game.
    _turnResult = "";
    for (int i=0; i<result.size(); i++)
    {
        int color = 0x888888;
        switch(result[i]) 
        {
            case 0:
                _turnResult += "⬜";
                break;
            case 1:
                _turnResult += "🟨";
                color = 0x44BBBB;
                break;
            case 2:
                _turnResult += "🟩";
                color = 0x44BB44;
        }
        _letters[i]->SetColor(color);
    }
}

// Wobble the letters in the event of a spelling error
void Turn::ShiftRightLeft()
{
    for(int i=1; i<4; i++)
    {
        for(auto &l : _letters)
        {
            // 4 - (6 * (i mod 2) i will result in a shift -2 one way 4 the other way with -2 back
            l->MoveX(4*(4 - (6 * (i % 2))));
        }
        // Bad practice to use wxYield to force the UI events to update
        // TODO replace with a wxTimer and Paint Event
        wxYield();
        wxMilliSleep(5);
    }
}

// Create a vector of Letter objects
void Turn::GenerateLetters(const int &numberofletters)
{
    for(int i=0; i<Turnlength; i++)
    {
        _letters.emplace_back( new Letter(_turnid, i));
    }
}