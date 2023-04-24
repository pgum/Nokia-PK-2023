#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"

namespace ue {

UserPort::UserPort(common::ILogger &logger, IUeGui &gui,
                   common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"), gui(gui), phoneNumber(phoneNumber) {}

void UserPort::start(IUserEventsHandler &handler) {
  this->handler = &handler;
  gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop() { handler = nullptr; }

void UserPort::showNotConnected() { gui.showNotConnected(); }

void UserPort::showConnecting() { gui.showConnecting(); }

void UserPort::showConnected() {
  IUeGui::IListViewMode &menu = gui.setListViewMode();
  menu.clearSelectionList();
  menu.addSelectionListItem("Compose SMS", "");
  menu.addSelectionListItem("View SMS", "");
}

void UserPort::showCallRequest(common::PhoneNumber requestNum) {
  auto &mode = gui.setAlertMode();
  mode.setText("Call from number:" + std::to_string(requestNum.value));

  gui.setAcceptCallback(
      [this, requestNum] { handler->handleCallAccept(requestNum); });

  gui.setRejectCallback([this] {
    // todo
  });
}

void UserPort::showTalking() {
  auto &callMode = gui.setCallMode();
  // todo
}
} // namespace ue
