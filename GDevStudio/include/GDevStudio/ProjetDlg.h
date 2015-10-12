
#pragma once

// Inclusions
#include "GDevStudioDialogBase.h"

// Inclusions
#include "GDevStudioApi/Projet.h"


class CProjetDlg : public CGDevStudioDialogBase
{
	DECLARE_DYNAMIC(CProjetDlg)

public:
	// Constructeur
	CProjetDlg(GDSAPI::CProjet* pProjet, CWnd* pParent = NULL);
	// Destructeur
	virtual ~CProjetDlg();

	// Données de boîte de dialogue
	enum { IDD = IDD_PROJET };

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
	afx_msg void OnChange();
	afx_msg void OnOk();


protected:
	// Contrôles
	CBCGPEdit m_edtCode;
	CBCGPEdit m_edtDescription;
	CBCGPEdit m_edtEmplacementFichierH;
	CBCGPEdit m_edtEmplacementFichierCpp;

	CBCGPStatic m_lblInfo;
	CBCGPStatic m_lblCode;
	CBCGPStatic m_lblDescription;
	CBCGPStatic m_lblRepertoires;
	CBCGPStatic m_lblFichierH;
	CBCGPStatic m_lblFichierCpp;

	CBCGPButton	m_btnOk;


private:
	GDSAPI::CProjet* m_pProjet = nullptr;
};
