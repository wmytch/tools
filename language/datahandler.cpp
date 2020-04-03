#include "datahandler.h"


DataHandler::DataHandler(QXYSeries *series,qint64 pointsCount,QObject *parent)
{
    Q_UNUSED(parent)
    mSeries=series;
    range=pointsCount;
}

qint64 DataHandler::readData(char *data, qint64 maxlen)
{
    Q_UNUSED(data)
    Q_UNUSED(maxlen)
    return -1;
}

qint64 DataHandler::writeData(const char *data, qint64 len)
{
    QVector<QPointF> oldPoints=mSeries->pointsVector();
    QVector<QPointF> points;
    if(oldPoints.count()<range)
    {
        points=mSeries->pointsVector();
    }
    else
    {
        for(int i=len;i<oldPoints.count();i++)
        {
            points.append(QPointF(i-len,oldPoints[i].y()));
        }
    }

    qint64 size=points.count();
    for(int k=0;k<len;k++)
    {
        points.append(QPointF(k+size,(quint8)data[k]));
    }

    mSeries->replace(points);
//    emit updateBlockSize(len);
    return len;
}
