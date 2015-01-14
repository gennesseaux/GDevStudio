
#pragma once


// Inculsions
#include "SItemDef.h"

// Inculsions
class CGDevStudioDoc;
class CTreeGrille;
class CSItemStructure;
class CSItemProjet;
class CSItemFiltre;

// Macro


//
class CStructureMgr
{
	friend class CSItemStructure;
	friend class CSItemProjet;
	friend class CSItemFiltre;

public:
	// Constructeur
	CStructureMgr(CGDevStudioDoc* pDoc, CTreeGrille* pTreeGrille);
	// Destructeurs
	virtual ~CStructureMgr();

public:
	// Initialisation de la structure
	void Initialiser(unsigned long ulIdProjet);


public:
	// Pointeur sur la grille utilisé comme Tree
	CTreeGrille* GetTreeGrille() const;
	// Modifie le titre du document
	void UpdateTitle();
	void UpdateTitle(CString sTitle);

	// Mise à jour d'un item dans la grille
	void UpdateTreeItem(CSItemStructure* pSItem);
	// Suppression d'ue ligne dans la grille
	void RemoveTreeRow(CBCGPGridRow* pRow);

protected:
	//void AddToMap(SItemType sitemType, CSItemStructure* pSItemStructure);

private:
	CGDevStudioDoc* m_pDoc = nullptr;
	CTreeGrille*	m_pTreeGrille = nullptr;
	CSItemProjet*	m_pSItemProjet = nullptr;

	//CMap<SItemType, SItemType, CSItemStructure*, CSItemStructure*> m_mapSItemStructure;
};

