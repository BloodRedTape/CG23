#pragma once

#include <chrono>
#include <ostream>

class Time{
private:
    std::chrono::nanoseconds m_Value;
public:
    Time(std::chrono::nanoseconds value = std::chrono::nanoseconds()):
        m_Value(value)
    {}

    float AsSeconds(){
        return (float)AsNanoseconds() / 1000000000.f;
    }

    int AsMilliseconds(){
        return AsNanoseconds() / 1000000;
    }

    int64_t AsNanoseconds(){
        return m_Value.count();
    }

    friend std::ostream& operator<<(std::ostream& stream, Time time) {
        stream << time.AsMilliseconds() << "ms";
        return stream;
    }
};

class Clock{
private:
    std::chrono::time_point<std::chrono::steady_clock> m_Begin;
public:
    Clock():
        m_Begin(std::chrono::steady_clock::now())
    {}

    Time GetElapsedTime(){
        std::chrono::time_point<std::chrono::steady_clock> now = std::chrono::steady_clock::now();
        return Time(std::chrono::duration_cast<std::chrono::nanoseconds>(now - m_Begin));
    }

    void Reset(){
        m_Begin = std::chrono::steady_clock::now();
    }
};
