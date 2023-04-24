#pragma once

#include "Context.hpp"
#include "IEventsHandler.hpp"
#include "Logger/PrefixedLogger.hpp"

namespace ue {

class BaseState : public IEventsHandler {
public:
  BaseState(Context &context, const std::string &name);
  ~BaseState() override;

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

protected:
  Context &context;
  common::PrefixedLogger logger;
};

} // namespace ue
