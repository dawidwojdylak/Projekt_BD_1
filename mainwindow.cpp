#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_isAppendingData(false)
{
    ui->setupUi(this);

    m_db = new Database();
    m_login = new login();

    connect(m_db, &Database::emit_log, this, &MainWindow::catch_log);
    connect(m_login, &login::emit_login_data, this, &MainWindow::onLoginOKClicked);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::onAboutClicked);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::onExitClicked);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->queryInput->insertPlainText("SELECT * FROM ksiazka;");
    m_logCounter = 0;
    setWindowTitle("Bazy Danych - Projekt - Dawid Wojdylak");
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
//        return;
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
    {
        ui->comboBox_table->setEnabled(true);
        ui->pushButton_ava->setEnabled(true);
        ui->pushButton_unav->setEnabled(true);
        ui->pushButton_input->setEnabled(true);
        on_comboBox_table_currentIndexChanged(0);
    }

    //    updateTableList();
}

void MainWindow::onAboutClicked() const
{
    QMessageBox msg;
    msg.setWindowTitle("Info");
    msg.setText("Bazy danych\nProjekt - Biblioteka\nDawid Wojdylak, 2022");
    msg.exec();
}

void MainWindow::onExitClicked()
{
    QCoreApplication::quit();
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
    ui->comboBox_table->setEnabled(false);
    ui->pushButton_ava->setEnabled(false);
    ui->pushButton_unav->setEnabled(false);
    ui->pushButton_input->setEnabled(false);
    m_db->setDBName(QString::fromStdString  (""));
    m_db->setUserName(QString::fromStdString(""));
    m_db->setPasswd(QString::fromStdString  (""));
    m_db->setHostAddress(QString::fromStdString(""));
    m_db->setPort(QString::fromStdString    (""));
}

void MainWindow::on_comboBox_table_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0:
            m_db -> setSelectedTab("adres_czytelnika");
            ui->comboBox_sort->setDisabled(true);
            ui->radioButton_down->setDisabled(true);
            ui->radioButton_up->setDisabled(true);
        break;
        case 1:
            m_db -> setSelectedTab("autor");
            ui->comboBox_sort->setEnabled(true);
            ui->radioButton_down->setEnabled(true);
            ui->radioButton_up->setEnabled(true);
        break;
        case 2:
            m_db -> setSelectedTab("czytelnik");
            ui->comboBox_sort->setEnabled(true);
            ui->radioButton_down->setEnabled(true);
            ui->radioButton_up->setEnabled(true);
        break;
        case 3:
            m_db -> setSelectedTab("e_czytnik");
            ui->comboBox_sort->setDisabled(true);
            ui->radioButton_down->setDisabled(true);
            ui->radioButton_up->setDisabled(true);
        break;
        case 4:
            m_db -> setSelectedTab("karta_biblioteczna");
            ui->comboBox_sort->setDisabled(true);
            ui->radioButton_down->setDisabled(true);
            ui->radioButton_up->setDisabled(true);
        break;
        case 5:
            m_db -> setSelectedTab("ksiazka");
            ui->comboBox_sort->setEnabled(true);
            ui->radioButton_down->setEnabled(true);
            ui->radioButton_up->setEnabled(true);
        break;
        case 6:
            m_db -> setSelectedTab("\"plyta_CD\"");
            ui->comboBox_sort->setDisabled(true);
            ui->radioButton_down->setDisabled(true);
            ui->radioButton_up->setDisabled(true);
        break;
        case 7:
            m_db -> setSelectedTab("plyta_film");
            ui->comboBox_sort->setEnabled(true);
            ui->radioButton_down->setEnabled(true);
            ui->radioButton_up->setEnabled(true);
        break;
        case 8:
            m_db -> setSelectedTab("plyta_muzyka");
            ui->comboBox_sort->setEnabled(true);
            ui->radioButton_down->setEnabled(true);
            ui->radioButton_up->setEnabled(true);
        break;
        case 9:
            m_db -> setSelectedTab("sztuka");
            ui->comboBox_sort->setDisabled(true);
            ui->radioButton_down->setDisabled(true);
            ui->radioButton_up->setDisabled(true);
        break;
        case 10:
            m_db -> setSelectedTab("wydawnictwo");
            ui->comboBox_sort->setDisabled(true);
            ui->radioButton_down->setDisabled(true);
            ui->radioButton_up->setDisabled(true);
        break;
        default:
            m_db -> setSelectedTab("");
        break;
    }

    QString gpby = "";
    switch(ui->comboBox_sort->currentIndex())
    {
    case 0:
        break;
    case 1:
        if (index == 1 or index == 2)
        {
            if (ui->radioButton_up->isChecked())
                gpby += " ORDER BY imie";
            else
                gpby += " ORDER BY imie DESC";
        }
        break;
    case 2:
        if (index == 1 or index == 2)
        {
            if (ui->radioButton_up->isChecked())
                gpby += " ORDER BY nazwisko";
            else
                gpby += " ORDER BY nazwisko DESC";
        }
        break;
    case 3:
        if (index == 5 or index == 7 or index == 8)
        {
            if (ui->radioButton_up->isChecked())
                gpby += " ORDER BY tytul";
            else
                gpby += " ORDER BY tytul DESC";
            break;
        }

    default:
        break;
    }

    showTable("SELECT * FROM " + m_db -> getSelectedTab() + gpby + ";");
}


void MainWindow::on_pushButton_input_clicked()
{
    if (!m_isAppendingData)
    {
        ui -> tableWidget -> setRowCount(ui->tableWidget->rowCount() + 1);
        ui -> pushButton_save -> setEnabled(true);
        m_isAppendingData = true;
    }

}


void MainWindow::on_pushButton_save_clicked()
{
    QRegularExpression re("^\\d");
    QString values = "";
    QString valNames = "";
    const int cols = ui->tableWidget->columnCount();
    for (int i = 0; i < cols; i++)
    {
        QString curVal = ui->tableWidget->model()->data(ui->tableWidget->model()->index(ui->tableWidget->rowCount()-1, i)).toString();

        if (i == cols - 1)
            if(re.match(curVal).hasMatch())
                values += curVal + " ";
            else
                values += "\'" + curVal + "\' ";

        else
            if(re.match(curVal).hasMatch())
                values += curVal + ", ";
            else
                values += "\'" + curVal + "\', ";

        valNames += ui->tableWidget->horizontalHeaderItem(i)->text() + " ";
    }



    QString query = "INSERT INTO " + m_db->getSelectedTab() + " (";
    for (int i = 0; i < cols - 1; i++)
        query += valNames.split(" ").at(i) + ", ";
    query += valNames.split(" ").at(cols - 1);
    query += ") VALUES (" + values + ");";

    m_db->sendQuery(query, true);
    ui->pushButton_save->setDisabled(true);
    m_isAppendingData = false;
}





void MainWindow::on_comboBox_tablestretch_activated(int index)
{
    switch (index)
    {
    case 0:
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        break;
    case 1:
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        break;
    case 2:
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
        break;
    default:
            ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        break;
    }
}


void MainWindow::on_pushButton_ava_clicked() { showTable("SELECT * FROM dostepne"); }


void MainWindow::on_pushButton_unav_clicked() { showTable("SELECT * FROM wypozyczone"); }


void MainWindow::on_pushButton_cAv_clicked() { showTable("SELECT COUNT(*) as Dostepne FROM sztuka where wypozyczona = false;"); }


void MainWindow::on_pushButton_cUnav_clicked() { showTable("SELECT COUNT(*) as Wypozyczone FROM sztuka where wypozyczona = true;"); }


void MainWindow::on_comboBox_sort_currentIndexChanged(int index) { on_comboBox_table_currentIndexChanged(ui->comboBox_table->currentIndex()); }


void MainWindow::on_radioButton_up_clicked() { on_comboBox_table_currentIndexChanged(ui->comboBox_table->currentIndex()); }


void MainWindow::on_radioButton_down_clicked() { on_comboBox_table_currentIndexChanged(ui->comboBox_table->currentIndex()); }

