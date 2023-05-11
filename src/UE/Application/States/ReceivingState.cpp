#include "ReceivingState.hpp"
#include "TalkingState.hpp"

namespace ue
{
ReceivingState::ReceivingState(Context &context) : CallState(context, "ReceivingState")
{

}

void ReceivingState::handleCallAccept()
{
    long uknownRecipientReactTime = 15000;

    context.bts.sendCallAccept(context.user.getCallerNumber());
    context.user.showTalking();
    context.timer.stopTimer();
    context.timer.startTimer(ITimerPort::Duration(uknownRecipientReactTime));
    context.setState<TalkingState>();
}

void ReceivingState::handleCallDrop()
{
    context.timer.stopTimer();
    context.bts.sendCallReject(context.user.getCallerNumber());
    context.user.showConnected();
    context.setState<ConnectedState>();
}

void ReceivingState::handleTimeout()
{
    context.bts.sendCallReject(context.user.getCallerNumber());
    context.user.showConnected();
    context.setState<ConnectedState>();
}

}
