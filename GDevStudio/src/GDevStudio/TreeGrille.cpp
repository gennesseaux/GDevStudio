
// Inclusions
#include "Stdafx.h"
#include "GDevStudio/GDevStudio.h"

// Inclusions
#include "Outils\MenuFunctions\MenuFunctions.h"

// Inclusions
#include "GDevStudio/TreeGrille.h"
#include "GDevStudio/TreeRow.h"
#include "GDevStudio/TreeIconMgr.h"
#include "GDevStudio/StructureMgr.h"
#include "GDevStudio/SItemStructure.h"
#include "GDevStudio/SItemProjet.h"
#include "GDevStudio/SItemFiltre.h"
#include "GDevStudio/SItemRessource.h"
#include "GDevStudio/SItemControle.h"

// Inclusions
#include "GDevStudio/ProjetDlg.h"
#include "GDevStudio/RessourceDlg.h"

// Macros
#define NbColumns 1


IMPLEMENT_DYNAMIC(CTreeGrille, CBCGPGridCtrl)

BEGIN_MESSAGE_MAP(CTreeGrille, CBCGPGridCtrl)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CONTEXTMENU()

	// --------------------------------------------------
	//			-~  COMMANDES LIEES AU MENU ~-
	// --------------------------------------------------
	ON_COMMAND(IDMS__NOUVEAU_FILTRE,		&CTreeGrille::OnNouveauFiltre)
	ON_COMMAND(IDMS__NOUVEAU_RESSOURCE,		&CTreeGrille::OnNouveauRessource)
	ON_COMMAND(IDMS__MODIFIER,				&CTreeGrille::OnModifier)
	ON_COMMAND(IDMS__COUPER,				&CTreeGrille::OnCouper)
	ON_COMMAND(IDMS__COPIER,				&CTreeGrille::OnCopier)
	ON_COMMAND(IDMS__COLLER,				&CTreeGrille::OnColler)
	ON_COMMAND(IDMS__SUPPRIMER,				&CTreeGrille::OnSupprimer)
	ON_COMMAND(IDMS__RENOMMER,				&CTreeGrille::OnRenommer)
	ON_COMMAND(IDMS__EXCLURE,				&CTreeGrille::OnExclure)
	ON_COMMAND(IDMS__ACTUALISER,			&CTreeGrille::OnActualiser)
	
	ON_UPDATE_COMMAND_UI(IDMS__MODIFIER,	&CTreeGrille::OnUpdateMenu)
	ON_UPDATE_COMMAND_UI(IDMS__COUPER,		&CTreeGrille::OnUpdateMenu)
	ON_UPDATE_COMMAND_UI(IDMS__COPIER,		&CTreeGrille::OnUpdateMenu)
	ON_UPDATE_COMMAND_UI(IDMS__COLLER,		&CTreeGrille::OnUpdateMenu)
	ON_UPDATE_COMMAND_UI(IDMS__SUPPRIMER,	&CTreeGrille::OnUpdateMenu)
	ON_UPDATE_COMMAND_UI(IDMS__RENOMMER,	&CTreeGrille::OnUpdateMenu)

END_MESSAGE_MAP()


// Constructeur
CTreeGrille::CTreeGrille()
{
}

// Destructeur
CTreeGrille::~CTreeGrille()
{
	delete m_pTreeImageMgr; m_pTreeImageMgr = nullptr;
}

// Création de la grille
BOOL CTreeGrille::Create(CView* pView)
{
	ASSERT_VALID(pView);

	// La grille sera contenue dans toute la vue parent
	CRect rectClient;
	pView->GetClientRect(rectClient);

	// Création de la grillle
	if (!CBCGPGridCtrl::Create(WS_CHILD | WS_VISIBLE, rectClient, pView, 1))
	{
		ASSERT(FALSE);
		return FALSE;
	}

	// Affichage de la grille
	SetScrollBarsStyle(CBCGPScrollBar::BCGP_SBSTYLE_VISUAL_MANAGER);

	return TRUE;
}

CBCGPGridRow* CTreeGrille::CreateRow(CSItemStructure* pSItem)
{
	ASSERT_VALID (this);
	
	CBCGPGridRow* pRow = new CTreeRow(pSItem);
	ASSERT_VALID (pRow);

	SetupRow(pRow, 1);

	return pRow;
}

int CTreeGrille::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPGridCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Paramétrage de la grille
	InitialiserProprites();
	// Images dans la grille
	InitialiserImages();

	return 0;
}

void CTreeGrille::OnDestroy()
{
	CBCGPGridCtrl::OnDestroy();
}

BOOL CTreeGrille::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg && (pMsg->message == WM_SYSKEYDOWN) && (GetParent()))
	{
		// AltDown
		if (GetKeyState(VK_MENU) < 0)
		{
			//switch (pMsg->wParam)
			//{
			//case 'A':		SendMessage(WM_COMMAND, IDMS__FORMULAIRE_DEMANDE_ACHAT);	return TRUE; break;
			//case 'B':		SendMessage(WM_COMMAND, IDMS__MISE_EN_BARRE);				return TRUE; break;
			//case 'E':		SendMessage(WM_COMMAND, IDMS__FORMULAIRE_EDITION);			return TRUE; break;
			//case 'T':		SendMessage(WM_COMMAND, IDMS__FORMULAIRE_TRANSMISSION);		return TRUE; break;
			//}
		}
	}
	else if (pMsg && (pMsg->message == WM_KEYDOWN) && (GetParent()))
	{
		// CtrlDown
		if (GetKeyState(VK_CONTROL) < 0)
		{
			switch (pMsg->wParam)
			{
			case 'X':		SendMessage(WM_COMMAND, IDMS__COUPER);	return TRUE; break;
			case 'C':		SendMessage(WM_COMMAND, IDMS__COPIER);	return TRUE; break;
			case VK_INSERT:	SendMessage(WM_COMMAND, IDMS__COPIER);	return TRUE; break;
			case 'V':		SendMessage(WM_COMMAND, IDMS__COLLER);	return TRUE; break;
			}
		}
		// ShiftDown
		else if (GetKeyState(VK_SHIFT) < 0)
		{
			switch (pMsg->wParam)
			{
			case VK_DELETE:	SendMessage(WM_COMMAND, IDMS__COUPER);	return TRUE; break;
			case VK_INSERT:	SendMessage(WM_COMMAND, IDMS__COLLER);	return TRUE; break;
			}
		}
		else 
		{
			switch (pMsg->wParam)
			{
			case VK_F2:			SendMessage(WM_COMMAND, IDMS__RENOMMER);				return TRUE; break;
			case VK_F5:			SendMessage(WM_COMMAND, IDMS__ACTUALISER);				return TRUE; break;
			case VK_DELETE:		SendMessage(WM_COMMAND, IDMS__SUPPRIMER);				return TRUE; break;
			}
		}
	}

	return CBCGPGridCtrl::PreTranslateMessage(pMsg);
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

BOOL CTreeGrille::OnDrawItem (CDC* pDC, CBCGPGridRow* pRow)
{
	/* ********************************************************************
	 * Par défaut, l'expand box est dessiné avant la selection. Cependant,
	 * comme je force la selection à âtre dessinée sur l(intégralité de la 
	 * ligne (voir CTreeGrille::OnFillSelItem), l'expandbox n'est plus 
	 * visible car la selection se dessine par dessus.
	 * Par conséquent, j'ai recopier le code permettant de dessiner
	 * l'expandbox et je la redessine après avoir appelé OnDrawItem afin
	 * que celle-ci soit visible par dessus la selection.
	 * Au passge je change la couleur de l'expandbox pour plus de visibilité
	 *********************************************************************/

	// Dessine la ligne
	BOOL bRet = CBCGPGridCtrl::OnDrawItem(pDC, pRow);

	// Pas de dessin pour les lignes non visibles.
	if(pRow->GetRect().IsRectEmpty())
		return bRet;

	// Test si la ligne est selectionnée.
	BOOL bSelected = ((m_bSingleSel && m_bWholeRowSel) ? pRow->IsSelected () : pRow->GetItem(0)->IsSelected());
	

	// Mémorise la couleur utilisée dans le dessin de l'expandbox
	// puis la modifie si la ligne est selectionnée.
	COLORREF color = m_ColorData.m_GroupColors.m_clrText;
	if(bSelected)
		m_ColorData.m_GroupColors.m_clrText = m_ColorData.m_GroupColors.m_clrBackground;

	// --------------------------------------------------------------------
	// draw expandbox:
	// --------------------------------------------------------------------
	if(pRow->IsGroup() && (!IsSortingMode() || IsGrouping()) && pRow->GetSubItemsCount())
	{
		CRect rectExpand = pRow->GetRect();
		int dx = IsSortingMode() && !IsGrouping() ? 0 : pRow->GetHierarchyLevel() * GetHierarchyLevelOffset();

		int nLeftMargin = GetExtraHierarchyOffset() + dx;
		rectExpand.right = rectExpand.left + nLeftMargin;
		rectExpand.DeflateRect(dx,0,0,0);

		CRgn rgnClipExpand;
		CRect rectExpandClip = rectExpand;
		rectExpandClip.bottom = rectExpandClip.bottom;

		rgnClipExpand.CreateRectRgnIndirect(&rectExpandClip);
		pDC->SelectClipRgn(&rgnClipExpand);

		pRow->OnDrawExpandBox(pDC,rectExpand);

		pDC->SelectClipRgn(&m_rgnClip);
	}

	// On réapplique la couleur d'origine
	if(bSelected)
		m_ColorData.m_GroupColors.m_clrText = color;

	return bRet;
}

COLORREF CTreeGrille::OnFillSelItem(CDC* pDC,CRect rectFill,CBCGPGridItem* pItem)
{
	/* ********************************************************************
	 * Par défaut, la zone à gauche de l'item ne prend pas la couleur de la
	 * sélection. Pour avoir une ligne complètement selectionnée, j'appel
	 * normalement la méthode CBCGPGridCtrl::OnFillSelItem qui se charge de
	 * desinner la selection et je la détourne afin de dessiner la partie 
	 * de gauche.
	 *********************************************************************/

	//
	CRect rectLeft = rectFill;
	rectLeft.left = 0;
	rectLeft.right = rectFill.left;

	// Dessine la sélection à fauche de l'item
	m_rgnClipItem.DeleteObject ();
 	m_rgnClipItem.CreateRectRgnIndirect(&rectLeft);
 	pDC->SelectClipRgn(&m_rgnClipItem);
	CBCGPGridCtrl::OnFillSelItem(pDC, rectLeft, pItem);

	// Dessine la sélection de l'item
	m_rgnClipItem.DeleteObject ();
 	m_rgnClipItem.CreateRectRgnIndirect(&rectFill);
 	pDC->SelectClipRgn(&m_rgnClipItem);
	return CBCGPGridCtrl::OnFillSelItem(pDC, rectFill, pItem);
}

// Paramétrage de la grille
void CTreeGrille::InitialiserProprites()
{
	// Propriétés
	EnableColumnAutoSize(TRUE);
	EnableGroupByBox(FALSE);
	EnableHeader(FALSE, 0);
	EnableGridLines(FALSE);

	m_bWholeRowSel = TRUE;
	SetSelectionBorder(FALSE);
	SetHighlightActiveItem (TRUE);
	SetEditFirstClick (FALSE);

	// Drag and drop
 	EnableDragSelection(TRUE);
 	HideDragInsertMarker();
 	HideDragFrame();
	m_pSerializeManager->SetClipboardFormatType (CBCGPGridSerializeManager::CF_Rows);


	// Colonne par défaut
	InsertColumn(0, _T("Tree"), 100);

	// Couleur de la grille
	CBCGPGridColors theme;
	CBCGPVisualManager::GetInstance ()->OnSetGridColorTheme(this, theme);
	theme.m_clrBackground						= globalData.clrWindow;
	theme.m_clrText								= globalData.clrWindowText;
	theme.m_LeftOffsetColors.m_clrBackground	= globalData.clrWindow;
	theme.m_LeftOffsetColors.m_clrText			= globalData.clrWindowText;
 	theme.m_EvenColors.m_clrBackground			= globalData.clrWindow;
 	theme.m_EvenColors.m_clrText				= globalData.clrWindowText;
	theme.m_OddColors.m_clrBackground			= globalData.clrWindow;
	theme.m_OddColors.m_clrText					= globalData.clrWindowText;
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
}

// Initialisation de la grille
void CTreeGrille::Initialiser(GDSAPI::CProjet* pProjet)
{

}

// Manageur d'icones
CTreeIconMgr* CTreeGrille::GetTreeImageMgr() const
{
	return m_pTreeImageMgr;
}

GDSAPI::CProjet* CTreeGrille::GetPointer(CSItemProjet* pSItemProjet)
{
	return dynamic_cast<GDSAPI::CProjet*>(pSItemProjet);
}

GDSAPI::CFiltre* CTreeGrille::GetPointer(CSItemFiltre* pSItemFiltre)
{
	return dynamic_cast<GDSAPI::CFiltre*>(pSItemFiltre);
}

GDSAPI::CRessource* CTreeGrille::GetPointer(CSItemRessource* pSItemRessource)
{
	return dynamic_cast<GDSAPI::CRessource*>(pSItemRessource);
}

GDSAPI::CControle* CTreeGrille::GetPointer(CSItemControle* pSItemControle)
{
	return dynamic_cast<GDSAPI::CControle*>(pSItemControle);
}

//
CSItemStructure* CTreeGrille::GetSelectedItem()
{
	CList <CBCGPGridItem*, CBCGPGridItem*> lstSelected;
	GetSelectedItems(lstSelected);
	
	return lstSelected.GetCount() ?  (CSItemStructure*)lstSelected.GetHead()->GetParentRow()->GetData() : nullptr; 
}

CSItemStructure* CTreeGrille::GetItem(int iRow)
{
	return (CSItemStructure*)GetRow(iRow)->GetData();
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
	bool bFiltre	=	IsFiltreAllowed(pSItem);
	bool bRessource =	IsRessourceAllowed(pSItem);
	if(bFiltre)		MenuFunctions::AddMenuItem(hMenu, _T("Filtre"),		IDMS__NOUVEAU_FILTRE);
	if(bRessource)	MenuFunctions::AddMenuItem(hMenu, _T("Ressource"),	IDMS__NOUVEAU_RESSOURCE);
 	if(bFiltre || bRessource)
 		MenuFunctions::AddMenuItem(hMenu, _T("Séparateur"), 0);
	
	// -> Modifier 
	bool bModifier	=	IsModifierAllowed(pSItem);
	if(bModifier)	MenuFunctions::AddMenuItem(hMenu, _T("Modifier"),	IDMS__MODIFIER);
 	if(bModifier)
 		MenuFunctions::AddMenuItem(hMenu, _T("Séparateur"), 0);

	
	// -> Couper
	// -> Copier
	// -> Coller
	// -> Supprimer
	// -> Renommer
	bool bColler =		IsCollerAllowed(pSItem);
	MenuFunctions::AddMenuItem(hMenu, _T("Couper\tCtrl+X"),				IDMS__COUPER);
	MenuFunctions::AddMenuItem(hMenu, _T("Copier\tCtrl+C"),				IDMS__COPIER);
	if(bColler) MenuFunctions::AddMenuItem(hMenu, _T("Coller\tCtrl+V"),	IDMS__COLLER);
	MenuFunctions::AddMenuItem(hMenu, _T("Supprimer\tSuppr"),			IDMS__SUPPRIMER);
	MenuFunctions::AddMenuItem(hMenu, _T("Renommer\tF2"),				IDMS__RENOMMER);
	MenuFunctions::AddMenuItem(hMenu, _T("Séparateur"), 0);

	// -> Exclu
	bool bExclu =		IsExclureAllowed(pSItem);
	if(bExclu)		MenuFunctions::AddMenuItem(hMenu, _T("Exclure"),	IDMS__EXCLURE);
 	if(bExclu)
 		MenuFunctions::AddMenuItem(hMenu, _T("Séparateur"), 0);

	// -> Actualiser
	bool brefresh =		IsActualiserAllowed(pSItem);
	if(brefresh)	MenuFunctions::AddMenuItem(hMenu, _T("Actualier"),	IDMS__ACTUALISER);

	// Affiche le menu
	theApp.GetContextMenuManager ()->ShowPopupMenu(hMenu,point.x,point.y,this,TRUE);
}

void CTreeGrille::OnUpdateMenu(CCmdUI* pCmdUI)
{
	// Récupère le CSItemStructure sélectionné
	CSItemStructure* pSItem = GetSelectedItem();

	switch (pCmdUI->m_nID)
	{
		case IDMS__MODIFIER:	pCmdUI->Enable(pSItem ? IsModifierAllowed(pSItem)	: FALSE);	break;
		case IDMS__COUPER:		pCmdUI->Enable(pSItem ? IsCouperAllowed(pSItem)		: FALSE);	break;
		case IDMS__COPIER:		pCmdUI->Enable(pSItem ? IsCopierAllowed(pSItem)		: FALSE);	break;
		case IDMS__COLLER:		pCmdUI->Enable(pSItem ? IsCollerAllowed(pSItem)		: FALSE);	break;
		case IDMS__SUPPRIMER:	pCmdUI->Enable(pSItem ? IsSupprimerAllowed(pSItem)	: FALSE);	break;
		case IDMS__RENOMMER:	pCmdUI->Enable(pSItem ? IsRenommerAllowed(pSItem)	: FALSE);	break;
	}
}

// Début de l'édition dans la grille
void CTreeGrille::OnAfterInplaceEditCreated(CBCGPGridItem* pItem, CWnd* pInplaceEdit)
{
	CBCGPGridCtrl::OnAfterInplaceEditCreated (pItem, pInplaceEdit);

	//CEdit* pEdit = DYNAMIC_DOWNCAST(CEdit, pInplaceEdit);
	//if(pEdit != NULL)
	//{
	//}
}

// Fin de l'édition dans la grille
void CTreeGrille::OnEndInplaceEdit(CBCGPGridItem* pItem)
{
	CSItemStructure* pSItem = (CSItemStructure*)pItem->GetParentRow()->GetData();

 	switch (pSItem->GetTypeItem())
 	{
 		case SItemType::Projet :
 			OnRenommerProjet((CSItemProjet*)pSItem);
 			break;
 
 		case SItemType::Filtre :
 			OnRenommerFiltre((CSItemFiltre*)pSItem);
 			break;
 
 		default :
 			break;
 	}
}

// Filtre
bool CTreeGrille::IsFiltreAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;
	if(pSItem->GetTypeItem() == SItemType::Filtre)		return true;

	return false;
}

// Ressource
bool CTreeGrille::IsRessourceAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;

	// Les ressource ne peuvent être ajouter qu'a un filtre
	// de type ressource ou un de ses déscendant
	if(pSItem->GetTypeItem() == SItemType::Filtre)
	{
		// Filtre de type ressource
		GDSAPI::CFiltre* pFiltre = GetPointer((CSItemFiltre*)pSItem);
		if(pFiltre->GetType()==FiltreType::Ressource)	return true;

		// Parent de type ressource
		GDSAPI::CFiltre* pFiltreParent = dynamic_cast<GDSAPI::CFiltre*>(pFiltre->GetOwner());
		while(pFiltreParent)
		{
			if(pFiltreParent->GetType()==FiltreType::Ressource)	return true;
			pFiltreParent = dynamic_cast<GDSAPI::CFiltre*>(pFiltreParent->GetOwner());
		}
	}

	return false;
}


bool CTreeGrille::IsCouperAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;

	if(pSItem->GetTypeItem() == SItemType::Ressource)	return true;

	return false;
}

bool CTreeGrille::IsCopierAllowed(CSItemStructure* pSItem)
{
	return false;
}

bool CTreeGrille::IsCollerAllowed(CSItemStructure* pSItem)
{
	return false;
}

bool CTreeGrille::IsSupprimerAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;

	if(pSItem->GetTypeItem() == SItemType::Filtre 
	   && GetPointer((CSItemFiltre*)pSItem)->GetType()==FiltreType::Filtre)		return true;
	if(pSItem->GetTypeItem() == SItemType::Ressource)	return true;

	return false;
}

bool CTreeGrille::IsRenommerAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;
	if(pSItem->GetTypeItem() == SItemType::Projet)		return true;
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

bool CTreeGrille::IsExclureAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;
	if(pSItem->GetTypeItem() == SItemType::Controle)
	{
		if(GetPointer((CSItemControle*)pSItem)->GetExclu()==true)
			return false;
		return true;
	}

	return false;
}

bool CTreeGrille::IsActualiserAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;
	if(pSItem->GetTypeItem() == SItemType::Projet)		return true;
	if(pSItem->GetTypeItem() == SItemType::Ressource)	return true;

	return false;
}

void CTreeGrille::OnNouveauFiltre()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	switch (pSItem->GetTypeItem())
	{
		case SItemType::Filtre :
			OnNouveauFiltre((CSItemFiltre*)pSItem);
			break;

		default :
			break;
	}
}

bool CTreeGrille::OnNouveauFiltre(CSItemFiltre* pSItem)
{
	// Test de cohérence
	if(!IsFiltreAllowed(pSItem)) return false;

	// Filtre parent
	GDSAPI::CFiltre* pFiltreParent = GetPointer(pSItem);

	// Création du filtre
	GDSAPI::CFiltre* pFiltre = new CFiltre(DefULong,pFiltreParent);
	pFiltre->SetLibelle("Nouveau Filtre");

	// Ajout du Filtre
	CFiltreListe* pFiltreListe = pFiltreParent->GetFiltreListe(false);
	pFiltreListe->Add(pFiltre);
	if(!pFiltreParent->Sauver())
		return false;

	// Ajout du filtre dans la grille
	int iIndexListe = pFiltreListe->GetCount()-1;
	CSItemFiltre* pSItemFiltre = new CSItemFiltre(m_pStructureMgr,*pFiltre, pSItem);
	pFiltreListe->RemoveAt(iIndexListe);
	pFiltreListe->Add(pSItemFiltre);

	//
	pSItem->Expand(TRUE);

	return true;
}

void CTreeGrille::OnNouveauRessource()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	switch (pSItem->GetTypeItem())
	{
		case SItemType::Filtre :
			OnNouveauRessource((CSItemFiltre*)pSItem);
			break;

		default :
			break;
	}
}

bool CTreeGrille::OnNouveauRessource(CSItemFiltre* pSItemFiltre)
{
	// Test de cohérence
	if(!IsRessourceAllowed(pSItemFiltre)) return false;

	// Filtre
	GDSAPI::CFiltre* pFiltreParent = GetPointer(pSItemFiltre);

	// Ressource
	GDSAPI::CRessource ressource(DefULong,pFiltreParent);
	ressource.SetFtrIdent(pFiltreParent->GetId());

	//
	CRessourceDlg dlg(&ressource,this);
	BOOL bRet = (dlg.DoModal()==IDOK)?TRUE:FALSE;;

	// Ajout du filtre dans la grille
	if(bRet)
	{
		CSItemRessource* pSItemRessource = new CSItemRessource(m_pStructureMgr, ressource, pSItemFiltre);
		pFiltreParent->GetRessourceListe()->Add(pSItemRessource);

		//
		pSItemFiltre->Expand(TRUE);

		// Ajout du générateur de ressource par défaut
		CProjet* pProjet = pSItemRessource->GetProjet();
		if(pProjet && !pProjet->GetUuidResGen().isNull())
		{
			//PluginDetails plugin = theApp.GetPluginDetails(pProjet->GetUuidResGen());
			//IPluginRessourceGenerateur& pPlugin = (IPluginRessourceGenerateur&)theApp.GetPlugin(pProjet->GetUuidResGen());
 		//	pSItemRessource->SetUuidDocument(pPlugin.GetDocuments()[0]->uuid());
 		//	pSItemRessource->Sauver();
		}
	}

	return bRet ? true : false;
}

void CTreeGrille::OnCouper()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	OnCouper(pSItem);
}

void CTreeGrille::OnCouper(CSItemStructure* pSItem)
{

}

void CTreeGrille::OnCopier()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	OnCopier(pSItem);
}

void CTreeGrille::OnCopier(CSItemStructure* pSItem)
{

}

void CTreeGrille::OnColler()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	OnColler(pSItem);
}

void CTreeGrille::OnColler(CSItemStructure* pSItem)
{

}

void CTreeGrille::OnSupprimer()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if(pSItem == nullptr) return;

	switch (pSItem->GetTypeItem())
	{
		case SItemType::Filtre :
			OnSupprimerFilte((CSItemFiltre*)pSItem);
			break;

		case SItemType::Ressource :
			OnSupprimerRessource((CSItemRessource*)pSItem);
			break;

		default :
			break;
	}
}

bool CTreeGrille::OnSupprimerFilte(CSItemFiltre* pSItem)
{
	// Test de cohérence
	if(!IsSupprimerAllowed(pSItem)) return false;

	//
	GDSAPI::CFiltre* pFiltre = GetPointer(pSItem);

	// Ligne de la grille
	CBCGPGridRow* pRow = pSItem->GetGridRow();

	// Suppression
	pFiltre->SetPourSupprimer(true);
	if(!pFiltre->Supprimer())
		return false;

	// Supression dans la grille
	m_pStructureMgr->RemoveTreeRow(pRow);

	return true;
}

bool CTreeGrille::OnSupprimerRessource(CSItemRessource* pSItem)
{
	// Test de cohérence
	if(!IsSupprimerAllowed(pSItem)) return false;

	//
	GDSAPI::CRessource* pRessource = GetPointer(pSItem);

	// Ligne de la grille
	CBCGPGridRow* pRow = pSItem->GetGridRow();

	// Suppression
	pRessource->SetPourSupprimer(true);
	if(!pRessource->Supprimer())
		return false;

	// Supression dans la grille
	m_pStructureMgr->RemoveTreeRow(pRow);

	return true;
}

void CTreeGrille::OnRenommer()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if(pSItem == nullptr) return;

	// Test de cohérence
	if(!IsRenommerAllowed(pSItem)) return;

	// La grille ne doit plus être en Readonly
	// pour accepter la saisie dans la grille
	SetReadOnly(FALSE);

	// Edition
	CBCGPGridRow* pSel = pSItem->GetGridRow();
	EnsureVisible(pSel);
	SetBeginEditReason(BeginEdit_F2);
	if(EditItem(pSel))
		DoInplaceEditSetSel(OnInplaceEditSetSel(GetCurSelItem(pSel), BeginEdit_Return));

	// Après avoir renommé la grille redevient Readonly
	// pour refuser la saisie dans la grille
	SetReadOnly(TRUE);
	SetWholeRowSel(TRUE);
}

bool CTreeGrille::OnRenommerProjet(CSItemProjet* pSItem)
{
	// Récupère le texte de la grille
	CString sLibelle = pSItem->GetGridRow()->GetItem(0)->GetLabel();

	//
	GDSAPI::CProjet projet(pSItem->GetId());
	projet.SetLibelle(ToStdString(sLibelle));
	bool bRet = projet.Sauver();

	// Mise à jour
	m_pStructureMgr->UpdateTitle(sLibelle);
	m_pStructureMgr->UpdateTreeItem(pSItem);
	m_pStructureMgr->UpdatePropertyGrid(pSItem);

	return bRet;
}

bool CTreeGrille::OnRenommerFiltre(CSItemFiltre* pSItem)
{
	// Récupère le texte de la grille
	CString sLibelle = pSItem->GetGridRow()->GetItem(0)->GetLabel();

	//
	GDSAPI::CFiltre filtre(pSItem->GetId());
	filtre.SetLibelle(ToStdString(sLibelle));
	bool bRet = filtre.Sauver();

	// Mise à jour
	m_pStructureMgr->UpdateTreeItem(pSItem);
	m_pStructureMgr->UpdatePropertyGrid(pSItem);

	return bRet;
}

void CTreeGrille::OnModifier()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	switch (pSItem->GetTypeItem())
	{
		case SItemType::Projet :
			OnModifierProjet((CSItemProjet*)pSItem);
			break;

		case SItemType::Filtre :
			OnModifierFilte((CSItemFiltre*)pSItem);
			break;

		default :
			break;
	}
}

bool CTreeGrille::OnModifierProjet(CSItemProjet* pSItem)
{
	// Test de cohérence
	if(!IsModifierAllowed(pSItem)) return false;

	//
	GDSAPI::CProjet projet(pSItem->GetId());

	//
	CProjetDlg dlg(&projet,this);
	BOOL bRet = (dlg.DoModal()==IDOK)?TRUE:FALSE;;

 	// Mise à jour de l'item
 	if(bRet==TRUE)
  		m_pStructureMgr->UpdateTreeItem(pSItem);

	return bRet ? true : false;
}

bool CTreeGrille::OnModifierFilte(CSItemFiltre* pSItem)
{
	// Test de cohérence
	if(!IsModifierAllowed(pSItem)) false;

	//
	BCGP_MSGBOXPARAMS params;
	params.lpszCaption = _T("Bientôt");
	params.lpszText = _T("A faire !!!");
	params.dwStyle = MB_ICONASTERISK | MB_OK;
	BCGPMessageBoxIndirect(&params);

	return false;
}

void CTreeGrille::OnExclure()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	switch (pSItem->GetTypeItem())
	{
		case SItemType::Controle :
			OnExclureControle((CSItemControle*)pSItem);
			break;

		default :
			break;
	}
}

bool CTreeGrille::OnExclureControle(CSItemControle* pSItem)
{
	// Test de cohérence
	if(!IsExclureAllowed(pSItem)) return false;

	//
	GDSAPI::CControle* pControle = GetPointer(pSItem);
	pControle->SetExclu(true);
	pControle->Sauver();

 	// Mise à jour de l'item
	m_pStructureMgr->UpdateTreeItem(pSItem);
	m_pStructureMgr->UpdatePropertyGrid(pSItem);

	return true;
}

void CTreeGrille::OnActualiser()
{
	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	switch (pSItem->GetTypeItem())
	{
		case SItemType::Projet :
			OnActualiserProjet((CSItemProjet*)pSItem);
			break;

		case SItemType::Ressource :
			OnActualiserRessource((CSItemRessource*)pSItem);
			break;

		default :
			break;
	}
}

bool CTreeGrille::OnActualiserProjet(CSItemProjet* pSItem)
{
	// Test de cohérence
	if(!IsActualiserAllowed(pSItem)) return false;

	//
	m_pStructureMgr->Initialiser(pSItem->GetId());

	return true;
}
bool CTreeGrille::OnActualiserRessource(CSItemRessource* pSItem)
{
	// Test de cohérence
	if(!IsActualiserAllowed(pSItem)) return false;

	//
	BCGP_MSGBOXPARAMS params;
	params.lpszCaption = _T("Bientôt");
	params.lpszText = _T("A faire !!!");
	params.dwStyle = MB_ICONASTERISK | MB_OK;
	BCGPMessageBoxIndirect(&params);

	return true;
}

void CTreeGrille::OnSelChanged(const CBCGPGridRange &range, BOOL bSelect)
{
	CBCGPGridCtrl::OnSelChanged(range,bSelect);

	// Récupère l'item sélectionné
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	// Mise à jour du propertygrid
	m_pStructureMgr->UpdatePropertyGrid(pSItem);
}

BOOL CTreeGrille::StartDragItems(CPoint point)
{
	m_pSItemDrag = nullptr;
	m_pSItemDrop = nullptr;

	return CBCGPGridCtrl::StartDragItems(point);
}

void CTreeGrille::StopDragItems()
{
	m_pSItemDrag = nullptr;
	m_pSItemDrop = nullptr;

	return CBCGPGridCtrl::StopDragItems();
}

BOOL CTreeGrille::DoDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point)
{
	// Récupère le CSItemStructure sélectionné
	if(m_pSItemDrag == nullptr)
	{
		CSItemStructure* pSItemDrag = GetItem(m_idDragFrom.m_nRow);
		if(!pSItemDrag->CanDrag()) return FALSE;
		m_pSItemDrag = pSItemDrag;
	}
	else
	{
		CSItemStructure* pSItemDrop = GetItem(m_idDropTo.m_nRow);
		if(!pSItemDrop->CanDrop(m_pSItemDrag)) return FALSE;
		m_pSItemDrop = pSItemDrop;
	}

	//		
	return CBCGPGridCtrl::DoDragOver(pDataObject, dwKeyState, point);
}

BOOL CTreeGrille::DoDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point)
{
	if(m_pSItemDrag && m_pSItemDrop && m_pSItemDrop->CanDrop(m_pSItemDrag))
		return CBCGPGridCtrl::DoDrop(pDataObject, dropEffect, point);
	return FALSE;
}




