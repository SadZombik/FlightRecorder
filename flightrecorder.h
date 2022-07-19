#ifndef FLIGHTRECORDER_H
#define FLIGHTRECORDER_H

#include <QWidget>
#include <QBoxLayout>
#include <QPainter>
#include <QCheckBox>
#include <QTimer>
#include <QDebug>
#include <QVector>
#include <ctime>
#include <cstdlib>

// Общий виджет
class FlightRecorder : public QWidget
{
    Q_OBJECT

public:
    FlightRecorder(quint16 width=0, quint16 height=0);
    ~FlightRecorder();

    void addParam(
        const QString &name,            // Название параметра
        const QString &abbreviation,    // Аббревиатура/сокращение
        const quint16 section,          // Секция, графика (0-3)
        const float min = 0,
        const float max = 100,
        QColor color = Qt::white        // Цвет графика и шкалы
    );

    void updateParam(quint16 id, const float val) { params_vector[id]->value = val; }
    void setMaxPoints(const int n) { max_points = n; }

public slots:
    void start(int t = 33) { timer->start(t); }
    void stop() { timer->stop(); }

private: // fields
    static quint16 w, h;

    QHBoxLayout *layout;
    QTimer *timer;

    static const int spacing = 10;  // Отступ
    static quint16 NParams;         // Количество параметров
    static quint16 max_points;      // Максимальное количество точек графика

    // Геометрия
    static int _x, y1, y2;

private: // inner classes
    // Виджет с чекбоксами
    class CheckBox : public QWidget
    {
    public:
        CheckBox() { layout = new QVBoxLayout(this); }
        ~CheckBox() { delete layout; }

        void addnew();
        QVector<QCheckBox*> checkbox_vector;
        QVBoxLayout *layout;

    private:
        int m_width, m_height;
        void paintEvent(QPaintEvent *event);
    };

    // Шкалы
    class Scales : public QWidget
    {
    public:
        Scales() {}
        ~Scales() {}

        void initScalesGeometry();
        QRect sections[4];

    private:
        int m_width, m_height;
        int ry, rx;
        void paintEvent(QPaintEvent *event);
        void draw_scales(QPainter *qp);
    };

    // Виджет рисующий область с графиками
    class Plots : public QWidget
    {
    public:
        Plots() {}
        ~Plots() {}

        void initPlotsGeometry();
        void addNew() { graph.resize(NParams); }

    private:
        int m_width, m_height;
        int dx = 5;     // Расстояние между точками по Х
        int ry, rx;     // Размеры прямоугольников
        QVector<QVector<float>> graph;
        QRect sections[4];

        void paintEvent(QPaintEvent *event);
        void draw_graph(QPainter *qp);
    };

    // Структура для атрибутов каждого параметра
    struct Param
    {
        static quint16 idGen;
        quint16 id;
        QString name;
        QString abbreviation;
        float value = 0;
        quint16 section;
        QColor color;
        float min;
        float max;
        float divisions[11];
    };

    static CheckBox *checkbox;
    static Scales *scales;
    static Plots *plots;

    static QVector<Param*> params_vector;
};

#endif // FLIGHTRECORDER_H

/* Параметры
 * Высота геометрическая
 * Скорость приборная
 * Гиромагнитный курс
 * Крен
 * Тангаж
 * Вертикальная перегрузка
 * Положение РУ общего шага
 * Частота вращения НВ
 * Частота вращения ТК левого двигателя
 * Частота вращения ТК правого двигателя
 *
 */
