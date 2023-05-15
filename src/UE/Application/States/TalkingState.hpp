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
    void handleSendTalkMessage(common::PhoneNumber destNumber, std::string message) override;
};
}
