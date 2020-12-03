#include "Scheduler.h"
#include "Task.h"
#include <queue>
#include <thread>
#include <unistd.h>

void enqueueTasks(std::queue<Task>* taskQueue)
{
    taskQueue->push(*(new Task("B",3)));
    taskQueue->push(*(new Task("F",2)));

    sleep(1);

    taskQueue->push(*(new Task("E",4)));

    sleep(1);

    taskQueue->push(*(new Task("A",1)));
    taskQueue->push(*(new Task("D",2)));

    sleep(2);

    taskQueue->push(*(new Task("C",4)));
}

int main()
{
    std::queue<Task>* taskQueue = new std::queue<Task>();

    Scheduler* scheduler = new Scheduler(taskQueue);

    std::thread thread(enqueueTasks, taskQueue);

    scheduler->schedule();

    thread.join();

    delete taskQueue;
    delete scheduler;
    return 0;
}