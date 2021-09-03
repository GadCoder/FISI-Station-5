#include "MainFrame.h"

enum{
    ID_gamesList= 1
};

MainFrame::MainFrame(std::string name)
     : wxFrame(nullptr, wxID_ANY, "FISI STATION", wxDefaultPosition, wxSize(700, 900)) 
{
    wxFont font(wxFontInfo(24));
    SetBackgroundColour(wxColour(122,204,226));
    playerName = name;
    playerNameDisplay = new wxTextCtrl(this,wxID_ANY,playerName,wxPoint(150,150),wxSize(400,100),wxTE_READONLY | wxTE_CENTRE);
    playerNameDisplay->SetFont(font);

    wxArrayString games;
    games.Add("Rocoto que bota y rebota");
    games.Add("Castillo Saltarin");
    games.Add("Loro Machaco Hambriento");
    gamesList = new wxListBox(this,ID_gamesList,wxPoint(150,450),wxSize(400,100),games,wxTE_CENTRE);
    button = new wxButton(this,ID_gamesList,"Jugar",wxPoint(262.4,700),wxSize(150,50));

    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_BUTTON, &MainFrame::getGameSelected, this, ID_gamesList);
}


MainFrame::~MainFrame(){
}


void MainFrame::getGameSelected(wxCommandEvent& event){
    int gameIndex = gamesList->GetSelection();
    bool gameSelected = false;
    int score;
    switch (gameIndex)
    {
    case 0: //rocoto
    {
        gameSelected = true;
        this->Show(false);
        rocotoLauncher = new RocotoLauncher();
        rocotoLauncher->launchGame(&score);
        break;
    }
    case 1: //castillo
    {
        gameSelected = true;
        this->Show(false);
        castilloLauncher = new CastilloLauncher();
        castilloLauncher->launchGame(&score);
        break;
    }
    case 2: //loro machaco
    {
        gameSelected = true;
        this->Show(false);
        snakeLauncher = new SnakeLauncher();
        snakeLauncher->launchGame(&score);
        break;
    }    
    default:
        gameSelected = false;
        break;
    }
    if(gameSelected){
        std::string scoreData = playerName + "," + std::to_string(score);
        scoreFrame = new ScoreFrame(gameIndex, scoreData, playerName);
        scoreFrame->Show(true);
        this->Destroy();
    }else{
        wxMessageBox("Seleccione un juego OwO");
    }
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

