/*!
*      \file parser.h
*      \brief 解析顶点、边、半边、面等的属性字符串
*          输入格式示例: "uv=(1.0 2.0) normal=(0.0 0.0 1.0) selected"
*          其中无值属性只保留键，有值属性格式为key=(value)
*      \brief Parse the trait strings of vertex, edge, halfedge , face etc.
*          Example input: "uv=(1.0 2.0) normal=(0.0 0.0 1.0) selected"
*          For valueless trait, only key is preserved; for valued trait, format is key=(value)
*	   \author David Gu
*      \date 10/07/2010
*
*/

#ifndef _MESHLIB_PARSER_H_
#define _MESHLIB_PARSER_H_

#include <string>
#include <assert.h>
#include <list>
#include <sstream>

namespace MeshLib
{

/*!
 *	\brief CToken类，存储格式为key=(value)，例如 uv=(x y)
 *	\brief CToken  class, key=(value), e.g. uv=(x y)
*/

class CToken
{
public:
	/*! 标记的键 */
	/*! key of the token */
	std::string m_key;
	/*! 标记的值 */
	/*! value of the token */
	std::string m_value;
};

/*!
 *	\brief 解析器类
 *	\brief CParser class
*/

class CParser
{
public:
	/*!
	 *	\brief CParser构造函数
	 *  \param str 输入字符串
	 *  \param str input string
	 */
	CParser( const std::string & str)
	{
		// 复制字符串到缓冲区
		//copy string
		unsigned int i;
		for(  i = 0; i < str.length(); i ++ )
		{
			m_line[i] = str.c_str()[i];
		}
		m_line[i] = 0;

		m_pt = m_line;
		
		// 未到达字符串末尾时继续解析
		//while not reaching the end
		while( !end() )
		{
			skip_blank();
			if( end() ) break;

			// 复制键
			//copy key

			char * pkey = m_key;
			char   ch = get_current_char();

			while( ch != ' ' && ch != '=' && !end() )
			{
				*pkey ++ = ch;
				ch = get_current_char();
			}
			if( ch != '=' && ch != ' ')
				*pkey++ = ch;

			*pkey = 0;

			if( ch == ' ' )
			{
				skip_blank();
			}

			// 如果没有等号，说明这是一个无值标记，只存储键
			if( ch != '=' )
			{
				CToken *	tk = new CToken;
				assert(tk);
				tk->m_key  = std::string( m_key );
				
				m_tokens.push_back( tk );
				continue;
			}

			if( end() ) break;

			ch = get_current_char();

			// 找到左括号
			while( ch != '(' ) ch = get_current_char();

			char * pvalue = m_value;

			// 读取直到右括号的内容作为值
			while( ch != ')' && !end() )
			{
				*pvalue ++ = ch;
				ch = get_current_char();
			}
			*pvalue++ = ch;
			*pvalue  = 0;

			// 创建标记并添加到列表
			CToken *	tk = new CToken;
			assert(tk);
			tk->m_key   = std::string( m_key   );
			tk->m_value = std::string( m_value );
			
			m_tokens.push_back( tk );
			
		}

	};

	/*!
	 *	CParser析构函数
	 *	CParser Destructor
	 */
	~CParser()
	{
	  // 释放所有标记的内存
	  //release all the tokens

	  for( std::list<CToken*>::iterator titer = m_tokens.begin(); titer != m_tokens.end(); titer ++ )
	  {
		  CToken * pT = *titer;
		  delete pT;
	  }
	  m_tokens.clear();
	};

	/*!
	 *	获取从字符串中提取的标记列表
	 *	List of tokens extracted from the string
	 */
	std::list<CToken*> & tokens() { return m_tokens; };
	
	/*!
	 *	将标记列表转换为字符串
	 *  \param str 输出字符串
	 *  \param str the output string
	 */
	void _toString( std::string & str )
	{
		std::stringstream iss;

		for( std::list<CToken*>::iterator iter = m_tokens.begin() ; iter != m_tokens.end(); ++ iter )
		{
			  CToken * token = *iter;
			  if( iss.str().length() > 0 ) iss << " ";
			  if( token->m_value.empty() )
			  {
				iss << token->m_key;
			  }
			  else
			  {
				iss << token->m_key << "=" << token->m_value;			  
			  }
		}

		str = iss.str();
	};
	/*!
	 *	移除指定键的标记key=(...)
	 *  \param key 要移除的标记的键
	 *  \param key the key to the token to be removed
	 */
	void _removeToken( const std::string & key )	
	{
		for( std::list<CToken*>::iterator iter = m_tokens.begin() ; iter != m_tokens.end(); ++ iter )
		{
			  CToken * token = *iter;
			  if( token->m_key == key )
			  {
				  m_tokens.erase( iter );
				  return;
			  }
		}
	};

private:

	/*!
	 *	获取当前指针位置的字符，并将指针移动到下一个位置
	 *	get the current char and move the pointer to next position
	 */
	char get_current_char()
	{
		char ch= *m_pt;
		m_pt++;
		return ch;
	};
	/*!
	 *	跳过空白字符
	 *	skip blank spaces
	 */
	void skip_blank()
	{
		while( *m_pt == ' ' ) m_pt++;
	};
	/*!
	 *	检查是否已经到达字符串末尾
	 *	verify if we reached the end of string
	 */
	bool end()
	{
		return ( (*m_pt) == 0 );
	};
	/*!
	 *	标记列表
	 *	list of tokens
	 */
	std::list<CToken*> m_tokens;
	
	/*!
	 * 存储输入字符串的缓冲区
	 * The buffer to contain the string
	 */
	char m_line[1024];
	/*!
	 *	当前解析到的键
	 *	current key
	 */
	char m_key[1024];
	/*!
	 *	当前解析到的值
	 *	current value
	 */
	char m_value[1024];
	/*!
	 *	当前字符缓冲区的指针
	 *	current pointer to the char buffer
	 */
	char * m_pt;
};


}; //namespace 
#endif