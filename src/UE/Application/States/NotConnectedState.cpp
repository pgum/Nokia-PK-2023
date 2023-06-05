#include "NotConnectedState.hpp"
#include "ConnectingState.hpp"

namespace ue
{

NotConnectedState::NotConnectedState(Context &context)
    : BaseState(context, "NotConnectedState")
{

}

NotConnectedState::NotConnectedState(Context &context, const std::string &name)
    : BaseState(context, name)
{

}

void NotConnectedState::handleSib(common::BtsId btsId)
{
    constexpr long bts_response_time_ms = 500;
    ITimerPort::Duration timerDuration = ITimerPort::Duration(bts_response_time_ms);

    context.bts.sendAttachRequest(btsId);
    context.user.showConnecting();
    context.timer.startTimer(timerDuration);
    context.setState<ConnectingState>();
}

}
