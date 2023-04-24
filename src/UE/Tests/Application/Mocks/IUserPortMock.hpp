#pragma once

#include "Ports/IUserPort.hpp"
#include <gmock/gmock.h>

namespace ue {

class IUserEventsHandlerMock : public IUserEventsHandler {
public:
  IUserEventsHandlerMock();
  ~IUserEventsHandlerMock() override;

  MOCK_METHOD(void, handleCallAccept, (common::PhoneNumber to), (final));
};

class IUserPortMock : public IUserPort {
public:
  IUserPortMock();
  ~IUserPortMock() override;

  MOCK_METHOD(void, showNotConnected, (), (final));
  MOCK_METHOD(void, showConnecting, (), (final));
  MOCK_METHOD(void, showConnected, (), (final));
  MOCK_METHOD(void, showCallRequest, (common::PhoneNumber from), (final));
  MOCK_METHOD(void, showTalking, (), (final));
};

} // namespace ue
