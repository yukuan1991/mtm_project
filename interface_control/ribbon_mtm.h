#pragma once
#include "ribbon.h"


class ribbon_mtm : public ribbon
{
    Q_OBJECT
signals:
    void cut();
    void copy();
    void paste();
    void del();
    void add_row();
    void help();
public:
    ribbon_mtm(QWidget * parent = nullptr);
private:
    ribbon_tool *cut_, *copy_, *paste_, *del_;
    ribbon_tool *add_row_;
    ribbon_tool *help_;
};

