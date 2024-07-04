#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <ctime>
#include <QtWidgets>
#include <QLabel>
#include <QPixmap>
#include <QString>
#include <QDebug>
#include "highscore.h"

// QPixmap cowPixmap(":/res/e3_picture_b7551283.jpg");
// QPixmap bullPixmap(":/res/png-transparent-goat-zebu-chophouse-restaurant-longhorn-steakhouse-ox-domestic-yak-texas-longhorn-cattle.png");

MainWindow::MainWindow(HighScore* highscore, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_highScore(highscore)
{
    ui->setupUi(this);
    ui->enterLabel->setText("ENTER A NUMBER");
    ui->gameInfoLabel->setText("THE GAME HASN'T BEEN STARTED");
    ui->enterButton->setDisabled(true);
    ui->inputLineEdit->setDisabled(true);
    srand(time(NULL));
    QRegularExpressionValidator* validator = new QRegularExpressionValidator(QRegularExpression("\\d{4}"), this);
    ui->inputLineEdit->setValidator(validator);
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 500);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("YOUR NUMBER"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("RESULT"));
    attempts = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newGameButton_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "", "Do you want to start a new game?",
                                                              QMessageBox::Yes | QMessageBox::No );
    if (reply == QMessageBox::Yes) {
        ui->tableWidget->setRowCount(0);
        ui->enterButton->setDisabled(false);
        ui->inputLineEdit->setDisabled(false);
        ui->gameInfoLabel->setText("THE GAME HAS BEEN STARTED!");
        attempts = 0;
        int a = 0 , b = 0, c = 0, d = 0;
        while (a == b || a == c || a == d || b == c || b == d || c == d) {
            a = rand() % 9 + 1;
            b = rand() % 10;
            c = rand() % 10;
            d = rand() % 10;
        }
        std::string s = std::to_string(1000 * a + 100 * b + 10 * c + d);
        rightAnswer = QString::fromLatin1(s.data(), s.size());
        qDebug() << rightAnswer;
    }
}

// void MainWindow::on_enterButton_clicked()
// {
//     if (ui->inputLineEdit->text().size() != 4) {
//         QMessageBox::critical(this, "ERROR", "Wrong data entered. You must enter a 4-digit number.");
//     }
//     else {
//         attempts++;
//         ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
//         QTableWidgetItem* showAttempt = new QTableWidgetItem(ui->inputLineEdit->text());
//         showAttempt->setFlags(showAttempt->flags() & ~Qt::ItemIsEditable);
//         ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, showAttempt);

//         QTableWidgetItem* res = result(ui->inputLineEdit->text());
//         res->setFlags(res->flags() & ~Qt::ItemIsEditable);
//         ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 1, res);
//     }
//     if (ui->inputLineEdit->text() == rightAnswer) {
//         endGame();
//     }
//     ui->inputLineEdit->clear();
// }
void MainWindow::on_enterButton_clicked()
{
    if (ui->inputLineEdit->text().size() != 4) {
        QMessageBox::critical(this, "ERROR", "Wrong data entered. You must enter a 4-digit number.");
    }
    else {
        attempts++;
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount() + 1);
        QTableWidgetItem* showAttempt = new QTableWidgetItem(ui->inputLineEdit->text());
        showAttempt->setFlags(showAttempt->flags() & ~Qt::ItemIsEditable);
        ui->tableWidget->setItem(ui->tableWidget->rowCount() - 1, 0, showAttempt);

        QTableWidgetItem* res = result(ui->inputLineEdit->text());
        res->setFlags(res->flags() & ~Qt::ItemIsEditable);
        // Теперь result возвращает пустой QTableWidgetItem, который не нужно добавлять в таблицу,
        // так как result уже добавляет QWidget в таблицу как CellWidget.
    }
    if (ui->inputLineEdit->text() == rightAnswer) {
        endGame();
    }
    ui->inputLineEdit->clear();
}


// QTableWidgetItem *MainWindow::result(QString attempt)
// {
//     int bulls = 0;
//     int cows = 0;
//     QString copy = rightAnswer;
//     for (int i = 0; i < 4; i++) {
//         if (attempt[i] == copy[i]) {
//             bulls++;
//         }
//         if(copy.indexOf(attempt[i]) > -1) {
//             copy[copy.indexOf(attempt[i])] = '.';
//             cows++;
//         }
//     }
//     cows -= bulls;
//     QTableWidgetItem* res = new QTableWidgetItem("COWS:  " + QString::number(cows) + ";   BULLS:  " + QString::number(bulls));
//     res->setFlags(res->flags() & ~Qt::ItemIsEditable);
//     return res;
// }
QTableWidgetItem* MainWindow::result(QString attempt)
{
    int bulls = 0;
    int cows = 0;
    QString copy = rightAnswer;
    for (int i = 0; i < 4; i++) {
        if (attempt[i] == copy[i]) {
            bulls++;
        }
        if(copy.indexOf(attempt[i]) > -1) {
            copy[copy.indexOf(attempt[i])] = '.';
            cows++;
        }
    }
    cows -= bulls;

    QWidget* resultWidget = new QWidget();
    QHBoxLayout* layout = new QHBoxLayout(resultWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    QLabel* cowsLabel = new QLabel("COWS: " + QString::number(cows));
    QLabel* bullsLabel = new QLabel("BULLS: " + QString::number(bulls));

    QPixmap cowPixmap(":/res/e3_picture_b7551283.jpg"); // Убедитесь, что путь к изображению правильный
    QPixmap bullPixmap(":/res/png-transparent-goat-zebu-chophouse-restaurant-longhorn-steakhouse-ox-domestic-yak-texas-longhorn-cattle.png"); // Убедитесь, что путь к изображению правильный

    QLabel* cowImage = new QLabel();
    QLabel* bullImage = new QLabel();
    cowImage->setPixmap(cowPixmap.scaled(20, 20, Qt::KeepAspectRatio));
    bullImage->setPixmap(bullPixmap.scaled(20, 20, Qt::KeepAspectRatio));

    layout->addWidget(cowImage);
    layout->addWidget(cowsLabel);
    layout->addSpacing(10);
    layout->addWidget(bullImage);
    layout->addWidget(bullsLabel);

    QTableWidgetItem* resultItem = new QTableWidgetItem();
    ui->tableWidget->setCellWidget(ui->tableWidget->rowCount() - 1, 1, resultWidget);

    return resultItem;
}


void MainWindow::endGame()
{
    ui->gameInfoLabel->setText("HORAY! YOU WON!");
    ui->enterButton->setDisabled(true);
    ui->inputLineEdit->setDisabled(true);

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Enter your name:");

    QVBoxLayout* layout = new QVBoxLayout();
    msgBox.setLayout(layout);

    QLineEdit* lineEdit = new QLineEdit(&msgBox);
    lineEdit->setPlaceholderText("Name");

    msgBox.layout()->addWidget(lineEdit);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setEscapeButton(QMessageBox::Cancel);

    int result = msgBox.exec();

    if (result == QMessageBox::Ok) {
        QString name = lineEdit->text();
        if (m_highScore->isTop(attempts)) {
            m_highScore->add(attempts, name);
        }
    } else if (result == QMessageBox::Cancel) {
        return;
    }
}

void MainWindow::on_recordsButton_clicked()
{
    m_highScore->refill();
    m_highScore->setWindowTitle("RECORDS");
    m_highScore->show();
}
