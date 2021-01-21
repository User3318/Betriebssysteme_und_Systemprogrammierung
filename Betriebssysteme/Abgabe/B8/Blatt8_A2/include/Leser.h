#pragma once

#include <queue>
#include <mutex>
#include <semaphore.h>
#include <shared_mutex>

class Leser {
public:
    Leser(std::array<int, 10>* database, std::shared_mutex* sharedMutex, int time, int id);
    void run();
private:
    int read(int random);
    void use_data(int value);
    std::array<int, 10>* database;
    std::shared_mutex* sharedMutex;
    int time;
    int id;
};