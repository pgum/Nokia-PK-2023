#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "Sms.hpp"

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
