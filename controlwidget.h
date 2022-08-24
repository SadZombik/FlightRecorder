#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>

class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    ControlWidget(quint16 width = 0, quint16 height = 0);
    virtual ~ControlWidget();

    QList<QString> *getList() { return &selected_list; }
    int getCount() const { return selected_list.size(); }
    int getIndex() const { return cw_index; }
    quint16 getSubPlotIndex() const { return sub_plot_index; }
    QString getName(int id) const { return name_list[id]; }
    QString getAbbrevation(int id) const { return abbrevation_list[id]; }
    float getMin() const { return static_cast<float>(min_edit.value()); }
    float getMax() const { return static_cast<float>(max_edit.value()); }
    bool getRadToDegCheck() const { return rad_to_deg_cb.isChecked(); }

public slots:
    void set_index(int);

signals:
    void ready_add();
    void ready_delete();

private:
    quint16 w, h;

protected:
    int cw_index = 0;
    quint16 sub_plot_index = 0;

    QVBoxLayout *layout;
    QComboBox *cb;
    QPushButton *btn;
    QSpinBox min_edit;
    QSpinBox max_edit;
    QCheckBox rad_to_deg_cb;

    QList<QString> name_list;
    QList<QString> abbrevation_list;
    static QList<QString> selected_list;
};

class AddWidget : public ControlWidget
{
    Q_OBJECT
public:
    AddWidget(quint16 width = 400, quint16 height = 300);
    virtual ~AddWidget();

private slots:
    void add_param();
    void set_sub_plot_index(int);

private:
    QLabel name_label;
    QLabel abr_label;
    QLabel min_label;
    QLabel max_label;
    QLabel subplot_label;

    QComboBox *sub_plot;
    void parse();
};

class DeleteWidget : public ControlWidget
{
    Q_OBJECT
public:
    DeleteWidget(quint16 width = 400, quint16 height = 150);
    virtual ~DeleteWidget();

private slots:
    void delete_param();
};

#endif // CONTROLWIDGET_H
