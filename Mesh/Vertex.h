/*!
*      \file Vertex.h
*      \brief 顶点基类，所有顶点类的基础
*	   \author David Gu
*      \date 10/07/2010
*
*/

#ifndef  _MESHLIB_VERTEX_H_
#define  _MESHLIB_VERTEX_H_

#include <stdlib.h>
#include <string>
#include <list>
#include "../Geometry/Point.h"
#include "../Geometry/Point2.h"
#include "HalfEdge.h"

namespace MeshLib
{

class CHalfEdge;
class CEdge;

/*!
 *  \brief CVertex 顶点类，是所有顶点类型的基类
 *
 *  基于半边数据结构，存储顶点基本信息：坐标、法向、纹理坐标，以及连接关系
 */
class CVertex
{
public:
    /*!
     *  CVertex 默认构造函数
     */
    CVertex() { m_halfedge = NULL; m_boundary = false; };

    /*!
     *  CVertex 析构函数
     */
    ~CVertex() {};

    /*!
     *  获取顶点位置坐标
     *  \return 顶点位置引用
     */
    CPoint & point() { return m_point; };

    /*!
     *  获取顶点法向
     *  \return 顶点法向引用
     */
    CPoint & normal() { return m_normal; };

    /*!
     *  获取顶点纹理坐标
     *  \return 纹理坐标(UV)引用
     */
    CPoint2 & uv() { return m_uv; };

    /*!
     *  找顶点最逆时针方向的出半边
     *  \return 最逆时针出半边指针
     */
    CHalfEdge * most_ccw_out_halfedge();

    /*!
     *  找顶点最顺时针方向的出半边
     *  \return 最顺时针出半边指针
     */
    CHalfEdge * most_clw_out_halfedge();

    /*!
     *  找顶点最逆时针方向的入半边
     *  \return 最逆时针入半边指针
     */
    CHalfEdge * most_ccw_in_halfedge();

    /*!
     *  找顶点最顺时针方向的入半边
     *  \return 最顺时针入半边指针
     */
    CHalfEdge * most_clw_in_halfedge();

    /*!
     *  获取/设置顶点的一个入半边（最CCW方向那个）
     *  \return 半边指针引用，可以用来修改
     */
    CHalfEdge * & halfedge() { return m_halfedge; };

    /*!
     *  获取顶点存储的字符串，用来保存扩展属性
     *  \return 字符串引用
     */
    std::string & string() { return m_string; };

    /*!
     *  获取顶点ID编号
     *  \return ID编号引用
     */
    int  & id() { return m_id; };

    /*!
     *  查询/设置顶点是否在网格边界上
     *  \return 边界标记引用，true表示顶点在边界，false表示内部顶点
     */
    bool & boundary() { return m_boundary; };

    /*!
     *  把顶点属性转换为字符串，子类可以重写
     */
    void _to_string() {};

    /*!
     *  从字符串读取顶点属性，子类可以重写
     */
    void _from_string() {};

    /*!
     *  邻接边列表，加载网格时临时使用
     *  \return 邻接边列表引用
     */
    std::list<CEdge*> & edges() { return m_edges; };

protected:
    int             m_id;         //!< 顶点ID编号
    CPoint          m_point;      //!< 顶点三维位置坐标
    CPoint          m_normal;     //!< 顶点法向（单位向量）
    CPoint2         m_uv;         //!< 二维纹理坐标(UV)
    CHalfEdge      *m_halfedge;   //!< 最逆时针方向的入半边
    bool            m_boundary;   //!< 边界标记：true表示顶点在网格边界
    std::string     m_string;     //!< 存储额外属性的字符串
    std::list<CEdge*> m_edges;    //!< 邻接边列表，加载网格临时使用
};

/*!
 *  寻找顶点最逆时针方向的入半边
 *  \return 最逆时针入半边指针
 *
 *  对于内部顶点，直接就是存储的m_halfedge，本身已经保持最CCW
 *  对于边界顶点，旋转直到找到最边缘的那个
 */
inline CHalfEdge * CVertex::most_ccw_in_halfedge()
{
    // 内部顶点
    if (!m_boundary)
    {
        return m_halfedge; // 当前存储的半边已经就是最CCW入半边
    }

    // 边界顶点，不断CCW旋转直到不能再转
    CHalfEdge * he = m_halfedge->ccw_rotate_about_target();
    while (he != NULL)
    {
        m_halfedge = he;
        he = m_halfedge->ccw_rotate_about_target();
    }
    // 现在m_halfedge就是最CCW的入半边了
    return m_halfedge;
}

/*!
 *  寻找顶点最顺时针方向的入半边
 *  \return 最顺时针入半边指针
 */
inline CHalfEdge * CVertex::most_clw_in_halfedge()
{
    // 内部顶点：最CCW再转一次CCW就是最CLW
    if (!m_boundary)
    {
        return most_ccw_in_halfedge()->ccw_rotate_about_target();
    }

    // 边界顶点，不断顺时针旋转直到不能再转
    CHalfEdge * he = m_halfedge->clw_rotate_about_target();
    while (he != NULL)
    {
        m_halfedge = he;
        he = m_halfedge->clw_rotate_about_target();
    }

    return m_halfedge;
}

/*!
 *  寻找顶点最逆时针方向的出半边
 *  \return 最逆时针出半边指针
 */
inline CHalfEdge * CVertex::most_ccw_out_halfedge()
{
    // 内部顶点：最CCW入半边的对称就是最CCW出半边
    if (!m_boundary)
    {
        return most_ccw_in_halfedge()->he_sym();
    }

    // 边界顶点，从边界开始找，不断绕源点旋转CCW直到结束
    CHalfEdge * he = m_halfedge->he_next();
    CHalfEdge * ne = he->ccw_rotate_about_source();

    while (ne != NULL)
    {
        he = ne;
        ne = he->ccw_rotate_about_source();
    }

    return he;
}

/*!
 *  寻找顶点最顺时针方向的出半边
 *  \return 最顺时针出半边指针
 */
inline CHalfEdge * CVertex::most_clw_out_halfedge()
{
    // 内部顶点：最CCW出半边再转一次CCW就是最CLW
    if (!m_boundary)
    {
        return most_ccw_out_halfedge()->ccw_rotate_about_source();
    }

    // 边界顶点，不断顺时针绕源点旋转直到结束
    CHalfEdge * he = m_halfedge->he_next();
    CHalfEdge * ne = he->clw_rotate_about_source();

    while (ne != NULL)
    {
        he = ne;
        ne = he->clw_rotate_about_source();
    }

    return he;
}

} // namespace MeshLib

#endif //_MESHLIB_VERTEX_H_