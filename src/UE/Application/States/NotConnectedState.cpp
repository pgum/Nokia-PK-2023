#include "NotConnectedState.hpp"
#include "ConnectingState.hpp"


namespace ue
{

NotConnectedState::NotConnectedState(Context &context)
    : BaseState(context, "NotConnectedState")
{
    context.user.showNotConnected();
}

void NotConnectedState::handleSib(common::BtsId btsId)
{
    logger.logDebug("SIB: ", btsId);

    using namespace std::chrono_literals;
    context.bts.sendAttachRequest(btsId);
    context.timer.startTimer(500ms);

    context.setState<ConnectingState>();
}

}
