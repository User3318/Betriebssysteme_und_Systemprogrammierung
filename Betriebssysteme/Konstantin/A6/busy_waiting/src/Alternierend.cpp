#include "Alternierend.h"
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <time.h>

const int Alternierend::gesamtZahl = 4;
Konto Alternierend::konto;
int Alternierend::selectedTask = 0;

Alternierend::Alternierend(int id)
{
    this->id = id;
}

[[noreturn]] void Alternierend::run()
{
    std::srand(time(NULL));
    {
        while (true) {
            while(this->id != selectedTask){
            }
            //KA START
            int randomNumber = std::rand() % 50;
            int posNeg = std::rand() % 2;
            std::cout << "Number: " << randomNumber << "  Neg: " << posNeg << std::endl;
            if (posNeg == 0) {
                konto.setKontoStand(konto.getKontoStand() + randomNumber);
            }else{
                konto.setKontoStand(konto.getKontoStand() - randomNumber);
            }
            std::cout << "[Task " << id << "]" << "Kontostand: " << konto.getKontoStand() << std::endl;
            //KA END
            selectedTask += 1;
            if (selectedTask == gesamtZahl){
                selectedTask = 0;
            }
        }
    }
}