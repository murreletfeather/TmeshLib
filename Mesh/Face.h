/*!
*      \file Face.h
*      \brief 面的基类
*	   \author David Gu
*      \date 10/07/2010
*      \details 半边网格结构中的面，存储一个指向面上任意一个半边的指针
*/

#ifndef _MESHLIB_FACE_H_
#define _MESHLIB_FACE_H_

#include <assert.h>
#include <string>
#include "../Geometry/Point.h"

namespace MeshLib{

// 前向声明，只用到指针不需要包含头文件
class CHalfEdge;

/*!
 * \brief CFace 面类，所有面类的基类
 *
 *  在半边网格结构中，每个面对应一个闭合的半边环。只需要存储环上任意一个半边的指针，
 *  通过半边的next链接就能遍历面上所有的顶点和半边。
 */
class CFace
{
public:
	/*!	
	 * @brief 构造函数，将半边指针初始化为NULL
	 */
	CFace(){ m_halfedge = NULL; };
	
	/*!
	 * @brief 析构函数
	 */
	~CFace(){};
	
	/*!
	 * @brief 获取面上的一个半边（任意一个半边，通常用来遍历整个面）
	 * @return 半边指针的引用
	 * @details 存储面上任意一个半边，通过halfedge->next()可以遍历整个面环
	 */
	CHalfEdge *& halfedge() { return m_halfedge; };
	
	/*!
	 * @brief 获取面ID的引用（可修改）
	 * @return 面ID的引用
	 */
	int & id() { return m_id; };
	
	/*!
	 * @brief 获取面ID的值（只读）
	 * @return 面ID的常值引用
	 */
	const int id() const { return m_id; };
	
	/*!
	 * @brief 获取当前面对联的字符串（用于存储自定义属性）
	 * @return 字符串引用
	 * @details 用于从.m文件读写自定义属性，存储为字符串格式
	 */
	std::string & string() { return m_string; };
	
	/*!
	 * @brief 将自定义属性写入字符串（子类可重写）
	 */
	void _to_string() {};
	
	/*!
	 * @brief 从字符串中读取自定义属性（子类可重写）
	 */
	void _from_string() {};
protected:
	int          m_id;       //!< 面的唯一ID
	CHalfEdge  * m_halfedge; //!< 指向面上任意一个半边的指针
    std::string  m_string;   //!< 存储自定义属性的字符串，用于文件IO
};


} // namespace MeshLib

#endif //_MESHLIB_FACE_H_ defined
