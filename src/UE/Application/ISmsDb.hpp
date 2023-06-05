#pragma once

#include "Messages/PhoneNumber.hpp"
#include "Sms.hpp"
#include <vector>

namespace ue {

class Sms;

enum class smsState
{
    Pending,
    Viewed,
    Send
};

class ISmsDb {
public:
    virtual ~ISmsDb() = default;

    virtual void addMessage(const Sms& sms) = 0;
    virtual void setMessageState(std::size_t i, SmsState state) = 0;
    virtual const std::vector<Sms>& getAllMessages() = 0;
    virtual const Sms& getMessage(std::size_t i) = 0;
    virtual std::size_t getNumberOfMessages() = 0;
};

} // namespace ue