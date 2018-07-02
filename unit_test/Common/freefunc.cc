#include "freefunc.h"

FreeFun::FreeFun()
{
}

FreeFun::~FreeFun()
{
}

char* FreeFun::toupper(char *s)
{
    register char *p = s;

    while(*p)
    {
        //跳过中文
        if(*p < 0)
        {
            p += 2;
            continue;
        } 
        else if(islower(*p))
        {
            *p = ::toupper(*p);
        }
        p++;
    }
    return s;
}

//added by zhaolin at 2009.01.06
void FreeFun::strToupper(string& inputStr)
{
    int i = 0;
    while(i < inputStr.length())
    {
        if(inputStr[i] < 0)
        {
            i +=2;
            continue;
            
        }
        else if(islower(inputStr[i]))
            inputStr[i] = ::toupper(inputStr[i]);
        i++;
    }
}

char* FreeFun::subString(char *str, const char* content, int start, int noofchars)
{
    str[0] = 0;
    if(start > strlen(content) ||
       start + noofchars > strlen(content))
        return str;
    else
    {
        int i;
        for(i = 0; i < start ; i++)
            ;
        int j;
        for(j = 0; j < noofchars; j++)
        {
            str[j] = content[i];
            i++;
        }
        str[j] = '\0';
    }
    return str;
}

string FreeFun::trim(string inputStr)
{
    inputStr.erase(0, inputStr.find_first_not_of(' '));
    inputStr.erase(inputStr.find_last_not_of(' ')+1);

    return inputStr;
}


//added by xphuang at 2008.7.25
//通配符匹配函数, 支持'*', 'abc*', '*abc', '*abc*', 'abc'
bool FreeFun::wildcardCompare(const char* wildcard, const char* str)
{
    if(strcmp(wildcard, "*") == 0 || strcmp(wildcard, str) == 0)
        return true;

    if(strlen(wildcard) == 0 || strlen(str) == 0)
        return false;

    //通配符位置
    bool starBegin = false;
    bool starEnd = false;
    if(wildcard[0] == '*')
        starBegin = true;
    if(wildcard[strlen(wildcard) - 1] == '*')
        starEnd = true;

    //拷贝非通配符字符至tmp
    char tmp[1024];
    memset(tmp, 0, sizeof(tmp));
    const char* pbegin = wildcard;
    int len = strlen(wildcard);
    if(starBegin)
    {
        pbegin++;
        len--;
    }
    if(starEnd)
        len--;

    if(len >= sizeof(tmp))
        return false;
    strncpy(tmp, pbegin, len);
    tmp[len] = 0;

    //通配符判断
    if(strlen(tmp) == 0)
        return false;

    const char * p = str;
    while(p = strstr(p, tmp))
    {
        if(starBegin && starEnd)
            return true;
        else if(!starBegin && starEnd)
        {
            if(p == str)
                return true;
        }
        else if(starBegin && !starEnd)
        {
            if(*(p + strlen(tmp)) == 0)
                return true;
        }
        else
            break;

        p++;
        if(*p == 0)
            break;
    }

    return false;
}

string FreeFun::replaceString(string content, string find, string rel)
{
    string::size_type posFound = 0;
    while(posFound < content.length())
    {
        posFound = content.find(find.c_str(), posFound, find.length());
        if(posFound < content.length())
        {
            content = content.replace(posFound, find.length(), rel.c_str());
            posFound = posFound + rel.length();
        }
        else
        {
            break;
        }
    }
    return content;
}

string& FreeFun::replaceXMLNameSpace(string& str, const string& oldValue, const string& newValue)
{
    string::size_type pos(0);
    string::size_type end(0);
    while(true)
    {
        if((pos=str.find(oldValue, pos)) != string::npos)
        {
            if((end = str.find(":", pos)) != string::npos)
            {
                string temp = str.substr(pos + oldValue.size(), end - pos - oldValue.size());
                if(temp.find(" ") == string::npos)
                {
                    str.replace(pos, end - pos+1, newValue);
                    pos = end- temp.size() + 1;
                }
                else
                {
                    pos = end;
                }
            }
        }
        else
        {
            break;
        }
    }
    return str;
}


void FreeFun::split(const string& src, const string& separator, vector<string>& dest)
{
    string str = src;
    string substring;
    string::size_type start = 0, index;

    do
    {
        index = str.find_first_of(separator,start);
        if(index == start)
        {
            start = index + 1;
            continue;
        }
        if (index != string::npos)
        {    
            substring = str.substr(start,index-start);
            dest.push_back(substring);
            start = str.find_first_not_of(separator,index);
            if (start == string::npos)
            {
                return;
            }
        }
    }while(index != string::npos);
    
    //the last token
    substring = str.substr(start);
    dest.push_back(substring);
}

// float类型取整
// type = 0,向上取整到十位
// type = 1,四舍五入到十位
// type = 2,四舍五入到个位
void FreeFun::getFloatToInt(int type, float& amount)
{
    if(type == 0)
    {
        amount = (int)((amount + 9.999) / 10) * 10;
    }
    else if(type == 1)
    {
        amount = (int)((amount + 5.0001) / 10) * 10;
    }
    else if(type == 2)
    {
        amount = (int)(amount + 0.5001);
    }
}

string FreeFun::unZipRequestString(const string& inputStr)
{
    int pos = -1;
    pos = inputStr.find_last_of("/");
    if(string::npos != pos)
    {
        string requestType = inputStr.substr(pos + 1);
        if(requestType == "Z")
        {
            string zipString = inputStr.substr(0, pos);
            zipString = base64Decode(zipString);

            //unzip
            static char buf[20 * 1024 * 1024];
            memset(buf, 0, sizeof(buf));
            unsigned long bufLen = sizeof(buf) - 4;
            int iRet = uncompress((Bytef *)buf, &bufLen, (Bytef *)(zipString.c_str()), zipString.size());
            if(Z_OK == iRet)
            {
                return string(buf);
            }
            else
            {
                return string();
            }
        }
        else
            return inputStr;
    }
    else
    {
        return inputStr;
    }
}

string FreeFun::zipResultString(const string& inputStr)
{
    //大于10K就压缩
    //if(inputStr.size() <= 10 * 1024)
    //    return inputStr;

    long length = inputStr.size() + 1024;
    unsigned long destLen = length;

    char* srcbuf = new char[length];
    char* desbuf = new char[length];
    memset(srcbuf, 0, length);
    memset(desbuf, 0, length);

    strcpy(srcbuf, inputStr.c_str());

    int iRet = compress((Bytef *)desbuf, &destLen, (Bytef *)srcbuf, strlen(srcbuf));
    if (Z_OK != iRet)
    {
        delete []srcbuf;
        delete []desbuf;
        return string();
    }    
    
    //转ascii码
    string zippedStr = string(desbuf, destLen);
    string ret = base64Encode(zippedStr) + "/Z";
    delete []srcbuf;
    delete []desbuf;
    return ret;
}

