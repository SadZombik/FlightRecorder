#include "fr_controls.h"

FR_Controls::FR_Controls(quint16 w, quint16 h, FlightRecorder *FR, QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Controls");
    resize(w, h);

    fr = FR;
    move(fr->getMoveControls()[0], fr->getMoveControls()[1]);

    cw.reset(new ControlWidget);

    // Синхронизация
    for (int i = 0; i < fr->getCount(); i++)
    {
        cw->getList()->push_back(fr->getParam(i)->abbreviation);
    }

    layout_buttons = new QVBoxLayout();
    layout_buttons->setSpacing(0);
    layout_buttons->setContentsMargins(0,0,0,0);

    layout = new QHBoxLayout(this);
    layout->addLayout(layout_buttons);
    setLayout(layout);

    btn_add     = new QPushButton("Add", this);
    btn_delete  = new QPushButton("Delete", this);
    btn_clear   = new QPushButton("Clear", this);
    btn_save    = new QPushButton("Save", this);
    btn_close   = new QPushButton("Close", this);

    btn_add->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn_delete->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn_clear->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn_save->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    btn_close->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    layout_buttons->addWidget(btn_add);
    layout_buttons->addWidget(btn_delete);
    layout_buttons->addWidget(btn_clear);
    layout_buttons->addWidget(btn_save);
    layout_buttons->addWidget(btn_close);

    connect(btn_add, &QPushButton::clicked, this, [this]()
    {
        cw.reset(new AddWidget);
        layout->addWidget(cw.get());
        showParamWidget();
    });
    connect(btn_delete, &QPushButton::clicked, this, [this]()
    {
        cw.reset(new DeleteWidget);
        layout->addWidget(cw.get());
        showParamWidget();
    });
    connect(btn_clear, &QPushButton::clicked, this, [this]()
    {
        cw.reset(new ControlWidget);
        while(fr->getCount())
            fr->deleteParam();
        fr->setSubPlots(1);
    });
    connect(btn_save, &QPushButton::clicked, this, [this]()
    {
        fr->saveConfig();
    });
    connect(btn_close, &QPushButton::clicked, this, []()
    {
        QApplication::closeAllWindows();
    });
    show();
}

FR_Controls::~FR_Controls()
{
    delete btn_save;
    delete btn_clear;
    delete btn_delete;
    delete btn_add;
    delete layout_buttons;
    delete layout;
}

void FR_Controls::showParamWidget()
{
    connect(cw.get(), &ControlWidget::ready_add, this, [this]()
    {
        if (fr->getSubPlots() < cw->getSubPlotIndex() + 1)
            fr->setSubPlots(cw->getSubPlotIndex() + 1);

        fr->addParam(
            cw->getName(cw->getIndex()),
            cw->getAbbrevation(cw->getIndex()),
            fr->fpar->getElement(cw->getIndex()),
            cw->getSubPlotIndex(),
            cw->getMin(),
            cw->getMax(),
            cw->getRadToDegCheck()
        );
        fr->saveParamId(cw->getIndex());
    });
    connect(cw.get(), &ControlWidget::ready_delete, this, [this]()
    {
        if (fr->getCount())
            fr->deleteParam(cw->getIndex());
    });
}
