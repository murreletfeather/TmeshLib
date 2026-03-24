/*!
*      \file Edge.h
*      \brief 边的基类
*	   \author David Gu
*      \date 10/07/2010
*      \details 半边网格结构中的边，每条边存储两个方向相反的半边指针
*/


#ifndef _MESHLIB_EDGE_H_
#define _MESHLIB_EDGE_H_

#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string>

namespace MeshLib{

// 前向声明
class CHalfEdge;
class CVertex;

/*!
* \brief CEdge 边类，所有边类的基类
*
*  在半边网格结构中，每条边包含两个方向相反的半边（halfedge），分别指向两个端点。
*  如果边在边界上，则只有一个半边被分配，另一个半边指针为NULL。
*/
class CEdge
{
public:
	/*!
	 * @brief 构造函数，将两个半边指针初始化为NULL
	 */
	CEdge(){ m_halfedge[0] = NULL; m_halfedge[1] = NULL; };
	
	/*!
	 * @brief 析构函数
	 */
	~CEdge(){};
	
	/*!
	 * @brief 获取边上指定索引的半边
	 * @param id 半边索引，只能是0或1，每条边最多存储两个方向相反的半边
	 * @return 返回对应索引的半边指针的引用
	 */
	CHalfEdge * & halfedge( int id ) { 
		assert( 0 <= id && id < 2 );  // 确保索引在合法范围内
		return m_halfedge[id];
	};
	
	/*!	
	 * @brief 判断当前边是否在网格边界上
	 * @return 如果边在边界上返回true，否则返回false
	 * @details 边界边只有一个半边（另一个半边指针为NULL），内部边有两个半边
	 */
	bool boundary() { 
		return (m_halfedge[0] == NULL && m_halfedge[1] != NULL) || (m_halfedge[0] != NULL && m_halfedge[1] == NULL); 
	};
	
	/*!
	 * @brief 获取输入半边对应的对偶半边（同一条边上的另一个半边）
	 * @param he 输入半边指针，必须是当前边上的一个半边
	 * @return 返回同一条边上的另一个半边指针的引用
	 */
	CHalfEdge * & other( CHalfEdge * he ) { 
		return (he != m_halfedge[0]) ? m_halfedge[0] : m_halfedge[1]; 
	};
	
	/*!
	 * @brief 获取当前边关联的字符串（用于存储自定义属性）
	 * @return 字符串引用
	 * @details 用于从.m文件读写自定义属性，存储为字符串格式
	 */
	std::string & string() { return m_string; };
	
	/*!
	 * @brief 从字符串中读取自定义属性（子类可重写）
	 */
	void _from_string() {};
	
	/*!
	 * @brief 将自定义属性写入字符串（子类可重写）
	 */
	void _to_string() {};
protected:
	CHalfEdge      * m_halfedge[2];  //!< 当前边上存储的两个方向相反的半边指针数组，索引0和1
    std::string      m_string;      //!< 存储自定义属性的字符串，用于文件IO
};



} // namespace MeshLib

#endif //_MESHLIB_EDGE_H_
