#include "mtm_main.h"
#include "ui_mtm_main.h"
#include <QInputDialog>
#include <QDialog>

mtm_main::mtm_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mtm_main)
{
    ui->setupUi(this);
    init();
    init_conn();
}

mtm_main::~mtm_main()
{
    delete ui;
}

void mtm_main::init()
{
    ui->widget_data->set_unit(0.036);
}

void mtm_main::init_conn()
{
    connect(ui->widget_ribbon, &ribbon_mtm::file_menu_triggered,
            [this] (const QString & s) { file_operations(s); });

}

void mtm_main::file_operations(const QString &s)
{
    if(s == "新建")
    {
        file_new();
    }
    else if(s == "退出")
    {
        close();
    }
}

void mtm_main::file_new()
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
