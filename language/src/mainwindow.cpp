#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initPlayer();
    initRecorder();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initPlayer()
{
    player=new QMediaPlayer(this);
//    playlist=new QMediaPlaylist(this);
//    playlist->setPlaybackMode(QMediaPlaylist::Loop);
//    player->setPlaylist(playlist);
//    player->setVolume(ui->volumn->value());

    playerSeries=new QLineSeries;
//    initChart(ui->playerChartView,playerSeries,"原声波形");
//    playerDisplayer=new Displayer(playerSeries,waveChartPoints,this);

    connect(player,&QMediaPlayer::playbackStateChanged,this,&MainWindow::onPlaybackStateChanged);
    connect(player,SIGNAL(positionChanged(qint64)),this,SLOT(onPositionChanged(qint64)));
    connect(player,SIGNAL(durationChanged(qint64)),this,SLOT(onDurationChanged(qint64)));
//    connect(playlist,SIGNAL(currentIndexChanged(int)),this,SLOT(onPlayListChanged(int)));

}

void MainWindow::initRecorder()
{
//    ui->comboRecorder->clear();
////    deviceList=QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
//    for(auto device:deviceList)
//    {
//        ui->comboRecorder->addItem(device.deviceName());
//    }
//    if(deviceList.size()>0)
//    {
//        ui->comboRecorder->setCurrentIndex(0);
//        currentDevice=deviceList[0];

//        recorderSeries=new QLineSeries;
//        initChart(ui->recorderChartView,recorderSeries,"跟读波形");

//        recorderDataHandler=new DataHandler(recorderSeries,waveChartPoints,this);

//        on_comboRecorder_currentIndexChanged(0);
//        ui->btnBeginRecord->setEnabled(false);
//        ui->btnStopRecord->setEnabled(false);
//        ui->btnReplayRecord->setEnabled(false);
//        ui->sliderRecorderVolumn->setEnabled(false);
//    }
//    else
//    {
//        ui->gbRecorder->setEnabled(false);
//    }
}

void MainWindow::initChart(QChartView *chartView,QLineSeries *series,QString title)
{
    QChart *chart=new QChart;
    chart->setTitle(title);
    chartView->setChart(chart);
    chart->addSeries(series);

    QValueAxis *axisX=new QValueAxis;
    axisX->setRange(0,waveChartPoints);
    axisX->setLabelFormat("%g");
    axisX->setTitleText("Samples");
    QValueAxis *axisY=new QValueAxis;
    axisY->setRange(0,256);
    axisY->setTitleText("Audio level");

    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    chart->legend()->hide();
}

void MainWindow::onPlaybackStateChanged(QMediaPlayer::PlaybackState playState)
{
    if(playState==QMediaPlayer::PlayingState)
    {
        ui->btnPlay->setIcon(QIcon(":/icon/pause.png"));
    }
    else
    {
        ui->btnPlay->setIcon(QIcon(":/icon/play.png"));

    }

}

void MainWindow::onPlayListChanged(int pos)
{
    ui->playList->setCurrentRow(pos);
    auto current=ui->playList->currentItem();
    if(current)
    {
        ui->labelCurrent->setText("当前播放："+current->text());
    }
}

void MainWindow::onDurationChanged(qint64 duration)
{
    ui->sliderDuration->setMaximum(duration);
    int secs=duration/1000;
    int hours=secs/3600;
    int mins=(secs%3600)/60;
    secs=secs%60;
    totalDuration=QString::asprintf("%02d:%02d:%02d",hours,mins,secs);
    ui->labelDuration->setText(currentPosition+"/"+totalDuration);
}

void MainWindow::onPositionChanged(qint64 pos)
{
    if(!ui->sliderDuration->isSliderDown())
    {
        ui->sliderDuration->setSliderPosition(pos);
        int secs=pos/1000;
        int hours=secs/3600;
        int mins=(secs%3600)/60;
        secs=secs%60;
        currentPosition=QString::asprintf("%02d:%02d:%02d",hours,mins,secs);
        ui->labelDuration->setText(currentPosition+"/"+totalDuration);
    }
}
void MainWindow::on_actOpenFile_triggered()
{
//    auto curPath=QDir::homePath();
//    QString dlgTitle{"选择文件"};
//    QString filter{"音频文件(*.mp3)"};
//    auto fileList=QFileDialog::getOpenFileNames(this,dlgTitle,curPath,filter);
//    if(fileList.count()>0)
//    {
//        for(auto file:fileList)
//        {
//            playlist->addMedia(QUrl::fromLocalFile(file));
//            QFileInfo fileInfo{file};
//            ui->playList->addItem(fileInfo.fileName());
//        }
//        if(player->state()!=QMediaPlayer::PlayingState)
//        {
//            playlist->setCurrentIndex(0);
//        }

////        player->play();
//    }
}

void MainWindow::on_playList_doubleClicked(const QModelIndex &index)
{
//    playlist->setCurrentIndex(index.row());
//    player->play();
}

void MainWindow::on_btnPlay_clicked()
{
//    if(playlist->mediaCount()>0)
//    {
//        if(player->state()==QMediaPlayer::PlayingState)
//        {
//            QIcon icon(":/icon/play.png");
//            ui->btnPlay->setIcon(icon);
//            player->pause();
//        }
//        else
//        {
//            QIcon icon(":/icon/pause.png");
//            ui->btnPlay->setIcon(icon);
//            if(playlist->currentIndex()<0)
//                playlist->setCurrentIndex(0);
//            player->play();
//        }
//    }
}

void MainWindow::on_btnStop_clicked()
{
    player->stop();
}

void MainWindow::on_btnSound_clicked()
{
//    bool mute=player->isMuted();
//    player->setMuted(!mute);
//    if(mute)
//    {
//        ui->btnSound->setIcon(QIcon(":/icon/sound.png"));
//    }
//    else
//    {
//        ui->btnSound->setIcon(QIcon(":/icon/mute.png"));
//    }
}

void MainWindow::on_volumn_valueChanged(int value)
{
//     player->setVolume(value);
}

void MainWindow::on_sliderDuration_valueChanged(int value)
{
    if(ui->sliderDuration->isSliderDown())
    {
        player->setPosition(value);
    }
}

void MainWindow::on_btnBackward_clicked()
{
    int pos=ui->sliderDuration->value()-5000;
    player->setPosition(pos>0?pos:0);
}

void MainWindow::on_btnForward_clicked()
{
    int pos=ui->sliderDuration->value()+5000;
    player->setPosition(pos>ui->sliderDuration->maximum()?ui->sliderDuration->maximum():pos);
}

void MainWindow::on_btnPrevious_clicked()
{
//    auto index=playlist->currentIndex()-1;
//    playlist->setCurrentIndex(index<0?0:index);
//    player->setPosition(0);
//    player->stop();
//    player->play();
}

void MainWindow::on_btnNext_clicked()
{
//    auto index=playlist->currentIndex()+1;
//    playlist->setCurrentIndex(index==playlist->mediaCount()?0:index);
//    player->setPosition(0);

//    player->stop();
//    player->play();
}

//void MainWindow::onIODeviceUpdateBlockSize(qint64 blockSize)
//{
//    Q_UNUSED(blockSize);
//    return;
////    ui->labBufferSize->setText(QString::asprintf("QAudioInput:bufferSize=%d",recorder->bufferSize()));
////    ui->labBlockSize->setText(QString("IODevice data block size=%1").arg(blockSize));
//}

void MainWindow::on_comboRecorder_currentIndexChanged(int index)
{
//    currentDevice=deviceList[index];

//    ui->comboRecordCodec->clear();
//    for(auto codec:currentDevice.supportedCodecs())
//    {
//        ui->comboRecordCodec->addItem(codec);
//    }

//    ui->comboRecordSampleRate->clear();
//    for(auto rate:currentDevice.supportedSampleRates())
//    {
//        ui->comboRecordSampleRate->addItem(QString("%1").arg(rate));
//    }

//    ui->comboRecordChannel->clear();
//    for(auto channel:currentDevice.supportedChannelCounts())
//    {
//        ui->comboRecordChannel->addItem(QString("%1").arg(channel));
//    }

//    ui->btnBeginRecord->setEnabled(false);
//    ui->btnStopRecord->setEnabled(false);
//    ui->btnReplayRecord->setEnabled(false);
//    ui->sliderRecorderVolumn->setEnabled(false);
}

void MainWindow::on_btnTestDevice_clicked()
{
//    settings.setCodec(ui->comboRecordCodec->currentText());
//    settings.setSampleRate(ui->comboRecordSampleRate->currentText().toInt());
//    settings.setChannelCount(ui->comboRecordChannel->currentText().toInt());
//    settings.setSampleType(currentDevice.supportedSampleTypes()[0]);
//    settings.setSampleSize(currentDevice.supportedSampleSizes()[0]);
//    settings.setByteOrder(currentDevice.supportedByteOrders()[0]);

//    if(currentDevice.isFormatSupported(settings))
//    {
//        QMessageBox::information(this,"音频测试","测试成功，输入设备支持此设置");
//        if(recorder)
//        {
//            delete recorder;
//            recorder=nullptr;
//        }
//        recorder=new QAudioInput(currentDevice,settings,this);
//        ui->btnBeginRecord->setEnabled(true);
//        ui->btnStopRecord->setEnabled(true);
//        ui->btnReplayRecord->setEnabled(true);
//        ui->sliderRecorderVolumn->setEnabled(true);
//    }
//    else
//    {
//        QMessageBox::critical(this,"音频测试","测试失败，输入设备不支持此设置");
//        ui->btnBeginRecord->setEnabled(false);
//        ui->btnStopRecord->setEnabled(false);
//        ui->btnReplayRecord->setEnabled(false);
//        ui->sliderRecorderVolumn->setEnabled(false);
//    }
}

void MainWindow::on_btnBeginRecord_clicked()
{
//    recorder->setBufferSize(waveChartPoints);
//    recorderDataHandler->open(QIODevice::WriteOnly);

//    recorder->start(recorderDataHandler);
//    ui->btnBeginRecord->setEnabled(false);
//    ui->btnStopRecord->setEnabled(true);
//    ui->btnReplayRecord->setEnabled(false);
}

void MainWindow::on_btnStopRecord_clicked()
{
//    recorder->stop();
//    ui->btnBeginRecord->setEnabled(true);
//    ui->btnStopRecord->setEnabled(true);
//    ui->btnReplayRecord->setEnabled(true);
}

void MainWindow::on_sliderRecorderVolumn_valueChanged(int value)
{
    recorder->setVolume(value);
}
