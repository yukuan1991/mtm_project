#ifndef MTM_WIDGET_H
#define MTM_WIDGET_H

#include <QWidget>

namespace Ui {
class mtm_widget;
}

class mtm_widget : public QWidget
{
    Q_OBJECT

public:
    explicit mtm_widget(QWidget *parent = 0);
    ~mtm_widget();

private:
    Ui::mtm_widget *ui;
};

#endif // MTM_WIDGET_H
