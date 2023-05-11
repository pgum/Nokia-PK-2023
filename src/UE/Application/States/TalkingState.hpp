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
};
}
