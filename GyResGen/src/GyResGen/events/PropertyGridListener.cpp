

// Inclusions
#include "Stdafx.h"
#include "GyResGen/RessourceGenerateur.h"
#include "GyResGen/TypeDocuments.h"
#include "GyResGen/events/PropertyGridListener.h"

#include "GyResGen/DObject/Controle.h"
#include "GyResGen/DObject/Ressource.h"


// Constructeur
GyResGen::CPropertyGridListener::CPropertyGridListener(CRessourceGenerateur* pOwner) : CListener(pOwner)
{
}

// Destructeur
GyResGen::CPropertyGridListener::~CPropertyGridListener()
{
	Register(false);
}

void GyResGen::CPropertyGridListener::Register(bool bReg)
{
	if(bReg)
	{
		// Ajout du listner
		GDSMM::CModulesEvents::ModulesEvents().propertyGridUpdate += Poco::delegate(this,&CPropertyGridListener::OnUpdatePropertyGridEvent);
		GDSMM::CModulesEvents::ModulesEvents().propertyUpdate += Poco::delegate(this,&CPropertyGridListener::OnUpdatePropertyEvent);
	}
	else
	{
		// Suppression du listner
		GDSMM::CModulesEvents::ModulesEvents().propertyGridUpdate -= Poco::delegate(this,&CPropertyGridListener::OnUpdatePropertyGridEvent);
		GDSMM::CModulesEvents::ModulesEvents().propertyUpdate -= Poco::delegate(this,&CPropertyGridListener::OnUpdatePropertyEvent);
	}
}

// Réception de la notification
void GyResGen::CPropertyGridListener::OnUpdatePropertyGridEvent(const GDSMM::PropertyGridEvent& event)
{
	// Ressource
	if(dynamic_cast<GDSAPI::CRessource*>(event._pDObjBase))
		OnUpdateRessourcePropertyGrid(dynamic_cast<GDSAPI::CRessource*>(event._pDObjBase),event._pPropList);

	// Controle
	if(dynamic_cast<GDSAPI::CControle*>(event._pDObjBase))
		OnUpdateControlePropertyGrid(dynamic_cast<GDSAPI::CControle*>(event._pDObjBase),event._pPropList);
}

void GyResGen::CPropertyGridListener::OnUpdateRessourcePropertyGrid(GDSAPI::CRessource* pRessource,CBCGPPropList* pPropList)
{
	GyResGen::CRessource ressource(pRessource->GetId(), pRessource);

	CBCGPProp* pGroupGeneration = new CBCGPProp(_T("Génération"));

	//
	CBCGPProp* pDocuments = new CBCGPProp(_T("Type de document"),(UINT)ResDocument,(_variant_t)"",_T(""));
	// Ajout des types de documents pouvant être générés
	CTypeDocument typeDocument;

	// Ajout des type de documents possible
	for( auto& td : typeDocument)
		pDocuments->AddOption(ToString(std::get<2>(td)),0,(DWORD_PTR)std::get<0>(td));
	pDocuments->AllowEdit(FALSE);

	// Selection du document existant
	if(ressource.GetUuidDocument().isNull()==false)	
	{
		pDocuments->SetValue((_variant_t)ToString(typeDocument.Nom(ressource.GetUuidDocument())));
		pDocuments->SetDescription((_variant_t)ToString(typeDocument.Description(ressource.GetUuidDocument())));
	}
	pGroupGeneration->AddSubItem(pDocuments);

	CBCGPProp* pClasseNom = new CBCGPProp(_T("Nom de la classe"),(UINT)ResClasseNom,(_variant_t)ToString(ressource.GetClasseNom()),_T("Nom de la classe"));
	pGroupGeneration->AddSubItem(pClasseNom);


	CBCGPProp* pGroupOptions = new CBCGPProp(_T("Options"));

	CBCGPProp* pDbMandatory = new CBCGPProp(_T("DbMandatory"),(UINT)ResDbMandatory,(_variant_t)ressource.GetDbMandatory(),_T("Inclure DbMandatory"));
	pGroupOptions->AddSubItem(pDbMandatory);


	CBCGPProp* pChangeHandler = new CBCGPProp(_T("GWndChangeHandler"),(UINT)ResChangeHandler,(_variant_t)ressource.GetChangeHandler(),_T("Inclure GWndChangeHandler"));
	pGroupOptions->AddSubItem(pChangeHandler);


	CBCGPProp* pWndResizer = new CBCGPProp(_T("WndResizer"),(UINT)ResWndResizer,(_variant_t)ressource.GetWndResizer(),_T("Inclure WndResizer"));
	pGroupOptions->AddSubItem(pWndResizer);


	CBCGPProp* pXSuperTooltip = new CBCGPProp(_T("XSuperTooltip"),(UINT)ResXSuperTooltip,(_variant_t)ressource.GetXSuperTooltip(),_T("Inclure XSuperTooltip"));
	pGroupOptions->AddSubItem(pXSuperTooltip);

	//
	pPropList->AddProperty(pGroupGeneration);
	pPropList->AddProperty(pGroupOptions);
}

void GyResGen::CPropertyGridListener::OnUpdateControlePropertyGrid(GDSAPI::CControle* pControle,CBCGPPropList* pPropList)
{
	GyResGen::CControle controle(pControle->GetId(), pControle);

	// Paramètres de génération
	CBCGPProp* pGroupParamGen	= new CBCGPProp(_T("Génération"));
	CBCGPProp* pClasse			= new CBCGPProp(_T("Classe"),		(UINT)CtlClasseNom,		(_variant_t)ToString(controle.GetClasseNom()),	_T(""));
	CBCGPProp* pVariable		= new CBCGPProp(_T("Variable"),		(UINT)CtlVariableNom,	(_variant_t)ToString(controle.GetVariableNom()),		_T(""));

	pGroupParamGen->AddSubItem(pClasse);
	pGroupParamGen->AddSubItem(pVariable);

	pPropList->AddProperty (pGroupParamGen);
	
}

void GyResGen::CPropertyGridListener::OnUpdatePropertyEvent(const GDSMM::PropertyEvent& event)
{
	// Ressource
	if(dynamic_cast<GDSAPI::CRessource*>(event._pDObjBase))
		OnUpdateRessourceProperty(dynamic_cast<GDSAPI::CRessource*>(event._pDObjBase),event._pProp);

	// Controle
	if(dynamic_cast<GDSAPI::CControle*>(event._pDObjBase))
		OnUpdateControleProperty(dynamic_cast<GDSAPI::CControle*>(event._pDObjBase),event._pProp);
}

void GyResGen::CPropertyGridListener::OnUpdateRessourceProperty(GDSAPI::CRessource* pRessource,CBCGPProp* pProp)
{
	PropID id = (PropID)pProp->GetID();

	switch(id)
	{
		case ResDocument:
		{
			//
			CTypeDocument typeDocument;

			// Option selectionnée
			int iIndex = pProp->GetSelectedOption();
			DWORD_PTR dataOption  = pProp->GetOptionData(iIndex);
			int idxTypeDocument = (int)dataOption;

			//
			GyResGen::CRessource ressource(pRessource->GetId(),pRessource);
			ressource.SetUuidDocument(typeDocument.uuid(idxTypeDocument));
			ressource.Sauver();

			break;
		}
		break;

		case ResClasseNom:
		{
			//
			std::string sClasseNom= ToStdString((CString)(LPCTSTR)(_bstr_t)pProp->GetValue());

			//
			GyResGen::CRessource ressource(pRessource->GetId(),pRessource);
			ressource.SetClasseNom(sClasseNom);
			ressource.Sauver();

			break;
		}
		break;

		case ResDbMandatory:
		{
			//
			bool bResDbMandatory = (bool)pProp->GetValue();

			//
			GyResGen::CRessource ressource(pRessource->GetId(),pRessource);
			ressource.SetDbMandatory(bResDbMandatory);
			ressource.Sauver();

			break;
		}
		break;

		case ResChangeHandler:
		{
			//
			bool bChangeHandler = (bool)pProp->GetValue();

			//
			GyResGen::CRessource ressource(pRessource->GetId(),pRessource);
			ressource.SetChangeHandler(bChangeHandler);
			ressource.Sauver();

			break;
		}
		break;

		case ResWndResizer:
		{
			//
			bool bWndResizer = (bool)pProp->GetValue();

			//
			GyResGen::CRessource ressource(pRessource->GetId(),pRessource);
			ressource.SetWndResizer(bWndResizer);
			ressource.Sauver();

			break;
		}
		break;

		case ResXSuperTooltip:
		{
			//
			bool bXSuperTooltip = (bool)pProp->GetValue();

			//
			GyResGen::CRessource ressource(pRessource->GetId(),pRessource);
			ressource.SetXSuperTooltip(bXSuperTooltip);
			ressource.Sauver();

			break;
		}
		break;
	}
}

void GyResGen::CPropertyGridListener::OnUpdateControleProperty(GDSAPI::CControle* pControle,CBCGPProp* pProp)
{
	PropID id = (PropID)pProp->GetID();

	switch(id)
	{
		case CtlClasseNom:
		{
			//
			std::string sClasseNom= ToStdString((CString)(LPCTSTR)(_bstr_t)pProp->GetValue());

			//
			GyResGen::CControle controle(pControle->GetId(),pControle);
			controle.SetClasseNom(sClasseNom);
			controle.Sauver();

			//
			pProp->SetValue((_variant_t)ToString(controle.GetClasseNom()));

			break;
		}
		break;

		case CtlVariableNom:
		{
			//
			std::string sVariableNom= ToStdString((CString)(LPCTSTR)(_bstr_t)pProp->GetValue());

			//
			GyResGen::CControle controle(pControle->GetId(),pControle);
			controle.SetVariableNom(sVariableNom);
			controle.Sauver();

			//
			pProp->SetValue((_variant_t)ToString(controle.GetVariableNom()));

			break;
		}
		break;
	}
}
