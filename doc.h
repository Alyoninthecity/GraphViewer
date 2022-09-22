#ifndef DOC_H
#define DOC_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QFont>
#include <QLabel>
#include <QHBoxLayout>
#include <QScrollArea>

class doc : public QWidget
{
    Q_OBJECT
public:
    explicit doc(QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void close();
};

#endif // DOC_H
