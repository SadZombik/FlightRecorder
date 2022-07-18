#include "flightrecorder.h"
#include "test.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    test t;

    float k = 1.2;
    FlightRecorder fr(1280*k, 720*k);

    fr.addParam("Высота\nгеометрическая", "Hgeo",   t.getParam(1), 0, -100, 100);
    fr.addParam("Скорость\nприборная", "Vp",        t.getParam(2), 0);
    fr.addParam("Гиромагнитный\nкурс", "",          t.getParam(3), 0);
    fr.addParam("Крен", "Кр",                       t.getParam(4), 1, -200, 200,  Qt::red);
    fr.addParam("Тангаж", "Тг",                     t.getParam(5), 1, 50, 100, Qt::darkGreen);
    fr.addParam("Вертикальная \nперегрузка", "",    t.getParam(6), 1, Qt::blue);
    fr.addParam("Положение РУ \nобщего шага", "",   t.getParam(7), 2);
    fr.addParam("Частота вращения НВ", "",          t.getParam(8), 2);
    fr.addParam("Частота вращения\nТК лев", "",     t.getParam(9), 2);
    fr.addParam("Частота вращения\nТК пра", "",     t.getParam(10), 3);

    fr.setMaxPoints(220);
    fr.start();
    return a.exec();
}
