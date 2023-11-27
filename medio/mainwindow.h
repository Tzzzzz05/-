
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMovie>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QMediaPlayer *player;
    QMediaPlaylist *playlist;

    QMovie *movie;//声明了一个Qmovie的指针，此指针指向一个类，
    bool flag;
private:
    Ui::MainWindow *ui;
public slots:
    void on_pushButton_5_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_verticalSlider_valueChanged(int value);
    void on_listWidget_currentRowChanged(int currentRow);
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_horizontalSlider_sliderPressed();
    void on_horizontalSlider_sliderReleased();
};

