/*
 *  \file test_quat.cpp
 *  \brief 测试 CQuat 四元数类的所有功能
 *
 *  测试项目：
 *  1. 构造函数，默认单位四元数
 *  2. 四元数乘法（复合旋转）
 *  3. 点旋转，验证旋转正确性
 *  4. 归一化测试
 *  5. 共轭和求逆测试
 *  6. 转换OpenGL矩阵测试
 *  7. 幂运算（插值）测试
 */

#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include "Geometry/quat.h"

using namespace MeshLib;
using namespace std;

// 浮点数近似相等判断
bool approxEqual(double a, double b, double eps = 1e-8) {
    return fabs(a - b) < eps;
}

int main() {
    cout << "===== Testing CQuat Class =====\n\n";

    // 1. 默认构造函数：应该是单位四元数 (1, 0, 0, 0) 表示不旋转
    CQuat q0;
    cout << "1. Default constructor test (identity quaternion): q0 = (" 
         << q0.m_w << ", " << q0.m_x << ", " << q0.m_y << ", " << q0.m_z << ")\n";
    if (approxEqual(q0.m_w, 1) && 
        approxEqual(q0.m_x, 0) && 
        approxEqual(q0.m_y, 0) && 
        approxEqual(q0.m_z, 0)) {
        cout << "   ✓ PASS\n";
    } else {
        cout << "   ✗ FAIL\n";
        return 1;
    }

    // 2. 绕X轴旋转90度构造四元数验证
    // 绕X轴θ旋转：w = cos(θ/2), x = sin(θ/2), y = z = 0
    // θ=90度=π/2 → θ/2=45度 → cos=sin=√2/2≈0.70710678
    double theta = M_PI / 2.0; // 90度
    double c = cos(theta / 2.0);
    double s = sin(theta / 2.0);
    CQuat qx(c, s, 0, 0);
    qx.normalize(); // 确保归一化
    cout << "\n2. Rotate 90° around X-axis: qx = (" << qx.m_w << ", " << qx.m_x << ", " << qx.m_y << ", " << qx.m_z << ")\n";
    if (approxEqual(qx.m_w, c) && approxEqual(qx.m_x, s) && approxEqual(qx.m_y, 0) && approxEqual(qx.m_z, 0)) {
        cout << "   ✓ PASS\n";
    } else {
        cout << "   ✗ FAIL\n";
        return 1;
    }

    // 3. 共轭和逆测试：单位四元数逆就是共轭
    CQuat qx_conj = qx.conjugate();
    CQuat qx_inv = qx.inverse();
    cout << "\n3. conjugate() and inverse() test:\n";
    cout << "   qx.conj = (" << qx_conj.m_w << ", " << qx_conj.m_x << ", " << qx_conj.m_y << ", " << qx_conj.m_z << ")\n";
    bool conj_ok = approxEqual(qx_conj.m_w, qx.m_w) && approxEqual(qx_conj.m_x, -qx.m_x) &&
                  approxEqual(qx_conj.m_y, -qx.m_y) && approxEqual(qx_conj.m_z, -qx.m_z);
    bool inv_ok = (qx_inv.m_w == qx_conj.m_w && qx_inv.m_x == qx_conj.m_x &&
                   qx_inv.m_y == qx_conj.m_y && qx_inv.m_z == qx_conj.m_z);
    if (conj_ok && inv_ok) {
        cout << "   ✓ PASS (conjugate correct, inverse == conjugate for unit quat)\n";
    } else {
        cout << "   ✗ FAIL\n";
        return 1;
    }

    // 4. 旋转点测试：绕X轴转90度把 (0, 1, 0) 转到 (0, 0, 1)
    CPoint p(0, 1, 0);
    CPoint rotated_p = qx * p;
    cout << "\n4. Rotate point test: rotate (0, 1, 0) 90° around X-axis\n";
    cout << "   Result = (" << rotated_p[0] << ", " << rotated_p[1] << ", " << rotated_p[2] << ")\n";
    cout << "   Expected = (0, 0, 1)\n";
    if (approxEqual(rotated_p[0], 0) && 
        approxEqual(rotated_p[1], 0, 1e-6) && 
        approxEqual(rotated_p[2], 1, 1e-6)) {
        cout << "   ✓ PASS\n";
    } else {
        cout << "   ✗ FAIL\n";
        return 1;
    }

    // 5. 反向旋转测试：qx * qx.inverse() 应该是单位变换，转回原点
    CPoint p_back = qx.inverse() * rotated_p;
    cout << "\n5. Reverse rotation test: rotate back using inverse\n";
    cout << "   Result = (" << p_back[0] << ", " << p_back[1] << ", " << p_back[2] << ")\n";
    cout << "   Expected = (0, 1, 0)\n";
    if (approxEqual(p_back[0], 0) && 
        approxEqual(p_back[1], 1, 1e-6) && 
        approxEqual(p_back[2], 0, 1e-6)) {
        cout << "   ✓ PASS\n";
    } else {
        cout << "   ✗ FAIL\n";
        return 1;
    }

    // 6. 四元数乘法复合测试：先转X90度，再转X90度，总旋转是X180度
    CQuat q_180x = qx * qx;
    q_180x.normalize();
    CPoint p2(0, 1, 0);
    CPoint rotated_180 = q_180x * p2;
    cout << "\n6. Quaternion multiplication (compose rotation) test: 2 * 90° X rotation = 180° X\n";
    cout << "   Rotate (0, 1, 0): result = (" << rotated_180[0] << ", " << rotated_180[1] << ", " << rotated_180[2] << ")\n";
    cout << "   Expected = (0, -1, 0)\n";
    if (approxEqual(rotated_180[0], 0) && 
        approxEqual(rotated_180[1], -1, 1e-6) && 
        approxEqual(rotated_180[2], 0, 1e-6)) {
        cout << "   ✓ PASS\n";
    } else {
        cout << "   ✗ FAIL\n";
        return 1;
    }

    // 7. 点积测试：两个相同四元数点积应该接近1
    double dot = qx.dot(qx);
    cout << "\n7. Dot product test: qx.dot(qx) = " << dot << "\n";
    if (approxEqual(dot, 1.0)) {
        cout << "   ✓ PASS\n";
    } else {
        cout << "   ✗ FAIL\n";
        return 1;
    }

    // 8. |运算符测试，就是点积
    double dot2 = qx | qx;
    cout << "\n8. | operator dot test: qx | qx = " << dot2 << "\n";
    if (approxEqual(dot2, 1.0)) {
        cout << "   ✓ PASS\n";
    } else {
        cout << "   ✗ FAIL\n";
        return 1;
    }

    // 9. 幂运算测试：半角插值
    // qx是90度，pow(qx, 0.5)应该是45度
    CQuat q_45x = pow(qx, 0.5);
    CPoint p_rot_45 = q_45x * p;
    // 45度旋转(0, 1, 0)应该得到 (0, √2/2, √2/2) ≈ (0, 0.7071, 0.7071)
    cout << "\n9. Power operation (interpolation) test: (90° rotation)^0.5 = 45° rotation\n";
    cout << "   Rotate (0, 1, 0): result = (" << p_rot_45[0] << ", " << p_rot_45[1] << ", " << p_rot_45[2] << ")\n";
    cout << "   Expected ≈ (0, 0.7071, 0.7071)\n";
    if (approxEqual(p_rot_45[0], 0) && 
        approxEqual(p_rot_45[1], sqrt(2)/2, 1e-4) && 
        approxEqual(p_rot_45[2], sqrt(2)/2, 1e-4)) {
        cout << "   ✓ PASS\n";
    } else {
        cout << "   ✗ FAIL\n";
        return 1;
    }

    // 10. convert to OpenGL 4x4 matrix test
    double m[16];
    qx.convert(m);
    // 绕X轴90度，OpenGL列主序：
    // | 1   0    0    0 |
    // | 0   0   -1    0 |
    // | 0   1    0    0 |
    // | 0   0    0    1 |
    // 列索引对应到m的位置：col *4 + row，所以 (row 1, col 1) → 1*4+1 = 5，(row 2, col 1) → 1*4+2 =6
    //                         (row 1, col 2) → 2*4+1 =9，(row 2, col 2) → 2*4+2 = 10
    cout << "\n10. Convert to OpenGL matrix test\n";
    // 验证旋转矩阵元素
    bool matrix_ok = true;
    matrix_ok &= approxEqual(m[0], 1);               // m[0][0]
    matrix_ok &= approxEqual(m[5], 0, 1e-6);         // m[1][1] = 0
    matrix_ok &= approxEqual(m[6], 1, 1e-6);         // m[2][1] = 1
    matrix_ok &= approxEqual(m[9], -1, 1e-6);        // m[1][2] = -1
    matrix_ok &= approxEqual(m[10], 0, 1e-6);        // m[2][2] = 0
    matrix_ok &= approxEqual(m[15], 1);              // m[3][3] = 1
    if (matrix_ok) {
        cout << "   ✓ PASS (rotation matrix matches expected 90° X rotation)\n";
    } else {
        cout << "   Elements: m[0] = " << m[0] << " m[5] = " << m[5] << " m[6] = " << m[6] << " m[9] = " << m[9] << "\n";
        cout << "   ✗ FAIL\n";
        return 1;
    }

    // 11. const correctness test：const对象能正常调用只读方法
    const CQuat const_q = qx;
    double const_dot = const_q.dot(qx);
    CQuat const_inv = const_q.inverse();
    CPoint const_rot = const_q * p;
    cout << "\n11. Const correctness test\n";
    if (approxEqual(const_dot, 1.0)) {
        cout << "   ✓ PASS (const quat can call all const methods correctly)\n";
    } else {
        cout << "   ✗ FAIL\n";
        return 1;
    }

    cout << "\n===== All " << 11 << " tests passed! =====\n";
    return 0;
}