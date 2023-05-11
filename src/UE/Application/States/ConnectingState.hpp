#pragma once

#include "NotConnectedState.hpp"

namespace ue
{

class ConnectingState : public NotConnectedState
{
public:
    ConnectingState(Context& context);
    void handleAttachAccept() override;
    void handleAttachReject() override;
    void handleTimeout() override;
    void handleBTSDisconnected() override;
};

}
