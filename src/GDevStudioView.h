// GDevStudioView.h : interface of the CGDevStudioView class
//


#pragma once

// Inclusions
class CTreeGrille;


class CGDevStudioView : public CBCGPGridView
{
protected: // create from serialization only
	CGDevStudioView();
	DECLARE_DYNCREATE(CGDevStudioView)

// Attributes
public:
	//
	CGDevStudioDoc* GetDocument() const;
	//
	CStructureMgr* GetStructureMgr() { return m_pStructureMgr; }


// Operations
public:
	void AdjustLayout();


// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);


// Implementation
public:
	virtual ~CGDevStudioView();
	#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	#endif

protected:

// Generated message map functions
protected:

	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd*, CPoint point);

protected:
	CTreeGrille*	m_pTreeGrille = nullptr;
	CStructureMgr*	m_pStructureMgr = nullptr;
};

#ifndef _DEBUG  // debug version in GDevStudioView.cpp
inline CGDevStudioDoc* CGDevStudioView::GetDocument() const
   { return reinterpret_cast<CGDevStudioDoc*>(m_pDocument); }
#endif

