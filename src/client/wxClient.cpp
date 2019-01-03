///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 31 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wxClient.h"

#include "resources/sync_24.png.h"

///////////////////////////////////////////////////////////////////////////

myMainFrame::myMainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );


	this->SetSizer( bSizer2 );
	this->Layout();
	m_statusBar1 = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	m_menubar1 = new wxMenuBar( 0 );
	file_menu = new wxMenu();
	wxMenuItem* m_menuItemSettings;
	m_menuItemSettings = new wxMenuItem( file_menu, wxID_MENU_ITEM_SETTINGS, wxString( wxT("Einstellungen") ) , wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( m_menuItemSettings );

	wxMenuItem* m_menuItemQuit;
	m_menuItemQuit = new wxMenuItem( file_menu, wxID_MENU_ITEM_QUIT, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( m_menuItemQuit );

	m_menubar1->Append( file_menu, wxT("Datei") );

	this->SetMenuBar( m_menubar1 );

	m_toolBar1 = this->CreateToolBar( wxTB_HORIZONTAL, wxID_ANY );
	m_toolBar1->SetMaxSize( wxSize( -1,42 ) );

	m_toolConnect = m_toolBar1->AddTool( wxID_ANY, wxT("Connect"), sync_24_png_to_wx_bitmap(), wxNullBitmap, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL );

	m_toolBar1->Realize();


	this->Centre( wxBOTH );

	// Connect Events
	file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( myMainFrame::OnMenuSettings ), this, m_menuItemSettings->GetId());
	file_menu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( myMainFrame::OnMenuQuit ), this, m_menuItemQuit->GetId());
	this->Connect( m_toolConnect->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( myMainFrame::OnConnectServer ) );
}

myMainFrame::~myMainFrame()
{
	// Disconnect Events
	this->Disconnect( m_toolConnect->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( myMainFrame::OnConnectServer ) );

}

mySettingsDialog::mySettingsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 600,-1 ), wxDefaultSize );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_sServerURL = new wxTextCtrl( this, wxID_ANY, wxT("http://127.0.0.1:8088"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_sServerURL, 10, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer6->Add( 0, 0, 1, 0, 5 );

	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Server"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer6->Add( m_staticText1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer6->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer4->Add( bSizer6, 0, wxALL|wxEXPAND, 2 );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );

	m_sCAPath = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( m_sCAPath, 10, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer15->Add( 0, 0, 1, wxEXPAND, 5 );

	m_xCAPicker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer15->Add( m_xCAPicker, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer15->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText121 = new wxStaticText( this, wxID_ANY, wxT("Stammzertifikat"), wxDefaultPosition, wxSize( 100,-1 ), 0 );
	m_staticText121->Wrap( -1 );
	bSizer15->Add( m_staticText121, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer15->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer4->Add( bSizer15, 0, wxALL|wxEXPAND, 2 );

	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxHORIZONTAL );

	m_sCertificatePath = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( m_sCertificatePath, 10, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer61->Add( 0, 0, 1, wxEXPAND, 5 );

	m_xCertPicker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer61->Add( m_xCertPicker, 0, wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer61->Add( 0, 0, 1, 0, 5 );

	m_staticText12 = new wxStaticText( this, wxID_ANY, wxT("Zertifikat"), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_CENTER_HORIZONTAL );
	m_staticText12->Wrap( -1 );
	bSizer61->Add( m_staticText12, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer61->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer4->Add( bSizer61, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer62;
	bSizer62 = new wxBoxSizer( wxHORIZONTAL );

	m_sKeyPath = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer62->Add( m_sKeyPath, 10, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer62->Add( 0, 0, 1, 0, 5 );

	m_xKeyPicker = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer62->Add( m_xKeyPicker, 0, wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer62->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText11 = new wxStaticText( this, wxID_ANY, wxT("Schlüssel"), wxDefaultPosition, wxSize( 100,-1 ), wxALIGN_CENTER_HORIZONTAL );
	m_staticText11->Wrap( -1 );
	bSizer62->Add( m_staticText11, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer62->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer4->Add( bSizer62, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	m_staticText111 = new wxStaticText( this, wxID_ANY, wxT("Verzeichnisse"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText111->Wrap( -1 );
	bSizer13->Add( m_staticText111, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	m_dirPicker1 = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	bSizer8->Add( m_dirPicker1, 0, wxALIGN_CENTER|wxALL, 5 );

	m_listBoxSyncedDirs = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE|wxLB_SORT );
	bSizer8->Add( m_listBoxSyncedDirs, 3, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	m_button4 = new wxButton( this, wxID_ANY, wxT("+"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_button4, 0, wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_button5 = new wxButton( this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_button5, 0, wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer8->Add( bSizer10, 1, 0, 5 );


	bSizer13->Add( bSizer8, 1, wxALIGN_CENTER|wxEXPAND, 5 );


	bSizer4->Add( bSizer13, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_buttonOK, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer5->Add( 0, 0, 3, wxALL, 5 );

	m_buttonCANCEL = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_buttonCANCEL, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer4->Add( bSizer5, 0, wxALIGN_CENTER, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_xCAPicker->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( mySettingsDialog::SelectCA ), NULL, this );
	m_xCertPicker->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( mySettingsDialog::SelectCertificate ), NULL, this );
	m_xKeyPicker->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( mySettingsDialog::SelectKey ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mySettingsDialog::AddDirectory ), NULL, this );
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mySettingsDialog::RemoveDirectory ), NULL, this );
	m_buttonOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mySettingsDialog::UpdateSettings ), NULL, this );
	m_buttonCANCEL->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mySettingsDialog::CancelSettings ), NULL, this );
}

mySettingsDialog::~mySettingsDialog()
{
	// Disconnect Events
	m_xCAPicker->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( mySettingsDialog::SelectCA ), NULL, this );
	m_xCertPicker->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( mySettingsDialog::SelectCertificate ), NULL, this );
	m_xKeyPicker->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( mySettingsDialog::SelectKey ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mySettingsDialog::AddDirectory ), NULL, this );
	m_button5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mySettingsDialog::RemoveDirectory ), NULL, this );
	m_buttonOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mySettingsDialog::UpdateSettings ), NULL, this );
	m_buttonCANCEL->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mySettingsDialog::CancelSettings ), NULL, this );

}

myKeyPasswdDialog::myKeyPasswdDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Key password"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer10->Add( m_staticText5, 0, wxALL, 5 );

	m_textCtrl4 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	bSizer10->Add( m_textCtrl4, 0, wxALL, 5 );

	m_button7 = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_button7, 0, wxALL, 5 );


	this->SetSizer( bSizer10 );
	this->Layout();
	bSizer10->Fit( this );

	this->Centre( wxBOTH );
}

myKeyPasswdDialog::~myKeyPasswdDialog()
{
}

myExceptionDialog::myExceptionDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 480,-1 ), wxDefaultSize );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	m_exceptiotext = new wxStaticText( this, wxID_ANY, wxT("An error occurred:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_exceptiotext->Wrap( -1 );
	bSizer11->Add( m_exceptiotext, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_listBox2 = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0|wxBORDER_NONE|wxHSCROLL|wxVSCROLL );
	bSizer11->Add( m_listBox2, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );

	m_button6 = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_button6, 0, wxALL, 5 );


	bSizer12->Add( 0, 0, 1, wxEXPAND, 5 );

	m_button7 = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( m_button7, 0, wxALL, 5 );


	bSizer11->Add( bSizer12, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer11 );
	this->Layout();
	bSizer11->Fit( this );

	this->Centre( wxBOTH );
}

myExceptionDialog::~myExceptionDialog()
{
}

myErrorMessage::myErrorMessage( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Error"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText7->Wrap( -1 );
	bSizer13->Add( m_staticText7, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_errortext = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( m_errortext, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonOK, 0, wxALL, 5 );

	m_buttonCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( m_buttonCancel, 0, wxALL, 5 );


	bSizer13->Add( bSizer14, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer13 );
	this->Layout();
	bSizer13->Fit( this );

	this->Centre( wxBOTH );
}

myErrorMessage::~myErrorMessage()
{
}
