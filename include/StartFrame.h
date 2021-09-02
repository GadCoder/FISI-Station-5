#pragma once
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <string>

#include "MainFrame.h"

class StartFrame : public wxFrame
{
public:
    wxButton *button;
    wxTextCtrl *nameField;

    std::string userName;
    MainFrame *main;

    StartFrame();
    ~StartFrame();

    void getName(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    
};