#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//    void log(const QString text);

public slots:
    void catch_log(const QString text);
private slots:
    void on_pushButton_connect_clicked();
    void on_pushButton_submit_clicked();



private:
    Ui::MainWindow *ui;
//    std::unique_ptr<Database> m_db;
    Database * m_db;

};
#endif // MAINWINDOW_H
