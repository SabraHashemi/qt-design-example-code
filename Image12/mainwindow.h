#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define APPLICATION_NAME "Image1"
#define MODIFICATION_WARNING "The image was modified, do you want to save it?"
#define ABOUT_TEXT "Created by Herr Ali Jahanbakhsh  (see Help -> About Qt)"

#include <QMainWindow>
#include <QtPrintSupport>
#include <algorithm>
#include <QClipboard>
#include <QFileDialog>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include "rgb_yuv.h"





#define DEFAULT_PATH        ""
#define DEFAULT_ZOOM_VALUE  100
#define DEFAULT_ZOOM(val)   ("Zoom "+QString::number(val)+" %")


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
            void save();
            bool maybeSave();
            void closeEvent(QCloseEvent *event);
            QLabel *statusBarLabelPath;
            QLabel *statusBarLabelZoom;
            void initStausBarText();
            void setStausBarTextPath(QString path=DEFAULT_PATH);
            void setStausBarTextZoom(int zoom=DEFAULT_ZOOM_VALUE);
            QString getStausBarText();

            QTranslator translator;
            void selectedLanguage(QString language="");



private slots:
    void on_actionExit_triggered();

    void on_actionOpen_triggered();

    void on_actionNew_triggered();


    void on_actionPrint_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionCut_triggered();



    void on_actionAbout_Qt_triggered();

    void on_actionAbout_triggered();




    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

    void on_action100_Zoom_triggered();

    void on_actionFit_to_Window_triggered();

    void on_actionSave_as_triggered();

    void on_actionDark_Mode_triggered();

    void on_actionSave_triggered();

    void on_actionRGB_YUVedit_triggered();

    void on_actionActionFont_triggered();

    void on_actionGerman_triggered();

    void on_actionEnglish_triggered();

private:
    bool modified = false;

        float zoomFactor = 1;
        QImage img;
        void applyZoom(float);
        void applyZoom();
        QPixmap pixmap;
        float calcFittingZoom();
        QString filePath = "";
        QList<QString> lastEditFiles;


        int Startmouse_X = 0;
        int Startmouse_Y = 0;

        Ui::MainWindow *ui;
        void openFile(QString);


        //mouse events
        void mousePressEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);
        void mouseMoveEvent(QMouseEvent *e);
        void wheelEvent(QWheelEvent *event);

        bool fileChanged= false;




         rgb_yuv second;
         QImage image;

        typedef struct RGB{
            uint8_t r;
            uint8_t g;
            uint8_t b;
        }strucRGB;

    public slots:
        void slotRGBYUVcolor(strucRGB rgb);
        void slotOkPressed();

    signals:
        void signalSetFileName(QString filename);


};
#endif
