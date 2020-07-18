#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_view(new QWebEngineView(this))
{
    setCentralWidget(m_view);
    setStyle("::-webkit-scrollbar {width: 12px;} ::-webkit-scrollbar-track {-webkit-box-shadow: inset 0 0 6px rgba(0,0,0,0.3); -webkit-border-radius: 10px; border-radius: 10px;} ::-webkit-scrollbar-thumb {    -webkit-border-radius: 10px; border-radius: 10px; background: rgba(255,255,0,0.8); -webkit-box-shadow: inset 0 0 6px rgba(0,0,0,0.5); } ::-webkit-scrollbar-thumb:window-inactive {background: rgba(255,0,0,0.4); }");
}

void MainWindow::loadURL(QUrl URL)
{
    m_view->page()->load(URL);
}

void MainWindow::setStyle(const QString data)
{
    QTemporaryFile file;
    if (file.open())
    {
        const QString path = file.fileName();

        QTextStream stream(&file);
        stream << data<<Qt::endl;
        QWebSettings *settings = QWebSettings::globalSettings();
        settings->setUserStyleSheetUrl(QUrl(path));
    }
}
