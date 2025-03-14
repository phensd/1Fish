#pragma once
#include "compile.h"
#include <stack>
void run(std::vector<operation>& ops,std::stack<int>& stack);
void show_stack(std::stack<int> st);