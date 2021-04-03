#ifndef VENDOR_SEARCH_H
#define VENDOR_SEARCH_H

#include <QMainWindow>
#include <QFuture>

namespace Ui { class vendor_search; }

class vendor_search : public QMainWindow
{
    Q_OBJECT

public:
    explicit vendor_search(QWidget *parent = nullptr);
    ~vendor_search();

public:
    void setData(QFuture<QJsonArray>);

private slots:
    void on_searchButton_clicked();

private:
    Ui::vendor_search *ui;


};

#endif // VENDOR_SEARCH_H
