#ifndef _FREEFUNC_H
#define _FREEFUNC_H

#include <cstring>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <zlib.h>
#include "b64.h"
#include "proxy.h"

using namespace std;

class DeleteObject{
public:
    template<typename T>
    void operator() (const T* ptr) const
    {
        delete ptr;
        ptr = NULL;
    }
};

class DeleteObjectArray{
public:
    template<typename T>
    void operator() (const T* ptr) const
    {
        delete []ptr;
        ptr = NULL;
    }
};

class FreeFun
{
    FreeFun();
    ~FreeFun();

public:
    static char* toupper(char *s);

    //added by zhaolin at 2009.01.06
    static void strToupper(string& inputStr);
    static string trim(string inputStr);
    static char* subString(char *str, const char* content, int start, int noofchars);

    static string replaceString(string content, string find, string rel);
    static string& replaceXMLNameSpace(string& str, const string& oldValue, const string& newValue);
    static void split(const string& src, const string& separator, vector<string>& dest);
    static void getFloatToInt(int type, float& obj);
    static string unZipRequestString(const string& inputStr);
    static string zipResultString(const string& inputStr);

    //added by liuhui at 2007.08.14
    template<typename T>
    static bool isUnique(list<T>* l)
    {
        l->sort();
        int size = l->size();
        l->unique();
        return (size == (int)l->size());
    }

    //added by liuhui at 2007.08.10
    template<typename T>
    static void clearList(list<T*>* l)
    {
        if(!l->empty())
        {
            for_each(l->begin(), l->end(), DeleteObject());
            l->clear();
        }
    }

    //added by liuhui at 2007.08.10
    template<typename T>
    static void clearVector(vector<T*>* v)
    {
        if(!v->empty())
        {
            for_each(v->begin(), v->end(), DeleteObject());
            v->clear();
        }
    }

    //added by liuyang at 2010.01.21
    template<typename T>
    static void clearVector(vector<pair<int,T*> >* v)
    {
        if(!v->empty())
        {
            for(int i = 0; i < v->size(); ++i)
            {
                if((*v)[i].second != NULL)
                    delete (*v)[i].second;
            }
            v->clear();
        }
    }

    //added by liuhui at 2009.03.02
    template<typename key, typename elem>
    static void clearMap(map<key, elem*>& m)
    {
        if(!m.empty())
        {
            typename map<key, elem*>::iterator iter;
            for(iter = m.begin(); iter != m.end(); iter++)
            {
                delete iter->second;
            }
            m.clear();
        }
    }

    //added by xphuang at 2009.11.02
    template<typename key, typename elem>
    static void clearMap(map<key, vector<elem*>*>& m)
    {
        if(!m.empty())
        {
            typename map<key, vector<elem*>*>::iterator iter;
            for(iter = m.begin(); iter != m.end(); iter++)
            {
                clearVector(iter->second);
                delete iter->second;
            }
            m.clear();
        }
    }

    //added by wugang at 20120731
    template<typename key, typename elem>
    static void clearMap(map<key, vector<elem>*>& m)
    {
        if(!m.empty())
        {
            typename map<key, vector<elem>*>::iterator iter;
            for(iter = m.begin(); iter != m.end(); iter++)
            {
                (iter->second)->clear();
                delete iter->second;
            }
            m.clear();
        }
    }   

    //added by zhaolin at 2008.11.26
    //用于两个list元素拷贝
    //前提:list中为对象指针; 元素存在拷贝构造函数; list已分配内存空间
    template<typename T>
    static void copyList(const list<T*>* src, list<T*>* dest)
    {
        clearList<T>(dest);

        if(!src->empty())
        {
            typename list<T*>::const_iterator first = src->begin();
            typename list<T*>::const_iterator last = src->end();
            T *iter;
            while(first != last)
            {
                iter = (T*)(*first);
                if(iter != NULL)
                    dest->push_back(new T(*iter));
                else
                    dest->push_back(NULL);
                first++;
            }
        }
    }

    static void copyList(const list<char*>* src, list<char*>* dest)
    {
        clearList<char>(dest);
        if(!src->empty())
        {
            list<char*>::const_iterator first = src->begin();
            list<char*>::const_iterator last = src->end();
            char* iter = NULL;
            char* iter1 = NULL;
            while(first != last)
            {
                iter = (char*)(*first);
                iter1 = new char[strlen(iter) + 1];
                memset(iter1, 0, strlen(iter1) + 1);
                strcpy(iter1, iter);
                dest->push_back(iter1);
                first++;
            }
        }
    }


    //added by zhaolin at 2008.11.26
    //用于两个list元素拷贝
    //前提:list中为对象; 元素存在拷贝构造函数; list已分配内存空间
    template<typename T>
    static void copyList(const list<T>* src, list<T>* dest)
    {
        dest->clear();
        if(!src->empty())
        {
            typename list<T>::const_iterator first = src->begin();
            typename list<T>::const_iterator last = src->end();
            T iter;
            while(first != last)
            {
                iter = (T)(*first);
                dest->push_back(iter);
                first++;
            }
        }

    }

    //added by zhaolin at 2008.11.26
    template<typename T>
    static void copyVector(const vector<T*>* src, vector<T*>* dest)
    {
        clearVector<T>(dest);
        if(!src->empty())
        {
            typename vector<T*>::const_iterator first = src->begin();
            typename vector<T*>::const_iterator last = src->end();
            T *iter;
            while(first != last)
            {
                iter = (T*)(*first);
                if(iter != NULL)
                    dest->push_back(new T(*iter));
                else
                    dest->push_back(NULL);
                first++;
            }
        }
    }

    //added by zhaolin at 2008.11.26
    template<typename T>
    static void copyVector(const vector<T>* src, vector<T>* dest)
    {
        dest->clear();
        if(!src->empty())
        {
            typename vector<T>::const_iterator first = src->begin();
            typename vector<T>::const_iterator last = src->end();
            T iter;
            while(first != last)
            {
                iter = (T)(*first);
                dest->push_back(iter);
                first++;
            }
        }
    }

    static bool wildcardCompare(const char* wildcard, const char* str);

    // added by zhangao at 20120723
    template<class T>
    static string toString(T t)
    {
        ostringstream stream;
        stream << t;
        return stream.str();
    }
    // end

    template<typename T>
    static bool compareVector(const vector<T*>& first, const vector<T*>& second)
    {
        if(first.size() != second.size())
        {
            return false;
        }

        vector<bool> vecIsCheck(first.size(), false);
        
        for(int i = 0; i < second.size(); i++)
        {
            bool isFind = false;
            const T* tmp = second[i];

            int j = 0;
            for(typename vector<T*>::const_iterator iter = first.begin();
                iter != first.end();
                iter++, j++)
            {
                if(vecIsCheck[j])
                {
                    continue;
                }
                if(*tmp == **iter)
                {
                    isFind = true;
                    vecIsCheck[j] = true;
                    break;
                }
            }

            if(!isFind)
            {
                return false;
            }
        }

        //vecIsCheck中应该全是true,才能说明完全匹配
        //有一个是false就说明不匹配
        for(int k = 0; k < vecIsCheck.size(); k++)
        {
            if(!vecIsCheck[k])
            {
                return false;
            }
        }

        return true;
    }
};

class PriorityGreater
{
public:
    template<typename T>
    bool operator()(const T* x, const T* y) const
    {
        return (x->getPriority() > y->getPriority());
    }
};

class BaseDiscountGreater
{
public:
    template<typename T>
    bool operator()(const T* x, const T* y) const
    {
        return (x->getBaseDiscount() > y->getBaseDiscount());
    }
};

class BaseDiscountLower
{
public:
    template<typename T>
    bool operator()(const T* x, const T* y) const
    {
        return (x->getBaseDiscount() < y->getBaseDiscount());
    }
};

template<typename T>
class FirstDiffDate : public binary_function<T*, T*, bool>
{
public:
    bool operator()(T* x, T* y) const
    {
        if(strcmp(y->getSaleEffDate(), x->getSaleEffDate()) != 0 ||
            strcmp(y->getTravelEffDate(), x->getTravelEffDate()) != 0)
            return true;
        else
            return false;
    }
};

template<typename T>
class FirstDiffPriority : public binary_function<T*, T*, bool>
{
public:
    bool operator()(T* x, T* y) const
    {
        if(y->getPriority() != x->getPriority())
            return true;
        else
            return false;
    }
};

template<class Iterator>
inline long distance(Iterator pos1, Iterator pos2)
{
    long d = 0;
    distance(pos1, pos2, d);
    return d;
}

#endif
