#include "mtm_widget.h"
#include "ui_mtm_widget.h"

mtm_widget::mtm_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mtm_widget)
{
    ui->setupUi(this);
}

mtm_widget::~mtm_widget()
{
    delete ui;
}
