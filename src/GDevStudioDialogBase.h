
#pragma once

// Inclusions


class CGDevStudioDialogBase : public CBCGPDialog
{

	DECLARE_DYNAMIC(CGDevStudioDialogBase)


public:
	// Construit une instance de la bo�te de dialogue.
	CGDevStudioDialogBase();

	// Construit une instance de la bo�te de dialogue.
	CGDevStudioDialogBase(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);

	// Construit une instance de la bo�te de dialogue.
	CGDevStudioDialogBase(UINT nIDTemplate, CWnd *pParentWnd = NULL);

	// Lib�re la m�moire occup�e par l'objet.</summary>
	virtual ~CGDevStudioDialogBase();


private:
	void PrivateConstruct();


protected:

	DECLARE_MESSAGE_MAP()


protected:
	// Initialisation de la bo�te de dialogue et de ses contr�les.
	virtual BOOL OnInitDialog();

	// Initialise les objets m�tiers.
	virtual void InitialiseObjetsMetiers() = 0;

	// Initialisation de l'interface utilisateur.
	virtual void InitialiseInterfaceUtilisateur() = 0;

	// Initialisation.
	virtual void Initialiser() = 0;

	// Mise � jour des contraintes.
	virtual void UpdateConstraints() = 0;


protected:
	// Gestion des contraintes
	bool					m_bUpdateConstraints;			// Mise � jour des contraintes en cours	
};
