
#pragma once


// Inculsions
#include <BCGPGridCtrl.h>
#include "TreeGrille.h"
#include "TreeRow.h"
#include "TreeIconMgr.h"
#include "SItemDef.h"



// Inclusions
class CStructureMgr;

class CSItemStructure
{
	friend class CStructureMgr;

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
	CTreeRow* GetGridRow();
	//
	CBCGPGridItem* GetGridItem();
	//
	CBCGPGridItemID GetGridItemID();
	//
	SItemType GetTypeItem() const { return m_SItemType; }

	//
	void Expand(BOOL bExpand = TRUE);
	// Appelé avant que l'expand soit fait
	virtual void OnExpand(BOOL bExpand) {};


protected:
	virtual void UpdateTreeItem() = 0;

	// Property grid
	virtual void UpdatePropertyGrid(CBCGPPropList* pPropList);
	static LRESULT CALLBACK OnPropertyChangedCallback(CBCGPProp* pProp);
	virtual LRESULT OnPropertyChanged(CBCGPProp* pProp) = 0;


public:
	// Drag & Drop
 	virtual bool CanDrag() = 0;
 	virtual bool CanDrop(CSItemStructure* pSItemDrag) = 0;


protected:
	CStructureMgr*	m_pStructureMgr = nullptr;
	CTreeGrille*	m_pTreeGrille = nullptr;
	CTreeRow*		m_pRow = nullptr;
	SItemType		m_SItemType;
};
