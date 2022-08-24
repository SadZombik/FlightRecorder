#ifndef SCALES_H
#define SCALES_H

#include <QWidget>

#include "flightrecorder.h"

// Шкалы
class Scales : public QWidget
{
public:
    Scales(FlightRecorder *FR);
    ~Scales() {}

    void initScalesGeometry();
    QVector<QRect> sections;

private:
    FlightRecorder *fr;

    // Геометрия
    int _x, y1, y2;
    int m_width, m_height;
    int ry, rx;
    void paintEvent(QPaintEvent *event);
    void draw_scales(QPainter *qp);
};

#endif // SCALES_H
