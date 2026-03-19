/*!
*      \file Point.h
*      \brief Three dimensional point class
*	   \author David Gu TIM HUNTER
*      \date 10/07/2010 3/19/2026
*
*/

#ifndef _T_MESHLIB_POINT_H_
#define _T_MESHLIB_POINT_H_

#include <assert.h>
#include <math.h>
#include <string>
#include <sstream>




/*!
*	\brief CPoint class, three dimensional point
*
*	Three dimensional point or vector \f$(x,y,z)\f$, inner product, cross product, scale multiplication etc.
*/
class CPoint{

public:
	/*!
	 * CPoint constructor, specifying \f$(x,y,z)\f$
	 * 带参数构造函数，指定x, y, z三个坐标分量
	 */
	CPoint( double x, double y, double z ){ v[0] = x; v[1] = y; v[2] = z;};

	/*!
	*	CPoint default constructor, initialized as (0,0,0)
	* 默认构造函数，初始化为原点(0, 0, 0)
	*/
	CPoint() { v[0] = v[1] = v[2] = 0; };

	/*!
	*	CPoint copy constructor, initialized from another CPoint
	* 拷贝构造函数，从另一个点复制坐标
	*/
	CPoint( const CPoint & p ) { v[0] = p[0]; v[1] = p[1]; v[2] = p[2]; };

	/*!
	*	CPoint assignment operator
	*	\param p another CPoint
	*	\return reference to this
	* 赋值运算符，从另一个点复制坐标
	*/
	CPoint & operator = ( const CPoint & p ) {
		v[0] = p[0];
		v[1] = p[1];
		v[2] = p[2];
		return *this;
	};

	/*!
	*	CPoint destructor
	* 析构函数
	*/
	~CPoint(){};

	/*!
	*	reference to  \f$(x,y,z)\f$ value
	*   \param i index
	*   \return CPoint[i]
	* 非const版本下标访问，返回引用可以修改分量
	*/
	double & operator[]( int i )		  { assert( 0<=i && i<3 ); return v[i]; };

	/*!
	*	constant (x,y,z) value
	*   \param i index
	*   \return CPoint[i]
	* 函数调用风格访问，只读，const保证不修改点
	*/
	double operator()( int i ) const { assert( 0<=i && i<3 ); return v[i]; };

	/*!
	*	constant  \f$(x,y,z)\f$ value
	*   \param i index
	*   \return CPoint[i]
	* const版本下标访问，只读
	*/
	double   operator[]( int i ) const { assert( 0<=i && i<3 ); return v[i]; };

	/*!
	 *	norm of the CPoint \f$\sqrt{x^2+y^2+z^2}\f$
	 *  计算点的模长（欧几里得距离）
	 */
	double norm() const { return sqrt( fabs( v[0] * v[0] + v[1] * v[1] + v[2] * v[2] ) ); };

	/*!
	 *	square norm of the CPoint \f$x^2+y^2+z^2\f$
	 *  计算模长的平方，避免开根号开销
	 */
	double norm2() const { return  v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; };

	/*!
	*	equality comparison
	*	\param p another point
	*	\return whether two points are equal
	*  判断两个点坐标是否完全相等
	*/
	bool operator==( const CPoint & p ) 
	{
		return ( v[0] == p[0] && v[1] == p[1] && v[2] == p[2] );
	}

	/*!
	 * Add another point to the current point
	 * \param p
	 * \return cuccrent point is added by p.
	 * 复合加法：将另一个点加到当前点上
	 */
	CPoint  & operator += ( const CPoint & p) { v[0] += p(0); v[1] += p(1); v[2] += p(2); return *this; }; 

	/*!
	 * Substract another point to the current point
	 * \param p
	 * \return cuccrent point is substracted by p.
	 * 复合减法：从当前点减去另一个点
	 */
	CPoint  & operator -= ( const CPoint & p)  { v[0] -= p(0); v[1] -= p(1); v[2] -= p(2); return *this; };

	/*!
	 * Multiply by a scalar
	 * \param s scalar
	 * \return current point is multipolied by s.
	 * 复合数乘：当前点每个分量乘以标量s
	 */
	CPoint  & operator *= ( const double  s) { v[0] *= s   ; v[1] *=    s; v[2] *=    s; return *this; };

	/*!
	 * Divide by a scalar
	 * \param s scalar
	 * \return current point is divided by s.
	 * 复合除法：当前点每个分量除以标量s
	 */
	CPoint  & operator /= ( const double  s) { v[0] /= s   ; v[1] /=    s; v[2] /=    s; return *this; };

	/*!
	 * dot product
	 * \param p another point
	 * \return dot product of current point with p.
	 * 点积（内积）运算：两个点对应分量相乘再相加
	 */
	double   operator*( const CPoint & p ) const 
	{
		return v[0] * p[0] + v[1] * p[1] + v[2] * p[2]; 
	};

	/*!
	 * Add two points
	 * \param p
	 * \return sum of two points.
	 * 加法：两个点对应分量相加，返回新点
	 */
	CPoint   operator+( const CPoint & p  ) const
	{
		CPoint r( v[0] + p[0], v[1] + p[1], v[2] + p[2] );
		return r;
	};

	/*!
	 * Subtract two points
	 * \param p
	 * \return difference of two points.
	 * 减法：两个点对应分量相减，返回新点
	 */
	CPoint   operator-( const CPoint & p  ) const
	{
		CPoint r( v[0] - p[0], v[1] - p[1], v[2] - p[2] );
		return r;
	};

	/*!
	 * Multiply by a scalar
	 * \param s scalar
	 * \return current point multiplied by s.
	 * 标量乘法：每个分量乘以标量s，返回新点
	 */
	CPoint   operator*( const double s  ) const
	{
		CPoint r( v[0] * s, v[1] * s, v[2] * s );
		return r;
	};
	
	/*!
	 * Divide by a scalar
	 * \param s scalar
	 * \return current point divided by s.
	 * 标量除法：每个分量除以标量s，返回新点
	 */
	CPoint   operator/( const double s  ) const
	{
		CPoint r( v[0] / s, v[1] / s, v[2] / s );
		return r;
	};

	/*!
	 * Cross product
	 * \param p2 another point
	 * \return cross product of the current point with p2.
	 * 叉积运算：返回两个三维向量的叉积，结果仍是三维向量
	 * \f[
	 * \left|
		\begin{array}{ccc}
		x_1& y_1 & z_1\\
		x_2 &y_2 & z_2\\
		\mathbf{e}_1 & \mathbf{e}_2 & \mathbf{e}_3\\
		\end{array}
	 * \right|
	 * \f]
	 */
	CPoint operator^( const CPoint & p2) const
	{
		CPoint r( v[1] * p2[2] - v[2] * p2[1],
			      v[2] * p2[0] - v[0] * p2[2],
		           v[0] * p2[1] - v[1] * p2[0]);
		return r;
	};

	/*!
	 * negate the point
	 * \return the negative of the current point
	 * 取反：每个分量都取相反数，返回新点
	 */
	CPoint operator-() const
	{
		CPoint p(-v[0],-v[1],-v[2]);
		return p;
	};

protected:
	/*!
	* \f$(x,y,z)\f$ 三个坐标分量存储数组
	*/
	double v[3];
};

/*!
 * Multiply a scalar by a CPoint
 * \param s scalar
 * \param p three dimensional point
 * \return the point multiplied by the scalar
 * 左乘：标量s左乘三维点p，满足交换律 s * p = p * s
 */
inline CPoint operator*( double s, const CPoint & p )
{
    return p * s;
}

/*!
 *	Read a CPoint from a string
 * \param str string 格式为 "(x y z)" 的字符串
 * \param p three dimenionsal point 存储结果的点
 * \return the input string reference to support chaining
 * 从字符串解析三维点，自动去掉括号和多余空格
 */
inline const std::string & operator>>(const std::string & str, CPoint &p )
{
	std::string t = str;
	t.erase(0, t.find_first_not_of("()") );
	t.erase(t.find_last_not_of("()") + 1);
	std::istringstream iss( t );

	iss >> p[0] >> p[1] >> p[2];
    return str;
}

/*!
 * Write a CPoint to an output stream
 * \param os output stream 输出流
 * \param p three dimensional point 要输出的点
 * \return the output stream reference to support chaining
 * 将三维点输出到流，格式为 "(x, y, z)"
 */
inline std::ostream & operator<<( std::ostream & os, const CPoint & p )
{
    os << "(" << p[0] << ", " << p[1] << ", " << p[2] << ")";
    return os;
}

/*!
 *	square of the norm of the CPoint \f$x^2+y^2+z^2\f$
 *  \param p input three dimensional point
 *  \return square of the norm of the point
 *  计算三维点模长的平方（全局函数版本）
 */
inline double mag2(  CPoint & p )
{
	return p[0] * p[0] + p[1] * p[1] + p[2] * p[2];
};

/*!
 *	norm of the CPoint \f$ \sqrt{x^2+y^2+z^2}\f$
 *  \param p input three dimensional point
 *  \return norm of the point
 *  计算三维点的模长（全局函数版本）
 */
inline double mag(  CPoint & p )
{
	return sqrt(mag2(p));
};


#endif
