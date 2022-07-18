#ifndef TEST_H
#define TEST_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <cstdlib>

class test : public QObject
{
    Q_OBJECT

public:

    test(QObject *parent = nullptr);

    float* getParam(int id) { return &params[id]; }

private:
    float params[12];
    float generate_number(float min, float max);

private slots:
    void update_params();

};

#endif // TEST_H
