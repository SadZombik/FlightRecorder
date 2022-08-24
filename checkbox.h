#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>

#include "flightrecorder.h"

class CheckBox : public QWidget
{
public:
    CheckBox(FlightRecorder *FR);
    ~CheckBox();

    void addParam();
    void deleteParam(int id);
    void initCheckboxGeometry();

    QVector<QCheckBox*> checkbox_vector;

private:
    FlightRecorder *fr;
    QVBoxLayout *layout;

    int m_width, m_height;
    void paintEvent(QPaintEvent *event);
};

#endif // CHECKBOX_H
