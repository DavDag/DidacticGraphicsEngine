module;
#include <format>
export module main;

import engine;

export
int main(int, const char** argv)
{
    LogInfo("OpenGL Sample App started: {}", argv[0]);
    return 0;
}
