#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include "database.h"
#include "login.h"
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//    void updateTableList();
    void showTable(QString query);
    void insertIntoTable();

public slots:
    void catch_log(const QString text, bool red = false);
    void onLoginOKClicked();
private slots:
    void on_pushButton_submit_clicked();

    void on_pushButton_login_clicked();

    void on_pushButton_logout_clicked();


    void on_comboBox_table_currentIndexChanged(int index);

    void on_pushButton_input_clicked();

    void on_pushButton_save_clicked();



    void on_comboBox_tablestretch_activated(int index);

    void on_pushButton_ava_clicked();

    void on_pushButton_unav_clicked();

private:
    Ui::MainWindow *ui;
//    std::unique_ptr<Database> m_db;
    Database * m_db;
    login * m_login;
    unsigned m_logCounter;
    bool m_isAppendingData;

};
#endif // MAINWINDOW_H
