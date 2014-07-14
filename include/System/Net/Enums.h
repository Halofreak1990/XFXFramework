/*****************************************************************************
 *	Enums.h 																 *
 *																			 *
 *	System::Net enumerations definition file.								 *
 *	Copyright (c) XFX Team. All rights reserved.							 *
 *****************************************************************************/
#ifndef _SYSTEM_NET_ENUMS_
#define _SYSTEM_NET_ENUMS_

namespace System
{
	namespace Net
	{
		/**
		 * The HTTP headers that may be specified in a client request.
		 */
		struct HttpRequestHeader
		{
			enum type
			{
				/**
				 * The Cache-Control header, which specifies directives that must be obeyed by all cache control mechanisms along the request/response chain.
				 */
				CacheControl,
				/**
				 * The Connection header, which specifies options that are desired for a particular connection.
				 */
				Connection,
				/**
				 * The Date header, which specifies the date and time at which the request originated.
				 */
				Date,
				/**
				 * The Keep-Alive header, which specifies a parameter used into order to maintain a persistent connection.
				 */
				KeepAlive,
				/**
				 * The Pragma header, which specifies implementation-specific directives that might apply to any agent along the request/response chain.
				 */
				Pragma,
				/**
				 * The Trailer header, which specifies the header fields present in the trailer of a message encoded with chunked transfer-coding.
				 */
				Trailer,
				/**
				 * The Transfer-Encoding header, which specifies what (if any) type of transformation that has been applied to the message body.
				 */
				TransferEncoding,
				/**
				 * The Upgrade header, which specifies additional communications protocols that the client supports.
				 */
				Upgrade,
				/**
				 * The Via header, which specifies intermediate protocols to be used by gateway and proxy agents.
				 */
				Via,
				/**
				 * The Warning header, which specifies additional information about that status or transformation of a message that might not be reflected in the message.
				 */
				Warning,
				/**
				 * The Allow header, which specifies the set of HTTP methods supported.
				 */
				Allow,
				/**
				 * The Content-Length header, which specifies the length, in bytes, of the accompanying body data.
				 */
				ContentLength,
				/**
				 * The Content-Type header, which specifies the MIME type of the accompanying body data.
				 */
				ContentType,
				/**
				 * The Content-Encoding header, which specifies the encodings that have been applied to the accompanying body data.
				 */
				ContentEncoding,
				/**
				 * The Content-Langauge header, which specifies the natural language(s) of the accompanying body data.
				 */
				ContentLanguage,
				/**
				 * The Content-Location header, which specifies a URI from which the accompanying body may be obtained.
				 */
				ContentLocation,
				/**
				 * The Content-MD5 header, which specifies the MD5 digest of the accompanying body data, for the purpose of providing an end-to-end message integrity check.
				 */
				ContentMd5,
				/**
				 * The Content-Range header, which specifies where in the full body the accompanying partial body data should be applied.
				 */
				ContentRange,
				/**
				 * The Expires header, which specifies the date and time after which the accompanying body data should be considered stale.
				 */
				Expires,
				/**
				 * The Last-Modified header, which specifies the date and time at which the accompanying body data was last modified.
				 */
				LastModified,
				/**
				 * The Accept header, which specifies the MIME types that are acceptable for the response.
				 */
				Accept,
				/**
				 * The Accept-Charset header, which specifies the character sets that are acceptable for the response.
				 */
				AcceptCharSet,
				/**
				 * The Accept-Encoding header, which specifies the content encodings that are acceptable for the response.
				 */
				AcceptEncoding,
				/**
				 * The Accept-Language header, which specifies that natural languages that are preferred for the response.
				 */
				AcceptLanguage,
				/**
				 * The Authorization header, which specifies the credentials that the client presents in order to authenticate itself to the server.
				 */
				Authorization,
				/**
				 * The Cookie header, which specifies cookie data presented to the server.
				 */
				Cookie,
				/**
				 * The Expect header, which specifies particular server behaviors that are required by the client.
				 */
				Expect,
				/**
				 * The From header, which specifies an Internet E-mail address for the human user who controls the requesting user agent.
				 */
				From,
				/**
				 * The Host header, which specifies the host name and port number of the resource being requested.
				 */
				Host,
				/**
				 * The If-Match header, which specifies that the requested operation should be performed only if the client's cached copy of the indicated resource is current.
				 */
				IfMatch,
				/**
				 * The If-Modified-Since header, which specifies that the requested operation should be performed only if the requested resource has been modified since the indicated data and time.
				 */
				IfModifiedSince,
				/**
				 * The If-None-Match header, which specifies that the requested operation should be performed only if none of client's cached copies of the indicated resources are current.
				 */
				IfNoneMatch,
				/**
				 * The If-Range header, which specifies that only the specified range of the requested resource should be sent, if the client's cached copy is current.
				 */
				IfRange,
				/**
				 * The If-Unmodified-Since header, which specifies that the requested operation should be performed only if the requested resource has not been modified since the indicated date and time.
				 */
				IfUnmodifiedSince,
				/**
				 * The Max-Forwards header, which specifies an integer indicating the remaining number of times that this request may be forwarded.
				 */
				MaxForwards,
				/**
				 * The Proxy-Authorization header, which specifies the credentials that the client presents in order to authenticate itself to a proxy.
				 */
				ProxyAuthorization,
				/**
				 * The Referer header, which specifies the URI of the resource from which the request URI was obtained.
				 */
				Referer,
				/**
				 * The Range header, which specifies the the sub-range(s) of the response that the client requests be returned in lieu of the entire response.
				 */
				Range,
				/**
				 * The TE header, which specifies the transfer encodings that are acceptable for the response.
				 */
				Te,
				/**
				 * The Translate header, a Microsoft extension to the HTTP specification used in conjunction with WebDAV functionality.
				 */
				Translate,
				/**
				 * The User-Agent header, which specifies information about the client agent.
				 */
				UserAgent
			};
		};

		/**
		 * Contains the values of status codes defined for HTTP.
		 */
		struct HttpStatusCode
		{
			enum type
			{
				/**
				 * Equivalent to HTTP status 202. System::Net::HttpStatusCode::Accepted indicates that the request has been accepted for further processing.
				 */
				Accepted = 202,
				/**
				 * Equivalent to HTTP status 300. System::Net::HttpStatusCode::Ambiguous indicates that the requested information has multiple representations. The default action is to treat this status as a redirect and follow the contents of the Location header associated with this response.
				 */
				Ambiguous = 300,
				/**
				 * Equivalent to HTTP status 502. System::Net::HttpStatusCode::BadGateway indicates that an intermediate proxy server received a bad response from another proxy or the origin server.
				 */
				BadGateway = 502,
				/**
				 * Equivalent to HTTP status 400. System::Net::HttpStatusCode::BadRequest indicates that the request could not be understood by the server. System::Net::HttpStatusCode::BadRequest is sent when no other error is applicable, or if the exact error is unknown or does not have its own error code.
				 */
				BadRequest = 400,
				/**
				 * Equivalent to HTTP status 409. System::Net::HttpStatusCode::Conflict indicates that the request could not be carried out because of a conflict on the server.
				 */
				Conflict = 409,
				/**
				 * Equivalent to HTTP status 100. System::Net::HttpStatusCode::Continue indicates that the client can continue with its request.
				 */
				Continue = 100,
				/**
				 * Equivalent to HTTP status 201. System::Net::HttpStatusCode::Created indicates that the request resulted in a new resource created before the response was sent.
				 */
				Created = 201,
				/**
				 * Equivalent to HTTP status 417. System::Net::HttpStatusCode::ExpectationFailed indicates that an expectation given in an Expect header could not be met by the server.
				 */
				ExpectationFailed = 417,
				/**
				 * Equivalent to HTTP status 403. System::Net::HttpStatusCode::Forbidden indicates that the server refuses to fulfill the request.
				 */
				Forbidden = 403,
				/**
				 * Equivalent to HTTP status 302. System::Net::HttpStatusCode::Found indicates that the requested information is located at the URI specified in the Location header. The default action when this status is received is to follow the Location header associated with the response. When the original request method was POST, the redirected request will use the GET method.
				 */
				Found = 302,
				/**
				 * Equivalent to HTTP status 504. System::Net::HttpStatusCode::GatewayTimeout indicates that an intermediate proxy server timed out while waiting for a response from another proxy or the origin server.
				 */
				GatewayTimeout = 504,
				/**
				 * Equivalent to HTTP status 410. System::Net::HttpStatusCode::Gone indicates that the requested resource is no longer available.
				 */
				Gone = 410,
				/**
				 * Equivalent to HTTP status 505. System::Net::HttpStatusCode::HttpVersionNotSupported indicates that the requested HTTP version is not supported by the server.
				 */
				HttpVersionNotSupported = 505,
				/**
				 * Equivalent to HTTP status 500. System::Net::HttpStatusCode::InternalServerError indicates that a generic error has occurred on the server.
				 */
				InternalServerError = 500,
				/**
				 * Equivalent to HTTP status 411. System::Net::HttpStatusCode::LengthRequired indicates that the required Content-length header is missing.
				 */
				LengthRequired = 411,
				/**
				 * Equivalent to HTTP status 405. System::Net::HttpStatusCode::MethodNotAllowed indicates that the request method (POST or GET) is not allowed on the requested resource.
				 */
				MethodNotAllowed = 405,
				/**
				 * Equivalent to HTTP status 301. System::Net::HttpStatusCode::Moved indicates that the requested information has been moved to the URI specified in the Location header. The default action when this status is received is to follow the Location header associated with the response. When the original request method was POST, the redirected request will use the GET method.
				 */
				Moved = 301,
				/**
				 * Equivalent to HTTP status 301. System::Net::HttpStatusCode::MovedPermanently indicates that the requested information has been moved to the URI specified in the Location header. The default action when this status is received is to follow the Location header associated with the response.
				 */
				MovedPermanently = 302,
				/**
				 * Equivalent to HTTP status 300. System::Net::HttpStatusCode::MultipleChoices indicates that the requested information has multiple representations. The default action is to treat this status as a redirect and follow the contents of the Location header associated with this response.
				 */
				MultipleChoices = 300,
				/**
				 * Equivalent to HTTP status 204. System::Net::HttpStatusCode::NoContent indicates that the request has been successfully processed and that the response is intentionally blank.
				 */
				NoContent = 204,
				/**
				 * Equivalent to HTTP status 203. System::Net::HttpStatusCode::NonAuthoritativeInformation indicates that the returned metadata information is from a cached copy instead of the origin server and therefore may be incorrect.
				 */
				NonAuthorativeInformation = 203,
				/**
				 * Equivalent to HTTP status 406. System::Net::HttpStatusCode::NotAcceptable indicates that the client has indicated with Accept headers that it will not accept any of the available representations of the resource.
				 */
				NotAcceptable = 406,
				/**
				 * Equivalent to HTTP status 404. System::Net::HttpStatusCode::NotFound indicates that the requested resource does not exist on the server.
				 */
				NotFound = 404,
				/**
				 * Equivalent to HTTP status 501. System::Net::HttpStatusCode::NotImplemented indicates that the server does not support the requested function.
				 */
				NotImplemented = 501,
				/**
				 * Equivalent to HTTP status 304. System::Net::HttpStatusCode::NotModified indicates that the client's cached copy is up to date. The contents of the resource are not transferred.
				 */
				NotModified = 304,
				/**
				 * Equivalent to HTTP status 200. System::Net::HttpStatusCode::OK indicates that the request succeeded and that the requested information is in the response. This is the most common status code to receive.
				 */
				OK = 200,
				/**
				 * Equivalent to HTTP status 206. System::Net::HttpStatusCode::PartialContent indicates that the response is a partial response as requested by a GET request that includes a byte range.
				 */
				PartialContent = 206,
				/**
				 * Equivalent to HTTP status 402. System::Net::HttpStatusCode::PaymentRequired is reserved for future use.
				 */
				PaymentRequired = 402,
				/**
				 * Equivalent to HTTP status 412. System::Net::HttpStatusCode::PreconditionFailed indicates that a condition set for this request failed, and the request cannot be carried out. Conditions are set with conditional request headers like If-Match, If-None-Match, or If-Unmodified-Since.
				 */
				PreconditionFailed = 412,
				/**
				 * Equivalent to HTTP status 407. System::Net::HttpStatusCode::ProxyAuthenticationRequired indicates that the requested proxy requires authentication. The Proxy-authenticate header contains the details of how to perform the authentication.
				 */
				ProxyAuthenticationRequired = 407,
				/**
				 * Equivalent to HTTP status 302. System::Net::HttpStatusCode::Redirect indicates that the requested information is located at the URI specified in the Location header. The default action when this status is received is to follow the Location header associated with the response. When the original request method was POST, the redirected request will use the GET method.
				 */
				Redirect = 302,
				/**
				 * Equivalent to HTTP status 307. System::Net::HttpStatusCode::RedirectKeepVerb indicates that the request information is located at the URI specified in the Location header. The default action when this status is received is to follow the Location header associated with the response. When the original request method was POST, the redirected request will also use the POST method.
				 */
				RedirectKeepVerb = 307,
				/**
				 * Equivalent to HTTP status 303. System::Net::HttpStatusCode::RedirectMethod automatically redirects the client to the URI specified in the Location header as the result of a POST. The request to the resource specified by the Location header will be made with a GET.
				 */
				RedirectMethod = 303,
				/**
				 * Equivalent to HTTP status 416. System::Net::HttpStatusCode::RequestedRangeNotSatisfiable indicates that the range of data requested from the resource cannot be returned, either because the beginning of the range is before the beginning of the resource, or the end of the range is after the end of the resource.
				 */
				RequestedRangeNotSatisfiable = 416,
				/**
				 * Equivalent to HTTP status 413. System::Net::HttpStatusCode::RequestEntityTooLarge indicates that the request is too large for the server to process.
				 */
				RequestedEntityTooLarge = 413,
				/**
				 * Equivalent to HTTP status 408. System::Net::HttpStatusCode::RequestTimeout indicates that the client did not send a request within the time the server was expecting the request.
				 */
				RequestTimeout = 408,
				/**
				 * Equivalent to HTTP status 414. System::Net::HttpStatusCode::RequestUriTooLong indicates that the URI is too long.
				 */
				RequestUriTooLong = 414,
				/**
				 * Equivalent to HTTP status 205. System::Net::HttpStatusCode::ResetContent indicates that the client should reset (not reload) the current resource.
				 */
				ResetContent = 205,
				/**
				 * Equivalent to HTTP status 303. System::Net::HttpStatusCode::SeeOther automatically redirects the client to the URI specified in the Location header as the result of a POST. The request to the resource specified by the Location header will be made with a GET.
				 */
				SeeOther = 303,
				/**
				 * Equivalent to HTTP status 503. System::Net::HttpStatusCode::ServiceUnavailable indicates that the server is temporarily unavailable, usually due to high load or maintenance.
				 */
				ServiceUnavailable = 503,
				/**
				 * Equivalent to HTTP status 101. System::Net::HttpStatusCode::SwitchingProtocols indicates that the protocol version or protocol is being changed.
				 */
				SwitchingProtocols = 101,
				/**
				 * Equivalent to HTTP status 307. System::Net::HttpStatusCode::TemporaryRedirect indicates that the request information is located at the URI specified in the Location header. The default action when this status is received is to follow the Location header associated with the response. When the original request method was POST, the redirected request will also use the POST method.
				 */
				TemporaryRedirect = 307,
				/**
				 * Equivalent to HTTP status 401. System::Net::HttpStatusCode::Unauthorized indicates that the requested resource requires authentication. The WWW-Authenticate header contains the details of how to perform the authentication.
				 */
				Unauthorized = 401,
				/**
				 * Equivalent to HTTP status 415. System::Net::HttpStatusCode::UnsupportedMediaType indicates that the request is an unsupported type.
				 */
				UnsupportedMediaType = 415,
				/**
				 * Equivalent to HTTP status 306. System::Net::HttpStatusCode::Unused is a proposed extension to the HTTP/1.1 specification that is not fully specified.
				 */
				Unused = 306,
				/**
				 * Equivalent to HTTP status 305. System::Net::HttpStatusCode::UseProxy indicates that the request should use the proxy server at the URI specified in the Location header.
				 */
				UseProxy = 305
			};
		};

		/**
		 * Defines status codes for the System::Net::WebException class.
		 */
		struct WebExceptionStatus
		{
			enum type
			{
				/**
				 * The remote service point could not be contacted at the transport level.
				 */
				ConnectFailure = 2,
				/**
				 * A message was received that exceeded the specified limit when sending a request or receiving a response from the server.
				 */
				MessageLengthLimitExceeded = 17,
				/**
				 * An internal asynchronous request is pending.
				 */
				Pending = 13,
				/**
				 * The request was canceled, the System::Net::WebRequest::Abort method was called, or an unclassifiable error occurred. This is the default value for System::Net::WebException::Status.
				 */
				RequestCanceled = 6,
				/**
				 * A complete request could not be sent to the remote server.
				 */
				SendFailure = 4,
				/**
				 * No error was encountered.
				 */
				Success = 0,
				/**
				 * An exception of unknown type has occurred.
				 */
				UnknownError = 16
			};
		};

		typedef HttpRequestHeader::type 	HttpRequestHeader_t;
		typedef HttpStatusCode::type		HttpStatusCode_t;
		typedef WebExceptionStatus::type	WebExceptionStatus_t;
	}
}

#endif //_SYSTEM_NET_ENUMS_
