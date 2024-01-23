#include "hello.hpp"

void Hello::print()
{
    spdlog::info("welcome");
    std::cout<<"hello\n";
}