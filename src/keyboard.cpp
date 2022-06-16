#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

#include <wx/wx.h>
#include <wx/gbsizer.h>

#include "keyboard.h"

// Keyboard constructor
Keyboard::Keyboard(wxWindow *parent, wxWindowID id, wxPoint pos, wxSize sz) : wxPanel(parent, id, pos, sz)
{

  // Set the font of the Keyboard Panel, will apply to all buttons
  wxFont keyboardfont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
  wxFont smallletters(6, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
  this->SetFont(keyboardfont);

  // The keyboard will be a wxGridSizer of centered wxBoxSizer rows each containing wxButtton objects attached to this panel
  wxGridSizer *keygrid = new wxGridSizer(1);
  std::vector<wxBoxSizer *> rows;

  // Read the keyboard layout file into _keys
  ReadKeyboardFile("../kb.txt");

  // For each key generate buttons and insert into keyboard rows
  for (auto &key : _keys)
  {
    // Create a new row when required
    if (key.grid_row + 1 > rows.size())
      rows.emplace_back(new wxBoxSizer(wxHORIZONTAL));

    // Create a wxButton object, encode its character value to create a unique id, bind to button event, add button to a keyboard row key.key_cap
    key.button = new wxButton(this, 11000 + key.character, key.key_cap, wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT);

    //Reduce the font for the Enter and Del buttons
    // this->SetBackgroundColour((isFromUser == true ? wxT("YELLOW") : wxT("BLUE")));
    if (key.character == 10)
    {
      key.button->SetFont(smallletters);
      key.button->SetLabel("Enter");
    }
    if (key.character == 8)
    {
      key.button->SetFont(smallletters);
      key.button->SetLabel("Del");
    }

    // finalize setup
    key.button->SetBackgroundColour(wxColor(0xDDDDDD));
    key.button->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &Keyboard::OnButtonClicked, this);
    rows[key.grid_row]->Add(key.button, wxEXPAND | wxALL);
  }

  // Add and center each keyboard row to the keygrid
  for (auto &row : rows)
    keygrid->Add(std::move(row), 0, wxALIGN_CENTER);

  // Display the keyboard
  this->SetSizer(keygrid);
  keygrid->Layout();

  // Bind keyboard event and set focus to this keyboard panel
  this->Bind(wxEVT_CHAR_HOOK, &Keyboard::OnKey, this);
  this->SetFocus();
}

Keyboard::~Keyboard()
{
}

// Virtual Keyboard button clicked
void Keyboard::OnButtonClicked(wxCommandEvent &evt)
{
  // Decode the id to get back the character
  _kbcallback(evt.GetId() - 11000);
  evt.Skip();
}

// Physical keyboard press event
// TODO Animate keypress
void Keyboard::OnKey(wxKeyEvent &evt)
{
  _kbcallback(evt.GetKeyCode());
}

// Set the color of the keys according to the result of a turn.
void Keyboard::SetKeys(const std::string &word, const std::vector<int> &result)
{
  for (int i = 0; i < result.size(); i++)
  {
    char c = word[i];
    int color = 0x888888;
    switch (result[i])
    {
    case 0:
      break;
    case 1:
      // In multiple letter words, make sure yellow does not over write a green key
      if (color != 0x44BB44)
        color = 0x44BBBB;
      break;
    case 2:
      color = 0x44BB44;
    }

    // find the matching key and set the color
    for (auto &k : _keys)
    {
      if (k.character == c)
      {
        k.button->SetBackgroundColour(wxColor(color));
        k.button->SetForegroundColour(wxColor(0xFFFFFF));
        break;
      }
    }
  }
}

// The file format is key_cap int character, int keyboard column, int keyboard row
// Reads the keyboard file into the _keys vector of key struct
void Keyboard::ReadKeyboardFile(const std::string &path)
{
  Keys key;
  std::ifstream kbfile(path);
  assert(kbfile.is_open());
  if (kbfile.is_open())
  {
    std::string line;
    while (std::getline(kbfile, line))
    {
      std::istringstream sline(line);
      while (sline >> key.character >> key.grid_row) // key.grid_col >> key.grid_row)
      {
        if (key.character >= 65 && key.character <= 90)
          key.key_cap = char(key.character);
        
        // Labels will be set at button creation for backspace and enter
        if (key.character == 10 || key.character == 8)
          key.key_cap = "";
        _keys.emplace_back(key);
      }
    }
    kbfile.close();
  }
}