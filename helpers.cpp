#include <QJsonArray>
#include <QJsonObject>
#include <QString>

QJsonObject findValueFromJsonArray(QJsonArray arr, QString key, QString val) {
    for (const auto obj : arr) {
        if (obj.toObject().value(key) == val)
            return obj.toObject();
    }
    return QJsonObject();
}
