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
        QRegularExpression reg("^((https?|ftp|smtp):\\/\\/)?(www.)?[a-z0-9]+\\.[a-z]+(\\/[a-zA-Z0-9#]+\\/?)*$");
        QRegularExpressionMatch match = reg.match(argv[1]);

        if (match.hasMatch())
            URL = QUrl(argv[1]);
        else
            return invalidArgument(QString("Invalid URL: " + QString(argv[1])));
    }
    else
        URL = QUrl("http://www.google.com");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.loadURL(URL);
    mainWindow.show();

    return app.exec();
}
