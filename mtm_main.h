#ifndef MTM_MAIN_H
#define MTM_MAIN_H

#include <QWidget>

namespace Ui {
class mtm_main;
}

class mtm_main : public QWidget
{
    Q_OBJECT

public:
    explicit mtm_main(QWidget *parent = 0);
    ~mtm_main();

private:
    Ui::mtm_main *ui;
};

#endif // MTM_MAIN_H
