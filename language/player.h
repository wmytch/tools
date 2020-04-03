#ifndef PLAYER_H
#define PLAYER_H
#include <QtCharts>
#include <QIODevice>
#include <QBuffer>
#include <QAudioDecoder>
#include <QAudioFormat>
#include <QFile>

// Class for decode audio files like MP3 and push decoded audio data to QOutputDevice (like speaker) and also signal newData().
// For decoding it uses QAudioDecoder which uses QAudioFormat for decode audio file for desire format, then put decoded data to buffer.
// based on: https://github.com/Znurre/QtMixer
#include <QObject>

class Player : public QIODevice
{
    Q_OBJECT
public:
    Player(QXYSeries *series,qint64 pointsCount,QObject *parent);

    bool init(const QAudioFormat& format);

    enum State { Playing, Stopped };

    void play(const QString &filePath);
    void stop();

    State state(){ return mState;}

    bool atEnd() const override;

protected:
    qint64 readData(char* data, qint64 maxlen) override;
    qint64 writeData(const char* data, qint64 len) override;

private:
    QFile mFile;
    QBuffer mInput{&mData};
    QBuffer mOutput{&mData};
    QByteArray mData;
    QAudioDecoder mDecoder;
    QAudioFormat mFormat;

    QXYSeries *mSeries;
    qint64 range=4000;

    State mState{Stopped};

    bool isInited;
    bool isDecodingFinished;

    void clear();

private slots:
    void bufferReady();
    void finished();

signals:
    void stateChanged(Player::State state);
    void newData(const QByteArray& data);
};

#endif // PLAYER_H
