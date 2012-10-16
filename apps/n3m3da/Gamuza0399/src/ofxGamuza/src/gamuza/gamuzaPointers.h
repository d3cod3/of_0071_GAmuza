#ifndef _GAMUZAPOINTERS
#define _GAMUZAPOINTERS


#include "ofMain.h"
// constants
#include "gamuzaConstants.h"

class intP{
	
public:
    
    intP(){
        
    }
    intP(int _s){
        p = new int[_s];
    }
    
    void set(int dim){
        p = new int[dim];
    }
    
    int* p;
	
};

class uintP{
	
public:
    
    uintP(){
        
    }
    uintP(int _s){
        p = new unsigned int[_s];
    }
    
    void set(int dim){
        p = new unsigned int[dim];
    }
    
    unsigned int* p;
	
};

class floatP{
	
public:
    
    floatP(){
        
    }
    floatP(int _s){
        p = new float[_s];
    }
    
    void set(int dim){
        p = new float[dim];
    }
    
    float* p;
	
};

class charP{
	
public:
		
    charP(){
        
    }
    charP(int _s){
        p = new char[_s];
    }
    
    void set(int dim){
        p = new char[dim];
    }
		
    char* p;
	
};

class ucharP{
	
public:
    
    ucharP(){
        
    }
    ucharP(int _s){
        p = new unsigned char[_s];
    }
    
    void set(int dim){
        p = new unsigned char[dim];
    }
    
    unsigned char* p;
	
};

#endif	