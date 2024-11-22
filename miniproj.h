#ifndef MINIPROJ_H
#define MINIPROJ_H



#include <QtWidgets/QMainWindow>
#include "ui_miniproj.h"

#include <opencv2/opencv.hpp>
#include <stack>


QT_BEGIN_NAMESPACE
namespace Ui { class miniprojClass; }
QT_END_NAMESPACE

class miniproj : public QMainWindow
{
    Q_OBJECT

public:
    miniproj(QWidget* parent = nullptr);
    ~miniproj();

private slots:
    void on_browseButton_clicked();
    void on_blurButton_clicked();
    void on_cropButton_clicked();
    void on_grayscaleButton_clicked();
    void on_HflipButton_clicked();
    void on_VflipButton_clicked();
    void on_saveButton_clicked();
    void on_saturationButton_clicked();
    void on_hueButton_clicked();
    void on_brightnessButton_clicked();
    void on_invertButton_clicked();
    void on_undoButton_clicked();
    void on_gradientButton_clicked();
    void on_redoButton_clicked();
    void updateImageInfo(const QString& filePath);

private:
    Ui::miniprojClass *ui;
    cv::Mat image;
    int valuex;
    int valuey;
    cv::Mat originalImage;
    cv::Mat preprocessedImage;
    bool isflipped = false;//checks if image is flipped or not ...
    bool isgrayscaled = false;
    std::stack<cv::Mat> undoStack;
    std::stack<cv::Mat> redoStack;

    void saveCurrentState();  // Save current image state to undo stack

    

    void displayImage(const cv::Mat& img);
};

#endif // !MINIPROJ_H