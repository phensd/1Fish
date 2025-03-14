#include <cmath>
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include "compile.h"

void show_op(operation& op){
    std::cerr << (int)op.type << "   " << op.val << '\n';
}


int base_10(std::vector<int> in){
    int sum;
    for(size_t i {0}; i < in.size(); ++i){
        sum += (in.at(i) * (0 + (std::pow(10,(in.size()-1)-i))));
    }
    return sum;
}

bool next_is(std::string& in, size_t& current, char p){
    if(current+1 >= in.size()) return false;
    return in.at(current+1) == p;
}

size_t find_next(std::string& in, size_t& current, char p){
    size_t ou = current;
    while(in.at(ou) != p){
        if(ou+1 >= in.size()) {
            break;
        }

        ou++;
    }
    return ou;
}

size_t find_next_non_digit(std::string& in, size_t& current){
    size_t ou = current;
    while((isdigit(in.at(ou)))){
        if(ou+1 >= in.size()) {
            break;
        }

        ou++;
    }
    return ou;
}

bool next_is_digit(std::string& in, size_t& current){
    if(current+1 >= in.size())return false;
    return isdigit(in.at(current+1)); 
}

bool match(std::string& in, size_t& current, char p, bool forwards){
    size_t i{current+1};

    if(forwards){
        while((in.at(i)) != p){
            if(i+1 >= in.size()) {
                return false;
            }
            i++;
        }
        return true;
    }else{
        while((in.at(i)) != p){
            if(i == 0) {
                return false;
            }
            i--;
        }
        return true;

    }
    
    return false;
}


std::vector<operation> compile(std::filesystem::path file){
    std::vector<operation> op_list{};


    size_t current{0};

    bool do_ascii {false};
    bool negate_next_num {false};

    std::string file_stream{};
    std::string line{};
    std::ifstream _file_handle(file);
    while(std::getline(_file_handle,line)){
        file_stream += line + "\n";
    }


    while(current < file_stream.size()){
    

        if(isdigit(file_stream.at(current)) && !do_ascii){
            if(!next_is(file_stream,current,' ')){
                std::vector<int> base;
                for(size_t i {current}; i < find_next_non_digit(file_stream, current); ++i){
                    base.push_back(file_stream.at(i) - '0');
                }
                operation op = {OP_TYPE::PUSH,base_10(base)};
                if(negate_next_num) op.val = -op.val;
                op_list.push_back(op);
                current = find_next_non_digit(file_stream, current);
                negate_next_num = false;
                continue;
            }else{
                operation op = {OP_TYPE::PUSH,file_stream.at(current) - '0'};
                if(negate_next_num) op.val = -op.val;
                op_list.push_back(op);
                current++;
                negate_next_num = false;
                continue;
            }
        
        }

        
        if(file_stream.at(current) == '"'){
            if(!match(file_stream,current,'"',true) && !do_ascii){
                std::cerr << "Unclosed string literal.." << '\n';
                std::exit(1);
            }else{
                do_ascii = !do_ascii;
                current++;
                continue;
            }
        }


        if(do_ascii){
            operation op = {OP_TYPE::PUSH,(char) file_stream.at(current)};
            op_list.push_back(op);
            current++;
            continue;
            
        }else{
            if(file_stream.at(current) == 'n'){
                op_list.push_back({SHOW_TOP_STACK_NUM,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == 'o'){
                op_list.push_back({SHOW_TOP_STACK_CHAR,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == 'l'){
                op_list.push_back({PUSHLNST,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == 'c'){
                op_list.push_back({RMST,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == 'q'){
                op_list.push_back({DISCRD,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == 's'){
                op_list.push_back({SWPST,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == 'd'){
                op_list.push_back({DUPSTACK,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == 'D'){
                op_list.push_back({DUPSTACK,-2});
                current++;
                continue;
            }
            if(file_stream.at(current) == '-'){
                if(next_is_digit(file_stream,current)){
                    negate_next_num = true;
                }else{
                    op_list.push_back({SUBTRACT,-1});
                }
                current++;
                continue;
            }
            if(file_stream.at(current) == '^'){
                op_list.push_back({POWER,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == '|'){
                op_list.push_back({FLOOR_DIV,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == '='){
                op_list.push_back({EQUALS,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == '>'){
                op_list.push_back({GREATER_THAN,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == '<'){
                op_list.push_back({LESS_THAN,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == '*'){
                op_list.push_back({MUL,-1});
                current++;
                continue;
            }

            if(file_stream.at(current) == '%'){
                op_list.push_back({MOD,-1});
                current++;
                continue;
            }

            if(file_stream.at(current) == '+'){
                op_list.push_back({ADD,-1});
                current++;
                continue;
            }

            if(file_stream.at(current) == 'r'){
                op_list.push_back({REVERSE_STACK,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == 'i'){
                op_list.push_back({CHINPUT,-1});
                current++;
                continue;
            }
            if(file_stream.at(current) == 'j'){
                op_list.push_back({JUMP,-1});
                current++;
                continue;
            }
    
            if(file_stream.at(current) == '('){
                if(!match(file_stream,current,')',true)){
                    std::cerr << "Unclosed loop.." << '\n';
                    std::exit(1);
                }else{
                    op_list.push_back({LOOP_OPEN,-1});
                    current++;
                    continue;
                }
            }

            if(file_stream.at(current) == ')'){
                if(!match(file_stream,current,'(',false)){
                    std::cerr << "Loop end with no start.." << '\n';
                    std::exit(1);
                }else{
                    op_list.push_back({LOOP_CLOSE,-1});
                    current++;
                    continue;
                }
            }


            if(file_stream.at(current) == '{'){
                if(!match(file_stream,current,'}',true)){
                    std::cerr << "Unclosed conditional.." << '\n';
                    std::exit(1);
                }else{
                    op_list.push_back({COND_OPEN,-1});
                    current++;
                    continue;
                }
            }

            if(file_stream.at(current) == '}'){
                if(!match(file_stream,current,'{',false)){
                    std::cerr << "Conditional start, but no end.." << '\n';
                    std::exit(1);
                }else{
                    op_list.push_back({COND_CLOSE,-1});
                    current++;
                    continue;
                }
            }
    

        }
        current++;
    }
    return op_list;
}