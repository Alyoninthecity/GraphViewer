#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>

class aboutUs : public QWidget
{
    Q_OBJECT
public:
    explicit aboutUs(QWidget *parent = nullptr);
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void close();
};

#endif // ABOUTUS_H
