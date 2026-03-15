#include "Geometry/Point.h"
#include <iostream>
#include <string>

int main() {
    std::cout << "===== Testing CPoint Class =====" << std::endl;

    // 1. 测试构造函数
    CPoint p1(1.0, 2.0, 3.0);
    std::cout << "1. Constructor test: p1 = (" << p1[0] << ", " << p1[1] << ", " << p1[2] << ")" << std::endl;

    // 2. 测试默认构造函数
    CPoint p0;
    std::cout << "2. Default constructor test: p0 = (" << p0[0] << ", " << p0[1] << ", " << p0[2] << ")" << std::endl;

    // 3. 测试标量乘法 (点 * 标量)
    CPoint p2 = 2.0 * p1;
    std::cout << "3. Scalar multiply test (2.0 * p1): p2 = (" << p2[0] << ", " << p2[1] << ", " << p2[2] << ")" << std::endl;

    // 4. 测试加法
    CPoint p3 = p1 + p2;
    std::cout << "4. Addition test (p1 + p2): p3 = (" << p3[0] << ", " << p3[1] << ", " << p3[2] << ")" << std::endl;

    // 5. 测试减法
    CPoint p4 = p2 - p1;
    std::cout << "5. Subtraction test (p2 - p1): p4 = (" << p4[0] << ", " << p4[1] << ", " << p4[2] << ")" << std::endl;

    // 6. 测试一元负号
    CPoint p5 = -p1;
    std::cout << "6. Unary minus test (-p1): p5 = (" << p5[0] << ", " << p5[1] << ", " << p5[2] << ")" << std::endl;

    // 7. 测试点乘
    double dot = p1 * p2;
    std::cout << "7. Dot product test (p1 * p2): " << dot << " (expected: 1*2 + 2*4 + 3*6 = 28)" << std::endl;

    // 8. 测试叉乘
    CPoint cross = p1 ^ p2;
    std::cout << "8. Cross product test (p1 ^ p2): (" << cross[0] << ", " << cross[1] << ", " << cross[2] << ")" << std::endl;
    std::cout << "   Expected: (2*6 - 3*4, 3*2 - 1*6, 1*4 - 2*2) = (0, 0, 0) (parallel vectors)" << std::endl;

    // 9. 测试模长
    double norm = p1.norm();
    std::cout << "9. Norm test: |p1| = " << norm << " (expected: sqrt(1+4+9) ≈ 3.7417)" << std::endl;

    // 10. 测试字符串解析
    std::string str = "(10.5 20.5 30.5)";
    CPoint p6;
    str >> p6;
    std::cout << "10. String parse test: parsed from \"" << str << "\" to (" << p6[0] << ", " << p6[1] << ", " << p6[2] << ")" << std::endl;

    // 11. 测试+=运算符
    CPoint p7(1, 1, 1);
    p7 += p1;
    std::cout << "11. += operator test: p7 += p1 = (" << p7[0] << ", " << p7[1] << ", " << p7[2] << ")" << std::endl;

    // 12. 测试*=运算符
    CPoint p8(2, 3, 4);
    p8 *= 2.5;
    std::cout << "12. *= operator test: p8 *= 2.5 = (" << p8[0] << ", " << p8[1] << ", " << p8[2] << ")" << std::endl;

    // 13. 测试/=运算符
    CPoint p9(10, 20, 30);
    p9 /= 2.0;
    std::cout << "13. /= operator test: p9 /= 2.0 = (" << p9[0] << ", " << p9[1] << ", " << p9[2] << ")" << std::endl;

    std::cout << "===== All tests completed =====" << std::endl;

    return 0;
}