#ifndef PLOTS_H
#define PLOTS_H

#include <QWidget>

#include "flightrecorder.h"

// Виджет рисующий область с графиками
class Plots : public QWidget
{
public:
    Plots(FlightRecorder *fr);
    ~Plots() {}

    void initPlotsGeometry();
    void addNew();
    QVector<QRect> sections;

private:
    FlightRecorder *fr;

    int m_width, m_height;
    float dx = 5.f; // Расстояние между точками по Х
    int ry, rx;     // Размеры прямоугольников
    QVector<QVector<float>> graph;

    void paintEvent(QPaintEvent *event);
    void draw_plot(QPainter *qp);
};

#endif // PLOTS_H
