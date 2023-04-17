#include "BaseState.hpp"
#include "Sms.hpp"

namespace ue {

BaseState::BaseState(Context& context, const std::string& name)
    : context(context), logger(context.logger, "[" + name + "]") {
  logger.logDebug("entry");
}

BaseState::~BaseState() {
  logger.logDebug("exit");
}

void BaseState::handleTimeout() {
  logger.logError("Unexpected: handleTimeout");
}

void BaseState::handleSib(common::BtsId btsId) {
  logger.logError("Unexpected: handleSib: ", btsId);
}

void BaseState::handleAttachAccept() {
  logger.logError("Unexpected: handleAttachAccept");
}

void BaseState::handleAttachReject() {
  logger.logError("Unexpected: handleAttachReject");
}

void BaseState::handleDisconnected() {
  logger.logError("Uexpected: handleDisconnected");
}
void BaseState::handleSms(const Sms& sms) {
  logger.logError("Uexpected: handleSms");
}

}  // namespace ue
