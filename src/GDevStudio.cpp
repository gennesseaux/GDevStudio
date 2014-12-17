// GDevStudio.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include <vld.h>
#include "GDevStudio.h"
#include "MainFrm.h"

#include "GDevStudioDoc.h"
#include "GDevStudioView.h"

// Inclusions
#include "SQLite/SQLiteSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDevStudioApp

BEGIN_MESSAGE_MAP(CGDevStudioApp, CBCGPWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CGDevStudioApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW,			&CGDevStudioApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN,		&CGDevStudioApp::OnFileOpen)
END_MESSAGE_MAP()


// CGDevStudioApp construction

CGDevStudioApp::CGDevStudioApp()
{
	SetVisualTheme(BCGP_VISUAL_THEME_OFFICE_2013_WHITE);
}


// The one and only CGDevStudioApp object

CGDevStudioApp theApp;


// CGDevStudioApp initialization

BOOL CGDevStudioApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CBCGPWinApp::InitInstance();

	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("GDevStudio"));
	LoadStdProfileSettings(4);  // Load standard INI file options (including MRU)

	SetRegistryBase(_T("Settings"));

// 	// Tests
// 	Test();

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGDevStudioDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CGDevStudioView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Ne pas afficher la fenêtre
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ouverture d'un projet par défaut
	OnFileNew();

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

// CGDevStudioApp message handlers

int CGDevStudioApp::ExitInstance() 
{
	return CBCGPWinApp::ExitInstance();
}

// CAboutDlg dialog used for App About

class CAboutDlg : public CBCGPDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };
	CBCGPURLLinkButton m_btnURL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CBCGPDialog(CAboutDlg::IDD)
{
	EnableVisualManagerStyle(TRUE, TRUE);
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPANY_URL, m_btnURL);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CBCGPDialog)
END_MESSAGE_MAP()

// App command to run the dialog
void CGDevStudioApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


// CGDevStudioApp message handlers


void CGDevStudioApp::PreLoadState()
{
}

void CGDevStudioApp::OnFileNew()
{
	CBCGPWinApp::OnFileNew();
}

void CGDevStudioApp::OnFileOpen()
{
	CBCGPWinApp::OnFileOpen();
}


#include "DObject/Projet.h"
#include "DObject/Filtre.h"
using namespace GDSObject;

void CGDevStudioApp::Test()
{
	// Base de données
	CSQLiteSource::instance().New();

	//
	CProjet* pProjet = new CProjet();
	pProjet->SetLibelle("TEST");
	pProjet->Sauver();
	pProjet->SetDescription("Description du projet");
	pProjet->Sauver();

	CFiltre* pFiltre1 = new CFiltre();
	pFiltre1->SetLibelle("Filtre01");

	CFiltre* pFiltre2 = new CFiltre();
	pFiltre2->SetLibelle("Filtre02");

	CFiltreListe* pFiltreProjet = pProjet->GetFiltreListe(false);
	pFiltreProjet->Add(pFiltre1);
	pFiltreProjet->Add(pFiltre2);
	pProjet->Sauver();

	delete pProjet;
}
