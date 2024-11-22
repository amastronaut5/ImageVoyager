#include "miniproj.h"
#include "ui_miniproj.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QFileInfo>

miniproj::miniproj(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::miniprojClass)
{
    ui->setupUi(this);
    //ui->centralWidget->setStyleSheet("background-image: url(:/miniproj/img-FdUJQY8r7g83GxZLt72Qc.jpeg);");
    QPixmap bkgnd(":/miniproj/images (2).jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);
}

miniproj::~miniproj()
{
        delete ui;
}

void miniproj::displayImage(const cv::Mat& img) {
    QImage qImg(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
    qImg = qImg.rgbSwapped();
    ui->imageLabel->setPixmap(QPixmap::fromImage(qImg).scaled(ui->imageLabel->size(), Qt::KeepAspectRatio));

}
void miniproj::saveCurrentState()
{
    undoStack.push(preprocessedImage.clone());  // Save the current state
    while (!redoStack.empty()) redoStack.pop();  // Clear redo stack
}

void miniproj::on_browseButton_clicked()
{    
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Image Files (*.png *.jpg *.bmp *.jpeg)\n All Files");
    if (!fileName.isEmpty()) {
        image = cv::imread(fileName.toStdString());
        if (image.empty()) {
            QMessageBox::warning(this, "Error", "Could not open or find the image!");
            return;
        }

        while (!undoStack.empty()) undoStack.pop();
        while (!redoStack.empty()) redoStack.pop();

        // Save the original image state to undo stack
        undoStack.push(image.clone());


        displayImage(image);
        updateImageInfo(fileName);
    }
}


void miniproj::on_blurButton_clicked()
{
    if (image.empty()) return;

    saveCurrentState();  // Save the current state for undo functionality

    int blurValue = ui->blurSlider->value();  // Get value from the slider

    // Ensure the kernel size is odd and within a safe range
    int kernelSize = (blurValue % 2 == 0) ? blurValue + 1 : blurValue;
    kernelSize = std::max(1, std::min(kernelSize, 31));  // Ensure kernelSize is between 1 and 31

    // Start from the base image to avoid cumulative effects
    preprocessedImage = image.clone();

    // Apply Gaussian blur
    cv::GaussianBlur(preprocessedImage, preprocessedImage, cv::Size(kernelSize, kernelSize), 0);

    // Display the blurred image
    displayImage(preprocessedImage);
}


void miniproj::on_cropButton_clicked()
{
    if (image.empty()) return;
    saveCurrentState();
    
    valuex = ui->axisX->text().toInt();
    valuey = ui->axisY->text().toInt();
    int x = (image.cols - valuex) / 2;
    int y = (image.rows - valuey) / 2;

    if (valuex == NULL || valuey == NULL) {
        QMessageBox::warning(this, "Error !", "Enter both values !");
        return;
    }
    else if (valuex > image.cols) {
        QMessageBox::warning(this, "Error !", "X is greater than the original image width 😂");
        return;
    }
    else if (valuey > image.rows) {
        QMessageBox::warning(this, "Error !", "Y is greater than the original image height😂");
        return;
    }
    cv::Rect region(x, y, valuex,valuey);
    preprocessedImage = image(region).clone();
    displayImage(preprocessedImage);


}

void miniproj::on_grayscaleButton_clicked()
{
    if (image.empty()) return;
    saveCurrentState();
    

    if (isgrayscaled) {
        preprocessedImage = image.clone();
        isgrayscaled = false;
    }
    else {



        cv::cvtColor(image, preprocessedImage, cv::COLOR_BGR2GRAY);
        cv::cvtColor(preprocessedImage, preprocessedImage, cv::COLOR_GRAY2RGB);  // Convert back to RGB for display

        isgrayscaled = true;

    }    
    
    displayImage(preprocessedImage);


}

void miniproj::on_HflipButton_clicked()
{
    if (image.empty()) return;
    saveCurrentState();

    
    if (isflipped) {
        preprocessedImage = image.clone();
        isflipped = false;
    }
    else {
        
        cv::flip(image, preprocessedImage, 1);  // Horizontal flip
        isflipped = true;

    }
    
    displayImage(preprocessedImage);
}

void miniproj::on_VflipButton_clicked()
{
    if (image.empty()) return;
    saveCurrentState();


    if (isflipped) {
        preprocessedImage = image.clone();
        isflipped = false;
    }
    else {

        cv::flip(image, preprocessedImage, 0);  // Vertical flip
        isflipped = true; 

    }

    displayImage(preprocessedImage);

}



void miniproj::on_undoButton_clicked()
{
    if (!undoStack.empty()) {
        // Save current state to redo stack
        if (!preprocessedImage.empty()) {
            redoStack.push(preprocessedImage.clone());
        }

        // Restore previous state from undo stack
        preprocessedImage = undoStack.top();
        undoStack.pop();

        // Update the image and display it
        image = preprocessedImage.clone();
        displayImage(preprocessedImage);
    }
    else {
        QMessageBox::information(this, "Undo", "No more steps to undo.");
    }
}

void miniproj::on_redoButton_clicked()
{
    if (!redoStack.empty()) {
        // Save current state to undo stack
        if (!preprocessedImage.empty()) {
            undoStack.push(preprocessedImage.clone());
        }

        // Restore next state from redo stack
        preprocessedImage = redoStack.top();
        redoStack.pop();

        // Update the image and display it
        image = preprocessedImage.clone();
        displayImage(preprocessedImage);
    }
    else {
        QMessageBox::information(this, "Redo", "No more steps to redo.");
    }
}



void miniproj::on_saturationButton_clicked()
{
    if (image.empty()) return;

    saveCurrentState();

    cv::Mat hsvImage;
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);;

    // Adjust the saturation channel
    int saturationValue = ui->saturationSlider->value();  // Get value from a slider (0 to 100)
    std::vector<cv::Mat> hsvChannels;
    cv::split(hsvImage, hsvChannels);
    hsvChannels[1] = hsvChannels[1] * (saturationValue / 50.0);  // Scale based on slider

    cv::merge(hsvChannels, hsvImage);
    cv::cvtColor(hsvImage, preprocessedImage, cv::COLOR_HSV2BGR);

    displayImage(preprocessedImage);

}


void miniproj::on_hueButton_clicked()
{
    if (image.empty()) return;
    saveCurrentState();
    cv::Mat hsvImage;
    cv::cvtColor(image, hsvImage, cv::COLOR_BGR2HSV);

    // Adjust the hue channel
    int hueValue = ui->hueSlider->value();  // Get value from a slider (-180 to 180)
    std::vector<cv::Mat> hsvChannels;
    cv::split(hsvImage, hsvChannels);
    hsvChannels[0] += hueValue;  // Shift hue by slider value

    cv::merge(hsvChannels, hsvImage);
    cv::cvtColor(hsvImage, preprocessedImage, cv::COLOR_HSV2BGR);

    displayImage(preprocessedImage);

}



void miniproj::on_brightnessButton_clicked()
{
    if (image.empty()) return;

    saveCurrentState();  // Save the current state for undo functionality

    int brightnessValue = ui->brightnessSlider->value();  // Get slider value (-100 to 100)

    // Reset preprocessedImage from the base image (to prevent cumulative changes)
    preprocessedImage = image.clone();

    // Adjust brightness
    preprocessedImage.convertTo(preprocessedImage, -1, 1, brightnessValue);

    // Display the adjusted image
    displayImage(preprocessedImage);
}



/* Let's see if the teacher reads it or not......*/
void miniproj::on_invertButton_clicked()
{
    if (image.empty()) return;
    saveCurrentState();
    cv::bitwise_not(image, preprocessedImage);  // Invert colors
    displayImage(preprocessedImage);
    image = preprocessedImage;

}



void miniproj::on_saveButton_clicked()
{


    if (preprocessedImage.empty()) {
        QMessageBox::warning(this, "Error", "No processed image to save.");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "*.png\n *.jpg\n *.bmp \n *All Files ('.')");
    if (fileName.isEmpty()) {
        return;  // If the user cancels, do nothing
    }

    // Save the processed image
    if (!cv::imwrite(fileName.toStdString(), preprocessedImage)) {
        QMessageBox::warning(this, "Error", "Failed to save image.");
    }
    else {
        QMessageBox::information(this, "Success", "Image saved successfully.");
    }
}


void miniproj::on_gradientButton_clicked()
{
    if (image.empty()) return;

    saveCurrentState();  // Save the current state for undo functionality

    // Clone the original image to reset the effect
    preprocessedImage = image.clone();

    int gradientValue = ui->gradientSlider->value();  // Get value from the gradient slider

    // Ensure gradientValue is between 0 and 100
    if (gradientValue < 0) gradientValue = 0;
    if (gradientValue > 100) gradientValue = 100;

    // Apply gradient based on the slider value
    for (int y = 0; y < image.rows; y++) {
        double alpha = (double)y / image.rows * (gradientValue / 100.0);  // Normalize alpha
        for (int x = 0; x < image.cols; x++) {
            cv::Vec3b color = image.at<cv::Vec3b>(y, x);
            preprocessedImage.at<cv::Vec3b>(y, x) = cv::Vec3b(
                static_cast<uchar>(color[0] * alpha),  // Scale Blue channel
                static_cast<uchar>(color[1] * alpha),  // Scale Green channel
                static_cast<uchar>(color[2] * alpha)   // Scale Red channel
            );
        }
    }

    displayImage(preprocessedImage);  // Display the result
}



















void miniproj::updateImageInfo(const QString& filePath)
{
    if (image.empty()) return;

    QFileInfo fileInfo(filePath);
    QString infoText;

    // Get basic file information
    QString fileName = fileInfo.fileName();
    QString fileSize = QString::number(fileInfo.size() / 1024.0, 'f', 2) + " KB";  // Convert size to KB
    int width = image.cols;
    int height = image.rows;
    int channels = image.channels();
    QString colorDepth = (channels == 1) ? "Grayscale" : (channels == 3 ? "Color (RGB)" : "Unknown");

    // Compile the information text
    infoText += "File Name: " + fileName + "\n";
    infoText += "File Size: " + fileSize + "\n";
    infoText += "Dimensions: " + QString::number(width) + " x " + QString::number(height) + "\n";
    infoText += "Color Depth: " + colorDepth + "\n";
    infoText += "Channels: " + QString::number(channels);

    // Display in the information section
    ui->infoText->setText(infoText);
}
