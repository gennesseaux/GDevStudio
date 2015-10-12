// GDevStudio.cpp : Defines the class behaviors for the application.
//

#include "Stdafx.h"
#include "GDevStudio/GDevStudio.h"
#include "GDevStudio/MainFrm.h"

#include "GDevStudio/GDevStudioDoc.h"
#include "GDevStudio/GDevStudioView.h"
//#include "IPluginRessourceGenerateur.h"
//#include "IPluginClasseGenerateur.h"

// Inclusions
#include "GDevStudioApi/SQLiteSource.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#include <crtdbg.h>
#endif


// CGDevStudioApp

BEGIN_MESSAGE_MAP(CGDevStudioApp, CBCGPWinApp)
	ON_COMMAND(ID_APP_ABOUT,		&CGDevStudioApp::OnAppAbout)
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW,			&CGDevStudioApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN,		&CGDevStudioApp::OnFileOpen)
END_MESSAGE_MAP()


// CGDevStudioApp construction

CGDevStudioApp::CGDevStudioApp()
{
	SetVisualTheme(CBCGPWinApp::BCGP_VISUAL_THEME_OFFICE_2013_GRAY);
	CBCGPVisualManagerVS2013::SetAccentColor(CBCGPVisualManagerVS2012::VS2012_Blue);

	globalData.m_bUseVisualManagerInBuiltInDialogs = TRUE;
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

	AfxEnableControlContainer();

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

	// Initialize all Managers for usage. They are automatically constructed
	// if not yet present
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CGDevStudioDoc),
		RUNTIME_CLASS(CMainFrame),
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

#ifdef _DEBUG
	size_t nbModules = _ModulesManager.getRessourcesServer().getModulesCount();
	GDSMM::CRessourcesServer::CRessourceModule* pModule = _ModulesManager.getRessourcesServer().getModule(0);
	GDSMM::CRessourcesServer::CRessourceModule* pModule2 = _ModulesManager.getRessourcesServer().getModule(Poco::UUID("b49589d4-aae9-11e4-89d3-123b93f75cba"));
	int toto = 0;
#endif

	// Ouverture d'un projet par défaut
	OnFileNew();

	// The one and only window has been initialized, so show and update it
	m_pMainWnd->ShowWindow(SW_SHOW);
 	CRect rect;
 	m_pMainWnd->GetWindowRect (rect);
 	m_pMainWnd->SetWindowPos (NULL, -1, -1, rect.Width (), rect.Height (), SWP_NOZORDER | SWP_NOMOVE | SWP_NOACTIVATE);
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
	//CBCGPURLLinkButton m_btnURL;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

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
	//DDX_Control(pDX, IDC_COMPANY_URL, m_btnURL);
}

BOOL CAboutDlg::OnInitDialog()
{
	SetFontBold(GetDlgItem(IDC_TITRE));
	return FALSE;
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

GDSMM::CModulesManager* CGDevStudioApp::ModulesManager()
{
	return  &_ModulesManager;
}

GDSMM::CModulesEvents* CGDevStudioApp::ModulesEvents()
{
	return  &_ModulesEvents;
}
