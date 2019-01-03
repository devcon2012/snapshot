///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 31 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __WXCLIENT_H__
#define __WXCLIENT_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/sizer.h>
#include <wx/gdicmn.h>
#include <wx/statusbr.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/toolbar.h>
#include <wx/frame.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/filepicker.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define wxID_MENU_ITEM_SETTINGS 1000
#define wxID_MENU_ITEM_QUIT 1001

///////////////////////////////////////////////////////////////////////////////
/// Class myMainFrame
///////////////////////////////////////////////////////////////////////////////
class myMainFrame : public wxFrame
{
	private:

	protected:
		wxStatusBar* m_statusBar1;
		wxMenuBar* m_menubar1;
		wxMenu* file_menu;
		wxToolBar* m_toolBar1;
		wxToolBarToolBase* m_toolConnect;

		// Virtual event handlers, overide them in your derived class
		virtual void OnMenuSettings( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConnectServer( wxCommandEvent& event ) { event.Skip(); }


	public:

		myMainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~myMainFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class mySettingsDialog
///////////////////////////////////////////////////////////////////////////////
class mySettingsDialog : public wxDialog
{
	private:

	protected:
		wxTextCtrl* m_sServerURL;
		wxStaticText* m_staticText1;
		wxTextCtrl* m_sCAPath;
		wxFilePickerCtrl* m_xCAPicker;
		wxStaticText* m_staticText121;
		wxTextCtrl* m_sCertificatePath;
		wxFilePickerCtrl* m_xCertPicker;
		wxStaticText* m_staticText12;
		wxTextCtrl* m_sKeyPath;
		wxFilePickerCtrl* m_xKeyPicker;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText111;
		wxDirPickerCtrl* m_dirPicker1;
		wxListBox* m_listBoxSyncedDirs;
		wxButton* m_button4;
		wxButton* m_button5;
		wxButton* m_buttonOK;
		wxButton* m_buttonCANCEL;

		// Virtual event handlers, overide them in your derived class
		virtual void SelectCA( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void SelectCertificate( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void SelectKey( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void AddDirectory( wxCommandEvent& event ) { event.Skip(); }
		virtual void RemoveDirectory( wxCommandEvent& event ) { event.Skip(); }
		virtual void UpdateSettings( wxCommandEvent& event ) { event.Skip(); }
		virtual void CancelSettings( wxCommandEvent& event ) { event.Skip(); }


	public:

		mySettingsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Settings"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP );
		~mySettingsDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class myKeyPasswdDialog
///////////////////////////////////////////////////////////////////////////////
class myKeyPasswdDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText5;
		wxTextCtrl* m_textCtrl4;
		wxButton* m_button7;

	public:

		myKeyPasswdDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~myKeyPasswdDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class myExceptionDialog
///////////////////////////////////////////////////////////////////////////////
class myExceptionDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_exceptiotext;
		wxListBox* m_listBox2;
		wxButton* m_button6;
		wxButton* m_button7;

	public:

		myExceptionDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Error"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~myExceptionDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class myErrorMessage
///////////////////////////////////////////////////////////////////////////////
class myErrorMessage : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText7;
		wxTextCtrl* m_errortext;
		wxButton* m_buttonOK;
		wxButton* m_buttonCancel;

	public:

		myErrorMessage( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Error"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
		~myErrorMessage();

};

#endif //__WXCLIENT_H__
