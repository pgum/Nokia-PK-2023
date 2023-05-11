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
    common::PhoneNumber PHONE_NUMBER_CALLER{ 115 };

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

//********************************************************************************************
struct ApplicationNotConnectedTestSuite : ApplicationTestSuite
{
    void sendAttachRequestOnSib();
};

void ApplicationNotConnectedTestSuite::sendAttachRequestOnSib()
{
    using Duration = std::chrono::milliseconds;
    Duration timeForBtsResponse = Duration(500);

    EXPECT_CALL(btsPortMock, sendAttachRequest(btsId));
    EXPECT_CALL(userPortMock, showConnecting());
    EXPECT_CALL(timerPortMock, startTimer(timeForBtsResponse));
    objectUnderTest.handleSib(btsId);

}

TEST_F(ApplicationNotConnectedTestSuite, shallSendAttachRequestOnSib)
{
    sendAttachRequestOnSib();
}

//********************************************************************************************
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

//RE-ATTACH
TEST_F(ApplicationConnectingTestSuite, shallNotConnectOnConnectionDrop)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    EXPECT_CALL(timerPortMock, stopTimer());
    objectUnderTest.handleBTSDisconnected();
}
//********************************************************************************************
struct ApplicationConnectedTestSuite : ApplicationConnectingTestSuite
{
    ApplicationConnectedTestSuite();
    void responseToCallRequest();
};

ApplicationConnectedTestSuite::ApplicationConnectedTestSuite()
{
    connectOnAttachAccept();
}

void ApplicationConnectedTestSuite::responseToCallRequest()
{
    short reaction_time_s = 30000;
    EXPECT_CALL(userPortMock, setCallerNumber(PHONE_NUMBER_CALLER));
    EXPECT_CALL(userPortMock, showCalling(PHONE_NUMBER_CALLER));
    EXPECT_CALL(timerPortMock, startTimer(ITimerPort::Duration(reaction_time_s)));
    objectUnderTest.handleCallRequest(PHONE_NUMBER_CALLER);
}

//RE-ATTACH
TEST_F(ApplicationConnectedTestSuite, shallDisconnectOnConnectionDrop)
{
    EXPECT_CALL(userPortMock, showNotConnected());
    objectUnderTest.handleBTSDisconnected();
}

TEST_F(ApplicationConnectedTestSuite, shallDisplayCallRequestToUser)
{
    responseToCallRequest();
}
//********************************************************************************************
struct ApplicationReceivingStateTestSuite : ApplicationConnectedTestSuite
{
    ApplicationReceivingStateTestSuite();
    void callAcceptTest();
};

ApplicationReceivingStateTestSuite::ApplicationReceivingStateTestSuite()
{
    responseToCallRequest();
}

void ApplicationReceivingStateTestSuite::callAcceptTest()
{
    const long uknownRecipientReactTime = 15000;

    EXPECT_CALL(userPortMock, getCallerNumber());
    EXPECT_CALL(btsPortMock, sendCallAccept(common::PhoneNumber{ 000 }));
    EXPECT_CALL(userPortMock, showTalking());
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(timerPortMock, startTimer(ITimerPort::Duration(uknownRecipientReactTime)));

    objectUnderTest.handleCallAccept();
}

TEST_F(ApplicationReceivingStateTestSuite, callAcceptHandlerTest)
{
    callAcceptTest();
}


TEST_F(ApplicationReceivingStateTestSuite, dropCallRequestTest)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, getCallerNumber());
    EXPECT_CALL(btsPortMock, sendCallReject(common::PhoneNumber{ 000 }));
    EXPECT_CALL(userPortMock, showConnected());

    objectUnderTest.handleCallDrop();
}

TEST_F(ApplicationReceivingStateTestSuite, callRequestTimeoutTest)
{
    EXPECT_CALL(userPortMock, getCallerNumber());
    EXPECT_CALL(btsPortMock, sendCallReject(common::PhoneNumber{ 000 }));
    EXPECT_CALL(userPortMock, showConnected());

    objectUnderTest.handleTimeout();
}

struct ApplicationTalkinggStateTestSuite : ApplicationReceivingStateTestSuite
{
    ApplicationTalkinggStateTestSuite();
};

ApplicationTalkinggStateTestSuite::ApplicationTalkinggStateTestSuite()
{
    callAcceptTest();
}

TEST_F(ApplicationTalkinggStateTestSuite, uknownRecipmentReceiveTest)
{
    EXPECT_CALL(timerPortMock, stopTimer());
    EXPECT_CALL(userPortMock, showPartnerNotAvailable());
    EXPECT_CALL(userPortMock, showConnected());

    objectUnderTest.handleUnknownRecipient();
}

} //namespace ue
