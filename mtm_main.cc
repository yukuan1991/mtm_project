#include "mtm_main.h"
#include "ui_mtm_main.h"
#include <QInputDialog>
#include <QDialog>
#include "mtm_analysis.h"
#include <memory>
#include <QMdiSubWindow>
#include "interface_control/about_us_dlg.h"
#include <QDateEdit>

using namespace std;

mtm_main::mtm_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mtm_main)
{
    ui->setupUi(this);
    ui->mdi->setViewMode (QMdiArea::TabbedView);
//    init();
    init_conn();
    set_button_enabled();
}

mtm_main::~mtm_main()
{
    delete ui;
}

//void mtm_main::init()
//{
//}

void mtm_main::init_conn()
{
    connect(ui->widget_ribbon, &ribbon_mtm::file_menu_triggered,
            [this] (const QString & s) { file_operations(s); });

    connect(ui->widget_ribbon, &ribbon_mtm::measure_date, this, &mtm_main::on_measure_date);
    connect(ui->widget_ribbon, &ribbon_mtm::measure_man, this, &mtm_main::on_measure_man);
    connect(ui->widget_ribbon, &ribbon_mtm::task_man, this, &mtm_main::on_task_man);

    connect(ui->widget_ribbon, &ribbon_mtm::help, this, &mtm_main::help_advice);

    connect(ui->mdi, &QMdiArea::subWindowActivated, this, &mtm_main::set_button_enabled);

}

void mtm_main::set_button_enabled()
{
    const bool state = (active_window() != nullptr);
    ui->widget_ribbon->set_enabled(state);
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
    auto w = create_window ("未命名");
    w->set_task_count ();
}

void mtm_main::help_advice()
{
    const QString text = R"(<html><head/><body><p>如果您有任何需求与改进建议，</p><p>请随时联系IEToolkit君qq3350436646</p>
                         <p><span style=" font-weight:600; color:red">加好友请扫右边二维码---&gt;</span></p></body></html>)";
    const QString qr_code = R"( <a href = "www.shionto.com"> <img src="./png/about-us.png" width="300" height = "400"/></a>)";
    about_us_dlg::show_info(text, qr_code);
}

not_null<mtm_analysis *> mtm_main::create_window(const QString &title)
{
    auto mtm_win = make_unique<mtm_analysis> ();
    auto ptr_mtm_win = mtm_win.get();

    mtm_win->setAttribute (Qt::WA_DeleteOnClose);
    auto w = ui->mdi->addSubWindow (ptr_mtm_win);
    w->setWindowTitle (title);

    w->setWindowState (Qt::WindowMaximized);

    connect(ui->widget_ribbon, &ribbon_mtm::add_row, ptr_mtm_win, &mtm_analysis::add_row);
    connect(ui->widget_ribbon, &ribbon_mtm::copy, ptr_mtm_win, &mtm_analysis::copy);
    connect(ui->widget_ribbon, &ribbon_mtm::cut, ptr_mtm_win, &mtm_analysis::cut);
    connect(ui->widget_ribbon, &ribbon_mtm::paste, ptr_mtm_win, &mtm_analysis::paste);
    connect(ui->widget_ribbon, &ribbon_mtm::del, ptr_mtm_win, &mtm_analysis::del);

    return mtm_win.release ();
}

mtm_analysis *mtm_main::active_window()
{
    if(QMdiSubWindow* active_subwindow = ui->mdi->activeSubWindow())
    {
        mtm_analysis* w = dynamic_cast<mtm_analysis*>(active_subwindow->widget());
        return w;
    }
    else
    {
        return nullptr;
    }
}

void mtm_main::on_measure_date()
{
    auto w = active_window ();
    if (w == nullptr)
    {
        return;
    }

    QDialog dlg (this);

    auto edit = new QDateEdit (&dlg);
    edit->setCalendarPopup (true);
    edit->setDate (QDate::currentDate ());

    auto ok_button = new QPushButton (&dlg);
    ok_button->setText ("确定");

    auto layout = new QHBoxLayout;

    layout->addWidget (edit);
    layout->addWidget (ok_button);
    dlg.setLayout (layout);

    connect (ok_button, &QPushButton::clicked, &dlg, &QDialog::accept);
    const auto res = dlg.exec ();

    if (res != QDialog::Accepted)
    {
        return;
    }

    w->set_measure_date (edit->date ());
}

void mtm_main::on_measure_man()
{
    auto w = active_window ();
    if (w == nullptr)
    {
        return;
    }

    bool is_ok;
    const auto old_data = w->measure_man ();
    const auto data = QInputDialog::getText (this, "测量人", "测量人", QLineEdit::Normal, old_data, &is_ok);
    if (is_ok)
    {
        w->set_measure_man (data);
    }
}

void mtm_main::on_task_man()
{
    auto w = active_window ();
    if (w == nullptr)
    {
        return;
    }

    bool is_ok;
    const auto old_data = w->task_man ();
    const auto data = QInputDialog::getText (this, "作业员", "作业员", QLineEdit::Normal, old_data, &is_ok);

    if (is_ok)
    {
        w->set_task_man (data);
    }
}
