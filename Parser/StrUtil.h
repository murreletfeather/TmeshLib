/*!
 *      \file StrUtil.h
 *      \brief 字符串工具库
 *      \date 创建日期: 2010/08/10
 *      \author 原作者未知
 *      \details
 *          提供常见字符串操作功能，包括：
 *              - 修剪空白字符: trimLeft / trimRight / trim
 *              - 大小写转换: toLower / toUpper
 *              - 前缀后缀判断: startsWith / endsWith
 *              - 大小写不敏感比较: equalsIgnoreCase
 *              - 字符串类型转换: toString / parseString / toHexString / parseHexString
 *              - 字符串分词: Tokenizer / split
 */

#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

//! 字符串工具命名空间
namespace strutil {

using std::string;
using std::vector;
using std::istringstream;
using std::ostringstream;
using std::transform;

/**
 * @brief   修剪字符串左侧的空白字符
 * @param   str 输入字符串
 * @return  修剪后的新字符串
 * @details 移除字符串开头的空格、制表符、换行符和回车符
 */
inline string trimLeft(const string& str)
{
    string t = str;
    t.erase(0, t.find_first_not_of(" \t\n\r"));
    return t;
}

/**
 * @brief   修剪字符串右侧的空白字符
 * @param   str 输入字符串
 * @return  修剪后的新字符串
 * @details 移除字符串末尾的空格、制表符、换行符和回车符
 */
inline string trimRight(const string& str)
{
    string t = str;
    t.erase(t.find_last_not_of(" \t\n\r") + 1);
    return t;
}

/**
 * @brief   修剪字符串两端的空白字符
 * @param   str 输入字符串
 * @return  修剪后的新字符串
 * @details 同时移除字符串开头和末尾的空白字符，先修剪左侧再修剪右侧
 */
inline string trim(const string& str)
{
    string t = str;
    t.erase(0, t.find_first_not_of(" \t\n\r"));
    t.erase(t.find_last_not_of(" \t\n\r") + 1);
    return t;
}

/**
 * @brief   按照指定字符集合修剪字符串两端
 * @param   str 输入字符串
 * @param   delimitor 要修剪的字符集合
 * @return  修剪后的新字符串
 * @details 移除字符串两端所有属于指定集合的字符
 */
inline string trim(const string& str, const string & delimitor)
{
    string t = str;
    t.erase(0, t.find_first_not_of(delimitor));
    t.erase(t.find_last_not_of(delimitor) + 1);
    return t;
}

/**
 * @brief   将字符串转换为全小写
 * @param   str 输入字符串
 * @return  转换为全小写的新字符串
 */
inline string toLower(const string& str)
{
    string t = str;
    transform(t.begin(), t.end(), t.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return t;
}

/**
 * @brief   将字符串转换为全大写
 * @param   str 输入字符串
 * @return  转换为全大写的新字符串
 */
inline string toUpper(const string& str)
{
    string t = str;
    transform(t.begin(), t.end(), t.begin(),
        [](unsigned char c) { return std::toupper(c); });
    return t;
}

/**
 * @brief   判断字符串是否以指定子串开头
 * @param   str 原字符串
 * @param   substr 开头子串
 * @return  如果str以substr开头返回true，否则返回false
 * @details 先检查长度，如果子串长度大于原字符串直接返回false
 *          使用std::string::compare比较前缀，比find更高效
 */
inline bool startsWith(const string& str, const string& substr)
{
    if (str.length() < substr.length()) {
        return false;
    }
    return str.compare(0, substr.length(), substr) == 0;
}

/**
 * @brief   判断字符串是否以指定子串结尾
 * @param   str 原字符串
 * @param   substr 结尾子串
 * @return  如果str以substr结尾返回true，否则返回false
 * @details 先检查长度，如果子串长度大于原字符串直接返回false
 *          使用std::string::compare比较后缀，比rfind更高效
 */
inline bool endsWith(const string& str, const string& substr)
{
    if (str.length() < substr.length()) {
        return false;
    }
    size_t pos = str.length() - substr.length();
    return str.compare(pos, substr.length(), substr) == 0;
}

/**
 * @brief   比较两个字符串是否相等（忽略大小写）
 * @param   str1 第一个字符串
 * @param   str2 第二个字符串
 * @return  忽略大小写后相等返回true，否则返回false
 */
inline bool equalsIgnoreCase(const string& str1, const string& str2)
{
    return toLower(str1) == toLower(str2);
}

/**
 * @brief   将布尔值转换为字符串
 * @param   value 布尔值
 * @return  "true"或"false"字符串
 */
inline string toString(const bool& value)
{
    ostringstream oss;
    oss << std::boolalpha << value;
    return oss.str();
}

/**
 * @brief   将字符串解析为指定类型的值
 * @tparam  T 目标类型
 * @param   str 输入字符串
 * @return  解析得到的值
 */
template<class T>
T parseString(const string& str) {
    T value;
    istringstream iss(str);
    iss >> value;
    return value;
}

/**
 * @brief   将字符串解析为布尔值（模板特化版本）
 * @param   str 输入字符串
 * @return  解析得到的布尔值
 * @details 使用boolalpha解析"true"/"false"字符串
 */
template<>
inline bool parseString<bool>(const string& str)
{
    bool value;
    istringstream iss(str);
    iss >> std::boolalpha >> value;
    return value;
}

/**
 * @brief   将十六进制字符串解析为指定类型的值
 * @tparam  T 目标类型
 * @param   str 输入十六进制字符串
 * @return  解析得到的值
 */
template<class T>
T parseHexString(const string& str) {
    T value;
    istringstream iss(str);
    iss >> std::hex >> value;
    return value;
}

/**
 * @brief   将任意类型转换为字符串
 * @tparam  T 输入值类型
 * @param   value 输入值
 * @return  转换得到的字符串
 */
template<class T>
string toString(const T& value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

/**
 * @brief   将任意类型转换为十六进制字符串
 * @tparam  T 输入值类型
 * @param   value 输入值
 * @param   width 输出宽度，不足则左侧补0，设置为0不补零
 * @return  十六进制字符串
 */
template<class T>
string toHexString(const T& value, int width) {
    ostringstream oss;
    oss << std::hex;
    if (width > 0) {
        oss << std::setw(width) << std::setfill('0');
    }
    oss << value;
    return oss.str();
}

} // namespace strutil


//! 字符串分词器类
namespace strutil {

/*!
 *	\brief  字符串分词器
 *
 *  将一个完整的字符串按照指定分隔符分割为多个标记（token）
 *  支持增量分词，每次获取一个token
 */
class Tokenizer
{
public:
    /**
     * @brief 构造函数，使用默认分隔符（空格）
     * @param str 要分词的字符串
     */
    Tokenizer(const string& str)
        : m_String(str), m_Offset(0), m_Delimiters("  ") {}

    /**
     * @brief 构造函数，指定分隔符集合
     * @param str 要分词的字符串
     * @param delimiters 分隔符集合
     */
    Tokenizer(const string& str, const string& delimiters)
        : m_String(str), m_Offset(0), m_Delimiters(delimiters) {}

    /**
     * @brief 获取下一个token，使用构造时指定的分隔符
     * @return 是否成功获取到下一个token
     */
    bool nextToken() {
        return nextToken(m_Delimiters);
    }

    /**
     * @brief 获取下一个token，使用指定的分隔符
     * @param delimiters 分隔符集合
     * @return 是否成功获取到下一个token
     */
    bool nextToken(const string& delimiters)
    {
        // 查找下一个token的起始位置（跳过开头分隔符）
        size_t i = m_String.find_first_not_of(delimiters, m_Offset);
        if (i == string::npos) {
            m_Offset = m_String.length();
            return false;
        }

        // 查找token的结束位置（下一个分隔符）
        size_t j = m_String.find_first_of(delimiters, i);
        if (j == string::npos) {
            m_Token = m_String.substr(i);
            m_Offset = m_String.length();
            return true;
        }

        // 截取token并更新当前位置
        m_Token = m_String.substr(i, j - i);
        m_Offset = j;
        return true;
    }

    /**
     * @brief 获取当前token
     * @return 当前token字符串
     */
    const string getToken() const {
        return m_Token;
    }

    /**
     * @brief 重置分词器，从头开始分词
     */
    void reset() {
        m_Offset = 0;
    }

private:
    size_t          m_Offset;        //!< 当前处理位置偏移
    const string    m_String;        //!< 待分词的原始字符串
    string          m_Token;         //!< 当前取出的token
    string          m_Delimiters;    //!< 分隔符集合
};

} // namespace strutil


namespace strutil {

/**
 * @brief   将字符串分割为字符串向量
 * @param   str 输入字符串
 * @param   delimiters 分隔符集合
 * @return  分割后的字符串向量
 */
inline vector<string> split(const string& str, const string& delimiters)
{
    vector<string> ss;

    Tokenizer tokenizer(str, delimiters);
    while (tokenizer.nextToken())
    {
        ss.push_back(tokenizer.getToken());
    }

    return ss;
}

} // namespace strutil


/*
// 字符串分词迭代器（已注释，保留供参考）
struct string_token_iterator
  : public std::iterator<std::input_iterator_tag, std::string>
{
public:
    string_token_iterator() : str(0), start(0), end(0) {}
    string_token_iterator(const std::string & str_, const char * separator_ = " ") :
    separator(separator_),
    str(&str_),
    end(0)
    {
      find_next();
    }
    string_token_iterator(const string_token_iterator & rhs) :
    separator(rhs.separator),
    str(rhs.str),
    start(rhs.start),
    end(rhs.end)
  {
  }

  string_token_iterator & operator++()
  {
    find_next();
    return *this;
  }

  string_token_iterator operator++(int)
  {
    string_token_iterator temp(*this);
    ++(*this);
    return temp;
  }

  std::string operator*() const
  {
    return std::string(*str, start, end - start);
  }

  bool operator==(const string_token_iterator & rhs) const
  {
    return (rhs.str == str && rhs.start == start && rhs.end == end);
  }

  bool operator!=(const string_token_iterator & rhs) const
  {
    return !(rhs == *this);
  }

private:

  void find_next(void)
  {
    start = str->find_first_not_of(separator, end);
    if(start == std::string::npos)
    {
      start = end = 0;
      str = 0;
      return;
    }

    end = str->find_first_of(separator, start);
  }

  const char * separator;
  const std::string * str;
  std::string::size_type start;
  std::string::size_type end;
};
*/