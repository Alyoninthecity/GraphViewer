#include "aboutus.h"

aboutUs::aboutUs(QWidget *parent) : QWidget(parent)
{
    QFont f( "Helvetica", 16, QFont::Bold);
    QFont g( "Helvetica", 10);
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Contacts:", this);
    layout->addWidget(label);
    label->setFont(f);
    QLabel *label2 = new QLabel("Massimo Chioru \n  Computer Science Student at the University of Padua, registration number 2013449", this);
    label2->setFont(g);
    layout->addWidget(label2);
    QLabel *label5 = new QLabel("   &nbsp;&nbsp;&nbsp;email: <a href=\"mailto:massimo.chioru@studenti.unipd.it\">massimo.chioru@studenti.unipd.it</a>", this);
    label5->setFont(g);
    label5->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label5->setOpenExternalLinks(true);
    layout->addWidget(label5);

    QLabel *label3 = new QLabel("\nElena Fabris \n  Computer Science Student at the University of Padua, registration number 2008072", this);
    label3->setFont(g);
    layout->addWidget(label3);
    QLabel *label4 = new QLabel("   &nbsp;&nbsp;&nbsp;email: <a href=\"mailto:elena.fabris.10@studenti.unipd.it\">elena.fabris.10@studenti.unipd.it</a>", this);
    label4->setFont(g);
    label5->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label5->setOpenExternalLinks(true);
    layout->addWidget(label4);

    this->layout()->setAlignment(this, Qt::AlignCenter);
    QPalette pale = qApp->palette();
    pale.setColor(QPalette::Window, QRgb(0xFFFFFFF));
    qApp->setPalette(pale);
}

void aboutUs::closeEvent(QCloseEvent *event)
{
    emit close();
    event->accept();
}
