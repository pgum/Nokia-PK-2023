#pragma once

#include "ConnectedState.hpp"

namespace ue
{

class CallState : public ConnectedState
{
public:
    CallState(Context& context, const std::string& name);
    CallState(Context& context);

};

}

