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
    void handleDialModeAction() override;
    
    void handleSms(const Sms& sms) final;
    void handleShowSmsList() final;
    void handleShowSms(IUeGui::IListViewMode::Selection) final;
    void handleSmsDrop() final;

    void handleComposeSms() final;
    void handleSendSms(const Sms& sms) final;
};

}