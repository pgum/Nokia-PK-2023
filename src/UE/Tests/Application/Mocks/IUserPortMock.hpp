#pragma once

#include <gmock/gmock.h>
#include "Ports/IUserPort.hpp"

namespace ue {

class IUserEventsHandlerMock : public IUserEventsHandler {
 public:
  IUserEventsHandlerMock();
  ~IUserEventsHandlerMock() override;
  MOCK_METHOD(void, handleSendCallRequest, (common::PhoneNumber), (final));
  MOCK_METHOD(void, handleSendCallDrop, (common::PhoneNumber), (final));
  MOCK_METHOD(void, handleSendCallAccept, (common::PhoneNumber), (final));
};

class IUserPortMock : public IUserPort {
 public:
  IUserPortMock();
  ~IUserPortMock() override;

  MOCK_METHOD(void, showNotConnected, (), (final));
  MOCK_METHOD(void, showConnecting, (), (final));
  MOCK_METHOD(void, showConnected, (), (final));
  MOCK_METHOD(void, showNewSmsNotification, (), (final));
  MOCK_METHOD(IUeGui::ISmsComposeMode&, composeSms, (), (final));
  MOCK_METHOD(int, getAction, (), (final));
  MOCK_METHOD(void, acceptCallback, (IUeGui::Callback), (final));
  MOCK_METHOD(void, rejectCallback, (IUeGui::Callback), (final));
  MOCK_METHOD(void, showEnterPhoneNumber, (), (final));
  MOCK_METHOD(void, showDialing, (common::PhoneNumber phoneNumber), (final));
  MOCK_METHOD(void, callAchieved, (common::PhoneNumber phoneNumber), (final));
};

}  // namespace ue
