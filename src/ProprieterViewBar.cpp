// CProprieterViewBar.h :
//


// Inclusions
#include "stdafx.h"
#include "GDevStudio.h"
#include "MainFrm.h"
#include "ProprieterViewBar.h"


// Constructeur
CProprieterViewBar::CProprieterViewBar()
{
}

// Deswtructeur
CProprieterViewBar::~CProprieterViewBar()
{
}

BEGIN_MESSAGE_MAP(CProprieterViewBar, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//ON_COMMAND(ID_SORTINGPROP, OnSortingprop)
	//ON_UPDATE_COMMAND_UI(ID_SORTINGPROP, OnUpdateSortingprop)
	//ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	//ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	//ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	//ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	//ON_COMMAND(ID_EXPAND, OnExpand)
	//ON_UPDATE_COMMAND_UI(ID_EXPAND, OnUpdateExpand)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

void CProprieterViewBar::AdjustLayout ()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int x = rectClient.left;
	int y = rectClient.top;
	int cx = rectClient.Width();
	int cy= rectClient.Height()-2;

	m_wndPropList.SetWindowPos (NULL, x, y, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
}

int CProprieterViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	InitPropList ();
	AdjustLayout ();

	return 0;
}

void CProprieterViewBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	AdjustLayout ();
}

void CProprieterViewBar::OnSortingprop() 
{
	m_wndPropList.SetAlphabeticMode ();
}

void CProprieterViewBar::OnUpdateSortingprop(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndPropList.IsAlphabeticMode ());
}

void CProprieterViewBar::OnExpand() 
{
	m_wndPropList.SetAlphabeticMode (FALSE);
}

void CProprieterViewBar::OnUpdateExpand(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (!m_wndPropList.IsAlphabeticMode ());
}

void CProprieterViewBar::OnProperties1() 
{
	// TODO: Add your command handler code here
	
}

void CProprieterViewBar::OnUpdateProperties1(CCmdUI* /*pCmdUI*/) 
{
	// TODO: Add your command update UI handler code here
	
}

void CProprieterViewBar::OnProperties2() 
{
	// TODO: Add your command handler code here
	
}

void CProprieterViewBar::OnUpdateProperties2(CCmdUI* /*pCmdUI*/) 
{
	// TODO: Add your command update UI handler code here
	
}

void CProprieterViewBar::InitPropList ()
{
	// Setup general look:
	m_wndPropList.EnableToolBar(FALSE);
	m_wndPropList.EnableSearchBox(FALSE);
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDesciptionArea();
	m_wndPropList.SetVSDotNetLook(FALSE);
	m_wndPropList.MarkModifiedProperties(TRUE);
	m_wndPropList.EnableContextMenu(TRUE);

	// Add properties:
	CBCGPProp* pGroup1 = new CBCGPProp (_T("Appearance"));

	pGroup1->AddSubItem (new CBCGPProp (_T("3D Look"), (_variant_t) false,
		_T("Specifies the dialog's font will be non-bold and controls will have a 3D border")));

	CBCGPProp* pProp = new CBCGPProp (_T("Border"), _T("Dialog Frame"),
		_T("One of: None, Thin, Resizable, or Dialog Frame"));
	pProp->AddOption (_T("None"));
	pProp->AddOption (_T("Thin"));
	pProp->AddOption (_T("Resizable"));
	pProp->AddOption (_T("Dialog Frame"));
	pProp->AllowEdit (FALSE);

	pGroup1->AddSubItem (pProp);
	pGroup1->AddSubItem (new CBCGPProp (_T("Caption"), (_variant_t) _T("About BCGProTest"),
		_T("Specifies the text that will be displayed in the dialog's title bar")));

	m_wndPropList.AddProperty (pGroup1);

}

void CProprieterViewBar::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus ();
}

void CProprieterViewBar::OnSettingChange(UINT uFlags, LPCTSTR lpszSection) 
{
	CBCGPDockingControlBar::OnSettingChange(uFlags, lpszSection);
}

void CProprieterViewBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	CRect rectClient;
	GetClientRect(&rectClient);

	dc.FillRect(rectClient, &globalData.brBarFace);
}
