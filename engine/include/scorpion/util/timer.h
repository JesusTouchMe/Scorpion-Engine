// Copyright 2025 JesusTouchMe

#ifndef SCORPION_TIMER_H
#define SCORPION_TIMER_H 1

#include <chrono>

namespace scorpion {
    template <class Clock = std::chrono::high_resolution_clock>
    class Timer {
    public:
        Timer()
            : mLastTime(Clock::now())
            , mAccumulator(0.0) {}

        void reset() {
            mLastTime = Clock::now();
            mAccumulator = 0.0;
        }

        double deltaTime() {
            auto now = Clock::now();
            std::chrono::duration<double> dt = now - mLastTime;
            mLastTime = now;
            return dt.count();
        }

        double getAccumulator() const {
            return mAccumulator;
        }

        void update(double dt) {
            mAccumulator += dt;
        }

    private:
        typename Clock::time_point mLastTime;
        double mAccumulator;
    };
}

#endif // SCORPION_TIMER_H
