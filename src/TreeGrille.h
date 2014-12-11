
#pragma once

// Inclusions
class CTreeIconMgr;
class CSItemStructure;

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

	// Création de la grille
	BOOL Create(CView* pView);

public:
	// Initialisation de la grille
	void Initialiser(GDSObject::CProjet* pProjet);
	// Manageur d'icones
	CTreeIconMgr* GetTreeImageMgr() const;


protected:

	DECLARE_MESSAGE_MAP()

protected:
	// Paramétrage de la grille
	void InitialiserProprites();
	// Images dans la grille
	void InitialiserImages();
	
// Accesseurs
protected:
	CSItemStructure* GetSelectedItem();

// Gestion des menus
protected:
	void OnContextMenu(CWnd* pWnd, CPoint point);

	bool IsFiltreAllowed(CSItemStructure* pSItem);
	bool IsModifierAllowed(CSItemStructure* pSItem);
	bool IsSupprimerAllowed(CSItemStructure* pSItem);

	
	//! Commandes des menus
	void OnNouveauFilte();
	void OnModifier();
		void OnModifierProjet(CSItemStructure* pSItem);
		void OnModifierFilte(CSItemStructure* pSItem);
	void OnSupprimer();
		bool OnSupprimerFilte(CSItemStructure* pSItem);

protected:
	virtual void SetRowHeight();
	virtual void OnFillLeftOffset (CDC* pDC, CRect rectFill, CBCGPGridRow* pRow, BOOL bDrawRightBorder = TRUE);


protected:
	CTreeIconMgr* m_pTreeImageMgr = nullptr;
};


