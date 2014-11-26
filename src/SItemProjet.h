
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "DObject/Projet.h"

//
using GDSObject::CProjet;


class CSItemProjet : public CSItemStructure, public CProjet
{
public:
	// Constructeur
	CSItemProjet(CStructureMgr* pStructureMgr, unsigned long ulIdProjet);
	// Destructeur
	virtual ~CSItemProjet();

protected:
	CProjet*	m_pProjet = nullptr;
};
