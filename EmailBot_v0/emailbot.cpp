#include "emailbot.h"
#include "ui_emailbot.h"
#include "SmtpMime"
#include <QErrorMessage>
#include <iostream>
#include <QMessageBox>
#include <QFileDialog>
EmailBot::EmailBot(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EmailBot)
{
    ui->setupUi(this);
    ui->username->setPlaceholderText("Your Email Account");
    ui->Password->setEchoMode(QLineEdit::EchoMode::Password);
    ui->Password->setText("your password");

}

EmailBot::~EmailBot()
{
    delete ui;
}




void EmailBot::on_send_clicked()
{
    SmtpClient smtp("smtp.gmail.com",465,SmtpClient::SslConnection);
    QString user=ui->username->text();
    EmailAddress sender=user;
    QString password = ui->Password->text();

    MimeMessage message;
    message.setSender(sender);
    message.setSubject(ui->Subject->text());
    QString html=ui->Text->toHtml();
    MimeHtml content;
    content.setHtml(html);

    message.addPart(&content);
    message.addRecipient(ui->Recipient->text());
    QList <QFile*> files;
    QList <MimeAttachment *> attackments;
    for (int i=0; i<ui->attchments->count();++i )
    {
        QFile *file=new QFile(ui->attchments->item(i)->text());
        MimeAttachment *att=new MimeAttachment(file);
        files.append(file);
        attackments.append(att);
        message.addPart(att);

    }

    smtp.connectToHost();
    if (!smtp.waitForReadyConnected())
    {
        QString error = QString("sorry we couldn't connect");
        err(error);

        return ;
    }

    smtp.login(user,password);
    if (!smtp.waitForAuthenticated())
    {
        QString error = QString("sorry we couldn't authenicate");
        err(error);

        return ;

    }
        smtp.sendMail(message);

    if (!smtp.waitForMailSent())
    {
        QString error = QString("sorry we couldn't send");
        err(error);

        return ;
    }


else {
        QMessageBox suc;
        suc.setText("The email was succesfully sent.");
        suc.exec();
}
    smtp.quit();
    for (auto &d: files)
        delete d;
for (auto &d: attackments)
{
    delete d;
}



}

void EmailBot:: err(QString &msg)
{
    QErrorMessage error;
    error.showMessage(msg);
    error.exec();

}


void EmailBot::on_pushButton_2_clicked()
{
    QFileDialog dial;
    dial.setFileMode(QFileDialog::FileMode::ExistingFile);
    if (dial.exec())
    {
        ui->attchments->addItems(dial.selectedFiles());

    }

}

