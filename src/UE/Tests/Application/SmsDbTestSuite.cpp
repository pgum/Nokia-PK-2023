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
    objectUnderTest.addSms(PHONE_NUMBER, "test message");

    const auto& messages = objectUnderTest.getSmsMessages();
    auto [sms, smsState] = messages.at(0);
    ASSERT_EQ(smsState, smsState::Send);
    ASSERT_EQ(sms.text, "test message");
}

TEST_F(SmsDbTestSuite, shallgetSms)
{
    const Sms sms { PHONE_NUMBER, "test message" };
    objectUnderTest.addReceivedSms(sms);

    const auto& retrievedSms = objectUnderTest.getSms(0);
    ASSERT_EQ(retrievedSms, sms);
}

TEST_F(SmsDbTestSuite, shallUpdateSmsState)
{
    const Sms sms {PHONE_NUMBER, "test message" };
    objectUnderTest.addReceivedSms(sms);

    const auto& msg = objectUnderTest.getSmsMessages();
    auto [_1, state] = msg.at(0);
    ASSERT_EQ(state, smsState::Pending);

    objectUnderTest.updateSmsState(0);

    const auto& msgAcc = objectUnderTest.getSmsMessages();
    auto [_2, stateAcc] = msgAcc.at(0);
    ASSERT_EQ(stateAcc, smsState::Viewed);
}

} // namespace ue