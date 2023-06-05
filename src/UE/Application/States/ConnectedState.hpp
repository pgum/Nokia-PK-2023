#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);

    void handleBTSDisconnected() override;
    void handleSms(const Sms& sms) override;
};

}
