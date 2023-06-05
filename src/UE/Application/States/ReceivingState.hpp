#pragma once

#include "CallState.hpp"

namespace ue
{

class ReceivingState : public CallState
{
public:
    ReceivingState(Context& context);
    void handleTimeout() override;
    void handleCallAccept() override;
    void handleCallDrop() override;
    void handleBTSCallDrop(common::PhoneNumber from) override;
};

}
