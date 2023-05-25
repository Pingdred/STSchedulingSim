#ifndef SJF_H
#define SJF_H

#include <algorithm>
#include <list>
#include <vector>

#include "Scheduler.h"

class SJF : public Scheduler
{

private:
    vector<Proc> readyHeap;
    Proc executedProc;

    size_t updateReadyQueue()
    {
        list<Proc> arrivedProcesses(this->getArrivedProc());

        for (auto &&it : arrivedProcesses)
        {
            readyHeap.push_back(std::move(it));
            push_heap(readyHeap.begin(), readyHeap.end(), ProcComparator(ProcComparator::BURST, ProcComparator::GREATER));
        }

        return arrivedProcesses.size();
    }

public:
    SJF(const list<Proc> &procList) : Scheduler(procList)
    {
        updateReadyQueue();
    }

    SchedulerResult dispatch() override
    {
        // Estrazione del processo con Burst minore
        executedProc = readyHeap.front();
        pop_heap(readyHeap.begin(), readyHeap.end(), ProcComparator(ProcComparator::BURST, ProcComparator::GREATER));
        readyHeap.pop_back();

        this->incCpuTime(executedProc.Burst);

        updateReadyQueue();

        return {executedProc, executedProc.Burst};
    }

    [[nodiscard]] size_t getProcCount() const override
    {
        return readyHeap.size() + this->getArrivalQueueSize();
    }

    [[nodiscard]] size_t getReadyProcCount() const override
    {
        return readyHeap.size();
    }
};

#endif // SJF_H