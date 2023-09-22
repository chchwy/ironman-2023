#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget w;

    QVBoxLayout* layout = new QVBoxLayout;
    w.setLayout(layout);

    QLabel* label = new QLabel("<h1>0</h1>");
    QPushButton* button = new QPushButton("產生亂數");

    layout->addWidget(label);
    layout->addWidget(button);

    QObject::connect(button, &QPushButton::clicked, [=]
    {
        // 按鈕的點擊事件(clicked)發生後，就執行這個 lambda!
        label->setText("<h1>" + QString::number(rand() % 100) + "</h1>");
    });
    w.show();
    return app.exec();
}
