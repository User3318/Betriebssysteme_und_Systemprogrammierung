#include "Verbraucher.h"
#include <iostream>
#include <unistd.h>

Verbraucher::Verbraucher(std::queue<std::string>* queue, std::mutex* mutex, std::condition_variable* conditionVariableLeer,
        std::condition_variable* conditionVariableBelegt, int time)
        : queue(queue)
        , mutex(mutex)
        , conditionVariableLeer(conditionVariableLeer)
        , conditionVariableBelegt(conditionVariableBelegt)
        , time(time)
{
}

std::string Verbraucher::entnehmen()
{

    std::unique_lock<std::mutex> lock(*this->mutex);
    this->conditionVariableBelegt->wait(lock, [&]() { return !this->queue->empty(); });

    std::string kuchen = this->queue->front();
    this->queue->pop();

    lock.unlock();
    this->conditionVariableLeer->notify_one();

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
