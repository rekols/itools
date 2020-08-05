#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include <QButtonGroup>

class SideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SideBar(QWidget *parent = 0);

signals:
    void buttonClicked(int index);

private:
    void paintEvent(QPaintEvent *);
    void initButtons();

private:
    QVBoxLayout *m_layout;
    QButtonGroup *m_buttonGroup;
    QStringList m_buttonNameList;
};

#endif
