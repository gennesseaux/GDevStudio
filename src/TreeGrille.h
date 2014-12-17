
#pragma once

// Inclusions
class CTreeIconMgr;
class CStructureMgr;
class CSItemStructure;

// Inclusions
namespace GDSObject {
	class CProjet;
	class CFiltre;
}


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
	//! Manager des structures
	CStructureMgr* GetStructureMgr() const { return m_pStructureMgr; }
	//! Manager des structures
	void SetStructureMgr(CStructureMgr* pSMgr) { m_pStructureMgr = pSMgr; }


protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()

protected:
	// Paramétrage de la grille
	void InitialiserProprites();
	// Images dans la grille
	void InitialiserImages();
	
// Accesseurs
protected:
	//
	CSItemStructure* GetSelectedItem();
	// Début de l'édition dans la grille
	virtual void OnAfterInplaceEditCreated(CBCGPGridItem* pItem, CWnd* pInplaceEdit);
	// Fin de l'édition dans la grille
	virtual void OnEndInplaceEdit(CBCGPGridItem* pItem);



// Gestion des menus
protected:
	void OnContextMenu(CWnd* pWnd, CPoint point);
	void OnUpdateMenu(CCmdUI* pCmdUI);

	bool IsFiltreAllowed(CSItemStructure* pSItem);

	bool IsCouperAllowed(CSItemStructure* pSItem);
	bool IsCopierAllowed(CSItemStructure* pSItem);
	bool IsCollerAllowed(CSItemStructure* pSItem);
	bool IsSupprimerAllowed(CSItemStructure* pSItem);
	bool IsRenommerAllowed(CSItemStructure* pSItem);

	bool IsModifierAllowed(CSItemStructure* pSItem);

	
	//! Commandes des menus
	void OnNouveauFilte();
	void OnCouper();
		void OnCouper(CSItemStructure* pSItem);
	void OnCopier();
		void OnCopier(CSItemStructure* pSItem);
	void OnColler();
		void OnColler(CSItemStructure* pSItem);
	void OnSupprimer();
		bool OnSupprimerFilte(CSItemStructure* pSItem);
	void OnRenommer();
		bool OnRenommerProjet(CSItemStructure* pSItem);
		bool OnRenommerFiltre(CSItemStructure* pSItem);
	void OnModifier();
		bool OnModifierProjet(CSItemStructure* pSItem);
		bool OnModifierFilte(CSItemStructure* pSItem);

protected:
	virtual void SetRowHeight();
	virtual void OnFillLeftOffset (CDC* pDC, CRect rectFill, CBCGPGridRow* pRow, BOOL bDrawRightBorder = TRUE);


protected:
	CTreeIconMgr*	m_pTreeImageMgr = nullptr;		//! Manager d'icones
	CStructureMgr*	m_pStructureMgr = nullptr;		//! Manager des structures
};

