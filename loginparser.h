#ifndef LOGINPARSER_H
#define LOGINPARSER_H

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QTextStream>
#include <QWebEnginePage>
#include <QThread>


class LoginParser : public QObject
{
    Q_OBJECT


    enum element_type_enum
    {
        TextField,
        TextFieldSel,
        ButtonById,
        ButtonBySelector,
        LocationOverride
    };

    struct element_s
    {
        element_type_enum type;
        QStringList elements;
    };

    struct login_s
    {
        QMap<QString,QString> Element;
        QList<element_s> Elements;
        QStringList TextField;
        QStringList TextFieldSel;
        QStringList ButtonById;
        QStringList ButtonBySelector;
        QStringList LocationOverride;
    };

public:
    explicit LoginParser(QObject *parent = nullptr);

    void loadFiles();

    QString getLoginJavascript(QString url);
    void runLogins(QString url, QWebEnginePage * page);


signals:

private:

    QList<login_s> Logins;

};

#endif // LOGINPARSER_H
