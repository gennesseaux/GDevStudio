
// Inclusions
#include "stdafx.h"
#include "GDevStudio.h"
#include "TreeGrille.h"

// Inclusions
#include "TreeIconMgr.h"

// Macros
#define NbColumns 1


IMPLEMENT_DYNAMIC(CTreeGrille, CBCGPGridCtrl)

BEGIN_MESSAGE_MAP(CTreeGrille, CBCGPGridCtrl)
END_MESSAGE_MAP()


// Constructeur
CTreeGrille::CTreeGrille()
{
	// Paramétrage de la grille
	InitialiserProprites();
	// Images dans la grille
	InitialiserImages();
}

// Destructeur
CTreeGrille::~CTreeGrille()
{
}

// Création de la grille
BOOL CTreeGrille::Create(CView* pView)
{
	ASSERT_VALID(pView);

	// La grille sera contenue dans toute la vue parent
	CRect rectClient;
	pView->GetClientRect(rectClient);

	// Création de la grillle
	if (!CBCGPGridCtrl::Create(WS_CHILD, rectClient, pView, 1))
	{
		ASSERT(FALSE);
		return FALSE;
	}

	// Affichage de la grille
	SetScrollBarsStyle(CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);
	ShowWindow(SW_SHOW);

	return TRUE;
}

// Paramétrage de la grille
void CTreeGrille::InitialiserProprites()
{
	// Propriétés
	EnableColumnAutoSize(TRUE);
	SetSingleSel(FALSE);
	SetWholeRowSel();
	SetReadOnly();
	EnableGroupByBox(FALSE);
	EnableHeader(FALSE, 0);
	EnableGridLines(FALSE);

	// Colonne par défaut
	InsertColumn(0, _T("Tree"), 100);

	// Couleur de la grille
	CBCGPGridColors colors;
	colors.m_LeftOffsetColors.m_clrBackground = globalData.clrWindow;
	SetColorTheme(colors);
}

// Images dans la grille
void CTreeGrille::InitialiserImages()
{
	if (m_pTreeImageMgr == nullptr)
		m_pTreeImageMgr = new CTreeIconMgr(this);

	//// Create root item:
	//CBCGPGridRow* pRoot = CreateRow(1);
	//ASSERT_VALID(pRoot);
	//pRoot->AllowSubItems();
	//pRoot->GetItem(0)->SetValue(_T("My Computer"));
	//pRoot->GetItem(0)->SetImage(m_pTreeImageMgr->GetIndex(TreeImage::Projet));
	//AddRow(pRoot, FALSE);
	//
	//CBCGPGridRow* pDiskC = CreateRow(1);
	//ASSERT_VALID(pDiskC);
	//pDiskC->GetItem(0)->SetValue(_T("My Local Disk (C:)"));
	//pDiskC->AllowSubItems();
	//pDiskC->GetItem(0)->SetImage(m_pTreeImageMgr->GetIndex(TreeImage::Filtre));
	//pRoot->AddSubItem(pDiskC, FALSE);
}

// Initialisation de la grille
void CTreeGrille::Initialiser(GDSObject::CProjet* pProjet)
{

}

// Manageur d'icones
CTreeIconMgr* CTreeGrille::GetTreeImageMgr() const
{
	return m_pTreeImageMgr;
}



