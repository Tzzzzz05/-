#include "mainwindow.h"//主窗口类的头文件
#include "ui_mainwindow.h"//Qt Designer 自动生成的用户界面类的头文件。
#include <QUrl>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
  //传递 parent 参数是为了告诉 Qt 框架，新创建的 MainWindow 对象的父对象应该是 parent 参数所指向的 QWidget 对象。
  //这样，MainWindow 就成为了 parent 指向的对象的子对象。
{
    ui->setupUi(this);
    /*用来将用户界面初始化并连接到你的 MainWindow 对象上，
     * 以便你可以通过 ui 指针访问和操作主窗口中的界面元素。
     * 例如，你可以使用 ui 来访问按钮和标签等元素，并在需要时更改它们的属性、文本等。*/

    this->player = new QMediaPlayer(this); //初始化了一个QmediaPlay的指针对象
    this->playlist = new QMediaPlaylist(this);//初始化了一个QmediaPlaylist的指针对象

    this->flag = false; // Slider release

    this->player->setPlaylist(this->playlist);//再将这个媒体播放列表放入到这个媒体播放家里面

    this->playlist->addMedia(QMediaContent(QUrl("qrc:/music/sound/小苹果.mp4")));
    this->playlist->addMedia(QMediaContent(QUrl("qrc:/music/sound/爱如火.mp3")));
    this->playlist->addMedia(QMediaContent(QUrl("qrc:/music/sound/蓝莲花.mp3")));
    this->playlist->addMedia(QMediaContent(QUrl("qrc:/music/sound/2983329198.mp3")));
    //完成一个显示模块的显示
    //表示为使得ui界面的QLable显示我们的动态图
    //参数为 QMovie *movie
    //1、先包含QMovie 头文件
    //2、在.h文件里面 声明一个QMovie 的指针
    //3、将QMovie 的指针放入到setMovie 里面

//    ui->label_4->setFixedWidth(400); // 设置QLabel的宽度为200像素
//    ui->label_4->setFixedHeight(200); // 设置QLabel的高度为200像素

    this->movie=new QMovie(":/new/prefix1/666.gif");//放置路劲
    ui->label_4->setMovie(this->movie);//动置动态图
    //注意：当你设置了 QMovie 但是你没有 启动 他是不会显示的
    //由于图片过大 但是 QLable 太小，因此导致图片显示不完全
    //因此需要加一行代码
    ui->label_4->setScaledContents(true);
    this->playlist->setPlaybackMode(QMediaPlaylist:: Loop);
    this->player->setVolume(50);
    ui->verticalSlider->setRange (0, 100);
    ui->verticalSlider->setValue(50);
    ui->listWidget->addItem("小苹果.mp4");
    ui->listWidget->addItem("爱如火.mp3");
    ui->listWidget->addItem("蓝莲花.mp3");
    ui->listWidget->addItem("好汉歌.mp4 ");

    connect(this->playlist,&QMediaPlaylist::currentIndexChanged,this,[=](int ipos){
        ui->listWidget->setCurrentRow(ipos);
    });

    connect(this->player,&QMediaPlayer::positionChanged,this, [=](int time){
        qDebug()<<time;
        if(this->flag == false){
            ui->horizontalSlider->setValue(time);
        }
        int total_mes = time/1000;
        int min = total_mes/60;
        int mes = total_mes%60;
        QString Min_text = QString::number(min);
        QString Mes_text= QString::number(mes);
        if(Min_text.size() < 2){
            Min_text = "0" + Min_text;
        }
        if(Mes_text.size() < 2){
            Mes_text = "0" + Mes_text;
        }

        ui->label_5->setText(Min_text + ":" + Mes_text);
    });

    connect(this->player,&QMediaPlayer::durationChanged,this, [=](int time){
         qDebug()<<time;
        ui->horizontalSlider->setRange (0, time);

        int total_mes = time/1000;
        int min = total_mes/60;
        int mes = total_mes%60;
        QString Min_text = QString::number(min);
        QString Mes_text= QString::number(mes);
        if(Min_text.size() < 2){
            Min_text = "0" + Min_text;
        }
        if(Mes_text.size() < 2){
            Mes_text = "0" + Mes_text;
        }

        ui->label_6->setText(Min_text + ":" + Mes_text);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_5_clicked()
{
    if (ui->pushButton_5->text() == "播放")
    {
        this->player->play();

        ui->pushButton_5->setText("暂停");

        this->movie->start();
    }
    else if (ui->pushButton_5->text() == "暂停")
    {
        this->player->pause();
        ui->pushButton_5->setText("播放");
        this->movie->stop();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    this->playlist->previous();
}

void MainWindow::on_pushButton_6_clicked()
{
    this->playlist->next();
}



void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    //参数 arg1 代表更改后的文本的信息
    if(arg1=="列表循环")
    {
        this->playlist->setPlaybackMode(QMediaPlaylist::Loop);

    }else if(arg1=="单曲循环")
    {
        this->playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }else if(arg1=="随机循环"){
        this->playlist->setPlaybackMode(QMediaPlaylist::Random);
    }

}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    this->player->setVolume(value);
}

void MainWindow::on_listWidget_currentRowChanged(int currentRow)
{
    this->playlist->setCurrentIndex(currentRow);
    this->player->play();
    ui->pushButton_5->setText("暂停");
    this->movie->start();
}

void MainWindow::on_pushButton_3_clicked()
{
   int index = ui->listWidget->currentRow();
   if(this->playlist->removeMedia(index)){
       ui->listWidget->takeItem(index);
   }
}

void MainWindow::on_pushButton_2_clicked()
{
    QStringList data = QFileDialog::getOpenFileNames (this, "选择音乐","D:\\QTproducts\\medio\\sound","*.mp3 *.mp4");
    for(int i = 0;i < data.size();i++){
        this->playlist->addMedia(QMediaContent(QUrl::fromLocalFile(data[i])));
        QFileInfo info(data[i]);
        ui->listWidget->addItem(info.fileName());
    }
}

void MainWindow::on_horizontalSlider_sliderPressed()
{
    this->flag = true;
}

void MainWindow::on_horizontalSlider_sliderReleased()
{
    this->flag = false;
    int current_val = ui->horizontalSlider->value();
    this->player->setPosition(current_val);

}















