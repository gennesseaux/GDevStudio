
#pragma once

// Inclusions
#include "GyResGen/events/Listener.h"

// Inclusions
#include "GDevStudioModulesManager/ModulesEvents.h"

// Inclusions
#include "GDevStudioApi\Controle.h"
#include "GDevStudioApi\Ressource.h"


namespace GyResGen
{
	class CRessourceGenerateur;

	class CPropertyGridListener : public CListener
	{
	public:
		// Constructeur
		CPropertyGridListener(CRessourceGenerateur* pOwner = nullptr);
		// Destructeur
		~CPropertyGridListener();
		// Force le plugin en s'enregistrer
		void Register(bool bReg);

	protected:
		CPropertyGridListener(CPropertyGridListener const&) = delete;             // Copy construct
		CPropertyGridListener(CPropertyGridListener&&) = delete;                  // Move construct
		CPropertyGridListener& operator=(CPropertyGridListener const&) = delete;  // Copy assign
		CPropertyGridListener& operator=(CPropertyGridListener &&) = delete;      // Move assign

	public:
		// Réception de la notification
		void OnUpdatePropertyGridEvent(const GDSMM::PropertyGridEvent& event);
		void OnUpdatePropertyEvent(const GDSMM::PropertyEvent& event);

	protected:
		// Mise à jour du property grid
		void OnUpdateRessourcePropertyGrid(GDSAPI::CRessource* pRessource,CBCGPPropList* pPropList);
		void OnUpdateControlePropertyGrid(GDSAPI::CControle* pControle,CBCGPPropList* pPropList);
		// Mise à jour du property du property grid
		void OnUpdateRessourceProperty(GDSAPI::CRessource* pRessource,CBCGPProp* pProp);
		void OnUpdateControleProperty(GDSAPI::CControle* pControle,CBCGPProp* pProp);
	};
}