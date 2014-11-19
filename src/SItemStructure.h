
#pragma once


// Inculsions
#include <BCGPGridCtrl.h>
#include "TreeGrille.h"
#include "TreeIconMgr.h"

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
	//! Op�rateur =
	CSItemStructure &operator=(const CSItemStructure &source) = delete;


public:
	CStructureMgr* GetStructureMgr() const { return m_pStructureMgr; }


public:
	// Libell�
	void SetLibelle(const char* sLibelle);
	// Image 
	void SetImage(TreeImage image);
	// Ajout de la ligne � la grille
	void AjouterLigneGrille();


protected:
	CStructureMgr*	m_pStructureMgr = nullptr;
	CTreeGrille*	m_pTreeGrille = nullptr;
	CBCGPGridRow*	m_pRow = nullptr;
};