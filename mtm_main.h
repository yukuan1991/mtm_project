#ifndef MTM_MAIN_H
#define MTM_MAIN_H

#include <QWidget>
#include "Qt-Utils/json.hpp"


namespace Ui {
class mtm_main;
}

using nlohmann::json;

class mtm_main : public QWidget
{
    Q_OBJECT

public:
    explicit mtm_main(QWidget *parent = 0);
    ~mtm_main();
private:
    void init();
    void init_conn();
private:
    void file_operations(const QString& s);
    void file_new();

private:
    Ui::mtm_main *ui;
    json current_file_data_;

};

#endif // MTM_MAIN_H
