#ifndef RR_H
#define RR_H

#include <list>

#include "Scheduler.h"

using namespace std;

class RR : public Scheduler
{
private:
    list<Proc> readyQueue;
    unsigned int quanto = 0;

    size_t updateReadyQueue()
    {
        list<Proc> arrivedProcesses(this->getArrivedProc());

        for (auto &&it : arrivedProcesses)
        {
            readyQueue.push_back(std::move(it));
        }

        return arrivedProcesses.size();
    }

public:
    RR(int quanto, const list<Proc> &procList) : quanto(quanto), Scheduler(procList)
    {
        updateReadyQueue();
    }

    SchedulerResult dispatch() override
    {

        if (readyQueue.empty())
        {
            return SchedulerResult{Proc(), 0};
        }
        // Indica il tempo di burst concesso al processo selezionato
        // in base a quanto e al burst totale richiesto dal processo
        unsigned int burst = 0;

        Proc executedProc(readyQueue.front());
        readyQueue.pop_front();

        if (executedProc.Burst > quanto)
        {
            executedProc.Burst -= quanto;
            burst = quanto;
        }
        else
        {
            burst = executedProc.Burst;
            executedProc.Burst = 0;
        }

        this->incCpuTime(burst);

        updateReadyQueue();

        // Se il processo precedentemente selezionato non ha terminato
        // la sua esecuzione viene reinserito in coda
        if (executedProc.Burst > 0)
        {
            readyQueue.push_back(executedProc);
        }

        return SchedulerResult{executedProc, burst};
    }

    [[nodiscard]] size_t getProcCount() const override
    {
        return readyQueue.size() + this->arrivalQueueSize();
    }

    [[nodiscard]] size_t getReadyProcCount() const override
    {
        return readyQueue.size();
    }
};

#endif // RR_H