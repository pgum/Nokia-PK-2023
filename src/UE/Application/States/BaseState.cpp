#include "BaseState.hpp"

namespace ue
{

BaseState::BaseState(Context &context, const std::string &name)
    : context(context),
      logger(context.logger, "[" + name + "]")
{
    logger.logDebug("entry");
}

BaseState::~BaseState()
{
    logger.logDebug("exit");
}

void BaseState::handleTimeout()
{
    logger.logError("Uexpected: handleTimeout");
}

void BaseState::handleSib(common::BtsId btsId)
{
    logger.logError("Uexpected: handleSib: ", btsId);
}

void BaseState::handleAttachAccept()
{
    logger.logError("Uexpected: handleAttachAccept");
}

void BaseState::handleAttachReject()
{
    logger.logError("Uexpected: handleAttachReject");
}
  
void BaseState::handleBTSDisconnected()
{
    logger.logError("Uexpected: handleBTSDisconnected");
}

void BaseState::handleSms(const Sms& sms)
{
    logger.logError("Uexpected: handleSms");
}

void BaseState::handleComposeSms()
{
    logger.logError("Unexpected: handleComposeSms");
}

void BaseState::handleSendSms()
{
    logger.logError("Unexpected: handleSendSms");
}

void BaseState::handleShowSmsList()
{
    logger.logError("Unexpected: handleShowSmsList");
}

} // namespace ue
