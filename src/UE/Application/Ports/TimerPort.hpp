#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

#include "ITimerPort.hpp"
#include "Logger/PrefixedLogger.hpp"

namespace ue
{

class TimerPort : public ITimerPort
{
public:
    TimerPort(common::ILogger& logger);

    void start(ITimerEventsHandler& handler);
    void stop();

    // ITimerPort interface
    /**
    * Start timer in separeted thread.
    *
    * If duration time elapses before stopTimer() is called - handleTimeout() method from handler is invoked.
    * If stopTimer() method is called before duration time runs out - no other functions are called, thread closes.
    *
    * @param duration When duration time runs out, handleTimeout() method is called.
    */
    void startTimer(Duration duration) override;
    void stopTimer() override;

private:
    std::mutex mtx_stop{};
    std::condition_variable isStopped{};
    common::PrefixedLogger logger;
    ITimerEventsHandler* handler = nullptr;
    void run(Duration duration);
};

}
