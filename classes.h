#include "helpers.h"
#include <QtConcurrent>
#include <QApplication>
#include <QFuture>
#include <QString>

// Localhost Network Information Class
class NetworkInformation
{
//Variables
public:
    QString IP;
    QString error;
    QString macAddress;

    // Constructor
    NetworkInformation()
    {
        this->error = "Network Error!";
    }

    // Decstructor
    ~NetworkInformation();

//Functions
public:
    // Get my computer IP
    virtual QString getMyIp()
    {
        QString myIp = helpers::findMyIp();
        this->IP = myIp;

        return QString("Your IP : " + myIp);
    }

    // Get my MAC address
    virtual QString getMyMacAddress()
    {
        QString myMacAddress = helpers::getMyMacAddress();
        this->macAddress = myMacAddress;

        return QString("Your Mac Address : " + myMacAddress);
    }

    // Get my MAC vendor name
    virtual QString getMyMacVendorName(QJsonArray vendorData)
    {
        QJsonObject obj = helpers::findValueFromJsonArray(vendorData, "oui", macAddress.left(8));

        return QString("Your Mac Vendor : " + obj.value("companyName").toString());
    }
private:

};
