#include "SmsDb.hpp"

namespace ue {

void SmsDb::addReceivedSms(const Sms& sms) {
  smsMessages.emplace_back(sms, SmsState::NotViewed);
}

void markLastSmsSentAsFailed() {}

void addSms(const Sms& sms){};

}  // namespace ue
