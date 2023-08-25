#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QString name, int id, QWidget *parent = nullptr);
    ~login();

private:
    Ui::login *ui;
    QVector<bool> IsShow;
    int clientid;
    QString clientname;
};

#endif // LOGIN_H
