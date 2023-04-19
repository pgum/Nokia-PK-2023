#pragma once

#include "BaseState.hpp"
#include "Messages/BtsId.hpp"

namespace ue
{

class NotConnectedState : public BaseState
{
public:
    NotConnectedState(Context& context);
    void handleSib(common::BtsId) override;
};

}
