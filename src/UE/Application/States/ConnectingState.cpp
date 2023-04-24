#include "ConnectingState.hpp"
#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

namespace ue
{

ConnectingState::ConnectingState(Context &context)
    : BaseState(context, "ConnectingState")
{
}
    void ConnectingState::handleAttachAccept()
    {
        context.user.showConnected();
        context.timer.stopTimer();
        context.setState<ConnectedState>();
    }

    void ConnectingState::handleAttachReject()
    {
        context.user.showNotConnected();
        context.timer.stopTimer();
        context.setState<NotConnectedState>();
    }

    void ConnectingState::handleTimeout()
    {
        context.user.showNotConnected();
        context.setState<NotConnectedState>();
    }

    void ConnectingState::handleBTSDisconnected()
    {
        context.timer.stopTimer();
        context.user.showNotConnected();
        context.setState<NotConnectedState>();
    }

}
