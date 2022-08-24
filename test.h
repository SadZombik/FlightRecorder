#ifndef TEST_H
#define TEST_H

#include "flightrecorder.h"

class Test : QObject
{
    Q_OBJECT
public:
    Test(FlightRecorder *FR);

private:
    FlightRecorder *fr;
    QTimer *timer;

    float generate_number(float min, float max);

private slots:
    void update_params();
};

#endif // TEST_H
