#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ISmsComposeMode.hpp"
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
    gui.setTitle("Nokia " + to_string(phoneNumber));
}

void UserPort::stop()
{
    handler = nullptr;
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
    menu.addSelectionListItem("Send SMS", "");
    gui.setAcceptCallback([this, &menu]
    {
        switch (menu.getCurrentItemIndex().second) {
            case 0:
                break;
            case 1:
                handler->handleShowSmsList();
                break;
        }
    });
}

void UserPort::showNewSmsNotification()
{
    gui.showNewSms(true);
}

void UserPort::showNewSmsToEdit()
{
    mode = &gui.setSmsComposeMode();
    gui.setAcceptCallback([this]{
        handler->handleSendSms();
    });
}

std::pair<common::PhoneNumber, std::string> UserPort::getSms()
{
    auto phoneNum = mode->getPhoneNumber();
    auto smsText = mode->getSmsText();
    mode->clearSmsText();
    return std::make_pair(phoneNum, smsText);
}

void UserPort::viewSmsList(const std::vector<std::pair<Sms, smsState>>& smsList)
{
    auto& menu = gui.setListViewMode();
    menu.clearSelectionList();
    for(const auto& sms : smsList){
        std::string label =
            sms.second == smsState::Viewed ? to_string(sms.first.from)
                            : "[New] " +to_string(sms.first.from);
        menu.addSelectionListItem(label, "");
    }
    gui.setAcceptCallback([this, &menu]
    {
        const auto idx = menu.getCurrentItemIndex().second;
        handler->handleShowSms(idx);
    });

    gui.setRejectCallback([this]
    {
        showConnected();
    });
}

void UserPort::viewSms(const Sms& sms)
{
    auto& display = gui.setViewTextMode();

    display.setText(sms.text);

    gui.setRejectCallback([this]
    {
        handler->handleShowSmsList();
    });
}

} // namespace ue
