
// Inclusions
#include "stdafx.h"
#include "GDevStudio.h"
#include "ProjetDlg.h"


IMPLEMENT_DYNAMIC(CProjetDlg, CBCGPDialog)


CProjetDlg::CProjetDlg(CWnd* pParent /*=NULL*/)
	: CBCGPDialog(CProjetDlg::IDD, pParent)
{
	EnableVisualManagerStyle(TRUE,TRUE);
	EnableLayout();
}

CProjetDlg::~CProjetDlg()
{
}

void CProjetDlg::DoDataExchange(CDataExchange* pDX)
{
	CBCGPDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_PROJET_CODE, m_edtCode);
	DDX_Control(pDX, IDC_PROJET_DESCRIPTION, m_edtDescription);
	DDX_Control(pDX, IDC_PROJET_FICHIER_H, m_edtEmplacementFichierH);
	DDX_Control(pDX, IDC_PROJET_FICHIER_CPP, m_edtEmplacementFichierCpp);
	DDX_Control(pDX, IDC_LBL_INFO, m_lblInfo);
	DDX_Control(pDX, IDC_LBL_CODE, m_lblCode);
	DDX_Control(pDX, IDC_LBL_DESCRIPTION, m_lblDescription);
	DDX_Control(pDX, IDC_LBL_REPERTOIRES, m_lblRepertoires);
	DDX_Control(pDX, IDC_LBL_FICHIER_H, m_lblFichierH);
	DDX_Control(pDX, IDC_LBL_FICHIER_CPP, m_lblFichierCpp);
}


BEGIN_MESSAGE_MAP(CProjetDlg, CBCGPDialog)
END_MESSAGE_MAP()


BOOL CProjetDlg::OnInitDialog()
{
	CBCGPDialog::OnInitDialog();

	// Layout
	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
	if (pLayout != NULL)
	{
		pLayout->AddAnchor(m_edtCode, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
		pLayout->AddAnchor(m_edtDescription, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeBoth);

		pLayout->AddAnchor(m_lblRepertoires, CBCGPStaticLayout::e_MoveTypeVert, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(m_lblFichierH, CBCGPStaticLayout::e_MoveTypeVert, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(m_lblFichierCpp, CBCGPStaticLayout::e_MoveTypeVert, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(m_edtEmplacementFichierH, CBCGPStaticLayout::e_MoveTypeVert, CBCGPStaticLayout::e_SizeTypeHorz);
		pLayout->AddAnchor(m_edtEmplacementFichierCpp, CBCGPStaticLayout::e_MoveTypeVert, CBCGPStaticLayout::e_SizeTypeHorz);

		pLayout->AddAnchor(IDOK, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone);
		pLayout->AddAnchor(IDCANCEL, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone);
	}
	//
	SetFontBoldUnderline(&m_lblInfo);
	SetFontBoldUnderline(&m_lblRepertoires);
	m_edtEmplacementFichierH.EnableFolderBrowseButton(L"Emplacement dse fichiers *.h", BIF_USENEWUI);
	m_edtEmplacementFichierCpp.EnableFolderBrowseButton(L"Emplacement dse fichiers *.cpp", BIF_USENEWUI);

	return FALSE;  // return TRUE unless you set the focus to a control
}
