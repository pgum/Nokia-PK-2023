#include <gtest/gtest.h>

#include "SmsDb.hpp"
#include "Sms.hpp"
#include "Messages/PhoneNumber.hpp"

namespace ue
{

using namespace ::testing;

class SmsDbTestSuite : public Test {
protected:
    static constexpr common::PhoneNumber PHONE_NUMBER { 112 };

    SmsDb objectUnderTest;
};

TEST_F(SmsDbTestSuite, shallAddReceivedSms)
{
    const auto exampleSmsText = "test message";
    const Sms dummySms { PHONE_NUMBER, exampleSmsText };
    objectUnderTest.addReceivedSms(dummySms);

    const auto& messages = objectUnderTest.getSmsMessages();
    const auto [sms, smsState] = messages.at(0);
    ASSERT_EQ(smsState, smsState::Pending);
    ASSERT_EQ(sms.text, exampleSmsText);
}

TEST_F(SmsDbTestSuite, shallAddSms)
{
    objectUnderTest.addSms(PHONE_NUMBER, "sms message");

    const auto& messages = objectUnderTest.getSmsMessages();
    auto [sms, smsState] = messages.at(0);
    ASSERT_EQ(smsState, smsState::Send);
    ASSERT_EQ(sms.text, "sms message");
}

} // namespace ue