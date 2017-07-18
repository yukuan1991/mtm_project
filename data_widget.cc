#include "data_widget.h"
#include "ui_data_widget.h"
#include "view/table_view.h"
#include <QScrollBar>
#include <QDebug>

data_widget::data_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::data_widget)
{
    ui->setupUi(this);
    ui->table_result->setItemDelegate(result_delegate_.get());
    view_ = ui->table_result;
}

data_widget::~data_widget()
{
    delete ui;
}

void data_widget::set_unit(double unit)
{
    this->result_model_->setData (QModelIndex (), unit, Qt::UserRole + 100);
}

void data_widget::set_row(int num)
{
    emit line_exists (num != 0);

    result_model_->resize (static_cast<unsigned int>(num));
    ui->table_result->setModel(nullptr);
    ui->table_result->setModel(result_model_.get ());
}

void data_widget::clear()
{
    result_model_->clear ();
    ui->table_result->setModel (nullptr);
    ui->table_result->setModel (result_model_.get ());
}

void data_widget::set_view()
{
    view_->horizontalHeader ()->setSectionResizeMode (QHeaderView::Interactive);
    view_->verticalHeader ()->setSectionResizeMode (QHeaderView::Fixed);

    auto scroll = make_unique<QScrollBar> ();
    view_->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOn);
    connect (scroll.get (), &QScrollBar::valueChanged, [=] (int value)
    {
            view_->verticalScrollBar ()->setValue (value);
    });

    view_->setVerticalScrollBar (scroll.release ());
}
