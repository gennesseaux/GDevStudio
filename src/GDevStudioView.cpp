

// Inclusions
#include "stdafx.h"
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

IMPLEMENT_DYNCREATE(CGDevStudioView, CBCGPGridView)

BEGIN_MESSAGE_MAP(CGDevStudioView, CBCGPGridView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(BCGM_CHANGEVISUALMANAGER, &CGDevStudioView::OnChangeVisualManager)
END_MESSAGE_MAP()

// CGDevStudioView construction/destruction

CGDevStudioView::CGDevStudioView()
{
}

CGDevStudioView::~CGDevStudioView()
{
	delete m_pStructureMgr; m_pStructureMgr = nullptr;

	m_pTreeGrille = nullptr;
}

// CGDevStudioView drawing
void CGDevStudioView::OnDraw(CDC* /*pDC*/)
{
	CGDevStudioDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

BOOL CGDevStudioView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CBCGPGridView::PreCreateWindow(cs);
}


// CGDevStudioView diagnostics
#ifdef _DEBUG
void CGDevStudioView::AssertValid() const
{
	CBCGPGridView::AssertValid();
}
void CGDevStudioView::Dump(CDumpContext& dc) const
{
	CBCGPGridView::Dump(dc);
}
CGDevStudioDoc* CGDevStudioView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDevStudioDoc)));
	return (CGDevStudioDoc*)m_pDocument;
}
#endif //_DEBUG


int CGDevStudioView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Création de la grille
	m_pTreeGrille = new CTreeGrille();
	if (!m_pTreeGrille->Create(this))
		return -1;

	m_pWndGridCtrl = m_pTreeGrille;

	AdjustLayout();
	m_pWndGridCtrl->SetFocus();

	return 0;
}

BOOL CGDevStudioView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void CGDevStudioView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CGDevStudioView::AdjustLayout()
{
	if (m_pTreeGrille->GetSafeHwnd() == NULL)
		return;

	CRect rectClient;
	GetClientRect(rectClient);

	m_pTreeGrille->SetWindowPos(NULL, 0, 0, rectClient.Width(), rectClient.Height(), SWP_NOACTIVATE | SWP_NOZORDER);
}

void CGDevStudioView::OnSetFocus(CWnd* pOldWnd)
{
	CBCGPGridView::OnSetFocus(pOldWnd);

	if (m_pTreeGrille->GetSafeHwnd() != NULL)
		m_pTreeGrille->SetFocus();
}

void CGDevStudioView::OnDestroy()
{
	if (m_pTreeGrille->GetSafeHwnd() != NULL)
	{
		m_pTreeGrille->DestroyWindow();
		delete m_pTreeGrille;
		m_pTreeGrille = nullptr;
	}

	CBCGPGridView::OnDestroy();
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
  	// Initialisation de la grille
  	if(m_pStructureMgr==nullptr)
  		m_pStructureMgr = new CStructureMgr(GetDocument(),m_pTreeGrille);
  	m_pStructureMgr->Initialiser(GetDocument()->Projet()->GetId());
}

