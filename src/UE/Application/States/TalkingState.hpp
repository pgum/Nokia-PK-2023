#pragma once

#include <thread>

#include "BaseState.hpp"

namespace ue
{
class TalkingState : public BaseState
{
public:
    TalkingState(Context& context);
    void handleUnknownRecipient() override;
};
}
