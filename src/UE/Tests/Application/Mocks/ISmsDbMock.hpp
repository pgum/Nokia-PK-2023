#pragma once

#include <gmock/gmock.h>

#include "ISmsDb.hpp"

namespace ue
{
class Sms;

class ISmsDbMock : public ISmsDb
{
public:
    ISmsDbMock();
    ~ISmsDbMock() override;

    MOCK_METHOD(void, addReceivedSms, (const Sms&), (final));
    MOCK_METHOD(void, addSms, (const common::PhoneNumber&, const std::string&), (final));
    MOCK_METHOD((const std::vector<std::pair<Sms, smsState>>&), getSmsMessages, (), (final));
    MOCK_METHOD(void, updateSmsState, (std::size_t), (final));
    MOCK_METHOD(const Sms&, getSms, (std::size_t), (final));
};

} // namespace ue