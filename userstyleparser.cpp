#include "userstyleparser.h"

UserstyleParser::UserstyleParser(QObject *parent) : QObject(parent)
{

}

void UserstyleParser::loadFiles()
{
    const QString dir =  QApplication::applicationDirPath().append("/Userstyles/");
    QDir directory(dir);
    QStringList cssdir = directory.entryList(QStringList() << "*.user.css",QDir::Files);
    foreach(auto file, cssdir)
    {
        QFile f(dir + file);
        bool bAbortFile = true;
        bool bFirstBracket = false;
        if(f.open(QFile::ReadOnly))
        {
            usercss_s s;
            QTextStream in(&f);
            while (!in.atEnd())
            {
                QString line = in.readLine();
                if(!bAbortFile)
                {
                    if(!bFirstBracket)
                    {
                        if(line.contains("{"))
                        {
                            bFirstBracket = true;
                            line.replace(line.indexOf('{'), 1, ' ');
                        }
                    }
                    s.css += line;
                }
                else
                {
                    QRegularExpression reg("@-moz-document domain\\(\"(.+)\"\\)");
                    QRegularExpressionMatch match = reg.match(line);

                    if (match.hasMatch())
                    {
                        bAbortFile = false;
                        s.domain = match.captured(1);
                        // bracket included
                        if(line.contains("{"))
                        {
                            bFirstBracket = true;
                            s.css += "";
                        }
                        // next line has bracket?
                        else
                        {

                        }
                    }
                    else
                    {
                        reg.setPattern("@-moz-document url-prefix\\(\"(.+)\"\\)");
                        match = reg.match(line);
                        if (match.hasMatch())
                        {
                            bAbortFile = false;
                            s.domain = match.captured(1);
                            // bracket included
                            if(line.contains("{"))
                            {
                                bFirstBracket = true;
                                s.css += "";
                            }
                            // next line has bracket?
                            else
                            {

                            }
                        }
                    }
                }
            }
            if(!bAbortFile)
            {
                s.css.replace(s.css.lastIndexOf('}'), 1, ' ');
                UserCss << s;
            }
        }
    }
}

QString UserstyleParser::getUserCss(QString url)
{
    for(auto s : UserCss)
    {
        qDebug() << url << " +++++ " << s.domain;
        if(url.contains(s.domain))
            return s.css;
    }
    return QString();
}
