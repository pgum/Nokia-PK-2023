#pragma once

#include "Ports/IBtsPort.hpp"
#include <gmock/gmock.h>

namespace ue {

class IBtsEventsHandlerMock : public IBtsEventsHandler {
public:
  IBtsEventsHandlerMock();
  ~IBtsEventsHandlerMock() override;

  MOCK_METHOD(void, handleDisconnected, (), (final));
  MOCK_METHOD(void, handleSib, (common::BtsId), (final));
  MOCK_METHOD(void, handleAttachAccept, (), (final));
  MOCK_METHOD(void, handleAttachReject, (), (final));
  MOCK_METHOD(void, handleCallRequest, (common::PhoneNumber from), (final));
};

class IBtsPortMock : public IBtsPort {
public:
  IBtsPortMock();
  ~IBtsPortMock() override;

  MOCK_METHOD(void, sendAttachRequest, (common::BtsId), (final));
  MOCK_METHOD(void, sendCallAccepted, (common::PhoneNumber answerNum), (final));
};

} // namespace ue
