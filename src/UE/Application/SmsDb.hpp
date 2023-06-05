#pragma once

#include "ISmsDb.hpp"
#include "Sms.hpp"

namespace ue
{

class SmsDb : public ISmsDb
{
public:
    void addReceivedSms(const Sms& sms) override;
    const std::vector<std::pair<Sms, smsState>>& getSmsMessages() override;
    const Sms& getSms(std::size_t) override;
    void addSms(const common::PhoneNumber& rcvNum, const std::string& text) override;
    void updateSmsState(std::size_t) override;
private:
    std::vector<std::pair<Sms, smsState>> messages;
};

} // namespace ue