#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

#include "Proc.h"

using SchedulerResult = pair<Proc, int>;

class Scheduler
{
private:
    unsigned int cpuTime = 0;
    list<Proc> arrivalQueue;

protected:
    void incCpuTime(unsigned int inc = 1)
    {
        cpuTime += inc;
    }

    [[nodiscard]] unsigned int getCpuTime() const
    {
        return cpuTime;
    }

    [[nodiscard]] list<Proc> getArrivedProc()
    {
        list<Proc> arrivedProcesses;

        while (!arrivalQueue.empty() && arrivalQueue.front().ArrivalTime <= this->getCpuTime())
        {
            arrivedProcesses.push_back(arrivalQueue.front());
            arrivalQueue.pop_front();
        }

        auto itLastProc = find_if(arrivalQueue.cbegin(), arrivalQueue.cend(),
                                  [this](Proc elem) -> bool
                                  {
                                      return elem.ArrivalTime > cpuTime;
                                  });

        arrivalQueue.splice(arrivedProcesses.cend(), arrivedProcesses, arrivalQueue.cbegin(), itLastProc);

        return arrivedProcesses;
    }

    [[nodiscard]] size_t arrivalQueueSize() const
    {
        return arrivalQueue.size();
    }

public:
    Scheduler(const list<Proc> &procList);

    virtual SchedulerResult dispatch() = 0;
    [[nodiscard]] virtual size_t getProcCount() const = 0;
    [[nodiscard]] virtual size_t getReadyProcCount() const = 0;

    virtual ~Scheduler() = default;

    Scheduler(const Scheduler& other) = delete; // Copy constructor
    Scheduler(Scheduler&& other) noexcept = delete; // Move constructor
    Scheduler& operator=(const Scheduler& other) = delete; // Copy assignment operator
    Scheduler& operator=(Scheduler&& other) noexcept = delete; // Move assignment operator
};

inline Scheduler::Scheduler(const list<Proc> &procList) : arrivalQueue(procList)
{
    arrivalQueue.sort(ProcComparator(ProcComparator::ARRIVAL_TIME, ProcComparator::LESS));
};

#endif // SCHEDULER_H