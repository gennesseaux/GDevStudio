
// Inclusions
#include "Stdafx.h"
#include "GDevStudio.h"
#include "TreeGrille.h"

// Inclusions
#include "Outils\MenuFunctions\MenuFunctions.h"

// Inclusions
#include "TreeIconMgr.h"
#include "StructureMgr.h"
#include "SItemStructure.h"
#include "SItemProjet.h"
#include "SItemFiltre.h"
#include "SItemRessource.h"
#include "SItemControle.h"

// Inclusions
#include "ProjetDlg.h"
#include "RessourceDlg.h"

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
	ON_COMMAND(IDMS__COUPER,				&CTreeGrille::OnCouper)
	ON_COMMAND(IDMS__COPIER,				&CTreeGrille::OnCopier)
	ON_COMMAND(IDMS__COLLER,				&CTreeGrille::OnColler)
	ON_COMMAND(IDMS__SUPPRIMER,				&CTreeGrille::OnSupprimer)
	ON_COMMAND(IDMS__RENOMMER,				&CTreeGrille::OnRenommer)
	ON_COMMAND(IDMS__MODIFIER,				&CTreeGrille::OnModifier)
	
	ON_UPDATE_COMMAND_UI(IDMS__MODIFIER,	&CTreeGrille::OnUpdateMenu)
	ON_UPDATE_COMMAND_UI(IDMS__SUPPRIMER,	&CTreeGrille::OnUpdateMenu)

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

void CTreeGrille::OnFillLeftOffset(CDC* pDC, CRect rectFill, CBCGPGridRow* pRow, BOOL bDrawRightBorder /*= TRUE*/)
{
	CBCGPGridCtrl::OnFillLeftOffset(pDC, rectFill, pRow, bDrawRightBorder);
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
void CTreeGrille::Initialiser(GDSObject::CProjet* pProjet)
{

}

// Manageur d'icones
CTreeIconMgr* CTreeGrille::GetTreeImageMgr() const
{
	return m_pTreeImageMgr;
}

GDSObject::CProjet* CTreeGrille::GetPointer(CSItemProjet* pSItemProjet)
{
	return (GDSObject::CProjet*)pSItemProjet;
}

GDSObject::CFiltre* CTreeGrille::GetPointer(CSItemFiltre* pSItemFiltre)
{
	return (GDSObject::CFiltre*)pSItemFiltre;
}

GDSObject::CRessource* CTreeGrille::GetPointer(CSItemRessource* pSItemRessource)
{
	return (GDSObject::CRessource*)pSItemRessource;
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

	
	// -> Couper
	// -> Copier
	// -> Coller
	// -> Supprimer
	// -> Renommer
	bool bCouper =		IsCouperAllowed(pSItem);
	bool bCopier =		IsCopierAllowed(pSItem);
	bool bColler =		IsCollerAllowed(pSItem);
	bool bSuprimer =	IsSupprimerAllowed(pSItem);
	bool bRenommer =	IsRenommerAllowed(pSItem);
	if(bCouper)			MenuFunctions::AddMenuItem(hMenu, _T("Couper\tCtrl+X"),			IDMS__COUPER);
	if(bCopier)			MenuFunctions::AddMenuItem(hMenu, _T("Copier\tCtrl+C"),			IDMS__COPIER);
	if(bColler)			MenuFunctions::AddMenuItem(hMenu, _T("Coller\tCtrl+V"),			IDMS__COLLER);
	if(bSuprimer)		MenuFunctions::AddMenuItem(hMenu, _T("Supprimer\tSuppr"),		IDMS__SUPPRIMER);
	if(bRenommer)		MenuFunctions::AddMenuItem(hMenu, _T("Renommer\tF2"),			IDMS__RENOMMER);
	if(bCouper | bCopier | bColler | bSuprimer | bRenommer)
		MenuFunctions::AddMenuItem(hMenu, _T("Séparateur"), 0);


	// Affiche le menu
	theApp.GetContextMenuManager ()->ShowPopupMenu(hMenu,point.x,point.y,this,TRUE);
}

void CTreeGrille::OnUpdateMenu(CCmdUI* pCmdUI)
{
	// Récupère le CSItemStructure sélectionné
	CSItemStructure* pSItem = GetSelectedItem();

	switch (pCmdUI->m_nID)
	{
		case IDMS__MODIFIER:	pCmdUI->Enable(pSItem ? IsModifierAllowed(pSItem) : FALSE);		break;
		case IDMS__SUPPRIMER:	pCmdUI->Enable(pSItem ? IsSupprimerAllowed(pSItem) : FALSE);	break;
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
 			OnRenommerProjet(pSItem);
 			break;
 
 		case SItemType::Filtre :
 			OnRenommerFiltre(pSItem);
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
		GDSObject::CFiltre* pFiltre = GetPointer((CSItemFiltre*)pSItem);
		if(pFiltre->GetType()==FiltreType::Ressource)	return true;

		// Parent de type ressource
		GDSObject::CFiltre* pFiltreParent = pFiltre->GetParent<GDSObject::CFiltre*>();
		while(pFiltreParent)
		{
			if(pFiltreParent->GetType()==FiltreType::Ressource)	return true;
			pFiltreParent = pFiltreParent->GetParent<GDSObject::CFiltre*>();
		}
	}

	return false;
}


bool CTreeGrille::IsCouperAllowed(CSItemStructure* pSItem)
{
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
	if(pSItem->GetTypeItem() == SItemType::Projet)		return false;
	if(pSItem->GetTypeItem() == SItemType::Filtre)		return true;
	if(pSItem->GetTypeItem() == SItemType::Ressource)	return true;
	if(pSItem->GetTypeItem() == SItemType::Controle)	return false;

	return false;
}

bool CTreeGrille::IsRenommerAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;
	if(pSItem->GetTypeItem() == SItemType::Projet)		return true;
	if(pSItem->GetTypeItem() == SItemType::Filtre)		return true;
	if(pSItem->GetTypeItem() == SItemType::Ressource)	return false;
	if(pSItem->GetTypeItem() == SItemType::Controle)	return false;

	return false;
}

bool CTreeGrille::IsModifierAllowed(CSItemStructure* pSItem)
{
	if(pSItem == nullptr)								return false;
	if(pSItem->GetTypeItem() == SItemType::Projet)		return true;
	if(pSItem->GetTypeItem() == SItemType::Filtre)		return true;

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

	// Filtre
	GDSObject::CFiltre* pFiltreParent = GetPointer(pSItem);

	// Ajout du Filtre
	GDSObject::CFiltre* pFiltre = new CFiltre();
	pFiltre->SetLibelle("Nouveau Filtre");
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
	GDSObject::CFiltre* pFiltreParent = GetPointer(pSItemFiltre);

	// Ressource
	GDSObject::CRessource ressource;
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
			OnSupprimerFilte(pSItem);
			break;

		case SItemType::Ressource :
			OnSupprimerRessource(pSItem);
			break;

		default :
			break;
	}
}

bool CTreeGrille::OnSupprimerFilte(CSItemStructure* pSItem)
{
	// Test de cohérence
	if(!IsSupprimerAllowed(pSItem)) return false;

	//
	GDSObject::CFiltre* pFiltre = GetPointer((CSItemFiltre*)pSItem);

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

bool CTreeGrille::OnSupprimerRessource(CSItemStructure* pSItem)
{
	// Test de cohérence
	if(!IsSupprimerAllowed(pSItem)) return false;

	//
	GDSObject::CRessource* pRessource = GetPointer((CSItemRessource*)pSItem);

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

bool CTreeGrille::OnRenommerProjet(CSItemStructure* pSItem)
{
	// Récupère le texte de la grille
	CString sVal = pSItem->GetGridRow()->GetItem(0)->GetLabel();

	//
	GDSObject::CProjet projet(((CSItemProjet*)pSItem)->GetId());
	projet.SetLibelle(ToStdString(sVal));
	if(!projet.Sauver())
	{
		m_pStructureMgr->UpdateTreeItem(pSItem);
		return false;
	}

	// Le document porte le même nom que le projet
	m_pStructureMgr->UpdateTitle(sVal);

	return true;
}

bool CTreeGrille::OnRenommerFiltre(CSItemStructure* pSItem)
{
	// Récupère le texte de la grille
	CString sVal = pSItem->GetGridRow()->GetItem(0)->GetLabel();

	//
	GDSObject::CFiltre filtre(((CSItemFiltre*)pSItem)->GetId());
	filtre.SetLibelle(ToStdString(sVal));
	if(!filtre.Sauver())
	{
		m_pStructureMgr->UpdateTreeItem(pSItem);
		return false;
	}
	return true;
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

bool CTreeGrille::OnModifierProjet(CSItemStructure* pSItem)
{
	// Test de cohérence
	if(!IsModifierAllowed(pSItem)) return false;

	//
	GDSObject::CProjet projet(((CSItemProjet*)pSItem)->GetId());

	//
	CProjetDlg dlg(&projet,this);
	BOOL bRet = (dlg.DoModal()==IDOK)?TRUE:FALSE;;

 	// Mise à jour de l'item
 	if(bRet==TRUE)
  		m_pStructureMgr->UpdateTreeItem(pSItem);

	return bRet ? true : false;
}

bool CTreeGrille::OnModifierFilte(CSItemStructure* pSItem)
{
	// Test de cohérence
	if(!IsModifierAllowed(pSItem)) false;

	return false;
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




