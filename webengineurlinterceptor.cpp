#include "webengineurlinterceptor.h"

WebEngineURLInterceptor::WebEngineURLInterceptor()
{

}

void WebEngineURLInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    if(info.requestUrl().toString().contains("MP4Video"))
        qDebug() << info.requestUrl();
//    info.

//    if(info.requestUrl().toString().contains("googleads"))
//        info.block(true);
}
