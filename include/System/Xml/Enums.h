#ifndef _SYSTEM_XML_ENUMS_
#define _SYSTEM_XML_ENUMS_

namespace System
{
	namespace Xml
	{
		// Specifies the amount of input or output checking that the created System::Xml::XmlReader and
		// System::Xml::XmlWriter objects perform.
		struct ConformanceLevel
		{
			enum type
			{
				Auto,
				Fragment,
				Document
			};
		};

		// Specifies how the System::Xml::XmlTextReader or System::Xml::XmlValidatingReader handle entities.
		struct EntityHandling
		{
			enum type
			{
				ExpandCharEntities = 2,
			    ExpandEntities = 1
			};
		};

		// Specifies formatting options for the System::Xml::XmlTextWriter.
		struct Formatting
		{
			enum type
			{
				None,
				Indented
			};
		};

		// Specifies how to handle line breaks.
		struct NewLineHandling
		{
			enum type
			{
				Replace,
				Entitize,
				None
			};
		};

		// Specifies the state of the reader.
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

		// Specifies the type of validation to perform.
		struct ValidationType
		{
			enum type
			{
				None,
				Schema
			};
		};

		// Specifies how white space is handled.
		struct WhitespaceHandling
		{
			enum type
			{
				All,
				Significant,
				None
			};
		};

		// Specifies the state of the System::Xml::XmlWriter.
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

		// Specifies how to treat the time value when converting between string and System::DateTime.
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

		// Defines the namespace scope.
		struct XmlNamespaceScope
		{
			enum type
			{
				All,
				ExcludeXml,
				Local
			};
		};

		// Specifies the type of node change.
		struct XmlNodeChangedAction
		{
			enum type
			{
				Insert,
				Remove,
				Change
			};
		};

		// Describes the document order of a node compared to a second node.
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

		// Specifies the type of node.
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

		// Specifies the method used to serialize the System::Xml::XmlWriter output.
		struct XmlOutputMethod
		{
			enum type
			{
				AutoDetect = 3,
				Xml = 0
			};
		};

		// Specifies the current xml:space scope.
		struct XmlSpace
		{
			enum type
			{
				None,
				Default,
				Preserve
			};
		};

		// Represents the XML type for the string. This allows the string to be read as a particular XML type, for example
		// a CDATA section type.
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

		typedef ConformanceLevel::type				ConformanceLevel_t;
		typedef EntityHandling::type				EntityHandling_t;
		typedef Formatting::type					Formatting_t;
		typedef NewLineHandling::type				NewLineHandling_t;
		typedef ReadState::type						ReadState_t;
		typedef ValidationType::type				ValidationType_t;
		typedef WhitespaceHandling::type			WhitespaceHandling_t;
		typedef WriteState::type					WriteState_t;
		typedef XmlDateTimeSerializationMode::type	XmlDateTimeSerializationMode_t;
		typedef XmlNamespaceScope::type				XmlNamespaceScope_t;
		typedef XmlNodeChangedAction::type			XmlNodeChangedAction_t;
		typedef XmlNodeOrder::type					XmlNodeOrder_t;
		typedef XmlNodeType::type					XmlNodeType_t;
		typedef XmlOutputMethod::type				XmlOutputMethod_t;
		typedef XmlSpace::type						XmlSpace_t;
	}
}

#endif //_SYSTEM_XML_ENUMS_
