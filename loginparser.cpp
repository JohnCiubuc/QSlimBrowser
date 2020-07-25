#include "loginparser.h"

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
                    s.TextField << in.readLine().simplified();
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: TextField IS EMPTY OR MISSING";
                        bAbortFile = true;
                        break;
                    }
                    s.TextField << in.readLine().simplified();
                }
                if (line == "TextFieldBySelector")
                {
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: TextField IS EMPTY OR MISSING";
                        bAbortFile = true;
                        break;
                    }
                    s.TextFieldSel << in.readLine().simplified();
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: TextField IS EMPTY OR MISSING";
                        bAbortFile = true;
                        break;
                    }
                    s.TextFieldSel << in.readLine().simplified();
                }
                if (line == "ButtonByID")
                {
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: ButtonByID IS EMPTY";
                        bAbortFile = true;
                        break;
                    }
                    s.ButtonById << in.readLine().simplified();
                }
                if (line == "ButtonBySelector")
                {
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: ButtonBySelector IS EMPTY";
                        bAbortFile = true;
                        break;
                    }
                    s.ButtonBySelector << in.readLine().simplified();
                }
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
            return js;
        }
    }
    return QString();
}
