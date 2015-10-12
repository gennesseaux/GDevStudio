
// Inclusions
#include "Stdafx.h"
#include "GDevStudio/GDevStudio.h"
#include "GDevStudio/ProjetDlg.h"


IMPLEMENT_DYNAMIC(CProjetDlg, CGDevStudioDialogBase)


// Constructeur
CProjetDlg::CProjetDlg(GDSAPI::CProjet* pProjet ,CWnd* pParent /*=NULL*/) : CGDevStudioDialogBase(CProjetDlg::IDD, pParent)
{
	m_pProjet = pProjet;
}

// Destructeur
CProjetDlg::~CProjetDlg()
{
}

// Prise en charge de DDX/DDV
void CProjetDlg::DoDataExchange(CDataExchange* pDX)
{
	CGDevStudioDialogBase::DoDataExchange(pDX);

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
	DDX_Control(pDX, IDOK, m_btnOk);
}


BEGIN_MESSAGE_MAP(CProjetDlg, CGDevStudioDialogBase)
	ON_EN_CHANGE(IDC_PROJET_CODE,				&CProjetDlg::OnChange)
	ON_EN_CHANGE(IDC_PROJET_DESCRIPTION,		&CProjetDlg::OnChange)
	ON_EN_CHANGE(IDC_PROJET_FICHIER_H,			&CProjetDlg::OnChange)
	ON_EN_CHANGE(IDC_PROJET_FICHIER_CPP,		&CProjetDlg::OnChange)
	ON_BN_CLICKED(IDOK,							&CProjetDlg::OnOk)
END_MESSAGE_MAP()


BOOL CProjetDlg::OnInitDialog()
{
	// Initialisation par défaut.
	CGDevStudioDialogBase::OnInitDialog();

	// Terminé.
	return FALSE;
}

// Initialise les objets métiers.
void CProjetDlg::InitialiseObjetsMetiers()
{
	if(m_pProjet)	m_pProjet->Initialiser();
}

// Initialisation de l'interface utilisateur.
void CProjetDlg::InitialiseInterfaceUtilisateur()
{
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
	m_edtEmplacementFichierH.EnableFolderBrowseButton(L"Emplacement des fichiers *.h", BIF_USENEWUI);
	m_edtEmplacementFichierCpp.EnableFolderBrowseButton(L"Emplacement des fichiers *.cpp", BIF_USENEWUI);
}

// Initialisation.
void CProjetDlg::Initialiser()
{
	/* Pas de mise à jour des contraintes intempestives */
	m_bUpdateConstraints = false;

	/* Initialisation */
	SetCWndWindowText(&m_edtCode,m_pProjet->GetLibelle());
	SetCWndWindowText(&m_edtDescription,m_pProjet->GetDescription());
	SetCWndWindowText(&m_edtEmplacementFichierH,m_pProjet->GetHFolder().toString());
	SetCWndWindowText(&m_edtEmplacementFichierCpp,m_pProjet->GetCppFolder().toString());

	/* La mise à jour des contraintes est à nouveau autorisée */
	m_bUpdateConstraints = true;

	/* Mise à jour des contraintes. */
	UpdateConstraints();
}

// Mise à jour des contraintes.
void CProjetDlg::UpdateConstraints()
{
 	// Validation du bouton OK
 	m_btnOk.EnableWindow(m_pProjet->EstModifier());
}


void CProjetDlg::OnChange()
{
	if(!m_bUpdateConstraints) return;

	m_pProjet->SetLibelle(GetCWndWindowTextString(&m_edtCode));
	m_pProjet->SetDescription(GetCWndWindowTextString(&m_edtDescription));
	m_pProjet->SetHFolder(GetCWndWindowTextString(&m_edtEmplacementFichierH));
	m_pProjet->SetCppFolder(GetCWndWindowTextString(&m_edtEmplacementFichierCpp));

	// Mise à jour des contraintes.
	UpdateConstraints();
}


void CProjetDlg::OnOk()
{
	// Sauvegarde
	if(m_pProjet->Sauver())
		CGDevStudioDialogBase::OnOK();
}
