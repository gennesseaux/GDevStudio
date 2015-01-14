// MainFrm.cpp : implementation of the CMainFrame class
//

#include "Stdafx.h"
#include "GDevStudio.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CBCGPFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CBCGPFrameWnd)
	ON_WM_CREATE()
	ON_REGISTERED_MESSAGE(BCGM_ON_RIBBON_CUSTOMIZE, OnRibbonCustomize)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//--------------------------------
	// Cr�ation du rubban
	//--------------------------------
	if (!CreateRibbonBar())
	{
		TRACE0("Failed to create ribbon bar\n");
		return -1;      // fail to create
	}
	
	//--------------------------------
	// Cr�ation des barres ancrables
	//--------------------------------
	if (!CreateDockingBars())
	{
		TRACE0("Failed to create docking bars\n");
		return -1;      // fail to create
	}

	
	//--------------------------------
	// Cr�ation ed la barre de status
	//--------------------------------
	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	
	CBCGPToolBar::SetMenuSizes (CSize (22, 22), CSize (16, 16));
	CBCGPToolBar::AddToolBarForImageCollection (IDR_TOOLBAR_IMAGES
												, IDB_TOOLBAR_IMAGES_16		// Hot
												, IDB_TOOLBAR_IMAGES_16		// Cold
												, IDB_TOOLBAR_IMAGES_16		// Menu
												, IDB_TOOLBAR_IMAGES_D16	// Disable
												, IDB_TOOLBAR_IMAGES_D16);	// Menu Disable


	//// TODO: add your status bar panes here:
	//m_wndStatusBar.AddElement (new CBCGPRibbonStatusBarPane (
	//	ID_STATUSBAR_PANE1, _T("Pane 1"), TRUE), _T("Pane 1"));
	//m_wndStatusBar.AddExtendedElement (new CBCGPRibbonStatusBarPane (
	//	ID_STATUSBAR_PANE2, _T("Pane 2"), TRUE), _T("Pane 2"));

	// Ancrage
	m_wndPropertiesBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);

	DockControlBar(&m_wndPropertiesBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CBCGPFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CBCGPFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CBCGPFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame message handlers




BOOL CMainFrame::CreateRibbonBar ()
{
	if (!m_wndRibbonBar.Create(this))
	{
		return FALSE;
	}

	if (!m_wndRibbonBar.LoadFromXML (_T("IDR_BCGP_RIBBON_XML")))
	{
		return FALSE;
	}
 // USE_RIBBON_DESIGNER

	m_wndRibbonBar.EnablePrintPreview(FALSE);
	m_wndRibbonBar.EnableMinimizeButton(TRUE);
	m_wndRibbonBar.EnableCustomization(FALSE);

	return TRUE;
}

BOOL CMainFrame::CreateDockingBars()
{
	//-----------------------
	// Propri�t�s
	//-----------------------
	if (!m_wndPropertiesBar.Create(_T("Propri�t�s"), this, CRect (0, 0, 300, 200),
		TRUE, 
		ID_VIEW_PROPRIETES,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create Properties Bar\n");
		return FALSE;		// fail to create
	}

	return TRUE;
}


LRESULT CMainFrame::OnRibbonCustomize (WPARAM wp, LPARAM /*lp*/)
{
	ShowOptions (wp == 0 ? 1 : 0);
	return 1;
}

void CMainFrame::OnToolsOptions()
{
	ShowOptions (0);
}

void CMainFrame::ShowOptions (int nPage)
{
	// Create custom categories:
	
	// "Popular" items:
	
	CList<UINT, UINT> lstPopular;
	
	lstPopular.AddTail (ID_FILE_NEW);
	lstPopular.AddTail (ID_FILE_OPEN);
	lstPopular.AddTail (ID_FILE_SAVE);
	lstPopular.AddTail (ID_EDIT_UNDO);
	
	// Hidden commands:
	CList<UINT,UINT> lstHidden;
	m_wndRibbonBar.GetItemIDsList (lstHidden, TRUE);
	
	// All commands:
	CList<UINT,UINT> lstAll;
	m_wndRibbonBar.GetItemIDsList (lstAll);

	// Create "Customize QAT" page:
	CBCGPRibbonCustomizeQATPage pageCustomizeQAT(&m_wndRibbonBar);
	
	pageCustomizeQAT.AddCustomCategory (_T("Popular Commands"), lstPopular);
	pageCustomizeQAT.AddCustomCategory (_T("Commands not in the Ribbon"), lstHidden);
	pageCustomizeQAT.AddCustomCategory (_T("All Commands"), lstAll);
	
	// Create property sheet:
	CBCGPPropertySheet propSheet (_T("Options"), this, nPage);
	propSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;
	propSheet.EnableLayout();
	
	propSheet.SetLook(CBCGPPropertySheet::PropSheetLook_List, 150 /* List width */);
	
	propSheet.AddPage (&pageCustomizeQAT);

	// TODO: add your option pages here:
	// COptionsPage1 pageOptions1;
	// propSheet.AddPage (&pageOptions1);
	//
	// COptionsPage1 pageOptions2;
	// propSheet.AddPage (&pageOptions2);
	
	if (propSheet.DoModal() != IDOK)
	{
		return;
	}
}
// WORKSPACEBAR
 // OUTPUTBAR
 // PROPERTYBAR
 // UI_TYPE_RIBBON

