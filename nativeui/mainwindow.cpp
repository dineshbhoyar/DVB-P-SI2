#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <Qt>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ptr(new csvdata)
{
    ui->setupUi(this);
    progressbar = new  QProgressBar;
    label = new QLabel;

    label->setText("Ready ....");
    ui->statusBar->addPermanentWidget(label,2);

    ui->statusBar->addPermanentWidget(progressbar,2);
    ui->listView->setModel(&ptr->tChannel);
    ui->listView_2->setModel(&ptr->tParams);
    ui->textEdit->setReadOnly(true);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    //quit application by clossing qt window
    close();
}

void MainWindow::on_actionOpen_TS_triggered()
{
    QUrl durl = QUrl("file://"+QDir::homePath());
    QUrl furl = QFileDialog::getOpenFileUrl(this,tr("open ts"),durl,tr("TS files (*.ts *.TS)"));
    qDebug() << furl.fileName();
    label->setText("Processing .....");
    ptr->setSource(furl.path().replace("\\\\\\",""));
  if(ptr->NetworkName.size())
    ui->groupBox->setTitle(ptr->NetworkName);
    //label->setText("Ready ....");
}

void MainWindow::on_actionEnable_SDT_Other_triggered()
{

}

void MainWindow::on_actionEnable_NIT_Other_triggered()
{

}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_actionVersion_triggered()
{

}


//just to avoid tying enough of code
class IndexToRoleString{
    const  QModelIndex& index;
    int role=Qt::UserRole+1;
public:
    explicit IndexToRoleString(const QModelIndex & d):index{d} {};
    ~IndexToRoleString(){};
    IndexToRoleString& String(int role, QString & content,QString header, QString unit=""){
        if(index.data(role).canConvert<QString>()){
            content += "<i><b>"+header+" : </b>"+ index.data(role).toString() + " "+unit+" </i><br>";
        }
        return *this;
    };
    IndexToRoleString& String( QString & content,QString header, QString unit=""){
        if(index.data(role).canConvert<QString>()){
            content += "<i><b>"+header+" : </b>"+ index.data(role).toString() + " "+unit+" </i><br>";
        }
        role++;
        return *this;
    };
};

void MainWindow::on_listView_clicked(const QModelIndex &index)
{
    QString content{};

    if(index.isValid()){
        IndexToRoleString parse{index};
        parse.String(content,"Channel")
                .String(content,"QAM")
                .String(content,"Frequency")
                .String(content,"Symbol Rate","Msymbols/s")
                .String(content,"FEC_Inner")
                .String(content,"FEC_Outer")
                .String(content,"ServiceID")
                .String(content,"Audio PID")
                .String(content,"Video PID")
                .String(content,"PCR PID")
                .String(content,"PMT PID")
                .String(content,"Audio Type")
                .String(content,"Video Type")
                .String(content,"Sequence ID")
                .String(content,"EPG Available")
                .String(content,"Stream Id")
                .String(content,"Encripted")
                .String(content,"Network ID")
                .String(content,"Language")
                .String(content,"Channel state")
                .String(content,"Channel descriptions");
    }else{
        content = "<b>Unable to show channel information </b>";
    }
    ui->textEdit->setHtml(content);
}

void MainWindow::on_listView_2_clicked(const QModelIndex &index)
{
    QString content{};
    quint32 type =0;

    if(index.isValid()){
        IndexToRoleString parse(index);
        if(index.data(TuningParametrRole::Type).canConvert<qint32>()){
            type =  index.data(TuningParametrRole::Type).toInt();
            if (type == CABLE){
                parse.String(TuningParametrRole::Frequency,content,"Frequency","MHz")
                        .String(TuningParametrRole::QAM,content,"QAM")
                        .String(TuningParametrRole::SymbolRate,content,"QAM","Msymbol/s")
                        .String(TuningParametrRole::FEC_INNER,content,"FEC_Inner")
                        .String(TuningParametrRole::FEC_OUTER,content,"FEC_Outer");
            }else if (type == TERRESTRIAL){
                parse.String(TuningParametrRole::Frequency,content,"Frequency","Hz")
                        .String(TuningParametrRole::Bandwidth,content,"Bandwidth")
                        .String(TuningParametrRole::Time_Slicing_indicator,content,"TimeSliceIndicator")
                        .String(TuningParametrRole::MPE_FEC_indicator,content,"MPE_FEC_indicator")
                        .String(TuningParametrRole::Constellation,content,"Constellation")
                        .String(TuningParametrRole::Hierarchy_information,content,"Hierarchy_information")
                        .String(TuningParametrRole::Code_rate_HP_stream,content,"Code_rate_HP_stream")
                        .String(TuningParametrRole::Code_rate_LP_stream,content,"Code_rate_LP_stream")
                        .String(TuningParametrRole::Guard_interval,content,"Guard_interval")
                        .String(TuningParametrRole::Transmission_mode,content,"Transmission_mode")
                        .String(TuningParametrRole::Other_frequency_flag,content,"Other_frequency_flag");
            }else if ( type == SATELATE){
                parse.String(TuningParametrRole::Frequency,content,"Frequency","GHz")
                        .String(TuningParametrRole::Orbital_position,content,"Orbital_position")
                        .String(TuningParametrRole::SymbolRate,content,"SymbolRate","Msymbol/s")
                        .String(TuningParametrRole::FEC_INNER,content,"FEC_Inner")
                        .String(TuningParametrRole::West_east_flag,content,"West_east_flag")
                        .String(TuningParametrRole::Polarization,content,"Polarization")
                        .String(TuningParametrRole::Roll_off,content,"Roll_off")
                        .String(TuningParametrRole::Modulation_system,content,"Modulation_system")
                        .String(TuningParametrRole::Modulation_type,content,"Modulation_type");
            }else{
                content = "<b> Can not recognise the type of tuner </b>";
            }
        }else{
            content = "<b>Unable to proceed as tuner information not avaliable  </b>";
        }
    }
    ui->textEdit->setHtml(content);
    return;
}
