#include "doc.h"

doc::doc(QWidget *parent) : QWidget(parent)
{
    QFont f( "Helvetica", 16, QFont::Bold);
    QFont g( "Helvetica", 10);

    QLabel *label = new QLabel("GraphViewer", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    label->setFont(f);
    QLabel *label2 = new QLabel("With this application you are allowed to create your own costumized charts and it's actually pretty simple and user-friendly.\n", this);
    layout->addWidget(label2);
    label2->setFont(g);
    QLabel *label3 = new QLabel("First of all insert your data by filling in the table or by importing an existing file.\n", this);
    layout->addWidget(label3);
    label3->setFont(g);
    QLabel *label4 = new QLabel("Now that your dataset is ready you'll be able to display the corrisponding charts.", this);
    layout->addWidget(label4);
    label4->setFont(g);
    QLabel *label5 = new QLabel("Choose between Line Chart, Bar Charts, Pie Chart, Area Chart, Scatter Chart or Polar Chart, the one that rappresent best your infos\n and suit the analysis you need to perform.", this);
    layout->addWidget(label5);
    label5->setFont(g);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout->addLayout(layout2);

    QLabel *label6 = new QLabel("\nNow a little focus on the controls and features:", this);
    layout->addWidget(label6);
    label6->setFont(g);
    QLabel *label7 = new QLabel("   ○  Press File->New Project or the first button to create a new workspace and start to fill a blank table;", this);
    layout->addWidget(label7);
    label7->setFont(g);
    QLabel *label8 = new QLabel("   ○  By clicking on File->Open file to import a file you want to upload but make sure it has the .json extention and that the datas has already been properly processed;", this);
    layout->addWidget(label8);
    label8->setFont(g);

    QLabel *label16 = new QLabel("   ○  By double-clicking on a cell in the grid you will be able to change the value of that cell, the same to customize the table labels to make everything clearer;", this);
    layout->addWidget(label16);
    label16->setFont(g);
    QLabel *label10 = new QLabel("   ○  Moreover, you can add or remove rows and colums from/to the table using simply the buttons on the left or the Edit Table menu", this);
    layout->addWidget(label10);
    label10->setFont(g);
    QLabel *label12 = new QLabel("   ○  Then comes the funny part, choose your preferenced graph type in the Graph View menu or, again, the side buttons and finally display your chart."
                                 "\n       When you change your data, just press the RELOAD button below the graph to view the UPDATED Graph;"
                                 "\n       Once your chart is created you can easily zoom in it by pressing the left mouse button and drawing the rectangle on the section you want to enlarge."
                                 "\n       Zoom out pressing the right button.", this);
    layout->addWidget(label12);
    label12->setFont(g);
    QLabel *label15 = new QLabel("   ○  You can save your project in JSON format by clicking on File->Save project or on the second button", this);
    layout->addWidget(label15);
    label15->setFont(g);
    QLabel *label9 = new QLabel("   ○  We also provide some examples to start familiarize with the application. They can be opened in File->Samples", this);
    layout->addWidget(label9);
    label9->setFont(g);
    QLabel *label13 = new QLabel("   ○  In the Help menu you'll find this manual and our contacts if you're interested in knowing more about us.\n", this);
    layout->addWidget(label13);
    label13->setFont(g);
    QLabel *label14 = new QLabel("   ○  To close the application you just need to do is click on File->Close and the application will close itself. | By doing that we will probably miss you :( |\n\n      If you find any bugs or need more help, Feel free to contact us.", this);
    layout->addWidget(label14);
    label14->setFont(g);
    QLabel *label20 = new QLabel("\nEnjoy!!! And stay tuned for updates.", this);
    layout->addWidget(label20);
    label20->setFont(g);

    this->layout()->setAlignment(this, Qt::AlignCenter);
    QPalette pale = qApp->palette();
    pale.setColor(QPalette::Window, QRgb(0xFFFFFFF));
    qApp->setPalette(pale);
}

void doc::closeEvent(QCloseEvent *event)
{
    emit close();
    event->accept();
}
