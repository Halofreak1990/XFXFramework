/*****************************************************************************
 *	Interfaces.h															 *
 *																			 *
 *	System::Xml::Schema Interfaces definition file. 						 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_XML_SCHEMA_INTERFACES_H
#define _SYSTEM_XML_SCHEMA_INTERFACES_H

#include <System/Types.h>

#include "Enums.h"

namespace System
{
	namespace Xml
	{
		namespace Schema
		{
			class XmlSchemaAttribute;
			class XmlSchemaElement;
			class XmlSchemaSimpleType;
			class XmlSchemaType;

			// Defines the post-schema-validation infoset of a validated XML node.
			interface IXmlSchemaInfo
			{
			public:
				virtual bool IsDefault() =0;
				virtual bool IsNil() =0;
				virtual XmlSchemaSimpleType* getMemberType() =0;
				virtual XmlSchemaAttribute* getSchemaAttribute() =0;
				virtual XmlSchemaElement* getSchemaElement() =0;
				virtual XmlSchemaType* SchemaType() =0;
				virtual XmlSchemaValidity_t getValidity() =0;

				virtual ~IXmlSchemaInfo() { }
			};
		}
	}
}

#endif // _SYSTEM_XML_SCHEMA_INTERFACES_H
