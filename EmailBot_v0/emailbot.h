#ifndef EMAILBOT_H
#define EMAILBOT_H

#include <QMainWindow>
#include "SmtpMime"
QT_BEGIN_NAMESPACE
namespace Ui { class EmailBot; }
QT_END_NAMESPACE

class EmailBot : public QMainWindow
{
    Q_OBJECT

public:
    EmailBot(QWidget *parent = nullptr);
    ~EmailBot();

private slots:
    void on_send_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::EmailBot *ui;
    void err(QString &message);
};
#endif // EMAILBOT_H
