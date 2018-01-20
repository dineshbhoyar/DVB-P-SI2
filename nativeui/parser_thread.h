#ifndef PARSER_THREAD_H
#define PARSER_THREAD_H

#include <QObject>
#include <QDebug>

#include "csvdata.h"
#include "fileparser.h"

class parser_thread : public QObject
{
    Q_OBJECT
public:
    explicit parser_thread(QString& filename, csvdata&ptr , QObject *parent = nullptr);

    ~parser_thread();

signals:

public slots:
    void Parse();
private:

    QString filepath;
    csvdata& dataptr;
};

#endif // PARSER_THREAD_H
