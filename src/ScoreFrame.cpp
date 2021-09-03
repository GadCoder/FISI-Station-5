#include "ScoreFrame.h"
#include <vector>
#include <algorithm>

enum{
    ID_board= 1
};


struct ScoreValues{
    std::string name;
    int score;
    void getValues(std::string data);
    ScoreValues(std::string data){
       getValues(data);
    }
    std::string makeData();
};

void ScoreValues::getValues(std::string data){
    std::size_t breakPoint = data.find(",");
    name = data.substr(0, breakPoint);
    score = stoi(data.substr(breakPoint + 1, data.length() - 1));
}

std::string ScoreValues::makeData(){
    return name + "," + std::to_string(score);
}


ScoreFrame::ScoreFrame(int opc, std::string p_score)
     : wxFrame(nullptr, wxID_ANY, "FISI STATION - SCORES", wxDefaultPosition, wxSize(700, 900)) 
{
    SetBackgroundColour(wxColour(122,204,226));
    ScorePATHS paths;
    scorePath = "./content/Scores/";
    switch (opc)
    {
    case 0:
        scorePath += paths.rocoto;
        gameName = "Rocot que bota y rebota";
        break;
    case 1:
        scorePath += paths.castillo;
        gameName = "Castillo Saltarin";
        break;
    case 2:
        scorePath += paths.snake;
        gameName = "Loro Machaco Hambriento";
        break;
    
    default:
        break;
    }
    wxFont font(wxFontInfo(18));
    SetBackgroundColour(wxColour(122,204,226));
    gameNameDisplay = new wxTextCtrl(this,wxID_ANY,gameName,wxPoint(150,150),wxSize(400,100),wxTE_READONLY | wxTE_CENTRE);
    gameNameDisplay->SetFont(font);

    writeTXT.open(scorePath,std::ios::app);
    readTXT.open(scorePath,std::ios::app);
    addScore(p_score);
    wxArrayString scores;
    updateScore(scores);
    writeTXT.close();
    readTXT.close();
    scoreBoard = new wxListBox(this,ID_board,wxPoint(150,300),wxSize(400,300),scores,wxTE_CENTRE);
    menuBTN = new wxButton(this,wxID_ANY,"Volver al menu",wxPoint(150,700),wxSize(150,50)); //+400
    exitBTN = new wxButton(this,wxID_ANY,"Salir",wxPoint(400,700),wxSize(150,50));
}

void ScoreFrame::addScore(std::string score){
    writeTXT << score <<std::endl; 
}

bool compareScore(const ScoreValues &a, const ScoreValues &b)
{
    return a.score > b.score;
}

void ScoreFrame::updateScore(wxArrayString &p_scores){
    std::string textLine;
    std::vector<ScoreValues> scores; 
    while (std::getline (readTXT, textLine)) {
        ScoreValues score(textLine);
        scores.push_back(score);
    }
    std::sort(scores.begin(), scores.end(), compareScore);
  
    std::ofstream sortedTXT(scorePath,std::ios::out);
    for(ScoreValues score : scores){
        sortedTXT <<score.makeData()<<std::endl;
        p_scores.Add(score.makeData());
    }
    sortedTXT.close();
}   

