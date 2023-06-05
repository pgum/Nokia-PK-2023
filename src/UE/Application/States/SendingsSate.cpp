#include "SendingState.hpp"
#include "TalkingState.hpp"

namespace ue
{
SendingState::SendingState(Context &context) : CallState(context, "SendingState")
{

}

void SendingState::handleCallAccept()
{
    using Duration = std::chrono::milliseconds;
    Duration timeForBtsResponse = Duration(60000);

    common::PhoneNumber recipientNumber = context.user.getEnteredPhoneNumber();
    context.bts.sendCallRequest(recipientNumber);
    context.user.setCallerNumber(recipientNumber);
    context.timer.startTimer(timeForBtsResponse);
    context.user.showCalling(recipientNumber);



}

void SendingState::handleBTSCallAccept(common::PhoneNumber from)
{
    logger.logInfo("RECEIVED CALL REQUSET");
    if(from == context.user.getCallerNumber())
    {
        context.user.showTalking();
        context.timer.stopTimer();
        context.setState<TalkingState>();
    }
}

}
