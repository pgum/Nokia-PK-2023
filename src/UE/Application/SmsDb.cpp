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
    messages.emplace_back({rcvNum, text}, smsState::Send);
}

} // namespace ue