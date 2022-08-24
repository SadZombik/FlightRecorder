#include <QApplication>
#include "flightrecorder.h"
#include "fr_controls.h"
#include "test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FlightRecorder fr;
    FR_Controls controls(400, 300, &fr);
    Test t(&fr);

    fr.setChecked();
    fr.start();
    fr.show();

    return a.exec();
}
