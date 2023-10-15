#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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

private:
    QLabel* m_imageLabel = nullptr;
};
#endif // MAINWINDOW_H
