#include "scriptparser.h"

ScriptParser::ScriptParser(QObject *parent) : QObject(parent)
{

}

void ScriptParser::loadFiles()
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
            script_s s;
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
                    s.Domain = in.readLine().simplified();
                }
                if (line == "ClickButton")
                {
                    if(in.atEnd())
                    {
                        qWarning() << "ERROR: USER IS EMPTY OR MISSING";
                        bAbortFile = true;
                        break;
                    }
                    s.ClickButtons << in.readLine().simplified();
                }

            }
            f.close();
            if(!bAbortFile)
                Scripts << s;
        }
    }
}

QString ScriptParser::getScriptJavascript(QString url)
{
    for(auto s: Scripts)
    {
        if(s.Domain == url)
        {
            QString js;
            for(auto element : s.ClickButtons)
                js +="document.getElementById(\""+ element + "\").click();";
            return js;
        }
    }
    return QString();
}
