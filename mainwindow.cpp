#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_view(new QWebEngineView(this))
{
    setCentralWidget(m_view);
    connect(m_view, &QWebEngineView::loadFinished, this, &MainWindow::loadFinished);
    connect(m_view, &QWebEngineView::urlChanged, this, &MainWindow::urlChanged);
    lParser.loadFiles();
    cssParser.loadFiles();
    sParser.loadFiles();
}

void MainWindow::loadURL(QUrl URL)
{
    m_view->page()->load(URL);
}

void MainWindow::insertStyleSheet(const QString &name, const QString &source, bool immediately)
{
    QWebEngineScript script;
    QString s = QString::fromLatin1("(function() {"\
                                    "    css = document.createElement('style');"\
                                    "    css.type = 'text/css';"\
                                    "    css.id = '%1';"\
                                    "    document.head.appendChild(css);"\
                                    "    css.innerText = '%2';"\
                                    "})()").arg(name).arg(source.simplified());


    if (immediately)
        m_view->page()->runJavaScript(s, QWebEngineScript::ApplicationWorld);

    script.setName(name);
    script.setSourceCode(s);
    script.setInjectionPoint(QWebEngineScript::DocumentReady);
    script.setRunsOnSubFrames(true);
    script.setWorldId(QWebEngineScript::ApplicationWorld);
    m_view->page()->scripts().insert(script);
}

void MainWindow::loadFinished(bool b)
{
    if(b == true)
    {
        QTimer::singleShot(1500, this, &MainWindow::loadScripts);
    }
}

void MainWindow::loadScripts()
{
    QString url = m_view->url().toString();
    QString js = lParser.getLoginJavascript(url);
    if(!js.isEmpty())
        m_view->page()->runJavaScript(js);

    QString scripts = sParser.getScriptJavascript(url);
    if(!scripts.isEmpty())
        m_view->page()->runJavaScript(scripts);
}

void MainWindow::urlChanged(QUrl url)
{
    QString css = cssParser.getUserCss(url.toString());
    if(!css.isEmpty())
        insertStyleSheet(url.toString(), css, true);

    QTimer::singleShot(1500, this, &MainWindow::loadScripts);
}
