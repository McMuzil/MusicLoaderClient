#include "connectiondialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QRegExpValidator>

ConnectionDialog::~ConnectionDialog()
{
    delete lineEdit;
    delete label;
}

ConnectionDialog::ConnectionDialog(QWidget* parent)
{
    lineEdit = new QLineEdit(this);
    lineEdit->setPlaceholderText("192.168.2.1");
    lineEdit->setValidator(new QRegExpValidator(QRegExp( "[0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}[.][0-9]{1,3}" )));
    QPushButton* connectButton = new QPushButton("Connect");
    QPushButton* cancelButton = new QPushButton("Cancel");

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(connectButton, QDialogButtonBox::AcceptRole);
    buttonBox->addButton(cancelButton, QDialogButtonBox::RejectRole);

    connect(buttonBox, SIGNAL(rejected()), this, SLOT(CloseDialog()));

    QVBoxLayout* vBoxLayout = new QVBoxLayout;
    vBoxLayout->addWidget(lineEdit);
    vBoxLayout->addWidget(buttonBox);

    setLayout(vBoxLayout);
}

void ConnectionDialog::CloseDialog()
{
    this->close();
}

QString ConnectionDialog::GetIP()
{
    return lineEdit->text();
}


