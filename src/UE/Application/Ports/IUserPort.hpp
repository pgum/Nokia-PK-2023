#pragma once

#include "IUeGui.hpp"
#include "SmsDb.hpp"

namespace ue {

class IUserEventsHandler {
 public:
  virtual ~IUserEventsHandler() = default;
};

class IUserPort {
 public:
  virtual ~IUserPort() = default;

  virtual void showNotConnected() = 0;
  virtual void showConnecting() = 0;
  virtual void showConnected() = 0;
  virtual IUeGui::ISmsComposeMode& composeSms() = 0;
  virtual void showNewSmsNotification() = 0;
  virtual void showSmsList() = 0;
  virtual void showSms(size_t index) = 0;
  virtual SmsDb& getSmsDb() = 0;
  virtual int getAction() = 0;
  virtual void acceptCallback(IUeGui::Callback acceptCallback) = 0;
  virtual void rejectCallback(IUeGui::Callback rejectCallback) = 0;
};

}  // namespace ue
