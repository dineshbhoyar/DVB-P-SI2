#include "parser_thread.h"

parser_thread::parser_thread(QString &filename, csvdata &ptr, QObject *parent) : QObject(parent),filepath(filename),dataptr(ptr)
{
qDebug() <<" parser thread started ";

}

void parser_thread::Parse()
{
    qDebug() <<"parser parse ";
    dataptr.setSource(filepath);
}

parser_thread::~parser_thread()
{
    qDebug() <<"parser end ";
}

