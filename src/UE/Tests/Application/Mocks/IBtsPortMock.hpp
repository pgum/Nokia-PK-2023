#pragma once

#include <gmock/gmock.h>
#include "Ports/IBtsPort.hpp"
#include "ITransport.hpp"

namespace ue
{

class IBtsEventsHandlerMock : public IBtsEventsHandler
{
public:
    IBtsEventsHandlerMock();
    ~IBtsEventsHandlerMock() override;

    MOCK_METHOD(void, handleSib, (common::BtsId), (final));
    MOCK_METHOD(void, handleAttachAccept, (), (final));
    MOCK_METHOD(void, handleAttachReject, (), (final));
    MOCK_METHOD(void, handleBTSDisconnected, (), (final));    
    MOCK_METHOD(void, handleCallRequest, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleUnknownRecipient, (), (final));
    MOCK_METHOD(void, handleRecieveTalkMessage, (std::string), (final));
    MOCK_METHOD(void, handleSendTalkMessage, (common::PhoneNumber, std::string), (final));
    MOCK_METHOD(void, handleBTSCallAccept, (common::PhoneNumber), (final));
    MOCK_METHOD(void, handleBTSCallDrop, (common::PhoneNumber), (final));
};

class IBtsPortMock : public IBtsPort
{
public:
    IBtsPortMock();
    ~IBtsPortMock() override;

    MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
    MOCK_METHOD(void, sendCallAccept,  (common::PhoneNumber), (final));
    MOCK_METHOD(void, sendCallReject,  (common::PhoneNumber), (final));
    MOCK_METHOD(void, callTalk, (common::PhoneNumber, std::string), (final));
    MOCK_METHOD(void, callDrop, (common::PhoneNumber), (final));
    MOCK_METHOD(void, sendCallRequest,  (common::PhoneNumber), (final));
};

}
