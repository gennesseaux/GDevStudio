
// Inclusions
#include "stdafx.h"
#include "GDevStudio.h"
#include "TreeGrille.h"

// Inclusions
#include "TreeIconMgr.h"
#include "StructureMgr.h"
#include "SItemStructure.h"
#include "Outils\MenuFunctions\MenuFunctions.h"

// Macros
#define NbColumns 1


IMPLEMENT_DYNAMIC(CTreeGrille, CBCGPGridCtrl)

BEGIN_MESSAGE_MAP(CTreeGrille, CBCGPGridCtrl)
	ON_WM_CONTEXTMENU()

	// --------------------------------------------------
	//			-~  COMMANDES LIEES AU MENU ~-
	// --------------------------------------------------
	ON_COMMAND(IDMS__NOUVEAU_FILTRE,		&CTreeGrille::OnNouveauFilte)
	ON_COMMAND(IDMS__MODIFIER,				&CTreeGrille::OnModifier)
	ON_COMMAND(IDMS__SUPPRIMER,				&CTreeGrille::OnSupprimer)

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

void CTreeGrille::SetRowHeight ()
{
	CBCGPGridCtrl::SetRowHeight();
	
	if (!m_bIsPrinting)
	{
		CBCGPGridCtrl::SetRowHeight();

		m_nBaseHeight = m_nBaseHeight + 3;
		m_nRowHeight = m_nBaseHeight;
		m_nLargeRowHeight = m_nBaseHeight;
		m_nButtonWidth = m_nBaseHeight;
	}
}

void CTreeGrille::OnFillLeftOffset(CDC* pDC, CRect rectFill, CBCGPGridRow* pRow, BOOL bDrawRightBorder /*= TRUE*/)
{
	CBCGPGridCtrl::OnFillLeftOffset(pDC, rectFill, pRow, bDrawRightBorder);
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
	SetSelectionBorder(FALSE);
	//SetRowMarker(TRUE);

	// Colonne par défaut
	InsertColumn(0, _T("Tree"), 100);

	// Couleur de la grille
	CBCGPGridColors theme;
	CBCGPVisualManager::GetInstance ()->OnSetGridColorTheme(this, theme);
	theme.m_clrText								= globalData.clrWindowText;
	theme.m_LeftOffsetColors.m_clrBackground	= theme.m_clrBackground;
	theme.m_LeftOffsetColors.m_clrText			= theme.m_clrText;
	theme.m_SelColors.m_clrBackground			= RGB(43,87,154);
	theme.m_SelColors.m_clrText					= globalData.clrTextHilite;
	theme.m_GroupSelColors.m_clrBackground		= RGB(43,87,154);
	theme.m_GroupSelColors.m_clrText			= globalData.clrTextHilite;
	SetColorTheme(theme);
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

//
CSItemStructure* CTreeGrille::GetSelectedItem()
{
	CList <CBCGPGridItem*, CBCGPGridItem*> lstSelected;
	GetSelectedItems(lstSelected);
	
	return lstSelected.GetCount() ?  (CSItemStructure*)lstSelected.GetHead()->GetParentRow()->GetData() : nullptr; 
}

// Menu
void CTreeGrille::OnContextMenu(CWnd* pWnd, CPoint point)
{
	// Position de la souris dans la grille
	CPoint Gpoint = point;
	ScreenToClient(&Gpoint);

	// Information de la grille sous le point
	CBCGPGridRow::ClickArea clickArea;
	CBCGPGridItemID id;
	CBCGPGridItem* pHitItem = nullptr;
	CBCGPGridRow* pHitRow = HitTest(Gpoint, id, pHitItem, &clickArea);

	// Création du nouveau menu 
	HMENU hMenu = ::CreatePopupMenu();
	CMenu* pMenu = CMenu::FromHandle(hMenu);

	// Récupère le CSItemStructure
	CSItemStructure* pSItem = pHitRow ? (CSItemStructure*)pHitRow->GetData() : nullptr;
	

	// Ajout des lignes du menu
	// ------------------------
	
	// -> Nouveau 
	bool bFiltre =	IsFiltreAllowed(pSItem);
	if(bFiltre)		MenuFunctions::AddMenuItem(hMenu, _T("Filtre"),		IDMS__NOUVEAU_FILTRE);

 	if(bFiltre)
 		MenuFunctions::AddMenuItem(hMenu, _T("Séparateur"), 0);

	
	// -> Modifier
	// -> Suprimer 
	bool bModifier =	IsModifierAllowed(pSItem);
	bool bSuprimer =	IsSupprimerAllowed(pSItem);
	MenuFunctions::AddMenuItem(hMenu, _T("Modifier"),			IDMS__MODIFIER);
	MenuFunctions::AddMenuItem(hMenu, _T("Supprimer\tSuppr"),	IDMS__SUPPRIMER);
	MenuFunctions::EnableMenuItem(hMenu,IDMS__MODIFIER,bModifier);
	MenuFunctions::EnableMenuItem(hMenu,IDMS__SUPPRIMER,bSuprimer);
	MenuFunctions::AddMenuItem(hMenu, _T("Séparateur"), 0);


	// Affiche le menu
	theApp.GetContextMenuManager ()->ShowPopupMenu(hMenu,point.x,point.y,this,TRUE);
}

// Filtre
bool CTreeGrille::IsFiltreAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;
	if(pSItem->GetTypeItem() == SItemType::Filtre)		return true;

	return false;
}

bool CTreeGrille::IsModifierAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;
	if(pSItem->GetTypeItem() == SItemType::Projet)		return true;
	if(pSItem->GetTypeItem() == SItemType::Filtre)		return true;

	return false;
}

bool CTreeGrille::IsSupprimerAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;
	if(pSItem->GetTypeItem() == SItemType::Filtre)		return true;

	return false;
}


void CTreeGrille::OnNouveauFilte()
{

}

void CTreeGrille::OnModifier()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	switch (pSItem->GetTypeItem())
	{
		case SItemType::Projet :
			OnModifierProjet(pSItem);
			break;

		case SItemType::Filtre :
			OnModifierFilte(pSItem);
			break;

		default :
			break;
	}
}

void CTreeGrille::OnModifierProjet(CSItemStructure* pSItem)
{
	// Test de cohérence
	if(!IsModifierAllowed(pSItem)) return;

}

void CTreeGrille::OnModifierFilte(CSItemStructure* pSItem)
{
	// Test de cohérence
	if(!IsModifierAllowed(pSItem)) return;

}

void CTreeGrille::OnSupprimer()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if(pSItem == nullptr) return;

	switch (pSItem->GetTypeItem())
	{
		case SItemType::Filtre :
			OnSupprimerFilte(pSItem);
			break;

		default :
			break;
	}
}

bool CTreeGrille::OnSupprimerFilte(CSItemStructure* pSItem)
{
	// Test de cohérence
	if(!IsSupprimerAllowed(pSItem)) return false;

	return false;
}



