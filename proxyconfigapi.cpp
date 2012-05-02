#include "proxyconfigapi.h"

ProxyConfigAPI::ProxyConfigAPI(LinphoneProxyConfig *proxyConfig) :
		mProxyConfig(proxyConfig) {
	FBLOG_DEBUG("ProxyConfigAPI::ProxyConfigAPI", this);
	linphone_proxy_config_set_user_data(mProxyConfig, this);
	init_proxy();
}

ProxyConfigAPI::ProxyConfigAPI() {
	FBLOG_DEBUG("ProxyConfigAPI::ProxyConfigAPI", this);
	mProxyConfig = linphone_proxy_config_new();
	linphone_proxy_config_set_user_data(mProxyConfig, this);
	init_proxy();
}

void ProxyConfigAPI::init_proxy() {
	registerMethod("setServerAddr", make_method(this, &ProxyConfigAPI::setServerAddr));
	registerMethod("getServerAddr", make_method(this, &ProxyConfigAPI::getServerAddr));

	registerMethod("setIdentity", make_method(this, &ProxyConfigAPI::setIdentity));
	registerMethod("getIdentity", make_method(this, &ProxyConfigAPI::getIdentity));

	registerMethod("setRoute", make_method(this, &ProxyConfigAPI::setRoute));
	registerMethod("getRoute", make_method(this, &ProxyConfigAPI::getRoute));

	registerMethod("setExpires", make_method(this, &ProxyConfigAPI::setExpires));
	registerMethod("getExpires", make_method(this, &ProxyConfigAPI::getExpires));

	registerMethod("enableRegister", make_method(this, &ProxyConfigAPI::enableRegister));
	registerMethod("registerEnabled", make_method(this, &ProxyConfigAPI::registerEnabled));

	registerMethod("getState", make_method(this, &ProxyConfigAPI::getState));

	registerMethod("edit", make_method(this, &ProxyConfigAPI::edit));
	registerMethod("done", make_method(this, &ProxyConfigAPI::done));
}

ProxyConfigAPI::~ProxyConfigAPI() {
	FBLOG_DEBUG("ProxyConfigAPI::~ProxyConfigAPI", this);
	linphone_proxy_config_set_user_data(mProxyConfig, NULL);
}

int ProxyConfigAPI::setServerAddr(const std::string &server_addr) {
	FBLOG_DEBUG("ProxyConfigAPI::setServerAddr()", "server_addr=" << server_addr);
	return linphone_proxy_config_set_server_addr(mProxyConfig, server_addr.c_str());
}
std::string ProxyConfigAPI::getServerAddr() const{
	FBLOG_DEBUG("ProxyConfigAPI::getServerAddr()", "");
	const char *txt = linphone_proxy_config_get_addr(mProxyConfig);
	return txt != NULL ? txt : "";
}

int ProxyConfigAPI::setIdentity(const std::string &identity) {
	FBLOG_DEBUG("ProxyConfigAPI::setIdentity()", "identity=" << identity);
	return linphone_proxy_config_set_identity(mProxyConfig, identity.c_str());
}
std::string ProxyConfigAPI::getIdentity() const{
	FBLOG_DEBUG("ProxyConfigAPI::getIdentity()", "");
	const char *txt = linphone_proxy_config_get_identity(mProxyConfig);
	return txt != NULL ? txt : "";
}

int ProxyConfigAPI::setRoute(const std::string &route) {
	FBLOG_DEBUG("ProxyConfigAPI::setRoute()", "route=" << route);
	return linphone_proxy_config_set_route(mProxyConfig, route.c_str());
}
std::string ProxyConfigAPI::getRoute() const{
	FBLOG_DEBUG("ProxyConfigAPI::getRoute()", "");
	const char *txt = linphone_proxy_config_get_route(mProxyConfig);
	return txt != NULL ? txt : "";
}

void ProxyConfigAPI::setExpires(int expires) {
	FBLOG_DEBUG("ProxyConfigAPI::expires()", "expires=" << expires);
	return linphone_proxy_config_expires(mProxyConfig, expires);
}
int ProxyConfigAPI::getExpires() const{
	FBLOG_DEBUG("ProxyConfigAPI::getExpires()", "");
	return linphone_proxy_config_get_expires(mProxyConfig);
}

void ProxyConfigAPI::enableRegister(bool val) {
	FBLOG_DEBUG("ProxyConfigAPI::enableRegister()", "val=" << val);
	return linphone_proxy_config_enable_register(mProxyConfig, val ? TRUE : FALSE);
}
bool ProxyConfigAPI::registerEnabled() const{
	FBLOG_DEBUG("ProxyConfigAPI::registerEnabled()", "");
	return linphone_proxy_config_register_enabled(mProxyConfig) == TRUE ? true : false;
}

int ProxyConfigAPI::getState() {
	FBLOG_DEBUG("ProxyConfigAPI::getState()", "");
	return linphone_proxy_config_get_state(mProxyConfig);
}

void ProxyConfigAPI::edit() {
	FBLOG_DEBUG("ProxyConfigAPI::edit()", "");
	linphone_proxy_config_edit(mProxyConfig);
}

int ProxyConfigAPI::done() {
	FBLOG_DEBUG("ProxyConfigAPI::done()", "");
	return linphone_proxy_config_done(mProxyConfig);
}

boost::shared_ptr<ProxyConfigAPI> ProxyConfigAPI::get(LinphoneProxyConfig *proxyConfig) {
	void *ptr = linphone_proxy_config_get_user_data(proxyConfig);
	boost::shared_ptr<ProxyConfigAPI> shared_ptr;
	if (ptr == NULL) {
		shared_ptr = boost::shared_ptr<ProxyConfigAPI>(new ProxyConfigAPI(proxyConfig));
	} else {
		shared_ptr = boost::static_pointer_cast<ProxyConfigAPI>(reinterpret_cast<ProxyConfigAPI *>(ptr)->shared_from_this());
	}
	return shared_ptr;
}