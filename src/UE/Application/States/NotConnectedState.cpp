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
        context.bts.sendAttachRequest(btsId);
        context.user.showConnecting();
        context.timer.startTimer(Duration(500));
        context.setState<ConnectingState>();
    }
}
