#ifndef _RAPID_XML_TOOL_H__
#define _RAPID_XML_TOOL_H__

#include <string>
#include <string.h>
#include <stdio.h>
#include <stdexcept>
#include <rapidxml.hpp>

#define MAX_TAGNAME 200 // ����ǩ�ַ�����
#define INT_INIT_VALUE -99999 // ���ͳ�Ա��ʼֵ
#define FLOAT_INIT_VALUE -99999 // �����ͳ�Ա��ʼֵ

#ifdef DEBUG
    #define EXCEPTION_FORMAT(msg)  string() + msg + string(" @") + __FILE__ + "::" + __FUNCTION__
#else
    #define EXCEPTION_FORMAT(msg)  string() + msg
#endif

// ���Ըýڵ����  
#define ASSERT_NODE(node, tag) \
        if (node == NULL) \
        {\
            throw runtime_error(EXCEPTION_FORMAT("��<" + tag + ">, ����XML�ı�!"));\
        }

// ���Ըýڵ���ڶ���Ψһ  
#define ASSERT_NODE_ONE(node, parentNode, tag) \
        if (node == NULL) \
        {\
            throw runtime_error(EXCEPTION_FORMAT("��<" + tag + ">, ����XML�ı�!"));\
        }\
        else if (node != parentNode->last_node(string(tag).c_str(), string(tag).size()))\
        {\
            throw runtime_error(EXCEPTION_FORMAT(tag + " tag more than one found!"));\
        }

// ���Ը����Խڵ���ڶ���Ψһ  
#define ASSERT_ATTR_ONE(attrNode, eleNode, attrName) \
        if (attrNode == NULL) \
        {\
            throw runtime_error(EXCEPTION_FORMAT("no " + attrName + " attribute found!"));\
        }\
        else if (attrNode != eleNode->last_attribute(attrName))\
        {\
            throw runtime_error(EXCEPTION_FORMAT(attrName + " attribute more than one found!"));\
        }

// ���Խڵ����������Ƿ�ﵽ
#define ASSERT_NODE_NUMBER(currentNumber, restrictNumber, tag) \
        if (currentNumber == restrictNumber)\
        {\
            throw runtime_error(EXCEPTION_FORMAT(tag + " tag has reach " + RapidXmlTool::itoa(restrictNumber) +  " number restriction !"));\
        }

// ����choice flagΪ��
#define ASSERT_CHOICE_FLAG_FALSE(choiceFlag, tag) \
        if (choiceFlag == true) \
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag  + "> ֮ǰһ��sibling�ڵ��Ѵ���, choiceʱֻ����һ���ڵ����!"));\
        }


// ����choice flagΪ��
#define ASSERT_CHOICE_FLAG_TRUE(choiceFlag, tag) \
        if (choiceFlag == false) \
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag  + "> ��choice�ӽڵ�ɸ�ʽ��!"));\
        }

// ���Զ�������Ƿ��������С������
#define ASSERT_MEMBER_MIN_MAX(objNumber, min, max, tag) \
        if ((objNumber < min) || (objNumber > max))\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> �ڵ�������Ʋ�����: " + RapidXmlTool::itoa(objNumber) + " ���� [" + RapidXmlTool::itoa(min) + "-" + RapidXmlTool::itoa( max) + "] !"));\
        }

// ���Զ������Ϊ1
#define ASSERT_VECTOR_ONE_INIT(objNumber, tag) \
        if (objNumber != 1)\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> �ڵ�������Ʋ�����: " + RapidXmlTool::itoa(objNumber) + " ���� [*-1] !"));\
        }

// ����ָ���Ա��Ϊ��
#define ASSERT_POINTER_NOT_NULL(objPtr, tag) \
        if (objPtr == NULL)\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> ����ָ�벻��Ϊ�� "));\
        }


// �������ͳ�Ա�Ѹ�ֵ
#define ASSERT_INT_INIT(member, tag) \
        if (member == -99999)\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> �ڵ�δ��ֵ!"));\
        }

// ���Ը����ͳ�Ա�Ѹ�ֵ
#define ASSERT_FLOAT_INIT(member, tag) \
        if (member == -99999)\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> �ڵ�δ��ֵ!"));\
        }

// �����ַ����ͳ�Ա�Ѹ�ֵ
#define ASSERT_STRING_INIT(member, tag) \
        if (member == "")\
        {\
            throw runtime_error(EXCEPTION_FORMAT("<" + tag + "> �ڵ�δ��ֵ!"));\
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
                // �������ֿռ�ǰ׺ƥ�� 
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
                        throw std::runtime_error(std::string("<") + node->name() + "> ֮ǰһ��sibling choice�ڵ��Ѵ���!");
                    }
                }
            }
            
            if (i == tagNumber)
            {
                throw std::runtime_error(std::string("<") + node->name() + "> �����δ�ڸýڵ㴦����!");
            }
        }
    }    

    inline void checkSequence(const rapidxml::xml_node<>* checkedNode, char tagList[][MAX_TAGNAME], int tagNumber) throw(std::exception)
    {
        rapidxml::xml_node<>* node = checkedNode->first_node();

        if (node == NULL) return;
        //if (node == NULL) throw std::runtime_error( std::string(checkedNode->name()) + " has no children!" );

        int index = -1;  // ��ǰƥ���ϵĽڵ�������
        int i; // taglistƥ�����Ԫ�ر��
        while (node)
        {
            if (node->type() != rapidxml::node_element) throw std::runtime_error( std::string("non-element node found in <") + checkedNode->name() + "> tag!" );

            int i = 0;
            if (index != -1) i = index;
            size_t pos;
            char* targetTag;
            for (; i < tagNumber; ++i)
            {
                // �������ֿռ�ǰ׺ƥ�� 
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

