#include <iostream>

#include <wx/wx.h>
#include <wx/textctrl.h>

#include "letter.h"

// Constructor and Destructor
Letter::Letter(const int &turnid, const int &letterpos) : _turnid(turnid), _letterpos(letterpos)
{
    // Positioning - 63 x 63 tile is a nice size
    // TODO Make this all scalable
    _xpos = 96 + (_letterpos * 63);
    _ypos = 63 + (_turnid * 63);
}
Letter::~Letter()
{
    _tile->Destroy();
}

// Based on the id of the letter create the tile and position it accordingly
void Letter::DisplayLetter(wxWindow *panel)
{
    int id = (_turnid * 6) + _letterpos;
    wxFont letterfont(20, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    _tile = new wxTextCtrl(panel, id, "", wxPoint(_xpos, _ypos), wxSize(63, 63), wxALIGN_CENTER_HORIZONTAL | wxBORDER_DOUBLE);
    _tile->SetFont(letterfont);
    _tile->SetEditable(false);
}

// Set the letter to the char value l, if 0 reset the value to ""
void Letter::SetLetter(const int &l)
{
    if (l == 0)
    {
        _tile->ChangeValue("");
    }
    else
    {
        _tile->ChangeValue(char(l));
    }
}

// Set the color of the tile
void Letter::SetColor(const int &color)
{
    _tile->SetBackgroundColour(wxColor(color));
    _tile->SetForegroundColour(wxColor(0xFFFFFF));
}

// Move delta d pixels horizontal relative to current position
void Letter::MoveX(int d)
{
    wxPoint p = _tile->GetPosition();
    _tile->Move(wxPoint(p.x + d, p.y));
}

// Does the tile have a value
bool Letter::HasValue()
{
    if (_tile->GetValue().length() > 0)
        return true;
    return false;
}

// Return the string value of the letter
std::string Letter::GetLetter()
{
    return _tile->GetValue().ToStdString();
}
