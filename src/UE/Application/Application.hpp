#pragma once

#include "Context.hpp"
#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue {

using common::ILogger;
using common::PhoneNumber;

class Application : public IEventsHandler {
public:
  Application(PhoneNumber phoneNumber, ILogger &iLogger, IBtsPort &bts,
              IUserPort &user, ITimerPort &timer);
  ~Application();

  // ITimerEventsHandler interface
  void handleTimeout() override;

  // IBtsEventsHandler interface
  void handleDisconnected() override;
  void handleSib(common::BtsId btsId) override;
  void handleAttachAccept() override;
  void handleAttachReject() override;
  void handleCallRequest(common::PhoneNumber requestNum) override;
  void handleCallAccepted(common::PhoneNumber anwserNum) override;
  void handleCallReject(common::PhoneNumber anwserNum) override;

private:
  Context context;
  common::PrefixedLogger logger;
};

} // namespace ue
