#ifndef DATAHANDLE_H
#define DATAHANDLE_H
#include <QtCharts>
#include <QIODevice>

class DataHandler : public QIODevice
{
    Q_OBJECT
public:
    DataHandler(QXYSeries *series,qint64 pointsCount,QObject *parent=nullptr);
protected:
    qint64 readData(char *data, qint64 maxlen) override;
    qint64 writeData(const char *data, qint64 len) override;
private:
    QXYSeries *mSeries;
    qint64 range=4000;

//signals:
//    void updateBlockSize(qint64 blockSize);
};

#endif // DATAHANDLE_H
