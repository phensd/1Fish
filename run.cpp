#include "compile.h"
#include <climits>
#include <cmath>
#include <iostream>
#include <stack>

int pop_and_get(std::stack<int>& st){
    if(st.empty()){
        std::cerr << "\nRuntime error: stack was accessed while empty.\n";
        std::exit(1);
    }
    int r = st.top();
    st.pop();
    return r;
}

std::stack<int> reverse_stack(std::stack<int>& stack){
    auto stack_clone = stack;
    while(!stack.empty()){
        stack.pop();
    }
    while(!stack_clone.empty()){
        stack.push(stack_clone.top());
        stack_clone.pop();
    }
    return stack;
}

std::pair<int,int> stack_expect(std::stack<int>& st){
    if(st.size() < 2){
        std::cerr << "\nRuntime error: Expected atleast " << "2" << " stack values, got " << st.size() << ". (Did you express in postfix notation? You must write it out like (1 2 +), not (1 + 2).\n";
        std::exit(1);
    }
    auto x {pop_and_get(st)};
    auto y {pop_and_get(st)};
    return std::make_pair(y,x);
}


void run(std::vector<operation>& ops,std::stack<int>& stack){
    for(size_t i {0}; i < ops.size(); ++i){
        switch(ops.at(i).type){
            case PUSH: {
                stack.push(ops.at(i).val);
            }
            break;
            case ADD: {
                auto pr = stack_expect(stack);
                stack.push(pr.first + pr.second);
            }
            break;

            case MUL: {
                auto pr = stack_expect(stack);
                stack.push(pr.first * pr.second);
            }
            break;

            case EQUALS:{
                auto pr = stack_expect(stack);
                stack.push(pr.first == pr.second);
            }
            break;

            case GREATER_THAN:{
                auto pr = stack_expect(stack);
                stack.push(pr.first > pr.second);
            }
            break;

            case LESS_THAN:{
                auto pr = stack_expect(stack);
                stack.push(pr.first < pr.second);
            }
            break;

            case SHOW_TOP_STACK_NUM:
                std::cout << pop_and_get(stack);
            break;

            case SHOW_TOP_STACK_CHAR:
                std::cout << (char) pop_and_get(stack);
            break;

            case POWER:{
                auto pr = stack_expect(stack);
                stack.push(std::pow(pr.first,pr.second));
            }
            break;
            case FLOOR_DIV:{
                auto pr = stack_expect(stack);
                stack.push(pr.first / pr.second);
            }
            break;
            case SUBTRACT:{
                auto pr = stack_expect(stack);
                stack.push(pr.first - pr.second);
            }
            break;
            
            //we skip over a loop if the stack is empty
            case LOOP_OPEN:{
                if(stack.empty()){
                    while(ops.at(i).type != LOOP_CLOSE){
                        ++i;
                    }
                }

            }
            break;

            case LOOP_CLOSE:{
                //repeat the code that the loop surrounds until the stack is empty
                if(!stack.empty()){
                    while(ops.at(i).type != LOOP_OPEN){
                        i--;
                    }
                }
            }
            break;


            case COND_OPEN:{
                if(stack.empty() || pop_and_get(stack)  != 0){
                    while(ops.at(i).type != COND_CLOSE){
                        ++i;
                    }

                }
            }
            break;

            case COND_CLOSE: break;


            case MOD:{
                auto pr = stack_expect(stack);
                stack.push(pr.first % pr.second);
            }
            break;

            case CHINPUT:{
                char c;
                std::cin >> c;
                stack.push((int)c);
                std::cin.clear(); std::cin.ignore(INT_MAX,'\n'); 
            }
            break;


            case REVERSE_STACK:{
                if(!stack.empty()){
                    stack = reverse_stack(stack);
                }
            }
            break;


            case JUMP:{
                auto x = (pop_and_get(stack));
                if(x > ops.size()){
                    std::cerr << "\nRuntime error: Counter was instructed to go further than operation count. \n";
                    std::exit(1);
                }
                if(x < 0){
                    std::cerr << "\nRuntime error: Counter was instructed to go below 0.. \n";
                    std::exit(1);
                }

                i = x-2;

            }
            break;

            case DUPSTACK:{
                auto val = ops.at(i).val;
                if(val == -1){
                    auto x = pop_and_get(stack);
                    stack.push(x);
                    stack.push(x);
                }
                if(val == -2){
                    auto clone {reverse_stack(stack)};
                    while(!clone.empty()){
                        stack.push(pop_and_get(clone));
                    }
                }

            }
            break;

            case DISCRD:{
                pop_and_get(stack);
            }  
            break;

            case RMST:{
                while(!stack.empty()){
                    stack.pop();
                }
            }
            break;

            case PUSHLNST:{
                stack.push(stack.size());
            }
            break;

            case SWPST:{
                auto xy = stack_expect(stack);
                stack.push(xy.second);
                stack.push(xy.first);
            }  
            break;

            default:
                std::cerr << "Unimplemented instruction " << std::quoted(std::to_string(ops.at(i).type)) << '\n';
                std::cerr << "Instruction counter was at " << i << ".\n";
                std::exit(1);
            break;

        }

    }
    
}

void show_stack(std::stack<int> st){
    size_t pos {0};
    std::cerr << '\n';
    while(!st.empty()){
        std::cerr << "Stack at: " << pos << " = " << st.top() << '\n';
        st.pop();
        pos++;
    }
}
