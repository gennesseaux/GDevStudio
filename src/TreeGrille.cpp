
// Inclusions
#include "stdafx.h"
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

// Inclusions
#include "ProjetDlg.h"

// Macros
#define NbColumns 1


IMPLEMENT_DYNAMIC(CTreeGrille, CBCGPGridCtrl)

BEGIN_MESSAGE_MAP(CTreeGrille, CBCGPGridCtrl)
	ON_WM_CONTEXTMENU()

	// --------------------------------------------------
	//			-~  COMMANDES LIEES AU MENU ~-
	// --------------------------------------------------
	ON_COMMAND(IDMS__NOUVEAU_FILTRE,		&CTreeGrille::OnNouveauFilte)
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
	// Param�trage de la grille
	InitialiserProprites();
	// Images dans la grille
	InitialiserImages();
}

// Destructeur
CTreeGrille::~CTreeGrille()
{
	delete m_pTreeImageMgr; m_pTreeImageMgr = nullptr;
}

// Cr�ation de la grille
BOOL CTreeGrille::Create(CView* pView)
{
	ASSERT_VALID(pView);

	// La grille sera contenue dans toute la vue parent
	CRect rectClient;
	pView->GetClientRect(rectClient);

	// Cr�ation de la grillle
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

// Param�trage de la grille
void CTreeGrille::InitialiserProprites()
{
	// Propri�t�s
	EnableColumnAutoSize(TRUE);
	SetSingleSel(FALSE);
	SetReadOnly(TRUE);
	SetWholeRowSel(TRUE);
	EnableGroupByBox(FALSE);
	EnableHeader(FALSE, 0);
	EnableGridLines(FALSE);
	SetSelectionBorder(FALSE);
	//SetRowMarker(TRUE);

	// Colonne par d�faut
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

	// Cr�ation du nouveau menu 
	HMENU hMenu = ::CreatePopupMenu();
	CMenu* pMenu = CMenu::FromHandle(hMenu);

	// R�cup�re le CSItemStructure
	CSItemStructure* pSItem = pHitRow ? (CSItemStructure*)pHitRow->GetData() : nullptr;
	

	// Ajout des lignes du menu
	// ------------------------
	
	// -> Nouveau 
	bool bFiltre =	IsFiltreAllowed(pSItem);
	if(bFiltre)		MenuFunctions::AddMenuItem(hMenu, _T("Filtre"),		IDMS__NOUVEAU_FILTRE);
 	if(bFiltre)
 		MenuFunctions::AddMenuItem(hMenu, _T("S�parateur"), 0);

	
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
		MenuFunctions::AddMenuItem(hMenu, _T("S�parateur"), 0);


	// Affiche le menu
	theApp.GetContextMenuManager ()->ShowPopupMenu(hMenu,point.x,point.y,this,TRUE);
}

void CTreeGrille::OnUpdateMenu(CCmdUI* pCmdUI)
{
	// R�cup�re le CSItemStructure s�lectionn�
	CSItemStructure* pSItem = GetSelectedItem();

	switch (pCmdUI->m_nID)
	{
		case IDMS__MODIFIER:	pCmdUI->Enable(pSItem ? IsModifierAllowed(pSItem) : FALSE);		break;
		case IDMS__SUPPRIMER:	pCmdUI->Enable(pSItem ? IsSupprimerAllowed(pSItem) : FALSE);	break;
	}
}

// D�but de l'�dition dans la grille
void CTreeGrille::OnAfterInplaceEditCreated(CBCGPGridItem* pItem, CWnd* pInplaceEdit)
{
	CBCGPGridCtrl::OnAfterInplaceEditCreated (pItem, pInplaceEdit);

	//CEdit* pEdit = DYNAMIC_DOWNCAST(CEdit, pInplaceEdit);
	//if(pEdit != NULL)
	//{
	//}
}

// Fin de l'�dition dans la grille
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
	if(pSItem->GetTypeItem() == SItemType::Filtre)		return true;

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

void CTreeGrille::OnNouveauFilte()
{

}

void CTreeGrille::OnCouper()
{
	// R�cup�re l'item s�lectionn�
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	OnCouper(pSItem);
}

void CTreeGrille::OnCouper(CSItemStructure* pSItem)
{

}

void CTreeGrille::OnCopier()
{
	// R�cup�re l'item s�lectionn�
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	OnCopier(pSItem);
}

void CTreeGrille::OnCopier(CSItemStructure* pSItem)
{

}

void CTreeGrille::OnColler()
{
	// R�cup�re l'item s�lectionn�
	CSItemStructure* pSItem = GetSelectedItem();
	if (pSItem == nullptr) return;

	OnColler(pSItem);
}

void CTreeGrille::OnColler(CSItemStructure* pSItem)
{

}

void CTreeGrille::OnSupprimer()
{
	// R�cup�re l'item s�lectionn�
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
	// Test de coh�rence
	if(!IsSupprimerAllowed(pSItem)) return false;

	//
	CSItemFiltre* pSFiltre = (CSItemFiltre*)pSItem;
	GDSObject::CFiltre* pFiltre = (GDSObject::CFiltre*)pSFiltre;

	// Ligne de la grille
	CBCGPGridRow* pRow = pSItem->GetLigne();

	// Suppression
	pFiltre->SetPourSupprimer(true);
	if(!pFiltre->Supprimer())
		return false;

	// Supression dans la grille
	m_pStructureMgr->RemoveTreeRow(pRow);

	return true;
}

void CTreeGrille::OnRenommer()
{
	// R�cup�re l'item s�lectionn�
	CSItemStructure* pSItem = GetSelectedItem();
	if(pSItem == nullptr) return;

	// Test de coh�rence
	if(!IsRenommerAllowed(pSItem)) return;

	// La grille ne doit plus �tre en Readonly
	// pour accepter la saisie dans la grille
	SetReadOnly(FALSE);

	// Edition
	CBCGPGridRow* pSel = pSItem->GetLigne();
	EnsureVisible(pSel);
	SetBeginEditReason(BeginEdit_F2);
	if(EditItem(pSel))
		DoInplaceEditSetSel(OnInplaceEditSetSel(GetCurSelItem(pSel), BeginEdit_Return));

	// Apr�s avoir renomm� la grille redevient Readonly
	// pour refuser la saisie dans la grille
	SetReadOnly(TRUE);
	SetWholeRowSel(TRUE);
}

bool CTreeGrille::OnRenommerProjet(CSItemStructure* pSItem)
{
	// R�cup�re le texte de la grille
	CString sVal = pSItem->GetLigne()->GetItem(0)->GetLabel();

	//
	GDSObject::CProjet projet(((CSItemProjet*)pSItem)->GetId());
	projet.SetLibelle(ToStdString(sVal));
	if(!projet.Sauver())
	{
		m_pStructureMgr->UpdateTreeItem(pSItem);
		return false;
	}

	// Le document porte le m�me nom que le projet
	m_pStructureMgr->UpdateTitle(sVal);

	return true;
}

bool CTreeGrille::OnRenommerFiltre(CSItemStructure* pSItem)
{
	// R�cup�re le texte de la grille
	CString sVal = pSItem->GetLigne()->GetItem(0)->GetLabel();

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
	// R�cup�re l'item s�lectionn�
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
	// Test de coh�rence
	if(!IsModifierAllowed(pSItem)) return false;

	//
	GDSObject::CProjet projet(((CSItemProjet*)pSItem)->GetId());

	//
	CProjetDlg dlg(&projet,this);
	BOOL bRet = (dlg.DoModal()==IDOK)?TRUE:FALSE;;

 	// Mise � jour de l'item
 	if(bRet==TRUE)
  		m_pStructureMgr->UpdateTreeItem(pSItem);

	return bRet ? true : false;
}

bool CTreeGrille::OnModifierFilte(CSItemStructure* pSItem)
{
	// Test de coh�rence
	if(!IsModifierAllowed(pSItem)) false;

	return false;
}




