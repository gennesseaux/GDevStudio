// MainFrm.h : interface of the CMainFrame class
//


#pragma once


// Inclusions
#include "ProprieterViewBar.h"


class CMainFrame : public CBCGPFrameWnd
{
	DECLARE_DYNCREATE(CMainFrame)

protected:
	// Constructeur
	CMainFrame();
public:
	// Destructeur
	virtual ~CMainFrame();


public:
	//
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//
	CBCGPPropList*	GetPropertyGridCtrl()	{ return &(m_wndPropertiesBar.m_propertyList); }


// Implementation
public:
	#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	#endif

// Generated message map functions
protected:

	DECLARE_MESSAGE_MAP()

	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT	OnRibbonCustomize (WPARAM wp, LPARAM lp);
	afx_msg void	OnToolsOptions();

	BOOL			CreateRibbonBar();
	BOOL			CreateDockingBars();
	void			ShowOptions (int nPage);



// control bar embedded members
protected:  
	CBCGPRibbonStatusBar	m_wndStatusBar;
	CBCGPRibbonBar			m_wndRibbonBar;
	CBCGPMenuBar			m_wndMenuBar;
	CBCGPToolBar			m_wndToolBar;

	CProprieterViewBar		m_wndPropertiesBar;
};
