#include "ConnectedState.hpp"

namespace ue
{

ConnectedState::ConnectedState(Context &context)
    : BaseState(context, "ConnectedState")
{
    //this should show connected status
    context.user.showConnected();
}

}
