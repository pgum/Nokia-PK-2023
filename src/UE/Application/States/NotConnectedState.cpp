#include "NotConnectedState.hpp"
#include "ConnectingState.hpp"

namespace ue
{

NotConnectedState::NotConnectedState(Context &context)
    : BaseState(context, "NotConnectedState")
{

}
void NotConnectedState::handleSib(common::BtsId btsId)
{
    const long bts_response_time_ms = 500;

    context.bts.sendAttachRequest(btsId);
    context.user.showConnecting();
    context.timer.startTimer(ITimerPort::Duration(bts_response_time_ms));
    context.setState<ConnectingState>();
}
}
