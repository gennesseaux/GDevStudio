

// Inclusions
#include "Stdafx.h"
#include "SItemControle.h"
#include "SItemRessource.h"

//
using GDSObject::CControle;
using GDSObject::CControleListe;

enum PropID
{
	Nom,
	Type,

	Exclu,
};


// Constructeur
CSItemControle::CSItemControle(CStructureMgr* pStructureMgr, const CControle &source, CSItemRessource* pSItemRessource) : CSItemStructure(SItemType::Controle,pStructureMgr), CControle(source)
{
	// Ajout du Controle dans la grille
	CSItemStructure::SetLibelle(CControle::GetLibelle().c_str());
	SetImage(GetControleType());
	CSItemStructure::AjouterLigneGrille(pSItemRessource);
	
	// Parent
	this->AddParent(pSItemRessource);
}

// Destructeur
CSItemControle::~CSItemControle()
{
}

 void CSItemControle::SetImage(ControleType controleType)
 {
 	switch(controleType)
 	{
		case ControleType::Boutton:				CSItemStructure::SetImage(TreeImage::ControleBoutton);				break;
		case ControleType::CheckBox:			CSItemStructure::SetImage(TreeImage::ControleCheckBox);				break;
		case ControleType::Edit:				CSItemStructure::SetImage(TreeImage::ControleEdit);					break;
		case ControleType::ComboBox:			CSItemStructure::SetImage(TreeImage::ControleComboBox);				break;
		case ControleType::ListBox:				CSItemStructure::SetImage(TreeImage::ControleListBox);				break;
		case ControleType::GroupBox:			CSItemStructure::SetImage(TreeImage::ControleGroupBox);				break;
		case ControleType::RadioButton:			CSItemStructure::SetImage(TreeImage::ControleRadioButton);			break;
		case ControleType::StaticText:			CSItemStructure::SetImage(TreeImage::ControleStaticText);			break;
		case ControleType::Image:				CSItemStructure::SetImage(TreeImage::ControleImage);				break;
		case ControleType::ScrollBarHorizontal:	CSItemStructure::SetImage(TreeImage::ControleScrollBarHorizontal);	break;
		case ControleType::ScrollBarVertical:	CSItemStructure::SetImage(TreeImage::ControleScrollBarVertical);	break;
		case ControleType::Slider:				CSItemStructure::SetImage(TreeImage::ControleSlider);				break;
		case ControleType::Spin:				CSItemStructure::SetImage(TreeImage::ControleSpin);					break;
		case ControleType::Progress:			CSItemStructure::SetImage(TreeImage::ControleProgress);				break;
		case ControleType::HotKey:				CSItemStructure::SetImage(TreeImage::ControleHotKey);				break;
		case ControleType::List:				CSItemStructure::SetImage(TreeImage::ControleList);					break;
		case ControleType::Tree:				CSItemStructure::SetImage(TreeImage::ControleTree);					break;
		case ControleType::Tab:					CSItemStructure::SetImage(TreeImage::ControleTab);					break;
		case ControleType::Animation:			CSItemStructure::SetImage(TreeImage::ControleAnimation);			break;
		case ControleType::DateTimePicker:		CSItemStructure::SetImage(TreeImage::ControleDateTimePicker);		break;
		case ControleType::MontCalendar:		CSItemStructure::SetImage(TreeImage::ControleMontCalendar);			break;
		case ControleType::IpAdress:			CSItemStructure::SetImage(TreeImage::ControleIpAdress);				break;
		case ControleType::ExtendedComboBox:	CSItemStructure::SetImage(TreeImage::ControleExtendedComboBox);		break;
		case ControleType::Custom:				CSItemStructure::SetImage(TreeImage::ControleCustom);				break;
		case ControleType::Syslink:				CSItemStructure::SetImage(TreeImage::ControleSyslink);				break;
		case ControleType::SplitButton:			CSItemStructure::SetImage(TreeImage::ControleSplitButton);			break;
		case ControleType::NetworkAdress:		CSItemStructure::SetImage(TreeImage::ControleNetworkAdress);		break;
		case ControleType::CommandButton:		CSItemStructure::SetImage(TreeImage::ControleCommandButton);		break;
		case ControleType::MfcButton:			CSItemStructure::SetImage(TreeImage::ControleMfcButton);			break;
		case ControleType::MfcColorButton:		CSItemStructure::SetImage(TreeImage::ControleMfcColorButton);		break;
		case ControleType::MfcEditBrowse:		CSItemStructure::SetImage(TreeImage::ControleMfcEditBrowse);		break;
		case ControleType::MfcVsListBox:		CSItemStructure::SetImage(TreeImage::ControleMfcVsListBox);			break;
		case ControleType::MfcFontComboBox:		CSItemStructure::SetImage(TreeImage::ControleMfcFontComboBox);		break;
		case ControleType::MfcMaskedEdit:		CSItemStructure::SetImage(TreeImage::ControleMfcMaskedEdit);		break;
		case ControleType::MfcMenuButton:		CSItemStructure::SetImage(TreeImage::ControleMfcMenuButton);		break;
		case ControleType::MfcPropertyGrid:		CSItemStructure::SetImage(TreeImage::ControleMfcPropertyGrid);		break;
		case ControleType::MfcShellList:		CSItemStructure::SetImage(TreeImage::ControleMfcShellList);			break;

		default:								CSItemStructure::SetImage(TreeImage::ControleInconnu);				break;
 	}
}

// Mise à jour de l'item
void CSItemControle::UpdateTreeItem()
{
	// Force l'objet à croire qu'il n'est pas initialisé
	SetInitaliser(false);
	SetAcquis(false);

	// Mise à jour du libelle dans la grille
	CSItemStructure::SetLibelle(CControle::GetLibelle().c_str());
}

// Interface pour la mise à jour du property grid
void CSItemControle::UpdatePropertyGrid(CBCGPPropList* pPropList)
{
	CSItemStructure::UpdatePropertyGrid(pPropList);

	// Divers
	CBCGPProp* pGroupDivers = new CBCGPProp(_T("Divers"));
	CBCGPProp* pNom		= new CBCGPProp(_T("Nom"),		(UINT)Nom,		(_variant_t)ToString(GetLibelle()),		_T("Identifiant du contrôle"));
	CBCGPProp* pType	= new CBCGPProp(_T("Type"),		(UINT)Type,		(_variant_t)ToString(GetType()),		_T("Type de contrôle"));

	pNom->Enable(FALSE);
	pType->Enable(FALSE);
	pGroupDivers->AddSubItem(pNom);
	pGroupDivers->AddSubItem(pType);

	pPropList->AddProperty (pGroupDivers);


	// Paramètres de génération
	CBCGPProp* pGroupParamGen = new CBCGPProp(_T("génération"));
	CBCGPProp* pExclu		= new CBCGPProp(_T("Exclu"),		(UINT)Exclu,		(_variant_t)false,		_T("Exclure de la génération"));

	pGroupParamGen->AddSubItem(pExclu);

	pPropList->AddProperty (pGroupParamGen);

	// Mise à jour de l'affichage
	pPropList->Invalidate();
}

LRESULT CSItemControle::OnPropertyChanged(CBCGPProp* pProp)
{
	PropID id = (PropID)pProp->GetID();

	switch(id)
	{
		case Exclu:
			{
				//
				bool bExclu = (bool)pProp->GetValue();

				//
				GDSObject::CControle controle(this->GetId());
 				controle.SetExclu(bExclu);
 				controle.Sauver();

				//
				UpdateTreeItem();

				break;
			}
	}

	return 0;
}

bool CSItemControle::CanDrag()
{
	return false;
}

bool CSItemControle::CanDrop(CSItemStructure* pSItemDrag)
{
	return false;
}
