#include <iostream>
#include <cassert>
#include "Mesh/HalfEdge.h"
#include "Mesh/Edge.h"

using namespace std;
using namespace MeshLib;

// 简单测试CHalfEdge类基本功能
int main()
{
    cout << "========================================" << endl;
    cout << "Testing CHalfEdge functions" << endl;
    cout << "========================================" << endl;

    // 测试1: 构造函数
    cout << "Testing constructor..." << endl;
    CHalfEdge he;
    assert(he.edge() == nullptr);
    assert(he.vertex() == nullptr);
    assert(he.he_prev() == nullptr);
    assert(he.he_next() == nullptr);
    assert(he.face() == nullptr);
    cout << "  Default constructor passed, all pointers are NULL" << endl;

    // 测试2: 指针赋值测试
    cout << "Testing pointer access..." << endl;
    CEdge edge;
    CHalfEdge prev_he, next_he;

    he.edge() = &edge;
    he.he_prev() = &prev_he;
    he.he_next() = &next_he;

    assert(he.edge() == &edge);
    assert(he.he_prev() == &prev_he);
    assert(he.he_next() == &next_he);
    cout << "  All pointer accessors passed" << endl;

    // 测试3: 对偶半边测试
    cout << "Testing he_sym()..." << endl;
    edge.halfedge(0) = &he;
    edge.halfedge(1) = &next_he;
    assert(he.he_sym() == &next_he);
    assert(next_he.he_sym() == &he);
    cout << "  he_sym() correctly returns opposite halfedge" << endl;

    // 测试4: 旋转函数边界情况
    cout << "Testing rotation boundary case..." << endl;
    // he_sym是null的时候ccw_rotate应该返回null
    edge.halfedge(1) = nullptr;
    assert(he.ccw_rotate_about_target() == nullptr);
    assert(he.clw_rotate_about_source() == nullptr);
    cout << "  Boundary null checks passed" << endl;

    // 测试5: string属性测试
    cout << "Testing string attribute..." << endl;
    he.string() = "HalfEdge test";
    assert(he.string() == "HalfEdge test");
    cout << "  String attribute passed" << endl;

    cout << "\n========================================" << endl;
    cout << "All tests passed successfully!" << endl;
    cout << "========================================" << endl;

    return 0;
}