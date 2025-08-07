//
// Copyright (c) 2023 xiaozhuai
//

#include <cassert>
#include <codecvt>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "ucpp/codecvt_win32.hpp"

int main() {
    std::string file1 = "aaa测试 bbb啊啊.txt";
    std::string file2 = std::filesystem::u8path(file1).string();
    std::string file3 = ucpp::utf8_to_ansi(file1);
    std::string file4 = ucpp::utf16_to_utf8(ucpp::utf8_to_utf16(file1));
    std::wstring file5 = ucpp::utf8_to_utf16(file1);
    std::wstring file6 = std::filesystem::u8path(file1).wstring();

    assert(file1 == file4);
    assert(file2 == file3);
    assert(file5 == file6);

    // SetConsoleOutputCP(CP_UTF8);

    // std::cout << "file1: " << file1 << std::endl;
    // std::cout << "file2: " << file2 << std::endl;
    // std::cout << "file3: " << file3 << std::endl;
    // std::cout << "file4: " << file4 << std::endl;
    // std::wcout << "file5: " << file5 << std::endl;
    // std::wcout << "file6: " << file6 << std::endl;

    return 0;
}
