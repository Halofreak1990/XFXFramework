#ifndef _XFX_GRAPHICS_MODELMESHPARTCOLLECTION_
#define _XFX_GRAPHICS_MODELMESHPARTCOLLECTION_

#include "ModelMeshPart.h"
#include <System/Collections/ObjectModel/ReadOnlyCollection.h>

using namespace System::Collections::ObjectModel;

namespace XFX
{
	namespace Graphics
	{
		/**
		 * 
		 */
		class ModelMeshPartCollection : public ReadOnlyCollection<ModelMeshPart>
		{
		private:
			ModelMeshPartCollection(IList<ModelMeshPart> list);

		public:

		};
	}
}

#endif //_XFX_GRAPHICS_MODELMESHPARTCOLLECTION_
