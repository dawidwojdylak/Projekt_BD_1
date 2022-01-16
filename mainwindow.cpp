#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_db = new Database();

    connect(m_db, &Database::emit_log, this, &MainWindow::catch_log);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::catch_log(const QString text)
{
    ui->appOstream->insertPlainText(text);
    ui->appOstream->verticalScrollBar()->setValue(ui->appOstream->verticalScrollBar()->maximum());
}


void MainWindow::on_pushButton_connect_clicked()
{
//    m_db->connect();
    QString log;
    m_db->connect();
    ui->appOstream->insertPlainText(QString(log));
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

//    qDebug() << rows << ' ' << cols;

    ui->tableWidget->setColumnCount(res.columns());
    ui->tableWidget->setRowCount(rows);

    if (rows == 0 or cols == 0)
    {
        catch_log("Empty table\n");
    }

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

