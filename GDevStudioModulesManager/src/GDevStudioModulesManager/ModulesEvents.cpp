

// Inclusions
#include "Stdafx.h"
#include "GDevStudioModulesManager/ModulesEvents.h"


// Singleton
GDSMM::CModulesEvents& GDSMM::CModulesEvents::ModulesEvents()
{
	// Since it's a static variable, if the class has already been created,
	// It won't be created again.
	// And it **is** thread-safe in C++11.
	static CModulesEvents _instance;
	// Return a reference to our instance.
	return _instance;
}

// Constructeur
GDSMM::CModulesEvents::CModulesEvents()
{
	int toto=0;
}

// Destructeur
GDSMM::CModulesEvents::~CModulesEvents()
{
	int toto=0;
}

// Property grid
void GDSMM::CModulesEvents::NotifyUpdatePropertyGrid(const PropertyGridEvent event)
{
	propertyGridUpdate.notify(this,event);
}

// Property grid
void GDSMM::CModulesEvents::NotifyUpdateProperty(const PropertyEvent event)
{
	propertyUpdate.notify(this,event);
}
