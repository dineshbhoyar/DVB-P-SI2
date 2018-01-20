#include "controller.h"

controller::controller(csvdata& ptr,QObject *parent) : QObject(parent),ptr(ptr)
{

}

void controller::start(QString path )
{
    if(parser){
        disconnect(thread,&QThread::finished,parser,&parser_thread::deleteLater);
        disconnect(thread,&QThread::started,parser,&parser_thread::Parse);
        delete parser;
    }
    if(thread){
        thread->quit();
        delete thread;
    }
    thread = new QThread();

    parser = new parser_thread(path,ptr);
    parser->moveToThread(thread);
    connect(thread,&QThread::finished,parser,&parser_thread::deleteLater);
    connect(thread,&QThread::started,parser,&parser_thread::Parse);
    thread->start();

}
