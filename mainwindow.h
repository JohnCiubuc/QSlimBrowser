
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

#include "loginparser.h"
#include "userstyleparser.h"
#include "scriptparser.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void loadURL(QUrl URL);
    void insertStyleSheet(const QString &name, const QString &source, bool immediately);
private slots:
    void loadFinished(bool b);
    void loadScripts();
    void urlChanged(QUrl url);
private:
    QWebEngineView *m_view;
    LoginParser lParser;
    UserstyleParser cssParser;
    ScriptParser sParser;
};

#endif // MAINWINDOW_H
