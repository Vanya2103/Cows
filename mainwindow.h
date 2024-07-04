#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableWidgetItem>
#include <QMainWindow>
#include "highscore.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(HighScore* highscore, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_newGameButton_clicked();

    void on_enterButton_clicked();

    void on_recordsButton_clicked();

private:
    Ui::MainWindow *ui;
    QString rightAnswer = 0;
    int attempts = 0;
    HighScore* m_highScore;

    QTableWidgetItem* result(QString attempt);
    void endGame();
};
#endif // MAINWINDOW_H
