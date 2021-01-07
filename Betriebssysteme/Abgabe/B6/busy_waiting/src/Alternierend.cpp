#include "Alternierend.h"
#include <iostream>
#include <cstdlib>

const int Alternierend::gesamtZahl = 4;
Konto Alternierend::konto;
int Alternierend::selectedTask = 0;

Alternierend::Alternierend(int id)
{
    this->id = id;
}

[[noreturn]] void Alternierend::run()
{
    while (true) {
        while (selectedTask != this->id);

        //generates Random Number between -1000 and 1000
        double randomNumber = (std::rand() / (RAND_MAX / (2000))) - 1000;

        konto.setKontoStand(konto.getKontoStand() + randomNumber);

        std::cout << "[Task " << id << "]" << "Kontostand: " << konto.getKontoStand() << std::endl;

        selectedTask = selectedTask < gesamtZahl - 1 ? selectedTask + 1 : 0;
    }
}