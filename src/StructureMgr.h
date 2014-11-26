
#pragma once


// Inculsions
#include "SItemDef.h"

// Inculsions
class CTreeGrille;
class CSItemStructure;
class CSItemProjet;
class CSItemFiltre;


//
class CStructureMgr
{
	friend class CSItemStructure;
	friend class CSItemProjet;
	friend class CSItemFiltre;

public:
	// Constructeur
	CStructureMgr(CTreeGrille* pTreeGrille);
	// Destructeurs
	virtual ~CStructureMgr();

public:
	// Initialisation de la structure
	void Initialiser(unsigned long ulIdProjet);


public:
	CTreeGrille* GetTreeGrille() const;

protected:
	void AddToMap(SItemType sitemType, CSItemStructure* pSItemStructure);

private:
	CTreeGrille*	m_pTreeGrille = nullptr;
	CSItemProjet*	m_pSItemProjet = nullptr;

	CMap<SItemType, SItemType, CSItemStructure*, CSItemStructure*> m_mapSItemStructure;
};

