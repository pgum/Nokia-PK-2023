#include <gtest/gtest.h>

#include "Messages/PhoneNumber.hpp"
#include "Sms.hpp"
#include "SmsDb.hpp"

namespace ue
{
using namespace ::testing;

class SmsDbTestSuite : public Test
{
protected:
    static constexpr common::PhoneNumber number{112};

    SmsDb objectUnderTest;
};

TEST_F(SmsDbTestSuite, shallAddReceivedSms)
{
    objectUnderTest.addMessage(Sms{number, "sms message"});
    const auto& sms = objectUnderTest.getMessage(0);
    ASSERT_EQ(sms.state, SmsState::NotViewed);
}

TEST_F(SmsDbTestSuite, shallgetSms)
{
    const Sms sms{number, "sms message"};
    objectUnderTest.addMessage(sms);
    const auto& retrieved = objectUnderTest.getMessage(0);
    ASSERT_EQ(retrieved, sms);
}

TEST_F(SmsDbTestSuite, shallUpdateSmsState)
{
    objectUnderTest.addMessage(Sms{number, "sms message"});
    objectUnderTest.setMessageState(0, SmsState::Viewed);
    const auto& sms = objectUnderTest.getMessage(0);
    ASSERT_EQ(sms.state, SmsState::Viewed);
}

TEST_F(SmsDbTestSuite, shallAddSentSms)
{
    const auto rcvNum = common::PhoneNumber{113};
    objectUnderTest.addMessage(Sms{rcvNum, "sms message", SmsState::Sent});
    constexpr std::size_t idx = 0;
    const auto& sms = objectUnderTest.getMessage(idx);
    ASSERT_EQ(sms.text, "sms message");
    ASSERT_EQ(sms.state, SmsState::Sent);
}

TEST_F(SmsDbTestSuite, shallGetNumberOfMessages)
{
    objectUnderTest.addMessage(Sms{number, "sms message", SmsState::Sent});
    objectUnderTest.addMessage(Sms{number, "sms message", SmsState::Sent});
    constexpr std::size_t numOfMsgs = 2;
    ASSERT_EQ(objectUnderTest.getNumberOfMessages(), numOfMsgs);
}

}  // namespace ue