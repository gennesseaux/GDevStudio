
#pragma once

// Inclusions Poco
#include <Poco/Foundation.h>
#include <Poco/BasicEvent.h>

// Inclusions
#include <DObject/DObjBase.h>


namespace GDSMM
{
	// Structure de l'évènement utilisé lors de la mise à jour du PropertyGrid
	struct PropertyGridEvent
	{
		PropertyGridEvent(DObject::CDObjBase* pDObjBase, CBCGPPropList* pPropList) : _pDObjBase(pDObjBase),_pPropList(pPropList) {};

		DObject::CDObjBase*	_pDObjBase;
		CBCGPPropList*		_pPropList;
	};

	// Structure de l'évènement utilisé lors de la modification dans PropertyGrid
	struct PropertyEvent
	{
		PropertyEvent(DObject::CDObjBase* pDObjBase, CBCGPProp* pProp) : _pDObjBase(pDObjBase),_pProp(pProp) {};

		DObject::CDObjBase*	_pDObjBase;
		CBCGPProp*			_pProp;
	};
}