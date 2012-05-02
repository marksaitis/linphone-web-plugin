#include "payloadtypeapi.h"
#include "coreapi.h"

PayloadTypeAPI::PayloadTypeAPI(const boost::shared_ptr<CoreAPI> &core, PayloadType *payloadType) :
		mCore(core), mPayloadType(payloadType) {
	FBLOG_DEBUG("PayloadTypeAPI::PayloadTypeAPI", this);
	//mPayloadType->user_data = this;

	registerProperty("type", make_property(this, &PayloadTypeAPI::getType));
	registerProperty("clockRate", make_property(this, &PayloadTypeAPI::getClockRate));
	registerProperty("bitsPerSample", make_property(this, &PayloadTypeAPI::getBitsPerSample));
	registerProperty("zeroPattern", make_property(this, &PayloadTypeAPI::getZeroPattern));
	registerProperty("patternLength", make_property(this, &PayloadTypeAPI::getPatternLength));
	registerProperty("normalBitrate", make_property(this, &PayloadTypeAPI::getNormalBitrate));
	registerProperty("mimeType", make_property(this, &PayloadTypeAPI::getMimeType));
	registerProperty("channels", make_property(this, &PayloadTypeAPI::getChannels));
	registerProperty("recvFmtp", make_property(this, &PayloadTypeAPI::getRecvFmtp));
	registerProperty("sendFmtp", make_property(this, &PayloadTypeAPI::getSendFmtp));
	registerProperty("flags", make_property(this, &PayloadTypeAPI::getFlags));
	registerProperty("enabled", make_property(this, &PayloadTypeAPI::getEnabled, &PayloadTypeAPI::setEnabled));
}

bool PayloadTypeAPI::getEnabled() const {
	FBLOG_DEBUG("PayloadTypeAPI::getEnabled()", this);
	boost::shared_ptr<CoreAPI> core(mCore.lock());
	if (core != NULL) {
		return linphone_core_payload_type_enabled(core->getRef(), mPayloadType) == TRUE? true: false;
	}
	return false;
}

void PayloadTypeAPI::setEnabled(bool enable) {
	FBLOG_DEBUG("PayloadTypeAPI::setEnabled()", "enable=" << enable);
	boost::shared_ptr<CoreAPI> core(mCore.lock());
	if (core != NULL) {
		linphone_core_enable_payload_type(core->getRef(), mPayloadType, enable? TRUE: FALSE);
	}
}

PayloadTypeAPI::~PayloadTypeAPI() {
	FBLOG_DEBUG("ProxyConfigAPI::~ProxyConfigAPI", this);
	mPayloadType->user_data = NULL;
}

boost::shared_ptr<PayloadTypeAPI> PayloadTypeAPI::get(const boost::shared_ptr<CoreAPI> &core, PayloadType *payloadType) {
	//void *ptr = payloadType->user_data;
	boost::shared_ptr<PayloadTypeAPI> shared_ptr;
	/*if (ptr == NULL) {*/
		shared_ptr = boost::shared_ptr<PayloadTypeAPI>(new PayloadTypeAPI(core, payloadType));
	/*} else {
		shared_ptr = boost::static_pointer_cast<PayloadTypeAPI>(reinterpret_cast<PayloadTypeAPI *>(ptr)->shared_from_this());
	}*/
	return shared_ptr;
}