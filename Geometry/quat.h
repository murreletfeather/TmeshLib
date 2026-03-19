/*!
*      \file Quat.h
*      \brief Quaternion (四元数，用于三维旋转)
*       \author David Gu  TIM HUNTER
*      \date 10/07/2010  19/03/2026
*
*/

#ifndef _QUAT_H_
#define _QUAT_H_

#include <math.h>
#include "Point.h"

// 4x4矩阵类型声明，用于输出OpenGL旋转矩阵
typedef double mat44[4][4];

namespace MeshLib
{

/*!
 *  \brief CQuat 四元数类，用于表示和计算三维空间旋转
 *
 *  四元数是三维旋转最方便的表示方式：
 *  - 避免欧拉角的万向锁问题
 *  - 方便做旋转插值 (SLERP)
 *  - 转换为旋转矩阵很高效，适合图形学渲染
 */
class CQuat
{
public:
    /*!
     *  CQuat 默认构造函数，构造单位四元数 (w=1, x=y=z=0)，表示不旋转
     */
    CQuat(){ m_w = 1; m_x = m_y = m_z = 0; };

    /*!
     *  CQuat 构造函数，直接指定四个分量
     *  \param w 实部
     *  \param x X分量虚部
     *  \param y Y分量虚部
     *  \param z Z分量虚部
     */
    CQuat( double w, double x, double y, double z)
    {
        m_w = w;
        m_x = x;
        m_y = y;
        m_z = z;
    };

    /*!
     *  CQuat 拷贝构造函数，从另一个四元数复制
     *  \param q 输入四元数
     */
    CQuat( const CQuat & q )
    {
        m_w =  q.m_w;
        m_x =  q.m_x;
        m_y =  q.m_y;
        m_z =  q.m_z;
    }

    /*!
     *  赋值运算符重载
     *  \param q 输入四元数
     *  \return 返回当前对象引用，支持链式赋值 a = b = c
     */
    CQuat & operator=(const CQuat & q)
    {
        m_w = q.m_w;
        m_x  = q.m_x;
        m_y  = q.m_y;
        m_z  = q.m_z;
        return *this;
    }

    /*!
     *  析构函数
     */
    ~CQuat(){};

    /*!
     *  四元数幂运算，用于旋转插值
     *  \param p 幂次，比如p=-1表示求逆旋转
     *  \return 返回缩放后的旋转四元数
     *
     *  如果原旋转是角度θ，结果就是角度pθ，用来在两个旋转之间做插值
     *  这个是成员版本，修改当前四元数本身
     */
    CQuat& pow(double p)
    {
        normalize();
        double theta = 2 * acos( m_w );
        if( theta < 1e-10 ) return (*this);

        CPoint axis( m_x, m_y, m_z );
        axis /= axis.norm();

        theta *= p;
        m_w   = cos( theta * 0.5 );
        axis *= sin( theta * 0.5 );

        m_x = axis[0];
        m_y = axis[1];
        m_z = axis[2];

        return (*this);
    };


    /*!
     *  转换四元数为OpenGL格式4x4旋转矩阵
     *  \param m 输出矩阵指针，必须能容纳16个double (4x4)
     *
     *  转换后的矩阵可以直接传给glLoadMatrixd或者给着色器用
     */
    void convert( double * m)
    {
        CQuat q = *this;
        double l = q.dot(q);
        double s = 2.0 / l;
        double xs = q.m_x * s;
        double ys = q.m_y * s;
        double zs = q.m_z * s;

        double wx = q.m_w * xs;
        double wy = q.m_w * ys;
        double wz = q.m_w * zs;

        double xx = q.m_x * xs;
        double xy = q.m_x * ys;
        double xz = q.m_x * zs;

        double yy = q.m_y * ys;
        double yz = q.m_y * zs;
        double zz = q.m_z * zs;


        m[0*4+0] = 1.0 - (yy + zz);
        m[1*4+0] = xy - wz;
        m[2*4+0] = xz + wy;
        m[0*4+1] = xy + wz;
        m[1*4+1] = 1.0 - (xx + zz);
        m[2*4+1] = yz - wx;
        m[0*4+2] = xz - wy;
        m[1*4+2] = yz + wx;
        m[2*4+2] = 1.0 - (xx + yy);


        m[0*4+3] = 0.0;
        m[1*4+3] = 0.0;
        m[2*4+3] = 0.0;
        m[3*4+0] = m[3*4+1] = m[3*4+2] = 0.0;
        m[3*4+3] = 1.0;
    };

    /*!
     *  用当前四元数旋转三维点
     *  \param  p 输入待旋转三维点
     *  \return 旋转后的新三维点
     *
     *  公式: p' = q * p * q^{-1}，把纯虚四元数p旋转得到新的p'
     */
    CPoint operator*( const CPoint & p )
    {
        CQuat   q(m_w, m_x, m_y, m_z);
        CQuat pq( 0, p[0], p[1], p[2]);
        CQuat iq(m_w, m_x, m_y, m_z);
        iq.pow(-1);
        CQuat r =     q *  pq * iq ;
        return CPoint(r.m_x, r.m_y, r.m_z);
    };


public:
    /*!
     *  四元数四个分量: (w, x, y, z) = w + x*i + y*j + z*k
     */
    double m_w, m_x, m_y, m_z;

    /*!
     *  归一化四元数，保证它是单位四元数（单位四元数才能正确表示旋转）
     */
    void normalize()
    {
        double l = m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z;
        if( l < 1e-20 ) {
            m_x = 0; m_y = 0; m_z = 0; m_w = 1;
            return;
        }

        l = sqrt(l);

        m_w /= l;
        m_x /= l;
        m_y /= l;
        m_z /= l;
    };

    /*!
    *  四元数乘法（旋转复合）
    *  公式: res = q_left * q_right
    *  含义: 结果对应的变换是先执行 q_right 对应的旋转，再执行 q_left 对应的旋转
    *  \param q 右操作数 (即 q_right，逻辑上先执行的旋转)
    *  \return 复合后的旋转四元数
    */
    CQuat operator*( const CQuat & q ) const
    {
        double   sp = m_w;
        CPoint vp( m_x, m_y, m_z );

        double   sq = q.m_w;
        CPoint vq( q.m_x, q.m_y, q.m_z );

        double   sr = sp * sq - vp * vq;

        CPoint vr;
        CPoint dp;
        dp = vp ^ vq;
        vp = vp * sq;
        vq = vq * sp;
        vr = vp   + vq + dp;

        return CQuat( sr, vr[0], vr[1], vr[2]);
    };

    /*!
     *  计算两个四元数的点积（内积）
     *  \param q 输入另一个四元数
     *  \return 点积结果，值越接近1两个旋转越接近
     */
    double dot( const CQuat & q ) const
    {
        return ( m_w * q.m_w + m_x * q.m_x + m_y * q.m_y + m_z * q.m_z);
    };

    /*!
     *  运算符版本点积，用管道符 | 做内积
     *  \param q 输入另一个四元数
     *  \return 两个四元数的内积结果
     */
    double operator|( const CQuat & q ) const
    {
        return dot(q);
    }

};


/*!
 *  全局版本四元数幂运算（重载pow函数），支持const对象，返回新四元数不修改原对象
 *  \param r 输入原四元数（const保证不修改输入对象）
 *  \param p 幂次，比如：
 *           - p=-1 → 求逆旋转
 *           - p=0.5 → 原旋转角度减半，得到中间旋转
 *  \return 幂运算后的新四元数结果
 * 
 *  作用：四元数幂运算是旋转球面线性插值(SLERP)的核心操作，如果原旋转角度是θ，
 *  经过pow(r, p)后得到对应角度pθ，用来在两个旋转之间插值得到平滑过渡的中间旋转。
 */
inline CQuat pow(const CQuat & r, double p)
{
    CQuat q = r;
    q.normalize();
    double theta = 2 * acos( q.m_w );
    if( theta < 1e-10 ) return q;

    CPoint axis( q.m_x, q.m_y, q.m_z );
    axis /= axis.norm();
    theta *= p;
    q.m_w   = cos( theta * 0.5 );
    axis *= sin( theta * 0.5 );

    q.m_x = axis[0];
    q.m_y = axis[1];
    q.m_z = axis[2];

    return q;
};

} // namespace MeshLib

#endif