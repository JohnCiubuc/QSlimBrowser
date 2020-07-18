
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QTemporaryFile>
#include <QWebSettings>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void loadURL(QUrl URL);
    void setStyle(const QString data);
private:
    QWebEngineView *m_view;
};

#endif // MAINWINDOW_H
