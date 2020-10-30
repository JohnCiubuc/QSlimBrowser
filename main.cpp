#include "mainwindow.h"

#include <QDebug>
#include <QApplication>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

int invalidArgument(QString error = nullptr)
{
    if(!error.isNull())
        qErrnoWarning(-1, error.toLocal8Bit());
    qErrnoWarning(-1, "Usage: qslimbrowser [URL]\n\n\tQSlimBrowser loads a selected url into a slim, browser experience.");
    return -1;
}

int main(int argc, char *argv[])
{
    QUrl URL;
    if (argc == 2)
    {
        QRegularExpression reg("(http|ftp|https)://([\\w_-]+(?:(?:\\.[\\w_-]+)+))([\\w.,@?^=%&:/~+#-]*[\\w@?^=%&/~+#-])?");
        QRegularExpressionMatch match = reg.match(argv[1]);

        if (match.hasMatch())
            URL = QUrl(argv[1]);
        else
            return invalidArgument(QString("Invalid URL: " + QString(argv[1])));
    }
    else
//        URL = QUrl("http://www.google.com");
        URL = QUrl("https://ads-blocker.com/testing/#ad-blocker-test-steps");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.loadURL(URL);
    mainWindow.show();

    return app.exec();
}
