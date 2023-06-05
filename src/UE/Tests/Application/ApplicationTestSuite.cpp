#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Application.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Mocks/ITimerPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Mocks/ISmsDbMock.hpp"
#include "Sms.hpp"
#include <memory>

namespace ue
{

using namespace ::testing;

class ApplicationTestSuite : public Test
{
protected:
    static constexpr common::PhoneNumber PHONE_NUMBER{ 112 };
    static constexpr common::BtsId btsId{ 333 };

    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IBtsPortMock> btsPortMock;
    StrictMock<IUserPortMock> userPortMock;
    StrictMock<ITimerPortMock> timerPortMock;
    StrictMock<ISmsDbMock> smsDbMock;

    Application objectUnderTest{PHONE_NUMBER,
                                loggerMock,
                                btsPortMock,
                                userPortMock,
                                timerPortMock,
                                smsDbMock };
};

struct ApplicationNotConnectedTestSuite : ApplicationTestSuite
{
    void sendAttachRequestOnSib();
};

void ApplicationNotConnectedTestSuite::sendAttachRequestOnSib()
{
    constexpr long bts_response_time_ms = 500;

    ITimerPort::Duration timerDuration =
        ITimerPort::Duration(bts_response_time_ms);

    EXPECT_CALL(btsPortMock, sendAttachRequest(btsId));
    EXPECT_CALL(userPortMock, showConnecting());
    EXPECT_CALL(timerPortMock, startTimer(timerDuration));
    objectUnderTest.handleSib(btsId);
}

TEST_F(ApplicationNotConnectedTestSuite, shallSendAttachRequestOnSib)
{
    sendAttachRequestOnSib();
}

struct ApplicationConnectingTestSuite : ApplicationNotConnectedTestSuite
{
    ApplicationConnectingTestSuite();
    void connectOnAttachAccept();
};

void ApplicationConnectingTestSuite::connectOnAttachAccept()
{
    EXPECT_CALL(userPortMock, showConnected());
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleAttachAccept();
}

ApplicationConnectingTestSuite::ApplicationConnectingTestSuite()
{
    sendAttachRequestOnSib();
}

TEST_F(ApplicationConnectingTestSuite, shallConnectOnAttachAccept)
{
    connectOnAttachAccept();
}

TEST_F(ApplicationConnectingTestSuite, shallNotConnectOnConnectionDrop)
{
        EXPECT_CALL(userPortMock, showNotConnected());
        EXPECT_CALL(timerPortMock, stopTimer());
        objectUnderTest.handleBTSDisconnected();
}

TEST_F(ApplicationConnectingTestSuite, shallNotConnectOnAttachReject)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleAttachReject();
}

struct ApplicationConnectedTestSuite : ApplicationConnectingTestSuite
{
    ApplicationConnectedTestSuite();
};

ApplicationConnectedTestSuite::ApplicationConnectedTestSuite()
{
    connectOnAttachAccept();
}

TEST_F(ApplicationConnectedTestSuite, shallHandleSms)
{
    Sms sms { PHONE_NUMBER, "sms message" };
    EXPECT_CALL(userPortMock, showNewSmsNotification());
    EXPECT_CALL(smsDbMock, addReceivedSms(sms));
    objectUnderTest.handleSms(sms);
}

TEST_F(ApplicationConnectedTestSuite, shallHandleComposeSms)
{
    EXPECT_CALL(userPortMock, showNewSmsToEdit());
    objectUnderTest.handleComposeSms();
}

TEST_F(ApplicationConnectedTestSuite, shallHandleSendSms)
{
    std::pair<common::PhoneNumber, std::string> sms;
    EXPECT_CALL(userPortMock, getSms()).WillOnce(Return(sms));
    EXPECT_CALL(btsPortMock, sendSms(common::PhoneNumber{}, ""));
    EXPECT_CALL(smsDbMock, addSms(common::PhoneNumber{}, ""));
    EXPECT_CALL(userPortMock, showConnected());
    objectUnderTest.handleSendSms();
}

TEST_F(ApplicationConnectedTestSuite, shallHandleShowSms)
{
    Sms sms { PHONE_NUMBER, "sms message" };

    constexpr std::size_t idx = 0;
    EXPECT_CALL(smsDbMock, updateSmsState(idx));
    EXPECT_CALL(smsDbMock, getSms(idx)).WillOnce(ReturnRef(sms));
    EXPECT_CALL(userPortMock, viewSms(sms));

    objectUnderTest.handleShowSms(idx);
}

TEST_F(ApplicationConnectedTestSuite, shallHandleShowSmsList)
{
    using smsT = std::pair<Sms, smsState>;
    std::vector<smsT> messages;
    Sms sms { PHONE_NUMBER, "sms message" };
    smsT msg { sms, smsState::Pending };
    messages.push_back(msg);

    EXPECT_CALL(smsDbMock, getSmsMessages()).WillOnce(ReturnRef(messages));
    EXPECT_CALL(userPortMock, viewSmsList(messages));

    objectUnderTest.handleShowSmsList();
}

} // namespace ue