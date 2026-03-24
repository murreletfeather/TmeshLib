/*!
*      \file HalfEdge.h
*      \brief 半边基类
*	   \author David Gu
*      \date 10/07/2010
*      \details 半边网格结构中的核心单元，每个半边表示有向边，记录方向和连接关系
*/

#ifndef _MESHLIB_HALFEDGE_H_
#define _MESHLIB_HALFEDGE_H_

#include <assert.h>
#include <math.h>
#include <string>
#include "Edge.h"

namespace MeshLib{

// 前向声明，只使用指针不需要包含头文件
class CVertex;
class CEdge;
class CFace;

/*!
 * \brief CHalfEdge 半边类，所有半边类的基类
 *
 *  半边网格(half-edge mesh)结构的核心，每条物理边拆分成两个方向相反的半边。
 *  半边记录了：
 *  - 目标顶点：该半边指向的顶点
 *  - 前驱后继：同一个面上相邻的前一个和后一个半边
 *  - 所在边：该半边归属的物理边
 *  - 所在面：该半边归属的面
 */
class CHalfEdge
{
public:
    /*!
     * @brief 构造函数，初始化所有指针为NULL
     */
	CHalfEdge(){ m_edge = NULL; m_vertex = NULL; m_prev = NULL; m_next = NULL; m_face = NULL; };
	
    /*!
     * @brief 析构函数
     */
	~CHalfEdge(){};

    /*!
     * @brief 获取该半边所在边的指针
     * @return 边指针的引用
     */
	CEdge * &  edge()    { return m_edge;   };
	
    /*!
     * @brief 获取该半边目标顶点的指针
     * @return 顶点指针的引用
     */
	CVertex * &  vertex()  { return m_vertex; };
	
    /*!
     * @brief 别名接口，同样获取目标顶点
     * @return 顶点指针的引用
     */
	CVertex * &  target()  { return m_vertex; };
	
    /*!
     * @brief 获取源顶点（起点）
     * @return 源顶点指针的引用
     * @details 源顶点就是前驱半边的目标顶点
     */
	CVertex * &  source()  { return m_prev->vertex();};
	
    /*!
     * @brief 获取前驱半边（同一个面环中前一个半边）
     * @return 前驱半边指针的引用
     */
	CHalfEdge * &  he_prev() { return m_prev;};
	
    /*!
     * @brief 获取后继半边（同一个面环中后一个半边）
     * @return 后继半边指针的引用
     */
	CHalfEdge * &  he_next() { return m_next;};
	
    /*!
     * @brief 获取对偶半边（同一条边上相反方向的半边）
     * @return 对偶半边指针的引用
     * @details 通过所在边的other()获取该边的另一个半边
     */
	CHalfEdge * & he_sym()  { return m_edge->other( this ); };
	
    /*!
     * @brief 获取该半边所在面的指针
     * @return 面指针的引用
     */
	CFace * & face()    { return m_face;};
	
    /*!
     * @brief 绕目标顶点逆时针(CCW)旋转半边，得到相邻的下一个半边
     * @return 旋转后的新半边，如果在边界没有找到返回NULL
     * @details 操作：当前半边 → 对偶 → 前驱，就是绕目标顶点逆时针旋转一步后的半边
     */
	CHalfEdge *   ccw_rotate_about_target();
	
    /*!
     * @brief 绕目标顶点顺时针(CLW)旋转半边，得到相邻的下一个半边
     * @return 旋转后的新半边，如果在边界没有找到返回NULL
     * @details 操作：当前半边 → 后继 → 对偶，就是绕目标顶点顺时针旋转一步后的半边
     */
	CHalfEdge *   clw_rotate_about_target();
	
    /*!
     * @brief 绕源顶点逆时针(CCW)旋转半边，得到相邻的下一个半边
     * @return 旋转后的新半边，如果在边界没有找到返回NULL
     * @details 操作：当前半边 → 前驱 → 对偶，就是绕源顶点逆时针旋转一步后的半边
     */
	CHalfEdge *   ccw_rotate_about_source();
	
    /*!
     * @brief 绕源顶点顺时针(CLW)旋转半边，得到相邻的下一个半边
     * @return 旋转后的新半边，如果在边界没有找到返回NULL
     * @details 操作：当前半边 → 对偶 → 后继，就是绕源顶点顺时针旋转一步后的半边
     */
	CHalfEdge *   clw_rotate_about_source();
	
    /*!
     * @brief 获取该半边关联的字符串属性
     * @return 字符串引用
     * @details 用于存储自定义属性，从.obj/.m文件读写
     */
	std::string & string() { return m_string; };
	
    /*!
     * @brief 将自定义属性写入字符串（子类可重写）
     */
	void _to_string()   {};
	
    /*!
     * @brief 从字符串中读取自定义属性（子类可重写）
     */
	void _from_string() {};

protected:
	CEdge       * m_edge;    //!< 该半边归属的物理边
	CFace       * m_face;    //!< 该半边归属的面
	CVertex     * m_vertex;  //!< 目标顶点（该半边指向的顶点）
	CHalfEdge  * m_prev;    //!< 同一个面环中的前驱半边
	CHalfEdge  * m_next;    //!< 同一个面环中的后继半边
	std::string  m_string;  //!< 存储自定义属性的字符串
};

/*!
 * @brief 绕目标顶点逆时针旋转（CCW）
 * @details CCW绕目标：当前半边 → 取对偶 → 取前驱
 */
inline CHalfEdge * CHalfEdge::ccw_rotate_about_target()
{
	CHalfEdge * he_dual = he_sym();
	if( he_dual == NULL ) return NULL;

	return he_dual->he_prev();
};

/*!
 * @brief 绕目标顶点顺时针旋转（CLW）
 * @details CLW绕目标：当前半边 → 取后继 → 取对偶
 */
inline CHalfEdge * CHalfEdge::clw_rotate_about_target()
{
	CHalfEdge * he = he_next()->he_sym();
	return he;
};

/*!
 * @brief 绕源顶点逆时针旋转（CCW）
 * @details CCW绕源：当前半边 → 取前驱 → 取对偶
 */
inline CHalfEdge * CHalfEdge::ccw_rotate_about_source()
{
	CHalfEdge * he = he_prev()->he_sym();
	return he;
};

/*!
 * @brief 绕源顶点顺时针旋转（CLW）
 * @details CLW绕源：当前半边 → 取对偶 → 取后继
 */
inline CHalfEdge * CHalfEdge::clw_rotate_about_source()
{
	CHalfEdge * he = he_sym();
	if( he == NULL ) return NULL;
	return he->he_next();
};

} // namespace MeshLib

#endif //_MESHLIB_HALFEDGE_H_ defined
