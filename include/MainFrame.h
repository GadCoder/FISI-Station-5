#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <string>
#include "SnakeLauncher.h"
#include "ScoreFrame.h"
#include "CastilloLauncher.h"


class MainFrame : public wxFrame
{
public:
    ScoreFrame *scoreFrame;
    SnakeLauncher *snakeLauncher;
    CastilloLauncher *castilloLauncher;
    wxTextCtrl  *playerNameDisplay;
    std::string playerName;
    wxButton *button;
    wxListBox *gamesList;
    MainFrame(std::string name);
    ~MainFrame();
    void OnExit(wxCommandEvent& event);
    void getGameSelected(wxCommandEvent& event);
};
