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
    using Duration = std::chrono::milliseconds;
    Duration timeForBtsResponse = Duration(500);

    context.bts.sendAttachRequest(btsId);
    context.user.showConnecting();
    context.timer.startTimer(timeForBtsResponse);
    context.setState<ConnectingState>();
}
}
