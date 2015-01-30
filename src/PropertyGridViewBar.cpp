// CProprieterViewBar.h :
//


// Inclusions
#include "stdafx.h"
#include "GDevStudio.h"
#include "MainFrm.h"
#include "PropertyGridViewBar.h"
#include "SItemStructure.h"


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
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_WM_PAINT()

	ON_REGISTERED_MESSAGE(BCGM_PROPERTY_CHANGED, &CProprieterViewBar::OnPropertyChanged)
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

	m_propertyList.SetWindowPos (NULL, x, y, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);
}

int CProprieterViewBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	if (!m_propertyList.Create(WS_VISIBLE | WS_CHILD | WS_BORDER | WS_TABSTOP, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	InitialiserPropertyGrid ();
	AdjustLayout ();

	return 0;
}

void CProprieterViewBar::InitialiserPropertyGrid ()
{
	// Setup general look:
	m_propertyList.EnableToolBar(FALSE);
	m_propertyList.EnableSearchBox(FALSE);
	m_propertyList.EnableHeaderCtrl(FALSE);
	m_propertyList.EnableDesciptionArea();
	m_propertyList.SetVSDotNetLook(FALSE);
	m_propertyList.MarkModifiedProperties(TRUE);
	m_propertyList.EnableContextMenu(TRUE);
}

void CProprieterViewBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);
	AdjustLayout ();
}

void CProprieterViewBar::OnSetFocus(CWnd* pOldWnd) 
{
	CBCGPDockingControlBar::OnSetFocus(pOldWnd);
	m_propertyList.SetFocus ();
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

LRESULT CProprieterViewBar::OnPropertyChanged(WPARAM wPram, LPARAM lParam)
{
	CBCGPProp* pProp = (CBCGPProp*) lParam;
	ASSERT_VALID(pProp);

	// Callback
	PG_ITEMCHANGED_CALLBACK fCbItemChanged = GetItemChangedCallback();
	if(fCbItemChanged!=NULL) return fCbItemChanged(pProp);

	return 0;
}
