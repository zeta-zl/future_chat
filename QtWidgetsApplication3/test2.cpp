#include "test2.h"
#include "ui_test2.h"

test2::test2(QWidget *parent)
    : QWidget(parent)
{
    ui = new Ui::test2();
    ui->setupUi(this);
}

test2::~test2()
{
    delete ui;
}
