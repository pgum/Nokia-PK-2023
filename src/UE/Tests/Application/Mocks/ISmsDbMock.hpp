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

    MOCK_METHOD(void, addMessage, (const Sms&), (final));
    MOCK_METHOD(const std::vector<Sms>&, getAllMessages, (), (final));
    MOCK_METHOD(void, setMessageState, (std::size_t i, SmsState state), (final));
    MOCK_METHOD(const Sms&, getMessage, (std::size_t i), (final));
    MOCK_METHOD(std::size_t, getNumberOfMessages, (), (final));

};

inline bool operator==(const std::vector<Sms>& lhs, const std::vector<Sms>& rhs)
{
    return lhs.data() == rhs.data() && lhs.size() == rhs.size();
}

} // namespace ue