#pragma once
#include <Messages/PhoneNumber.hpp>
#include <chrono>
class Sms {
 private:
  std::string text;
  common::PhoneNumber from;
  common::PhoneNumber to;
  bool read = false;
  bool received = true;
  std::chrono::time_point<std::chrono::system_clock> receiveTime;

 public:
  Sms();

  Sms(const std::string& text,
      const common::PhoneNumber& from,
      const common::PhoneNumber& to,
      bool read,
      bool received,
      const std::chrono::time_point<std::chrono::system_clock>& receiveTime);

  Sms(const std::string& text,
      const common::PhoneNumber& from,
      const common::PhoneNumber& to,
      bool read,
      bool received);
  void markAsRead();
  void markAsNotReceived();
  bool isRead() const;
  bool isReceived() const;
  std::string getText();

  const common::PhoneNumber& getFrom() const;

  const common::PhoneNumber& getTo() const;

  const std::chrono::time_point<std::chrono::system_clock>& getReceiveTime()
      const;
};
