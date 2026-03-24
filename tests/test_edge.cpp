#include <iostream>
#include <cassert>
#include "Mesh/Edge.h"
#include "Mesh/HalfEdge.h"
#include "Mesh/Vertex.h"

using namespace std;
using namespace MeshLib;

// 测试CEdge类基本功能
int main()
{
    cout << "========================================" << endl;
    cout << "Testing CEdge functions" << endl;
    cout << "========================================" << endl;

    // 测试1: 构造函数，默认两个半边都为NULL
    cout << "\nTesting constructor..." << endl;
    CEdge edge;
    assert(edge.halfedge(0) == NULL);
    assert(edge.halfedge(1) == NULL);
    // 两个都是NULL，不算边界边（边界边只一个NULL）
    assert(!edge.boundary());
    cout << "  Default constructor passed, both halfedges are NULL" << endl;

    // 测试2: 设置半边索引测试
    cout << "\nTesting halfedge access..." << endl;
    CHalfEdge he0, he1;
    edge.halfedge(0) = &he0;
    edge.halfedge(1) = &he1;
    assert(edge.halfedge(0) == &he0);
    assert(edge.halfedge(1) == &he1);
    cout << "  halfedge(0) and halfedge(1) access passed" << endl;

    // 测试3: boundary测试
    cout << "\nTesting boundary check..." << endl;
    // 两个半边都存在，不是边界
    assert(!edge.boundary());
    cout << "  Internal edge (two halfedges) correctly not boundary" << endl;
    
    // 只有halfedge[0]，是边界
    edge.halfedge(1) = NULL;
    assert(edge.boundary());
    cout << "  Boundary edge (one halfedge) correctly detected" << endl;
    
    // 只有halfedge[1]，也是边界
    edge.halfedge(0) = NULL;
    edge.halfedge(1) = &he1;
    assert(edge.boundary());
    cout << "  Boundary edge (one halfedge on index 1) correctly detected" << endl;
    
    // 恢复两个半边
    edge.halfedge(0) = &he0;
    edge.halfedge(1) = &he1;

    // 测试4: other获取对偶半边
    cout << "\nTesting other() function..." << endl;
    assert(edge.other(&he0) == &he1);
    assert(edge.other(&he1) == &he0);
    cout << "  other() correctly returns the opposite halfedge" << endl;

    // 测试5: string属性测试
    cout << "\nTesting string attribute..." << endl;
    string test_str = "Edge test custom attribute";
    edge.string() = test_str;
    assert(edge.string() == test_str);
    cout << "  string attribute storage passed: '" << edge.string() << "'" << endl;

    // 测试6: _from_string和_to_string默认实现为空，调用不会出错
    cout << "\nTesting _from_string/_to_string default implementation..." << endl;
    edge._from_string();
    edge._to_string();
    cout << "  Default implementations called successfully" << endl;

    cout << "\n========================================" << endl;
    cout << "All tests passed successfully!" << endl;
    cout << "========================================" << endl;

    return 0;
}