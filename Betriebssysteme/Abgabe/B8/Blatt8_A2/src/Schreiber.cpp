#include "Schreiber.h"
#include <iostream>
#include <unistd.h>

Schreiber::Schreiber(std::array<int, 10>* database, std::shared_mutex* sharedMutex, int time)
        : database(database)
        , sharedMutex(sharedMutex)
        , time(time)
{
}

int Schreiber::create_data()
{
    srand(std::time(NULL));
    return rand() % 100 +1;
}

void Schreiber::write(int random, int value)
{
    std::unique_lock<std::shared_mutex> lock(*this->sharedMutex);

    std::cout << "Writer writes at database on position " << random << " this value: " << value << std::endl;
    database->at(random) = value;

    lock.unlock();
}

void Schreiber::run()
{
    while (true) {
        sleep(time);
        int random = rand() % 10;
        write(random, this->create_data());
    }
}