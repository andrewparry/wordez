#ifndef WORDEZAPP_H_
#define WORDEZAPP_H_

#include <wx/wx.h>

#include "keyboard.h"
#include "game.h"

// wxWidgets app that hides main()
class WordezApp : public wxApp
{
public:
    virtual bool OnInit();
};

// Core application wxFrame
class WordezFrame : public wxFrame
{
public:
    WordezFrame();
    void ResetGame();               // Function to restart a game

    DECLARE_EVENT_TABLE();

private:

    //Game *_game;    // Raw pointer refering to the current Game object
    std::unique_ptr<Game> _game;
};

BEGIN_EVENT_TABLE(WordezFrame, wxFrame)
END_EVENT_TABLE()

#endif