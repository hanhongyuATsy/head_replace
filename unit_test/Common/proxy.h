#ifndef _PROXY_H
#define _PROXY_H

#include <list>
#include <vector>
#include <map>

using namespace std;

template<typename T>
class Proxy
{
public:
    Proxy(T* obj = NULL) : _obj(obj)
    {
    }
    /*
    Proxy(const Proxy& proxy)
    {
        _obj = proxy._obj;
    }

    Proxy& operator = (const Proxy& proxy)
    {
        if(this == &proxy)
            return *this;

        _obj = new T(proxy._obj);
    }*/

    ~Proxy()
    {
        deleteObj(_obj);
    }

private:
    template<typename T1>
    void deleteObj(T1 obj)
    {
        return;
    }

    template<typename T2>
    void deleteObj(T2* obj)
    {
        if(obj != NULL)
        {
            delete obj;
            obj = NULL;
        }
    }

    template<typename T3>
    void deleteObj(list<T3*>* listT3)
    {
        if(listT3 == NULL)
            return;

        typename list<T3*>::iterator iter;
        for(iter = listT3->begin(); iter != listT3->end(); iter++)
        {
            deleteObj(*iter);
        }

        listT3->clear();
        delete listT3;
        listT3 = NULL;
    }

    template<typename T4>
    void deleteObj(vector<T4*>* vectorT4)
    {
        if(vectorT4 == NULL)
            return;

        typename vector<T4*>::iterator iter;
        for(iter = vectorT4->begin(); iter != vectorT4->end(); iter++)
        {
            deleteObj(*iter);
        }

        vectorT4->clear();
        delete vectorT4;
        vectorT4 = NULL;
    }

    template<typename T5, typename T6>
    void deleteObj(map<T5*, T6*>* mapT5)
    {
        if(mapT5 == NULL)
            return;

        typename map<T5*, T6*>::iterator iter;
        for(iter = mapT5->begin(); iter != mapT5->end(); iter++)
        {
            deleteObj(*iter);
        }

        mapT5->clear();
        delete mapT5;
        mapT5 = NULL;
    }

private:
    T* _obj;
};

#endif

