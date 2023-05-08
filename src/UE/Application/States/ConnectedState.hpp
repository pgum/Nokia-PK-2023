#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    void handleBTSDisconnected() override;
    void handleCallRequest(common::PhoneNumber from) override;
    void handleCallAccept() override;
    void handleCallDrop() override;
    void handleTimeout() override;
};

}
