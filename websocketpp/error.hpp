/*
 * Copyright (c) 2013, Peter Thorson. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the WebSocket++ Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED. IN NO EVENT SHALL PETER THORSON BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef WEBSOCKETPP_ERROR_HPP
#define WEBSOCKETPP_ERROR_HPP

#include <string>

#include <websocketpp/common/cpp11.hpp>
#include <websocketpp/common/system_error.hpp>

namespace websocketpp {

// setup for errors that should be propogated back to the user.
namespace error {
enum value {
    /// Catch-all library error
    general = 1,

    /// send attempted when endpoint write queue was full
    send_queue_full,

    /// Attempted an operation using a payload that was improperly formatted
    /// ex: invalid UTF8 encoding on a text message.
    payload_violation,

    /// Attempted to open a secure connection with an insecure endpoint
    endpoint_not_secure,

    /// Attempted an operation that required an endpoint that is no longer
    /// available. This is usually because the endpoint went out of scope 
    /// before a connection that it created.
    endpoint_unavailable,

    /// An invalid uri was supplied
    invalid_uri,

    /// The endpoint is out of outgoing message buffers
    no_outgoing_buffers,

    /// The connection was in the wrong state for this operation
    invalid_state,
    
    /// Unable to parse close code
    bad_close_code,
    
    /// Close code is in a reserved range
    reserved_close_code,

    /// Close code is invalid
    invalid_close_code,
    
    /// Invalid UTF-8
    invalid_utf8,
    
    /// Bad or unknown connection
    bad_connection,
    
    /// Unit testing utility error code
    test
}; // enum value


class category : public lib::error_category {
public:
	category() {}

	const char *name() const _WEBSOCKETPP_NOEXCEPT_TOKEN_ {
		return "websocketpp";
	}
	
	std::string message(int value) const {
		switch(value) {
			case error::general:
				return "Generic error";
			case error::send_queue_full:
				return "send queue full";
			case error::payload_violation:
				return "payload violation";
			case error::endpoint_not_secure:
				return "endpoint not secure";
			case error::endpoint_unavailable:
				return "endpoint not available";
			case error::invalid_uri:
				return "invalid uri";
			case error::no_outgoing_buffers:
				return "no outgoing message buffers";
			case error::invalid_state:
				return "invalid state";
			case error::bad_close_code:
				return "Unable to extract close code";
			case error::invalid_close_code:
				return "Extracted close code is in an invalid range";
			case error::reserved_close_code:
				return "Extracted close code is in a reserved range";
			case error::invalid_utf8:
				return "Invalid UTF-8";
			case error::bad_connection:
				return "Bad Connection";
			case error::test:
				return "Test Error";
			default:
				return "Unknown";
		}
	}
};

inline const lib::error_category& get_category() {
	static category instance;
	return instance;
}

inline lib::error_code make_error_code(error::value e) {
	return lib::error_code(static_cast<int>(e), get_category());
}

} // namespace error
} // namespace websocketpp

_WEBSOCKETPP_ERROR_CODE_ENUM_NS_START_
template<> struct is_error_code_enum<websocketpp::error::value>
{
    static const bool value = true;
};
_WEBSOCKETPP_ERROR_CODE_ENUM_NS_END_

namespace websocketpp {

class exception : public std::exception {
public: 
    exception(const std::string& msg,
              error::value code = error::general) 
    : m_msg(msg),m_code(code) {}
    ~exception() throw() {}
    
    virtual const char* what() const throw() {
        return m_msg.c_str();
    }
    
    error::value code() const throw() {
        return m_code;
    }
    
    std::string m_msg;
    error::value m_code;
};

} // namespace websocketpp

#endif // WEBSOCKETPP_ERROR_HPP