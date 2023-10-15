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
    m_imageLabel->setBackgroundRole(QPalette::Base);

    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setBackgroundRole(QPalette::Dark);
    m_scrollArea->setWidget(m_imageLabel);
    setCentralWidget(m_scrollArea);

    setAcceptDrops(true);

    QStatusBar* statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    statusBar->showMessage("Status");

    QMenuBar* menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu* fileMenu = menuBar->addMenu("檔案");
    QMenu* viewMenu = menuBar->addMenu("瀏覽");
    QMenu* aboutMenu = menuBar->addMenu("關於");

    QAction* openAction = new QAction("開啟圖片");
    QAction* exitAction = new QAction("離開程式");
    QAction* aboutQtAction = new QAction("關於Qt");
    QAction* prevImgAction = new QAction("上一張");
    QAction* nextImgAction = new QAction("下一張");

    prevImgAction->setShortcut(QKeySequence(Qt::Key_Left));
    nextImgAction->setShortcut(QKeySequence(Qt::Key_Right));

    fileMenu->addAction(openAction);
    fileMenu->addAction(exitAction);
    aboutMenu->addAction(aboutQtAction);
    viewMenu->addAction(prevImgAction);
    viewMenu->addAction(nextImgAction);

    connect(openAction, &QAction::triggered, this, &MainWindow::openFile);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitApp);
    connect(aboutQtAction, &QAction::triggered, this, &MainWindow::about);
    connect(prevImgAction, &QAction::triggered, this, &MainWindow::prevImage);
    connect(nextImgAction, &QAction::triggered, this, &MainWindow::nextImage);

    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
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
    m_imageLabel->resize(newImage.size());

    QFileInfo fileInfo(fileName);
    int byteSize = fileInfo.size();

    QString statusInfo = QString("寬高: %1x%2, 檔案大小: %3 Bytes")
                       .arg(newImage.width())
                       .arg(newImage.height())
                       .arg(byteSize);

    statusBar()->showMessage(statusInfo);

    m_currentImageName = fileInfo.fileName();
    m_currentDir = fileInfo.dir();
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

void MainWindow::prevImage()
{
    QStringList nameFilter{"*.jpg", "*.png"};
    QFileInfoList files = m_currentDir.entryInfoList(nameFilter);
    int currentImgIndex = -1;
    for (int i = 0; i < files.size(); ++i)
    {
        if (files[i].fileName() == m_currentImageName)
        {
            currentImgIndex = i;
            break;
        }
    }
    int prevImgIndex = currentImgIndex - 1;
    if (prevImgIndex < 0)
        return;
    loadImage(files[prevImgIndex].absoluteFilePath());
}

void MainWindow::nextImage()
{
    QStringList nameFilter{"*.jpg", "*.png"};
    QFileInfoList files = m_currentDir.entryInfoList(nameFilter);
    int currentImgIndex = -1;
    for (int i = 0; i < files.size(); ++i)
    {
        if (files[i].fileName() == m_currentImageName)
        {
            currentImgIndex = i;
            break;
        }
    }
    int nextImgIndex = currentImgIndex + 1;
    if (nextImgIndex < 0 || nextImgIndex >= files.size())
        return;
    loadImage(files[nextImgIndex].absoluteFilePath());
}

