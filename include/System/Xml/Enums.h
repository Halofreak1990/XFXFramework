/*****************************************************************************
 *	Enums.h 																 *
 *																			 *
 *	System::Xml Enumerations definition file.								 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_XML_ENUMS_
#define _SYSTEM_XML_ENUMS_

namespace System
{
	namespace Xml
	{
		struct ConformanceLevel
		{
			enum type
			{
				Auto,
				Fragment,
				Document
			};
		};

		struct EntityHandling
		{
			enum type
			{
				ExpandCharEntities = 2,
				ExpandEntities = 1
			};
		};

		struct Formatting
		{
			enum type
			{
				None,
				Indented
			};
		};

		struct NewLineHandling
		{
			enum type
			{
				Replace,
				Entitize,
				None
			};
		};

		struct ReadState
		{
			enum type
			{
				Initial,
				Interactive,
				Error,
				EndOfFile,
				Closed
			};
		};

		struct ValidationType
		{
			enum type
			{
				None,
				Schema
			};
		};

		struct WhitespaceHandling
		{
			enum type
			{
				All,
				Significant,
				None
			};
		};

		struct WriteState
		{
			enum type
			{
				Start,
				Prolog,
				Element,
				Attribute,
				Content,
				Closed,
				Error
			};
		};

		struct XmlDateTimeSerializationMode
		{
			enum type
			{
				Local,
				Utc,
				Unspecified,
				RoundtripKind
			};
		};

		struct XmlNamespaceScope
		{
			enum type
			{
				All,
				ExcludeXml,
				Local
			};
		};

		struct XmlNodeChangedAction
		{
			enum type
			{
				Insert,
				Remove,
				Change
			};
		};

		struct XmlNodeOrder
		{
			enum type
			{
				Before,
				After,
				Same,
				Unknown
			};
		};

		struct XmlNodeType
		{
			enum type
			{
				None,
				Element,
				Attribute,
				Text,
				CDATA,
				EntityReference,
				Entity,
				ProcessingInstruction,
				Comment,
				Document,
				DocumentType,
				DocumentFragment,
				Notation,
				Whitespace,
				SignificantWhitespace,
				EndElement,
				EndEntity,
				XmlDeclaration
			};
		};

		struct XmlOutputMethod
		{
			enum type
			{
				AutoDetect = 3,
				Xml = 0
			};
		};

		struct XmlSpace
		{
			enum type
			{
				None,
				Default,
				Preserve
			};
		};

		struct XmlTokenizedType
		{
			enum type
			{
				CDATA,
				ID,
				IDREF,
				IDREFS,
				ENTITY,
				ENTITIES,
				NMTOKEN,
				NMTOKENS,
				NOTATION,
				ENUMERATION,
				QName,
				NCName,
				None
			};
		};

		/**
		 * Specifies the amount of input or output checking that the created System::Xml::XmlReader and
		 * System::Xml::XmlWriter objects perform.
		 */
		typedef ConformanceLevel::type				ConformanceLevel_t;
		/**
		 * Specifies how the System::Xml::XmlTextReader or System::Xml::XmlValidatingReader handle entities.
		 */
		typedef EntityHandling::type				EntityHandling_t;
		/**
		 * Specifies formatting options for the System::Xml::XmlTextWriter.
		 */
		typedef Formatting::type					Formatting_t;
		/**
		 * Specifies how to handle line breaks.
		 */
		typedef NewLineHandling::type				NewLineHandling_t;
		/**
		 * Specifies the state of the reader.
		 */
		typedef ReadState::type 					ReadState_t;
		/**
		 * Specifies the type of validation to perform.
		 */
		typedef ValidationType::type				ValidationType_t;
		/**
		 * Specifies how white space is handled.
		 */
		typedef WhitespaceHandling::type			WhitespaceHandling_t;
		/**
		 * Specifies the state of the System::Xml::XmlWriter.
		 */
		typedef WriteState::type					WriteState_t;
		/**
		 * Specifies how to treat the time value when converting between string and System::DateTime.
		 */
		typedef XmlDateTimeSerializationMode::type	XmlDateTimeSerializationMode_t;
		/**
		 * Defines the namespace scope.
		 */
		typedef XmlNamespaceScope::type				XmlNamespaceScope_t;
		/**
		 * Specifies the type of node change.
		 */
		typedef XmlNodeChangedAction::type			XmlNodeChangedAction_t;
		/**
		 * Describes the document order of a node compared to a second node.
		 */
		typedef XmlNodeOrder::type					XmlNodeOrder_t;
		/**
		 * Specifies the type of node.
		 */
		typedef XmlNodeType::type					XmlNodeType_t;
		/**
		 * Specifies the method used to serialize the System::Xml::XmlWriter output.
		 */
		typedef XmlOutputMethod::type				XmlOutputMethod_t;
		/**
		 * Specifies the current xml:space scope.
		 */
		typedef XmlSpace::type						XmlSpace_t;
		/**
		 * Represents the XML type for the string. This allows the string to be read as a particular XML type, for example
		 * a CDATA section type.
		 */
		typedef XmlTokenizedType::type				XmlTokenizedType_t;
	}
}

#endif //_SYSTEM_XML_ENUMS_
