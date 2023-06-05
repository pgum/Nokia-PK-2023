#pragma once

#include <vector>

#include "ISmsDb.hpp"
#include "Sms.hpp"

namespace ue
{

enum class smsState
{
    Pending,
    Viewed
};

class SmsDb : public ISmsDb {
public:
    void addReceivedSms(const Sms& sms) override;
    const auto& getSmsMessages() const { return messages; }
private:
    std::vector<std::pair<Sms, smsState>> messages;
};

} // namespace ue