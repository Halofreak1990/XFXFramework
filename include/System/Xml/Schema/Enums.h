/*****************************************************************************
 *	Enums.h																	 *
 *																			 *
 *	System::Xml::Schema Enumerations definition file. 						 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_XML_SCHEMA_ENUMS_H
#define _SYSTEM_XML_SCHEMA_ENUMS_H

namespace System
{
	namespace Xml
	{
		namespace Schema
		{
			struct XmlSchemaContentProcessing
			{
				enum type
				{
					// Document items are not validated.
					None,
					// Document items must consist of well-formed XML and are not validated by the schema.
					Skip,
					// If the associated schema is found, the document items will be validated. No errors will be thrown otherwise.
					Lax,
					// The schema processor must find a schema associated with the indicated namespace to validate the document items.
					Strict
				};
			};

			struct XmlSchemaContentType
			{
				enum type
				{
					// Text-only content.
					TextOnly,
					// Empty content.
					Empty,
					// Element-only content.
					ElementOnly,
					// Mixed content.
					Mixed
				};
			};

			struct XmlSchemaDatatypeVariety
			{
				enum type
				{
					// A W3C XML schema atomic type.
					Atomic,
					// A W3C XML schema list type.
					List,
					// A W3C XML schema union type.
					Union
				};
			};

			struct XmlSchemaDerivationMethod
			{
				enum type
				{
					// #all. Refers to all derivation methods.
					All = 255,
					// Override default derivation method to allow any derivation.
					Empty = 0,
					// Refers to derivations by Extension.
					Extension = 2,
					// Refers to derivations by List.
					List = 8,
					// Accepts the default derivation method.
					None = 256,
					// Refers to derivations by Restriction.
					Restriction = 4,
					// Refers to derivations by Substitution.
					Substitution = 1,
					// Refers to derivations by Union.
					Union = 16
				};
			};

			struct XmlSchemaForm
			{
				enum type
				{
					// Element and attribute form is not specified in the schema.
					None,
					// Elements and attributes must be qualified with a namespace prefix.
					Qualified,
					// Elements and attributes are not required to be qualified with a namespace prefix.
					Unqualified
				};
			};

			struct XmlSchemaUse
			{
				enum type
				{
					// Attribute use not specified.
					None,
					// Attribute is optional.
					Optional,
					// Attribute cannot be used.
					Prohibited,
					// Attribute must appear once.
					Required
				};
			};

			struct XmlSchemaValidationFlags
			{
				enum type
				{
					// Allow xml:* attributes even if they are not defined in the schema. The attributes will be validated based on their data type.
					AllowXmlAttributes = 16,
					// Do not process identity constraints, inline schemas, schema location hints, or report schema validation warnings.
					None = 0,
					// Process identity constraints (xs:ID, xs:IDREF, xs:key, xs:keyref, xs:unique) encountered during validation.
					ProcessIdentityConstraints = 8,
					// Process inline schemas encountered during validation.
					ProcessInlineSchema = 1,
					// Process schema location hints (xsi:schemaLocation, xsi:noNamespaceSchemaLocation) encountered during validation.
					ProcessSchemaLocation = 2,
					// Report schema validation warnings encountered during validation.
					ReportValidationWarnings = 4
				};
			};

			struct XmlSchemaValidity
			{
				enum type
				{
					// The validity of the XML item is not known.
					NotKnown,
					// The XML item is valid.
					Valid,
					// The XML item is invalid.
					Invalid
				};
			};

			struct XmlSeverityType
			{
				enum type
				{
					// Indicates a validation error occurred when validating the instance document. This applies to document type definitions (DTDs) and XML Schema definition language (XSD) schemas. The World Wide Web Consortium (W3C) validity constraints are considered errors. If no validation event handler has been created, errors throw an exception.
					Error,
					// Indicates that a validation event occurred that is not an error. A warning is typically issued when there is no DTD, or XML Schema to validate a particular element or attribute against. Unlike errors, warnings do not throw an exception if there is no validation event handler.
					Warning
				};
			};

			struct XmlTypeCode
			{
				enum type
				{
					// Any atomic value of a union.
					AnyAtomicType = 10,
					// A W3C XML Schema xs:anyURI type.
					AnyUri = 28,
					// This value supports the .NET Framework infrastructure and is not intended to be used directly from your code.
					Attribute = 5,
					// A W3C XML Schema xs:base64Binary type.
					Base64Binary = 27,
					// A W3C XML Schema xs:boolean type.
					Boolean = 13,
					// A W3C XML Schema xs:byte type.
					Byte = 46,
					// This value supports the .NET Framework infrastructure and is not intended to be used directly from your code.
					Comment = 8,
					// A W3C XML Schema xs:date type.
					Date = 20,
					// A W3C XML Schema xs:dateTime type.
					DateTime = 18,
					// This value supports the .NET Framework infrastructure and is not intended to be used directly from your code.
					DayTimeDuration = 54,
					// A W3C XML Schema xs:decimal type.
					Decimal = 14,
					// This value supports the .NET Framework infrastructure and is not intended to be used directly from your code.
					Document = 3,
					// A W3C XML Schema xs:double type.
					Double = 16,
					// A W3C XML Schema xs:Duration type.
					Duration = 17,
					// This value supports the .NET Framework infrastructure and is not intended to be used directly from your code.
					Element = 4,
					//  A W3C XML Schema xs:ENTITY type.
					Entity = 39,
					// A W3C XML Schema xs:float type.
					Float = 15,
					// A W3C XML Schema xs:gDay type.
					GDay = 24,
					// A W3C XML Schema xs:gMonth type.
					GMonth = 25,
					// A W3C XML Schema xs:gMonthDay type.
					GMonthDay = 23,
					// A W3C XML Schema xs:gYear type.
					GYear = 22,
					// A W3C XML Schema xs:gYearMonth type.
					GYearMonth = 21,
					// A W3C XML Schema xs:hexBinary type.
					HexBinary = 26,
					// A W3C XML Schema xs:ID type.
					Id = 37,
					// A W3C XML Schema xs:IDREF type.
					Idref = 38,
					// A W3C XML Schema xs:int type.
					Int = 44,
					// A W3C XML Schema xs:integer type.
					Integer = 40,
					// An item such as a node or atomic value.
					Item = 1,
				};
			};

			// Provides information about the validation mode of any and anyAttribute element replacements.
			typedef XmlSchemaContentProcessing::type		XmlSchemaContentProcessing_t;
			// Enumerations for the content model of the complex type. This represents the content in the post-schema-validation information set (infoset).
			typedef XmlSchemaContentType::type				XmlSchemaContentType_t;
			// Specifies the W3C XML schema data type variety of the type.
			typedef XmlSchemaDatatypeVariety::type			XmlSchemaDatatypeVariety_t;
			// Provides different methods for preventing derivation.
			typedef XmlSchemaDerivationMethod::type			XmlSchemaDerivationMethod_t;
			// Indicates if attributes or elements need to be qualified with a namespace prefix.
			typedef XmlSchemaForm::type						XmlSchemaForm_t;
			// Indicator of how the attribute is used.
			typedef XmlSchemaUse::type						XmlSchemaUse_t;
			// Specifies schema validation options used by the System::Xml::Schema::XmlSchemaValidator and System::Xml::XmlReader classes.
			typedef XmlSchemaValidationFlags::type			XmlSchemaValidationFlags_t;
			// Represents the validity of an XML item validated by the System.Xml.Schema.XmlSchemaValidator class.
			typedef XmlSchemaValidity::type					XmlSchemaValidity_t;
			// Represents the severity of the validation event.
			typedef XmlSeverityType::type					XmlSeverityType_t;
			// Represents the W3C XML Schema Definition Language (XSD) schema types.
			typedef XmlTypeCode::type						XmlTypeCode_t;
		}
	}
}

#endif // _SYSTEM_XML_SCHEMA_ENUMS_H
