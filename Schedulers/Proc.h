#ifndef PROC_H
#define PROC_H

#include <string>

using namespace std;

struct Proc
{
    string Name;
    unsigned int ArrivalTime = 0;
    unsigned int Burst = 0;
    unsigned int Priority = 0;
};

// Funtore comparatore per Proc
class ProcComparator
{
public:
    enum CompareBy
    {
        ARRIVAL_TIME,
        BURST,
        PRIORITY
    };

    enum CompareType
    {
        GREATER,
        LESS
    };

    ProcComparator(CompareBy cb, CompareType ct) : compareBy(cb), compareType(ct){};

    bool operator()(const Proc &p1, const Proc &p2) const
    {
        if (compareBy == CompareBy::BURST)
        {
            if (p1.Burst == p2.Burst)
            {
                return static_cast<int>(p1.Name < p2.Name) == compareType;
            }
            return static_cast<int>(p1.Burst < p2.Burst) == compareType;
        }

        if (compareBy == CompareBy::PRIORITY)
        {
            if (p1.Priority == p2.Priority)
            {
                return static_cast<int>(p1.Name < p2.Name) == compareType;
            }
            return static_cast<int>(p1.Priority < p2.Priority) == compareType;
        }

        if (p1.ArrivalTime == p2.ArrivalTime)
        {
            return static_cast<int>(p1.Name < p2.Name) == compareType;
        }

        return static_cast<int>(p1.ArrivalTime < p2.ArrivalTime) == compareType;
    }

private:
    CompareBy compareBy;
    CompareType compareType;
};

#endif // PROC_H
