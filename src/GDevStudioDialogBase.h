
#pragma once

// Inclusions


class CGDevStudioDialogBase : public CBCGPDialog
{

	DECLARE_DYNAMIC(CGDevStudioDialogBase)


public:
	// Construit une instance de la boîte de dialogue.
	CGDevStudioDialogBase();

	// Construit une instance de la boîte de dialogue.
	CGDevStudioDialogBase(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);

	// Construit une instance de la boîte de dialogue.
	CGDevStudioDialogBase(UINT nIDTemplate, CWnd *pParentWnd = NULL);

	// Libère la mémoire occupée par l'objet.</summary>
	virtual ~CGDevStudioDialogBase();


private:
	void PrivateConstruct();


protected:

	DECLARE_MESSAGE_MAP()


protected:
	// Initialisation de la boîte de dialogue et de ses contrôles.
	virtual BOOL OnInitDialog();

	// Initialise les objets métiers.
	virtual void InitialiseObjetsMetiers() = 0;

	// Initialisation de l'interface utilisateur.
	virtual void InitialiseInterfaceUtilisateur() = 0;

	// Initialisation.
	virtual void Initialiser() = 0;

	// Mise à jour des contraintes.
	virtual void UpdateConstraints() = 0;


protected:
	// Gestion des contraintes
	bool					m_bUpdateConstraints;			// Mise à jour des contraintes en cours	
};
