#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "vendor_search.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_closeButton_clicked();

    void on_actionExit_triggered();

    void on_readButton_clicked();

    void on_searchButton_clicked();

    void on_actionVendor_Search_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    vendor_search *vendorSearchPage;
};
#endif // MAINWINDOW_H
