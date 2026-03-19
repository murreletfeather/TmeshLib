/*!
*      \file Point2.h
*      \brief Two dimensional point class
*	   \author David Gu TIM HUNTER
*      \date 10/07/2010 3/19/2026
*
*/

#ifndef _T_MESHLIB_POINT2_H_
#define _T_MESHLIB_POINT2_H_

#include <math.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <sstream>




/*!
*	\brief CPoint2 class, two dimensional point
*
*	Two dimensional point \f$(x,y)\f$
*/
class CPoint2
{
	public:
	/*!
	 * CPoint2 constructor, specifying \f$(x,y)\f$
	 * 带参数构造函数，指定x, y两个坐标分量
	 */
	CPoint2( double  x, double y ) { m_c[0] = x; m_c[1] = y; };

	/*!
	*	CPoint2 default constructor, it is initialized to be (0,0)
	* 默认构造函数，初始化为原点(0, 0)
	*/
	CPoint2(){ m_c[0] = 0; m_c[1] = 0; };

	/*!
	*	CPoint2 copy constructor, initialized from another CPoint2
	* 拷贝构造函数，从另一个二维点复制坐标
	*/
    CPoint2( const CPoint2 & p ) { m_c[0] = p[0]; m_c[1] = p[1]; };

	/*!
	*	CPoint2 assignment operator
	*	\param p another CPoint2
	*	\return reference to this
	* 赋值运算符，从另一个二维点复制坐标
	*/
	CPoint2 & operator = ( const CPoint2 & p ) {
		m_c[0] = p[0];
		m_c[1] = p[1];
		return *this;
	};

	/*!
	 *	CPoint2 class destructor
	 * 析构函数
	 */
    ~CPoint2(){};
	
	 /*!
	  *	reference to the values, CPoint2[0] x value ; CPoint2[1] y value; 
	  * 非const版本下标访问，返回引用可以修改分量
	  */
    double & operator[]( int i ) { 	assert( i < 2 && i >= 0 ); return m_c[i]; };

	/*!
	*	constant (x,y) value
	*   \param i index
	*   \return CPoint2(i)
	*  函数调用风格访问，只读，const保证不修改点
	*/
	double   operator()( int i) const { assert( 0<=i && i<2 ); return m_c[i]; };

	/*!
	*	constant values, CPoint2[0] x value ; CPoint2[1] y value; 
	*  const版本下标访问，只读
	*/
    double  operator[]( int i ) const { 	assert( i < 2 && i >= 0 ); return m_c[i]; };

	/*!
	*	equality comparison
	*	\param uv another point
	*	\return whether two points are equal
	*  判断两个二维点坐标是否完全相等
	*/
	bool operator==( const CPoint2 & uv ) 
	{
		return ( m_c[0] == uv.m_c[0] && m_c[1] == uv.m_c[1] );
	}

	/*!
	 * The norm of CPoint2 \f$\sqrt{x^2+y^2}\f$
	 * 计算二维点的模长（欧几里得距离）
	 */
	double norm() const { return sqrt( fabs( m_c[0] * m_c[0] + m_c[1] * m_c[1] ) ); };

	/*!
	 * The square norm of CPoint2 \f$x^2+y^2\f$
	 * 计算模长的平方，避免开根号开销
	 */
	double norm2() const { return  m_c[0] * m_c[0] + m_c[1] * m_c[1]; };

	/*!
	 * Add another point to the current point
	 * \param p
	 * \return current point is added by p.
	 * 复合加法：将另一个点加到当前点上
	 */
	CPoint2  & operator += ( const CPoint2 & p) { m_c[0] += p[0]; m_c[1] += p[1]; return *this; }; 
	/*!
	 * Substract another point to the current point
	 * \param p
	 * \return current point is substracted by p.
	 * 复合减法：从当前点减去另一个点
	 */
	CPoint2  & operator -= ( const CPoint2 & p)  { m_c[0] -= p[0]; m_c[1] -= p[1]; return *this; };
	/*!
	 * Multiply by a scalar
	 * \param s scalar
	 * \return current point is multipolied by s.
	 * 复合数乘：当前点每个分量乘以标量s
	 */
	
	CPoint2  & operator *= ( const double  s) { m_c[0] *= s; m_c[1] *= s; return *this; };

	/*!
	 * Divide by a scalar
	 * \param s scalar
	 * \return current point is divided by s.
	 * 复合除法：当前点每个分量除以标量s
	 */
	CPoint2  & operator /= ( const double  s) { m_c[0] /= s   ; m_c[1] /=    s; return *this; };

	/*!
	 * dot product
	 * \param p another point
	 * \return dot product of current point with p.
	 * 点积（内积）运算：两个点对应分量相乘再相加
	 */
	double   operator*( const CPoint2 & p ) const 
	{
		return m_c[0] * p[0] + m_c[1] * p[1]; 
	};

	/*!
	 * Add two points
	 * \param p
	 * \return sum of current point and p.
	 * 加法：两个点对应分量相加，返回新点
	 */
	CPoint2   operator+( const CPoint2 & p  ) const
	{
		CPoint2 r( m_c[0] + p[0], m_c[1] + p[1] );
		return r;
	};

	/*!
	 * Subtract two points
	 * \param p
	 * \return difference of current point and p.
	 * 减法：两个点对应分量相减，返回新点
	 */
	CPoint2   operator-( const CPoint2 & p  ) const
	{
		CPoint2 r( m_c[0] - p[0], m_c[1] - p[1] );
		return r;
	};

	/*!
	 * Multiply by a scalar
	 * \param s scalar
	 * \return current point multiplied by s.
	 * 标量乘法：每个分量乘以标量s，返回新点
	 */
	CPoint2   operator*( const double s  ) const
	{
		CPoint2 r( m_c[0] * s, m_c[1] * s );
		return r;
	};
	
	/*!
	 * Divide by a scalar
	 * \param s scalar
	 * \return current point divided by s.
	 * 标量除法：每个分量除以标量s，返回新点
	 */
	CPoint2   operator/( const double s  ) const
	{
		CPoint2 r( m_c[0] / s, m_c[1] / s );
		return r;
	};

	/*!
	 * negate the point
	 * \return the negative of the current point
	 * 取反：每个分量都取相反数，返回新点
	 */
	CPoint2 operator-() const
	{
		CPoint2 p(-m_c[0],-m_c[1]);
		return p;
	};

	private:
		/*!
		* (x,y) 两个坐标分量存储数组
		*/
		double m_c[2];

};

/*!
 * Multiply a scalar by a CPoint2
 * \param s scalar
 * \param p two dimensional point
 * \return the point multiplied by the scalar
 * 左乘：标量s左乘二维点p，满足交换律 s * p = p * s
 */
inline CPoint2 operator*( double s, const CPoint2 & p )
{
    return p * s;
}

/*!
 * Write a CPoint2 to an output stream
 * \param os output stream
 * \param p two dimensional point
 * \return the output stream reference to support chaining
 * 将二维点输出到流，格式为 "(x, y)"
 */
inline std::ostream & operator<<( std::ostream & os, const CPoint2 & p )
{
    os << "(" << p[0] << ", " << p[1] << ")";
    return os;
}

/*!
 *	square of the norm of the CPoint2 \f$x^2+y^2\f$
 *  \param uv input two dimensional point
 *  \return square of the norm of the point
 *  计算二维点模长的平方（全局函数）
 */
inline double mag2(  CPoint2 & uv )
{
	return uv[0] * uv[0] + uv[1] * uv[1];
};

/*!
 *	norm of the CPoint2 \f$ \sqrt{x^2+y^2}\f$
 *  \param uv input two dimensional point
 *  \return norm of the point
 *  计算二维点的模长（全局函数）
 */
inline double mag(  CPoint2 & uv )
{
	return sqrt(uv[0] * uv[0] + uv[1] * uv[1]);
};

/*!
 *	cross product of two CPoint2
 *  \param uv1 the first  two diemenional point
 *  \param uv2 the second two diemenional point
 *  \return the cross product of the two points
 *  两个二维向量叉积，结果等于平行四边形面积
 *  \f[
 *  \left|
 *	\begin{array}{cc}
 *  x_1 & y_1\\
 *  x_2 & y_2 \\
 *  \end{array}
 *	\right|
 *  \f]
 */

inline double cross(  CPoint2 uv1,  CPoint2 uv2 )
{
	return (uv1[0] * uv2[1] - uv1[1] * uv2[0]);
};


// 内点积已经有类成员版本，保持和CPoint一致，去掉全局重复版本避免匹配歧义
/*!
 *	cross product of two CPoint2
 *  \param uv1 the first  two diemenional point
 *  \param uv2 the second two diemenional point
 *  \return the cross product of the two points
 *  两个二维向量叉积（运算符版本）
 */

inline double operator^(  CPoint2 uv1,  CPoint2 uv2 )
{
	return (uv1[0] * uv2[1] - uv1[1] * uv2[0]);
};

/*!
 *	read in a CPoint2 from a string
 *  \param str input string 格式为 "(x y)" 的字符串
 *  \param c   the reference to a point
 *  \return 从字符串中读出(x,y)赋值给c
 *  从字符串解析二维点，自动去掉括号和多余空格
 */

inline void operator>>(const std::string & str, CPoint2& c )
{
	std::string t = str;
	t.erase(0, t.find_first_not_of("()") );
	t.erase(t.find_last_not_of("()") + 1);
	std::istringstream iss( t );

	iss >> c[0] >> c[1];
}



#endif
