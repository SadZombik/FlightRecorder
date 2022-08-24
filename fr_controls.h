#ifndef FR_CONTROLS_H
#define FR_CONTROLS_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>

#include "flightrecorder.h"
#include "controlwidget.h"

class FR_Controls : public QWidget
{
    Q_OBJECT

public:
    FR_Controls(quint16 w, quint16 h, FlightRecorder *FR, QWidget *parent = nullptr);
    ~FR_Controls();

private:
    quint16 w, h;
    FlightRecorder *fr;
    QScopedPointer<ControlWidget> cw;

    QHBoxLayout *layout;
    QVBoxLayout *layout_buttons;
    QPushButton *btn_add;
    QPushButton *btn_delete;
    QPushButton *btn_clear;
    QPushButton *btn_save;
    QPushButton *btn_close;

    void showParamWidget();
};

#endif // FR_CONTROLS_H
