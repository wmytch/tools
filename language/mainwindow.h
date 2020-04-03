#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtCharts>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QAudioDeviceInfo>
#include <QAudioInput>
#include <QAudioOutput>
#include "datahandler.h"
#include "player.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using namespace QtCharts;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMediaPlayer *player;
//    Player *player;
    QMediaPlaylist *playlist;
    QString totalDuration;
    QString currentPosition;

    QAudioInput *recorder{nullptr};
//    QAudioOutput *audioOutput{nullptr};

    QList<QAudioDeviceInfo> deviceList;

    QAudioDeviceInfo currentDevice;
    QAudioFormat settings;

    const qint64 waveChartPoints=4000;
    DataHandler *recorderDataHandler;
//    RecorderDataHandler *player;
    QLineSeries *recorderSeries;
    QLineSeries *playerSeries;

    void initPlayer();
    void initRecorder();
    void initChart(QChartView *chartView,QLineSeries *series,QString title);

private slots:
    void onStateChanged(QMediaPlayer::State state);
    void onPlayListChanged(int pos);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 pos);
//    void onIODeviceUpdateBlockSize(qint64 blockSize);

    void on_actOpenFile_triggered();

    void on_playList_doubleClicked(const QModelIndex &index);

    void on_btnPlay_clicked();

    void on_btnStop_clicked();

    void on_btnSound_clicked();

    void on_volumn_valueChanged(int value);

    void on_sliderDuration_valueChanged(int value);

    void on_btnBackward_clicked();

    void on_btnForward_clicked();

    void on_btnPrevious_clicked();

    void on_btnNext_clicked();

    void on_comboRecorder_currentIndexChanged(int index);

    void on_btnTestDevice_clicked();

    void on_btnBeginRecord_clicked();

    void on_btnStopRecord_clicked();

    void on_sliderRecorderVolumn_valueChanged(int value);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
