#include "mainwindow.h"
#include <QImageReader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_imageLabel = new QLabel(this);
    setCentralWidget(m_imageLabel);

    QString fileName = "C:/temp/taipei-101.jpg";
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
    }
    m_imageLabel->setPixmap(QPixmap::fromImage(newImage));
}

MainWindow::~MainWindow()
{
}

