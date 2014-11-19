
#pragma once

// Inclusions


class CProjetDlg : public CBCGPDialog
{
	DECLARE_DYNAMIC(CProjetDlg)

public:
	//
	CProjetDlg(CWnd* pParent = NULL);
	//
	virtual ~CProjetDlg();

	// Données de boîte de dialogue
	enum { IDD = IDD_PROJET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

	DECLARE_MESSAGE_MAP()

protected:
	virtual BOOL OnInitDialog();

protected:
	// Contrôles
	CBCGPEdit m_edtCode;
	CBCGPEdit m_edtDescription;
	CBCGPEdit m_edtEmplacementFichierH;
	CBCGPEdit m_edtEmplacementFichierCpp;

	CBCGPStatic m_lblInfo;
	CBCGPStatic m_lblCode;
	CBCGPStatic m_lblDescription;
	CBCGPStatic m_lblRepertoires;
	CBCGPStatic m_lblFichierH;
	CBCGPStatic m_lblFichierCpp;

	CFont m_font;
};
