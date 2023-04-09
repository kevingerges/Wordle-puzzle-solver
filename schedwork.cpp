#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;


// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here

bool isWorkerAvailable(const AvailabilityMatrix& avail, const size_t maxShifts, 
                       const std::vector<size_t>& shiftsByWorker, size_t day, size_t worker)
{
    return avail[day][worker] && shiftsByWorker[worker] < maxShifts;
}


Worker_T getWorkerWithFewestShifts(const std::vector<size_t>& shiftsByWorker)
{
    Worker_T worker = INVALID_ID;
    size_t minShifts = std::numeric_limits<size_t>::max();

    for (Worker_T i = 0; i < shiftsByWorker.size(); ++i) {
        if (shiftsByWorker[i] < minShifts) {
            worker = i;
            minShifts = shiftsByWorker[i];
        }
    }

    return worker;
}

bool backtrack(const AvailabilityMatrix& avail, const size_t dailyNeed,
               const size_t maxShifts, DailySchedule& sched, size_t day,
               size_t shifts, std::vector<size_t>& shiftsByWorker);

bool schedule(const AvailabilityMatrix& avail, const size_t dailyNeed,
              const size_t maxShifts, DailySchedule& sched)
{
    if (avail.empty()) {
        return false;
    }

    const size_t numDays = avail.size();
    const size_t numWorkers = avail[0].size();
    sched = DailySchedule(numDays, std::vector<Worker_T>(dailyNeed, INVALID_ID));
    std::vector<size_t> shiftsByWorker(numWorkers, 0);

    if (!backtrack(avail, dailyNeed, maxShifts, sched, 0, 0, shiftsByWorker)) {
        return false;
    }

    return true;
}

bool backtrack(const AvailabilityMatrix& avail, const size_t dailyNeed,
               const size_t maxShifts, DailySchedule& sched, size_t day,
               size_t shifts, std::vector<size_t>& shiftsByWorker)
{
    const size_t numDays = avail.size();
    const size_t numWorkers = avail[0].size();


    if (day == numDays) {
        return true;
    }


    if (shifts == dailyNeed) {
        return backtrack(avail, dailyNeed, maxShifts, sched, day+1, 0, shiftsByWorker);
    }


    if (std::none_of(avail[day].begin(), avail[day].end(), 
                     [&](bool available) { return available; })) {
        return false;
    }


    for (Worker_T worker = 0; worker < numWorkers; ++worker) {
        if (isWorkerAvailable(avail, maxShifts, shiftsByWorker, day, worker)) {

            sched[day][shifts] = worker;
            shiftsByWorker[worker]++;


            if (backtrack(avail, dailyNeed, maxShifts, sched, day, shifts+1, shiftsByWorker)) {
                return true;
            }


           
                    sched[day][shifts] = INVALID_ID;
        shiftsByWorker[worker]--;
    }
}


return false;
}