#include <iostream>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <iomanip>
using namespace std ;
#define REG_COUNT 16
#define INVALID_REG 17

unsigned long long  execution_time;
unsigned long long request_get;
unsigned long long request_done;
unsigned long long line_num;
int current_cycle;
int cycle_needed = 1;
int pipe[3] = {-1,-1,-1};
void execte();
void fetch(int i,int *,int size);
void decode();
int reg[16]={0};

class Simple_Pipe{
public:
    int registers[16];
    void print_regs();
};

