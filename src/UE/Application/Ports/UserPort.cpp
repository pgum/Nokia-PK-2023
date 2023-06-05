#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ICallMode.hpp"
#include "UeGui/ITextMode.hpp"

namespace ue
{

UserPort::UserPort(common::ILogger &logger, IUeGui &gui, common::PhoneNumber phoneNumber)
    : logger(logger, "[USER-PORT]"),
      gui(gui),
      phoneNumber(phoneNumber)
{}

void UserPort::start(IUserEventsHandler &handler)
{
    this->handler = &handler;

    gui.setAcceptCallback([this]{this->handler->handleCallAccept();});
    gui.setRejectCallback([this]{this->handler->handleCallDrop();});
    gui.setDialModeActionCallback([this]{this->handler->handleDialModeAction();});
    gui.setSmsComposeCallback([this]{this->handler->handleComposeMessage();}); //-> ustaw zamiast tego odpowiedni callback
    gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop()
{
    handler = nullptr;
}

common::PhoneNumber UserPort::getCallerNumber()
{
    return callerNumber;
}

void UserPort::setCallerNumber(common::PhoneNumber& number)
{
    callerNumber = number;
}

void UserPort::showNotConnected()
{
    gui.showNotConnected();
}

void UserPort::showConnecting()
{
    gui.showConnecting();
}

void UserPort::showConnected()
{
    IUeGui::IListViewMode& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    menu.addSelectionListItem("Call", "");
}

void UserPort::showCalling(common::PhoneNumber from)
{
    IUeGui::ITextMode& textMode = gui.setViewTextMode();
    textMode.setText("Calling: " + common::to_string(from));
}

void UserPort::showTalking()
{
    IUeGui::ICallMode& callView = gui.setCallMode();
}

void UserPort::showPartnerNotAvailable()
{
   gui.showNotAvailable();
}

std::string UserPort::getOutgoingMessage()
{
    IUeGui::ICallMode& callView = gui.setCallMode();
    std::string msg = callView.getOutgoingText();
    callView.clearOutgoingText();

    return msg;
}

void UserPort::displayMessage(std::string message)
{
    logger.logInfo("Recieved message: " + message);
    IUeGui::ICallMode& callView = gui.setCallMode();

    callView.appendIncomingText(message);
}
void UserPort::showCallEnded()
{
    //TODO: if possible, display some dialog, informing that call has ended before going back to menu
    showConnected();
}

PhoneNumber UserPort::getEnteredPhoneNumber()
{
    return gui.getPhoneNumber();
}

}
