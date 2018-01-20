#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "csvdata.h"
#include "nativeui/parser_thread.h"
#include <QThread>

class controller : public QObject
{
    Q_OBJECT
    QThread *thread;
    parser_thread *parser;
    csvdata& ptr;
public:
    explicit controller(csvdata& ptr,QObject *parent = nullptr);
Q_INVOKABLE void start(QString path);
signals:

public slots:
};

#endif // CONTROLLER_H
