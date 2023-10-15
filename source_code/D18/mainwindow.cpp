#include "mainwindow.h"
#include <QImageReader>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QStatusBar>
#include <QFileInfo>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    m_imageLabel = new QLabel(this);
    setCentralWidget(m_imageLabel);
    setAcceptDrops(true);

    QStatusBar* statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    statusBar->showMessage("Status");

    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu* fileMenu = menuBar->addMenu("檔案");
    QMenu* aboutMenu = menuBar->addMenu("關於");

    QAction* openAction = new QAction("開啟圖片");
    QAction* exitAction = new QAction("離開程式");
    QAction* aboutQtAction = new QAction("關於Qt");

    fileMenu->addAction(openAction);
    fileMenu->addAction(exitAction);
    aboutMenu->addAction(aboutQtAction);

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitApp);
    connect(aboutQtAction, &QAction::triggered, this, &MainWindow::about);
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

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("開啟圖片"), "", "Images (*.png *.jpg)");
    if (!fileName.isEmpty())
        loadImage(fileName);
}

void MainWindow::exitApp()
{
    close();
}

void MainWindow::about()
{
    QApplication::aboutQt();
}

