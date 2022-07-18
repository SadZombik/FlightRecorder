#include "test.h"

test::test(QObject *parent): QObject(parent)
{
    for (int i = 0; i < 12; ++i)
        params[i] = 0;


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_params()));
    timer->start(33);
}

float test::generate_number(float min, float max)
{
    float f = (float)rand() / RAND_MAX;
    return min + f * (max - min);
}

void test::update_params()
{
    for (int i = 0; i < 12; ++i)
        params[i] = generate_number(0, 100);

}
