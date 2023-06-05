#include "TalkingState.hpp"
#include "ConnectedState.hpp"


namespace ue
{
TalkingState::TalkingState(Context &context) : CallState(context, "TalkingState")
{
    //TODO: stop timer
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
    logger.logInfo("Recieved message: ");
    logger.logInfo(message);

    //should get invoked by BTS
    //takes care of displaying Message on gui as part of converstaion
    context.user.displayMessage(message);
}


void TalkingState::handleComposeMessage()
{
    //should get invoked by gui somehow
    //takes care of both displaying Message on gui as part of conversation
    //+ takes care of sending message via BTS via CallTalk()
    //TODO: cancel???
    context.bts.callTalk(context.user.getCallerNumber(), context.user.getOutgoingMessage());

}

void TalkingState::handleCallDrop()
{
    //handleCallDrop is recieved from UE, by pressing disconnect buton while talking

    //TODO: send CallDropped(from=myPhoneNumber, to=partnerPhoneNumber) to BTS
     context.bts.callDrop(context.user.getCallerNumber());

    //show main menu
    context.user.showCallEnded();

    //change state to Connected
    context.setState<ConnectedState>();
}

void TalkingState::handleBTSCallDrop(common::PhoneNumber from)
{
    //is recieved from BTS

    context.user.showCallEnded();

    context.setState<ConnectedState>();
}


}

