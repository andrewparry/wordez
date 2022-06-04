#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <vector>
#include <functional>
#include <wx/wx.h>
#include "wx/button.h"
#include <string>

// The Keys struct Contains the position and character for each key in the keyboard.
// A vector of Keys will be populated from a file
struct Keys
{
    int character;    // Character code of the keyboard character.
    //int grid_col;     // Keyboard grid col
    int grid_row;     // Keyboard grid row
    wxString key_cap; // Will hold the string to display on the button keycap
    wxButton *button; // Pointer to the wxButton object
};

// Keyboard creates an onscreen keyboard of buttons & event handlers from a file of Keys 
class Keyboard : public wxPanel
{
public:
    Keyboard(wxWindow *parent, wxWindowID id, wxPoint pos, wxSize sz);          // Keyboard inherits from wxPanel
    ~Keyboard();
    using someCallbackName = std::function<void(int)>;                          // Function wrapper for the call back to the game class
    void SetCallback(someCallbackName cb) { _kbcallback = cb; }                 // Sets the call back to the game class                                        
    void OnButtonClicked(wxCommandEvent &evt);                                  // Event handler for mouse events
    void OnKey(wxKeyEvent &evt);                                                // Event handler for keyboard events

    void SetKeys(std::string word, std::vector<int> result);                    // Set color of keys based on the word result
    
    virtual bool AcceptsFocus() const override { return false; }                // wxWidgets focus setting
    virtual bool AcceptsFocusFromKeyboard() const override { return false; }    // wxWidgets focus setting

private:
    void ReadKeyboardFile(std::string path);                                    // Read file of keys and position in the keyboard
    std::vector<Keys> _keys;                                                    // Vector of _keys for the keyboard
    someCallbackName _kbcallback;                                               // The callback to the game object to process keys
};

#endif /* KEYBOARD_H_ */