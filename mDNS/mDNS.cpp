// mDNS.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

void onError(const void* sender, const Poco::DNSSD::DNSSDResponder::ErrorEventArgs& args)
{
	std::cerr
		<< "Service registration failed: "
		<< args.error.message()
		<< " (" << args.error.code() << ")"
		<< std::endl;
}

//void onRegistered(const void* sender, const Poco::DNSSD::DNSSDResponder::ErrorEventArgs& args)
//{
//	std::cerr
//		<< "Service registration failed: "
//		<< args.error.message()
//		<< " (" << args.error.code() << ")"
//		<< std::endl;
//}



void mDNS::discardAdvertise(Poco::DNSSD::ServiceHandle serviceHandle)
{
	DNSSDResponder dnssdResponder;
	dnssdResponder.unregisterService(serviceHandle);
}
mDNS::mDNS()
{
	initializeDNSSD();
	props = new Poco::DNSSD::Service::Properties;
	dnsResponder = new Poco::DNSSD::DNSSDResponder;
	dnsResponder->start();

}
mDNS::~mDNS()
{
	if (dnsResponder != nullptr) {
		delete dnsResponder;
		dnsResponder = nullptr;
	}

	if (props != nullptr) {
		delete props;
		props = nullptr;
	}
}

ServiceHandle mDNS::advertise(std::string SERVICE_TYPE, int port)
{
	//Service service(SERVICE_TYPE, port, *props);
	Service service(0, "", "", SERVICE_TYPE, "", "", port, *props);
	ServiceHandle sh = dnsResponder->registerService(service);
	dnsResponder->serviceRegistrationFailed += Poco::delegate(onError);
	printf("Service Name: %s. Port: %d", SERVICE_TYPE, port);
	return sh;
}

void mDNS::addProps(std::string key, std::string value) {
	props->add(key, value);
}
