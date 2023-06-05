#pragma once

#include "Messages/PhoneNumber.hpp"
namespace ue
{

class IUserEventsHandler
{
public:
    virtual ~IUserEventsHandler() = default;
    //call
    virtual void handleCallAccept() = 0;
    virtual void handleCallDrop() = 0;
    virtual void handleDialModeAction() = 0;
    virtual void handleComposeMessage() = 0;
};

class IUserPort
{
public:
    virtual ~IUserPort() = default;

    virtual void showNotConnected() = 0;
    virtual void showConnecting() = 0;
    virtual void showConnected() = 0;
    virtual void showCalling(common::PhoneNumber from) = 0;
    virtual void showTalking() = 0;
    virtual void setCallerNumber(common::PhoneNumber& number) = 0;
    virtual common::PhoneNumber getCallerNumber() = 0;
    virtual void showPartnerNotAvailable() = 0;
    virtual std::string getOutgoingMessage() = 0;
    virtual void displayMessage(std::string message) = 0;
    virtual void showCallEnded() = 0;
    virtual common::PhoneNumber getEnteredPhoneNumber() = 0;

};

}
