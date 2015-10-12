
#pragma once

// Inclusions
#include "Config.h"

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/BasicEvent.h>
#include <Poco/Delegate.h>
#include <Poco/EventArgs.h>

// Inclusions des évènements
#include "GDevStudioModulesManager/events/PropertyGridEvent.h"

namespace GDSMM
{
	class GDEVSTUDIOMM_API CModulesEvents
	{
	public:
		static CModulesEvents& ModulesEvents();

	protected:
		// Constructeur
		CModulesEvents();
		// Destructuer
		~CModulesEvents();

	protected:
		CModulesEvents(CModulesEvents const&) = delete;             // Copy construct
		CModulesEvents(CModulesEvents&&) = delete;                  // Move construct
		CModulesEvents& operator=(CModulesEvents const&) = delete;  // Copy assign
		CModulesEvents& operator=(CModulesEvents &&) = delete;      // Move assign

	// Notifications
	public:
		// Property grid
		void NotifyUpdatePropertyGrid(const PropertyGridEvent event);
		void NotifyUpdateProperty(const PropertyEvent event);

	// Evènements
	public:
		// Property grid
		Poco::BasicEvent<const PropertyGridEvent>	propertyGridUpdate;
		Poco::BasicEvent<const PropertyEvent>		propertyUpdate;
	};
}