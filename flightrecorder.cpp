#include "flightrecorder.h"

FlightRecorder::FlightRecorder(quint16 width, quint16 height)
{
    setStyleSheet("background-color: silver");
    if (!(width && height))
    {
        showFullScreen();
        w = this->width();
        h = this->height();
    }
    else
    {
        w = width; h = height;
        resize(width, height);
    }

    layout = new QHBoxLayout(this);
    layout->setSpacing(spacing);
    layout->setContentsMargins(spacing,spacing,0,0);
    setLayout(layout);

    checkbox = new CheckBox;
    checkbox->setFixedSize(w*0.1, h);
    layout->addWidget(checkbox);

    scales = new Scales;
    scales->setFixedSize(w*0.15, h);
    scales->initScalesGeometry();
    layout->addWidget(scales);

    plots = new Plots;
    plots->setFixedSize(w*0.75, h);
    plots->initPlotsGeometry();
    layout->addWidget(plots);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    this->show();
    checkbox->show();
    scales->show();
    plots->show();
}

FlightRecorder::~FlightRecorder()
{
    stop();

    // Удаляет указатели в векторе?
    for (auto p : params_vector)
        delete p;
    params_vector.clear();

    for (auto c : checkbox->checkbox_vector)
        delete c;
    checkbox->checkbox_vector.clear();

    delete plots;
    delete scales;
    delete checkbox;
    delete layout;
}

void FlightRecorder::addParam(const QString &name, const QString &abbreviation, const float *p_param, const quint16 section, const float min, const float max, QColor color)
{
    NParams++;

    if (color == Qt::white)
    {
        srand(time(NULL)+rand());
        int r = rand()/255, g = rand()/255,  b = rand()/255;
        color = QColor(r, g, b);
    }

    Param *newParam = new Param;
    newParam->name = name;
    newParam->abbreviation = abbreviation;
    newParam->p_param = p_param;
    newParam->section = section;
    newParam->color = color;
    newParam->min = min;
    newParam->max = max;

    int d = (max-min)/10;
    for (int i = 0; i < 11; i++)
        newParam->divisions[i] = max-d*i;

    params_vector.push_back(newParam);
    checkbox->addnew();
    plots->addNew();
}

// statics
quint16 FlightRecorder::NParams = 0, FlightRecorder::w, FlightRecorder::h, FlightRecorder::max_points = 100;
int FlightRecorder::_x, FlightRecorder::y1, FlightRecorder::y2;
QVector<FlightRecorder::Param*> FlightRecorder::params_vector;
FlightRecorder::CheckBox* FlightRecorder::checkbox = nullptr;
FlightRecorder::Scales* FlightRecorder::scales = nullptr;
FlightRecorder::Plots* FlightRecorder::plots = nullptr;

// CHECKBOX
void FlightRecorder::CheckBox::addnew()
{
    QCheckBox *newCheckBox = new QCheckBox(params_vector.back()->name, this);
    newCheckBox->setStyleSheet("color: " + params_vector.back()->color.name());
    // newCheckBox->setChecked(true);
    checkbox_vector.push_back(newCheckBox);
    layout->addWidget(checkbox_vector.back());
}

void FlightRecorder::CheckBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter checkbox_painter(this);
    m_width = width()-spacing; m_height = height()-spacing;
    QRect r(0, 0, m_width, m_height );
    checkbox_painter.drawRect(r);
}

// SCALES
void FlightRecorder::Scales::initScalesGeometry()
{
    m_width = width()-spacing; m_height = height()-spacing;

    ry = m_height/4;
    rx = w/200;

    for (int i = 0; i < 4; i++)
        sections[i] = QRect(0, ry*i, m_width , ry);
}

void FlightRecorder::Scales::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter scales_painter(this);
    scales_painter.drawRects(sections, 4);
    draw_scales(&scales_painter);
}

void FlightRecorder::Scales::draw_scales(QPainter *scales_painter)
{
    for (int i = 0; i < NParams; i++)
    {
        if (checkbox->checkbox_vector[i]->isChecked())
        {
            scales_painter->save();
            {
                _x = m_width-m_width/3*(i%3)-spacing;
                y1 = spacing*2+ry*params_vector[i]->section;
                y2 = ry*(params_vector[i]->section+1)-spacing;

                scales_painter->setPen(params_vector[i]->color);
                scales_painter->drawLine(_x, y1, _x, y2);
                scales_painter->drawLine(_x, y1, _x-rx, y1);
                scales_painter->drawText(_x-rx, y1-spacing/2, params_vector[i]->abbreviation);

                for (int j = 0; j < 11; j++)
                {
                    float dy = float(y2-y1)/10*(j);
                    scales_painter->drawLine(_x, y1+dy, _x-rx, y1+dy);
                    scales_painter->drawText(_x-rx*4, y1+dy, QString::number(params_vector[i]->divisions[j]));
                }
            }
            scales_painter->restore();
        }
    }
}

// PLOTS
void FlightRecorder::Plots::initPlotsGeometry()
{
    m_width = width()-spacing; m_height = height()-spacing;

    ry = m_height/4;
    rx = w/200;

    for (int i = 0; i < 4; i++)
        sections[i] = QRect(0, ry*i, m_width , ry);
}

void FlightRecorder::Plots::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter plots_painter(this);
    plots_painter.drawRects(sections, 4);
    draw_graph(&plots_painter);
}

void FlightRecorder::Plots::draw_graph(QPainter *plots_painter)
{
    for (int par = 0; par < NParams; par++)
    {
        graph[par].push_back(*params_vector[par]->p_param);

        if (graph[par].size() > max_points)
            graph[par].pop_front();

        if (checkbox->checkbox_vector[par]->isChecked())
        {
            plots_painter->save();
            {
                float ratio = (m_height/4 - spacing*3) / (params_vector[par]->max - params_vector[par]->min);

                plots_painter->setClipRect(sections[params_vector[par]->section]);
                plots_painter->scale(1, -1);
                plots_painter->translate(0, -m_height/4 * (params_vector[par]->section+1) - params_vector[par]->min * ratio + spacing);
                plots_painter->setPen(params_vector[par]->color);

                for (int i = 0; i < graph[par].size()-1; ++i)
                {
                    plots_painter->drawLine(
                        dx * (i+1),
                        graph[par][i+1] * ratio,
                        dx * i,
                        graph[par][i] * ratio
                    );
                }
            }
            plots_painter->restore();
        }
    }
}
