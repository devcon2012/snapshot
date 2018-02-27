///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Feb 24 2018)
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
	m_statusBar1 = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
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
	this->Connect( m_menuItemSettings->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( myMainFrame::OnMenuSettings ) );
	this->Connect( m_menuItemQuit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( myMainFrame::OnMenuQuit ) );
	this->Connect( m_toolConnect->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( myMainFrame::OnConnectServer ) );
}

myMainFrame::~myMainFrame()
{
	// Disconnect Events
	this->Disconnect( wxID_MENU_ITEM_SETTINGS, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( myMainFrame::OnMenuSettings ) );
	this->Disconnect( wxID_MENU_ITEM_QUIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( myMainFrame::OnMenuQuit ) );
	this->Disconnect( m_toolConnect->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( myMainFrame::OnConnectServer ) );
	
}

SettingsDialog::SettingsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 600,-1 ), wxDefaultSize );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxT("http://127.0.0.1:8088"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( m_textCtrl1, 10, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer6->Add( 0, 0, 1, 0, 5 );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Server"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer6->Add( m_staticText1, 0, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer6->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	bSizer4->Add( bSizer6, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );
	
	m_dirPicker1 = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	bSizer8->Add( m_dirPicker1, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_listBoxSyncedDirs = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_SINGLE|wxLB_SORT ); 
	bSizer8->Add( m_listBoxSyncedDirs, 3, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	m_button4 = new wxButton( this, wxID_ANY, wxT("+"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_button4, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	m_button5 = new wxButton( this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_button5, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	bSizer8->Add( bSizer10, 1, 0, 5 );
	
	
	bSizer4->Add( bSizer8, 1, wxALIGN_CENTER|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_buttonOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_buttonOK, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	bSizer5->Add( 0, 0, 3, wxALL, 5 );
	
	m_buttonCANCEL = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_buttonCANCEL, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	bSizer4->Add( bSizer5, 1, wxALIGN_CENTER, 5 );
	
	
	this->SetSizer( bSizer4 );
	this->Layout();
	bSizer4->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::AddDirectory ), NULL, this );
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::RemoveDirectory ), NULL, this );
	m_buttonOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::UpdateSettings ), NULL, this );
	m_buttonCANCEL->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::CancelSettings ), NULL, this );
}

SettingsDialog::~SettingsDialog()
{
	// Disconnect Events
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::AddDirectory ), NULL, this );
	m_button5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::RemoveDirectory ), NULL, this );
	m_buttonOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::UpdateSettings ), NULL, this );
	m_buttonCANCEL->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SettingsDialog::CancelSettings ), NULL, this );
	
}
