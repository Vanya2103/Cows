#include "highscore.h"

HighScore::HighScore(QString filename, QWidget *parent)
    : QWidget(parent), m_filename(filename)
{
    setAttribute(Qt::WA_DeleteOnClose, false);

    QFile file(filename);
    if (file.exists() && file.open(QIODevice::ReadWrite))
    {
        QTextStream fileStream(&file);
        while (!fileStream.atEnd())
        {
            QString name = fileStream.readLine();
            QString scoreStr = fileStream.readLine();
            int score = scoreStr.toInt();
            m_highScore.insert(std::make_pair(score, name));
        }
        file.close();
    }
    else
    {
        if (file.open(QIODevice::WriteOnly))
        {
            file.close();
        }
        else
        {
            throw std::runtime_error("Can't create file");
        }
    }

    m_scoreTable.setColumnCount(2);
    m_scoreTable.setHorizontalHeaderLabels(QStringList() << "Name" << "Score");
    resize(600, 300);
    m_scoreTable.setRowCount(m_highScore.size());
    int row = 0;
    for (const auto& record : m_highScore)
    {
        QTableWidgetItem* nameItem = new QTableWidgetItem(record.second);
        QTableWidgetItem* scoreItem = new QTableWidgetItem(QString::number(record.first));

        nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
        scoreItem->setFlags(scoreItem->flags() & ~Qt::ItemIsEditable);

        m_scoreTable.setItem(row, 0, nameItem);
        m_scoreTable.setItem(row, 1, scoreItem);

        ++row;
    }

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(&m_scoreTable);
}

void HighScore::add(int score, QString name)
{
    m_highScore.insert(std::make_pair(score, name));
    if (m_highScore.size() == 11) {
        m_highScore.erase(10);
    }
    save();
}

bool HighScore::isTop(int score)
{
    int i = 0;
    for (auto it = m_highScore.begin(); it != m_highScore.end(); ++it)
    {
        if (i > 10)
            return false;
        if (it->first > score)
            return true;
        ++i;
    }
    return true;
}

void HighScore::refill()
{
    m_scoreTable.clearContents();

    m_scoreTable.setRowCount(m_highScore.size());

    int row = 0;
    int num = 0;
    for (auto it = m_highScore.begin(); it != m_highScore.end(); ++it)
    {
        if (num <= 10) {
            QTableWidgetItem *nameItem = new QTableWidgetItem(it->second);
            QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(it->first));

            nameItem->setFlags(nameItem->flags() & ~Qt::ItemIsEditable);
            scoreItem->setFlags(scoreItem->flags() & ~Qt::ItemIsEditable);

            m_scoreTable.setItem(row, 0, nameItem);
            m_scoreTable.setItem(row, 1, scoreItem);

            ++row;
            ++num;
        } else {
            break;
        }
    }
    save();
}

void HighScore::save() {
    QFile file(m_filename);
    if (false == file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        throw std::runtime_error("can't open file");
    }
    QTextStream fileStream(&file);
    for (auto it = m_highScore.begin(); it != m_highScore.end(); ++it) {
        fileStream << it->second << "\n" << it->first << "\n";
    }
}

void HighScore::closeEvent(QCloseEvent *event)
{
    hide();
    event->ignore();
}
