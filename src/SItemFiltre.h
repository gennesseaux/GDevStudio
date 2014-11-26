
#pragma once


// Inculsions
#include "SItemStructure.h"
#include "DObject/Filtre.h"

//
using GDSObject::FiltreType;
using GDSObject::CFiltre;
using GDSObject::CFiltreListe;


class CSItemFiltre : public CSItemStructure, public CFiltre
{
public:
	// Constructeur
	CSItemFiltre(CStructureMgr* pStructureMgr, unsigned long ulIdFiltre);
	//! Constructeur par copie.
	CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source);
	// Destructeur
	virtual ~CSItemFiltre();


public:
	// Image 
	void SetImage(FiltreType filtreType);

protected:
	CFiltre*	m_pFiltre = nullptr;
};
