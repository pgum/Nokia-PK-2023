#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "Ports/UserPort.hpp"
#include "Mocks/ILoggerMock.hpp"
#include "Mocks/IUserPortMock.hpp"
#include "Messages/PhoneNumber.hpp"
#include "Mocks/IUeGuiMock.hpp"

namespace ue
{
using namespace ::testing;

class UserPortTestSuite : public Test
{
protected:
    const common::PhoneNumber PHONE_NUMBER{112};
    NiceMock<common::ILoggerMock> loggerMock;
    StrictMock<IUserEventsHandlerMock> handlerMock;
    StrictMock<IUeGuiMock> guiMock;
    StrictMock<IListViewModeMock> listViewModeMock;

    IUeGui::Callback acceptCallback;
    IUeGui::Callback rejectCallback;

    StrictMock<ISmsComposeModeMock> smsComposeModeMock;
    StrictMock<ITextModeMock> textModeMock;

    UserPort objectUnderTest{loggerMock, guiMock, PHONE_NUMBER};

    UserPortTestSuite()
    {
        EXPECT_CALL(guiMock, setTitle(HasSubstr(to_string(PHONE_NUMBER))));
        EXPECT_CALL(guiMock, setAcceptCallback(_))
                .WillOnce(SaveArg<0>(&acceptCallback));
        EXPECT_CALL(guiMock, setRejectCallback(_))
                .WillOnce(SaveArg<0>(&rejectCallback));
        objectUnderTest.start(handlerMock);
    }

    ~UserPortTestSuite()
    {
        objectUnderTest.stop();
    }
};

TEST_F(UserPortTestSuite, shallStartStop)
{
}

TEST_F(UserPortTestSuite, shallShowNotConnected)
{
    EXPECT_CALL(guiMock, showNotConnected());
    objectUnderTest.showNotConnected();
}

TEST_F(UserPortTestSuite, shallShowConnecting)
{
    EXPECT_CALL(guiMock, showConnecting());
    objectUnderTest.showConnecting();
}

TEST_F(UserPortTestSuite, shallViewSmsList)
{
    const auto sms = Sms{PHONE_NUMBER, "text1", SmsState::NotViewed};

    const std::vector<Sms> smsMessages{sms, sms};

    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(listViewModeMock, addSelectionListItem(_, _)).Times(AtLeast(2));
    EXPECT_CALL(guiMock, setAcceptCallback(_));
    EXPECT_CALL(guiMock, setRejectCallback(_));
    objectUnderTest.viewSmsList(smsMessages);
}

TEST_F(UserPortTestSuite, shallViewEmptySmsList)
{
    const std::vector<Sms> smsMessages;

    EXPECT_CALL(guiMock, setListViewMode()).WillOnce(ReturnRef(listViewModeMock));
    EXPECT_CALL(listViewModeMock, clearSelectionList());
    EXPECT_CALL(guiMock, setAcceptCallback(_));
    EXPECT_CALL(guiMock, setRejectCallback(_));
    objectUnderTest.viewSmsList(smsMessages);
}

TEST_F(UserPortTestSuite, shallViewSms)
{
    const Sms sms{PHONE_NUMBER, "example"};

    EXPECT_CALL(guiMock, setViewTextMode()).WillOnce(ReturnRef(textModeMock));
    EXPECT_CALL(textModeMock, setText(sms.text));
    EXPECT_CALL(guiMock, setAcceptCallback(_));
    EXPECT_CALL(guiMock, setRejectCallback(_));
    objectUnderTest.viewSms(sms);
}

TEST_F(UserPortTestSuite, shallShowSmsEditMode)
{
    EXPECT_CALL(guiMock, setSmsComposeMode()).WillOnce(ReturnRef(smsComposeModeMock));
    EXPECT_CALL(guiMock,setAcceptCallback(_));
    EXPECT_CALL(guiMock,setRejectCallback(_));
    objectUnderTest.showNewSmsToEdit();
}

}
