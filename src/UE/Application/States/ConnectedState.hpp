#pragma once

#include "BaseState.hpp"

namespace ue
{

class ConnectedState : public BaseState
{
public:
    ConnectedState(Context& context);

    void handleBTSDisconnected() override;
    void handleSms(const Sms& sms) final;
    void handleComposeSms() final;
    void handleSendSms() final;
    void handleShowSmsList() final;
    void handleShowSms(std::size_t) final;
};

}