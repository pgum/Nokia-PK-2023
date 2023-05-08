#include "TalkingState.hpp"
#include "ConnectedState.hpp"


namespace ue
{
TalkingState::TalkingState(Context &context) : BaseState(context, "TalkingState")
{

}

void TalkingState::handleUnknownRecipient()
{
    using Duration = std::chrono::seconds;
    Duration uknownRecipientDisplayTime = Duration(5);

    context.timer.stopTimer();
    context.user.showPartnerNotAvailable();
    std::this_thread::sleep_for(uknownRecipientDisplayTime);
    context.user.showConnected();
    context.setState<ConnectedState>();
}
}

