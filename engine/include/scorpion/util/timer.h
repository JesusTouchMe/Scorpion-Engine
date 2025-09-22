// Copyright 2025 JesusTouchMe

#ifndef SCORPION_TIMER_H
#define SCORPION_TIMER_H 1

#include <chrono>
#include <thread>

namespace scorpion {
    template <class Clock = std::chrono::high_resolution_clock>
    class Timer {
    public:
        using TimePoint = typename Clock::time_point;

        explicit Timer(double targetSeconds = 0.0)
            : mTarget(targetSeconds)
            , mBase(Clock::now())
            , mPrevious(mBase)
            , mCurrent(mBase)
            , mDelta(0.0) {}

        void reset(double newTarget) {
            mTarget = newTarget;
            mBase = Clock::now();
            mPrevious = mBase;
            mCurrent = mBase;
            mDelta = 0.0;
        }

        void tick() {
            mPrevious = mCurrent;
            mCurrent = Clock::now();

            std::chrono::duration<double> delta = mCurrent - mPrevious;
            mDelta = delta.count();
        }

        void wait() {
            if (mTarget <= 0.0) return;

            auto target = std::chrono::duration<double>(mTarget);
            auto elapsed = Clock::now() - mPrevious;
            if (elapsed < target) {
                std::this_thread::sleep_for(target - elapsed); // TODO: maybe use a different way to sleep 90% of the wait time, then busy wait the last 10% for accuracy
            }
        }

        double getTarget() const { return mTarget; }
        double getDelta() const { return mDelta; }

        void setTarget(double target) { mTarget = target; }

        // utility for timing stuff weirdly
        TimePoint getCurrentTime() const { return Clock::now(); }
        TimePoint nextDue() const { return mPrevious + std::chrono::duration_cast<typename Clock::duration>(std::chrono::duration<double>(mTarget)); }

    private:
        double mTarget;
        TimePoint mBase;
        TimePoint mPrevious;
        TimePoint mCurrent;
        double mDelta;
    };
}

#endif // SCORPION_TIMER_H
