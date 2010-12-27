#ifndef _SYSTEM_XML_ENUMS_
#define _SYSTEM_XML_ENUMS_

namespace System
{
	namespace Xml
	{
		/// <summary>
		/// Specifies the amount of input or output checking that the created System.Xml.XmlReader and
		/// System.Xml.XmlWriter objects perform.
		/// </summary>
		struct ConformanceLevel
		{
			enum type
			{
				Auto,
				Fragment,
				Document
			};
		};

		/// <summary>
		/// Specifies how the System.Xml.XmlTextReader or System.Xml.XmlValidatingReader handle entities.
		/// </summary>
		struct EntityHandling
		{
			enum type
			{
				ExpandCharEntities = 2,
			    ExpandEntities = 1
			};
		};

		/// <summary>
		/// Specifies formatting options for the System.Xml.XmlTextWriter.
		/// </summary>
		struct Formatting
		{
			enum type
			{
				None,
				Indented
			};
		};

		/// <summary>
		/// Specifies how to handle line breaks.
		/// </summary>
		struct NewLineHandling
		{
			enum type
			{
				Replace,
				Entitize,
				None
			};
		};

		/// <summary>
		/// Specifies the state of the reader.
		/// </summary>
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

		/// <summary>
		/// Specifies the type of validation to perform.
		/// </summary>
		struct ValidationType
		{
			enum type
			{
				None,
				Schema
			};
		};

		/// <summary>
		/// Specifies how white space is handled.
		struct WhitespaceHandling
		{
			enum type
			{
				All,
				Significant,
				None
			};
		};

		/// <summary>
		/// Specifies the state of the System.Xml.XmlWriter.
		/// </summary>
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

		/// <summary>
		/// Specifies how to treat the time value when converting between string and System.DateTime.
		/// </summary>
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

		/// <summary>
		/// Defines the namespace scope.
		/// </summary>
		struct XmlNamespaceScope
		{
			enum type
			{
				All,
				ExcludeXml,
				Local
			};
		};

		/// <summary>
		/// Specifies the type of node change.
		/// </summary>
		struct XmlNodeChangedAction
		{
			enum type
			{
				Insert,
				Remove,
				Change
			};
		};

		/// <summary>
		/// Describes the document order of a node compared to a second node.
		/// </summary>
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

		/// <summary>
		/// Specifies the type of node.
		/// </summary>
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

		/// <summary>
		/// Specifies the method used to serialize the System.Xml.XmlWriter output.
		/// </summary>
		struct XmlOutputMethod
		{
			enum type
			{
				AutoDetect = 3,
				Xml = 0
			};
		};

		/// <summary>
		/// Specifies the current xml:space scope.
		/// </summary>
		struct XmlSpace
		{
			enum type
			{
				None,
				Default,
				Preserve
			};
		};

		/// <summary>
		/// Represents the XML type for the string. This allows the string to be read as a particular XML type, for example
		/// a CDATA section type.
		/// </summary>
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
