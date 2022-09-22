#include "graphviewer.h"
#include "controller.h"
#include <iostream>

void GraphViewer::addMenus()
{

    QMenuBar* menuBar= new QMenuBar(this);

    file= new QMenu("File",menuBar);
    options=new QMenu("Edit Table",menuBar);
    graphview=new QMenu("Graph View",menuBar);
    help=new QMenu("Help",menuBar);

    sample=new QMenu("Samples", file);

    file->addAction(new QAction(QIcon(":/images/newp.png"), "New project", file));//f0
    file->addAction(new QAction(QIcon(":/images/load.png"), "Open file", file));//f1
    file->addAction(new QAction(QIcon(":/images/save.png"), "Save project", file));//2
    file->addSeparator();//f3
    file->addMenu(sample);//f4
    file->addSeparator();//f5
    file->addAction(new QAction(QIcon(":/images/close.png"),"Close", file));//f6

    sample->addAction(new QAction(QIcon(":/images/open.png"),"Fuel prices sample",sample));
    sample->addAction(new QAction(QIcon(":/images/open.png"),"Inflation sample",sample));
    sample->addAction(new QAction(QIcon(":/images/open.png"),"Population sample",sample));
    sample->setIcon(QIcon(":/images/open.png"));


    options->addAction(new QAction(QIcon(":/images/addC.png"), "Add columns", options));
    options->addAction(new QAction(QIcon(":/images/addR.png"), "Add rows", options));
    options->addAction(new QAction(QIcon(":/images/removeC.png"), "Remove column", options));
    options->addAction(new QAction(QIcon(":/images/removeR.png"), "Remove row", options));

    graphview->addAction(new QAction(QIcon(":/images/line.png"),"Line Chart", graphview));
    graphview->addAction(new QAction(QIcon(":/images/bar.png"),"Bar Chart", graphview));
    graphview->addAction(new QAction(QIcon(":/images/pie.png"),"Pie Chart", graphview));
    graphview->addAction(new QAction(QIcon(":/images/area.png"),"Area Chart", graphview));
    graphview->addAction(new QAction(QIcon(":/images/scatter.png"),"Scatter Chart", graphview));
    graphview->addAction(new QAction(QIcon(":/images/polar.png"),"Polar Chart", graphview));

    help->addAction(new QAction(QIcon(":/images/doc.png"),"Documentation", help));
    help->addAction(new QAction(QIcon(":/images/about.png"),"About Us", help));

    menuBar->addMenu(file);
    menuBar->addMenu(options);
    menuBar->addMenu(graphview);
    menuBar->addMenu(help);

    mainLayout->addWidget(menuBar,0,0,1,9);
}

void GraphViewer::addButtons()
{
    QVBoxLayout* buttonsLayout = new  QVBoxLayout();

    newProjectButton = new QPushButton(QIcon(":/images/newp.png"),"");
    loadButton = new QPushButton(QIcon(":/images/load.png"),"");
    saveButton = new QPushButton(QIcon(":/images/save.png"),"");
    addColumnsButton = new QPushButton(QIcon(":/images/addC.png"), "");
    addRowsButton = new QPushButton(QIcon(":/images/addR.png"), "");
    delColumnButton = new QPushButton(QIcon(":/images/removeC.png"), "");
    delRowButton = new QPushButton(QIcon(":/images/removeR.png"), "");
    chartsButton= new QComboBox();

    chartsButton->addItem(QIcon(":/images/line.png"),"");
    chartsButton->addItem(QIcon(":/images/bar.png"), "");
    chartsButton->addItem(QIcon(":/images/pie.png"),"");
    chartsButton->addItem(QIcon(":/images/area.png"),"");
    chartsButton->addItem(QIcon(":/images/scatter.png"),"");
    chartsButton->addItem(QIcon(":/images/polar.png"),"");

    buttonsLayout->addWidget(newProjectButton);
    buttonsLayout->addWidget(loadButton);
    buttonsLayout->addWidget(saveButton);
    buttonsLayout->addWidget(addColumnsButton);
    buttonsLayout->addWidget(addRowsButton);
    buttonsLayout->addWidget(delColumnButton);
    buttonsLayout->addWidget(delRowButton);
    buttonsLayout->addWidget(chartsButton);

    newProjectButton->setToolTip("New project");
    loadButton->setToolTip("Load Project");
    saveButton->setToolTip("Save project");
    addColumnsButton->setToolTip("Add columns");
    addRowsButton->setToolTip("Add rows");
    delColumnButton->setToolTip("Remove column");
    delRowButton->setToolTip("Remove row");

    chartsButton->setItemData(0, "Line chart", Qt::ToolTipRole);
    chartsButton->setItemData(1, "Bar chart", Qt::ToolTipRole);
    chartsButton->setItemData(2, "Pie chart", Qt::ToolTipRole);
    chartsButton->setItemData(3, "Area chart", Qt::ToolTipRole);
    chartsButton->setItemData(4, "Scatter chart", Qt::ToolTipRole);
    chartsButton->setItemData(5, "Polar chart", Qt::ToolTipRole);

    buttonsLayout->addStretch(1);
    buttonsLayout->setSpacing(5);
    buttonsLayout->setContentsMargins(20, 20, 5, 20);

    mainLayout->addLayout(buttonsLayout,1,0,1,1);
}

void GraphViewer::updateModel(){
    table->setModel(controller->getModel());
    table->resizeRowsToContents();
    table->resizeColumnsToContents();
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);
}


void GraphViewer::addTableScreen()
{
    table=new QTableView();
    updateModel();
    mainLayout->addWidget(table,1,1,2,4);
}

void GraphViewer::addChartView()
{
    chartView = new QChartView();
    mainLayout->addWidget(chartView,1,5,1,4);
    controller->graph(0);
    updateButton= new QPushButton(QIcon(":/images/update.png"), "");
    updateButton->setToolTip("Update chart");
    updateButton->setStyleSheet("min-width: 250px; margin: 20px;");
    chartView->setRubberBand(QChartView::HorizontalRubberBand);
    mainLayout->addWidget(updateButton, 2, 6, 1,2);
}

GraphViewer::GraphViewer(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout(this);
    addMenus();
    addButtons();
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);
    mainLayout->setColumnStretch(1, 0);
    setLayout(mainLayout);
    resize(QSize(1024,420));
}

void GraphViewer::setController(Controller *c)
{
    controller=c;
    addTableScreen();
    addChartView();
    //menu
    //file
    connect(file->actions()[0], SIGNAL(triggered()), controller, SLOT(newP()));
    connect(file->actions()[1], SIGNAL(triggered()), controller, SLOT(openJson()));
    connect(file->actions()[2], SIGNAL(triggered()), controller, SLOT(saveJson()));

    connect(sample->actions()[0], SIGNAL(triggered()), controller, SLOT(openS1()));
    connect(sample->actions()[1], SIGNAL(triggered()), controller, SLOT(openS2()));
    connect(sample->actions()[2], SIGNAL(triggered()), controller, SLOT(openS3()));

    connect(file->actions()[6], SIGNAL(triggered()), this, SLOT(close()));

    //edit table
    connect(options->actions()[0], SIGNAL(triggered()), controller, SLOT(addCols()));
    connect(options->actions()[1], SIGNAL(triggered()), controller, SLOT(addRows()));
    connect(options->actions()[2], SIGNAL(triggered()), controller, SLOT(removeCol()));
    connect(options->actions()[3], SIGNAL(triggered()), controller, SLOT(removeRow()));

    //graph view
    connect(graphview->actions()[0], SIGNAL(triggered()), controller, SLOT(line()));
    connect(graphview->actions()[1], SIGNAL(triggered()), controller, SLOT(bar()));
    connect(graphview->actions()[2], SIGNAL(triggered()), controller, SLOT(pie()));
    connect(graphview->actions()[3], SIGNAL(triggered()), controller, SLOT(area()));
    connect(graphview->actions()[4], SIGNAL(triggered()), controller, SLOT(scatter()));
    connect(graphview->actions()[5], SIGNAL(triggered()), controller, SLOT(polar()));

    //help
    connect(help->actions()[0], SIGNAL(triggered()), this, SLOT(documentation()));
    connect(help->actions()[1], SIGNAL(triggered()), this, SLOT(about()));


    //buttons
    connect(newProjectButton, SIGNAL(clicked()), controller, SLOT(newP()));
    connect(loadButton, SIGNAL(clicked()), controller, SLOT(openJson()));
    connect(saveButton, SIGNAL(clicked()), controller, SLOT(saveJson()));
    connect(addColumnsButton, SIGNAL(clicked()), controller, SLOT(addCols()));
    connect(addRowsButton, SIGNAL(clicked()), controller, SLOT(addRows()));
    connect(delColumnButton, SIGNAL(clicked()), controller, SLOT(removeCol()));
    connect(delRowButton, SIGNAL(clicked()), controller, SLOT(removeRow()));

    connect(chartsButton, SIGNAL(activated(int)), controller, SLOT(graph(int)));

    //Headers
    connect(table->horizontalHeader(), SIGNAL(sectionDoubleClicked(int)), controller, SLOT(editHHeader(int)));
    connect(table->verticalHeader(), SIGNAL(sectionDoubleClicked(int)), controller, SLOT(editVHeader(int)));
    connect(updateButton, SIGNAL(clicked()), controller, SLOT(update()));
}

void GraphViewer::setHome()
{
    documentation();

}

QWidget *GraphViewer::getChartView() const
{
    return chartView;
}

QWidget *GraphViewer::getTableView() const
{
    return table;
}

BaseChart *GraphViewer::getChart() const
{
    return chart;
}

void GraphViewer::setChart(BaseChart* c){
    chart = c;
}

int GraphViewer::getChartType()const{
    return chartType;
}

void GraphViewer::setChartType(int n){
    chartType = n;
}

void GraphViewer::showDialog(const QString &message)
{
    QDialog* dialog=new QDialog(this);
    QLabel * l = new QLabel(message, dialog);
    l->setFont(QFont( "Helvetica", 10));
    dialog->setLayout(new QHBoxLayout());
    dialog->layout()->addWidget(l);
    dialog->layout()->setAlignment(Qt::AlignCenter);
    dialog->setMinimumWidth(200);
    dialog->setMaximumWidth(800);
    dialog->show();
}

std::pair<int,int> GraphViewer::showNewProjectDialog()
{
    bool ok1=false;
    bool ok2=false;
    int nc=QInputDialog::getInt(this,"New project", "Insert number of column: ",1,1,100,QLineEdit::Normal,&ok1);
    int nr=QInputDialog::getInt(this,"New project", "Insert number of rows: ",1,1,100, QLineEdit::Normal,&ok2);
    if(!ok1 || !ok2)
         throw std::runtime_error("Invalid choice: creation canceled");
    return std::make_pair(nc,nr);
}

unsigned int GraphViewer::showRemoveColDialog()
{
    bool ok=false;
    int remove= QInputDialog::getInt(this, tr("Remove column"), "Index of the column to remove: ", 0, 0, 2147483647, 1, &ok);
    if(!ok)
        throw std::runtime_error("Invalid index: removal canceled");
    return remove;
}

unsigned int GraphViewer::showRemoveRowDialog()
{
    bool ok=false;
    int remove= QInputDialog::getInt(this, tr("Remove row"), "Index of the row to remove: ", 0, 0, 2147483647, 1, &ok);
    if(!ok)
        throw std::runtime_error("Invalid index: removal canceled");
    return remove;
}

QString GraphViewer::showUpdateHeaderDialog()
{
    bool ok=false;
    QString newValue= QInputDialog::getText(this, tr("Update Label"), tr("Enter a new Label:"), QLineEdit::Normal, tr("label"), &ok);
    if(!ok || newValue.isEmpty())
        throw std::runtime_error("Invalid label");
    return newValue;
}

unsigned int GraphViewer::showAddColsDialog()
{
    bool ok=false;
    int n= QInputDialog::getInt(this, tr("Add columns"), "Number of columns to be inserted: ", 1, 1, 99,1, &ok);
    if(!ok)
         throw std::runtime_error("Invalid choice: insertion canceled");
    return n;
}

unsigned int GraphViewer::showAddRowsDialog()
{
    bool ok=false;
    int n= QInputDialog::getInt(this, tr("Add rows"), "Number of rows to be inserted: ", 1, 1, 99,1, &ok);
    if(!ok)
         throw std::runtime_error("Invalid choice: insertion canceled");
    return n;
}

void GraphViewer::showChart()
{
    if (!chart)
   {
       std::cerr << "Trying to draw a nullptr chart\n";
       return;
   }
   chartView->setChart(getChart()->toChart());
   chartView->setRenderHint(QPainter::Antialiasing);
}

void GraphViewer::documentation() const
{
    doc *manual = new doc();
    manual->setWindowTitle("User Manual");
    manual->layout()->setAlignment(manual, Qt::AlignLeft);
    manual->show();
}

void GraphViewer::about() const
{
    aboutUs *c = new aboutUs();
    c->setWindowTitle("About Us");
    c->layout()->setAlignment(c, Qt::AlignLeft);
    c->show();
}
