#pragma once

template <typename T1, typename T2>
class Pair
{
private:
    T1 first;
    T2 second;
public:
    Pair (T1 first, T2 second): first(first), second(second) {}

    bool operator==(Pair<T1, T2> other) const
    {
        return first == other.first && second == other.second;
    }

    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }
};