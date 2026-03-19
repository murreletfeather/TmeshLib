#include "Geometry/Point2.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    cout << "===== Testing CPoint2 Class =====\n" << endl;

    // 1. 构造函数测试
    CPoint2 p1(1, 2);
    cout << "1. Constructor test: p1 = (" << p1[0] << ", " << p1[1] << ")\n";
    CPoint2 p2 = p1;
    cout << "   Copy constructor test: p2 = (" << p2[0] << ", " << p2[1] << ")\n";

    // 2. 默认构造函数测试
    CPoint2 p0;
    cout << "2. Default constructor test: p0 = (" << p0[0] << ", " << p0[1] << ")\n";

    // 3. 数乘测试
    CPoint2 p3 = 2.0 * p1;
    cout << "3. Scalar multiply test (2.0 * p1): p3 = (" << p3(0) << ", " << p3(1) << ")\n";

    // 4. 加法测试
    CPoint2 p4 = p1 + p3;
    cout << "4. Addition test (p1 + p3): p4 = (" << p4(0) << ", " << p4(1) << ")\n";

    // 5. 减法测试
    CPoint2 p5 = p3 - p1;
    cout << "5. Subtraction test (p3 - p1): p5 = (" << p5(0) << ", " << p5(1) << ")\n";

    // 6. 一元取反测试
    CPoint2 p6 = -p1;
    cout << "6. Unary minus test (-p1): p6 = (" << p6(0) << ", " << p6(1) << ")\n";

    // 7. 点积测试
    double dot = p1 * p3;
    cout << "7. Dot product test (p1 * p3): " << dot << " (expected: 1*2 + 2*4 = 10)\n";

    // 8. 叉积测试
    CPoint2 p7(3, 4);
    double cross_val = p1 ^ p7;
    cout << "8. Cross product test (p1 ^ p7): " << cross_val << " (expected: 1*4 - 2*3 = -2)\n";

    // 9. norm 和 norm2 测试
    double n = p1.norm();
    double n2 = p1.norm2();
    cout << "9. Norm test: |p1| = " << n << ", |p1|^2 = " << n2 << " (expected: sqrt(5) ≈ 2.236, 5)\n";

    // 10. 相等比较
    bool eq = (p1 == p2);
    cout << "10. Equality test (p1 == p2): " << (eq ? "true" : "false") << " (expected: true)\n";
    CPoint2 p8(2, 3);
    eq = (p1 == p8);
    cout << "    p1 == (2,3): " << (eq ? "true" : "false") << " (expected: false)\n";

    // 11. 全局mag2, mag 测试
    double gmag2 = mag2(p1);
    double gmag = mag(p1);
    cout << "11. Global mag2/mag test: mag2=" << gmag2 << " mag=" << gmag << "\n";

    // 12. 复合运算符测试
    CPoint2 p9(1, 2);
    p9 += p1;
    cout << "12. += operator test: p9 += p1 = (" << p9[0] << ", " << p9[1] << ")\n";

    CPoint2 p10(2, 3);
    p10 *= 2.5;
    cout << "13. *= operator test: p10 *= 2.5 = (" << p10[0] << ", " << p10[1] << ")\n";

    CPoint2 p11(10, 20);
    p11 /= 2.0;
    cout << "14. /= operator test: p11 /= 2.0 = (" << p11[0] << ", " << p11[1] << ")\n";

    cout << "\n===== All tests completed =====\n";
    return 0;
}