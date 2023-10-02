#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QVBoxLayout* layout = new QVBoxLayout;
    w.setLayout(layout);

    //創建下拉選單，添加選項
    QComboBox* comboBox = new QComboBox;
    comboBox->addItem("台灣銀行", "004");
    comboBox->addItem("土地銀行", "005");
    comboBox->addItem("第一銀行", "007");
    comboBox->addItem("華南銀行", "008");
    comboBox->addItem("中華郵政", "700");

    //接著創建一個標籤來顯示郵遞區號查詢結果
    QLabel* label = new QLabel;

    layout->addWidget(label);
    layout->addWidget(comboBox);

    QObject::connect(comboBox, &QComboBox::activated, [=]
    {
        QString bankName = comboBox->currentText();
        QString bankCode = comboBox->currentData().toString();

        label->setText(bankName + "的轉帳代號是" + bankCode);
    });

    w.show();
    return a.exec();
}
