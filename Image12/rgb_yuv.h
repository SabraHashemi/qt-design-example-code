#ifndef RGB_YUV_H
#define RGB_YUV_H

#include <QDialog>
#include <QGroupBox>
#include <QButtonGroup>


namespace Ui {
class rgb_yuv;
}

class rgb_yuv : public QDialog
{
    Q_OBJECT

public:
    explicit rgb_yuv(QWidget *parent = 0);
    ~rgb_yuv();

    int clip_u8(int num);//Restrict to 0 - 255

    QString mainImagePath="";
    QString fileSuffix="";

    bool imagehaschanged = false;
    bool RGBisEnable = false;

    typedef struct RGB{
        uint8_t r;
        uint8_t g;
        uint8_t b;
    }strucRGB;


public slots:
    void slotSetFileName(QString filename);

signals:
    void signalRGBYUVcolor(strucRGB rgb);
    void signalOkPressed();



private slots:
    void on_radioButtonRGB_pressed();

    void on_radioButtonYUV_pressed();

    void on_sliderRGB_R_valueChanged(int value);

    void on_sliderRGB_G_valueChanged(int value);

    void on_sliderRGB_B_valueChanged(int value);

    void on_sliderYUV_Y_valueChanged(int value);

    void on_sliderYUV_U_valueChanged(int value);

    void on_sliderYUV_V_valueChanged(int value);

    void on_spinBoxRGB_R_valueChanged(int arg1);

    void on_spinBoxRGB_G_valueChanged(int arg1);

    void on_spinBoxRGB_B_valueChanged(int arg1);

    void on_spinBoxYUV_Y_valueChanged(int arg1);

    void on_spinBoxYUV_U_valueChanged(int arg1);

    void on_spinBoxYUV_V_valueChanged(int arg1);

    void on_pushButton_ok_pressed();

    void on_pushButton_preview_released();

    void on_pushButton_preview_pressed();

    void on_pushButton_cancel_pressed();



private:
    Ui::rgb_yuv *ui;


    void enableRGBorYUV(bool en);


};

#endif // RGB_YUV_H
