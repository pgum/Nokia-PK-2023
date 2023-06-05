#include "SmsDb.hpp"

#include "Sms.hpp"

namespace ue
{
void SmsDb::addMessage(const Sms& sms)
{
    messages.push_back(sms);
}

const std::vector<Sms>& SmsDb::getAllMessages()
{
    return messages;
}

void SmsDb::setMessageState(std::size_t i, SmsState state)
{
    messages.at(i).state = state;
}

const Sms& SmsDb::getMessage(std::size_t i)
{
    return messages.at(i);
}

std::size_t SmsDb::getNumberOfMessages()
{
    return messages.size();
}

}  // namespace ue