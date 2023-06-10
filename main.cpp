#include <iostream>
#include <fstream>
#include <limits>
#include <list>
#include <format>
#include <string_view>

#include "./Schedulers/Proc.h"
#include "./Schedulers/RR.h"
#include "./Schedulers/SJF.h"

using namespace std;

bool load_processes(string_view configFile, list<Proc> &procList);
void runner(Scheduler &&sch);

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "You must specify the path to the process file\n";
        return 1;
    }

    int quanto = 10;
    list<Proc> procList;

    if (!load_processes(argv[1], procList))
    {
        cout << format("Could not open the file: {} \n", argv[1]);
        return 1;
    }

    // Stampa dei processi letti dal file
    // for(auto it = procList.begin(); it != procList.end(); ++it){
    //     cout << it->ArrivalTime << " " << it->Name << " " <<  it->Burst << "
    //     "
    //     << it->Priority << endl;
    // }
    // cout << endl;

    cout << "FCFS:\t\t";
    runner(RR(procList, numeric_limits<int>::max()));

    cout << "SJF:\t\t";
    runner(SJF(procList));

    cout << "RR:\t\t";
    runner(RR(procList, quanto));

    return 0;
}

bool load_processes(string_view configFile, list<Proc> &procList)
{
    ifstream cf(configFile.data(), ios::in);

    if (!cf.is_open())
    {
        return false;
    }

    string name;
    unsigned int arrivalTime = 0;
    unsigned int burst = 0;
    unsigned int priority = 0;

    while (!cf.eof())
    {
        cf >> arrivalTime >> name >> burst >> priority;
        procList.push_back(Proc{name, arrivalTime, burst, priority});
    }

    cf.close();

    return true;
}

void runner(Scheduler &&sch)
{
    unordered_map<string, unsigned int> procBurst;
    unordered_map<string, unsigned int> procWaitingTime;
    unsigned int totalBurst = 0;

    SchedulerResult res;

    while (sch.getProcCount() != 0)
    {
        res = sch.dispatch();

        std::cout << res.first.Name;
        sch.getProcCount() == 0 ? std::cout << ",\t" : std::cout << "->";

        totalBurst += res.second;
        procBurst[res.first.Name] += res.second;
        procWaitingTime[res.first.Name] = totalBurst - procBurst[res.first.Name] - res.first.ArrivalTime;
    }

    unsigned int totalWaitingTime = 0;
    for (auto &&it : procWaitingTime)
    {
        totalWaitingTime += it.second;
    }

    std::cout << "TMA " << (float)totalWaitingTime / (float)procWaitingTime.size() << endl;
}