#ifdef MDNS_EXPORTS
#define MDNS_API __declspec(dllexport)
#else
#define MDNS_API __declspec(dllimport)
#endif // STREAMSERVER_EXPORTS

#include "Poco/DNSSD/DNSSDResponder.h"
//#if POCO_OS == POCO_OS_LINUX && !defined(POCO_DNSSD_USE_BONJOUR)
//#include "Poco/DNSSD/Avahi/Avahi.h"
//#else
#include "Poco/DNSSD/Bonjour/Bonjour.h"
//#endif
#include "Poco/Delegate.h"

#include <iostream>
#include <assert.h>
#include <string>

using namespace Poco::DNSSD;
class MDNS_API mDNS {
public:
	mDNS();
	~mDNS();
	ServiceHandle advertise(std::string serviceName, int port);
	void addProps(std::string key, std::string value);
	void discardAdvertise(Poco::DNSSD::ServiceHandle serviceHandle);

private:
	DNSSDResponder * dnsResponder;
	Poco::DNSSD::Service::Properties * props;
};
