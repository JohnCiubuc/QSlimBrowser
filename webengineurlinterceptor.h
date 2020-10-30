#ifndef WEBENGINEURLINTERCEPTOR_H
#define WEBENGINEURLINTERCEPTOR_H

#include <QObject>
#include <QDebug>
#include <QWebEngineUrlRequestInterceptor>
class WebEngineURLInterceptor: public QWebEngineUrlRequestInterceptor
{
    Q_OBJECT
public:
    WebEngineURLInterceptor();
protected:
    void interceptRequest(QWebEngineUrlRequestInfo &info);
};

#endif // WEBENGINEURLINTERCEPTOR_H
