#ifndef _RAPID_XML_TOOL_H__
#define _RAPID_XML_TOOL_H__

#include <string>
#include <string.h>
#include <stdio.h>
#include <stdexcept>
#include <rapidxml.hpp>

#define MAX_TAGNAME 200 // 最大标签字符长度
#define INT_INIT_VALUE -99999 // 整型成员初始值
#define FLOAT_INIT_VALUE -99999 // 浮点型成员初始值

#ifdef DEBUG
    #define EXCEPTION_FORMAT(msg)  string() + msg + string(" @") + __FILE__ + "::" + __FUNCTION__
#else
    #define EXCEPTION_FORMAT(msg)  string() + msg
#endif

// 断言该节点存在  
#define ASSERT_NODE(node, tag) \
        if (node == NULL) \
        {\
            throw runtime_error(EXCEPTION_FORMAT("无<" + tag + ">, 请检查XML文本!"));\
        }

// 断言该节点存在而且唯一  
#define ASSERT_NODE_ONE(node, parentNode, tag) \
        if (node == NULL) \
        {\
            throw runtime_error(EXCEPTION_FORMAT("无<" + tag + ">, 请检查XML文本!"));\
        }\
        else if (node != parentNode->last_node(string(tag).c_str(), string(tag).size()))\
        {\
            throw runtime_error(EXCEPTION_FORMAT(tag + " tag more than one found!"));\
        }

// 断言该属性节点存在而且唯一  
#define ASSERT_ATTR_ONE(attrNode, eleNode, attrName) \
        if (attrNode == NULL) \
        {\
            throw runtime_error(EXCEPTION_FORMAT("no " + attrName + " attribute found!"));\
        }\
        else if (attrNode != eleNode->last_attribute(attrName))\
        {\
            throw runtime_error(EXCEPTION_FORMAT(attrName + " attribute more than one found!"));\
        }

// 断言节点数量限制是否达到
#define ASSERT_NODE_NUMBER(currentNumber, restrictNumber, tag) \
        if (currentNumber == restrictNumber)\
        {\
            throw runtime_error(EXCEPTION_FORMAT(tag + " tag has reach " + RapidXmlTool::itoa(restrictNumber) +  " number restriction !"));\
        }

// 断言choice flag为假
#define ASSERT_CHOICE_FLAG_FALSE(choiceFlag, tag) \
        if (choiceFlag == true) \
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag  + "> 之前一个sibling节点已存在, choice时只能有一个节点存在!"));\
        }


// 断言choice flag为真
#define ASSERT_CHOICE_FLAG_TRUE(choiceFlag, tag) \
        if (choiceFlag == false) \
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag  + "> 无choice子节点可格式化!"));\
        }

// 断言对象个数是否在最大最小限制里
#define ASSERT_MEMBER_MIN_MAX(objNumber, min, max, tag) \
        if ((objNumber < min) || (objNumber > max))\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> 节点个数限制不满足: " + RapidXmlTool::itoa(objNumber) + " 不在 [" + RapidXmlTool::itoa(min) + "-" + RapidXmlTool::itoa( max) + "] !"));\
        }

// 断言对象个数为1
#define ASSERT_VECTOR_ONE_INIT(objNumber, tag) \
        if (objNumber != 1)\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> 节点个数限制不满足: " + RapidXmlTool::itoa(objNumber) + " 不在 [*-1] !"));\
        }

// 断言指针成员不为空
#define ASSERT_POINTER_NOT_NULL(objPtr, tag) \
        if (objPtr == NULL)\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> 对象指针不能为空 "));\
        }


// 断言整型成员已赋值
#define ASSERT_INT_INIT(member, tag) \
        if (member == -99999)\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> 节点未赋值!"));\
        }

// 断言浮点型成员已赋值
#define ASSERT_FLOAT_INIT(member, tag) \
        if (member == -99999)\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> 节点未赋值!"));\
        }

// 断言字符串型成员已赋值
#define ASSERT_STRING_INIT(member, tag) \
        if (member == "")\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> 节点未赋值!"));\
        }

                               
namespace RapidXmlTool
{
    inline std::string itoa(int i)
    {
       char str[1000];
       sprintf(str, "%d", i);
       return std::string(str);
    }

    inline std::string ftoa(float f)
    {
       char str[1000];
       sprintf(str, "%.2f", f);
       return std::string(str);
    }

    inline std::string booltoa(bool b)
    {
        if(b) return std::string("true");
        else return std::string("false");
    }

    inline void checkChoice(const rapidxml::xml_node<>* checkedNode, char tagList[][MAX_TAGNAME], int tagNumber) throw(std::exception)
    {
        rapidxml::xml_node<>* node = checkedNode->first_node();

        //if (node == NULL) return;        
        if (node == NULL) throw std::runtime_error( std::string(checkedNode->name()) + " has no children!" );

        int index = -1;
        while (node)
        {
            if (node->type() != rapidxml::node_element) throw std::runtime_error( std::string("non-element node found in <") + checkedNode->name() + "> tag!" );
        
            int i = 0;
            size_t pos;
            char* targetTag;
            for (; i < tagNumber; ++i)
            {
                // 忽略名字空间前缀匹配 
                pos = std::string(node->name()).find(":");
                if (pos == std::string::npos)
                {
                    targetTag = node->name();
                }
                else
                {
                    targetTag = node->name() + pos + 1;
                }
                
                if (strcmp(targetTag, tagList[i]) == 0)
                {
                    if ((index == -1) || (index == i))
                    {
                        index = i;
                        node = node->next_sibling();
                        break;
                    }
                    else
                    {
                        throw std::runtime_error(std::string("<") + node->name() + "> 之前一个sibling choice节点已存在!");
                    }
                }
            }
            
            if (i == tagNumber)
            {
                throw std::runtime_error(std::string("<") + node->name() + "> 错序或未在该节点处定义!");
            }
        }
    }    

    inline void checkSequence(const rapidxml::xml_node<>* checkedNode, char tagList[][MAX_TAGNAME], int tagNumber) throw(std::exception)
    {
        rapidxml::xml_node<>* node = checkedNode->first_node();

        if (node == NULL) return;
        //if (node == NULL) throw std::runtime_error( std::string(checkedNode->name()) + " has no children!" );

        int index = -1;  // 当前匹配上的节点索引号
        int i; // taglist匹配的首元素编号
        while (node)
        {
            if (node->type() != rapidxml::node_element) throw std::runtime_error( std::string("non-element node found in <") + checkedNode->name() + "> tag!" );

            int i = 0;
            if (index != -1) i = index;
            size_t pos;
            char* targetTag;
            for (; i < tagNumber; ++i)
            {
                // 忽略名字空间前缀匹配 
                pos = std::string(node->name()).find(":");
                if (pos == std::string::npos)
                {
                    targetTag = node->name();
                }
                else
                {
                    targetTag = node->name() + pos + 1;
                }

                if (strcmp(targetTag, tagList[i]) == 0)
                {
                    index = i;
                    node = node->next_sibling();
                    break;
                }
            }

            if (i == tagNumber)
            {
                throw std::runtime_error(std::string("<") + node->name() + "> is out of sequence!");
            }
        }
    }


}

#endif

