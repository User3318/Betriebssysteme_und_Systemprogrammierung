#pragma once

#include "Konto.h"

class Alternierend
{
public:
    Alternierend(int id);

    [[noreturn]] void run();
    const static int gesamtZahl;
    static Konto konto;
    static int selectedTask;

private:
    int id;
};
