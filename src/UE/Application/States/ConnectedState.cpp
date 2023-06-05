#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "ReceivingState.hpp"
#include "SendingState.hpp"
#include "TalkingState.hpp"

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

}
