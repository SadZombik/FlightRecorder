#include "scales.h"

Scales::Scales(FlightRecorder *FR)
{
    fr = FR;
    sections.resize(fr->getSubPlots());
}

void Scales::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter scales_painter(this);
    scales_painter.drawRects(sections);
    draw_scales(&scales_painter);
}

void Scales::initScalesGeometry()
{
    m_width = width() - fr->getSpacing();
    m_height = height() - fr->getSpacing();

    ry = m_height/fr->getSubPlots();
    rx = fr->getWidth() / 200;

    for (int i = 0; i < fr->getSubPlots(); i++)
        sections[i] = QRect(0, ry*i, m_width , ry);
}

void Scales::draw_scales(QPainter *scales_painter)
{
    for (int i = 0; i < fr->getCount(); i++)
    {
        if (fr->getCheckBox(i))
        {
            scales_painter->save();
            {
                _x = m_width - m_width / 3 * (i % 3) - fr->getSpacing() * 2;
                y1 = fr->getSpacing() * 2 + ry * fr->getParam(i)->section;
                y2 = ry * (fr->getParam(i)->section + 1) - fr->getSpacing();

                scales_painter->setPen(fr->getParam(i)->color);
                scales_painter->drawLine(_x, y1, _x, y2);
                scales_painter->drawLine(_x, y1, _x-rx, y1);
                scales_painter->drawText(_x-rx, y1-fr->getSpacing() / 2, fr->getParam(i)->abbreviation);

                for (int j = 0; j < 11; j++)
                {
                    float dy = float(y2-y1)/10*(j);
                    scales_painter->drawLine(_x, y1+dy, _x-rx, y1+dy);
                    scales_painter->drawText(_x-rx*4, y1+dy, QString::number(fr->getParam(i)->divisions[j]));
                }
            }
            scales_painter->restore();
        }
    }
}
