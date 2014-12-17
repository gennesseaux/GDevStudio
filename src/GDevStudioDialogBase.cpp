
// Inclusions
#include "stdafx.h"
#include "GDevStudio.h"
#include "GDevStudioDialogBase.h"


IMPLEMENT_DYNAMIC(CGDevStudioDialogBase, CBCGPDialog)


// Construit une instance de la bo�te de dialogue.
CGDevStudioDialogBase::CGDevStudioDialogBase() : CBCGPDialog()
{
	PrivateConstruct();
}

// Construit une instance de la bo�te de dialogue.
CGDevStudioDialogBase::CGDevStudioDialogBase(LPCTSTR lpszTemplateName, CWnd* pParentWnd /*= NULL*/) : CBCGPDialog(lpszTemplateName,pParentWnd)
{
	PrivateConstruct();
}

// Construit une instance de la bo�te de dialogue.
CGDevStudioDialogBase::CGDevStudioDialogBase(UINT nIDTemplate, CWnd *pParentWnd /*= NULL*/) : CBCGPDialog(nIDTemplate,pParentWnd)
{
	PrivateConstruct();
}

// Destructeur
CGDevStudioDialogBase::~CGDevStudioDialogBase()
{
}

void CGDevStudioDialogBase::PrivateConstruct()
{
	EnableVisualManagerStyle(TRUE,TRUE);
	EnableLayout();
}


BEGIN_MESSAGE_MAP(CGDevStudioDialogBase, CBCGPDialog)
END_MESSAGE_MAP()


BOOL CGDevStudioDialogBase::OnInitDialog()
{
	// Initialisation par d�faut.
	CBCGPDialog::OnInitDialog();
	
	// Initialise les objets m�tiers.
	InitialiseObjetsMetiers();

	// Initialisation de l'interface utilisateur.
	InitialiseInterfaceUtilisateur();

	// Initialisation.
	Initialiser();

	// Termin�.
	return FALSE;
}
