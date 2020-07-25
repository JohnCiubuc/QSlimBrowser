#ifndef USERSTYLEPARSER_H
#define USERSTYLEPARSER_H

#include <QObject>
#include <QDir>
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>
class UserstyleParser : public QObject
{
    Q_OBJECT
    struct usercss_s
    {
        QString domain;
        QString css;
    };

public:
    explicit UserstyleParser(QObject *parent = nullptr);

    void loadFiles();
    QString getUserCss(QString url);
signals:
private:
    QList<usercss_s> UserCss;
};

#endif // USERSTYLEPARSER_H
