#pragma once
#include <filesystem>
#include <vector>
enum OP_TYPE : uint8_t {
    PUSH,                   //0
    ADD,                    //1
    MUL,                    //2
    SHOW_TOP_STACK_NUM,     //3
    EQUALS,                 //4
    FLOOR_DIV,              //5
    POWER,                  //6
    SUBTRACT,               //7
    LOOP_OPEN,              //8
    LOOP_CLOSE,             //9
    SHOW_TOP_STACK_CHAR,    //10
    REVERSE_STACK,          //11
    GREATER_THAN,           //12
    LESS_THAN,              //13
    MOD,                    //14
    CHINPUT,                //15
    JUMP,                   //16

    PUSHLNST,                //17
    DUPSTACK,               //18
    RMST,                   //19
    DISCRD,                 //20
    SWPST,                  //21
    COND_OPEN,              //22
    COND_CLOSE,             //23


};

struct operation{
    OP_TYPE type;
    int val;
};

std::vector<operation> compile(std::filesystem::path file);

void show_op(operation& op);