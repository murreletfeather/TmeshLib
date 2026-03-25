/*!
*      \file Iterators.h
*      \brief 网格迭代器，遍历网格中不同几何元素
*	   \author David Gu
*      \date 10/07/2010
*      \details 提供各种迭代器，方便按顺序遍历网格中元素：比如遍历顶点邻接元素、面上的半边/顶点/边，遍历整个网格所有顶点/边/面/半边
*/

#ifndef  _ITERATORS_H_
#define  _ITERATORS_H_

#include <list>
#include <cassert>
#include "BaseMesh.h"

namespace MeshLib{

/*!
 * \class VertexOutHalfedgeIterator
 * \brief 顶点出半边迭代器，按逆时针(CCW)顺序遍历顶点所有出半边
 * 
 * 从最顺时针(CLW)半边开始，一步步逆时针旋转，遍历顶点所有 outgoing 半边
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class VertexOutHalfedgeIterator
{
public:
    /*!
     * @brief 构造函数
     * @param pMesh 网格指针
     * @param v 目标顶点指针，要遍历它的所有出半边
     */
	VertexOutHalfedgeIterator( CBaseMesh<CVertex, CEdge, CFace, CHalfEdge> *  pMesh, CVertex *  v )
	{ 
        m_pMesh = pMesh; 
        m_vertex = v; 
        m_halfedge = m_pMesh->vertexMostClwOutHalfEdge(v); 
	};

    /*! @brief 析构函数 */
	~VertexOutHalfedgeIterator(){};
	
    /*!
     * @brief 前缀++，跳到下一个逆时针出半边
     */
	void operator++() //前缀形式
	{
        assert( m_halfedge != NULL ); 
	    if( m_halfedge == m_pMesh->vertexMostCcwOutHalfEdge(m_vertex) ) 
		     m_halfedge = NULL;
	    else
	 	     m_halfedge = m_pMesh->vertexNextCcwOutHalfEdge(m_halfedge); 
	};

    /*!
     * @brief 后缀++，跳到下一个逆时针出半边
     */
	void operator++(int) //后缀形式
	{
        assert( m_halfedge != NULL ); 
	    if( m_halfedge == m_pMesh->vertexMostCcwOutHalfEdge(m_vertex) ) 
		     m_halfedge = NULL;
	    else
	 	     m_halfedge = m_pMesh->vertexNextCcwOutHalfEdge(m_halfedge); 
	};

    /*!
     * @brief 获取当前迭代器指向的半边
     * @return 当前半边指针
     */
	 CHalfEdge * value() { return m_halfedge; };
	 
    /*!
     * @brief 判断是否遍历完毕
     * @return true表示已经遍历完所有半边，false表示还有
     */
	 bool end(){ return m_halfedge == NULL; };
	 
    /*!
     * @brief 重载*运算符，获取当前半边，和value()等价
     * @return 当前半边指针
     */
	 CHalfEdge * operator*() { return value(); };

private:
	CBaseMesh<CVertex,CEdge,CFace,CHalfEdge> *        m_pMesh;    //!< 当前网格指针
	CVertex *                                         m_vertex;   //!< 当前目标顶点
	CHalfEdge *                                       m_halfedge; //!< 当前迭代指向的半边
};

/*!
 * \class VertexInHalfedgeIterator
 * \brief 顶点入半边迭代器，按逆时针(CCW)顺序遍历顶点所有入半边
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class VertexInHalfedgeIterator
{
public:
    /*!
     * @brief 构造函数
     * @param pMesh 网格指针
     * @param v 目标顶点指针，要遍历它的所有入半边
     */
	VertexInHalfedgeIterator(CBaseMesh<CVertex, CEdge, CFace, CHalfEdge> *  pMesh, CVertex * v )
	{ 
        m_pMesh = pMesh; 
        m_vertex = v; 
        m_halfedge = m_pMesh->vertexMostClwInHalfEdge(v); 
	};
	
    /*! @brief 析构函数 */
	~VertexInHalfedgeIterator(){};

    /*! @brief 前缀++，跳到下一个逆时针入半边 */
	void operator++()	//前缀形式
	{
        assert( m_halfedge != NULL ); 
	    if( m_halfedge == m_pMesh->vertexMostCcwInHalfEdge(m_vertex) ) 
		     m_halfedge = NULL; 
	    else
		    m_halfedge = m_pMesh->vertexNextCcwInHalfEdge(m_halfedge); 
	};
	
    /*! @brief 后缀++，跳到下一个逆时针入半边 */
	void operator++(int)	//后缀形式
	{
        assert( m_halfedge != NULL ); 
	    if( m_halfedge == m_pMesh->vertexMostCcwInHalfEdge(m_vertex) ) 
		     m_halfedge = NULL; 
	    else
		    m_halfedge = m_pMesh->vertexNextCcwInHalfEdge(m_halfedge); 
	};

    /*! @brief 获取当前半边 */
	CHalfEdge * value() { return m_halfedge; };
	
    /*! @brief 判断是否遍历完毕 */
	bool end(){ return m_halfedge == NULL; };
	
    /*! @brief 重载*运算符获取当前半边 */
	CHalfEdge * operator*() { return value(); };

private:
	CBaseMesh<CVertex, CEdge, CFace, CHalfEdge> *        m_pMesh;    //!< 当前网格指针
	CVertex *                                         m_vertex;   //!< 当前目标顶点
	CHalfEdge *                                       m_halfedge; //!< 当前迭代指向的半边
};

/*!
 * \class VertexVertexIterator
 * \brief 顶点邻接顶点迭代器，按逆时针(CCW)顺序遍历顶点所有邻接顶点（一圈邻居）
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class VertexVertexIterator
{
public:
    /*!
     * @brief 构造函数
     * @param v 目标顶点指针，要遍历它的邻接顶点
     */
	VertexVertexIterator( CVertex *  v )
	{ 
		m_vertex = v; 
		m_halfedge = (CHalfEdge*)m_vertex->most_clw_out_halfedge();
	};

    /*! @brief 析构函数 */
	~VertexVertexIterator(){};

    /*! @brief 前缀++，跳到下一个逆时针邻接顶点 */
	void operator++() //前缀形式
	{
		assert( m_halfedge != NULL ); 
		
		if( !m_vertex->boundary() ) // 如果顶点不在边界上（内部顶点）
		{
			if( m_halfedge != m_vertex->most_ccw_out_halfedge() )
			{
				m_halfedge = (CHalfEdge*)m_halfedge->ccw_rotate_about_source();
			}
			else
			{
				m_halfedge = NULL;
			}
			return;
		}

		// 如果顶点在边界上，边界顶点需要特殊处理
		if( m_vertex->boundary() )
		{
			if( m_halfedge == (CHalfEdge*)m_vertex->most_ccw_in_halfedge() )
			{
				m_halfedge = NULL;
				return;
			}

			CHalfEdge * he = (CHalfEdge*)m_halfedge->ccw_rotate_about_source();

			if( he == NULL )
			{
				m_halfedge = (CHalfEdge*)m_vertex->most_ccw_in_halfedge();
			}
			else
			{
				m_halfedge = he;
			}
		}

		return;
	};


    /*! @brief 后缀++，跳到下一个逆时针邻接顶点 */
	void operator++(int) //后缀形式
	{
		assert( m_halfedge != NULL ); 
		
		if( !m_vertex->boundary() )
		{
			if( m_halfedge != (CHalfEdge*)m_vertex->most_ccw_out_halfedge() )
			{
				m_halfedge = (CHalfEdge*)m_halfedge->ccw_rotate_about_source();
			}
			else
			{
				m_halfedge = NULL;
			}
			return;
		}

		if( m_vertex->boundary() )
		{
			if( m_halfedge == (CHalfEdge*)m_vertex->most_ccw_in_halfedge() )
			{
				m_halfedge = NULL;
				return;
			}

			CHalfEdge * he = (CHalfEdge*)m_halfedge->ccw_rotate_about_source();

			if( he == NULL )
			{
				m_halfedge = (CHalfEdge*)m_vertex->most_ccw_in_halfedge();
			}
			else
			{
				m_halfedge = he;
			}
		}

		return;
	};

    /*!
     * @brief 获取当前邻接顶点
     * @return 当前相邻顶点指针
     */
	 CVertex * value() 
	 { 
		 if( !m_vertex->boundary() )
		 {
			 return (CVertex*)m_halfedge->target(); 
		 }
		 // 边界顶点特殊处理
		 if( m_halfedge != (CHalfEdge*)m_vertex->most_ccw_in_halfedge() )
		 {
			 return (CVertex*)m_halfedge->target();
		 }
		 if( m_halfedge == (CHalfEdge*)m_vertex->most_ccw_in_halfedge() )
		 {
			 return (CVertex*)m_halfedge->source();
		 }
		 return NULL;
	 };

    /*! @brief 重载*运算符获取当前邻接顶点 */
	 CVertex * operator*() { return value(); };

    /*! @brief 判断遍历是否结束 */
	 bool end(){ return m_halfedge == NULL; };

    /*! @brief 重置迭代器回到起始点 */
	 void reset()	{ m_halfedge = (CHalfEdge*)m_vertex->most_clw_out_halfedge(); };

private:
	CVertex *   m_vertex;      //!< 目标顶点，我们遍历它的邻接点
	CHalfEdge * m_halfedge;    //!< 当前迭代指向的半边
};

/*!
 * \class VertexEdgeIterator
 * \brief 顶点邻接边迭代器，按逆时针(CCW)顺序遍历顶点所有邻接边
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class VertexEdgeIterator
{
public:
    /*!
     * @brief 构造函数
     * @param v 目标顶点指针，遍历它邻接的所有边
     */
	VertexEdgeIterator( CVertex *  v )
	{ 
		m_vertex = v; 
		m_halfedge = (CHalfEdge*)m_vertex->most_clw_out_halfedge();
	};

    /*! @brief 析构函数 */
	~VertexEdgeIterator(){};
	
    /*! @brief 前缀++，跳到下一个逆时针邻接边 */
	void operator++() //前缀形式
	{
		assert( m_halfedge != NULL ); 
		
		if( !m_vertex->boundary() )
		{
			if( m_halfedge != (CHalfEdge*)m_vertex->most_ccw_out_halfedge() )
			{
				m_halfedge = (CHalfEdge*)m_halfedge->ccw_rotate_about_source();
			}
			else
			{
				m_halfedge = NULL;
			}
			return;
		}

		if( m_vertex->boundary() )
		{
			if( m_halfedge == (CHalfEdge*)m_vertex->most_ccw_in_halfedge() )
			{
				m_halfedge = NULL;
				return;
			}

			CHalfEdge * he = (CHalfEdge*)m_halfedge->ccw_rotate_about_source();

			if( he == NULL )
			{
				m_halfedge = (CHalfEdge*)m_vertex->most_ccw_in_halfedge();
			}
			else
			{
				m_halfedge = he;
			}
		}

		return;
	};
	
    /*! @brief 后缀++，跳到下一个逆时针邻接边 */
	void operator++(int) //后缀形式
	{
		assert( m_halfedge != NULL ); 
		
		if( !m_vertex->boundary() )
		{
			if( m_halfedge != (CHalfEdge*)m_vertex->most_ccw_out_halfedge() )
			{
				m_halfedge = (CHalfEdge*)m_halfedge->ccw_rotate_about_source();
			}
			else
			{
				m_halfedge = NULL;
			}
			return;
		}

		if( m_vertex->boundary() )
		{
			if( m_halfedge == (CHalfEdge*)m_vertex->most_ccw_in_halfedge() )
			{
				m_halfedge = NULL;
				return;
			}

			CHalfEdge * he = (CHalfEdge*)m_halfedge->ccw_rotate_about_source();

			if( he == NULL )
			{
				m_halfedge = (CHalfEdge*)m_vertex->most_ccw_in_halfedge();
			}
			else
			{
				m_halfedge = he;
			}
		}

		return;
	};
	
    /*! @brief 获取当前边指针 */
	 CEdge * value() 
	 { 
		 assert( m_halfedge != NULL );
		 return (CEdge*)m_halfedge->edge();
	 };

    /*! @brief 重载*运算符获取当前边 */
	 CEdge * operator*() { return value(); };
	 
    /*! @brief 判断遍历是否结束 */
	 bool end(){ return m_halfedge == NULL; };
	 
    /*! @brief 重置迭代器回到起始点 */
	 void reset()	{ m_halfedge = (CHalfEdge*)m_vertex->most_clw_out_halfedge(); };

private:
	CVertex *   m_vertex;   //!< 目标顶点，遍历它的邻接边
	CHalfEdge * m_halfedge; //!< 当前迭代指向的半边
};

/*!
 * \class VertexFaceIterator
 * \brief 顶点邻接面迭代器，按逆时针(CCW)顺序遍历顶点所有邻接面
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class VertexFaceIterator
{
public:
    /*!
     * @brief 构造函数
     * @param v 目标顶点指针，遍历它所有邻接面
     */
	VertexFaceIterator( CVertex * & v )
	{ 
		m_vertex = v; 
		m_halfedge = (CHalfEdge*)m_vertex->most_clw_out_halfedge(); 
	};
	
    /*! @brief 析构函数 */
	~VertexFaceIterator(){};
	
    /*! @brief 前缀++，跳到下一个逆时针邻接面 */
	void operator++() //前缀形式
	{
		assert( m_halfedge != NULL );  

		if( m_halfedge == (CHalfEdge*)m_vertex->most_ccw_out_halfedge() ) 
		{
			m_halfedge = NULL;
			return;
		}
		m_halfedge = (CHalfEdge*)m_halfedge->ccw_rotate_about_source();
	};
	
    /*! @brief 后缀++，跳到下一个逆时针邻接面 */
	void operator++(int) //后缀形式
	{
		assert( m_halfedge != NULL );  

		if( m_halfedge == (CHalfEdge*)m_vertex->most_ccw_out_halfedge() ) 
		{
			m_halfedge = NULL;
			return;
		}
		m_halfedge = (CHalfEdge*)m_halfedge->ccw_rotate_about_source();
	};
	
    /*! @brief 获取当前邻接面 */
	CFace * value() { return (CFace*) m_halfedge->face(); };
	
    /*! @brief 重载*运算符获取当前邻接面 */
	 CFace * operator*() { return value(); };
	 
    /*! @brief 判断遍历是否结束 */
	 bool end(){ return m_halfedge == NULL; };
	 
    /*! @brief 重置迭代器回到起始位置 */
	 void reset()	{ m_halfedge = (CHalfEdge*)m_vertex->most_clw_out_halfedge(); };

private:
	CVertex *   m_vertex;   //!< 目标顶点，遍历它的邻接面
	CHalfEdge * m_halfedge; //!< 当前迭代指向的半边
};

/*!
 * \class FaceHalfedgeIterator
 * \brief 面半边迭代器，按逆时针(CCW)顺序遍历面边界所有半边
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class FaceHalfedgeIterator
{
public:
    /*!
     * @brief 构造函数
     * @param f 目标面对象指针，遍历它边界上所有半边
     */
	FaceHalfedgeIterator( CFace * f )
	{ 
		m_face = f; 
		m_halfedge = (CHalfEdge*)f->halfedge(); 
	};
	
    /*! @brief 析构函数 */
	~FaceHalfedgeIterator(){};
	
    /*! @brief 前缀++，跳到下一个逆时针半边 */
	void operator++() //前缀形式
	{
		assert( m_halfedge != NULL );
		m_halfedge = (CHalfEdge*)m_halfedge->he_next();

		if( m_halfedge == m_face->halfedge() )
		{
			 m_halfedge = NULL;
			return;
		};
	}

    /*! @brief 后缀++，跳到下一个逆时针半边 */
	void operator++(int) //后缀形式
	{
		assert( m_halfedge != NULL );
		m_halfedge = (CHalfEdge*)m_halfedge->he_next();

		if( m_halfedge == m_face->halfedge() )
		{
			 m_halfedge = NULL;
			return;
		};
	}

    /*! @brief 获取当前半边指针 */
	CHalfEdge * value() { return m_halfedge; };
	
    /*! @brief 重载*运算符获取当前半边 */
	CHalfEdge * operator*() { return value(); };

    /*! @brief 判断是否遍历完毕 */
	bool end(){ return m_halfedge == NULL; };

private:
	CFace *        m_face;     //!< 目标面，遍历它的边界半边
	CHalfEdge *    m_halfedge; //!< 当前迭代指向的半边
};


/*!
 * \class FaceEdgeIterator
 * \brief 面边迭代器，按逆时针(CCW)顺序遍历面边界所有边
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class FaceEdgeIterator
{
public:
    /*!
     * @brief 构造函数
     * @param f 目标面对象指针，遍历它边界上所有边
     */
	FaceEdgeIterator( CFace * f )
	{ 
		m_face = f; 
		m_halfedge = (CHalfEdge*)f->halfedge(); 
	};

    /*! @brief 析构函数 */
	~FaceEdgeIterator(){};
	
    /*! @brief 前缀++，跳到下一个逆时针边 */
	void operator++()	//前缀形式
	{
		assert( m_halfedge != NULL );
		m_halfedge = (CHalfEdge*)m_halfedge->he_next();

		if( m_halfedge == (CHalfEdge*)m_face->halfedge() )
		{
			 m_halfedge = NULL;
			return;
		};
	}

    /*! @brief 后缀++，跳到下一个逆时针边 */
	void operator++(int)	//后缀形式
	{
		assert( m_halfedge != NULL );
		m_halfedge = (CHalfEdge*)m_halfedge->he_next();

		if( m_halfedge == m_face->halfedge() )
		{
			 m_halfedge = NULL;
			return;
		};
	}
	
    /*! @brief 获取当前边指针 */
	CEdge * value() { return (CEdge*) m_halfedge->edge(); };
	
    /*! @brief 重载*运算符获取当前边 */
	CEdge * operator*() { return value(); };
	
    /*! @brief 判断是否遍历完毕 */
	bool end(){ return m_halfedge == NULL; };

private:
	CFace  *       m_face;     //!< 目标面，遍历它的边界边
	CHalfEdge *    m_halfedge; //!< 当前迭代指向的半边
};


/*!
 * \class FaceVertexIterator
 * \brief 面顶点迭代器，按逆时针(CCW)顺序遍历面边界所有顶点
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class FaceVertexIterator
{
public:
    /*!
     * @brief 构造函数
     * @param f 目标面对象指针，遍历它边界上所有顶点
     */
	FaceVertexIterator( CFace * f )
	{ 
		m_face = f; 
		m_halfedge = (CHalfEdge*)f->halfedge(); 
	};
	
    /*! @brief 析构函数 */
	~FaceVertexIterator(){};
	
    /*! @brief 前缀++，跳到下一个逆时针顶点 */
	void operator++() //前缀形式
	{
		assert( m_halfedge != NULL );
		m_halfedge = (CHalfEdge*)m_halfedge->he_next();

		if( m_halfedge == (CHalfEdge*)m_face->halfedge() )
		{
			 m_halfedge = NULL;
			return;
		};
	}

    /*! @brief 后缀++，跳到下一个逆时针顶点 */
	void operator++(int) //后缀形式
	{
		assert( m_halfedge != NULL );
		m_halfedge = (CHalfEdge*)m_halfedge->he_next();

		if( m_halfedge == (CHalfEdge*)m_face->halfedge() )
		{
			 m_halfedge = NULL;
			return;
		};
	}
	
    /*! @brief 获取当前顶点指针 */
	CVertex * value() { return (CVertex*) m_halfedge->target(); };
	
    /*! @brief 重载*运算符获取当前顶点 */
	CVertex * operator*() { return value(); };
	
    /*! @brief 判断是否遍历完毕 */
	bool end(){ return m_halfedge == NULL; };

private:
	CFace         * m_face;     //!< 目标面，遍历它的边界顶点
	CHalfEdge *    m_halfedge; //!< 当前迭代指向的半边
};

/*!
 * \class MeshVertexIterator
 * \brief 网格顶点迭代器，遍历整个网格所有顶点
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class MeshVertexIterator
{
public:
    /*!
     * @brief 构造函数
     * @param pMesh 目标网格指针，遍历它所有顶点
     */
	MeshVertexIterator( CBaseMesh<CVertex,CEdge,CFace,CHalfEdge> * pMesh )
	{
		m_pMesh = pMesh;
		m_iter = m_pMesh->vertices().begin();
	}
	
    /*! @brief 获取当前顶点 */
	CVertex * value() { return *m_iter; };
	
    /*! @brief 重载*运算符获取当前顶点 */
	CVertex * operator*(){ return value(); };
	
    /*! @brief 前缀++，跳到下一个顶点 */	
	void operator++()	 { ++ m_iter; }; //前缀形式
	
    /*! @brief 后缀++，跳到下一个顶点 */
	void operator++(int) { ++ m_iter; }; //后缀形式
	
    /*! @brief 判断是否遍历完所有顶点 */
	bool end() { return m_iter == m_pMesh->vertices().end(); }
	
private:
	CBaseMesh<CVertex,CEdge,CFace,CHalfEdge> *        m_pMesh; //!< 目标网格，遍历它的所有顶点
	typename std::list<CVertex*>::iterator             m_iter;  //!< std::list迭代器，封装内部遍历
};

/*!
 * \class MeshFaceIterator
 * \brief 网格面对迭代器，遍历整个网格所有面
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class MeshFaceIterator
{
public:
    /*!
     * @brief 构造函数
     * @param pMesh 目标网格指针，遍历它所有面
     */
	MeshFaceIterator( CBaseMesh<CVertex,CEdge,CFace,CHalfEdge> * pMesh )
	{
        m_pMesh = pMesh;
        m_iter = pMesh->faces().begin();
	}
	
    /*! @brief 获取当前面 */
	CFace * value() { return *m_iter; };
	
    /*! @brief 重载*运算符获取当前面 */
	CFace * operator*(){ return value(); };

    /*! @brief 前缀++，跳到下一个面 */
	void operator++() { ++ m_iter; }; //前缀形式
	
    /*! @brief 后缀++，跳到下一个面 */
	void operator++(int) { ++ m_iter; }; //后缀形式
	
    /*! @brief 判断是否遍历完所有面 */
	bool end() { return m_iter == m_pMesh->faces().end(); }

private:
	CBaseMesh<CVertex,CEdge,CFace,CHalfEdge> *        m_pMesh; //!< 目标网格，遍历它的所有面
	typename std::list<CFace*>::iterator               m_iter;  //!< std::list迭代器，封装内部遍历
};

/*!
 * \class MeshEdgeIterator
 * \brief 网格边迭代器，遍历整个网格所有边
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class MeshEdgeIterator
{
public:
    /*!
     * @brief 构造函数
     * @param pMesh 目标网格指针，遍历它所有边
     */
	MeshEdgeIterator( CBaseMesh<CVertex,CEdge,CFace,CHalfEdge> * pMesh )
	{
		m_pMesh = pMesh;
		m_iter = m_pMesh->edges().begin();
	}
	
    /*! @brief 获取当前边 */
	CEdge * value() { return *m_iter; };
	
    /*! @brief 重载*运算符获取当前边 */
	CEdge * operator*(){ return value(); };
	
    /*! @brief 前缀++，跳到下一条边 */
	void operator++() { ++ m_iter; }; //前缀形式
	
    /*! @brief 后缀++，跳到下一条边 */
	void operator++(int) {m_iter++; }; //后缀形式
	
    /*! @brief 判断是否遍历完所有边 */
	bool end() { return m_iter == m_pMesh->edges().end(); }

private:
	CBaseMesh<CVertex,CEdge,CFace,CHalfEdge> *        m_pMesh; //!< 目标网格，遍历它的所有边
	typename std::list<CEdge*>::iterator              m_iter;  //!< std::list迭代器，封装内部遍历
};

/*!
 * \class MeshHalfEdgeIterator
 * \brief 网格半边迭代器，遍历整个网格所有半边
 * \note 每条边包含两个半边，所以依次遍历每个边的两个半边
 */
template<typename CVertex, typename CEdge, typename CFace, typename CHalfEdge>
class MeshHalfEdgeIterator
{
public:
    /*!
     * @brief 构造函数
     * @param pMesh 目标网格指针，遍历它所有半边
     */
	MeshHalfEdgeIterator( CBaseMesh<CVertex,CEdge,CFace,CHalfEdge> * pMesh )
	{
        m_pMesh = pMesh;
        m_iter = m_pMesh->edges().begin();
        m_id = 0; // 从每个边的0号半边开始
	}
	
    /*! @brief 获取当前半边 */
	CHalfEdge * value() { 
        CEdge * e = *m_iter; 
        return (CHalfEdge*)e->halfedge(m_id); 
    };
	
    /*! @brief 重载*运算符获取当前半边 */
	CHalfEdge * operator*(){ return value(); };
	
    /*! @brief 前缀++，跳到下一个半边 */
	void operator++() //前缀形式
	{ 
		++m_id;

		switch( m_id )
		{
		case 1:
			{
				CEdge * e = *m_iter;
				if( e->halfedge(m_id) == NULL )
				{
					m_id = 0;
					++ m_iter;
				}
			}
			break;
		case 2:
			m_id = 0;
			++m_iter;
			break;
		}
	};
	
    /*! @brief 后缀++，跳到下一个半边 */
	void operator++(int) //后缀形式
	{ 
		++m_id;

		switch( m_id )
		{
		case 1:
			{
				CEdge * e = *m_iter;
				if( e->halfedge(m_id) == NULL )
				{
					m_id = 0;
					++ m_iter;
				}
			}
			break;
		case 2:
			m_id = 0;
			++m_iter;
			break;
		}
	};
	
    /*! @brief 判断是否遍历完所有半边 */
	bool end() { return m_iter == m_pMesh->edges().end(); }

private:
	CHalfEdge *                                      m_he;   //!< 未使用，保留成员
	CBaseMesh<CVertex,CEdge,CFace,CHalfEdge> *       m_pMesh; //!< 目标网格，遍历它的所有半边
	typename std::list<CEdge*>::iterator             m_iter;  //!< 当前正在遍历的边迭代器
	int                                             m_id;    //!< 当前边的第几个半边（0或1）
};


} // namespace MeshLib

#endif
