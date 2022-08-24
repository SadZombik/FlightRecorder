#include "test.h"

Test::Test(FlightRecorder *FR)
{
    fr = FR;

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_params()));
    timer->start(33);
}

float Test::generate_number(float min, float max)
{
    float f = (float)rand() / RAND_MAX;
    return min + f * (max - min);
}

void Test::update_params()
{
    for (unsigned int i = 0; i < fr->fpar->count; i++)
        *fr->fpar->getElement(i) = generate_number(0, 100);
}
