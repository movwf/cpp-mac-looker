#include "vendor_search.h"
#include "ui_vendor_search.h"
#include <QtConcurrent>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>
#include <QFuture>
#include <QDir>

QFuture<QJsonArray> macVendorData;

vendor_search::vendor_search(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::vendor_search)
{
    ui->setupUi(this);
}

vendor_search::~vendor_search()
{
    delete ui;
}

void vendor_search::setData(QFuture<QJsonArray> data)
{
    // Set vendor data via parent call
    macVendorData = data;
}


void vendor_search::on_searchButton_clicked()
{
    // Get mac address input value
    QString inputMac = ui-> macAddressInput->text();

    // Finalize array data
    QJsonArray test = macVendorData.result();

    // Search for mac address @ vendor data
    foreach(const QJsonValue item,test)
    {
        QJsonObject obj = item.toObject();
        if(obj.value("oui").toString()==QString(inputMac).left(8).toUpper())
        {
            // Print vendor name
            ui-> resultLabel-> setText(obj.value("companyName").toString());
        }
    }
}
