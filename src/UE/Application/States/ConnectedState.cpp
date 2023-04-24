#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "TalkingState.hpp"
namespace ue {

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState") {
  // this should show connected status
  context.user.showConnected();
}

void ConnectedState::handleDisconnected() {
  context.setState<NotConnectedState>();
}

void ConnectedState::handleCallRequest(common::PhoneNumber requestNum) {
  using namespace std::chrono_literals;
  context.user.showCallRequest(requestNum);
  context.timer.startTimer(30s);
}

void ConnectedState::handleCallAccepted(common::PhoneNumber anwserNum) {
  context.bts.sendAcceptCall(anwserNum);
  context.user.showTalking();
  context.timer.stopTimer();
  context.setState<TalkingState>();
}

void ConnectedState::handleCallReject(common::PhoneNumber anwserNum) {
  // to do
  logger.logError("Here handleCallReject for number:", anwserNum);
}
} // namespace ue
