#pragma once
#include <QNetworkInterface>
#include <QJsonParseError>
#include <QAbstractSocket>
#include <QApplication>
#include <QHostAddress>
#include <QJsonObject>
#include <QStringList>
#include <QJsonArray>
#include <QHostInfo>
#include <iostream>
#include <QProcess>
#include <QRegExp>
#include <QString>
#include <QList>
#include <QFile>

namespace helpers {

    // Read Json File into Array - async enabled
    extern QJsonArray readFile(QString fileName)
    {
        QFile file(fileName);
        QByteArray result;
        // Get file content if exists
        if(file.exists())
        {

            file.open(QIODevice::ReadOnly | QIODevice::Text);

            result = file.readAll();

            file.close();
        }

        QJsonParseError errorParseJson;
        QJsonDocument data = QJsonDocument::fromJson(result, &errorParseJson);
        QJsonObject obj = data.object();
        QJsonArray arr = obj.value("data").toArray();

        return arr;
    }

    // Get all network users - async enabled
    extern QList<QString> getNetworkUsers(QString IP)
    {
        QStringList ipParts = IP.split(".");

        QString network = ipParts[0] + "." + ipParts[1] + "." + ipParts[2] + ".";

        QList<QString> list;

        for(int i=0;i<255;i++)
        {
            QString currIp = (network+"%1").arg(i);
            QHostInfo HI = QHostInfo::fromName(currIp);
            if(currIp!=HI.hostName())
                list.append(currIp + " : " + HI.hostName());
        }
        return list;
    }

    // Json Array Search - Get object with right key-value pair
    QJsonObject findValueFromJsonArray(QJsonArray arr, QString key, QString val)
    {
        for (const auto obj : arr) {
            if (obj.toObject().value(key) == val)
                return obj.toObject();
        }
        return QJsonObject();
    }

    // Find my computer IP address
    QString findMyIp()
    {
        QString result = "0.0.0.0";
        QList<QHostAddress> list = QNetworkInterface::allAddresses();

         for(int nIter=0; nIter<list.count(); nIter++)
          {
              if(!list[nIter].isLoopback())
              {
                  if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol )
                  {
                    result = list[nIter].toString();
                  }
              }
          }
         return result;
    }

    // Find my computer MAC address
    QString getMyMacAddress()
    {
        foreach(QNetworkInterface netInterface, QNetworkInterface::allInterfaces())
        {
            // Return only the first non-loopback MAC Address
            if (!(netInterface.flags() & QNetworkInterface::IsLoopBack))
                return netInterface.hardwareAddress();
        }
        return QString();
    }

    // Find MAC address via local IP address
    QString getMacAddressByIp(QString IP)
    {
        QProcess pingProcess;

        QString exec = "arp";
        QStringList params;
        params << "-a" << IP;
        pingProcess.start(exec,params,QIODevice::ReadOnly);
        pingProcess.waitForFinished(-1);

        QString p_stdout = pingProcess.readAllStandardOutput();
        QString p_stderr = pingProcess.readAllStandardError();

        QString result = "No Match!";
        QStringList list = p_stdout.split(QRegExp("\\s+"));

        if(list[2]=="at")// Simple result control.
        {
            // Eq. /-0 user.local /-1 (192.168.1.12) /-2 at  /-3 00:00:00:00:00:00 /-4 [ether] /-5 on /-6 wlp0s18d0a1

            result = list[3]; // Mac Address Location
        }

        return result;
    }
}
