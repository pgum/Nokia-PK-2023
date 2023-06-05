#include "SmsDb.hpp"
#include "Sms.hpp"

namespace ue
{

void SmsDb::addReceivedSms(const Sms& sms) {
    messages.emplace_back(sms, smsState::Pending);
}

} // namespace ue