#pragma once

#include "Messages/PhoneNumber.hpp"

namespace ue {

struct Sms
{
    common::PhoneNumber from;
    std::string text;

    Sms(const common::PhoneNumber& from, const std::string& text)
            : from { from }, text { std::move(text) } {}
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