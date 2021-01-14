#include "Verbraucher.h"
#include <iostream>
#include <unistd.h>

Verbraucher::Verbraucher(std::queue<std::string>* queue, std::mutex* mutex, sem_t* semaphoreLeer, sem_t* semaphoreBelegt, int time)
        : queue(queue)
        , mutex(mutex)
        , semaphoreLeer(semaphoreLeer)
        , semaphoreBelegt(semaphoreBelegt)
        , time(time)
{
}

std::string Verbraucher::entnehmen()
{
    sem_wait(this->semaphoreBelegt);
    this->mutex->lock();

    std::string kuchen = this->queue->front();
    this->queue->pop();

    this->mutex->unlock();
    sem_post(this->semaphoreLeer);
    return kuchen;
}

void Verbraucher::konsumieren(std::string kuchen)
{
    std::cout << "[Verbraucher]Verbrauche " + kuchen << std::endl;
    sleep(this->time);
}

void Verbraucher::run()
{
    while (true) {
        konsumieren(this->entnehmen());
    }
}
