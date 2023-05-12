#include "TimerPort.hpp"

namespace ue
{

TimerPort::TimerPort(common::ILogger &logger)
    : logger(logger, "[TIMER PORT]")
{}

void TimerPort::start(ITimerEventsHandler &handler)
{
    logger.logDebug("Started");
    this->handler = &handler;
}

void TimerPort::stop()
{
    logger.logDebug("Stoped");
    handler = nullptr;
}

void TimerPort::startTimer(Duration duration)
{
    logger.logDebug("Start timer: ", duration.count(), "ms");
    std::thread t0 = std::thread(&TimerPort::run, this, duration);
    t0.detach();
}

void TimerPort::stopTimer()
{
    logger.logDebug("Stop timer");
    isStopped.notify_all();
}

void TimerPort::run(Duration duration)
{
    std::unique_lock<std::mutex> cond_lock(mtx_stop);
    if (isStopped.wait_for(cond_lock, duration) == std::cv_status::timeout)
    {
        handler->handleTimeout();
    }
}

}// namespace ue
