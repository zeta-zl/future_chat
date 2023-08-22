#pragma once

#include <QtWidgets/QWidget>
#include "ui_QtWidgetsApplication3.h"

class QtWidgetsApplication3 : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsApplication3(QWidget *parent = Q_NULLPTR);

private:
    Ui::QtWidgetsApplication3Class *ui;
};
