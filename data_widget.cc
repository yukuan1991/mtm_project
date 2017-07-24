#include "data_widget.h"
#include "ui_data_widget.h"
#include "view/table_view.h"
#include <QScrollBar>
#include <QMessageBox>
#include <QDebug>

data_widget::data_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::data_widget)
{
    ui->setupUi(this);
    ui->table_result->setItemDelegate(result_delegate_.get());
    view_ = ui->table_result;
    set_view();

    connect(result_model_.get(), &pts_model::dataChanged,
            [this] { auto sum = get_std_time_sum(); emit std_time_sum(sum); });
}

data_widget::~data_widget()
{
    delete ui;
}

QString data_widget::get_std_time_sum() const
{
    auto col = 5;
    double sum = 0;
    for (int row = 0; row < static_cast<int>(result_model_->size ()); ++row)
    {
        auto pos = result_model_->index (row, col);
        auto vat = result_model_->data (pos);
        if (vat.isNull ())
        {
            continue;
        }
        else
        {
            auto time = vat.toDouble ();
            sum += time;
        }
    }
    return QString::number(sum, 'f', 2);
}

void data_widget::add_code(const QVariant &code)
{
    if (result_model_->size() <= 0)
    {
        QMessageBox::information (this, "代码", "请新建一个表格");
        return;
    }

    if (view_ == nullptr or view_->selectionModel()->selectedIndexes ().empty ())
    {
        QMessageBox::information (this, "代码", "请选中一个表格");
        return;
    }

    assert (view_);

    auto list = view_->selectionModel ()->selectedIndexes ();
    decltype (list) code_list;

    for (auto& index : list)
    {
        auto variant = index.model ()->headerData (index.column (), Qt::Horizontal, Qt::DisplayRole);
        QString header = variant.toString ();
        if (header == "代码")
        {
            code_list.append (index);
        }
    }

    if (code_list.empty ())
    {
        QMessageBox::information (this, "代码", "请选中代码这一列");
        return;
    }

    auto min_row = 99999;
    auto min_row_index = -1;
    for (int i = 0; i < code_list.size (); i++)
    {
        if (code_list[i].row () < min_row)
        {
            min_row_index = i;
            min_row = code_list[i].row ();
        }
    }
    assert (min_row_index != -1 and min_row_index < code_list.size ());

    view_->model ()->setData (code_list[min_row_index], code);

//    auto sum = get_std_time_sum();
//    qDebug() << sum;
//    emit std_time_sum(sum);
}

void data_widget::set_unit(double unit)
{
    this->result_model_->setData (QModelIndex (), unit, Qt::UserRole + 100);
}

void data_widget::next_code()
{
    if (view_ == nullptr or view_->model () == nullptr)
    {
        return;
    }

    auto list_index = view_->selectionModel ()->selectedIndexes ();


    QModelIndex code_index;
    for (auto& it : list_index)
    {
        auto variant = it.model ()->headerData (it.column (), Qt::Horizontal, Qt::DisplayRole);
        QString header = variant.toString ();
        if (header == "代码")
        {
            code_index = it;
            break;
        }
    }


    if (!code_index.isValid () or code_index.row () >= code_index.model ()->rowCount () - 1)
    {
        return;
    }

    auto next_index = view_->model ()->index (code_index.row () + 1, code_index.column ());
    view_->scrollTo(next_index);
    assert (next_index.isValid ());

    view_->clearSelection ();
    view_->selectionModel ()->select (next_index, QItemSelectionModel::Select);
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

void data_widget::on_cut()
{
    if (view_ != nullptr)
    {
        view_->on_copy_del (table_view::OPERATION_COPY | table_view::OPERATION_DEL);
    }
}

void data_widget::on_copy()
{
    if (view_ != nullptr)
    {
        view_->on_copy_del (table_view::OPERATION_COPY);
    }
}

void data_widget::on_paste()
{
    if (view_ != nullptr)
    {
        view_->on_paste ();
    }
}

void data_widget::on_del()
{
    if (view_ != nullptr)
    {
        view_->on_copy_del (table_view::OPERATION_DEL);
    }
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
