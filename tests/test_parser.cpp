#include <iostream>
#include "Parser/parser.h"

using namespace MeshLib;

int main()
{
    std::cout << "Testing CParser..." << std::endl;
    
    // 测试示例输入
    std::string input = "uv=(1.0 2.0) normal=(0.0 0.0 1.0) selected";
    std::cout << "Input string: " << input << std::endl;
    
    CParser parser(input);
    
    // 输出解析结果
    std::cout << "\nParsed tokens:" << std::endl;
    std::list<CToken*> &tokens = parser.tokens();
    for (std::list<CToken*>::iterator iter = tokens.begin(); iter != tokens.end(); ++iter)
    {
        CToken *token = *iter;
        if (token->m_value.empty())
        {
            std::cout << "Key: " << token->m_key << ", (no value)" << std::endl;
        }
        else
        {
            std::cout << "Key: " << token->m_key << ", Value: " << token->m_value << std::endl;
        }
    }
    
    // 测试转换回字符串
    std::string output;
    parser._toString(output);
    std::cout << "\nConverted back to string: " << output << std::endl;
    
    // 测试删除标记
    std::cout << "\nRemoving token 'uv'..." << std::endl;
    parser._removeToken("uv");
    parser._toString(output);
    std::cout << "After removal: " << output << std::endl;
    
    std::cout << "\nTest completed successfully!" << std::endl;
    
    return 0;
}