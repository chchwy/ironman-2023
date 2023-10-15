#include <QApplication>
#include <QLabel>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    bool ok = translator.load("my_translation.qm");
    qDebug() << ok;
    app.installTranslator(&translator);

    QLabel* label = new QLabel(QObject::tr("Hello World!"));
    label->show();
    return app.exec();
}
