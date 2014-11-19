
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "DObject/Projet.h"


class CSItemProjet : public CSItemStructure, GDSObject::CProjet
{
public:
	// Constructeur
	CSItemProjet(CStructureMgr* pStructureMgr, unsigned long ulIdProjet);
	// Destructeur
	virtual ~CSItemProjet();

protected:
	GDSObject::CProjet*	m_pProjet = nullptr;
};
