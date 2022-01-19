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

    ui->queryInput->insertPlainText("SELECT * FROM ksiazka;");
    m_logCounter = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showTable(QString query)
{
    pqxx::result res = m_db->sendQuery(query);

    int cols = 0, rows = 0;
    for (const auto & row : res)
    {
        rows++;
        for (const auto & i : row)
            cols++;
    }

    if (rows == 0 or cols == 0)
    {
        catch_log("Empty table\n", true);
        return;
    }

    ui->tableWidget->setColumnCount(res.columns());
    ui->tableWidget->setRowCount(rows);



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

void MainWindow::insertIntoTable()
{

}

//void MainWindow::updateTableList()
//{
//    pqxx::result res = m_db->sendQuery("\d");
//    for (const auto & row : res)
//        for (const auto & i : row)
//            qDebug() << i.c_str();
//}

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
    if (m_db->isConnected())
        ui->comboBox_table->setEnabled(true);
//    updateTableList();
}



void MainWindow::on_pushButton_submit_clicked()
{
    QString query = ui->queryInput->toPlainText();
    if (query.split(" ").at(0) == "INSERT" or query.split(" ").at(0) == "insert")
        m_db -> sendQuery(query, true);
    else
        showTable(query);
}


void MainWindow::on_pushButton_login_clicked()
{
    m_login->show();
}


void MainWindow::on_pushButton_logout_clicked()
{
    m_db->disconnect();
}

void MainWindow::on_comboBox_table_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:
            m_db -> setSelectedTab("adres_czytelnika");
        break;
        case 1:
            m_db -> setSelectedTab("autor");
        break;
        case 2:
            m_db -> setSelectedTab("czytelnik");
        break;
        case 3:
            m_db -> setSelectedTab("e_czytnik");
        break;
        case 4:
            m_db -> setSelectedTab("karta_biblioteczna");
        break;
        case 5:
            m_db -> setSelectedTab("ksiazka");
        break;
        case 6:
            m_db -> setSelectedTab("\"plyta_CD\"");
        break;
        case 7:
            m_db -> setSelectedTab("plyta_film");
        break;
        case 8:
            m_db -> setSelectedTab("plyta_muzyka");
        break;
        case 9:
            m_db -> setSelectedTab("sztuka");
        break;
        case 10:
            m_db -> setSelectedTab("wydawnictwo");
        break;
        default:
            m_db -> setSelectedTab("");
        break;
    }
    showTable("SELECT * FROM " + m_db -> getSelectedTab() + ";");
}


void MainWindow::on_pushButton_input_clicked()
{
//    insertIntoTable();
    ui -> tableWidget -> setRowCount(ui->tableWidget->rowCount() + 1);
    ui -> pushButton_save -> setEnabled(true);
}


void MainWindow::on_pushButton_save_clicked()
{
    QRegularExpression re("\\d+");
    QString values = "";
    QString valNames = "";
    const int cols = ui->tableWidget->columnCount();
    for (int i = 0; i < cols; i++)
    {
        QString curVal = ui->tableWidget->model()->data(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1, i)).toString();
        if(re.match(curVal).hasMatch())
            values += curVal + " ";
        else
            values += "\'" + curVal + "\' ";

        valNames += ui->tableWidget->horizontalHeaderItem(i)->text() + " ";
    }

    QString query = "INSERT INTO " + m_db->getSelectedTab() + " (";
    for (int i = 0; i < cols - 1; i++)
        query += valNames.split(" ").at(i) + ", ";
    query += valNames.split(" ").at(cols - 1);
    query += ") VALUES (";
    for (int i = 0; i < cols - 1; i++)
        query += "" + values.split(" ").at(i) + ", ";
    query += "" + values.split(" ").at(cols - 1) + "";
    query += ");";
//    qDebug() << query;
    m_db->sendQuery(query, true);
    ui->pushButton_save->setDisabled(true);
//    catch_log("Data has been appended successfully");
}

