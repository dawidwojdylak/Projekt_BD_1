#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_db = new Database();
    m_login = new login();

    connect(m_db, &Database::emit_log, this, &MainWindow::catch_log);
    connect(m_login, &login::emit_login_data, this, &MainWindow::onLoginOKClicked);

    ui->queryInput->insertPlainText("SELECT * FROM customer;");
    m_logCounter = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::catch_log(const QString text, bool red)
{
    if (red)
        ui->appOstream->setTextColor(Qt::red);
    ui->appOstream->insertPlainText(QString::number(++m_logCounter) + ": " + text);
    ui->appOstream->verticalScrollBar()->setValue(ui->appOstream->verticalScrollBar()->maximum());
    ui->appOstream->setTextColor(Qt::black);
}

void MainWindow::onLoginOKClicked()
{
    m_db->setDBName(QString::fromStdString(m_login->getDBName()));
    m_db->setUserName(QString::fromStdString(m_login->getUserName()));
    m_db->setPasswd(QString::fromStdString(m_login->getPasswd()));
    m_db->setHostAddress(QString::fromStdString(m_login->getHostAddress()));
    m_db->setPort(QString::fromStdString(m_login->getPort()));

    m_db->connect();
}



void MainWindow::on_pushButton_submit_clicked()
{
    QString query = ui->queryInput->toPlainText();

    pqxx::result res = m_db->sendQuery(query);

    int cols = 0, rows = 0;
    for (const auto & row : res)
    {
        rows++;
        for (const auto & i : row)
            cols++;
    }



    ui->tableWidget->setColumnCount(res.columns());
    ui->tableWidget->setRowCount(rows);

    if (rows == 0 or cols == 0)
    {
        catch_log("Empty table\n", true);
    }

    QStringList labels;
    for (unsigned i = 0; i < res.columns(); i++)
        labels << res.column_name(i);

    ui->tableWidget->setHorizontalHeaderLabels(labels);

    rows = 0;
    for (const auto & row : res)
    {
        cols = 0;
        for (const auto & i : row)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(QString(i.c_str()));
            ui->tableWidget->setItem(rows, cols, newItem);
            cols++;
        }
        rows++;
    }
}


void MainWindow::on_pushButton_login_clicked()
{
    m_login->show();
}


void MainWindow::on_pushButton_logout_clicked()
{
    m_db->disconnect();
}

