#include <iostream>
#include <fstream>
#include <string>
#include <curl/curl.h>
#include <cstdio>
using namespace std;
class CHttpClient
{
public:
    CHttpClient(void);
    ~CHttpClient(void);
    
    /**
     *@brief HTTP POST请求
     *@param strUrl 输入参数，请求Url地址，如:http://www.baidu.com
     *@param strPost 输入参数，使用如下格式:para1=val1¶2=val2
     *@param strResponse 输出参数，返回内容
     *@return 返回是否Post成功
     */
    int Post(const std::string& strUrl,const std::string& strPost,std::string& strResponse);
    
    /**
     *@brief HTTP GET请求
     *@param strUrl 输入参数，请求的Url地址，如:https://www.alipay.com
     *@param strResponse 输出参数，返回的内容
     *@return 返回是否成功
     */
    int Get(const std::string& strUrl,std::string& strResponse);
    
    /**
     *@brief HTTPS POST请求，无证书版本
     *@param strUrl 输入参数，请求的Url地址，如：https://www.alipay.com
     *@param strPost 输入参数，使用格式如下：para1=val1¶2=val2
     *@param strResponse 输出参数，返回的内容
     *@param pCaPath 输入参数，为CA证书的路径，如果输入为NULL，则不验证服务器端证书的有效性
     *@return 返回是否Posts成功
     */
    int Posts(const std::string& strUrl,const std::string& strPost,std::string& strResponse,const char* pCaPath = NULL);
    
    /**
     *@brief HTTPS GET请求，无证书版
     *@param strUrl 输入参数，请求的Url地址，如https://www.alipay.com
     *@param strResponse 输出参数，返回的内容
     *@param pCaPath 输入参数，为CA证书的路径，如果输入为NULL，则不验证服务端证书的有效性
     *@return 返回是否Gets成功
     */
    int Gets(const std::string& strUrl,std::string& strResponse,const char* pCaPath = NULL);
    
public:
    void setDebug(bool bDebug);
private:
    bool m_Debug;
};

CHttpClient::CHttpClient(void)
:m_Debug(false)
{

}
CHttpClient::~CHttpClient(void)
{
    
}

static int OnDebug(CURL *,curl_infotype itype,char* pData,size_t size,void *)
{
    if(itype == CURLINFO_TEXT)
    {
        //printf("[TEXT]%s\n", pData);
    }
    else if(itype == CURLINFO_HEADER_IN)
    {
        printf("[HEADER_IN]%s\n", pData);
    }
    else if(itype == CURLINFO_HEADER_OUT)
    {
        printf("[HEADER_OUT]%s\n", pData);
    }
    else if(itype == CURLINFO_DATA_IN)
    {
        printf("[DATA_IN]%s\n", pData);
    }
    else if(itype == CURLINFO_DATA_OUT)
    {
        printf("[DATA_OUT]%s\n", pData);
    }
    return 0;
}
FILE *rfp = fopen("read.dat", "wb");
FILE *wfp = fopen("write.dat", "wb");
FILE *hfp = fopen("head.dat", "wb");

size_t OnBodyData(char* buffer,size_t size,size_t nmemb,void* lpVoid)
{
    printf("body data: %p %lu %lu %p\n", buffer, size, nmemb, lpVoid);
    if (buffer)
        return fwrite(buffer, size, nmemb, (FILE*)lpVoid);
    return 0;
}

size_t OnHeadData(char* buffer,size_t size,size_t nmemb,void* lpVoid)
{
    printf("header data: %p %lu %lu %p\n", buffer, size, nmemb, lpVoid);
    if (buffer)
        return fwrite(buffer, size, nmemb, (FILE*)lpVoid);
    return 0;
}

int CHttpClient::Post(const std::string &strUrl, const std::string &strPost, std::string &strResponse)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(m_Debug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE,1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION,OnDebug);
    }
    curl_easy_setopt(curl, CURLOPT_URL,strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, strPost.c_str());
    // curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);
    // curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, NULL);
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnWirteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 20);//连接时间
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}

string strRead;
int CHttpClient::Get(const std::string &strUrl, std::string &strResponse)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    printf("%d\n",NULL == curl?0:1);
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(m_Debug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE,1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION,OnDebug);
    }
    curl_easy_setopt(curl, CURLOPT_URL,strUrl.c_str());
    // curl_easy_setopt(curl, CURLOPT_HEADER, 1);
    printf("%p %p\n", rfp, wfp);

    // curl_easy_setopt(curl, CURLOPT_READFUNCTION,OnReadData);
    // curl_easy_setopt(curl, CURLOPT_READDATA, rfp);

    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, OnHeadData);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void*)hfp);

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, OnBodyData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)wfp);

    
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL,1);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT,20);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,20);
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed:%s\n",curl_easy_strerror(res));
    }
    curl_off_t len;
    curl_easy_getinfo(curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD_T, &len);
    printf("len:%lu\n", len);
    // curl_easy_perform(curl);
    return res;
}

int CHttpClient::Posts(const std::string &strUrl, const std::string &strPost, std::string &strResponse,const char* pCaPath)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(m_Debug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE,1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION,OnDebug);
    }
    
    curl_easy_setopt(curl, CURLOPT_URL,strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_POST,1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS,strPost.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION,NULL);
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,OnWirteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,(void*)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL,1);
    
    if(NULL == pCaPath)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
    }else{
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,true);
        curl_easy_setopt(curl, CURLOPT_CAINFO,pCaPath);
    }
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT,10);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,10);
    res = curl_easy_perform(curl);
    curl_easy_perform(curl);
    return res;
}

int CHttpClient::Gets(const std::string &strUrl, std::string &strResponse,const char* pCaPath)
{
    CURLcode res;
    CURL* curl = curl_easy_init();
    if(NULL == curl)
    {
        return CURLE_FAILED_INIT;
    }
    if(m_Debug)
    {
        curl_easy_setopt(curl, CURLOPT_VERBOSE,1);
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION,OnDebug);
    }
    curl_easy_setopt(curl, CURLOPT_URL,strUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_READFUNCTION,NULL);
    // curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,OnWirteData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,(void*)&strResponse);
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL,1);
    if(NULL == pCaPath)
    {
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST,false);
    }else{
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER,true);
        curl_easy_setopt(curl, CURLOPT_CAINFO,pCaPath);
    }
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT,3);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT,3);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return res;
}
void CHttpClient::setDebug(bool bDebug)
{
    m_Debug = bDebug;
}


int main()
{
    CHttpClient* httpClient = new CHttpClient();
    httpClient->setDebug(false);
    std::string result;
    int res = httpClient->Get("https://middle-oss.oss-cn-shenzhen.aliyuncs.com/ota/20200512/RrAvVq_Jetson_Nano_OTA-V0.0.3-20200512.zip", result);
    // _label1->setString(StringUtils::format("Get Statu = %d",res));
    printf("res:%d result = %s\n",res, result.c_str());
    
    //post
    // std::string result1;
    // res = httpClient->Post("http://blog.csdn.net/yuxikuo_1?", "viewmode=list", result1);
    // // _label2->setString(StringUtils::format("Post Statu = %d",res));
    // printf("*******************");
    // printf("res:%d result = %s\n",res, result1.c_str());
    
    return 0;
    //gets
    httpClient->setDebug(false);
    std::string result2;
    // res = httpClient->Gets("https://www.alipay.com", result2);
    res = httpClient->Get("https://middle-oss.oss-cn-shenzhen.aliyuncs.com/ota/20200512/RrAvVq_Jetson_Nano_OTA-V0.0.3-20200512.zip", result2);
    // _label3->setString(StringUtils::format("Get Statu = %d",res2));
    printf("res:%d result size = %lu\n",res, result2.size());
    std::ofstream ofs("ota.zip");
    ofs.write(result2.c_str(), result2.size());

    
    delete httpClient;
}
