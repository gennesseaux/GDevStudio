
#pragma once

// Inclusions
#include "GDevStudioModulesManager/ModulesEvents.h"


namespace GyResGen
{
	class CRessourceGenerateur;

	class CListener
	{
		friend class CPropertyGridListener;

	public:
		// Constructeur
		CListener(CRessourceGenerateur* pOwner = nullptr);
		// Destructeur
		~CListener();
		// Force le plugin en s'enregistrer
		virtual void Register(bool bReg) = 0;

	protected:
		CListener(CListener const&) = delete;             // Copy construct
		CListener(CListener&&) = delete;                  // Move construct
		CListener& operator=(CListener const&) = delete;  // Copy assign
		CListener& operator=(CListener &&) = delete;      // Move assign

	private:
		CRessourceGenerateur* _pOwner = nullptr;
	};
}