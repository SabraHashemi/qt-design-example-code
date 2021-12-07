#include "rgb_yuv.h"
#include "ui_rgb_yuv.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

rgb_yuv::rgb_yuv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rgb_yuv)
{
    ui->setupUi(this);


    ui->label_7->setScaledContents(false);

    ui->pushButton_preview->setText(tr("Preview"));
    ui->pushButton_ok->setText(tr("OK"));
    ui->pushButton_cancel->setText(tr("Cancel"));

    QButtonGroup group;
    group.addButton(ui->radioButtonRGB);
    group.addButton(ui->radioButtonYUV);

    enableRGBorYUV(true);


    int maximumValueForSliders = 100;
    ui->sliderRGB_R->setMaximum(maximumValueForSliders);
    ui->sliderRGB_G->setMaximum(maximumValueForSliders);
    ui->sliderRGB_B->setMaximum(maximumValueForSliders);
    ui->sliderYUV_Y->setMaximum(maximumValueForSliders);
    ui->sliderYUV_U->setMaximum(maximumValueForSliders);
    ui->sliderYUV_V->setMaximum(maximumValueForSliders);
    ui->spinBoxRGB_R->setMaximum(maximumValueForSliders);
    ui->spinBoxRGB_G->setMaximum(maximumValueForSliders);
    ui->spinBoxRGB_B->setMaximum(maximumValueForSliders);
    ui->spinBoxYUV_Y->setMaximum(maximumValueForSliders);
    ui->spinBoxYUV_U->setMaximum(maximumValueForSliders);
    ui->spinBoxYUV_V->setMaximum(maximumValueForSliders);

    ui->sliderRGB_R->setValue(maximumValueForSliders);
    ui->sliderRGB_G->setValue(maximumValueForSliders);
    ui->sliderRGB_B->setValue(maximumValueForSliders);
    ui->sliderYUV_Y->setValue(maximumValueForSliders);
    ui->sliderYUV_U->setValue(maximumValueForSliders);
    ui->sliderYUV_V->setValue(maximumValueForSliders);
}

rgb_yuv::~rgb_yuv()
{
    delete ui;
}

void rgb_yuv::enableRGBorYUV(bool enable)
{
    RGBisEnable = enable;
    if(enable==true){
        ui->radioButtonRGB->setChecked(true);
        ui->radioButtonRGB->setChecked(false);

        ui->sliderRGB_R->setEnabled(true);
        ui->sliderRGB_G->setEnabled(true);
        ui->sliderRGB_B->setEnabled(true);
        ui->spinBoxRGB_R->setEnabled(true);
        ui->spinBoxRGB_G->setEnabled(true);
        ui->spinBoxRGB_B->setEnabled(true);


        ui->sliderYUV_Y->setEnabled(false);
        ui->sliderYUV_U->setEnabled(false);
        ui->sliderYUV_V->setEnabled(false);
        ui->spinBoxYUV_Y->setEnabled(false);
        ui->spinBoxYUV_U->setEnabled(false);
        ui->spinBoxYUV_V->setEnabled(false);


    }else{

        ui->radioButtonRGB->setChecked(false);
        ui->radioButtonYUV->setChecked(true);

        ui->sliderYUV_Y->setEnabled(true);
        ui->sliderYUV_U->setEnabled(true);
        ui->sliderYUV_V->setEnabled(true);
        ui->spinBoxYUV_Y->setEnabled(true);
        ui->spinBoxYUV_U->setEnabled(true);
        ui->spinBoxYUV_V->setEnabled(true);

        ui->sliderRGB_R->setEnabled(false);
        ui->sliderRGB_G->setEnabled(false);
        ui->sliderRGB_B->setEnabled(false);
        ui->spinBoxRGB_R->setEnabled(false);
        ui->spinBoxRGB_G->setEnabled(false);
        ui->spinBoxRGB_B->setEnabled(false);
    }


}


int rgb_yuv::clip_u8(int num)
{
    return (num<0) ? 0 : ((num>255) ? 255 : num);
}



void rgb_yuv::on_radioButtonRGB_pressed()
{
    enableRGBorYUV(true);
}
void rgb_yuv::on_radioButtonYUV_pressed()
{
    enableRGBorYUV(false);
}
void rgb_yuv::on_sliderRGB_R_valueChanged(int value)
{
    ui->spinBoxRGB_R->setValue(value);
    imagehaschanged = true;
}
void rgb_yuv::on_sliderRGB_G_valueChanged(int value)
{
    ui->spinBoxRGB_G->setValue(value);
    imagehaschanged = true;
}
void rgb_yuv::on_sliderRGB_B_valueChanged(int value)
{
    ui->spinBoxRGB_B->setValue(value);
    imagehaschanged = true;
}
void rgb_yuv::on_sliderYUV_Y_valueChanged(int value)
{
    ui->spinBoxYUV_Y->setValue(value);
    imagehaschanged = true;
}

void rgb_yuv::on_sliderYUV_U_valueChanged(int value)
{
    ui->spinBoxYUV_U->setValue(value);
    imagehaschanged = true;
}

void rgb_yuv::on_sliderYUV_V_valueChanged(int value)
{
    ui->spinBoxYUV_V->setValue(value);
    imagehaschanged = true;
}

void rgb_yuv::on_spinBoxRGB_R_valueChanged(int arg1)
{
    ui->sliderRGB_R->setValue(arg1);
    imagehaschanged = true;
}

void rgb_yuv::on_spinBoxRGB_G_valueChanged(int arg1)
{
    ui->sliderRGB_G->setValue(arg1);
    imagehaschanged = true;
}

void rgb_yuv::on_spinBoxRGB_B_valueChanged(int arg1)
{
    ui->sliderRGB_B->setValue(arg1);
    imagehaschanged = true;
}

void rgb_yuv::on_spinBoxYUV_Y_valueChanged(int arg1)
{
    ui->sliderYUV_Y->setValue(arg1);
    imagehaschanged = true;
}

void rgb_yuv::on_spinBoxYUV_U_valueChanged(int arg1)
{
    ui->sliderYUV_U->setValue(arg1);
    imagehaschanged = true;
}

void rgb_yuv::on_spinBoxYUV_V_valueChanged(int arg1)
{
    ui->sliderYUV_V->setValue(arg1);
    imagehaschanged = true;
}


void rgb_yuv::on_pushButton_preview_pressed()
{
    strucRGB rgb;
    if(RGBisEnable == true)
    {
        rgb.r = ui->sliderRGB_R->value();
        rgb.g = ui->sliderRGB_G->value();
        rgb.b = ui->sliderRGB_B->value();

    }else{

        int Y,U,V;
        Y = ui->sliderYUV_Y->value();
        U = ui->sliderYUV_U->value();
        V = ui->sliderYUV_V->value();

        rgb.r = clip_u8(Y               +1.402*V);
        rgb.g = clip_u8(Y   -0.344*U    -0.714*V);
        rgb.b = clip_u8(Y               +1.772*U);
    }


    if(mainImagePath.isEmpty()){


        QMessageBox::information(this,tr("Empty Image"),tr("First open an Image."));
        this->close();

    }

    QImage img_src(mainImagePath);
    QImage img_dst = img_src;

    int width = img_src.size().width();
    int height = img_src.size().height();
    int R,G,B;
    int procentR,procentG,procentB;
    QRgb pixel;

    for (int i=0;i< width;i++) {
        for (int j = 0; j < height; j++) {

            pixel = img_src.pixel(i,j);

            R = qRed(pixel);
            procentR = rgb.r;
            R = std::round(R*procentR/100.);

            G = qGreen(pixel);
            procentG = rgb.g;
            G = std::round(G*procentG/100.);

            B = qBlue(pixel);
            procentB = rgb.b;
            B = std::round(B*procentB/100.);

            img_dst.setPixel(i,j,qRgb(R,G,B));
        }
    }
    QPixmap pix= QPixmap::fromImage(img_dst);
    ui->label_7->setPixmap(pix);
    emit signalRGBYUVcolor(rgb);
}

void rgb_yuv::on_pushButton_preview_released()
{
    strucRGB rgb;
    int percent = 100;
    rgb.r = percent;
    rgb.g = percent;
    rgb.b = percent;

    emit signalRGBYUVcolor(rgb);
}

void rgb_yuv::on_pushButton_cancel_pressed()
{
    strucRGB rgb = {100,100,100};
    emit signalRGBYUVcolor(rgb);
    this->close();
}
void rgb_yuv::on_pushButton_ok_pressed()
{
    on_pushButton_preview_pressed();
    emit signalOkPressed();
    this->close();
}

void rgb_yuv::slotSetFileName(QString filename)
{
    mainImagePath = filename;

    QStringList list = mainImagePath.split(".");
    if(!list.isEmpty()){

        fileSuffix = list.last();

    }else{
        fileSuffix = nullptr;
    }
}

