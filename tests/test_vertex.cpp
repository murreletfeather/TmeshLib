#include "Mesh/Vertex.h"
#include "Mesh/HalfEdge.h"
#include "Mesh/Edge.h"
#include "Geometry/Point.h"
#include "Geometry/Point2.h"
#include <iostream>

int main() {
    std::cout << "===== Testing CVertex Class =====" << std::endl;

    // 1. 测试默认构造函数
    MeshLib::CVertex v;
    std::cout << "1. Default constructor test:" << std::endl;
    std::cout << "   Initial halfedge = " << v.halfedge() << " (expected: NULL)" << std::endl;
    std::cout << "   Initial boundary flag = " << v.boundary() << " (expected: false)" << std::endl;

    // 2. 测试坐标存取
    v.point() = CPoint(1.0, 2.0, 3.0);
    std::cout << "\n2. Point test: v.point() = (" 
              << v.point()[0] << ", " 
              << v.point()[1] << ", " 
              << v.point()[2] << ")" << std::endl;

    // 3. 测试法向存取
    v.normal() = CPoint(0.0, 0.0, 1.0);
    std::cout << "3. Normal test: v.normal() = (" 
              << v.normal()[0] << ", " 
              << v.normal()[1] << ", " 
              << v.normal()[2] << ")" << std::endl;

    // 4. 测试纹理坐标存取
    v.uv() = CPoint2(0.5, 0.5);
    std::cout << "4. UV test: v.uv() = (" 
              << v.uv()[0] << ", " 
              << v.uv()[1] << ")" << std::endl;

    // 5. 测试ID存取
    v.id() = 42;
    std::cout << "5. ID test: v.id() = " << v.id() << " (expected: 42)" << std::endl;

    // 6. 测试边界标记
    v.boundary() = true;
    std::cout << "6. Boundary flag test: v.boundary() = " << v.boundary() << " (expected: true)" << std::endl;
    v.boundary() = false;
    std::cout << "   After setting to false: v.boundary() = " << v.boundary() << " (expected: false)" << std::endl;

    // 7. 测试halfedge存取
    MeshLib::CHalfEdge he;
    v.halfedge() = &he;
    std::cout << "\n7. halfedge() test: stored halfedge address = " << v.halfedge() 
              << ", address of he = " << &he << std::endl;
    std::cout << "   They should match: " << (v.halfedge() == &he ? "PASS" : "FAIL") << std::endl;

    // 8. 测试字符串存取
    std::cout << "\n8. String attribute test:" << std::endl;
    v.string() = "test_attribute";
    std::cout << "   v.string() = \"" << v.string() << "\"" << std::endl;

    // 9. 创建几个顶点和半边验证CCW旋转概念（一个简单三角案例）
    std::cout << "\n9. Testing halfedge direction concept:" << std::endl;
    MeshLib::CVertex v1, v2, v3;
    MeshLib::CEdge  e1, e2, e3;
    MeshLib::CHalfEdge h1, h2, h3, h1t, h2t, h3t;

    // 设置简单三角形：v1->v2, v2->v3, v3->v1
    h1.edge() = &e1; h1.target() = &v2; // h1 v1->v2
    h2.edge() = &e2; h2.target() = &v3; // h2 v2->v3
    h3.edge() = &e3; h3.target() = &v1; // h3 v3->v1
    
    // 反向半边：v2->v1, v3->v2, v1->v3
    h1t.edge() = &e1; h1t.target() = &v1; // v2->v1
    h2t.edge() = &e2; h2t.target() = &v2; // v3->v2
    h3t.edge() = &e3; h3t.target() = &v3; // v1->v3

    // 必须设置he_prev和he_next，否则source()访问m_prev会段错误
    // source() = m_prev->vertex()
    h1.he_prev() = &h3;  // v3->v1 is h3, so before h1 (v1->v2) is h3
    h1.he_next() = &h2;  // 三角形顺序正确：h1->next = h2, h2->next = h3, h3->next = h1
    h2.he_prev() = &h1;
    h2.he_next() = &h3;
    h3.he_prev() = &h2;
    h3.he_next() = &h1;
    
    // 对称半边：对于h3t (v1->v3), 前一个是什么？
    // v1 -> v2, v2 -> v1, 所以顺序是: h1t( v2 ->v1 ) -> h3t (v1->v3 )
    h1t.he_prev() = &h2t;
    h1t.he_next() = &h3t;
    h2t.he_prev() = &h3t;
    h2t.he_next() = &h1t;
    h3t.he_prev() = &h1t;
    h3t.he_next() = &h2t;

    // 设置边的两个半边，CEdge没有set方法，直接用halfedge(index)
    e1.halfedge(0) = &h1;
    e1.halfedge(1) = &h1t;
    e2.halfedge(0) = &h2;
    e2.halfedge(1) = &h2t;
    e3.halfedge(0) = &h3;
    e3.halfedge(1) = &h3t;

    // 设置顶点v1的入半边为h3 (h3 -> v1)
    v1.halfedge() = &h3;
    std::cout << "   For v1 in triangle, m_halfedge is h3, which has target = v1" << std::endl;
    std::cout << "   So m_halfedge is indeed an 'in halfedge' (入半边) to v1" << std::endl;
    
    // 获取最CCW入半边，内部顶点直接返回m_halfedge
    MeshLib::CHalfEdge* ccw_in = v1.most_ccw_in_halfedge();
    std::cout << "   v1.most_ccw_in_halfedge() = " << ccw_in << " (expected same as m_halfedge " << &h3 << ")" << std::endl;
    std::cout << "   Check: " << (ccw_in == v1.halfedge() ? "PASS" : "FAIL") << ", internal vertex returns stored m_halfedge directly" << std::endl;

    // 获取最CCW出半边，就是h3->he_sym()
    MeshLib::CHalfEdge* ccw_out = v1.most_ccw_out_halfedge();
    std::cout << "   v1.most_ccw_out_halfedge() = " << ccw_out << " (expected: " << h3.he_sym() << ")" << std::endl;
    std::cout << "   Check: " << (ccw_out == h3.he_sym() ? "PASS" : "FAIL") << ", most ccw out is sym of most ccw in" << std::endl;

    // 必须给对称半边h3t也设置好he_prev
    h3t.he_prev() = &h2t;
    // 验证出半边源顶点就是v1
    if (ccw_out != nullptr) {
        std::cout << "   ccw_out->source() = " << ccw_out->source() << " (expected address of v1 " << &v1 << ")" << std::endl;
        std::cout << "   Check: " << (ccw_out->source() == &v1 ? "PASS" : "FAIL") << ", out halfedge has source = v1" << std::endl;
        std::cout << "   Which confirms that m_halfedge is an in halfedge (入半边)" << std::endl;
    }

    // 10. Test boundaries
    std::cout << "\n10. Boundary vertex test:" << std::endl;
    v1.boundary() = true;
    std::cout << "   After setting v1.boundary() = true, most_ccw_in_halfedge() will search until NULL" << std::endl;
    // 对于这个简单案例，边界处理也能正常工作
    ccw_in = v1.most_ccw_in_halfedge();
    std::cout << "   Result: v1.most_ccw_in_halfedge() = " << ccw_in << std::endl;

    std::cout << "\n===== All CVertex tests completed =====" << std::endl;

    return 0;
}
