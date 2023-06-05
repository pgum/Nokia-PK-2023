#include "BtsPort.hpp"
#include "Messages/IncomingMessage.hpp"
#include "Messages/OutgoingMessage.hpp"
#include "Sms.hpp"

namespace ue
{

BtsPort::BtsPort(common::ILogger &logger, common::ITransport &transport, common::PhoneNumber phoneNumber)
    : logger(logger, "[BTS-PORT]"),
      transport(transport),
      phoneNumber(phoneNumber)
{}

void BtsPort::start(IBtsEventsHandler &handler)
{
    transport.registerMessageCallback([this](BinaryMessage msg) {handleMessage(msg);});
    transport.registerDisconnectedCallback([this]{this->handler->handleBTSDisconnected();});
    this->handler = &handler;
}

void BtsPort::stop()
{
    transport.registerMessageCallback(nullptr);
    handler = nullptr;
}

void BtsPort::handleMessage(BinaryMessage msg)
{
    try
    {
        common::IncomingMessage reader{msg};
        auto msgId = reader.readMessageId();
        auto from = reader.readPhoneNumber();
        auto to = reader.readPhoneNumber();

        switch (msgId)
        {
        case common::MessageId::Sib:
        {
            auto btsId = reader.readBtsId();
            handler->handleSib(btsId);
            break;
        }
        case common::MessageId::AttachResponse:
        {
            bool accept = reader.readNumber<std::uint8_t>() != 0u;
            if (accept)
                handler->handleAttachAccept();
            else
                handler->handleAttachReject();
            break;
        }

        case common::MessageId::CallRequest:
        {
            handler->handleCallRequest(from);
            break;
        }
        case common::MessageId::UnknownRecipient:
        {
            handler->handleUnknownRecipient();
            break;
        }
        case common::MessageId::CallTalk:
        {
            handler->handleRecieveTalkMessage(reader.readRemainingText()); //TODO consider changing readRemainingText to readText, and pass message size somehow
            break;
        }
        case common::MessageId::CallAccepted:
        {
            handler->handleBTSCallAccept(from);
            break;
        }
        case common::MessageId::CallDropped:
        {
            handler->handleBTSCallDrop(from);
            break;
        }
        case common::MessageId::Sms:
        {
            const auto sms = Sms { from, reader.readRemainingText() };
            handler->handleSms(sms);
        }
        default:
            logger.logError("unknown message: ", msgId, ", from: ", from);

        }
        //TODO: case common::MessageId::CallTalk
        //handler-> void TalkingState::handleRecieveTalkMessage()
    }
    catch (std::exception const& ex)
    {
        logger.logError("handleMessage error: ", ex.what());
    }
}

void BtsPort::sendAttachRequest(common::BtsId btsId)
{
    logger.logDebug("sendAttachRequest: ", btsId);
    common::OutgoingMessage msg{common::MessageId::AttachRequest,
                                phoneNumber,
                                common::PhoneNumber{}};
    msg.writeBtsId(btsId);
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallAccept(common::PhoneNumber destNumber)
{
    logger.logDebug("sendCallAccepted: ");
    common::OutgoingMessage msg{common::MessageId::CallAccepted, phoneNumber, destNumber};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallReject(common::PhoneNumber destNumber)
{
    logger.logDebug("sendCalRejected: ");
    common::OutgoingMessage msg{common::MessageId::CallDropped, phoneNumber, destNumber};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendCallRequest(common::PhoneNumber destNumber)
{
    logger.logDebug("sendCallRequest: ");
    common::OutgoingMessage msg{common::MessageId::CallRequest, phoneNumber, destNumber};
    transport.sendMessage(msg.getMessage());
}

//TODO: change this into CallTalk
void BtsPort::callTalk(common::PhoneNumber destNumber, std::string message)
{
    logger.logDebug("sendMessage: "); //TODO: add message content to log info?
    common::OutgoingMessage msg{common::MessageId::CallTalk, phoneNumber, destNumber};
    msg.writeText(message);
    transport.sendMessage(msg.getMessage());
}

void BtsPort::callDrop(common::PhoneNumber destNumber)
{
    logger.logDebug("send callDropped");
    common::OutgoingMessage msg{common::MessageId::CallDropped, phoneNumber, destNumber};
    transport.sendMessage(msg.getMessage());
}

void BtsPort::sendSms(const Sms& sms)
{
    logger.logDebug("send sms to: ", sms.text);
    common::OutgoingMessage msg{common::MessageId::Sms, phoneNumber, sms.from};
    msg.writeText(sms.text);
    transport.sendMessage(msg.getMessage());
}

} // namespace ue
