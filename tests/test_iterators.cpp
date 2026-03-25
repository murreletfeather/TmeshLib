/**
 * @file test_iterators.cpp
 * @brief 测试网格迭代器功能
 * @author 
 * @date 2026
 */

#include <iostream>
#include "Geometry/Point.h"
#include "Mesh/BaseMesh.h"
#include "Mesh/Vertex.h"
#include "Mesh/Edge.h"
#include "Mesh/Face.h"
#include "Mesh/HalfEdge.h"
#include "Mesh/iterators.h"

// 使用标准网格类型定义
typedef MeshLib::CBaseMesh<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge>  Mesh;

/**
 * @brief 创建一个简单的三角形网格用于测试
 * @return 返回创建的网格指针
 */
Mesh* createTriangleMesh() {
    Mesh* mesh = new Mesh();
    
    // 使用CBaseMesh提供的API创建三角形
    // 创建三个顶点，ID从1开始
    MeshLib::CVertex* v1 = mesh->createVertex(1);
    MeshLib::CVertex* v2 = mesh->createVertex(2);
    MeshLib::CVertex* v3 = mesh->createVertex(3);
    
    // 设置顶点坐标
    v1->point() = CPoint(0, 0, 0);
    v2->point() = CPoint(1, 0, 0);
    v3->point() = CPoint(0, 1, 0);
    
    // 创建一个三角形面
    MeshLib::CVertex* vertices[3] = {v1, v2, v3};
    mesh->createFace(vertices, 1);
    
    // 标记边界，CBaseMesh会自动处理
    mesh->labelBoundary();
    
    return mesh;
}

/**
 * @brief 测试Mesh整体迭代器：顶点、边、面、半边遍历
 */
bool testMeshIterators() {
    std::cout << "Testing Mesh global iterators..." << std::endl;
    
    Mesh* mesh = createTriangleMesh();
    
    // 测试 MeshVertexIterator
    int vertexCount = 0;
    for (MeshLib::MeshVertexIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(mesh); !it.end(); ++it) {
        MeshLib::CVertex* v = *it;
        std::cout << "  Vertex found: " << v->id() << std::endl;
        vertexCount++;
    }
    if (vertexCount != 3) {
        std::cerr << "  FAIL: Expected 3 vertices, got " << vertexCount << std::endl;
        delete mesh;
        return false;
    }
    std::cout << "  MeshVertexIterator PASS: " << vertexCount << " vertices found" << std::endl;
    
    // 测试 MeshFaceIterator
    int faceCount = 0;
    for (MeshLib::MeshFaceIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(mesh); !it.end(); ++it) {
        MeshLib::CFace* f = *it;
        std::cout << "  Face found: " << f->id() << std::endl;
        faceCount++;
    }
    if (faceCount != 1) {
        std::cerr << "  FAIL: Expected 1 face, got " << faceCount << std::endl;
        delete mesh;
        return false;
    }
    std::cout << "  MeshFaceIterator PASS: " << faceCount << " face found" << std::endl;
    
    // 测试 MeshEdgeIterator
    int edgeCount = 0;
    for (MeshLib::MeshEdgeIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(mesh); !it.end(); ++it) {
        MeshLib::CEdge* e = *it;
        (void)e;  // 抑制未使用警告
        std::cout << "  Edge found" << std::endl;
        edgeCount++;
    }
    if (edgeCount != 3) {
        std::cerr << "  FAIL: Expected 3 edges, got " << edgeCount << std::endl;
        delete mesh;
        return false;
    }
    std::cout << "  MeshEdgeIterator PASS: " << edgeCount << " edges found" << std::endl;
    
    // 测试 MeshHalfEdgeIterator
    int heCount = 0;
    for (MeshLib::MeshHalfEdgeIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(mesh); !it.end(); ++it) {
        MeshLib::CHalfEdge* he = *it;
        (void)he;  // 抑制未使用警告
        std::cout << "  HalfEdge found" << std::endl;
        heCount++;
    }
    if (heCount != 3) {
        std::cerr << "  FAIL: Expected 3 halfedges (one per face corner), got " << heCount << std::endl;
        delete mesh;
        return false;
    }
    std::cout << "  MeshHalfEdgeIterator PASS: " << heCount << " halfedges found" << std::endl;
    
    delete mesh;
    std::cout << "  All mesh global iterators test PASSED!" << std::endl;
    return true;
}

/**
 * @brief 测试Face相关迭代器：FaceHalfedgeIterator, FaceEdgeIterator, FaceVertexIterator
 */
bool testFaceIterators() {
    std::cout << "\nTesting Face iterators..." << std::endl;
    
    Mesh* mesh = createTriangleMesh();
    
    // 获取第一个面
    MeshLib::CFace* f = NULL;
    for (MeshLib::MeshFaceIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(mesh); !it.end() && f == NULL; ++it) {
        f = *it;
    }
    
    // 测试 FaceHalfedgeIterator
    int heCount = 0;
    for (MeshLib::FaceHalfedgeIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(f); !it.end(); ++it) {
        MeshLib::CHalfEdge* he = *it;
        (void)he;  // 抑制未使用警告
        std::cout << "  Face halfedge found" << std::endl;
        heCount++;
    }
    if (heCount != 3) {
        std::cerr << "  FAIL: Expected 3 halfedges on triangle, got " << heCount << std::endl;
        delete mesh;
        return false;
    }
    std::cout << "  FaceHalfedgeIterator PASS: " << heCount << " halfedges found" << std::endl;
    
    // 测试 FaceEdgeIterator
    int edgeCount = 0;
    for (MeshLib::FaceEdgeIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(f); !it.end(); ++it) {
        MeshLib::CEdge* e = *it;
        (void)e;  // 抑制未使用警告
        std::cout << "  Face edge found" << std::endl;
        edgeCount++;
    }
    if (edgeCount != 3) {
        std::cerr << "  FAIL: Expected 3 edges on triangle, got " << edgeCount << std::endl;
        delete mesh;
        return false;
    }
    std::cout << "  FaceEdgeIterator PASS: " << edgeCount << " edges found" << std::endl;
    
    // 测试 FaceVertexIterator
    int vertexCount = 0;
    for (MeshLib::FaceVertexIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(f); !it.end(); ++it) {
        MeshLib::CVertex* v = *it;
        std::cout << "  Face vertex found: " << v->id() << std::endl;
        vertexCount++;
    }
    if (vertexCount != 3) {
        std::cerr << "  FAIL: Expected 3 vertices on triangle, got " << vertexCount << std::endl;
        delete mesh;
        return false;
    }
    std::cout << "  FaceVertexIterator PASS: " << vertexCount << " vertices found" << std::endl;
    
    delete mesh;
    std::cout << "  All face iterators test PASSED!" << std::endl;
    return true;
}

/**
 * @brief 测试顶点相关迭代器
 */
bool testVertexIterators() {
    std::cout << "\nTesting Vertex iterators..." << std::endl;
    
    Mesh* mesh = createTriangleMesh();
    
    // 获取第一个顶点
    MeshLib::CVertex* v = NULL;
    for (MeshLib::MeshVertexIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(mesh); !it.end() && v == NULL; ++it) {
        v = *it;
    }
    
    // 在我们的三角形网格中，边界顶点应该有两个邻接顶点
    // 测试 VertexVertexIterator
    int vvCount = 0;
    for (MeshLib::VertexVertexIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(v); !it.end(); ++it) {
        MeshLib::CVertex* neighbor = *it;
        std::cout << "  Vertex neighbor found: " << neighbor->id() << std::endl;
        vvCount++;
    }
    std::cout << "  VertexVertexIterator: " << vvCount << " neighbors found (expected 2 for boundary vertex)" << std::endl;
    
    // 测试 VertexEdgeIterator
    int veCount = 0;
    for (MeshLib::VertexEdgeIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(v); !it.end(); ++it) {
        MeshLib::CEdge* edge = *it;
        (void)edge;  // 抑制未使用警告
        std::cout << "  Vertex edge found" << std::endl;
        veCount++;
    }
    if (veCount != vvCount) {
        std::cerr << "  FAIL: VertexEdgeCount != VertexVertexCount " << veCount << " != " << vvCount << std::endl;
        delete mesh;
        return false;
    }
    std::cout << "  VertexEdgeIterator PASS: " << veCount << " edges found" << std::endl;
    
    // 测试 VertexFaceIterator
    int vfCount = 0;
    for (MeshLib::VertexFaceIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(v); !it.end(); ++it) {
        MeshLib::CFace* face = *it;
        std::cout << "  Vertex face found: " << face->id() << std::endl;
        vfCount++;
    }
    // 对于三角形边界顶点，应该只有一个邻接面
    if (vfCount != 1) {
        std::cerr << "  FAIL: Expected 1 face on boundary vertex, got " << vfCount << std::endl;
        delete mesh;
        return false;
    }
    std::cout << "  VertexFaceIterator PASS: " << vfCount << " faces found" << std::endl;
    
    delete mesh;
    std::cout << "  All vertex iterators test PASSED!" << std::endl;
    return true;
}

/**
 * @brief 测试后缀++运算符
 */
bool testPostIncrement() {
    std::cout << "\nTesting postfix increment operator..." << std::endl;
    
    Mesh* mesh = createTriangleMesh();
    MeshLib::CFace* f = NULL;
    for (MeshLib::MeshFaceIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(mesh); !it.end() && f == NULL; ++it) {
        f = *it;
    }
    
    // 使用后缀++测试FaceVertexIterator
    int count = 0;
    for (MeshLib::FaceVertexIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(f); !it.end(); it++) {
        MeshLib::CVertex* v = *it;
        std::cout << "  Vertex found (postfix): " << v->id() << std::endl;
        count++;
    }
    
    if (count != 3) {
        std::cerr << "  FAIL: Expected 3 vertices, got " << count << std::endl;
        delete mesh;
        return false;
    }
    
    delete mesh;
    std::cout << "  Postfix increment test PASSED!" << std::endl;
    return true;
}

/**
 * @brief 测试reset功能
 */
bool testReset() {
    std::cout << "\nTesting iterator reset..." << std::endl;
    
    Mesh* mesh = createTriangleMesh();
    
    MeshLib::CVertex* v = NULL;
    for (MeshLib::MeshVertexIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(mesh); !it.end() && v == NULL; ++it) {
        v = *it;
    }
    
    MeshLib::VertexVertexIterator<MeshLib::CVertex, MeshLib::CEdge, MeshLib::CFace, MeshLib::CHalfEdge> it(v);
    
    int firstCount = 0;
    for (; !it.end(); ++it) {
        firstCount++;
    }
    std::cout << "  First traversal: " << firstCount << " vertices" << std::endl;
    
    it.reset();
    int secondCount = 0;
    for (; !it.end(); ++it) {
        secondCount++;
    }
    std::cout << "  Second traversal after reset: " << secondCount << " vertices" << std::endl;
    
    if (firstCount != secondCount) {
        std::cerr << "  FAIL: Counts don't match: " << firstCount << " != " << secondCount << std::endl;
        delete mesh;
        return false;
    }
    
    delete mesh;
    std::cout << "  Reset test PASSED!" << std::endl;
    return true;
}

int main() {
    std::cout << "===== TmeshLib Iterators Unit Test =====\n" << std::endl;
    
    bool allPassed = true;
    
    allPassed &= testMeshIterators();
    allPassed &= testFaceIterators();
    allPassed &= testVertexIterators();
    allPassed &= testPostIncrement();
    allPassed &= testReset();
    
    std::cout << "\n===== Test Summary =====" << std::endl;
    if (allPassed) {
        std::cout << "ALL TESTS PASSED! ✓" << std::endl;
        return 0;
    } else {
        std::cerr << "SOME TESTS FAILED! ✗" << std::endl;
        return 1;
    }
}