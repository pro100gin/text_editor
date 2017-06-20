#include "../include/init.h"


int  main(int argc, char* argv[]){

        if(argc>1){
                if(argc>2){
                        if(!chdir(argv[2]))
                                InitDraw(argv[1]);
                }
                else
                        InitDraw(argv[1]);
        }
        return 0;
}

