// CProprieterViewBar.h :
//


#pragma once


class CProprieterViewBar : public CBCGPDockingControlBar  
{
public:
	// Constructeur
	CProprieterViewBar();
	// Destructeur
	virtual ~CProprieterViewBar();
	//
	void AdjustLayout ();

protected:
	virtual void GetPaneInfo(CString& strName, CString& strInfo, HICON& hIcon, BOOL& bAutoDestroyIcon)
	{
		CBCGPDockingControlBar::GetPaneInfo(strName, strInfo, hIcon, bAutoDestroyIcon);
		strInfo = _T("Displays the property pages for the item currently selected.");
		
		if (hIcon == NULL)
		{
			//// Current Visual theme doesn't have docking pane icons:
			//int nImage = BCGPGetCmdMgr()->GetCmdImage(ID_VIEW_PROPERTIES, FALSE);
			//if (nImage >= 0)
			//{
			//	hIcon = CBCGPToolBar::GetImages()->ExtractIcon(nImage);
			//	bAutoDestroyIcon = TRUE;
			//}
		}
	}

	// Generated message map functions
protected:

	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSortingprop();
	afx_msg void OnUpdateSortingprop(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnExpand();
	afx_msg void OnUpdateExpand(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnPaint();

	void InitPropList ();

protected:
	CBCGPPropList		m_wndPropList;
};
