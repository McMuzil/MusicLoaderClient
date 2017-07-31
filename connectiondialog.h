#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>

class ConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectionDialog(QWidget* parent = 0);
    ~ConnectionDialog();
    QString GetIP();
    QDialogButtonBox* buttonBox;
private:
    QLabel* label;
    QLineEdit* lineEdit; 
private slots:
    void CloseDialog();
};

#endif // CONNECTIONDIALOG_H
