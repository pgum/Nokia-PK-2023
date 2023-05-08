#pragma once

#include "BaseState.hpp"

namespace ue {

class ConnectedState : public BaseState {
 public:
  ConnectedState(Context& context);
  void handleDisconnected() final;
  void handleSms(const Sms& sms) final;
  virtual void showSmsButton();
};

}  // namespace ue
