///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 19 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __WXCLIENT_H__
#define __WXCLIENT_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class myMainFrame
///////////////////////////////////////////////////////////////////////////////
class myMainFrame : public wxFrame 
{
	private:
	
	protected:
		wxStaticText* m_staticText1;
		wxButton* m_button2;
		
		// Virtual event handlers, overide them in your derived class
		virtual void ExitButton( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		myMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~myMainFrame();
	
};

#endif //__WXCLIENT_H__
