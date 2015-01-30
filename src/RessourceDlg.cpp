
// Inclusions
#include "Stdafx.h"
#include "GDevStudio.h"
#include "RessourceDlg.h"


IMPLEMENT_DYNAMIC(CRessourceDlg, CDialogEx)


// Constructeur
CRessourceDlg::CRessourceDlg(GDSObject::CRessource* pRessource, CWnd* pParent /*=NULL*/) : CGDevStudioDialogBase(CRessourceDlg::IDD, pParent)
{
	m_pRessource = pRessource;
}

// Destructeur
CRessourceDlg::~CRessourceDlg()
{
	delete m_pRcReader;
}

// Prise en charge de DDX/DDV
void CRessourceDlg::DoDataExchange(CDataExchange* pDX)
{
	CGDevStudioDialogBase::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_edtEmplacement);
	DDX_Control(pDX, IDC_COMBO1, m_cbxRessource);
	DDX_Control(pDX, IDOK, m_btnAjouter);
	DDX_Control(pDX, IDCANCEL, m_btnAnnuler);
}


BEGIN_MESSAGE_MAP(CRessourceDlg, CGDevStudioDialogBase)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1,	&CRessourceDlg::OnEmplacementChange)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CRessourceDlg::OnRessourceChange)
	ON_BN_CLICKED(IDOK, &CRessourceDlg::OnAjouter)
END_MESSAGE_MAP()


BOOL CRessourceDlg::OnInitDialog()
{
	// Initialisation par défaut.
	CGDevStudioDialogBase::OnInitDialog();

	// Terminé.
	return FALSE;
}

// Initialise les objets métiers.
void CRessourceDlg::InitialiseObjetsMetiers()
{
	if(m_pRessource)	m_pRessource->Initialiser();
}

// Initialisation de l'interface utilisateur.
void CRessourceDlg::InitialiseInterfaceUtilisateur()
{
	// Contrôles
	m_edtEmplacement.EnableFileBrowseButton(NULL, _T("Fichier ressource (*.rc)|*.rc|"));

 	// Layout
 	CBCGPStaticLayout* pLayout = (CBCGPStaticLayout*)GetLayout();
 	if (pLayout != NULL)
 	{
 		pLayout->AddAnchor(m_edtEmplacement, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
 		pLayout->AddAnchor(m_cbxRessource, CBCGPStaticLayout::e_MoveTypeNone, CBCGPStaticLayout::e_SizeTypeHorz);
 
 		pLayout->AddAnchor(IDOK, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone);
 		pLayout->AddAnchor(IDCANCEL, CBCGPStaticLayout::e_MoveTypeBoth, CBCGPStaticLayout::e_SizeTypeNone);
 	}
}

// Initialisation.
void CRessourceDlg::Initialiser()
{
	/* Pas de mise à jour des contraintes intempestives */
	m_bUpdateConstraints = false;

	/* Initialisation */

	/* La mise à jour des contraintes est à nouveau autorisée */
	m_bUpdateConstraints = true;

	/* Mise à jour des contraintes. */
	UpdateConstraints();
}

// Mise à jour des contraintes.
void CRessourceDlg::UpdateConstraints()
{
	m_cbxRessource.EnableWindow(m_cbxRessource.GetCount()?TRUE:FALSE);

 	// Validation du bouton OK
 	m_btnAjouter.EnableWindow(m_pRessource->Verifier());
}


void CRessourceDlg::OnEmplacementChange()
{
	CWaitCursor cur;

	//
	CString sEmplacement = GetCWndWindowText(&m_edtEmplacement);
	m_pRessource->SetFile(ToStdString(sEmplacement));

	// Chargement du fichier RC
	delete m_pRcReader;
	m_pRcReader = new RcReader::CRcReader(ToStdString(sEmplacement));

	// Mise à jour du comboBox
	m_cbxRessource.ResetContent();
	int iDlg = m_pRcReader->GetDialogCount();
	for (int i = 0; i < iDlg ; i++)
	{
		RcReader::CRcResourceDialog* pResDlg = m_pRcReader->GetDialog(i);
		m_cbxRessource.AddString(ToString(pResDlg->GetId()));
	}

	/* Mise à jour des contraintes. */
	UpdateConstraints();
}


void CRessourceDlg::OnRessourceChange()
{
	int iDlg = m_cbxRessource.GetCurSel();
	m_pRcDialog = m_pRcReader->GetDialog(iDlg);

	m_pRessource->SetLibelle(m_pRcDialog->GetId());

	/* Mise à jour des contraintes. */
	UpdateConstraints();
}


void CRessourceDlg::OnAjouter()
{
	// Finalisation de la ressource
	for (int i = 0; i < m_pRcDialog->GetControlCount() ; i++)
	{
		// Récupération du control
		RcReader::CRcResourceControl rcControl = m_pRcDialog->GetControl(i);

		// Ajout du conrtol à la ressource
		GDSObject::CControle* pControl = new GDSObject::CControle();
		pControl->SetLibelle(rcControl.GetId());
		pControl->SetType(rcControl.GetControle().ToString());
		m_pRessource->GetControleListe()->Add(pControl);
	}

	// Sauvegarde
	if(m_pRessource->Sauver())
		CGDevStudioDialogBase::OnOK();
}
