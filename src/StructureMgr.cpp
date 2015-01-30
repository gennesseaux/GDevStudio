

// Inclusions
#include "Stdafx.h"
#include "StructureMgr.h"
#include "MainFrm.h"

// Inclusions
#include "GDevStudioDoc.h"
#include "TreeGrille.h"
#include "SItemProjet.h"


// Constructeur
CStructureMgr::CStructureMgr(CGDevStudioDoc* pDoc, CTreeGrille* pTreeGrille)
{
	m_pDoc = pDoc;
 	m_pTreeGrille = pTreeGrille;
 	m_pTreeGrille->SetStructureMgr(this);
}

// Destructeur
CStructureMgr::~CStructureMgr()
{
	m_pTreeGrille = nullptr;

	delete m_pSItemProjet; m_pSItemProjet = nullptr;
}

// Initialisation de la structure
void CStructureMgr::Initialiser(unsigned long ulIdProjet)
{
	// Vide le tree grille
	GetTreeGrille()->RemoveAll();

	// Projet
	delete m_pSItemProjet;
	m_pSItemProjet = new CSItemProjet(this,ulIdProjet);
}

// Pointeur sur la grille utilisé comme Tree
CTreeGrille* CStructureMgr::GetTreeGrille() const
{
	return m_pTreeGrille;
}

// Modifie le titre du document
void CStructureMgr::UpdateTitle()
{
	UpdateTitle(ToString(m_pSItemProjet->GetLibelle()));
}
void CStructureMgr::UpdateTitle(CString sTitle)
{
	m_pDoc->SetTitle(sTitle);
}

// Mise à jour d'un item dans la grille
void CStructureMgr::UpdateTreeItem(CSItemStructure* pSItem)
{
	pSItem->UpdateTreeItem();
}

// Suppression d'ue ligne dans la grille
void CStructureMgr::RemoveTreeRow(CBCGPGridRow* pRow)
{
	int nPos = pRow->GetRowId();
	m_pTreeGrille->RemoveRow(nPos,TRUE);
}

// Mise à jour du propertygrid
void CStructureMgr::UpdatePropertyGrid(CSItemStructure* pSItem)
{
	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pMainFrame);
	pSItem->UpdatePropertyGrid(pMainFrame->GetPropertyGridCtrl());
}
