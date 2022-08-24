#include "checkbox.h"

CheckBox::CheckBox(FlightRecorder *FR)
{
    fr = FR;

    layout = new QVBoxLayout(this);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(fr->getSpacing(), 0, 0, 0);
    layout->setAlignment(Qt::AlignCenter);
    setLayout(layout);
}

CheckBox::~CheckBox()
{
    for (auto c : checkbox_vector)
        delete c;
    checkbox_vector.clear();
    delete layout;
}

void CheckBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter checkbox_painter(this);
    QRect r(0, 0, m_width, m_height);
    checkbox_painter.drawRect(r);
}

void CheckBox::initCheckboxGeometry()
{
    m_width = width() - fr->getSpacing();
    m_height = height() - fr->getSpacing();
}

void CheckBox::addParam()
{
    QCheckBox *newCheckBox = new QCheckBox(fr->getParam(fr->getCount()-1)->name, this);
    newCheckBox->setStyleSheet("color: " + fr->getParam(fr->getCount()-1)->color.name());
    newCheckBox->setFixedSize(m_width - fr->getSpacing(), m_height / (fr->getSubPlots() * 3));

    if (fr->getChecked())
        newCheckBox->setChecked(true);

    checkbox_vector.push_back(newCheckBox);
    layout->addWidget(checkbox_vector.back(), 0, Qt::AlignCenter);
}

void CheckBox::deleteParam(int id)
{
    QLayoutItem *item;
    item = layout->takeAt(id);
    delete item->widget();
    delete item;
    checkbox_vector.remove(id);
}
