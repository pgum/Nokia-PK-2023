#pragma once

#include <thread>

#include "CallState.hpp"

namespace ue
{
class TalkingState : public CallState
{
public:
    TalkingState(Context& context);
    void handleUnknownRecipient() override;
    void handleRecieveTalkMessage(std::string message) override;
    void handleComposeMessage() override;
    void handleCallDrop() override;
    void handleBTSCallDrop(common::PhoneNumber) override;
};
}
