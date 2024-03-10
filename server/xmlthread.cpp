#include "xmlthread.h"

XMLThread::XMLThread(QObject *parent):QThread(parent)
{
    connect(this, &XMLThread::finished, this, &XMLThread::deleteLater);
    connect(&par, &XMLParser::parseError, this, &XMLThread::error);
}

void XMLThread::setFile(QString fileName)
{
    filePath=fileName;
}



void XMLThread::run()
{
#ifdef DEBUG_LOG
    qDebug()<<"Thread "<<QThread::currentThreadId()<<" running...";
#endif
    par.parseXML(filePath, str);
#ifdef DEBUG_LOG
    printDTO(str);
#endif
    delete[] str.iq_example;
    emit finished();
#ifdef DEBUG_LOG
    qDebug()<<"Thread "<<QThread::currentThreadId()<<" finished...";
#endif
}
