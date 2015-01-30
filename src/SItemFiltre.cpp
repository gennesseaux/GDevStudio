

// Inclusions
#include "Stdafx.h"
#include "SItemFiltre.h"
#include "SItemProjet.h"
#include "SItemRessource.h"

enum PropID
{
	Nom,
	CheminH,
	CheminCpp,
};


// Constructeur
CSItemFiltre::CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source) : CSItemStructure(SItemType::Filtre,pStructureMgr), CFiltre(source)
{
	// Ajout du Filtre dans la grille
	CSItemStructure::SetLibelle(CFiltre::GetLibelle().c_str());
	SetImage(GetType());
}

// Constructeur
CSItemFiltre::CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source, CSItemProjet* pSItemProjet) : CSItemFiltre(pStructureMgr,source)
{
	// Ajout du Filtre dans la grille
	CSItemStructure::AjouterLigneGrille(pSItemProjet);

	// Parent
	this->AddParent(pSItemProjet);

	// Ajout des filtres du filtre
	CFiltreListe* pFiltreListe = GetFiltreListe();
	for (int i = 0; i < pFiltreListe->GetCount() ; i++)
	{
		CFiltre* pFiltre = pFiltreListe->GetAt(i);
		pFiltre->Initialiser();

		CSItemFiltre* pSItemFiltre = new CSItemFiltre(pStructureMgr,*pFiltre, this);

		pFiltreListe->RemoveAt(i);
		pFiltreListe->InsertAt(i,pSItemFiltre);
	}

	// Ajout des ressources du filtre
	CRessourceListe* pRessourceListe = GetRessourceListe();
	for (int i = 0; i < pRessourceListe->GetCount() ; i++)
	{
		CRessource* pRessource = pRessourceListe->GetAt(i);
		pRessource->Initialiser();

		CSItemRessource* pSItemRessource = new CSItemRessource(pStructureMgr,*pRessource, this);

		pRessourceListe->RemoveAt(i);
		pRessourceListe->InsertAt(i,pSItemRessource);
	}
}

// Constructeur
CSItemFiltre::CSItemFiltre(CStructureMgr* pStructureMgr, const CFiltre &source, CSItemFiltre* pSItemFiltre) : CSItemFiltre(pStructureMgr,source)
{
	// Ajout du Filtre dans la grille
	CSItemStructure::AjouterLigneGrille(pSItemFiltre);

	//
	pSItemFiltre->Expand(FALSE);

	// Parent
	this->AddParent(pSItemFiltre);

	// Ajout des filtres du filtre
	CFiltreListe* pFiltreListe = GetFiltreListe();
	for (int i = 0; i < pFiltreListe->GetCount() ; i++)
	{
		CFiltre* pFiltre = pFiltreListe->GetAt(i);
		pFiltre->Initialiser();

		CSItemFiltre* pSItemFiltre = new CSItemFiltre(pStructureMgr,*pFiltre, this);

		pFiltreListe->RemoveAt(i);
		pFiltreListe->InsertAt(i,pSItemFiltre);
	}
}

// Destructeur
CSItemFiltre::~CSItemFiltre()
{
}

void CSItemFiltre::SetImage(FiltreType filtreType)
{
	switch(filtreType)
	{
		case FiltreType::Filtre:		CSItemStructure::SetImage(TreeImage::Filtre);			break;
		case FiltreType::SQL:			CSItemStructure::SetImage(TreeImage::FiltreSql);		break;
		case FiltreType::SQLite:		CSItemStructure::SetImage(TreeImage::FiltreSQLite);		break;
		case FiltreType::Ressource:		CSItemStructure::SetImage(TreeImage::FiltreRessource);	break;
	}
}

// Mise à jour de l'item
void CSItemFiltre::UpdateTreeItem()
{
	// Force l'objet à croire qu'il n'est pas initialisé
	SetInitaliser(false);
	SetAcquis(false);

	// Mise à jour du libelle dans la grille
	CSItemStructure::SetLibelle(CFiltre::GetLibelle().c_str());
}

// Interface pour la mise à jour du property grid
void CSItemFiltre::UpdatePropertyGrid(CBCGPPropList* pPropList)
{
	CSItemStructure::UpdatePropertyGrid(pPropList);

	// Ajout des propriétés
	CBCGPProp* pGroupDivers = new CBCGPProp(_T("Divers"));
	CBCGPProp* pNom		= new CBCGPProp(_T("Nom"),						(UINT)Nom,			(_variant_t)ToString(this->GetLibelle()),			_T(""));
	CBCGPProp* pChH		= new CBCGPProp(_T("Chemin des fichiers .h"),	(UINT)CheminH,		(_variant_t)ToString(GetHFolder().toString()),		_T(""));
	CBCGPProp* pChCpp	= new CBCGPProp(_T("Chemin des fichiers .cpp"),	(UINT)CheminCpp,	(_variant_t)ToString(GetCppFolder().toString()),	_T(""));

	pGroupDivers->AddSubItem(pNom);
	pGroupDivers->AddSubItem(pChH);
	pGroupDivers->AddSubItem(pChCpp);

	pPropList->AddProperty (pGroupDivers);

	// Mise à jour de l'affichage
	pPropList->Invalidate();
}

LRESULT CSItemFiltre::OnPropertyChanged(CBCGPProp* pProp)
{
	PropID id = (PropID)pProp->GetID();

	switch(id)
	{
		case Nom:
			{
				//
				CString sLibelle = (LPCTSTR)(_bstr_t)pProp->GetValue();

				//
				GDSObject::CFiltre filtre(this->GetId());
 				filtre.SetLibelle(ToStdString(sLibelle));
 				filtre.Sauver();

				//
				UpdateTreeItem();

				break;
			}

		case CheminH:
			break;

		case CheminCpp:
			break;
	}

	return 0;
}
