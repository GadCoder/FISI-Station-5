#include "MainFrame.h"

enum{
    ID_gamesList= 1
};

MainFrame::MainFrame(std::string name)
     : wxFrame(nullptr, wxID_ANY, "FISI STATION", wxDefaultPosition, wxSize(1000, 800)) 
{
    wxFont font(wxFontInfo(24));
    SetBackgroundColour(wxColour(122,204,226));
    button = new wxButton(this,ID_gamesList,"Jugar",wxPoint(425,650),wxSize(150,50));
    playerName = name;
    playerNameDisplay = new wxTextCtrl(this,wxID_ANY,playerName,wxPoint(300,100),wxSize(400,100),wxTE_READONLY | wxTE_CENTRE);
    playerNameDisplay->SetFont(font);

    wxArrayString games;
    games.Add("Rocoto que bota y rebota");
    games.Add("Castillo Saltarin");
    games.Add("Loro Machaco Hambriento");
    gamesList = new wxListBox(this,ID_gamesList,wxPoint(300,400),wxSize(400,100),games,wxTE_CENTRE);

    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &MainFrame::getGameSelected, this, ID_gamesList);
}


MainFrame::~MainFrame(){
}


void MainFrame::getGameSelected(wxCommandEvent& event){
    int gameIndex = gamesList->GetSelection();
    bool gameSelected = false;
    int score;
    this->Show(false);
    switch (gameIndex)
    {
    case 0: //rocoto
    {
        /* code */
        break;
    }
    case 1: //castillo
    {
        gameSelected = true;
        castilloLauncher = new CastilloLauncher();
        castilloLauncher->launchGame(&score);
        break;
    }
    case 2: //loro machaco
    {
        gameSelected = true;
        snakeLauncher = new SnakeLauncher();
        snakeLauncher->launchGame(&score);
        break;
    }    
    default:
        break;
    }
    if(gameSelected){
        std::string scoreData = playerName + "," + std::to_string(score);
        scoreFrame = new ScoreFrame(gameIndex, scoreData);
        scoreFrame->Show(true);
    }
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

