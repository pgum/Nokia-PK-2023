#pragma once

#include <vector>

#include "ISmsDb.hpp"
#include "Sms.hpp"

namespace ue
{

enum class smsState
{
    Pending,
    Viewed,
    Send
};

class SmsDb : public ISmsDb {
public:
    void addReceivedSms(const Sms& sms) override;
    const auto& getSmsMessages() const { return messages; }
    void addSms(const common::PhoneNumber& rcvNum, const std::string& text) override;
private:
    std::vector<std::pair<Sms, smsState>> messages;
};

} // namespace ue