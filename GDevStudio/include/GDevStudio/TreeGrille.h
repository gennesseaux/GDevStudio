
#pragma once

// Inclusions
class CTreeRow;
class CTreeIconMgr;
class CStructureMgr;
class CSItemStructure;
class CSItemProjet;
class CSItemFiltre;
class CSItemRessource;
class CSItemControle;

// Inclusions
namespace GDSAPI
{
	class CProjet;
	class CFiltre;
	class CRessource;
	class CControle;
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
	// Création d'une ligne
	CBCGPGridRow* CreateRow(CSItemStructure* pSItem);

public:
	// Initialisation de la grille
	void Initialiser(GDSAPI::CProjet* pProjet);
	// Manageur d'icones
	CTreeIconMgr* GetTreeImageMgr() const;
	//! Manager des structures
	CStructureMgr* GetStructureMgr() const { return m_pStructureMgr; }
	//! Manager des structures
	void SetStructureMgr(CStructureMgr* pSMgr) { m_pStructureMgr = pSMgr; }


protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnDestroy();

	DECLARE_MESSAGE_MAP()

protected:
	// Paramétrage de la grille
	void InitialiserProprites();
	// Images dans la grille
	void InitialiserImages();
	
// Accesseurs
protected:
	//
	GDSAPI::CProjet*	GetPointer(CSItemProjet* pSItemProjet);
	GDSAPI::CFiltre*	GetPointer(CSItemFiltre* pSItemFiltre);
	GDSAPI::CRessource*	GetPointer(CSItemRessource* pSItemRessource);
	GDSAPI::CControle*	GetPointer(CSItemControle* pSItemControle);
	//
	CSItemStructure* GetSelectedItem();
	CSItemStructure* GetItem(int iRow);
	// Début de l'édition dans la grille
	virtual void OnAfterInplaceEditCreated(CBCGPGridItem* pItem, CWnd* pInplaceEdit);
	// Fin de l'édition dans la grille
	virtual void OnEndInplaceEdit(CBCGPGridItem* pItem);
	// Drag and drop
 	virtual BOOL StartDragItems (CPoint point);
	virtual void StopDragItems ();
	virtual BOOL DoDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual BOOL DoDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);


// Surcharges de la grille
protected:
	virtual void OnSelChanged (const CBCGPGridRange &range, BOOL bSelect);


// Gestion des menus
protected:
	void OnContextMenu(CWnd* pWnd, CPoint point);
	void OnUpdateMenu(CCmdUI* pCmdUI);

	bool IsFiltreAllowed(CSItemStructure* pSItem);
	bool IsRessourceAllowed(CSItemStructure* pSItem);

	bool IsCouperAllowed(CSItemStructure* pSItem);
	bool IsCopierAllowed(CSItemStructure* pSItem);
	bool IsCollerAllowed(CSItemStructure* pSItem);
	bool IsSupprimerAllowed(CSItemStructure* pSItem);
	bool IsRenommerAllowed(CSItemStructure* pSItem);

	bool IsModifierAllowed(CSItemStructure* pSItem);
	bool IsExclureAllowed(CSItemStructure* pSItem);
	bool IsActualiserAllowed(CSItemStructure* pSItem);

	
	//! Commandes des menus
	void OnNouveauFiltre();
		bool OnNouveauFiltre(CSItemFiltre* pSItem);
	void OnNouveauRessource();
		bool OnNouveauRessource(CSItemFiltre* pSItem);
	void OnCouper();
		void OnCouper(CSItemStructure* pSItem);
	void OnCopier();
		void OnCopier(CSItemStructure* pSItem);
	void OnColler();
		void OnColler(CSItemStructure* pSItem);
	void OnSupprimer();
		bool OnSupprimerFilte(CSItemFiltre* pSItem);
		bool OnSupprimerRessource(CSItemRessource* pSItem);
	void OnRenommer();
		bool OnRenommerProjet(CSItemProjet* pSItem);
		bool OnRenommerFiltre(CSItemFiltre* pSItem);
	void OnModifier();
		bool OnModifierProjet(CSItemProjet* pSItem);
		bool OnModifierFilte(CSItemFiltre* pSItem);
	void OnExclure();
		bool OnExclureControle(CSItemControle* pSItem);
	void OnActualiser();
		bool OnActualiserProjet(CSItemProjet* pSItem);
		bool OnActualiserRessource(CSItemRessource* pSItem);

protected:
	virtual void SetRowHeight();
	virtual BOOL OnDrawItem (CDC* pDC, CBCGPGridRow* pItem);
	virtual COLORREF OnFillSelItem (CDC* pDC, CRect rectFill, CBCGPGridItem* pItem);


protected:
	CTreeIconMgr*	m_pTreeImageMgr = nullptr;		//! Manager d'icones
	CStructureMgr*	m_pStructureMgr = nullptr;		//! Manager des structures

	CSItemStructure* m_pSItemDrag = nullptr;
	CSItemStructure* m_pSItemDrop = nullptr;
};

