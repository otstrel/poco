//
// SocketAddress.h
//
// $Id: //poco/1.4/Net/include/Poco/Net/SocketAddress.h#2 $
//
// Library: Net
// Package: NetCore
// Module:  SocketAddress
//
// Definition of the SocketAddress class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef Net_SocketAddress_INCLUDED
#define Net_SocketAddress_INCLUDED


#include "Poco/Net/Net.h"
#include "Poco/Net/SocketAddressImpl.h"


namespace Poco {
namespace Net {


class IPAddress;


class Net_API SocketAddress
	/// This class represents an internet (IP) endpoint/socket
	/// address. The address can belong either to the
	/// IPv4 or the IPv6 address family and consists of a
	/// host address and a port number.
{
public:
	SocketAddress();
		/// Creates a wildcard (all zero) IPv4 SocketAddress.

	SocketAddress(const IPAddress& hostAddress, Poco::UInt16 portNumber);
		/// Creates a SocketAddress from an IP address and given port number.

	SocketAddress(Poco::UInt16 port);
		/// Creates a SocketAddress with unspecified (wildcard) IP address 
		/// and given port number.

	SocketAddress(const std::string& hostAddress, Poco::UInt16 portNumber);
		/// Creates a SocketAddress from an IP address and given port number.
		///
		/// The IP address must either be a domain name, or it must
		/// be in dotted decimal (IPv4) or hex string (IPv6) format.

	SocketAddress(const std::string& hostAddress, const std::string& portNumber);
		/// Creates a SocketAddress from an IP address and the
		/// service name or port number.
		///
		/// The IP address must either be a domain name, or it must
		/// be in dotted decimal (IPv4) or hex string (IPv6) format.
		///
		/// The given port must either be a decimal port number, or
		/// a service name.

	explicit SocketAddress(const std::string& hostAndPort);
		/// Creates a SocketAddress from an IP address or host name and the
		/// port number/service name. Host name/address and port number must
		/// be separated by a colon. In case of an IPv6 address,
		/// the address part must be enclosed in brackets.
		///
		/// Examples:
		///     192.168.1.10:80
		///     [::ffff:192.168.1.120]:2040
		///     www.appinf.com:8080

	SocketAddress(const SocketAddress& addr);
		/// Creates a SocketAddress by copying another one.

	SocketAddress(const struct sockaddr* addr, poco_socklen_t length);
		/// Creates a SocketAddress from a native socket address.

	~SocketAddress();
		/// Destroys the SocketAddress.

	SocketAddress& operator = (const SocketAddress& socketAddress);
		/// Assigns another SocketAddress.

	IPAddress host() const;
		/// Returns the host IP address.

	Poco::UInt16 port() const;
		/// Returns the port number.

	poco_socklen_t length() const;
		/// Returns the length of the internal native socket address.

	const struct sockaddr* addr() const;
		/// Returns a pointer to the internal native socket address.

	int af() const;
		/// Returns the address family (AF_INET or AF_INET6) of the address.

	std::string toString() const;
		/// Returns a string representation of the address.

	IPAddress::Family family() const;
		/// Returns the address family of the host's address.

	bool operator < (const SocketAddress& socketAddress) const;
	bool operator == (const SocketAddress& socketAddress) const;
	bool operator != (const SocketAddress& socketAddress) const;

	enum
	{
		MAX_ADDRESS_LENGTH = 
#if defined(POCO_HAVE_IPv6)
			sizeof(struct sockaddr_in6)
#else
			sizeof(struct sockaddr_in)
#endif
			/// Maximum length in bytes of a socket address.
	};

protected:
	void init(const IPAddress& hostAddress, Poco::UInt16 portNumber);
	void init(const std::string& hostAddress, Poco::UInt16 portNumber);
	Poco::UInt16 resolveService(const std::string& service);

private:
	typedef Poco::Net::Impl::SocketAddressImpl Impl;
	typedef Impl* Ptr;

	Ptr pImpl() const;
	void destruct();

	char _memory[sizeof(Poco::Net::Impl::IPv6SocketAddressImpl)];
};


//
// inlines
//


inline void SocketAddress::destruct()
{
	pImpl()->~SocketAddressImpl();
}


inline SocketAddress::Ptr SocketAddress::pImpl() const
{
	return reinterpret_cast<Ptr>(const_cast<char *>(_memory));
}


inline IPAddress::Family SocketAddress::family() const
{
	return host().family();
}


inline 	bool SocketAddress::operator == (const SocketAddress& socketAddress) const
{
	return host() == socketAddress.host() && port() == socketAddress.port();
}


inline bool SocketAddress::operator != (const SocketAddress& socketAddress) const
{
	return host() != socketAddress.host() || port() != socketAddress.port();
}


} } // namespace Poco::Net


#endif // Net_SocketAddress_INCLUDED
