

// Inclusions
#include "Stdafx.h"
#include "GDevStudio.h"

// Inclusions
#include "GDevStudioDoc.h"
#include "GDevStudioView.h"

// Inclusions
#include "TreeGrille.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGDevStudioView

IMPLEMENT_DYNCREATE(CGDevStudioView, CView)

BEGIN_MESSAGE_MAP(CGDevStudioView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_SETFOCUS()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CGDevStudioView construction/destruction

CGDevStudioView::CGDevStudioView()
{
}

CGDevStudioView::~CGDevStudioView()
{
}

// CGDevStudioView drawing
void CGDevStudioView::OnDraw(CDC* pDC)
{
	CGDevStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CRect rectClient;
	GetClientRect(rectClient);

	pDC->FillRect(rectClient, &globalData.brWindow);
}

BOOL CGDevStudioView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}


// CGDevStudioView diagnostics
#ifdef _DEBUG
void CGDevStudioView::AssertValid() const
{
	CView::AssertValid();
}
void CGDevStudioView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CGDevStudioDoc* CGDevStudioView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDevStudioDoc)));
	return (CGDevStudioDoc*)m_pDocument;
}
#endif //_DEBUG


CTreeGrille* CGDevStudioView::GetGrille()
{
	if(m_pTreeGrille==nullptr)
	{
		m_pTreeGrille = new CTreeGrille();
		if(!m_pTreeGrille->Create(this))
			delete m_pTreeGrille;
	}
	return m_pTreeGrille;
}

int CGDevStudioView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Création de la grille
	if(!GetGrille())
		return -1;

	return 0;
}

void CGDevStudioView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	AdjustLayout();
}

void CGDevStudioView::AdjustLayout()
{
	if(GetGrille() && GetGrille()->GetSafeHwnd () != NULL)
	{
		CRect rectClient;
		GetClientRect(rectClient);

		rectClient.DeflateRect(0,6,0,2);
		int x = rectClient.left;
		int y = rectClient.top;
		int cx = rectClient.Width();
		int cy = rectClient.Height();

		m_pTreeGrille->SetWindowPos(NULL, x, y, cx, cy, SWP_NOZORDER | /*SWP_NOMOVE |*/ SWP_NOACTIVATE);
	}
}

BOOL CGDevStudioView::OnEraseBkgnd(CDC* /*pDC*/) 
{
	return TRUE;
}

void CGDevStudioView::OnSetFocus(CWnd* pOldWnd)
{
	CView::OnSetFocus(pOldWnd);

	if (m_pTreeGrille->GetSafeHwnd() != NULL)
		m_pTreeGrille->SetFocus();
}

void CGDevStudioView::OnDestroy()
{
	delete m_pStructureMgr; m_pStructureMgr = nullptr;

	if (m_pTreeGrille->GetSafeHwnd() != NULL)
	{
		m_pTreeGrille->DestroyWindow();
		delete m_pTreeGrille; m_pTreeGrille = nullptr;
	}

	CView::OnDestroy();
}

void CGDevStudioView::OnContextMenu(CWnd*, CPoint point)
{
// 	if (point.x == -1 && point.y == -1 && m_pCurrGrid != NULL)
// 	{
// 		//--------------------------------------------------------
// 		// Keyboard, show menu for the currently selected item(s):
// 		//--------------------------------------------------------
// 		CBCGPGridItem* pItem = m_pCurrGrid->GetCurSelItem();
// 		if (pItem != NULL)
// 		{
// 			CRect rectItem = pItem->GetRect();
// 			CPoint ptItem(rectItem.left, rectItem.bottom + 1);
// 
// 			if (m_pCurrGrid->GetListRect().PtInRect(ptItem))
// 			{
// 				point = ptItem;
// 				ClientToScreen(&point);
// 			}
// 		}
// 	}
// 
// 	BOOL bInsertMenu = FALSE;
// 	if (m_nCurrType == BCGGRID_DRAGNDROP)
// 	{
// 		CDragDropGridCtrl* pDragDropGrid = DYNAMIC_DOWNCAST(CDragDropGridCtrl, m_pCurrGrid);
// 		bInsertMenu = (pDragDropGrid != NULL && pDragDropGrid->IsSampleForDragDropRows());
// 	}
// 
// 	theApp.ShowPopupMenu(bInsertMenu ? IDR_CONTEXT_INSERT_MENU : IDR_CONTEXT_MENU, point, this);
}

void CGDevStudioView::OnInitialUpdate()
{
	// Suppression des bords de la vue
	ModifyStyleEx(WS_EX_CLIENTEDGE, 0, SWP_FRAMECHANGED); 
}


void CGDevStudioView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
  	// Initialisation de la grille
  	if(m_pStructureMgr==nullptr)
  		m_pStructureMgr = new CStructureMgr(GetDocument(),m_pTreeGrille);

	m_pStructureMgr->Initialiser(GetDocument()->GetProjetId());
	m_pStructureMgr->UpdateTitle();
}
