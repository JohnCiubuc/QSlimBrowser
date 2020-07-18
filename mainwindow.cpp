#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_view(new QWebEngineView(this))
{
    setCentralWidget(m_view);
}

void MainWindow::loadURL(QUrl URL)
{
    m_view->page()->load(URL);
}
