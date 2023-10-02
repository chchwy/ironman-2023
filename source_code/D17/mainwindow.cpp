#include "mainwindow.h"
#include <QImageReader>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QStatusBar>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    m_imageLabel = new QLabel(this);
    setCentralWidget(m_imageLabel);
    setAcceptDrops(true);

    QStatusBar* statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    statusBar->showMessage("Status");
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

    QFileInfo fileInfo(fileName);
    int byteSize = fileInfo.size();

    QString statusInfo = QString("寬高: %1x%2, 檔案大小: %3 Bytes")
                       .arg(newImage.width())
                       .arg(newImage.height())
                       .arg(byteSize);

    statusBar()->showMessage(statusInfo);
}

