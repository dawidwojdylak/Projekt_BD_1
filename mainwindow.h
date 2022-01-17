#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include "database.h"
#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void catch_log(const QString text);
    void onLoginOKClicked();
private slots:
    void on_pushButton_submit_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_logout_clicked();

private:
    Ui::MainWindow *ui;
//    std::unique_ptr<Database> m_db;
    Database * m_db;
    login * m_login;
    unsigned m_logCounter;

};
#endif // MAINWINDOW_H
