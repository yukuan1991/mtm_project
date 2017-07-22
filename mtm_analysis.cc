#include "mtm_analysis.h"
#include "ui_mtm_analysis.h"
#include <QInputDialog>

mtm_analysis::mtm_analysis(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mtm_analysis)
{
    ui->setupUi(this);
}

mtm_analysis::~mtm_analysis()
{
    delete ui;
}

void mtm_analysis::set_task_count()
{
    QInputDialog dlg;
    dlg.setWindowTitle ("调整步数");
    dlg.setLabelText ("请输入工作步数");
    dlg.setOkButtonText ("确 定");
    dlg.setCancelButtonText ("取 消");
    dlg.setInputMode (QInputDialog::IntInput);
    dlg.setIntRange (0, 10000);

    if (dlg.exec () == QDialog::Accepted)
    {
        auto row = dlg.intValue ();
        ui->widget_data->clear ();
        ui->widget_data->set_row (row);

        current_file_data_.clear ();
    }
}

void mtm_analysis::init()
{
    ui->widget_data->set_unit(0.036);
}

void mtm_analysis::init_conn()
{
    connect (ui->widget_mtm, &mtm_widget::code_changed,
             ui->widget_data, &data_widget::add_code);

    connect (ui->widget_mtm, &mtm_widget::return_pressed,
             ui->widget_data, &data_widget::next_code);

    connect (ui->widget_data, &data_widget::std_time_sum,
             ui->widget_mtm, &mtm_widget::set_std_time_sum);
}

void mtm_analysis::set_measure_date(const QDate &date)
{
    ui->widget_mtm->set_measure_date(date);
}

QString mtm_analysis::measure_date() const
{
    return ui->widget_mtm->measure_date();
}

void mtm_analysis::set_measure_man(const QString &data)
{
    ui->widget_mtm->set_measure_man(data);
}

QString mtm_analysis::measure_man() const
{
    return ui->widget_mtm->measure_man();
}

void mtm_analysis::set_task_man(const QString &data)
{
    ui->widget_mtm->set_task_man(data);
}

QString mtm_analysis::task_man() const
{
    return ui->widget_mtm->task_man();
}
