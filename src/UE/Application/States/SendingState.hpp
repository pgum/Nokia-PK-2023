#pragma once

#include "CallState.hpp"

namespace ue
{
class SendingState :  public CallState
{
public:
    SendingState(Context& context);
    void handleCallAccept() override;
    void handleBTSCallAccept(common::PhoneNumber number) override;
    void handleBTSCallDrop(common::PhoneNumber number) override;
    void handleUnknownRecipient();
    void handleTimeout()override;
    void handleCallDrop()override;

};

}
