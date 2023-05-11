#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);
    ConnectedState(Context& context, const std::string& name);
    void handleBTSDisconnected() override;
    void handleCallRequest(common::PhoneNumber from) override;
};

}
