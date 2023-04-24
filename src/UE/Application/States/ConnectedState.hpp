#pragma once

#include "BaseState.hpp"

namespace ue {

class ConnectedState : public BaseState {
public:
  ConnectedState(Context &context);
  void handleDisconnected() final;
  void handleCallRequest(common::PhoneNumber requestNum) final;

  void handleCallAccepted(common::PhoneNumber answerNum) final;
  void handleCallReject(common::PhoneNumber answerNum) final;
};

} // namespace ue
