
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QTemporaryFile>
#include <QWebEngineScript>
#include <QApplication>
#include <QWebEngineScriptCollection>
#include <QWebSettings>
#include <QTimer>
#include <QWebEngineProfile>
#include <QFileDialog>
#include "loginparser.h"
#include "userstyleparser.h"
#include "scriptparser.h"
#include "webengineurlinterceptor.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void loadURL(QUrl URL);
    void insertStyleSheet(const QString &name, const QString &source);
private slots:
    void loadFinished(bool b);
    void loadScripts();
    void urlChanged(QUrl url);
    void downloadRequested(QWebEngineDownloadItem*);
private:
    QWebEngineView *m_view;
    LoginParser lParser;
    UserstyleParser cssParser;
    ScriptParser sParser;
    WebEngineURLInterceptor * Interceptor;
};

#endif // MAINWINDOW_H
