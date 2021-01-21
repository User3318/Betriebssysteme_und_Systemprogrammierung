#include "Leser.h"
#include <iostream>
#include <unistd.h>

Leser::Leser(std::array<int, 10>* database, std::shared_mutex* sharedMutex, int time, int id)
        : database(database)
        , sharedMutex(sharedMutex)
        , time(time)
        , id(id)
{
}

int Leser::read(int random)
{
    std::shared_lock<std::shared_mutex> lock(*this->sharedMutex);
    int ret = database->at(random);
    std::cout << "Reader with id: " << id << " reads database at " << random << " and gets this value: " << ret << std::endl;
    lock.unlock();

    return ret;

}

void Leser::use_data(int value)
{
    sleep(time);
}

void Leser::run()
{
    while (true) {
        int random = rand() % 10;
        use_data(this->read(random));
    }
}
