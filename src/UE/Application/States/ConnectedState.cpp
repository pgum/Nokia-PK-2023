#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"

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

}
