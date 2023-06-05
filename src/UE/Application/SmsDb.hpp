#pragma once

#include <vector>

#include "ISmsDb.hpp"
#include "Sms.hpp"

namespace ue
{
class SmsDb : public ISmsDb
{
public:
    void addMessage(const Sms& sms) override;
    void setMessageState(std::size_t i, SmsState state) override;
    const std::vector<Sms>& getAllMessages() override;
    const Sms& getMessage(std::size_t i) override;
    std::size_t getNumberOfMessages() override;

private:
    std::vector<Sms> messages;
};

}  // namespace ue