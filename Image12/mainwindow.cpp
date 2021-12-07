#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFontDialog>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "rgb_yuv.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   ui->scrollArea->setBackgroundRole(QPalette::Dark);
   setWindowTitle("");
   setWindowIcon(QIcon(":/imgs/appIcon.ico"));
   initStausBarText();
   selectedLanguage();



}

void MainWindow::applyZoom(float newZoomFactor)
{
   zoomFactor = newZoomFactor;
   applyZoom();
}
void MainWindow::applyZoom()
{

    bool flag = false;

    if(zoomFactor*100 <=25){
        //enableZoomOut(false);
        flag = true;
    }else{
        //enableZoomOut();
    }

    if(zoomFactor*100 >= 400){
        //enableZoomIn(false);
        flag = true;
    }else{
       // enableZoomIn();
    }

    if(flag == false){
        ui->picLabel->setPixmap(pixmap.scaled(pixmap.size() * zoomFactor, Qt::KeepAspectRatio));
        setStausBarTextZoom(zoomFactor*100);

    }




}

MainWindow::~MainWindow()
{
   delete ui;
}
bool MainWindow::maybeSave()
{
   if (fileChanged)
   {
       auto ret = QMessageBox::warning(this, APPLICATION_NAME,
       MODIFICATION_WARNING, QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

       if (ret == QMessageBox::Save)
           save();
       else if (ret == QMessageBox::Discard)
           return true;
       else
           return false;
   }
   return true;
}

void MainWindow::save()
{
    QImage img  = ui->picLabel->pixmap()->toImage();

    if(img.save(filePath) == false)
    {
        QMessageBox::information(this,tr("Failed to save image"),tr("Could not save Image. Make sure you have write permission on the folder"));
    }

        int found = lastEditFiles.indexOf(filePath);
        if(found == -1){
            //File not found in list
            lastEditFiles.append(filePath);
        }

        fileChanged=false;
}


void MainWindow::on_actionNew_triggered()
{
   {
       if(!maybeSave())
           return;
       pixmap = QPixmap(0, 0);
       applyZoom(1);
   }
}
void MainWindow::closeEvent(QCloseEvent *event)
{
   if(maybeSave())
       event->accept();
   else
       event->ignore();
}

void MainWindow::on_actionOpen_triggered()
{
   if(!maybeSave())
       return;

   QString fileName = QFileDialog::getOpenFileName(this,
                                                       tr("Open File"),
                                                       QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).last(),
                                                       tr("Images (*.png *.bmp *.jpg *.jpeg)")
                                                       );
   if(! fileName.isEmpty()){
       filePath=fileName;
       openFile(fileName);

   }else{
       QMessageBox::information(this,tr("open file"),tr("Please select *png , *.bmp , *jpg , *jpeg image "));
   }
//   QString fileName = QFileDialog::getOpenFileName(this, tr("Open file for edit") );
//   openFile(fileName);

}

//void MainWindow::on_actionSave_as_triggered()
//{
//   QString fileName = QFileDialog::getSaveFileName(this, "Save as");
  // QFile file(fileName);
 //  if (!file.open(QFile::WriteOnly | QFile::Text)) {
    //       QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
       //    return;
     //  }

  // setWindowTitle(fileName);
  // QTextStream out(&file);
  // QString text = ui->textEdit->toPlainText();
  // out << text;
  // file.close();
//}

void MainWindow::on_actionPrint_triggered()
{
   QPrinter printer;

    QPrintDialog pDialog(&printer, this);
    if(pDialog.exec() == QDialog::Rejected)

            return;
}


void MainWindow::openFile(QString fname)
{
    if(fileChanged == true){
    maybeSave();
    }
   img = QImage(fname);
   pixmap = QPixmap::fromImage(img);
   applyZoom(1);

   setStausBarTextPath(fname);
   fileChanged=false;



//void MainWindow::on_actionUndo_triggered()
//{
  // ui->textEdit->undo();
//}

//void MainWindow::on_actionRedo_triggered()
//{
 //  ui->textEdit->redo();
//}


//void MainWindow::on_actionGerman_triggered()
//{
  // QString title = QWidget::windowTitle();
 //  selectLanguage(tr("de_DE"));
 //  setWindowTitle(title);
//}
//void loadLanguage(const QLocale&rlocale);
//{
//qApp->removeeTralator(&m_translator);
//}









}
float MainWindow::calcFittingZoom()
{
   QSize imageSize = ui->picLabel->size();
   QSize widgetSize = ui->scrollArea->size();
   float newZoom = min((float)widgetSize.width() / (float)imageSize.width(), (float)widgetSize.height() / (float)imageSize.height());
   return newZoom - 0.02; // `scrollArea`
}

void MainWindow::on_actionFit_to_Window_triggered()
{

   applyZoom(calcFittingZoom());
}
void MainWindow::on_actionPaste_triggered()
{
   QPixmap cPixmap = QGuiApplication::clipboard()->pixmap();
   if (!cPixmap.isNull())
   {
       pixmap = cPixmap;
       applyZoom(1);
   }
}
void MainWindow::on_actionCopy_triggered()
{
   QGuiApplication::clipboard()->setPixmap(pixmap);
}
void MainWindow::on_actionCut_triggered()
{
   on_actionCopy_triggered();
       on_actionNew_triggered();
}

void MainWindow::on_actionExit_triggered()
{
   if(maybeSave()){
   QApplication::quit();}
}

void MainWindow::on_actionZoom_in_triggered()
{
   applyZoom(zoomFactor * 1.1);
}

void MainWindow::on_actionZoom_out_triggered()
{
   applyZoom(zoomFactor * 0.9);
}

void MainWindow::on_action100_Zoom_triggered()
{
  applyZoom(1);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About " APPLICATION_NAME), tr(ABOUT_TEXT));

}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));

}

void MainWindow::on_actionSave_as_triggered()
{
   QString pathFileName= QFileDialog::getSaveFileName(this,tr("Save File as"),filePath,tr("Images (*.png *.jpeg *.jpg *.bmp)"));
       if(! pathFileName.isEmpty())
       {
           filePath = pathFileName;
           on_actionSave_triggered();
       }
}

void MainWindow::initStausBarText()
{
    statusBarLabelPath = new QLabel;
    statusBarLabelZoom = new QLabel;

    statusBarLabelPath->setText(DEFAULT_PATH);
    statusBarLabelPath->setAlignment(Qt::AlignLeft);

    statusBarLabelZoom->setText(DEFAULT_ZOOM(DEFAULT_ZOOM_VALUE));
    statusBarLabelZoom->setAlignment(Qt::AlignRight);

    ui->statusbar->addWidget(statusBarLabelPath);
    ui->statusbar->addWidget(statusBarLabelZoom,1);
}
void MainWindow::setStausBarTextPath(QString path)
{
    statusBarLabelPath->setText(path);
}
void MainWindow::setStausBarTextZoom(int zoom)
{
    statusBarLabelZoom->setText(DEFAULT_ZOOM(zoom));
}
QString MainWindow::getStausBarText()
{
    return this->statusBar()->currentMessage();
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
   Startmouse_X = event->x();
   Startmouse_Y = event->y();
   setCursor(Qt::ClosedHandCursor);
   event->accept();
   return;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    ui->scrollArea->horizontalScrollBar()->setValue(ui->scrollArea->horizontalScrollBar()->value() - (event->x() - Startmouse_X));
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->value() - (event->y() - Startmouse_Y));
    Startmouse_X = event->x();
    Startmouse_Y = event->y();
    event->accept();
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    event->accept();
    return;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15;

    if(numSteps >0){
        applyZoom(zoomFactor * 1.1);

    }else{
        applyZoom(zoomFactor * 0.8);
    }
    event->accept();
}


void MainWindow::on_actionDark_Mode_triggered()
{

        if(ui->actionDark_Mode->text() ==tr("Dark Mode"))
        {
            //Window ist in White Mode and will be dark now
            ui->actionDark_Mode->setText(tr("White Mode"));

            qApp->setStyle(QStyleFactory::create("Fusion"));
            QPalette darkPalette;

            darkPalette.setColor(QPalette::Window, QColor(53,53,53));
            darkPalette.setColor(QPalette::WindowText, Qt::white);
            darkPalette.setColor(QPalette::Base, QColor(25,25,25));
            darkPalette.setColor(QPalette::AlternateBase, QColor(53,53,53));
            darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
            darkPalette.setColor(QPalette::ToolTipText, Qt::white);
            darkPalette.setColor(QPalette::Text, Qt::white);
            darkPalette.setColor(QPalette::Button, QColor(53,53,53));
            darkPalette.setColor(QPalette::ButtonText, Qt::white);
            darkPalette.setColor(QPalette::BrightText, Qt::red);
            darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
            darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
            darkPalette.setColor(QPalette::HighlightedText, Qt::black);

            qApp->setPalette(darkPalette);
            qApp->setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");

        }else{
            //Window ist in Dark Mode and will be white now
            ui->actionDark_Mode->setText(tr("Dark Mode"));

            qApp->setStyle(QStyleFactory::create("White Mode"));
            QPalette whitePalette;

            whitePalette.setColor(QPalette::Window, QColor(255,255,255));
            whitePalette.setColor(QPalette::WindowText, QColor(38,38,38));
            whitePalette.setColor(QPalette::Base, QColor(255,255,255));
            whitePalette.setColor(QPalette::AlternateBase, QColor(217,217,217));
            whitePalette.setColor(QPalette::ToolTipBase, Qt::white);
            whitePalette.setColor(QPalette::ToolTipText, Qt::white);
            whitePalette.setColor(QPalette::Text, QColor(38,38,38));
            whitePalette.setColor(QPalette::Button, QColor(217,217,217));
            whitePalette.setColor(QPalette::ButtonText, QColor(38,38,38));
            whitePalette.setColor(QPalette::BrightText, QColor(38,38,38));
            whitePalette.setColor(QPalette::Link, QColor(255, 255, 255));
            whitePalette.setColor(QPalette::Highlight, QColor(255, 255, 255));
            whitePalette.setColor(QPalette::HighlightedText, Qt::white);

            qApp->setPalette(whitePalette);
            qApp->setStyleSheet("QToolTip { color: #000000; background-color: #ffffff; border: 1px solid white; }");
        }


}



void MainWindow::on_actionSave_triggered()
{
//    maybeSave();
    QImage img  = ui->picLabel->pixmap()->toImage();
    fileChanged=false;

    if(img.save(filePath) == false)
    {
        QMessageBox::information(this,tr("Failed to save image"),tr("Could not save Image. Make sure you have write permission on the folder"));
    }
    fileChanged=false;

}

void MainWindow::on_actionRGB_YUVedit_triggered()
{

    connect(&second,SIGNAL(signalOkPressed()),this,SLOT(slotOkPressed()));

    connect(this,SIGNAL(signalSetFileName(QString)),&second,SLOT(slotSetFileName(QString)));

    connect(&second,SIGNAL(signalRGBYUVcolor(strucRGB)),this,SLOT(slotRGBYUVcolor(strucRGB)));

    emit signalSetFileName(filePath);

    second.setModal(false);
    second.show();

}
void MainWindow::slotOkPressed()
{
    QImage img = ui->picLabel->pixmap()->toImage();
    image = img;
    fileChanged=true;
}
void MainWindow::slotRGBYUVcolor(strucRGB strucrgb)
{
    QImage img_src(filePath);
    QImage img_dst = img_src;

    int width = img_src.size().width();
    int height = img_src.size().height();
    int R,G,B;
    int procentR,procentG,procentB;
    QRgb pixel;

    // Jeden Pixel manipulieren
    for (int i=0;i< width;i++) {
        for (int j = 0; j < height; j++) {

            pixel = img_src.pixel(i,j);

            R = qRed(pixel);
            procentR = strucrgb.r;
            R = std::round(R*procentR/100.);// Sich die Prozentzahl ausrechnen

            G = qGreen(pixel);
            procentG = strucrgb.g;
            G = std::round(G*procentG/100.);

            B = qBlue(pixel);
            procentB = strucrgb.b;
            B = std::round(B*procentB/100.);

            img_dst.setPixel(i,j,qRgb(R,G,B));
        }
    }
    QPixmap pix= QPixmap::fromImage(img_dst);
    ui->picLabel->setPixmap(pix);
}

void MainWindow::on_actionActionFont_triggered()
{
bool ok;
QFont font=QFontDialog::getFont(&ok,this);
if(ok){

    qApp->setFont(font);

}
else{

    QApplication::font();
}
}

void MainWindow::on_actionGerman_triggered()
{
    selectedLanguage(tr("de_DE"));
}

void MainWindow::on_actionEnglish_triggered()
{
    selectedLanguage(tr("en_GB"));

}

void MainWindow::selectedLanguage(QString language)
{
    qApp->removeTranslator(&translator);
    if(language.isEmpty()){
        language = QLocale::system().name();
    }

    if(language == tr("de_DE")){
        translator.load(":/German.qm");
    }else{

        translator.load(":/English.qm");
    }
    qApp->installTranslator(&translator);
    const QPixmap *pix = ui->picLabel->pixmap();
    if (pix == nullptr) {
        ui->retranslateUi(this);
    }else {
        QPixmap a= *pix;
        ui->retranslateUi(this);
        ui->picLabel->setPixmap(a);
    }
}

