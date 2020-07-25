#ifndef SCRIPTPARSER_H
#define SCRIPTPARSER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QTextStream>

class ScriptParser : public QObject
{
    Q_OBJECT
    struct script_s
    {
        QString Domain;
        QStringList ClickButtons;
    };

public:
    explicit ScriptParser(QObject *parent = nullptr);

    void loadFiles();

    QString getScriptJavascript(QString url);
signals:
private:
    QList<script_s> Scripts;
};

#endif // SCRIPTPARSER_H
