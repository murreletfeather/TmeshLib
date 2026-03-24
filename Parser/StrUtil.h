/*!
*      \file StrUtil.h
*      \brief 字符串工具库
*      \date 文档创建于 10/08/2010
*      \author 原始作者未知
*      \details 提供常见字符串操作功能，包括修剪、大小写转换、比较、类型转换、分割等
*/

#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>

// 字符串工具命名空间
namespace strutil {

using namespace std;

/**
 * @brief 修剪字符串左侧的空白字符
 * @param str 输入字符串
 * @return 修剪后的新字符串
 * @details 移除字符串开头的空格、制表符、换行符和回车符
 *          t.find_first_not_of(" \t\n\r") 查找第一个不在空白字符集合中的字符位置
 *          t.erase(0, pos) 删除从开头到该位置之前的所有字符，即删除开头的空白字符
 */
inline std::string trimLeft(const std::string& str)
{
    string t = str;
    // find_first_not_of找到第一个非空白字符的位置，从位置0开始删除到该位置之前的所有字符
    t.erase(0, t.find_first_not_of(" \t\n\r"));
    return t;
};

/**
 * @brief 修剪字符串右侧的空白字符
 * @param str 输入字符串
 * @return 修剪后的新字符串
 * @details 移除字符串末尾的空格、制表符、换行符和回车符
 *          t.find_last_not_of(" \t\n\r") 查找最后一个不在空白字符集合中的字符位置
 *          t.erase(pos + 1) 删除从该位置之后到末尾的所有字符，即删除末尾的空白字符
 */
inline std::string trimRight(const std::string& str)
{
    string t = str;
    // find_last_not_of找到最后一个非空白字符的位置，删除从该位置+1到末尾的所有字符
    t.erase(t.find_last_not_of(" \t\n\r") + 1);
    return t;
};

/**
 * @brief 修剪字符串两端的空白字符
 * @param str 输入字符串
 * @return 修剪后的新字符串
 * @details 同时移除字符串开头和末尾的空白字符
 *          先修剪左侧，再修剪右侧
 */
inline std::string trim(const std::string& str)
{
    string t = str;
    // 修剪左侧：删除开头的空白字符
    t.erase(0, t.find_first_not_of(" \t\n\r"));
    // 修剪右侧：删除末尾的空白字符
    t.erase(t.find_last_not_of(" \t\n\r") + 1);
    return t;
};

/**
 * @brief 按照指定分隔符修剪字符串两端
 * @param str 输入字符串
 * @param delimitor 要修剪的字符集合
 * @return 修剪后的新字符串
 * @details 移除字符串两端属于指定分隔符集合的字符
 */
inline std::string trim(const std::string& str, const std::string & delimitor)
{
    string t = str;
    // 修剪左侧：删除开头所有属于delimitor的字符
    t.erase(0, t.find_first_not_of(delimitor));
    // 修剪右侧：删除末尾所有属于delimitor的字符
    t.erase(t.find_last_not_of(delimitor) + 1);
    return t;
};

/**
 * @brief 将字符串转换为小写
 * @param str 输入字符串
 * @return 转换为全小写的新字符串
 */
inline std::string toLower(const std::string& str)
{
    string t = str;
    transform(t.begin(), t.end(), t.begin(), ::tolower);
    return t;
};

/**
 * @brief 将字符串转换为大写
 * @param str 输入字符串
 * @return 转换为全大写的新字符串
 */
inline std::string toUpper(const std::string& str)
{
    string t = str;
    transform(t.begin(), t.end(), t.begin(), ::toupper);
    return t;
};

/**
 * @brief 判断字符串是否以指定子串开头
 * @param str 原字符串
 * @param substr 开头子串
 * @return 如果str以substr开头返回true，否则返回false
 * @details 先检查长度，如果子串长度大于原字符串直接返回false
 *          然后使用compare直接比较前缀部分，比find更高效
 */
inline bool startsWith(const std::string& str, const std::string& substr)
{
    if (str.length() < substr.length()) {
        return false;
    }
    return str.compare(0, substr.length(), substr) == 0;
};

/**
 * @brief 判断字符串是否以指定子串结尾
 * @param str 原字符串
 * @param substr 结尾子串
 * @return 如果str以substr结尾返回true，否则返回false
 * @details 先检查长度，如果子串长度大于原字符串直接返回false
 *          然后使用compare直接比较后缀部分，比rfind更高效
 */
inline bool endsWith(const std::string& str, const std::string& substr)
{
    if (str.length() < substr.length()) {
        return false;
    }
    size_t pos = str.length() - substr.length();
    return str.compare(pos, substr.length(), substr) == 0;
};

/**
 * @brief 比较两个字符串是否相等（忽略大小写）
 * @param str1 第一个字符串
 * @param str2 第二个字符串
 * @return 忽略大小写后相等返回true，否则返回false
 */
inline bool equalsIgnoreCase(const std::string& str1, const std::string& str2)
{
  return toLower(str1) == toLower(str2);
};

/**
 * @brief 将布尔值转换为字符串
 * @param value 布尔值
 * @return "true"或"false"字符串
 */
inline std::string toString(const bool& value)
{
    ostringstream oss;
    oss << boolalpha << value;
    return oss.str();
};

/**
 * @brief 将字符串解析为指定类型的值
 * @tparam T 目标类型
 * @param str 输入字符串
 * @return 解析得到的值
 */
template<class T> T parseString(const std::string& str) {
    T value;
    std::istringstream iss(str);
    iss >> value;
    return value;
};

/**
 * @brief 将字符串解析为布尔值（特化版本）
 * @param str 输入字符串
 * @return 解析得到的布尔值
 * @details 使用boolalpha解析"true"/"false"字符串
 */
template<> bool parseString<bool>(const std::string& str)
{
    bool value;
    std::istringstream iss(str);
    iss >> boolalpha >> value;
    return value;
};

/**
 * @brief 将十六进制字符串解析为指定类型的值
 * @tparam T 目标类型
 * @param str 输入十六进制字符串
 * @return 解析得到的值
 */
template<class T> T parseHexString(const std::string& str) {
    T value;
    std::istringstream iss(str);
    iss >> hex >> value;
    return value;
};

/**
 * @brief 将任意类型转换为字符串
 * @tparam T 输入值类型
 * @param value 输入值
 * @return 转换得到的字符串
 */
template<class T> std::string toString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
};

/**
 * @brief 将任意类型转换为十六进制字符串
 * @tparam T 输入值类型
 * @param value 输入值
 * @param width 输出宽度，不足则左侧补0
 * @return 十六进制字符串
 */
template<class T> std::string toHexString(const T& value, int width) {
    std::ostringstream oss;
    oss << hex;
    if (width > 0) {
        oss << setw(width) << setfill('0');
    }
    oss << value;
    return oss.str();
};

} // namespace strutil

// 分词器类
namespace strutil {

/*!
*	\brief 字符串分词器
*
*	将一个完整的字符串分割为多个标记（token）
*/
class Tokenizer
{
public:
    /**
     * @brief 构造函数，使用默认分隔符（空格）
     * @param str 要分词的字符串
     */
    Tokenizer(const std::string& str)
        : m_String(str), m_Offset(0), m_Delimiters("  ") {};

    /**
     * @brief 构造函数，指定分隔符
     * @param str 要分词的字符串
     * @param delimiters 分隔符集合
     */
    Tokenizer(const std::string& str, const std::string& delimiters)
        : m_String(str), m_Offset(0), m_Delimiters(delimiters) {};

    /**
     * @brief 获取下一个token，使用构造时指定的分隔符
     * @return 是否成功获取到下一个token
     */
    bool nextToken() { return nextToken(m_Delimiters); };

    /**
     * @brief 获取下一个token，使用指定的分隔符
     * @param delimiters 分隔符集合
     * @return 是否成功获取到下一个token
     */
    bool nextToken(const std::string& delimiters)
    {
        // 查找下一个token的起始位置
        size_t i = m_String.find_first_not_of(delimiters, m_Offset);
        if (i == string::npos) {
            m_Offset = m_String.length();
            return false;
        }

        // 查找token的结束位置
        size_t j = m_String.find_first_of(delimiters, i);
        if (j == string::npos) {
            m_Token = m_String.substr(i);
            m_Offset = m_String.length();
            return true;
        }

        // 截取token并保存当前位置
        m_Token = m_String.substr(i, j - i);
        m_Offset = j;
        return true;
    };

    /**
     * @brief 获取当前token
     * @return 当前token字符串
     */
    const std::string getToken() const { return m_Token; };

    /**
     * @brief 重置分词器，从头开始分词
     */
    void reset() { m_Offset = 0; };

protected:
    size_t m_Offset;               // 当前处理位置偏移
    const std::string m_String;    // 原始字符串
    std::string m_Token;           // 当前token
    std::string m_Delimiters;      // 分隔符集合
};

} // namespace strutil

namespace strutil {

/**
 * @brief 将字符串分割为字符串向量
 * @param str 输入字符串
 * @param delimiters 分隔符集合
 * @return 分割后的字符串向量
 */
inline std::vector<std::string> split(const std::string& str, const std::string& delimiters)
{
        vector<string> ss;

        Tokenizer tokenizer(str, delimiters);
        while (tokenizer.nextToken())
        {
            ss.push_back(tokenizer.getToken());
        }

        return ss;
};

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