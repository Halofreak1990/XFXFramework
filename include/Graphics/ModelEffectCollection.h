/*****************************************************************************
 *	ModelEffectCollection.h 												 *
 *																			 *
 *	XFX::Graphics::ModelEffectCollection class definition file  			 *
 *	Copyright (c) XFX Team. All Rights Reserved 							 *
 *****************************************************************************/
#ifndef _XFX_GRAPHICS_MODELEFFECTCOLLECTION_
#define _XFX_GRAPHICS_MODELEFFECTCOLLECTION_

#include "Effect.h"
#include <System/Collections/ObjectModel/ReadOnlyCollection.h>

using namespace System::Collections::ObjectModel;

namespace XFX
{
	namespace Graphics
	{
		/**
		 * Represents a collection of effects associated with a model.
		 */
		class ModelEffectCollection : public ReadOnlyCollection<Effect*>
		{
		private:
			friend class Model;

			ModelEffectCollection(IList<Effect*>* list);
		};
	}
}

#endif //_XFX_GRAPHICS_MODELEFFECTCOLLECTION_
