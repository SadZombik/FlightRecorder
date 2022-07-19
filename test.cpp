#include "test.h"

test::test(QObject *parent): QObject(parent)
{
    for (int i = 0; i < 12; ++i)
        params[i] = 0;

    float k = 1.2;
    fr = new FlightRecorder(1280*k, 720*k);

    fr->addParam("Высота\nгеометрическая", "Hgeo",   0, -100, 100);
    fr->addParam("Скорость\nприборная", "Vp",        0);
    fr->addParam("Гиромагнитный\nкурс", "",          0);
    fr->addParam("Крен", "Кр",                       1, -200, 200,  Qt::red);
    fr->addParam("Тангаж", "Тг",                     1, 50, 100, Qt::darkGreen);
    fr->addParam("Вертикальная \nперегрузка", "",    1, Qt::blue);
    fr->addParam("Положение РУ \nобщего шага", "",   2);
    fr->addParam("Частота вращения НВ", "",          2);
    fr->addParam("Частота вращения\nТК лев", "",     2);
    fr->addParam("Частота вращения\nТК пра", "",     3);
    fr->addParam("TEST PARAM", "",                   3);
    fr->addParam("TEST PARAM", "",                   3);

    fr->setMaxPoints(220);
    fr->start();


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_params()));
    timer->start(33);
}

test::~test()
{
    delete fr;
}

float test::generate_number(float min, float max)
{
    float f = (float)rand() / RAND_MAX;
    return min + f * (max - min);
}

void test::update_params()
{
    for (int i = 0; i < 12; ++i)
    {
        //params[i] = generate_number(0, 100);
        fr->updateParam(i, generate_number(0, 100));
    }
}
