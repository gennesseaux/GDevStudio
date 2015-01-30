// CProprieterViewBar.h :
//


#pragma once


//
class CSItemStructure;



// Message envoyé lors d'un changement de l'item
const UINT WM_PG_ITEMCHANGED  = ::RegisterWindowMessage(_T("CProprieterViewBar-WM_PG_ITEMCHANGED"));
// Prototypage des fonctions callback pour la notification des changements des items
typedef LRESULT (CALLBACK* PG_ITEMCHANGED_CALLBACK) (CBCGPProp* pProperty);


class CProprieterViewBar : public CBCGPDockingControlBar  
{
	friend class CMainFrame;

public:
	// Constructeur
	CProprieterViewBar();
	// Destructeur
	virtual ~CProprieterViewBar();
	// Ajustement du layout
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


protected:

	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnPaint();

	void InitialiserPropertyGrid ();

	afx_msg LRESULT OnPropertyChanged(WPARAM lParam,LPARAM wPram);
	

public:
  // callback
  const PG_ITEMCHANGED_CALLBACK	GetItemChangedCallback() const { return m_fCbItemChanged; };
  void	SetItemChangedCallback( PG_ITEMCHANGED_CALLBACK fCbItemChanged ) { m_fCbItemChanged = fCbItemChanged; };

protected:
	CBCGPPropList			m_propertyList;

	/* Callback */
	PG_ITEMCHANGED_CALLBACK	m_fCbItemChanged = nullptr;
};
