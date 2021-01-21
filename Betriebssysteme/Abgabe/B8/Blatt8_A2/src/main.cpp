#include "Schreiber.h"
#include "Leser.h"
#include <cstdlib>
#include <mutex>
#include <queue>
#include <thread>
#include <unistd.h>
#include <shared_mutex>

int main()
{

    srand(time(NULL));

    std::array<int, 10> data{0,0,0,0,0,0,0,0,0,0};
    std::array<int, 10>* database = &data;
    std::shared_mutex* sharedMutex = new std::shared_mutex;

    std::thread* writer = new std::thread(&Schreiber::run, Schreiber(database, sharedMutex, rand() % 5 + 1));
    std::thread* reader1 = new std::thread(&Leser::run, Leser(database, sharedMutex, rand() % 10 + 1, 1));
    std::thread* reader2 = new std::thread(&Leser::run, Leser(database, sharedMutex, rand() % 10 + 1, 2));
    std::thread* reader3 = new std::thread(&Leser::run, Leser(database, sharedMutex, rand() % 10 + 1, 3));
    std::thread* reader4 = new std::thread(&Leser::run, Leser(database, sharedMutex, rand() % 10 + 1, 4));

    while (true) {
        sleep(1);
    }

    delete database;
    writer->join();
    reader1->join();
    reader2->join();
    reader3->join();
    reader4->join();
    delete writer;
    delete reader1;
    delete reader2;
    delete reader3;
    delete reader4;

    return EXIT_SUCCESS;
}