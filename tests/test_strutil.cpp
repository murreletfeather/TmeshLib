#include <iostream>
#include <cassert>
#include "Parser/StrUtil.h"

using namespace strutil;

void test_trim()
{
    std::cout << "Testing trim functions..." << std::endl;
    
    // 测试 trimLeft
    std::string s1 = "   hello world";
    std::string s1_trim = trimLeft(s1);
    assert(s1_trim == "hello world");
    std::cout << "  trimLeft passed: '" << s1 << "' -> '" << s1_trim << "'" << std::endl;
    
    // 测试 trimRight
    std::string s2 = "hello world   ";
    std::string s2_trim = trimRight(s2);
    assert(s2_trim == "hello world");
    std::cout << "  trimRight passed: '" << s2 << "' -> '" << s2_trim << "'" << std::endl;
    
    // 测试 trim
    std::string s3 = "   hello world   ";
    std::string s3_trim = trim(s3);
    assert(s3_trim == "hello world");
    std::cout << "  trim passed: '" << s3 << "' -> '" << s3_trim << "'" << std::endl;
    
    // 测试带自定义分隔符的trim
    std::string s4 = "###hello world###";
    std::string s4_trim = trim(s4, "#");
    assert(s4_trim == "hello world");
    std::cout << "  trim (custom delimiter) passed: '" << s4 << "' -> '" << s4_trim << "'" << std::endl;
    
    std::cout << "  All trim tests passed!\n" << std::endl;
}

void test_case_conversion()
{
    std::cout << "Testing case conversion..." << std::endl;
    
    std::string s = "Hello World";
    std::string lower = toLower(s);
    std::string upper = toUpper(s);
    
    assert(lower == "hello world");
    assert(upper == "HELLO WORLD");
    
    std::cout << "  toLower passed: '" << s << "' -> '" << lower << "'" << std::endl;
    std::cout << "  toUpper passed: '" << s << "' -> '" << upper << "'" << std::endl;
    std::cout << "  All case conversion tests passed!\n" << std::endl;
}

void test_starts_ends_with()
{
    std::cout << "Testing startsWith and endsWith..." << std::endl;
    
    std::string s = "hello world";
    
    // 测试 startsWith
    assert(startsWith(s, "hello") == true);
    assert(startsWith(s, "hell") == true);
    assert(startsWith(s, "world") == false);
    assert(startsWith(s, "hello world") == true);
    assert(startsWith(s, "hello world!") == false); // 子串更长
    assert(startsWith("", "h") == false); // 空字符串
    assert(startsWith("h", "") == true); // 空子串
    
    std::cout << "  startsWith all assertions passed" << std::endl;
    
    // 测试 endsWith
    assert(endsWith(s, "world") == true);
    assert(endsWith(s, "ld") == true);
    assert(endsWith(s, "hello") == false);
    assert(endsWith(s, "hello world") == true);
    assert(endsWith(s, "!hello world") == false); // 子串更长
    assert(endsWith("", "h") == false); // 空字符串
    assert(endsWith("h", "") == true); // 空子串
    
    std::cout << "  endsWith all assertions passed" << std::endl;
    std::cout << "  All startsWith/endsWith tests passed!\n" << std::endl;
}

void test_equals_ignore_case()
{
    std::cout << "Testing equalsIgnoreCase..." << std::endl;
    
    assert(equalsIgnoreCase("Hello", "hello") == true);
    assert(equalsIgnoreCase("HELLO", "hello") == true);
    assert(equalsIgnoreCase("World", "world") == true);
    assert(equalsIgnoreCase("Hello", "world") == false);
    assert(equalsIgnoreCase("", "") == true);
    assert(equalsIgnoreCase("", "a") == false);
    
    std::cout << "  All equalsIgnoreCase tests passed!\n" << std::endl;
}

void test_conversion()
{
    std::cout << "Testing string conversion..." << std::endl;
    
    // bool
    assert(toString(true) == "true");
    assert(toString(false) == "false");
    assert(parseString<bool>("true") == true);
    assert(parseString<bool>("false") == false);
    
    // int
    assert(toString(42) == "42");
    assert(parseString<int>("42") == 42);
    assert(parseString<int>("-123") == -123);
    
    // double
    assert(toString(3.14159).find("3.14159") != std::string::npos);
    assert(parseString<double>("3.14159") > 3.14 && parseString<double>("3.14159") < 3.15);
    
    // hex
    std::string hex_str = "FF";
    int value = parseHexString<int>(hex_str);
    assert(value == 255);
    std::cout << "  parseHexString passed: 0x" << hex_str << " = " << value << std::endl;
    
    std::string hex_output = toHexString(255, 2);
    assert(hex_output == "ff");
    std::cout << "  toHexString passed: " << 255 << " -> 0x" << hex_output << std::endl;
    
    std::cout << "  All conversion tests passed!\n" << std::endl;
}

void test_tokenizer()
{
    std::cout << "Testing Tokenizer..." << std::endl;
    
    std::string s = "hello world  123  456";
    Tokenizer tokenizer(s);
    
    int count = 0;
    while (tokenizer.nextToken())
    {
        count++;
        std::cout << "    Token " << count << ": '" << tokenizer.getToken() << "'" << std::endl;
    }
    assert(count == 4);
    
    // 测试自定义分隔符
    std::string s2 = "one,two,three,four";
    Tokenizer tokenizer2(s2, ",");
    count = 0;
    while (tokenizer2.nextToken())
    {
        count++;
    }
    assert(count == 4);
    std::cout << "  Tokenizer with custom delimiter passed, got " << count << " tokens" << std::endl;
    
    // 测试reset
    tokenizer.reset();
    count = 0;
    while (tokenizer.nextToken())
    {
        count++;
    }
    assert(count == 4);
    std::cout << "  reset passed" << std::endl;
    
    std::cout << "  All Tokenizer tests passed!\n" << std::endl;
}

void test_split()
{
    std::cout << "Testing split..." << std::endl;
    
    std::string s = "hello world  test split";
    std::vector<std::string> tokens = split(s, " ");
    
    assert(tokens.size() == 4);
    assert(tokens[0] == "hello");
    assert(tokens[1] == "world");
    assert(tokens[2] == "test");
    assert(tokens[3] == "split");
    
    for (size_t i = 0; i < tokens.size(); i++)
    {
        std::cout << "    Split token " << i + 1 << ": '" << tokens[i] << "'" << std::endl;
    }
    
    // 测试逗号分隔
    std::string s2 = "apple,banana,orange,grape";
    std::vector<std::string> tokens2 = split(s2, ",");
    assert(tokens2.size() == 4);
    assert(tokens2[0] == "apple");
    assert(tokens2[3] == "grape");
    
    std::cout << "  All split tests passed!\n" << std::endl;
}

void test_edge_cases()
{
    std::cout << "Testing edge cases..." << std::endl;
    
    // 空字符串
    assert(trim("") == "");
    assert(trimLeft("") == "");
    assert(trimRight("") == "");
    
    // 全空白字符
    assert(trim("   \t\n  ") == "");
    
    // 单个字符
    assert(trim(" a ") == "a");
    
    std::cout << "  All edge case tests passed!\n" << std::endl;
}

int main()
{
    std::cout << "========================================" << std::endl;
    std::cout << "Testing StrUtil functions" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    test_trim();
    test_case_conversion();
    test_starts_ends_with();
    test_equals_ignore_case();
    test_conversion();
    test_tokenizer();
    test_split();
    test_edge_cases();
    
    std::cout << "========================================" << std::endl;
    std::cout << "All tests passed successfully!" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}