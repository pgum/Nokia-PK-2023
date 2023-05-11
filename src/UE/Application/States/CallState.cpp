#include "CallState.hpp"

namespace ue
{
CallState::CallState(Context& context) : ConnectedState(context, "CallState")
{

}

CallState::CallState(Context& context, const std::string&  name) : ConnectedState(context, name)
{

}

}
