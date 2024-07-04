#ifndef HIGHSCORE_H
#define HIGHSCORE_H
#include <QtWidgets>

class HighScore : public QWidget {
    Q_OBJECT
public:
    explicit HighScore(QString filename, QWidget *parent = 0);
    void add(int score, QString name);
    bool isTop(int score);
    void refill();

private:
    void save();
    QString m_filename;
    std::multimap<int, QString, std::less<int> > m_highScore;
    QTableWidget m_scoreTable;

protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // HIGHSCORE_H
