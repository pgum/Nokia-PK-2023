#include "Application.hpp"
#include "States/NotConnectedState.hpp"

namespace ue
{

Application::Application(common::PhoneNumber phoneNumber,
                         common::ILogger &iLogger,
                         IBtsPort &bts,
                         IUserPort &user,
                         ITimerPort &timer)
    : context{iLogger, bts, user, timer},
      logger(iLogger, "[APP] ")
{
    logger.logInfo("Started");
    context.setState<NotConnectedState>();
}

Application::~Application()
{
    logger.logInfo("Stopped");
}

void Application::handleTimeout()
{
    context.state->handleTimeout();
}

void Application::handleSib(common::BtsId btsId)
{
    context.state->handleSib(btsId);
}

void Application::handleAttachAccept()
{
    context.state->handleAttachAccept();
}

void Application::handleAttachReject()
{
    context.state->handleAttachReject();
}

void Application::handleBTSDisconnected()
{
    context.state->handleBTSDisconnected();
}

void Application::handleCallRequest(common::PhoneNumber from)
{
    context.state->handleCallRequest(from);
}

void Application::handleCallAccept()
{
    context.state->handleCallAccept();
}

void Application::handleCallDrop()
{
    context.state->handleCallDrop();
}

void Application::handleUnknownRecipient()
{
    context.state->handleUnknownRecipient();
}
}
