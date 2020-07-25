#ifndef LOGINPARSER_H
#define LOGINPARSER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QTextStream>


class LoginParser : public QObject
{
    Q_OBJECT

    struct login_s
    {
        QMap<QString,QString> Element;
        QStringList TextField;
        QStringList TextFieldSel;
        QStringList ButtonById;
        QStringList ButtonBySelector;
    };

public:
    explicit LoginParser(QObject *parent = nullptr);

    void loadFiles();

    QString getLoginJavascript(QString url);


signals:

private:

    QList<login_s> Logins;

};

#endif // LOGINPARSER_H
