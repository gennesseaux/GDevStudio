

// Inclusions
#include "Stdafx.h"
#include "GyResGen/RessourceGenerateur.h"
#include "GyResGen/events/Listener.h"


// Constructeur
GyResGen::CListener::CListener(CRessourceGenerateur* pOwner)
{
	_pOwner = pOwner;
}

// Destructeur
GyResGen::CListener::~CListener()
{
}
