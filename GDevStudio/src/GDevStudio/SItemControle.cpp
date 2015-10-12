

// Inclusions
#include "Stdafx.h"
#include "GDevStudio/GDevStudio.h"
#include "GDevStudio/SItemControle.h"
#include "GDevStudio/SItemRessource.h"

//
using GDSAPI::CControle;
using GDSAPI::CControleListe;

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
}

// Destructeur
CSItemControle::~CSItemControle()
{
}

 void CSItemControle::SetImage(ControleType controleType)
 {
 	switch(controleType)
 	{
		case ControleType::Boutton:				CSItemStructure::SetImage(GetExclu()?TreeImage::ControleBouttonRemoved:TreeImage::ControleBoutton);							break;
		case ControleType::CheckBox:			CSItemStructure::SetImage(GetExclu()?TreeImage::ControleCheckBoxRemoved:TreeImage::ControleCheckBox);						break;
		case ControleType::Edit:				CSItemStructure::SetImage(GetExclu()?TreeImage::ControleEditRemoved:TreeImage::ControleEdit);								break;
		case ControleType::ComboBox:			CSItemStructure::SetImage(GetExclu()?TreeImage::ControleComboBoxRemoved:TreeImage::ControleComboBox);						break;
		case ControleType::ListBox:				CSItemStructure::SetImage(GetExclu()?TreeImage::ControleListBoxRemoved:TreeImage::ControleListBox);							break;
		case ControleType::GroupBox:			CSItemStructure::SetImage(GetExclu()?TreeImage::ControleGroupBoxRemoved:TreeImage::ControleGroupBox);						break;
		case ControleType::RadioButton:			CSItemStructure::SetImage(GetExclu()?TreeImage::ControleRadioButtonRemoved:TreeImage::ControleRadioButton);					break;
		case ControleType::StaticText:			CSItemStructure::SetImage(GetExclu()?TreeImage::ControleStaticTextRemoved:TreeImage::ControleStaticText);					break;
		case ControleType::Image:				CSItemStructure::SetImage(GetExclu()?TreeImage::ControleImageRemoved:TreeImage::ControleImage);								break;
		case ControleType::ScrollBarHorizontal:	CSItemStructure::SetImage(GetExclu()?TreeImage::ControleScrollBarHorizontalRemoved:TreeImage::ControleScrollBarHorizontal);	break;
		case ControleType::ScrollBarVertical:	CSItemStructure::SetImage(GetExclu()?TreeImage::ControleScrollBarVerticalRemoved:TreeImage::ControleScrollBarVertical);		break;
		case ControleType::Slider:				CSItemStructure::SetImage(GetExclu()?TreeImage::ControleSliderRemoved:TreeImage::ControleSlider);							break;
		case ControleType::Spin:				CSItemStructure::SetImage(GetExclu()?TreeImage::ControleSpinRemoved:TreeImage::ControleSpin);								break;
		case ControleType::Progress:			CSItemStructure::SetImage(GetExclu()?TreeImage::ControleProgressRemoved:TreeImage::ControleProgress);						break;
		case ControleType::HotKey:				CSItemStructure::SetImage(GetExclu()?TreeImage::ControleHotKeyRemoved:TreeImage::ControleHotKey);							break;
		case ControleType::List:				CSItemStructure::SetImage(GetExclu()?TreeImage::ControleListRemoved:TreeImage::ControleList);								break;
		case ControleType::Tree:				CSItemStructure::SetImage(GetExclu()?TreeImage::ControleTreeRemoved:TreeImage::ControleTree);								break;
		case ControleType::Tab:					CSItemStructure::SetImage(GetExclu()?TreeImage::ControleTabRemoved:TreeImage::ControleTab);									break;
		case ControleType::Animation:			CSItemStructure::SetImage(GetExclu()?TreeImage::ControleAnimationRemoved:TreeImage::ControleAnimation);						break;
		case ControleType::DateTimePicker:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleDateTimePickerRemoved:TreeImage::ControleDateTimePicker);			break;
		case ControleType::MontCalendar:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleMontCalendarRemoved:TreeImage::ControleMontCalendar);				break;
		case ControleType::IpAdress:			CSItemStructure::SetImage(GetExclu()?TreeImage::ControleIpAdressRemoved:TreeImage::ControleIpAdress);						break;
		case ControleType::ExtendedComboBox:	CSItemStructure::SetImage(GetExclu()?TreeImage::ControleExtendedComboBoxRemoved:TreeImage::ControleExtendedComboBox);		break;
		case ControleType::Custom:				CSItemStructure::SetImage(GetExclu()?TreeImage::ControleCustomRemoved:TreeImage::ControleCustom);							break;
		case ControleType::Syslink:				CSItemStructure::SetImage(GetExclu()?TreeImage::ControleSyslinkRemoved:TreeImage::ControleSyslink);							break;
		case ControleType::SplitButton:			CSItemStructure::SetImage(GetExclu()?TreeImage::ControleSplitButtonRemoved:TreeImage::ControleSplitButton);					break;
		case ControleType::NetworkAdress:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleNetworkAdressRemoved:TreeImage::ControleNetworkAdress);				break;
		case ControleType::CommandButton:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleCommandButtonRemoved:TreeImage::ControleCommandButton);				break;
		case ControleType::MfcButton:			CSItemStructure::SetImage(GetExclu()?TreeImage::ControleMfcButtonRemoved:TreeImage::ControleMfcButton);						break;
		case ControleType::MfcColorButton:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleMfcColorButtonRemoved:TreeImage::ControleMfcColorButton);			break;
		case ControleType::MfcEditBrowse:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleMfcEditBrowseRemoved:TreeImage::ControleMfcEditBrowse);				break;
		case ControleType::MfcVsListBox:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleMfcVsListBoxRemoved:TreeImage::ControleMfcVsListBox);				break;
		case ControleType::MfcFontComboBox:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleMfcFontComboBoxRemoved:TreeImage::ControleMfcFontComboBox);			break;
		case ControleType::MfcMaskedEdit:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleMfcMaskedEditRemoved:TreeImage::ControleMfcMaskedEdit);				break;
		case ControleType::MfcMenuButton:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleMfcMenuButtonRemoved:TreeImage::ControleMfcMenuButton);				break;
		case ControleType::MfcPropertyGrid:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleMfcPropertyGridRemoved:TreeImage::ControleMfcPropertyGrid);			break;
		case ControleType::MfcShellList:		CSItemStructure::SetImage(GetExclu()?TreeImage::ControleMfcShellListRemoved:TreeImage::ControleMfcShellList);				break;

		default:								CSItemStructure::SetImage(GetExclu()?TreeImage::ControleInconnuRemoved:TreeImage::ControleInconnu);							break;
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
	// Mise à jour de l'icone
	SetImage(GetControleType());
}

// Interface pour la mise à jour du property grid
void CSItemControle::UpdatePropertyGrid(CBCGPPropList* pPropList)
{
	CSItemStructure::UpdatePropertyGrid(pPropList);

	// Divers
	CBCGPProp* pGroupDivers = new CBCGPProp(_T("Divers"));
	CBCGPProp* pNom			= new CBCGPProp(_T("Nom"),		(UINT)Nom,		(_variant_t)ToString(GetLibelle()),		_T("Identifiant du contrôle"));
	CBCGPProp* pType		= new CBCGPProp(_T("Type"),		(UINT)Type,		(_variant_t)ToString(GetType()),		_T("Type de contrôle"));
	CBCGPProp* pExclu		= new CBCGPProp(_T("Exclu"),	(UINT)Exclu,	(_variant_t)GetExclu(),					_T("Exclure de la génération"));

	pNom->Enable(FALSE);
	pType->Enable(FALSE);
	pGroupDivers->AddSubItem(pNom);
	pGroupDivers->AddSubItem(pType);
	pGroupDivers->AddSubItem(pExclu);

	pPropList->AddProperty(pGroupDivers);

	// PropertyGridEvent
	GDSMM::PropertyGridEvent event(this,pPropList);
	theApp.ModulesEvents()->NotifyUpdatePropertyGrid(event);

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
				GDSAPI::CControle controle(this->GetId());
 				controle.SetExclu(bExclu);
 				controle.Sauver();

				//
				UpdateTreeItem();

				break;
			}
	}

	// PropertyEvent
	GDSMM::PropertyEvent event(this,pProp);
	theApp.ModulesEvents()->NotifyUpdateProperty(event);
	
	// Mise à jour dans la grille
	UpdateTreeItem();

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
