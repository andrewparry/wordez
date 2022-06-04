#ifndef LETTER_H_
#define LETTER_H_

#include <memory>

#include <string>
#include <wx/wx.h>

// Letter object
// TODO Inherit from the wxTextCtrl object
class Letter
{
public:
    Letter(int turnid, int letterpos);          // Letter is a member of a turn and has a position
    ~Letter();
    int GetLetterPos() { return _letterpos; };  // Letter position
    void DisplayLetter(wxWindow *panel);        // Display the letter on the app window
    void SetLetter(int l);                      // Sets the character of the letter
    void SetColor(const int &color);            // Sets the color of the background
    void MoveX(int x);                          // Moves letter tile, used to wobble the tiles 
    std::string GetLetter();                    // Returns the set letter 
    bool HasValue();                            // True if letter has been set a value

private:

    wxTextCtrl *_tile;                          // The wxTextCtl Object for the tile in this letter 

    int _letterpos;                             // This letter's id in the turn
    int _turnid;                                // The turn this letter is contained in
    int _xpos;                                  // x position
    int _ypos;                                  // y position
};

#endif /* LETTER_H_ */