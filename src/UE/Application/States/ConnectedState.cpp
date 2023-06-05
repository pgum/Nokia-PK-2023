#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "ReceivingState.hpp"
#include "TalkingState.hpp"
#include "SendingsSate.cpp"
#include "Sms.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{

}

ConnectedState::ConnectedState(Context &context, const std::string& name)
    : BaseState(context, name)
{

}

void ConnectedState::handleBTSDisconnected()
{
    context.user.showNotConnected();
    context.setState<NotConnectedState>();
}

void ConnectedState::handleCallRequest(common::PhoneNumber from)
{
    const short reaction_time_ms = 30000;

    context.user.setCallerNumber(from);
    context.user.showCalling(from);
    context.timer.startTimer(ITimerPort::Duration(reaction_time_ms));
    context.setState<ReceivingState>();
}

void ConnectedState::handleDialModeAction()
{
    context.setState<SendingState>();
}

void ConnectedState::handleSms(const Sms& sms)
{
    context.user.showNewSmsNotification();
    context.smsDb.addMessage(sms);
}

void ConnectedState::handleShowSmsList()
{
    const auto& smsMessages = context.smsDb.getAllMessages();
    context.user.viewSmsList(smsMessages);
}

void ConnectedState::handleShowSms(IUeGui::IListViewMode::Selection indexOfSms)
{
    const auto& retrievedSms = context.smsDb.getMessage(indexOfSms);

    if (retrievedSms.state == SmsState::NotViewed)
    {
        context.smsDb.setMessageState(indexOfSms, SmsState::Viewed);
    }

    context.user.viewSms(retrievedSms);
}

void ConnectedState::handleComposeSms()
{
    context.user.showNewSmsToEdit();
}

void ConnectedState::handleSendSms(const Sms& sms)
{
    context.smsDb.addMessage(sms);
    context.bts.sendSms(sms);
    context.user.showConnected();
}

void ConnectedState::handleSmsDrop()
{
    context.user.showConnected();
}

} // namespace ue
