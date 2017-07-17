#include "mtm_main.h"
#include "ui_mtm_main.h"

mtm_main::mtm_main(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mtm_main)
{
    ui->setupUi(this);
}

mtm_main::~mtm_main()
{
    delete ui;
}
