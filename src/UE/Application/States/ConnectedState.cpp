#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState") {}

void ConnectedState::handleBTSDisconnected()
{
    context.user.showNotConnected();
    context.setState<NotConnectedState>();
}

void ConnectedState::handleSms(const Sms& sms)
{
    context.user.showNewSmsNotification();
    context.smsDb.addReceivedSms(sms);
}

void ConnectedState::handleComposeSms()
{
    context.user.showNewSmsToEdit();
}

void ConnectedState::handleSendSms()
{
    constexpr common::PhoneNumber rcvNum { 112 };
    const std::string text = "text message here";

    context.smsDb.addSms(rcvNum, text);
    context.bts.sendSms(rcvNum, text);
    context.user.showConnected();
}

} // namespace ue
