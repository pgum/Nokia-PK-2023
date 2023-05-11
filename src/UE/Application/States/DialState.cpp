#include "DialState.hpp"
#include "ConnectedState.hpp"
#include "IUeGui.hpp"
#include "TalkingState.hpp"

namespace ue {
DialState::DialState(Context& context, IUeGui::IDialMode& iDialMode)
    : ConnectedState(context), iDialMode(iDialMode) {}
// TODO idialmode argument fix

void DialState::acceptButton() {
  // context.setState<TalkingState>(iDialMode.getPhoneNumber());
}

void DialState::rejectButton() {
  context.setState<ConnectedState>();
}
}  // namespace ue
