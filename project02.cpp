#include "project02.h"


void print_pipe(const string& s){
    int *intr = new int [s.size()];
    for (int i = 0; i < s.length(); i+=4)
    {
        intr[i+3]= s[i]&0xff;
        intr[i+2]= s[i+1]&0xff;
        intr[i+1]= s[i+2]&0xff;
        intr[i]= s[i+3]&0xff;
    }
   cout<<"execution time: "<< std::dec <<execution_time<<"\n";
    if(pipe[2] != -1){
        cout<< "executing "<< std::hex<<intr[pipe[2]]<<std::hex<<intr[pipe[2]+1]<<std::hex<<intr[pipe[2]+2]<<std::hex<<intr[pipe[2]+3]<<"\n";
    }
    if(pipe[1] != -1){
        cout<< "decoding: "<< std::hex<<intr[pipe[1]]<<std::hex<<intr[pipe[1]+1]<<std::hex<<intr[pipe[1]+2]<<std::hex<<intr[pipe[1]+3]<<"\n";
    }
    if(pipe[0] != -1){
        cout << "fectching: "<< std::hex<<intr[pipe[0]]<< std::hex<<intr[pipe[0]+1]<< std::hex<<intr[pipe[0]+2] << std::hex<<intr[pipe[0]+3]<<"\n";
    }
    
}
void fetch(int i,int *intr,int size){
    if(i<size){
        pipe[0] = i;
        request_done++;
    }
    else
        pipe[0] =-1;
}

void execute(int *intr){
    if(pipe[2]!=-1){
        int st = pipe[2];
        cycle_needed=1;
        switch(intr[st]){
            case 0x00:{
                // cout<<"set"<<"\n";
                reg[intr[st+1]] = intr[st+2];
                }
            break;
            case 0x10:{
                
                // cout<<"add"<<"\n";
                reg[intr[st+1]] = reg[intr[st+2]] + reg[intr[st+3]];
                }
            break;
            case 0x11:{
                
                // cout<<"add1"<<"\n";//
                reg[intr[st+1]] = reg[intr[st+2]] + intr[st+3];
            }
            break;
            case 0x20:{
                // cout<<"sub"<<"\n";//
                reg[intr[st+1]] = reg[intr[st+2]] - reg[intr[st+3]];
            }
            break;
            case 0x21:{
                // cout<<"sub1"<<"\n";//
                reg[intr[st+1]] = reg[intr[st+2]] - intr[st+3];
            }
            break;
            case 0x30:{
                // cout<<"mul"<<"\n";//
                cycle_needed = 2;
                reg[intr[st+1]] = reg[intr[st+2]] * reg[intr[st+3]];
            }
            break;
            case 0x31:{
                // cout<<"mul1"<<"\n";//
                cycle_needed = 2;
                reg[intr[st+1]] = reg[intr[st+2]] * intr[st+3];
            }
            break;
            case 0x40:{
                // cout<<"div"<<"\n";
                cycle_needed = 4;
                reg[intr[st+1]] = reg[intr[st+2]] / reg[intr[st+3]];
            }
            break;
            case 0x41:{
                // cout<<"div1"<<"\n";
                cycle_needed = 4;
                reg[intr[st+1]] = reg[intr[st+2]] / intr[st+3];
            }
            break;
        }

    }   
        
    pipe[2] = pipe[1];
}

void decode(const string& s , int *intr){
    if(pipe[2]!=-1){
        int i = pipe[2];
        intr[i+3]= s[i]&0xff;
        intr[i+2]= s[i+1]&0xff;
        intr[i+1]= s[i+2]&0xff;
        intr[i]= s[i+3]&0xff;
    }
    pipe[1] = pipe[0];
}

void run_pipe(const string& s,int size){
    int i=0;
    int *intr = new int [size];
    while(i<size || pipe[2]!=-1){
        
        execute(intr);
        current_cycle =1;
        while(current_cycle < cycle_needed){
            // print_pipe(s); uncomment to print the log
            current_cycle++;
            execution_time++;
            //cout<<"\n"; uncomment to print the log
        }
        
        
        decode(s,intr);
        fetch(i,intr,size);
        i=i+4;
        
        if(pipe[0]!=-1 || pipe[1]!=-1 || pipe[2]!=-1){
            // print_pipe(s); uncomment to print the log
            //cout<<"\n";
            execution_time++;

        }
    }
    
}
int main(int argc, char *argv[]){
    ifstream::pos_type size;
    char * memblock;
  
    ifstream file (argv[1], ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
  
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();
        run_pipe(std::string(memblock, size),size);
    }   

    Simple_Pipe simple_pipe;
    for(int i = 0; i < REG_COUNT; i++){
        simple_pipe.registers[i] = reg[i];
        //cout<< std::dec <<reg[i]<<"\n";
    }

    simple_pipe.print_regs();
    std::cout << "Total execution cycles: " << execution_time << std::endl;
    std::cout << "\nIPC: " << (request_done/(double)execution_time) << std::endl << std::endl;

    return 0;
}



void Simple_Pipe::print_regs(){
    printf("\nRegisters: \n");
    std::cout << "----------------------------------------" << std::endl;
    for(int i = 0; i < REG_COUNT; i+=2){
        std::string regl("R");
        regl.append(std::to_string(i));
        regl.append(": ");

        std::string regr("R");
        regr.append(std::to_string(i+1));
        regr.append(": ");
        if(i < 15){
            std::cout << "  " << std::setiosflags(std::ios::left) 
            << std::setw(5) << regl  << std::setw(10) << std::dec  << registers[i] << " |   " 
            << std::setw(5) << regr << std::setw(10) << std::dec  << registers[i+1] << std::endl;
            std::cout << "----------------------------------------" << std::endl;
        }else{
            std::cout << "  " << std::setiosflags(std::ios::left) 
            << std::setw(5) << regl << std::setw(10) << reg[i] << " |   " << std::endl;
            std::cout << "----------------------------------------" << std::endl;
        }
    }  
    printf("\n");
}

