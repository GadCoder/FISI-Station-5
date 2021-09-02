#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "StartFrame.h"
#include "MainFrame.h"


class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit(){
    StartFrame *frame = new StartFrame();
    frame->Show(true);
    return true;
}




