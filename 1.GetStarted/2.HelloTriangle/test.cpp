//
// Created by 10578 on 2021/4/27.
//

#include "iostream"
#include "string"
#include "fmt/core.h"

using namespace std;

int main(){
    string s = fmt::format("this {}.", 42);
    cout << s << endl;

    const string s1 = fmt::format(R"(
        #version 460 core
        out vec4 FragColor;
        void main(){{
            FragColor = vec4({}f, {}f, {}f, 1.0f);)", 2 / 255.0, 1 / 255.0, 3 / 255.0);
    cout << s1 << endl;

//    const string fragmentShaderSourceStr = fmt::format(R"(
//        #version 460 core
//        out vec4 FragColor;
//        void main(){
//           FragColor = vec4({}f, {}f, {}f, 1.0f);
//        }
//)", 2 / 255.0, 1 / 255.0, 3 / 255.0);
//    cout << fragmentShaderSourceStr << endl;

    cout << _MSC_VER << endl;
    return 0;
}
