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

void BaseState::handleCallRequest(common::PhoneNumber from)
{
    logger.logError("Unexcepted: handleCallRequest");
}

void BaseState::handleCallAccept()
{
    logger.logError("Unexcepted: handleCallAccept");

}

void BaseState::handleCallDrop()
{
    logger.logError("Unexcepted: handleCallDrop");
}

void BaseState::handleUnknownRecipient()
{
    logger.logError("Unexcepted: handleUnknownRecipient");
}

void BaseState::handleRecieveTalkMessage(std::string message)
{
    logger.logError("Unexcepted: handleRecieveCallMessage()");
}

void BaseState::handleSendTalkMessage(common::PhoneNumber destNumber, std::string message)
{
    logger.logError("Unexcepted: handleSendCallMessage()");
}

void BaseState::handleBTSCallDrop(common::PhoneNumber number)
{
    logger.logError("Unexcepted: handleDialModeAction()");
}

void BaseState::handleBTSCallAccept(common::PhoneNumber number)
{
    logger.logError("Unexcepted: handleBTSCallAccept()");
}

void BaseState::handleBTSCallDrop(common::PhoneNumber number)
{
    logger.logError("Unexcepted: handleBTSCallDrop()");
}

void BaseState::handleDialModeAction()
{
    logger.logError("Unexcepted: handleDialModeAction()");
}

void BaseState::handleBTSCallAccept(common::PhoneNumber number)
{
    logger.logError("Unexcepted: handleBTSCallAccept()");
}


}
