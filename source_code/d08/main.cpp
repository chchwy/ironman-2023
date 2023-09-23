#include <QApplication>
#include <QWidget>
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QSlider* slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    slider->setMaximum(100);
    slider->setMinimum(0);
    slider->setValue(50);

    QSpinBox* spinbox = new QSpinBox;
    spinbox->setMaximum(100);
    spinbox->setMinimum(0);
    spinbox->setValue(50);
    spinbox->setPrefix("攝氏");
    spinbox->setSuffix("度");

    QHBoxLayout* layout = new QHBoxLayout;
    w.setLayout(layout);

    //layout->addWidget(slider);
    layout->addWidget(spinbox);

    w.show();
    return a.exec();
}
