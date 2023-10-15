#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QDir>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

    void loadImage(const QString& filepath);

    void openFile();
    void exitApp();
    void about();

    void prevImage();
    void nextImage();

private:
    QLabel* m_imageLabel = nullptr;
    QString m_currentImageName;
    QDir m_currentDir;
};
#endif // MAINWINDOW_H
