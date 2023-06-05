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
    auto [rcvNum, text] = context.user.getSms();
    context.smsDb.addSms(rcvNum, text);
    context.bts.sendSms(rcvNum, text);
    context.user.showConnected();
}

void ConnectedState::handleShowSmsList()
{
    const auto& smsMessages = context.smsDb.getSmsMessages();
    context.user.viewSmsList(smsMessages);
}

void ConnectedState::handleShowSms(std::size_t idx)
{
    context.smsDb.updateSmsState(idx);
    const auto& retrivedSms = context.smsDb.getSms(idx);
    context.user.viewSms(retrivedSms);
}

} // namespace ue
