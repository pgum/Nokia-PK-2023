#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "TalkingState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{

}

void ConnectedState::handleBTSDisconnected()
{
    context.user.showNotConnected();
    context.setState<NotConnectedState>();
}

void ConnectedState::handleCallRequest(common::PhoneNumber from)
{
    context.user.setReceivingCall(true);
    using Duration = std::chrono::seconds;
    Duration timeToReact = Duration(30);

    context.user.setCallerNumber(from);

    context.user.showCalling(from);
    context.timer.startTimer(timeToReact);
}

void ConnectedState::handleCallAccept()
{
    if(context.user.isReceivingCall())
    {
        using Duration = std::chrono::seconds;
        Duration uknownRecipientRecTime = Duration(15);

        context.bts.sendCallAccept(context.user.getCallerNumber());
        context.user.showTalking();
        context.timer.stopTimer();
        context.timer.startTimer(uknownRecipientRecTime);
        context.user.setReceivingCall(false);
        context.setState<TalkingState>();
    }
}

void ConnectedState::handleCallDrop()
{
    if(context.user.isReceivingCall())
    {
        context.timer.stopTimer();
        context.bts.sendCallReject(context.user.getCallerNumber());
        context.user.showConnected();
        context.user.setReceivingCall(false);
    }
}

void ConnectedState::handleTimeout()
{
    context.bts.sendCallReject(context.user.getCallerNumber());
    context.user.showConnected();
}

}
