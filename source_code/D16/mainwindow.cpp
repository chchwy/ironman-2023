#include "mainwindow.h"
#include <QImageReader>
#include <QDragEnterEvent>
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_imageLabel = new QLabel(this);
    setCentralWidget(m_imageLabel);
    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls())
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent* event)
{
    const QUrl url = event->mimeData()->urls().first();
    const QString filePath = url.toLocalFile();

    loadImage(filePath);
    event->acceptProposedAction();
}

void MainWindow::loadImage(const QString& fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    Q_ASSERT(!newImage.isNull());
    m_imageLabel->setPixmap(QPixmap::fromImage(newImage));
}

