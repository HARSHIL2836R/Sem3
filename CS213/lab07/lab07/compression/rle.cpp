#include "rle.h"

// Constructor
rle::rle(int gamma): gamma(gamma){}

// Convert integer to gamma-bit binary string
string rle::f(int i)
{
    string s;
    while (i > 0)
    {
        s = std::to_string(i % 2) + s;
        i >>= 1;
    }
    return s;
}

// Convert gamma-bit binary string to integer
int rle::g(string i)
{ 
    int res = 0;
    for (auto ch: i){
        res <<= 1;
        res += (ch == '1');
    }
    return res;
}

// Compress the input file
string rle::compress_old(string input_string)
{ 
    int i = 0;
    string res = "";
    char ch = input_string[i];
    while (i<input_string.length()){
        int count = 1;
        while (input_string[++i] == ch){
            count++;
        }
        res.append(1,ch);
        res.append(1, count+'0');
        ch = input_string[i];
    }
    return res;
}
string rle::compress(string input_string)
{ 
    int i = 0;
    string res = "";
    char ch = input_string[i];
    while (i<input_string.length()){
        int count = 1;
        while (input_string[++i] == ch){
            count++;
        }
        res.append(1,ch);
        res.append(1, count+'0');
        ch = input_string[i];
    }
    return res;
}

// Decompress the input file
string rle::decompress_old(string input_string)
{
    string res = "";
    for (int i = 0; i < input_string.length();i++){
        char ch = input_string[i];
        res.append(input_string[++i]-'0',ch);
    }
    return res;
}
string rle::decompress(string input_string)
{
    string res = "";
    for (int i = 0; i < input_string.length();i++){
        char ch = input_string[i];
        res.append(input_string[++i]-'0',ch);
    }
    return res;
}

/* int main(){
    rle rle_obj(2);
    std::cout << rle_obj.f(10) << std::endl; // Output: 1010
    std::cout << rle_obj.g("1010") << std::endl; // Output: 10
    std::cout << rle_obj.compress("1000111100") << std::endl; // Output: 11031402
    std::cout << rle_obj.decompress("11031402") << std::endl; // Output: 1000111100
} */