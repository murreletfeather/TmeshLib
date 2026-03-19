/*!
*      \file BaseMesh.h
*      \brief 所有网格类的基类
*
*		这是网格的基础类
*	   \作者 David Gu
*      \日期 10/07/2010
*
*/

#ifndef _MESHLIB_BASE_MESH_H_
#define _MESHLIB_BASE_MESH_H_

#define MAX_LINE 2048

#include <math.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <map>

#include "../Geometry/Point.h"
#include "../Geometry/Point2.h"
#include "../Parser/StrUtil.h"

namespace MeshLib
{

/*!
* \brief CBaseMesh, 所有网格类型的基类
*
*  这是网格的基础类，包含顶点列表、边列表和面列表。所有几何对象通过指针连接，
*  顶点、边和面都通过半边结构连接。网格类提供文件IO功能，支持.obj、.m和.off文件格式。
*  提供欧拉操作，每个几何图元都可以自由访问邻居。
*  
* \tparam CVertex   顶点类，派生自 MeshLib::CVertex   类
* \tparam CEdge     边类，派生自 MeshLib::CEdge     类
* \tparam CFace     面对类，派生自 MeshLib::CFace     类
* \tparam CHalfEdge 半边类，派生自 MeshLib::CHalfEdge 类
*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class CBaseMesh
{
public:
	// 顶点、半边、边、面的指针类型定义
	typedef CVertex   * tVertex;
	typedef CHalfEdge * tHalfEdge;
	typedef CEdge     * tEdge;
	typedef CFace     * tFace;

	// 构造函数和析构函数
	/*!
	构造函数
	*/
	CBaseMesh(){};
	/*!
	析构函数
	*/
	~CBaseMesh();

	// 拷贝操作
	/*!
	拷贝运算符
	*/
	void copy( CBaseMesh & mesh );

	// 文件IO
	/*!
	读取.obj文件
	\param filename 输入.obj文件名
	*/
	void read_obj(  const char * filename );
	/*!
	写入.obj文件
	\param output 输出.obj文件名
	*/
	void write_obj( const char * output);

	/*!
	读取.m文件
	\param input 输入.m文件名
	*/
	void read_m(  const char * input );
	/*!
	写入.m文件
	\param output 输出.m文件名
	*/
	void write_m( const char * output);
	
	/*!
	读取.off文件
	\param input 输入.off文件名
	*/
	void read_off( const char * input );
	/*!
	写入.off文件
	\param output 输出.off文件名
	*/
	void write_off( const char * output);

	// 顶点、面、边数量
	/*! 顶点数量 */
	int  numVertices();
	/*! 边数量 */
	int  numEdges();
	/*! 面数量 */
	int  numFaces();

	// 判断是否在边界上
	/*! 判断顶点是否在边界上
	\param v 顶点指针
	*/
	bool    isBoundary( tVertex  v );
	/*! 判断边是否在边界上
	\param e 边指针
	*/
	bool    isBoundary( tEdge    e );
	/*! 判断半边是否在边界上
	\param he 半边指针
	*/
	bool    isBoundary( tHalfEdge  he );

	// 根据ID访问顶点
	/*!
	通过ID访问顶点
	\param id 顶点ID
	\return ID等于id的顶点，如果不存在返回NULL
	*/
	tVertex idVertex( int id );
	/*!
	获取顶点ID
	\param v 输入顶点
	\return 顶点ID
	*/
	int     vertexId( tVertex  v );

	// 根据ID访问面
	/*!
	通过ID访问面
	\param id 面ID
	\return ID等于id的面，如果不存在返回NULL
	*/
	tFace   idFace( int id );
	/*!
	获取面ID
	\param f 输入面
	\return 面ID
	*/
	int     faceId( tFace  f );

	// 通过两个顶点访问边
	/*!
	通过两个端点访问边
	\param v0 边的一个顶点
	\param v1 边的另一个顶点
	\return 连接v0和v1的边，如果不存在返回NULL
	*/
	tEdge   vertexEdge( tVertex v0, tVertex v1 );

	// 通过两个顶点访问半边
	/*!
	通过两个端点访问半边
	\param v0 半边的一个顶点
	\param v1 半边的另一个顶点
	\return 连接v0和v1的半边，如果不存在返回NULL
	*/
	
	tHalfEdge   vertexHalfedge( tVertex v0, tVertex v1 );
	/*!
	通过目标顶点和面访问半边
	\param v 目标顶点 
	\param f 关联面
	\return 目标顶点为v，关联面为f的半边，如果不存在返回NULL
	*/
	tHalfEdge   corner( tVertex v, tFace f);

	// 半边 -> 面
	/*!
	获取半边关联的面
	\param he 输入半边
	\return 半边所附着的面
	*/
	tFace   halfedgeFace( tHalfEdge he );
	// 半边 -> 顶点
	/*!
	获取半边的目标顶点
	\param he 输入半边
	\return 半边的目标顶点
	*/
	tVertex halfedgeVertex( tHalfEdge he );
	// 半边 -> 顶点
	/*!
	获取半边的目标顶点
	\param he 输入半边
	\return 半边的目标顶点
	*/
	tVertex halfedgeTarget( tHalfEdge he );
	// 半边 -> 顶点
	/*!
	获取半边的源顶点
	\param he 输入半边
	\return 半边的源顶点
	*/
	tVertex halfedgeSource( tHalfEdge he );

	// 半边 -> 下一个半边
	/*!
	获取半边的下一个半边
	\param he 输入半边
	\return 输入半边he的下一个半边
	*/

	tHalfEdge   halfedgeNext( tHalfEdge he );
	// 半边 -> 前一个半边
	/*!
	获取半边的前一个半边
	\param he 输入半边
	\return 输入半边he的前一个半边
	*/
	tHalfEdge   halfedgePrev( tHalfEdge he );
	// 半边 -> 对偶半边
	/*!
	获取半边的对偶半边
	\param he 输入半边
	\return 输入半边he的对偶半边
	*/
	tHalfEdge   halfedgeSym( tHalfEdge he );
	// 半边 -> 边
	/*!
	获取半边所属的边
	\param he 输入半边
	\return 半边所属的边
	*/

	tEdge       halfedgeEdge( tHalfEdge he );
	// 顶点 -> 半边
	/*!
	获取指向顶点v的半边，它是顶点v所有半边中最逆时针的
	\param v 输入顶点
	\return 指向顶点v的最逆时针半边
	*/
	tHalfEdge   vertexHalfedge( tVertex v );
	// 顶点 -> 边列表
	/*!
	获取附着在顶点v的边列表，其中v是边的第一个顶点
	\param v 输入顶点
	\return 边列表的引用
	*/
	std::list<tEdge> &  vertexEdges( tVertex v );

	// 边 -> 顶点
	/*!
	获取边的第一个顶点
	\param e 输入边
	\return 边e的第一个顶点
	*/
	tVertex edgeVertex1( tEdge  e );
	/*!
	获取边的第二个顶点
	\param e 输入边
	\return 边e的第二个顶点
	*/
	tVertex edgeVertex2( tEdge  e );

	// 边 -> 面
	/*!
	获取边的第一个面
	\param e 输入边
	\return 附着在边e的第一个面
	*/
	tFace edgeFace1( tEdge  e );
	/*!
	获取边的第二个面
	\param e 输入边
	\return 附着在边e的第二个面
	*/
	tFace edgeFace2( tEdge  e );

	// 边 -> 半边
	/*!
	获取边上索引为id的半边
	\param e 输入边
	\param id 半边索引，只能是0或1
	\return 边e上的第id个半边
	*/

	tHalfEdge edgeHalfedge( tEdge  e, int id);

	// 面 -> 半边
	/*!
	获取面的第一个半边
	\param f 输入面
	\return 面f的第一个半边
	*/

	tHalfEdge faceHalfedge( tFace f );

	// 欧拉操作
	/*!
	顶点最顺时针出半边
	\param v 输入顶点
	\return 顶点v的最顺时针出半边
	*/
	tHalfEdge vertexMostClwOutHalfEdge( tVertex  v );
	/*!
	下一个逆时针出半边
	\param he 输入半边
	\return 与he共享源顶点的下一个逆时针出半边
	*/

	tHalfEdge vertexNextCcwOutHalfEdge( tHalfEdge  he );

	/*!
	顶点最逆时针出半边
	\param v 输入顶点
	\return 顶点v的最逆时针出半边
	*/
	tHalfEdge vertexMostCcwOutHalfEdge( tVertex  v );
	/*!
	下一个顺时针出半边
	\param he 输入半边
	\return 与he共享源顶点的下一个顺时针出半边
	*/
	tHalfEdge vertexNextClwOutHalfEdge( tHalfEdge  he );

	/*!
	顶点最顺时针入半边
	\param v 输入顶点
	\return 顶点v的最顺时针入半边
	*/
	tHalfEdge vertexMostClwInHalfEdge( tVertex  v );
	/*!
	下一个逆时针入半边
	\param he 输入半边
	\return 与he共享目标顶点的下一个逆时针入半边
	*/
	tHalfEdge vertexNextCcwInHalfEdge( tHalfEdge  he );

	/*!
	顶点最逆时针入半边
	\param v 输入顶点
	\return 顶点v的最逆时针入半边
	*/
	tHalfEdge vertexMostCcwInHalfEdge( tVertex  v );
	/*!
	下一个顺时针入半边
	\param he 输入半边
	\return 与he共享目标顶点的下一个顺时针入半边
	*/
	tHalfEdge vertexNextClwInHalfEdge( tHalfEdge  he );

	/*!
	面的最顺时针半边
	\param face 输入面
	\return 面face的最顺时针半边
	*/
	
	tHalfEdge faceMostClwHalfEdge( tFace  face );
	/*!
	面的最逆时针半边
	\param face 输入面
	\return 面face的最逆时针半边
	*/
	tHalfEdge faceMostCcwHalfEdge( tFace  face );
	/*!
	面中当前半边的下一个逆时针半边
	\param he 输入半边
	\return 面中he的下一个逆时针半边
	*/
	tHalfEdge faceNextCcwHalfEdge( tHalfEdge  he );
	/*!
	面中当前半边的下一个顺时针半边
	\param he 输入半边
	\return 面中he的下一个顺时针半边
	*/
	tHalfEdge faceNextClwHalfEdge( tHalfEdge  he );


	/*!
	计算边长
	\param e 输入边
	\return 边e的长度
	*/
	double edgeLength( tEdge e );

	/*!
	获取网格边列表
	*/
	std::list<tEdge>   & edges()		{ return m_edges; };
	/*!
	获取网格面列表
	*/
	std::list<tFace>   & faces()		{ return m_faces; };
	/*!
	获取网格顶点列表
	*/
	std::list<tVertex> & vertices()	{ return m_verts; };
/*
	bool with_uv() { return m_with_texture; };
	bool with_normal() { return m_with_normal; };
*/
protected:

	/*! 边列表 */
	std::list<tEdge>                          m_edges;
	/*! 顶点列表 */
	std::list<tVertex>                        m_verts;
	/*! 面列表 */
	std::list<tFace>						  m_faces;

	// 映射表

	/*! 顶点ID到顶点指针的映射表 */
	std::map<int, tVertex>                    m_map_vert;
	/*! 面ID到面对指针的映射表 */
	std::map<int, tFace>					  m_map_face;
public:
	/*! 创建顶点
	\param id 顶点ID
	\return 新创建顶点的指针
	*/
	tVertex   createVertex(   int id = 0 );
	/*! 创建边
	\param v1 边的第一个端点
	\param v2 边的第二个端点
	\return 新创建边的指针
	*/
	tEdge     createEdge(	tVertex v1, tVertex v2 );
	/*! 创建面
	\param v 顶点数组
	\param id 面ID
	\return 新创建面的指针
	*/
	tFace     createFace(   tVertex  v[], int id ); // 创建三角形
	/*! 创建面
	\param v 顶点向量数组
	\param id 面ID
	\return 新创建面的指针
	*/
	tFace     createFace(   std::vector<tVertex> &  v, int id ); // 创建三角形

	/*! 删除一个面
	\param pFace 要删除的面
	*/
	void      deleteFace( tFace  pFace );
	
	/*! 顶点是否包含纹理坐标 */
	bool      m_with_texture;
	/*! 网格是否包含法向量 */
	bool      m_with_normal;

	/*! 标记边界顶点、边、面 */
	void labelBoundary( void );

};



/*!
获取边的第一个顶点
\param e 输入边
\return 边e的第一个顶点
*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CVertex * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::edgeVertex1( tEdge   e )
{
	assert( e->halfedge(0 ) != NULL );
	return (CVertex*)e->halfedge(0)->source();
};

/*!
获取边的第二个顶点
\param e 输入边
\return 边e的第二个顶点
*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CVertex *  CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::edgeVertex2( tEdge   e )
{
	assert( e->halfedge(0 ) != NULL );
	return (CVertex*)e->halfedge(0)->target();
};

/*!
获取边的第一个面
\param e 输入边
\return 边e上附着的第一个面
*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CFace * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::edgeFace1( tEdge   e )
{
	assert( e->halfedge(0) != NULL );
	return (CFace*) e->halfedge(0)->face();
};

// 半边 -> 边
/*!
获取边上第id个半边
\param e 输入边
\param id 半边索引，0或1
\return 边e上第id个半边
*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::edgeHalfedge( tEdge   e, int id )
{
	return (CHalfEdge*)e->halfedge(id);
};

//access e->f
/*!
The second face attaching to an edge.
\param e the input edge.
\return the first face attaching to e.
*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CFace * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::edgeFace2( tEdge   e )
{
	assert( e->halfedge(1) != NULL );
	return (CFace*) e->halfedge(1)->face();
};

//access he->f
/*!
	The face a halfedge attaching to. 
	\param he the input halfedge
	\return the face he attaches
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CFace * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::halfedgeFace( tHalfEdge   he )
{
	return (CFace*)he->face();
};

//access f->he
	/*!
	The first halfedge attaching to a face f.
	\param f the input face.
	\return the first halfedge attaching to f.
	*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::faceHalfedge( tFace   f )
{
	return (CHalfEdge*)f->halfedge();
};


//access he->next
/*!
	The next halfedge of a halfedge. 
	\param he the input halfedge.
	\return the next halfedge of he.
	*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::halfedgeNext( tHalfEdge   he )
{
	return (CHalfEdge*)he->he_next();
};

//access he->prev
/*!
	The previous halfedge of a halfedge. 
	\param he the input halfedge.
	\return the next halfedge of he.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::halfedgePrev( tHalfEdge  he )
{
	return (CHalfEdge*)he->he_prev();
};

//access he->sym
/*!
	The dual halfedge of a halfedge. 
	\param he the input halfedge.
	\return the dual halfedge of he.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::halfedgeSym( tHalfEdge   he )
{
	return (CHalfEdge*)he->he_sym();
};

//access he->edge
/*!
	The edge of a halfedge. 
	\param he the input halfedge.
	\return the edge of he.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::halfedgeEdge( tHalfEdge  he )
{
	return (CEdge*)he->edge();
};

//access he->v
/*!
	The target vertex of a halfedge. 
	\param he the input halfedge.
	\return the target vertex of he.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CVertex * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::halfedgeVertex( tHalfEdge  he )
{
	return (CVertex*)he->vertex();
};

//access he->v
/*!
	The target vertex of a halfedge. 
	\param he the input halfedge.
	\return the target vertex of he.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CVertex * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::halfedgeTarget( tHalfEdge   he )
{
	return (CVertex*)he->vertex();
};

//access he->v
/*!
	The source vertex of a halfedge. 
	\param he the input halfedge.
	\return the source vertex of he.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CVertex * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::halfedgeSource( tHalfEdge   he )
{
	return (CVertex*)he->he_prev()->vertex();
};
/*! whether a vertex is on the boundary
	\param v the pointer to the vertex
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline bool CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::isBoundary( tVertex   v )
{
	return v->boundary();
};
/*! whether an edge is on the boundary
	\param e the pointer to the edge
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline bool CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::isBoundary( tEdge   e )
{
	if( e->halfedge(0) == NULL || e->halfedge(1) == NULL ) return true;
	return false;
};
/*! whether a halfedge is on the boundary
	\param he the pointer to the halfedge
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline bool CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::isBoundary( tHalfEdge   he )
{
	if( he->he_sym() == NULL ) return true;
	return false;
};

/*! Number of vertices of the mesh
*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline int CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::numVertices() 
{
	return (int) m_verts.size();
};

/*! Number of edges of the mesh
*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline int CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::numEdges() 
{
	return (int) m_edges.size();
};

/*! Number of faces of the mesh
*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline int CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::numFaces() 
{
	return (int) m_faces.size();
};


//Euler operation
/*!
	The most Clw Out HalfEdge of a vertex
	\param v the input vertex.
	\return the most Clw Out HalfEdge of v.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge *  CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexMostClwOutHalfEdge( tVertex   v )
{
	return (CHalfEdge*)v->most_clw_out_halfedge();
};
/*!
	The next Ccw Out HalfEdge 
	\param v the input vertex.
	\return the next Ccw Out HalfEdge, sharing the same source of he.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexMostCcwOutHalfEdge( tVertex   v )
{
	return (CHalfEdge*)v->most_ccw_out_halfedge();
};

/*!
	Access a halfedge by its target vertex, and attaching face.
	\param v target vertex 
	\param f attaching face
	\return halfedge, whose target is v, attaching face is f. NULL if no such an halfedge exists.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::corner( tVertex  v, tFace  f)
{
	CHalfEdge * he = faceMostCcwHalfEdge( f );
	do{
		if( he->vertex() == v )
			return (CHalfEdge*) he;
		he = faceNextCcwHalfEdge( he );
	}while( he != faceMostCcwHalfEdge(f) );
	return NULL;
};
/*!
	The next Ccw Out HalfEdge 
	\param he the input halfedge .
	\return the next Ccw Out HalfEdge, sharing the same source of he.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexNextCcwOutHalfEdge( tHalfEdge  he )
{
	return (CHalfEdge*) he->ccw_rotate_about_source();
};
/*!
	The next Clw Out HalfEdge 
	\param he the input halfedge .
	\return the next Clw Out HalfEdge, sharing the same source of he.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexNextClwOutHalfEdge( tHalfEdge   he )
{
	assert( he->he_sym() != NULL );
	return (CHalfEdge*)he->clw_rotate_about_source();
};
	/*!
	The most Clw In HalfEdge of a vertex
	\param v the input vertex.
	\return the most Clw In HalfEdge of v.
	*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexMostClwInHalfEdge( tVertex   v )
{
	return (CHalfEdge*)v->most_clw_in_halfedge();
};
	/*!
	The most Ccw In HalfEdge of a vertex
	\param v the input vertex.
	\return the most Clw In HalfEdge of v.
	*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexMostCcwInHalfEdge( tVertex   v )
{
	return (CHalfEdge*)v->most_ccw_in_halfedge();
};

	/*!
	The next Ccw In HalfEdge 
	\param he the input halfedge .
	\return the next Ccw In HalfEdge, sharing the same target of he.
	*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexNextCcwInHalfEdge( tHalfEdge   he )
{
	assert( he->he_sym() != NULL );
	return (CHalfEdge*)he->ccw_rotate_about_target();
};
/*!
	The next Clw In HalfEdge 
	\param he the input halfedge .
	\return the next Clw In HalfEdge, sharing the same target of he.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexNextClwInHalfEdge( tHalfEdge   he )
{
	return (CHalfEdge*)he->clw_rotate_about_target();
};
/*!
	The next Clw HalfEdge of a halfedge in a face
	\param he the input halfedge.
	\return the next Clw HalfEdge of he in a face.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::faceNextClwHalfEdge( tHalfEdge   he )
{
	return (CHalfEdge*)he->he_prev();
};
/*!
	The next Ccw HalfEdge of a halfedge in a face
	\param he the input halfedge.
	\return the next Ccw HalfEdge of he in a face.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::faceNextCcwHalfEdge( tHalfEdge   he )
{
	return (CHalfEdge*)he->he_next();
};

/*!
	The most Ccw HalfEdge of a face
	\param face the input face.
	\return the most Ccw HalfEdge of f.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge *  CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::faceMostCcwHalfEdge( tFace   face )
{
	return (CHalfEdge*)face->halfedge();
};
	/*!
	The most Clw HalfEdge in a face
	\param face the input face.
	\return the most Clw HalfEdge in a face.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::faceMostClwHalfEdge( tFace   face )
{
	return (CHalfEdge*)face->halfedge()->he_next();
};
/*!
 CBaseMesh destructor
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::~CBaseMesh()
{
	//remove vertices
	
  for( typename std::list<CVertex*>::iterator viter = m_verts.begin(); viter != m_verts.end(); viter ++ )
  {
      CVertex * pV = *viter;
      delete pV;
  }
  m_verts.clear();

	//remove faces

  for( typename std::list<CFace*>::iterator fiter = m_faces.begin(); fiter != m_faces.end(); fiter ++ )
  {
      CFace * pF = *fiter;

      tHalfEdge he = faceHalfedge( pF );
 
      std::list<CHalfEdge*> hes;
      do{
        he = halfedgeNext( he );
        hes.push_back( he );
      }while( he != pF->halfedge() );

      for( typename std::list<CHalfEdge*>::iterator hiter = hes.begin(); hiter != hes.end(); hiter ++)
      {
          CHalfEdge * pH = *hiter;
          delete pH;
      }
      hes.clear();

      delete pF;
  }
  m_faces.clear();
	
  //remove edges
  for( typename std::list<CEdge*>::iterator eiter = m_edges.begin(); eiter != m_edges.end(); eiter ++ )
  {
      CEdge * pE = *eiter;
      delete pE;
  }

  m_edges.clear();
	
  //clear all the maps
  m_map_vert.clear();
  m_map_face.clear();
  //m_map_edge.clear();
};

/*!
	Edge length
*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
double CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::edgeLength( tEdge  e )
{
	CVertex * v1 = edgeVertex1(e);
	CVertex * v2 = edgeVertex2(e);

	return ( v1->point() - v2->point() ).norm();
}


//create new gemetric simplexes
/*! Create a vertex 
\param id Vertex id
\return pointer to the new vertex
*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CVertex * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::createVertex( int id )
{
	CVertex * v = new CVertex();
	assert( v != NULL );
	v->id() = id;
	m_verts.push_back( v );
	m_map_vert.insert( std::pair<int,CVertex*>(id,v));
	return v;
};


/*!
Read an .obj file.
\param filename the filename .obj file name
*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::read_obj( const char * filename )
{

	std::fstream f(filename, std::fstream::in);
	if( f.fail() ) return;

	char cmd[1024];

	int  vid = 1;
	int  fid = 1;
	
	bool with_uv = false;
	bool with_normal = false;

	std::vector<CPoint2> uvs;
	std::vector<CPoint> normals;


	while ( f.getline( cmd, 1024) )
    {
		std::string line( cmd );
		line = strutil::trim( line );

		strutil::Tokenizer stokenizer( line, " \t\r\n" );

		stokenizer.nextToken();
		std::string token = stokenizer.getToken();
		
		if( token == "v" )
		{
			CPoint p;
			for( int i = 0; i < 3; i ++ )
			{
				stokenizer.nextToken();
				token = stokenizer.getToken();
				p[i] = strutil::parseString<float>(token);
			}
			
			CVertex * v = createVertex( vid);
			v->point() = p;
			vid ++;
			continue;
		}


		if( token == "vt" )
		{
			with_uv = true;
			CPoint2 uv;
			for( int i = 0; i < 2; i ++ )
			{
				stokenizer.nextToken();
				token = stokenizer.getToken();
				uv[i] = strutil::parseString<float>(token);
			}
			uvs.push_back( uv );
			continue;
		}


		if ( token ==  "vn" )
		{
			with_normal = true;

			CPoint n;
			for( int i = 0; i < 3; i ++ )
			{
				stokenizer.nextToken();
				token = stokenizer.getToken();
				n[i] = strutil::parseString<float>(token);
			}
			normals.push_back( n );
			continue;
		}




		if ( token == "f" )
		{
			CVertex* v[3];
			for( int i = 0 ; i < 3; i ++ )
			{
				stokenizer.nextToken();
				token = stokenizer.getToken();
				
				
				strutil::Tokenizer tokenizer( token, " /\t\r\n" );
				
				int ids[3];
				int k = 0;
				while( tokenizer.nextToken() )
				{
					std::string token = tokenizer.getToken();
					ids[k] = strutil::parseString<int>(token);
					k ++;
				}

				
				v[i] = m_map_vert[ ids[0] ];
				if( with_uv )
					v[i]->uv() = uvs[ ids[1]-1 ];
				if( with_normal )
					v[i]->normal() = normals[ ids[2]-1 ];
			}
			createFace( v, fid++ );
		}
	}

	f.close();

	labelBoundary();
}

/*! Create a face
	\param v an array of vertices
	\param id face id
	\return pointer to the new face
	*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CFace * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::createFace( tVertex  v[] , int id )
{
	  CFace * f = new CFace();
	  assert( f != NULL );
	  f->id() = id;
	  m_faces.push_back( f );
	  m_map_face.insert( std::pair<int,tFace>(id,f) );

		//create halfedges
		tHalfEdge hes[3];

		for(int i = 0; i < 3; i ++ )
		{
			hes[i] = new CHalfEdge;
			assert( hes[i] );
			CVertex * vert =  v[i];
			hes[i]->vertex() = vert;
			vert->halfedge() = hes[i];
		}

		//linking to each other
		for(int i = 0; i < 3; i ++ )
		{
			hes[i]->he_next() = hes[(i+1)%3];
			hes[i]->he_prev() = hes[(i+2)%3];
		}

		//linking to face
		for(int i = 0; i < 3; i ++ )
		{
			hes[i]->face()   = f;
			f->halfedge()    = hes[i];
		}

		//connecting with edge
		for(int i = 0; i < 3; i ++ )
		{
			tEdge e = createEdge( v[i], v[(i+2)%3] );
			if( e->halfedge(0)  == NULL )
			{
				e->halfedge(0) = hes[i];
			}
			else
			{
				assert( e->halfedge(1) == NULL );
				e->halfedge(1) = hes[i];
			}
			hes[i]->edge() = e;
		}

		return f;
};


//access id->v
/*!
Access a vertex by its id
\param id the vertex id
\return the vertex, whose ID equals to id. NULL, if there is no such a vertex.
*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CVertex * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::idVertex( int id ) 
{
	return m_map_vert[id];
};

//access v->id
/*!
	The vertex id
	\param v the input vertex
	\return the vertex id.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline int CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexId( tVertex   v )
{
	return v->id();
};

//access id->f
/*!
	Access a face by its id
	\param id the face id
	\return the face, whose ID equals to id. NULL, if there is no such a face.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CFace * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::idFace( int id )
{
	return m_map_face[id];
};

//acess f->id
/*!
	The face id
	\param f the input face
	\return the face id.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline int CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::faceId( tFace   f )
{
	return f->id();
};

/*! Create an edge
\param v1 end vertex of the edge
\param v2 end vertex of the edge
\return pointer to the new edge
*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::createEdge( tVertex  v1, tVertex  v2 )
{
	tVertex pV = ( v1->id()<v2->id())?v1:v2;
	std::list<CEdge*> & ledges = (std::list<CEdge*> &) pV->edges();

	
	for( typename std::list<CEdge*>::iterator te = ledges.begin(); te != ledges.end(); te ++ )
	{
		CEdge	  * pE = *te;
		CHalfEdge * pH = (CHalfEdge*) pE->halfedge(0);
	
		if( pH->source() == v1 && pH->target() == v2 ) 
		{
			return pE;		
		}
		if( pH->source() == v2 && pH->target() == v1 )
		{
			return pE;
		}
	}

	//new edge
	CEdge * e = new CEdge;
	assert( e != NULL );
	m_edges.push_back( e );
	ledges.push_back( e );


	return e;

};



//access vertex->edge
/*!
Access an edge by its two end vertices
\param v0 one vertex of the edge
\param v1 the other vertex of the edge
\return the edge connecting both v0 and v1, NULL if no such edge exists.
*/
//use the edge list associated with each vertex to locate the edge

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexEdge( tVertex  v0, tVertex  v1 )
{
	CVertex * pV = (v0->id() < v1->id() )? v0: v1;
	std::list<CEdge*> & ledges = vertexEdges( pV );

	for( typename std::list<CEdge*>::iterator eiter = ledges.begin(); eiter != ledges.end(); eiter ++ )
	{
		CEdge * pE = *eiter;
		CHalfEdge * pH =  edgeHalfedge(pE,0);
		if( pH->source() == v0 && pH->target() == v1 ) return pE;
		if( pH->source() == v1 && pH->target() == v0 ) return pE;
	}
	return NULL;
};

/*!
Access a halfedge by its two end vertices
\param v0 one vertex of the halfedge
\param v1 the other vertex of the halfedge
\return the halfedge connecting both v0 and v1, NULL if no such edge exists.
*/

//access vertex->halfedge
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexHalfedge( tVertex  v0, tVertex  v1 )
{
	CEdge * e = vertexEdge( v0, v1 );
	assert( e != NULL );
	CHalfEdge * he = (CHalfEdge*) e->halfedge(0);
	if( he->vertex() == v1 && he->he_prev()->vertex() == v0 ) return he;
	he = (CHalfEdge*) e->halfedge(1);
	assert( he->vertex() == v1 && he->he_prev()->vertex() == v0 );
	return he;
};


/*!
Access the edge list of a vertex, {e} such that e->vertex1() == v
\param v vertex
\return the list of adjacent edges
*/

//access vertex->edges
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline std::list<CEdge*> & CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexEdges( tVertex  v0 )
{
	return (std::list<CEdge*> &)v0->edges();
};

//access vertex->halfedge
/*!
	The halfedge targeting at a vertex. 
	\param v the input vertex.
	\return the halfedge targeting at v, which is the most ccw in halfedge of v.
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
inline CHalfEdge * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::vertexHalfedge( tVertex  v  )
{
	return (CHalfEdge*) v->halfedge();
};

/*!
	Read an .m file.
	\param input the input obj file name
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::read_m( const char * input )
{
	std::fstream is( input, std::fstream::in );

	if( is.fail() )
	{
		fprintf(stderr,"Error in opening file %s\n", input );
		return;
	}

	char buffer[MAX_LINE];
	int id;

	while( is.getline(buffer, MAX_LINE )  )
	{		
	
		std::string line( buffer );
		line = strutil::trim( line );

		strutil::Tokenizer stokenizer( line, " \r\n" );

		stokenizer.nextToken();
		std::string token = stokenizer.getToken();
	
		if( token == "Vertex"  ) 
		{
			stokenizer.nextToken();
			token = stokenizer.getToken();
			id = strutil::parseString<int>(token);

			CPoint p;
			for( int i = 0 ; i < 3; i ++ )
			{
				stokenizer.nextToken();
				token = stokenizer.getToken();
				p[i] = strutil::parseString<float>(token);
			}
		
			tVertex v  = createVertex( id );
			v->point() = p;
			v->id()    = id;

			if( ! stokenizer.nextToken("\t\r\n") ) continue;
			token = stokenizer.getToken();

			int sp = (int) token.find("{");
			int ep = (int) token.find("}");

			if( sp >= 0 && ep >= 0 )
			{
				v->string() = token.substr( sp+1, ep-sp-1 );
			}
			continue;
		}
		

		if( token == "Face" ) 
		{

			stokenizer.nextToken();
			token = stokenizer.getToken();
			id = strutil::parseString<int>(token);
	
			std::vector<CVertex*> v;
			while( stokenizer.nextToken() )
			{
				token = stokenizer.getToken();
				if( strutil::startsWith( token, "{" ) ) break;
				int vid = strutil::parseString<int>(token);
				v.push_back( idVertex( vid ) );
			}

			tFace f = createFace( v, id );

			if( strutil::startsWith( token, "{" ) )
			{
				f->string() = strutil::trim( token, "{}" );
			}
			continue;
		}

		//read in edge attributes
		if( token == "Edge" )
		{
			stokenizer.nextToken();
			token = stokenizer.getToken();
			int id0 = strutil::parseString<int>( token );

			stokenizer.nextToken();
			token = stokenizer.getToken();
			int id1 = strutil::parseString<int>( token );


			CVertex * v0 = idVertex( id0 );
			CVertex * v1 = idVertex( id1 );

			tEdge edge = vertexEdge( v0, v1 );

			if( !stokenizer.nextToken("\t\r\n") ) continue;
			token = stokenizer.getToken();	
			
			int sp = (int) token.find("{");
			int ep = (int) token.find("}");

			if( sp >= 0 && ep >= 0 )
			{
				  edge->string() = token.substr( sp+1, ep-sp-1 );
			}
			continue;
		}

		//read in edge attributes
		if( token == "Corner" ) 
		{
			stokenizer.nextToken();
			token = stokenizer.getToken();
			int vid = strutil::parseString<int>( token );

			stokenizer.nextToken();
			token = stokenizer.getToken();
			int fid = strutil::parseString<int>( token );


			CVertex * v = idVertex( vid );
			CFace   * f = idFace( fid );
			tHalfEdge he = corner( v, f );


			if( !stokenizer.nextToken("\t\r\n") ) continue;
			token = stokenizer.getToken();	

			int sp = (int) token.find("{");
			int ep = (int) token.find("}");

			if( sp >= 0 && ep >= 0 )
			{
				he->string() = token.substr( sp+1, ep-sp-1 );
			}
			continue;
		}
	}
	
	//labelBoundary();

	//Label boundary edges
	for(typename std::list<CEdge*>::iterator eiter= m_edges.begin() ; eiter != m_edges.end() ; ++ eiter )
	{
		CEdge *     edge = *eiter;
		CHalfEdge * he[2];

		he[0] = edgeHalfedge( edge, 0 );
		he[1] = edgeHalfedge( edge, 1 );
		
		assert( he[0] != NULL );
		

		if( he[1] != NULL )
		{
			assert( he[0]->target() == he[1]->source() && he[0]->source() == he[1]->target() );

			if( he[0]->target()->id() < he[0]->source()->id() )
			{
				edge->halfedge(0 ) = he[1];
				edge->halfedge(1 ) = he[0];
			}

			assert( edgeVertex1(edge)->id() < edgeVertex2(edge)->id() );
		}
		else
		{
			he[0]->vertex()->boundary() = true;
			he[0]->he_prev()->vertex()->boundary()  = true;
		}

	}

	std::list<CVertex*> dangling_verts;
	//Label boundary edges
	for(typename std::list<CVertex*>::iterator viter = m_verts.begin();  viter != m_verts.end() ; ++ viter )
	{
		CVertex *     v = *viter;
		if( v->halfedge() != NULL ) continue;
		dangling_verts.push_back( v );
	}

	for( typename std::list<CVertex*>::iterator  viter = dangling_verts.begin() ; viter != dangling_verts.end(); ++ viter )
	{
		CVertex * v = *viter;
		m_verts.remove( v );
		delete v;
		v = NULL;
	}

	//Arrange the boundary half_edge of boundary vertices, to make its halfedge
	//to be the most ccw in half_edge

	for(typename std::list<CVertex*>::iterator viter = m_verts.begin();  viter != m_verts.end() ; ++ viter )
	{
		CVertex *     v = *viter;
		if( !v->boundary() ) continue;

		CHalfEdge * he = vertexMostCcwInHalfEdge( v );
		while( he->he_sym() != NULL )
		{
			he =  vertexNextCcwInHalfEdge ( he );
		}
		v->halfedge() = he;
	}

	//read in the traits

	for(typename std::list<CVertex*>::iterator viter = m_verts.begin();  viter != m_verts.end() ; ++ viter )
	{
		CVertex *     v = *viter;
		v->_from_string();
	}

	for(typename std::list<CEdge*>::iterator eiter = m_edges.begin();  eiter != m_edges.end() ; ++ eiter )
	{
		CEdge *     e = *eiter;
		e->_from_string();
	}

	for(typename std::list<CFace*>::iterator fiter = m_faces.begin();  fiter != m_faces.end() ; ++ fiter )
	{
		CFace *     f = *fiter;
		f->_from_string();
	}

	for( typename std::list<CFace*>::iterator fiter=m_faces.begin(); fiter != m_faces.end(); fiter ++ )
	{
		CFace * pF = *fiter;

		CHalfEdge * pH  = faceMostCcwHalfEdge( pF );
		do{
			pH->_from_string();
			pH = faceNextCcwHalfEdge( pH );
		}while( pH != faceMostCcwHalfEdge(pF ) );
	}

};

/*!
	Write an .m file.
	\param output the output .m file name
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::write_m( const char * output )
{
	//write traits to string
	for( typename std::list<CVertex*>::iterator viter=m_verts.begin(); viter != m_verts.end(); viter ++ )
	{
		CVertex * pV = *viter;
		pV->_to_string();
	}

	for( typename std::list<CEdge*>::iterator eiter=m_edges.begin(); eiter != m_edges.end(); eiter ++ )
	{
		CEdge * pE = *eiter;
		pE->_to_string();
	}

	for( typename std::list<CFace*>::iterator fiter=m_faces.begin(); fiter != m_faces.end(); fiter ++ )
	{
		CFace * pF = *fiter;
		pF->_to_string();
	}

	for( typename std::list<CFace*>::iterator fiter=m_faces.begin(); fiter != m_faces.end(); fiter ++ )
	{
		CFace * pF = *fiter;
		CHalfEdge * pH  = faceMostCcwHalfEdge( pF );
		do{
			pH->_to_string();
			pH = faceNextCcwHalfEdge( pH );
		}while( pH != faceMostCcwHalfEdge(pF ) );
	}


	std::fstream _os( output, std::fstream::out );
	if( _os.fail() )
	{
		fprintf(stderr,"Error is opening file %s\n", output );
		return;
	}


	//remove vertices
  for( typename std::list<CVertex*>::iterator viter = m_verts.begin(); viter != m_verts.end(); viter ++)
  {
		tVertex v = *viter;

		_os << "Vertex " << v->id();
		
		for( int i = 0; i < 3; i ++ )
		{
			_os << " " << v->point()[i];
		}
		if( v->string().size() > 0 )
		{
			_os << " " <<"{"<< v->string() << "}";
		}
		_os << std::endl;
	}

  for( typename std::list<CFace*>::iterator fiter = m_faces.begin(); fiter != m_faces.end(); fiter ++ )
	{
		tFace f = *fiter;

		_os << "Face " << f->id();
		tHalfEdge he = faceHalfedge( f );
		do{
			_os << " " <<  he->target()->id();
			he = halfedgeNext( he );
		}while( he != f->halfedge() );

		if( f->string().size() > 0 )
		{
			_os << " " << "{"<< f->string() << "}";
		}
		_os << std::endl;
	}

  for( typename std::list<CEdge*>::iterator eiter = m_edges.begin(); eiter != m_edges.end(); eiter ++ )
	{
		tEdge e = *eiter;
		if( e->string().size() > 0 )
		{
			_os << "Edge "<<  edgeVertex1(e)->id() <<" " << edgeVertex2(e)->id() << " ";
			_os << "{" << e->string() << "}" << std::endl;
		}
	}

  for( typename std::list<CFace*>::iterator fiter = m_faces.begin(); fiter != m_faces.end(); fiter ++  )
	{
		tFace f = *fiter;

		tHalfEdge he = faceHalfedge( f );

    do{
  			if( he->string().size() > 0 )
			  {
				  _os << "Corner "<< he->vertex()->id() << " " << f->id() << " ";
				  _os << "{" << he->string() << "}" << std::endl;
			  }
			  he = halfedgeNext( he );
		}while( he != f->halfedge() );

  }

	_os.close();
};


//assume the mesh is with uv coordinates and normal vector for each vertex
/*!
	Write an .obj file.
	\param output the output .obj file name
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::write_obj( const char * output )
{
	std::fstream _os( output, std::fstream::out );
	if( _os.fail() )
	{
		fprintf(stderr,"Error is opening file %s\n", output );
		return;
	}

	int vid = 1;
	for( typename std::list<CVertex*>::iterator viter = m_verts.begin(); viter != m_verts.end(); viter ++)
	{
		tVertex v = *viter;
		v->id() = vid ++;
	}

	for( typename std::list<CVertex*>::iterator viter = m_verts.begin(); viter != m_verts.end(); viter ++)
	{
		tVertex v = *viter;

		_os << "v";
		
		for( int i = 0; i < 3; i ++ )
		{
			_os << " " << v->point()[i];
		}
		_os << std::endl;
	}

	for( typename std::list<CVertex*>::iterator viter = m_verts.begin(); viter != m_verts.end(); viter ++)
	{
		tVertex v = *viter;

		_os << "vt";
		
		for( int i = 0; i < 2; i ++ )
		{
			_os << " " << v->uv()[i];
		}
		_os << std::endl;
	}

	for( typename std::list<CVertex*>::iterator viter = m_verts.begin(); viter != m_verts.end(); viter ++)
	{
		tVertex v = *viter;

		_os << "vn";
		
		for( int i = 0; i < 3; i ++ )
		{
			_os << " " << v->normal()[i];
		}
		_os << std::endl;
	}


  for( typename std::list<CFace*>::iterator fiter = m_faces.begin(); fiter != m_faces.end(); fiter ++ )
	{
		tFace f = *fiter;

		_os << "f";

		tHalfEdge he = faceHalfedge( f );
		
		do{
			int vid = he->target()->id();
			_os << " " <<  vid << "/" << vid << "/" << vid;
			he = halfedgeNext( he );
		}while( he != f->halfedge() );
		_os << std::endl;
	}

	_os.close();
};

/*!
	Write an .off file.
	\param output the output .off file name
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::write_off( const char * output )
{
	std::fstream _os( output, std::fstream::out );
	if( _os.fail() )
	{
		fprintf(stderr,"Error is opening file %s\n", output );
		return;
	}

	_os << "OFF" << std::endl;
	_os << m_verts.size() << " " << m_faces.size() << " " << m_edges.size() << std::endl;


	int vid = 0;
	for( typename std::list<CVertex*>::iterator viter = m_verts.begin(); viter != m_verts.end(); viter ++)
	{
		tVertex v = *viter;
		v->id() = vid ++;
	}

	for( typename std::list<CVertex*>::iterator viter = m_verts.begin(); viter != m_verts.end(); viter ++)
	{
		tVertex v = *viter;
		_os << v->point()[0]  << " " << v->point()[1] << " " << v->point()[2]<< std::endl;
		//_os << v->normal()[0] << " " << v->normal()[1]<< " " << v->normal()[2]<< std::endl;
	}


	for( typename std::list<CFace*>::iterator fiter = m_faces.begin(); fiter != m_faces.end(); fiter ++ )
	{
		tFace f = *fiter;

		_os << "3";

		tHalfEdge he = faceHalfedge( f );
		
		do{
			int vid = he->target()->id();
			_os << " " <<  vid;
			he = halfedgeNext( he );
		}while( he != f->halfedge() );
		_os << std::endl;
	}

	_os.close();
};


//template pointer converting to base class pointer is OK (BasePointer) = (TemplatePointer)
//(TemplatePointer)=(BasePointer) is incorrect
/*! delete one face
\param pFace the face to be deleted
*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::deleteFace( tFace  pFace )
{  	  
	  typename std::map<int,tFace>::iterator fiter = m_map_face.find( pFace->id() );
	  if( fiter != m_map_face.end() )
	  {
		  m_map_face.erase( fiter );
	  }	
	  m_faces.remove( pFace );

		
	 //create halfedges
	 tHalfEdge hes[3];

	 hes[0] = faceHalfedge( pFace );
	 hes[1] = faceNextCcwHalfEdge( hes[0] );
	 hes[2] = faceNextCcwHalfEdge( hes[1] );

	 for(int i = 0; i < 3; i ++ )
	 {
		//connection with edge
		CHalfEdge * pH = hes[i];

		//connection to target
		CVertex * pV = halfedgeTarget( pH );
		if( pV->halfedge() == pH )
		{
			if( pH->he_next()->he_sym() != NULL )
				pV->halfedge() = pH->he_next()->he_sym();
			else
			{
				assert( pH->he_sym() != NULL ); //otherwise the mesh is not a manifold
				pV->halfedge() = pH->he_sym()->he_prev();
			}
		}
	 }

		for(int i = 0; i < 3; i ++ )
		{
			//connection with edge
			CHalfEdge * pH = hes[i];
			CHalfEdge * pS = halfedgeSym( pH );
			CEdge * pE = halfedgeEdge( pH );

			pE->halfedge(0) = pS;
			pE->halfedge(1) = NULL;

			if( pS == NULL )
			{
				//assert(0);
				m_edges.remove( pE );
				CVertex * v0 = halfedgeSource( pH );
				CVertex * v1 = halfedgeTarget( pH );
				delete pE;
			}

			
		}
		
		//remove half edges
		for(int i = 0; i < 3; i ++ )
		{
			delete hes[i];
		}
		
		delete pFace;
};

/*!
	Read an .off file
	\param input the input .off filename
	*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::read_off( const char * input )
{
	std::fstream is( input, std::fstream::in );

	if( is.fail() )
	{
		fprintf(stderr,"Error is opening file %s\n", input );
		return;
	}

	char buffer[MAX_LINE];

	//read in the first line "OFF"

	while( is.getline(buffer, MAX_LINE )  )
	{		
		std::string line( buffer );
	
		strutil::Tokenizer stokenizer( line, " \r\n" );

		stokenizer.nextToken();
		std::string token = stokenizer.getToken();
		if( token == "OFF"  || token == "NOFF" ) break;
	}

	int nVertices, nFaces, nEdges;

	//read in Vertex Number, Face Number, Edge Number

		is.getline(buffer, MAX_LINE );
		std::string line( buffer );
	
		strutil::Tokenizer stokenizer( line, " \r\n" );

		stokenizer.nextToken();
		std::string token = stokenizer.getToken();
		nVertices = strutil::parseString<int>( token );

		stokenizer.nextToken();
		token = stokenizer.getToken();
		nFaces = strutil::parseString<int>( token );

		stokenizer.nextToken();
		token = stokenizer.getToken();
		nEdges = strutil::parseString<int>( token );

		//printf("V %d F %d E %d\n" , nVertices, nFaces, nEdges);
	

	for( int id = 0; id < nVertices; id ++ )
	{
		is.getline(buffer, MAX_LINE );
		std::string line( buffer );
		
		strutil::Tokenizer stokenizer( line, " \r\n" );
		CPoint p;
		for( int j = 0; j < 3; j ++ )
		{
			stokenizer.nextToken();
			std::string token = stokenizer.getToken();
			p[j] = strutil::parseString<float>( token );
		}

			CVertex * v = createVertex( id + 1 );
			v->point() = p;
	}


	for( int id = 0; id < nFaces; id ++ )
	{

		is.getline(buffer, MAX_LINE );
		std::string line( buffer );
		
		strutil::Tokenizer stokenizer( line, " \r\n" );
		stokenizer.nextToken();
		std::string token = stokenizer.getToken();
		
		int n = strutil::parseString<int>(token);
		assert( n == 3 );

		CVertex * v[3];
		for( int j = 0; j < 3; j ++ )
		{
			stokenizer.nextToken();
			std::string token = stokenizer.getToken();
			int vid = strutil::parseString<int>( token );
			v[j] = idVertex( vid + 1);
		}
		
		createFace( v, id + 1 );
	}

	is.close();

	labelBoundary();

};


/*!
	Label boundary edges, vertices
*/
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
void CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::labelBoundary( void )
{
	
	//Label boundary edges
	for(typename std::list<CEdge*>::iterator eiter= m_edges.begin() ; eiter != m_edges.end() ; ++ eiter )
	{
		CEdge *     edge = *eiter;
		CHalfEdge * he[2];

		he[0] = (CHalfEdge*)edge->halfedge(0);
		he[1] = (CHalfEdge*)edge->halfedge(1);
		
		assert( he[0] != NULL );
		

		if( he[1] != NULL )
		{
			assert( he[0]->target() == he[1]->source() && he[0]->source() == he[1]->target() );

			if( he[0]->target()->id() < he[0]->source()->id() )
			{
				edge->halfedge(0 ) = he[1];
				edge->halfedge(1 ) = he[0];
			}

			assert( edgeVertex1(edge)->id() < edgeVertex2(edge)->id() );
		}
		else
		{
			he[0]->vertex()->boundary() = true;
			he[0]->he_prev()->vertex()->boundary()  = true;
		}

	}

	std::list<CVertex*> dangling_verts;
	//Label boundary edges
	for(typename std::list<CVertex*>::iterator viter = m_verts.begin();  viter != m_verts.end() ; ++ viter )
	{
		tVertex     v = *viter;
		if( v->halfedge() != NULL ) continue;
		dangling_verts.push_back( v );
	}

	for( typename std::list<CVertex*>::iterator  viter = dangling_verts.begin() ; viter != dangling_verts.end(); ++ viter )
	{
		tVertex v = *viter;
		m_verts.remove( v );
		delete v;
		v = NULL;
	}

	//Arrange the boundary half_edge of boundary vertices, to make its halfedge
	//to be the most ccw in half_edge

	for(typename std::list<CVertex*>::iterator viter = m_verts.begin();  viter != m_verts.end() ; ++ viter )
	{
		tVertex     v = *viter;
		if( !v->boundary() ) continue;

		CHalfEdge * he = (CHalfEdge*)v->halfedge();
		while( he->he_sym() != NULL )
		{
			he = (CHalfEdge*)he->ccw_rotate_about_target();
		}
		v->halfedge() = he;
	}


};

/*! Create a face
	\param v an array of vertices
	\param id face id
	\return pointer to the new face
	*/

template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
CFace * CBaseMesh<CVertex,CEdge,CFace,CHalfEdge>::createFace( std::vector<tVertex> &  v, int id )
{
	  CFace * f = new CFace();
	  assert( f != NULL );
	  f->id() = id;
	  m_faces.push_back( f );
	  m_map_face.insert( std::pair<int,tFace>(id,f) );

		//create halfedges
	  std::vector<tHalfEdge> hes;

		for(size_t i = 0; i < v.size(); i ++ )
		{
			tHalfEdge pH = new CHalfEdge;
			assert( pH );
			CVertex * vert =  v[i];
			pH->vertex() = vert;
			vert->halfedge() = pH;
			hes.push_back( pH );
		}

		//linking to each other
		for( size_t i = 0; i < hes.size(); i ++ )
		{
			hes[i]->he_next() = hes[(i+1)%hes.size()];
			hes[i]->he_prev() = hes[(i+hes.size()-1)%hes.size()];
		}

		//linking to face
		for(size_t i = 0; i < hes.size(); i ++ )
		{
			hes[i]->face()   = f;
			f->halfedge()    = hes[i];
		}

		//connecting with edge
		for( size_t i = 0; i < hes.size(); i ++ )
		{
			tEdge e = createEdge( v[i], v[(i+hes.size()-1)%hes.size()] );
			if( e->halfedge(0)  == NULL )
			{
				e->halfedge(0) = hes[i];
			}
			else
			{
				assert( e->halfedge(1) == NULL );
				if( e->halfedge(1) != NULL )
				{
					std::cout << "Illegal Face Construction " << id << std::endl;
				}
				e->halfedge(1) = hes[i];
			}
			hes[i]->edge() = e;
		}

		return f;
};


}//name space MeshLib

#endif //_MESHLIB_BASE_MESH_H_ defined
