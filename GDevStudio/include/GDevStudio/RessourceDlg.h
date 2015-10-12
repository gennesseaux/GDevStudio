#pragma once

// Inclusions
#include "GDevStudioDialogBase.h"

// Inclusions
#include "GDevStudioApi/Ressource.h"
#include "GDevStudioApi/Controle.h"
#include "RcReader/RcReader.h"


class CRessourceDlg : public CGDevStudioDialogBase
{
	DECLARE_DYNAMIC(CRessourceDlg)

public:
	// Constructeur
	CRessourceDlg(GDSAPI::CRessource* pRessource, CWnd* pParent = NULL);
	// Destructeur
	virtual ~CRessourceDlg();

	// Données de boîte de dialogue
	enum { IDD = IDD_RESSOURCE };

protected:
	// Prise en charge de DDX/DDV
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

protected:
	// Initialisation de la boîte de dialogue et de ses contrôles.
	virtual BOOL OnInitDialog();

	// Initialise les objets métiers.
	virtual void InitialiseObjetsMetiers();

	// Initialisation de l'interface utilisateur.
	virtual void InitialiseInterfaceUtilisateur();

	// Initialisation.
	virtual void Initialiser();

	// Mise à jour des contraintes.
	virtual void UpdateConstraints();
	
protected:
	afx_msg void OnEmplacementChange();
	afx_msg void OnRessourceChange();
	afx_msg void OnAjouter();

protected:
	CBCGPEdit		m_edtEmplacement;
	CBCGPComboBox	m_cbxRessource;
	CBCGPButton		m_btnAjouter;
	CBCGPButton		m_btnAnnuler;

private:
	GDSAPI::CRessource*				m_pRessource = nullptr;

	RcReader::CRcReader*			m_pRcReader = nullptr;
	RcReader::CRcResourceDialog*	m_pRcDialog = nullptr;
};
