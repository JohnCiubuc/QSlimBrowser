#include "loginparser.h"

#define db qDebug() << this <<
LoginParser::LoginParser(QObject *parent) : QObject(parent)
{

}

void LoginParser::loadFiles()
{
    const QString dir =  QApplication::applicationDirPath().append("/Scripts/");
    QDir directory(dir);
    QStringList logindir = directory.entryList(QStringList() << "*.txt",QDir::Files);
    foreach(auto file, logindir)
    {
        QFile f(dir + file);
        bool bAbortFile = false;
        if(f.open(QFile::ReadOnly))
        {
            login_s s;
            QTextStream in(&f);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                element_s El;
                if (line == "Domain")
                {
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: DOMAIN IS EMPTY";
                        bAbortFile = true;
                        break;
                    }
                    s.Element.insert("Domain", in.readLine().simplified());
                }
                if (line == "TextFieldByID")
                {
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: TextField IS EMPTY OR MISSING";
                        bAbortFile = true;
                        break;
                    }
                    El.type = TextField;
                    El.elements << in.readLine().simplified();
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: TextField IS EMPTY OR MISSING";
                        bAbortFile = true;
                        break;
                    }
                    El.elements << in.readLine().simplified();
                }
                if (line == "TextFieldBySelector")
                {
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: TextField IS EMPTY OR MISSING";
                        bAbortFile = true;
                        break;
                    }
                    El.type = TextFieldSel;
                    El.elements << in.readLine().simplified();
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: TextField IS EMPTY OR MISSING";
                        bAbortFile = true;
                        break;
                    }
                    El.elements << in.readLine().simplified();
                }
                if (line == "ButtonByID")
                {
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: ButtonByID IS EMPTY";
                        bAbortFile = true;
                        break;
                    }
                    El.type = ButtonById;
                    El.elements << in.readLine().simplified();
                }
                if (line == "LocationOverride")
                {
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: LocationOverride IS EMPTY";
                        bAbortFile = true;
                        break;
                    }
                    El.type = LocationOverride;
                    El.elements << in.readLine().simplified();
                }
                if (line == "ButtonBySelector")
                {
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: ButtonBySelector IS EMPTY";
                        bAbortFile = true;
                        break;
                    }
                    El.type = ButtonBySelector;
                    El.elements << in.readLine().simplified();
                }
                if(!El.elements.isEmpty())
                    s.Elements << El;
            }
            f.close();
            if(!bAbortFile)
                Logins << s;
        }
    }
}

QString LoginParser::getLoginJavascript(QString url)
{
    for(auto s: Logins)
    {
        if(s.Element.value("Domain") == url)
        {
            QString js;
            qDebug() << this << s.TextField;
            qDebug() << this << s.TextFieldSel;
            qDebug() << this << s.ButtonById;
            qDebug() << this << s.ButtonBySelector;
            qDebug() << this << s.LocationOverride;
            for(int i = 0; i < s.TextField.size(); ++i)
            {
                auto element = s.TextField.at(i++);
                auto value = s.TextField.at(i);
                js += "document.getElementById(\"" + element + "\").value=\""+value+"\";\n";
                js += "document.getElementById(\"" + element + "\").dispatchEvent(new Event('change'));\n";
            }
            for(int i = 0; i < s.TextFieldSel.size(); ++i)
            {
                auto element = s.TextFieldSel.at(i++);
                auto value = s.TextFieldSel.at(i);
                js += "document.querySelectorAll('" + element + "')[0].value=\""+value+"\";\n";
                js += "document.querySelectorAll('" + element + "')[0].dispatchEvent(new Event('change'));\n";
            }

            for(int i = 0; i < s.ButtonById.size(); ++i)
            {
                auto element = s.ButtonById.at(i);
                js += "document.getElementById(\""+ element + "\").click();";
            }

            for(int i = 0; i < s.ButtonBySelector.size(); ++i)
            {
                auto element = s.ButtonBySelector.at(i);
                js += "document.querySelectorAll('"+ element + "')[0].click();";
            }
            for(int i = 0; i < s.LocationOverride.size(); ++i)
            {
                auto element = s.LocationOverride.at(i);
                js += "location.href=\""+ element + "\";";
            }
            return js;
        }
    }
    return QString();
}

void LoginParser::runLogins(QString url, QWebEnginePage *page)
{
    for(auto s: Logins)
    {
        if(s.Element.value("Domain") == url)
        {
            QString js;
            for(int x = 0; x < s.Elements.size(); ++x)
            {
                element_s elements = s.Elements.at(x);
                switch(elements.type)
                {
                case TextField:
                {
                    auto element = elements.elements.at(0);
                    auto value = elements.elements.at(1);
                    js = "document.getElementById(\"" + element + "\").value=\""+value+"\";\n";
                    js += "document.getElementById(\"" + element + "\").dispatchEvent(new Event('change'));\n";
                }
                break;
                case TextFieldSel:
                {
                    auto element = elements.elements.at(0);
                    auto value = elements.elements.at(1);
                    js = "document.querySelectorAll('" + element + "')[0].value=\""+value+"\";\n";
                    js += "document.querySelectorAll('" + element + "')[0].dispatchEvent(new Event('change'));\n";
                }
                break;
                case ButtonById:
                {
                    auto element = elements.elements.at(0);
                    js = "document.getElementById(\""+ element + "\").click();";
                }
                break;
                case ButtonBySelector:
                {
                    auto element = elements.elements.at(0);
                    js = "document.querySelectorAll('"+ element + "')[0].click();";
                }
                break;
                case LocationOverride:
                {
                    auto element = elements.elements.at(0);
                    js = "location.href=\""+ element + "\";";
                }
                break;
                default:
                    break;
                }
//                QThread::sleep(1);
                db js;
                page->runJavaScript(js);
            }
        }
    }
}
