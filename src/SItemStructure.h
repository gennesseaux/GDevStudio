
#pragma once


// Inculsions
#include <BCGPGridCtrl.h>
#include "TreeGrille.h"
#include "TreeIconMgr.h"
#include "SItemDef.h"



// Inclusions
class CStructureMgr;

class CSItemStructure
{
public:
	// Constructeur
	CSItemStructure(SItemType sitemType, CStructureMgr* pStructureMgr);
	// Destructeur
	virtual ~CSItemStructure();


protected:
	//! Constructeur par copie
	CSItemStructure(const CSItemStructure &source) = delete;
	//! Opérateur =
	CSItemStructure &operator=(const CSItemStructure &source) = delete;


public:
	// Libellé
	void SetLibelle(const char* sLibelle);
	// Image 
	void SetImage(TreeImage image);
	// Ajout de la ligne à la grille
	void AjouterLigneGrille();
	// Ajout de la ligne à la grille
	void AjouterLigneGrille(CSItemStructure* pParent);
	//
	CBCGPGridRow* GetLigne();
	//
	SItemType GetTypeItem() const { return m_SItemType; }

public:
	virtual void UpdateTreeItem() = 0;

protected:
	CStructureMgr*	m_pStructureMgr = nullptr;
	CTreeGrille*	m_pTreeGrille = nullptr;
	CBCGPGridRow*	m_pRow = nullptr;
	SItemType		m_SItemType;
};
