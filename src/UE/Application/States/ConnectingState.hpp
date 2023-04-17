#pragma once

#include "BaseState.hpp"

namespace ue {

class ConnectingState : public BaseState {
 public:
  ConnectingState(Context& context);

  void handleTimeout() override;
  void handleAttachAccept() override;
  void handleAttachReject() override;
};

}  // namespace ue
