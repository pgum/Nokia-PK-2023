#include "UserPort.hpp"
#include "UeGui/IListViewMode.hpp"
#include "UeGui/ICallMode.hpp"
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
    auto& menu = gui.setListViewMode();
    menu.clearSelectionList();
    menu.addSelectionListItem("Compose SMS", "");
    menu.addSelectionListItem("View SMS", "");
    menu.addSelectionListItem("Call", "");

    gui.setAcceptCallback([this, &menu] {
        const auto [isSelected, index] = menu.getCurrentItemIndex();

        if (isSelected)
        {
            switch (index)
            {
            case 0:
                handler->handleComposeSms();
                break;
            case 1:
                handler->handleShowSmsList();
                break;
            default:
                break;
            }
        }
    });

    gui.setRejectCallback([] {});
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

void UserPort::showNewSmsNotification()
{
    gui.showNewSms(true);
}

void UserPort::showNewSmsToEdit()
{
    auto& mode = gui.setSmsComposeMode();
    gui.setAcceptCallback([this, &mode] {
        auto phoneNum = mode.getPhoneNumber();
        if(phoneNum.isValid()){
            auto smsText = mode.getSmsText();
            mode.clearSmsText();
            handler->handleSendSms(Sms{phoneNum, smsText, SmsState::Sent});
        }
    });

    gui.setRejectCallback([this, &mode] {
        mode.clearSmsText();
        handler->handleSmsDrop();
    });
}

std::string makeSmsLabel(const Sms& sms)
{
    std::stringstream ss;

    switch (sms.state)
    {
    case SmsState::NotViewed:
        ss << "[New][From]: ";
        break;
    case SmsState::Viewed:
        ss << "[From]: ";
        break;
    case SmsState::Sent:
        ss << "[To]: ";
        break;
    case SmsState::Failed:
        ss << "[Failed][To]: ";
        break;
    }

    ss << static_cast<int>(sms.from.value);
    return ss.str();
}

void UserPort::viewSmsList(const std::vector<Sms>& smsList)
{
    auto& menu = gui.setListViewMode();
    menu.clearSelectionList();

    for (const auto& sms : smsList)
    {
        menu.addSelectionListItem(makeSmsLabel(sms), "");
    }

    gui.setAcceptCallback([this, &menu] {
        const auto [isSelected, index] = menu.getCurrentItemIndex();

        if (isSelected)
        {
            handler->handleShowSms(index);
        }
    });

    gui.setRejectCallback([this] {
        showConnected();
    });
}

void UserPort::viewSms(const Sms& sms)
{
    auto& mode = gui.setViewTextMode();
    mode.setText(sms.text);

    gui.setAcceptCallback([] {});

    gui.setRejectCallback([this, &mode] {
        mode.setText("");
        handler->handleShowSmsList();
    });
}

} // namespace ue
