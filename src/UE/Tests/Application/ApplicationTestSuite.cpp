#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Application.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IBtsPortMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Mocks/ITimerPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include <memory>

namespace ue
{
using namespace ::testing;

class ApplicationTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{ 112 };
    const common::BtsId btsId{ 333 };

    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IBtsPortMock> btsPortMock;
    StrictMock<IUserPortMock> userPortMock;
    StrictMock<ITimerPortMock> timerPortMock;

    Application objectUnderTest{PHONE_NUMBER,
                loggerMock,
                btsPortMock,
                userPortMock,
                timerPortMock};
};

struct ApplicationNotConnectedTestSuite : ApplicationTestSuite
{
    void sendAttachRequestOnSib();
};

void ApplicationNotConnectedTestSuite::sendAttachRequestOnSib()
{
    constexpr long bts_response_time_ms = 500;
    ITimerPort::Duration timerDuration = ITimerPort::Duration(bts_response_time_ms);

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

TEST_F(ApplicationConnectingTestSuite, shallNotConnectOnAttachReject)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleAttachReject();
}

// RE-ATTACH
TEST_F(ApplicationConnectingTestSuite, shallNotConnectOnConnectionDrop)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleBTSDisconnected();
}

struct ApplicationConnectedTestSuite : ApplicationConnectingTestSuite
{
    ApplicationConnectedTestSuite();
};

ApplicationConnectedTestSuite::ApplicationConnectedTestSuite()
{
    connectOnAttachAccept();
}

// RE-ATTACH
TEST_F(ApplicationConnectedTestSuite, shallDisconnectOnConnectionDrop)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleBTSDisconnected();
}

} // namespace ue
