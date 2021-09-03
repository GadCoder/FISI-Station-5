#include "StartFrame.h"

enum{
    ID_nameBTN = 1
};

StartFrame::StartFrame()
     : wxFrame(nullptr, wxID_ANY, "FISI STATION 5", wxDefaultPosition, wxSize(700, 900)) 
{
    wxFont font(wxFontInfo(24));
    SetBackgroundColour(wxColour(122, 204, 226 ));
    button = new wxButton(this,ID_nameBTN,"Ingresar nombre",wxPoint(425,450),wxSize(150,50));
    nameField = new wxTextCtrl(this,wxID_ANY,"",wxPoint(300,300),wxSize(400,100),wxTE_CENTRE);
    nameField->SetFont(font);
    Bind(wxEVT_BUTTON, &StartFrame::getName, this, ID_nameBTN);
    Bind(wxEVT_MENU, &StartFrame::OnExit, this, wxID_EXIT);

}


StartFrame::~StartFrame(){
    delete button;
    delete nameField;
}


void StartFrame::getName(wxCommandEvent& event){
    userName = nameField->GetValue().ToStdString();

    if(userName.size() < 1){

    }else{
        this->Show(false);
        main = new MainFrame(userName);
        main->Show(true);
    }
}

void StartFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}