
#pragma once

// Inclusions
class CTreeIconMgr;

// Inclusions
#include "DObject/Projet.h"

class CTreeGrille : public CBCGPGridCtrl
{
	DECLARE_DYNAMIC(CTreeGrille)

public:
	// Constructeur
	CTreeGrille();
	// Destructeur
	virtual ~CTreeGrille();

	// Cr�ation de la grille
	BOOL Create(CView* pView);

public:
	// Initialisation de la grille
	void Initialiser(GDSObject::CProjet* pProjet);
	// Manageur d'icones
	CTreeIconMgr* GetTreeImageMgr() const;


protected:

	DECLARE_MESSAGE_MAP()

protected:
	// Param�trage de la grille
	void InitialiserProprites();
	// Images dans la grille
	void InitialiserImages();

protected:
	CTreeIconMgr* m_pTreeImageMgr = nullptr;
};


