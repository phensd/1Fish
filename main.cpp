#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <stack>
#include "compile.h"
#include "run.h"



int main(int argc, char *argv[]){
    std::vector<std::string> args{argv+1,argc+argv};
    std::stack<int> stack{};
    std::vector<operation> ops {};

    //"show ops and stack if not empty"
    bool debug {(std::find(args.begin(),args.end(),"-sopsasine") != args.end())};

    if(args.size() >= 1){
        if(debug)std::cerr << "Scanning file " << args.at(0) << '\n';
        if(std::filesystem::is_regular_file(args.at(0))){
            ops = compile(args.at(0));

        }else{
            std::cerr << "File not found ... " << std::quoted(args.at(0)) << ".\n";
            std::exit(1);
        }
    }else{
        //todo: add a REPL here maybe?
        std::cerr << "Please input a file to compile & run...\n";
        std::exit(1);
    }
    if(debug){
        for(auto& op : ops){
            show_op(op);
        }
    }

    if(ops.size() > 0){
        run(ops,stack);

        if(debug){
            show_stack(stack);
        }

        std::cerr << '\n';
    }else{
        std::cerr << "No operations made from file ... "<< std::quoted(args.at(0)) << ". (Is it empty?) \n";
        std::exit(1);
    }
    return 0; 
}