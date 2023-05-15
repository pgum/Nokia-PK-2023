#include "TalkingState.hpp"
#include "ConnectedState.hpp"


namespace ue
{
TalkingState::TalkingState(Context &context) : CallState(context, "TalkingState")
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

void TalkingState::handleRecieveTalkMessage(std::string message)
{
    //should get invoked by BTS
    //takes care of displaying Message on gui as part of converstaion
    context.user.displayMessage(message);
}


void TalkingState::handleSendTalkMessage(common::PhoneNumber destNumber, std::string message)
{
    //should get invoked by gui somehow
    //takes care of both displaying Message on gui as part of conversation
    //+ takes care of sending message via BTS via CallTalk()
    //TODO: cancel???

    context.bts.callTalk(context.user.getCallerNumber(), context.user.getOutgoingMessage());
}

}

