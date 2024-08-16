#include <iostream>
#include <locale>
#include <unordered_map>

int main()
{
    std::unordered_map<char, char> p;
    std::unordered_map<long, char> q;

    std::cout.imbue(std::locale("en_US.UTF-8"));
    std::cout << std::uppercase<< "p.max_size() = " << std::dec << p.max_size() << " = 0x"<< std::hex << p.max_size() << '\n'<< "q.max_size() = " << std::dec << q.max_size() << " = 0x"<< std::hex << q.max_size() << '\n';
}