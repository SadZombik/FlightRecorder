#include "flightrecorder.h"
#include "fr_controls.h"
#include "checkbox.h"
#include "scales.h"
#include "plots.h"

FlightRecorder::FlightRecorder(quint16 width, quint16 height)
{
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

    fpar = new FParam;
    ipar = new IParam;

    layout = new QHBoxLayout(this);
    layout->setSpacing(spacing);
    layout->setContentsMargins(spacing,spacing,0,0);
    setLayout(layout);

    checkbox = new CheckBox(this);
    checkbox->setFixedSize(w*0.1, h);
    checkbox->initCheckboxGeometry();
    layout->addWidget(checkbox);

    plots = new Plots(this);
    plots->setFixedSize(w*0.75, h);
    plots->initPlotsGeometry();
    layout->addWidget(plots);

    scales = new Scales(this);
    scales->setFixedSize(w*0.15, h);
    scales->initScalesGeometry();
    layout->addWidget(scales);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    this->show();
    checkbox->show();
    plots->show();
    scales->show();

    ini = new QSettings("fr_config.ini", QSettings::IniFormat);
    read_config();
    move(move_x, move_y);
    setSubPlots(NParams);
}

FlightRecorder::~FlightRecorder()
{
    stop();

    for (auto p : params_vector)
        delete p;
    params_vector.clear();

    delete ini;
    delete plots;
    delete scales;
    delete checkbox;
    delete layout;
}

bool FlightRecorder::getCheckBox(int id) const
{
    return checkbox->checkbox_vector[id]->isChecked();
}

int* FlightRecorder::getMoveControls() const
{
   static int arr[] = {c_move_x, c_move_y};
   return arr;
}

const FlightRecorder::Param* FlightRecorder::getParam(int id)
{
    return params_vector[id];
}

void FlightRecorder::setSubPlots(const unsigned int sp)
{
    sub_plots = sp;

    scales->sections.resize(sp);
    plots->sections.resize(sp);

    checkbox->initCheckboxGeometry();
    scales->initScalesGeometry();
    plots->initPlotsGeometry();
}

void FlightRecorder::read_config()
{
    ini->beginGroup("POSITION");
    {
        move_x = ini->value("move_x").toInt();
        move_y = ini->value("move_y").toInt();
        c_move_x = ini->value("controls_move_x").toInt();
        c_move_y = ini->value("controls_move_y").toInt();
    }
    ini->endGroup();

    int size = ini->beginReadArray("PARAMS");
    {
        for (int i = 0; i < size; i++)
        {
            ini->setArrayIndex(i);
            config_list.push_back(ini->value("id").toInt());
            addParam(
                ini->value("name").toString(),
                ini->value("abr").toString(),
                fpar->getElement(config_list[i]),
                ini->value("subplot").toInt(),
                ini->value("min").toFloat(),
                ini->value("max").toFloat(),
                ini->value("rad_to_deg").toBool(),
                QColor(ini->value("color").toString())
            );
        }
    }
    ini->endArray();
}

void FlightRecorder::saveConfig()
{
    ini->beginWriteArray("PARAMS");
    {
        for (int i = 0; i < NParams; i++)
        {
            ini->setArrayIndex(i);
            ini->setValue("id", config_list[i]);
            ini->setValue("name", params_vector[i]->name);
            ini->setValue("abr", params_vector[i]->abbreviation);
            ini->setValue("subplot", params_vector[i]->section);
            ini->setValue("min", QString::number(params_vector[i]->min));
            ini->setValue("max", QString::number(params_vector[i]->max));
            ini->setValue("color", QString(params_vector[i]->color.name()));
            ini->setValue("rad_to_deg", params_vector[i]->rad_to_deg);
        }
    }
    ini->endArray();
}

void FlightRecorder::addParam(
    const QString &name,
    const QString &abbreviation,
    float *param_ptr,
    const quint16 section,
    const float min,
    const float max,
    const bool rad_to_deg,
    QColor color
)
{
    int sections_check = 0;
    for (auto param : params_vector)
        if (param->section == section) { sections_check++; }

    if (sections_check < 3)
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
        newParam->param_ptr = param_ptr;
        newParam->section = section;
        newParam->color = color;
        newParam->min = min;
        newParam->max = max;
        newParam->rad_to_deg = rad_to_deg;

        float d = static_cast<float>(max - min) / 10;
        for (int i = 0; i < 11; i++)
            newParam->divisions[i] = max - d * i;

        params_vector.push_back(newParam);
        checkbox->addParam();
        plots->addNew();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Максимум 3 графика в одной секции");
    }
}

void FlightRecorder::deleteParam(int id)
{
    NParams--;
    params_vector.remove(id);
    checkbox->deleteParam(id);
}
