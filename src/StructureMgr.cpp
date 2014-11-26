

// Inclusions
#include "Stdafx.h"
#include "StructureMgr.h"

// Inclusions
#include "TreeGrille.h"
#include "SItemProjet.h"


// Constructeur
CStructureMgr::CStructureMgr(CTreeGrille* pTreeGrille)
{
	m_pTreeGrille = pTreeGrille;
}

// Destructeur
CStructureMgr::~CStructureMgr()
{
	m_pTreeGrille = nullptr;

	delete m_pSItemProjet;
}

// Initialisation de la structure
void CStructureMgr::Initialiser(unsigned long ulIdProjet)
{
	// Vide le tree grille
	GetTreeGrille()->RemoveAll();

	// Projet
	m_pSItemProjet = new CSItemProjet(this,ulIdProjet);
}

//
CTreeGrille* CStructureMgr::GetTreeGrille() const
{
	return m_pTreeGrille;
}

void CStructureMgr::AddToMap(SItemType sitemType, CSItemStructure* pSItemStructure)
{
//	m_mapSItemStructure[m_mapSItemStructure];
}
