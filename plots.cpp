#include "plots.h"

Plots::Plots(FlightRecorder *FR)
{
    fr = FR;    
    sections.resize(fr->getSubPlots());
    graph.resize(fr->getCount());
}

void Plots::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter plots_painter(this);
    plots_painter.drawRects(sections);
    draw_plot(&plots_painter);
}

void Plots::initPlotsGeometry()
{
    m_width = width() - fr->getSpacing();
    m_height = height() - fr->getSpacing();

    ry = m_height / fr->getSubPlots();
    rx = fr->getWidth() / 200;

    for (int i = 0; i < fr->getSubPlots(); i++)
        sections[i] = QRect(0, ry*i, m_width , ry);

    fr->setMaxPoints(m_width/dx - 2);
}

void Plots::addNew()
{
    graph.resize(fr->getCount());
}

void Plots::draw_plot(QPainter *plots_painter)
{
    for (int par = 0; par < fr->getCount(); par++)
    {
        float new_value = fr->getParam(par)->rad_to_deg ?
                    *(fr->getParam(par)->param_ptr) * 57.2958 :
                    *(fr->getParam(par)->param_ptr);

        graph[par].push_back(new_value);

        if (graph[par].size() > fr->getMaxPoints())
            graph[par].pop_front();

        if (fr->getCheckBox(par))
        {
            plots_painter->save();
            {
                float ratio =
                    (m_height / fr->getSubPlots() - fr->getSpacing() * 3) /
                    (fr->getParam(par)->max - fr->getParam(par)->min);

                plots_painter->setClipRect(sections[fr->getParam(par)->section]);
                plots_painter->scale(1, -1);
                plots_painter->translate(
                    0, -m_height / fr->getSubPlots() *
                    (fr->getParam(par)->section+1) -
                    fr->getParam(par)->min * ratio +
                    fr->getSpacing()
                );
                plots_painter->setPen(fr->getParam(par)->color);

                for (int i = 0; i < graph[par].size()-1; i++)
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
