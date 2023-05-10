#include "ConnectedState.hpp"
#include "NotConnectedState.hpp"
#include "SendingSmsState.hpp"

namespace {
enum { SENDING_SMS = 0, VIEW_SMS_LIST = 1, DIAL = 2 };
}

namespace ue {

ConnectedState::ConnectedState(Context& context)
    : BaseState(context, "ConnectedState") {
  context.user.acceptCallback([this] { showSmsButton(); });
  // this should show connected status
  context.user.showConnected();
}

void ConnectedState::handleDisconnected() {
  context.setState<NotConnectedState>();
}
void ConnectedState::handleSms(const Sms& sms) {
  logger.logInfo("sms: from ", sms.getFrom(), " message: ", sms.getText(),
                 " is being handled");
  context.user.showNewSmsNotification();
  context.smsDb.addReceivedSms(sms);
}

void ConnectedState::showSmsButton() {
  switch (context.user.getAction()) {
    case SENDING_SMS:
      context.setState<SendingSmsState>();
      break;
  }
}

}  // namespace ue
