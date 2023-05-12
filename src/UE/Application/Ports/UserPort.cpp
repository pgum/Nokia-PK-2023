#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
#include "UeGui/ITextMode.hpp"

namespace ue {

UserPort::UserPort(common::ILogger& logger,
                   IUeGui& gui,
                   common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"), gui(gui), phoneNumber(phoneNumber) {}

void UserPort::start(IUserEventsHandler& handler) {
  this->handler = &handler;
  gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop() {
  handler = nullptr;
}

void UserPort::showNotConnected() {
  gui.showNotConnected();
}

void UserPort::showConnecting() {
  gui.showConnecting();
}

void UserPort::showConnected() {
  IUeGui::IListViewMode& menu = gui.setListViewMode();
  menu.clearSelectionList();
  menu.addSelectionListItem("Compose SMS", "");
  if (smsDb.isUnreadSms()) {
    menu.addSelectionListItem("View SMS (New!)", "");
  } else {
    menu.addSelectionListItem("View SMS", "");
  }

  gui.setAcceptCallback([this, &menu] { onAcceptCallback(menu); });
}

void UserPort::showNewSmsNotification() {
  gui.showNewSms(true);
}

IUeGui::ISmsComposeMode& UserPort::composeSms() {
  IUeGui::ISmsComposeMode& smsComposer = gui.setSmsComposeMode();
  smsComposer.clearSmsText();
  smsComposer.getPhoneNumber();
  smsComposer.getSmsText();

  return smsComposer;
}

void UserPort::showSms(size_t index) {
  auto sms = smsDb.retrieveSms(index);
  IUeGui::ITextMode& textMode = gui.setViewTextMode();
  if (sms) {
    textMode.setText(sms.get()->getText());
  }
}

void UserPort::showSmsList() {
  gui.showNewSms(false);
  IUeGui::IListViewMode& listMode = gui.setListViewMode();
  listMode.clearSelectionList();
  for (const auto& sms : smsDb.getSmsMessages()) {
    std::string header = "from " + common::to_string(sms.first.getFrom()) +
                         " to " + common::to_string(sms.first.getTo());
    if (!sms.first.isReceived()) {
      header = "Fail! " + header;
    }
    listMode.addSelectionListItem(header, "");
  }
  gui.setAcceptCallback([this, &listMode] { onAcceptCallback(listMode); });
}

SmsDb& UserPort::getSmsDb() {
  return smsDb;
}

int UserPort::getAction() {
  return action;
}

void UserPort::acceptCallback(IUeGui::Callback acceptCallback) {
  this->callback = acceptCallback;
  gui.setAcceptCallback(acceptCallback);
}

void UserPort::onAcceptCallback(IUeGui::IListViewMode& menu) {
  IUeGui::IListViewMode::OptionalSelection pair = menu.getCurrentItemIndex();
  if (!pair.first) {
    action = -1;
  } else {
    action = pair.second;
  }
  callback();
}

void UserPort::rejectCallback(IUeGui::Callback rejectCallback) {
  gui.setRejectCallback(rejectCallback);
}

}  // namespace ue
