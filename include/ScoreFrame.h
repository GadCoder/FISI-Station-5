#pragma once
#include <fstream>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <string>


class ScoreFrame : public wxFrame{
public:
    ScoreFrame(int opc, std::string p_score, std::string p_playerName);
private:
    struct ScorePATHS{
        std::string rocoto = "rocotoScore.txt";
        std::string castillo = "castilloScore.txt";
        std::string snake = "snakeScore.txt";
    };
    std::string scorePath;
    std::string gameName;
    std::string playerName;
    std::ofstream writeTXT;
    std::ifstream readTXT;
    wxListBox *nameBoard;
    wxListBox *scoreBoard;
    wxButton *menuBTN;
    wxButton *exitBTN;
    wxTextCtrl *gameNameDisplay;
    void addScore(std::string score);
    void updateScore(wxArrayString &p_scores, wxArrayString &p_names);
    void launchMenu(wxCommandEvent& event);
    void exit(wxCommandEvent& event);
};