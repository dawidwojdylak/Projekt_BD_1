#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    m_db = std::make_unique<Database>(this);
    m_db = new Database();

    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(5);

//    QTableWidgetItem * newItem = new QTableWidgetItem(tr("%1").arg(row+1)*(column_1));




//    QObject::connect(m_db, &Database::log, this, &MainWindow::log);
    connect(m_db, &Database::emit_log, this, &MainWindow::catch_log);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::catch_log(const QString text)
{
    ui->appOstream->insertPlainText(text);
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
    m_db->sendQuery(query);
}

