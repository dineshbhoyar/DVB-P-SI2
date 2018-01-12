#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QFileDialog>
#include <QUrl>
#include <QStandardPaths>
#include <QDebug>
#include <QScopedPointer>

#include <QLabel>

#include "csvdata.h"
#include "fileparser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionOpen_TS_triggered();

    void on_actionEnable_SDT_Other_triggered();

    void on_actionEnable_NIT_Other_triggered();

    void on_actionAbout_triggered();

    void on_actionVersion_triggered();

    void on_listView_2_clicked(const QModelIndex &index);
    
    void on_listView_clicked(const QModelIndex &index);
    
private:
    Ui::MainWindow *ui;
    QProgressBar *progressbar;
    QLabel *label;
    QScopedPointer<csvdata> ptr;
};

#endif // MAINWINDOW_H
