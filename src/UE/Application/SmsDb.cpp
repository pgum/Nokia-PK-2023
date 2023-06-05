#include "SmsDb.hpp"
#include "Sms.hpp"

namespace ue
{

void SmsDb::addReceivedSms(const Sms& sms)
{
    messages.emplace_back(sms, smsState::Pending);
}

void SmsDb::addSms(const common::PhoneNumber& rcvNum, const std::string& text)
{
    messages.emplace_back(Sms{rcvNum, text}, smsState::Send);
}

const std::vector<std::pair<Sms, smsState>>& SmsDb::getSmsMessages()
{
    return messages;
}

void SmsDb::updateSmsState(std::size_t idx)
{
    messages.at(idx).second = smsState::Viewed;
}

const Sms& SmsDb::getSms(std::size_t idx)
{
    return messages.at(idx).first;
}

} // namespace ue