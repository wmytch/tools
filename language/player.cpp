#include "player.h"

Player::Player(QXYSeries *series,qint64 pointsCount,QObject *parent)
{
    Q_UNUSED(parent)
    setOpenMode(QIODevice::ReadWrite);
    mSeries=series;
    range=pointsCount;
    isInited = false;
    isDecodingFinished = false;
}

bool Player::init(const QAudioFormat &format)
{
    mFormat = format;
    mDecoder.setAudioFormat(mFormat);

    connect(&mDecoder, SIGNAL(bufferReady()), this, SLOT(bufferReady()));
    connect(&mDecoder, SIGNAL(finished()), this, SLOT(finished()));

    // Initialize buffers
    if (!mOutput.open(QIODevice::ReadOnly) || !mInput.open(QIODevice::WriteOnly))
    {
        return false;
    }

    isInited = true;

    return true;
}

qint64 Player::readData(char *data, qint64 maxlen)
{
    memset(data, 0, maxlen);

    if (mState == State::Playing)
    {
        mOutput.read(data, maxlen);

        // There is we send readed audio data via signal, for ability get audio signal for the who listen this signal.
        // Other word this emulate QAudioProbe behaviour for retrieve audio data which of sent to output device (speaker).
        if (maxlen > 0)
        {
            QByteArray buff(data, maxlen);
            emit newData(buff);
        }

        // Is finish of file
        if (atEnd())
        {
            stop();
        }
    }

    return maxlen;
}

qint64 Player::writeData(const char* data, qint64 len)
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

void Player::play(const QString &filePath)
{
    clear();
    if(filePath.isEmpty())
    {
        return;
    }

    mFile.setFileName(filePath);

    if (!mFile.open(QIODevice::ReadOnly))
    {
        return;
    }

    mDecoder.setSourceDevice(&mFile);
    mDecoder.start();

    mState = State::Playing;
    emit stateChanged(mState);
}

void Player::stop()
{
    clear();
    mState = State::Stopped;
    emit stateChanged(mState);
}


void Player::clear()
{
    mDecoder.stop();
    mData.clear();
    isDecodingFinished = false;
}

bool Player::atEnd() const
{
    return mOutput.size()
        && mOutput.atEnd()
        && isDecodingFinished;
}

// QAudioDecoder logic this methods responsible for decode audio file and put audio data to stream buffer

// Run when decode decoded some audio data
void Player::bufferReady() // SLOT
{
    const QAudioBuffer &buffer = mDecoder.read();

    const int length = buffer.byteCount();
    const char *data = buffer.constData<char>();

    mInput.write(data, length);
}

// Run when decode finished decoding
void Player::finished() // SLOT
{
    isDecodingFinished = true;
}