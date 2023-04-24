#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue {

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger &iLogger, IBtsPort &bts,
                         IUserPort &user, ITimerPort &timer)
    : context{iLogger, bts, user, timer}, logger(iLogger, "[APP] ") {
  logger.logInfo("Started");
  context.setState<NotConnectedState>();
}

Application::~Application() { logger.logInfo("Stopped"); }

void Application::handleTimeout() { context.state->handleTimeout(); }

void Application::handleDisconnected() { context.state->handleDisconnected(); }

void Application::handleSib(common::BtsId btsId) {
  context.state->handleSib(btsId);
}

void Application::handleAttachAccept() { context.state->handleAttachAccept(); }

void Application::handleAttachReject() { context.state->handleAttachReject(); }

void Application::handleCallRequest(common::PhoneNumber requestNum) {
  context.state->handleCallRequest(requestNum);
}

void Application::handleCallAccepted(common::PhoneNumber anwserNum) {
  context.state->handleCallAccepted(anwserNum);
}

void Application::handleCallReject(common::PhoneNumber anwserNum) {
  context.state->handleCallReject(anwserNum);
}

} // namespace ue
