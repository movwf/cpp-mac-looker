#include "ui_mainwindow.h"
#include "vendor_search.h"
#include "mainwindow.h"
#include "classes.h"
#include "helpers.h"
#include "about.h"

#include <QtConcurrent>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringRef>
#include <QHostInfo>
#include <iostream>
#include <QFuture>
#include <QRegExp>
#include <QList>
#include <QDir>




// Create about page object
about *aboutPage;

// Get directory
QDir dir;
// Load mac vendor data for global scope
QFuture<QJsonArray> vendorData = QtConcurrent::run(helpers::readFile,QString(dir.dirName()+"/data.json"));
// Scan local computers
QFuture<QList<QString>> localScanResult = QtConcurrent::run(helpers::getNetworkUsers,helpers::findMyIp());

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Set your ip to input when loaded
    ui->ipInput->setText(helpers::findMyIp());
    // Initialize vendor search page
    vendorSearchPage = new vendor_search(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_closeButton_clicked()
{
    // Close application when close button clicked
    MainWindow::close();
}

void MainWindow::on_actionExit_triggered()
{
    // Close application when Exit menu item triggered
    MainWindow::close();
}

void MainWindow::on_readButton_clicked()
{
    NetworkInformation *myNetworkData = new NetworkInformation;
    // Print IP Address
    ui-> resultPrompt -> append(myNetworkData->getMyIp());

    // Print Mac Address
    ui-> resultPrompt -> append(myNetworkData->getMyMacAddress());

    // Print Mac Address Vendor
    ui-> resultPrompt -> append(myNetworkData->getMyMacVendorName(vendorData));


    // List All Available Network Computers
    ui-> resultPrompt -> append("\nLocal Available Computers");
    ui-> resultPrompt -> append("===========================\n");

    foreach(QString item,localScanResult.result())
    {
        // Get mac address by ip for scan results
        QFuture<QString> itemMacAddress = QtConcurrent::run(helpers::getMacAddressByIp,QString(item.split(QRegExp("\\s+"))[0]));

        // Append Mac Addresses of local ips
        ui->resultPrompt->append(item + "- Mac : " + itemMacAddress);
    }
}


void MainWindow::on_searchButton_clicked()
{
    QString searchIP = ui->ipInput->text();

    // Get mac address by IP

    ui-> macAddressInput -> setText(helpers::getMacAddressByIp(searchIP));

    // Get mac vendor by mac address;

    QString macAddress = ui-> macAddressInput -> text();
    QJsonObject obj = helpers::findValueFromJsonArray(vendorData, "oui", macAddress.left(8).toUpper());

    // Show it on the mac vendor input
    ui-> macVendorInput -> setText(obj.value("companyName").toString());
}


void MainWindow::on_actionVendor_Search_triggered()
{
    // Pass vendorData to search page
    vendorSearchPage->setData(vendorData);
    // Show vendor search page
    vendorSearchPage->show();
}

void MainWindow::on_actionAbout_triggered()
{
    // Show about page
    aboutPage = new about;
    aboutPage->show();
}
