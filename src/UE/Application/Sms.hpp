#pragma once

#include "Messages/PhoneNumber.hpp"

namespace ue {

enum class SmsState
{
    NotViewed,
    Viewed,
    Sent,
    Failed
};

struct Sms
{
    common::PhoneNumber from{};
    std::string text;
    SmsState state{};
};

inline const auto operator==(const Sms& lhs, const Sms& rhs)
{
    return lhs.from == rhs.from and 
           lhs.text == rhs.text;
}

inline const auto operator!=(const Sms& lhs, const Sms& rhs)
{
    return not (lhs == rhs);
}

} // namespace ue