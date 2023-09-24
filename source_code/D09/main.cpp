#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QLabel* label = new QLabel("請輸入112年 05 ~ 06 月統一發票號碼:");
    QLabel* label2 = new QLabel("");

    QLineEdit* lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText("八位數號碼");
    lineEdit->setFocus();

    QVBoxLayout* layout = new QVBoxLayout;
    w.setLayout(layout);

    layout->addWidget(label);
    layout->addWidget(lineEdit);
    layout->addWidget(label2);

    QObject::connect(lineEdit, &QLineEdit::textChanged, [=]
    {
        if ("29268886" == lineEdit->text())
        {
            label2->setText("<h1>恭喜你！中了特獎1000萬元</h1>");
        }
        else
        {
            label2->setText("您沒有中特獎");
        }
    });

    w.show();
    return a.exec();
}
