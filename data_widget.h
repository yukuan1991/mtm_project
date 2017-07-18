﻿#ifndef DATA_WIDGET_H
#define DATA_WIDGET_H

#include <QWidget>
#include <memory>
#include "model/json_model.h"
#include "pts/pts_model.h"
#include "pts/pts_delegate.h"

class table_view;
class QStyledItemDelegate;
namespace Ui {
class data_widget;
}

class data_widget : public QWidget
{
    Q_OBJECT
signals:
    void line_exists (bool yes_or_no);
public:
    explicit data_widget(QWidget *parent = 0);
    ~data_widget();
public:
    void set_unit (double unit);

    void set_row (int num);
    void clear();
private:
    void set_view ();

private:
    table_view* view_;
    std::unique_ptr<json_model> result_model_ = pts_model::make (PTS::result);
    std::unique_ptr<QStyledItemDelegate> result_delegate_ {new pts_delegate};
private:
    Ui::data_widget *ui;
};

#endif // DATA_WIDGET_H
