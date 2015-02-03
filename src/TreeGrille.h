
#pragma once

// Inclusions
class CTreeIconMgr;
class CStructureMgr;
class CSItemStructure;
class CSItemProjet;
class CSItemFiltre;
class CSItemRessource;
class CSItemControle;

// Inclusions
namespace GDSObject
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

	// Cr�ation de la grille
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
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	void OnDestroy();

	DECLARE_MESSAGE_MAP()

protected:
	// Param�trage de la grille
	void InitialiserProprites();
	// Images dans la grille
	void InitialiserImages();
	
// Accesseurs
protected:
	//
	GDSObject::CProjet*		GetPointer(CSItemProjet* pSItemProjet);
	GDSObject::CFiltre*		GetPointer(CSItemFiltre* pSItemFiltre);
	GDSObject::CRessource*	GetPointer(CSItemRessource* pSItemRessource);
	//
	CSItemStructure* GetSelectedItem();
	CSItemStructure* GetItem(int iRow);
	// D�but de l'�dition dans la grille
	virtual void OnAfterInplaceEditCreated(CBCGPGridItem* pItem, CWnd* pInplaceEdit);
	// Fin de l'�dition dans la grille
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
		bool OnSupprimerFilte(CSItemStructure* pSItem);
		bool OnSupprimerRessource(CSItemStructure* pSItem);
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

	CSItemStructure* m_pSItemDrag = nullptr;
	CSItemStructure* m_pSItemDrop = nullptr;
};

