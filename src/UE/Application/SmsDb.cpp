#include "SmsDb.hpp"

namespace ue {

void SmsDb::addReceivedSms(const Sms& sms) {
  smsMessages.emplace_back(sms, SmsState::NotViewed);
}

void SmsDb::addSms(const Sms& sms) {
  smsMessages.emplace_back(sms, SmsState::NotViewed);
}

}  // namespace ue
