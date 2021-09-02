#include "wxSFMLCanvas.h"

BEGIN_EVENT_TABLE( wxSFMLCanvas, wxControl )
        EVT_IDLE( wxSFMLCanvas::OnIdle )
        EVT_PAINT( wxSFMLCanvas::OnPaint )
        EVT_ERASE_BACKGROUND( wxSFMLCanvas::OnEraseBackground )
END_EVENT_TABLE()

void wxSFMLCanvas::OnIdle(wxIdleEvent&)
{
    // Send a paint message when the control is idle, to ensure maximum framerate
    Refresh();
}

void wxSFMLCanvas::OnEraseBackground(wxEraseEvent&)
{
}

void wxSFMLCanvas::OnPaint(wxPaintEvent&)
{
    // Prepare the control to be repainted
    wxPaintDC Dc(this);

    // Let the derived class do its specific stuff
    OnUpdate();

    // Display on screen
    display();
}

wxSFMLCanvas::wxSFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style) :
wxControl(Parent, Id, Position, Size, Style)
{
    #ifdef __WXGTK__

        // GTK implementation requires to go deeper to find the
        // low-level X11 identifier of the widget
        gtk_widget_realize(m_wxwindow);
        gtk_widget_set_double_buffered(m_wxwindow, false);
        GdkWindow* Win = gtk_widget_get_window( (GtkWidget *) GetHandle() );
        XFlush(GDK_WINDOW_XDISPLAY(Win));
        sf::RenderWindow::create(GDK_WINDOW_XID(Win));

    #else

        // Tested under Windows XP only (should work with X11
        // and other Windows versions - no idea about MacOS)
        sf::RenderWindow::Create(GetHandle());

    #endif
}

