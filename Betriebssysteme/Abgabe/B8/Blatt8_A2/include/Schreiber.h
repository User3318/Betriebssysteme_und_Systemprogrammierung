#pragma once

#include <string>
#include <queue>
#include <mutex>
#include <semaphore.h>
#include <shared_mutex>

class Schreiber {
public:
    Schreiber(std::array<int, 10>* database, std::shared_mutex* sharedMutex, int time);
    void run();
private:
    int create_data();
    void write(int random, int value);
    std::array<int, 10>* database;
    std::shared_mutex* sharedMutex;
    int time;
};