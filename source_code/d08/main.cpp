#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QSlider>
#include <QSpinBox>
#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QLabel* label = new QLabel("溫度：");

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

    layout->addWidget(label);
    layout->addWidget(slider);
    layout->addWidget(spinbox);

    QObject::connect(slider, &QSlider::valueChanged, spinbox, &QSpinBox::setValue);
    QObject::connect(spinbox, &QSpinBox::valueChanged, slider, &QSlider::setValue);

    w.show();
    return a.exec();
}
