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
    textMode.setText(common::to_string(from));
}

void UserPort::showTalking()
{
    IUeGui::ICallMode& callView = gui.setCallMode();
}

void UserPort::showPartnerNotAvailable()
{
    IUeGui::ITextMode& textMode = gui.setViewTextMode();
    textMode.setText(common::to_string(getCallerNumber()) + " is currently not available.");
}

}
