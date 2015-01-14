
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "DObject/Ressource.h"

//
using GDSObject::CRessource;
using GDSObject::CRessourceListe;

//
class CSItemFiltre;

class CSItemRessource : public CSItemStructure, public CRessource
{
public:
	//! Constructeur.
	CSItemRessource(CStructureMgr* pStructureMgr, const CRessource &source, CSItemFiltre* pSItemFiltre);
	// Destructeur
	virtual ~CSItemRessource();

public:
	void UpdateTreeItem();
};
