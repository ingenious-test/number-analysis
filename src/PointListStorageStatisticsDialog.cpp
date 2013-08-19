#include "PointListStorageStatisticsDialog.h"

PointListStorageStatisticsDialog::PointListStorageStatisticsDialog(PointListStorageStatistics &statistics, QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* subLayout = new QHBoxLayout;

    text_ = new QTextEdit;
    text_->setPlainText(statistics.toString().join("\n"));
    okButton_ = new QPushButton("OK");


    subLayout->addStretch();
    subLayout->addWidget(okButton_);
    subLayout->addStretch();

    mainLayout->addWidget(text_);
    mainLayout->addLayout(subLayout);

    this->setLayout(mainLayout);

    connect(okButton_, SIGNAL(clicked()), this, SLOT(close()));
}
