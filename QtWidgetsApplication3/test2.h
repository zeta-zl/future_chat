#pragma once

#include <QWidget>
namespace Ui { class test2; };

class test2 : public QWidget
{
    Q_OBJECT

public:
    test2(QWidget *parent = Q_NULLPTR);
    ~test2();

private:
    Ui::test2 *ui;
};
