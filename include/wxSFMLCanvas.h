#include <SFML/Graphics.hpp>
//class wxSFML: public wxControl, public sf::RenderWindow

#include <wx/wxprec.h>
#include <wx/wx.h>

#include <SFML/Graphics.hpp>
#ifdef __WXGTK__
    #include <gdk/gdkx.h>
    #include <gtk/gtk.h>
#endif


class wxSFMLCanvas : public wxControl, public sf::RenderWindow
{
public :

    wxSFMLCanvas(wxWindow* Parent = NULL, wxWindowID Id = -1, const wxPoint& Position = wxDefaultPosition,
                 const wxSize& Size = wxDefaultSize, long Style = 0);

    virtual ~wxSFMLCanvas() {};

private :

    DECLARE_EVENT_TABLE()

    virtual void OnUpdate() {};

    void OnIdle(wxIdleEvent&);

    void OnPaint(wxPaintEvent&);

    void OnEraseBackground(wxEraseEvent&);
};

