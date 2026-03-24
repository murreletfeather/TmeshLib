#include <iostream>
#include <cassert>
#include "Mesh/Face.h"
#include "Mesh/HalfEdge.h"

using namespace std;
using namespace MeshLib;

// 测试CFace类基本功能
int main()
{
    cout << "========================================" << endl;
    cout << "Testing CFace functions" << endl;
    cout << "========================================" << endl;

    // 测试1: 构造函数，默认halfedge为NULL
    cout << "\nTesting constructor..." << endl;
    CFace face;
    assert(face.halfedge() == NULL);
    cout << "  Default constructor passed, halfedge is NULL" << endl;

    // 测试2: halfedge访问测试
    cout << "\nTesting halfedge access..." << endl;
    CHalfEdge he;
    face.halfedge() = &he;
    assert(face.halfedge() == &he);
    cout << "  halfedge() access and assignment passed" << endl;

    // 测试3: ID访问测试
    cout << "\nTesting ID access..." << endl;
    int test_id = 123;
    face.id() = test_id;
    assert(face.id() == test_id);
    // 测试const版本
    const CFace &const_face = face;
    assert(const_face.id() == test_id);
    cout << "  id() (mutable and const) access passed, id = " << face.id() << endl;

    // 测试4: string属性测试
    cout << "\nTesting string attribute..." << endl;
    string test_str = "Face test custom attribute";
    face.string() = test_str;
    assert(face.string() == test_str);
    cout << "  string attribute storage passed: '" << face.string() << "'" << endl;

    // 测试5: _from_string和_to_string默认实现为空，调用不会出错
    cout << "\nTesting _from_string/_to_string default implementation..." << endl;
    face._from_string();
    face._to_string();
    cout << "  Default implementations called successfully" << endl;

    cout << "\n========================================" << endl;
    cout << "All tests passed successfully!" << endl;
    cout << "========================================" << endl;

    return 0;
}