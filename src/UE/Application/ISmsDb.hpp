#pragma once

#include "Messages/PhoneNumber.hpp"
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

    virtual void addReceivedSms(const Sms& sms) = 0;
    virtual void addSms(const common::PhoneNumber& rcvNum,
                        const std::string& text) = 0;
    virtual const std::vector<std::pair<Sms, smsState>>& getSmsMessages() = 0;
    virtual void updateSmsState(std::size_t) = 0;
    virtual const Sms& getSms(std::size_t) = 0;
};

} // namespace ue