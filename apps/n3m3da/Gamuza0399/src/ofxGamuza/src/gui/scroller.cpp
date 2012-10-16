#include "scroller.h"


//---------------------------------------------------------
scroller::scroller(){
	
}

//---------------------------------------------------------
scroller::~scroller(){
	
}

//--------------------------------------------------------
void scroller::setup(float x, float y, float w, float h){
    
    normPos = 0.0;
    reset(x,y,w,h);
    
}

//--------------------------------------------------------
void scroller::mouseMoved(float x, float y){
	
	float xdiff = scrollX - x;
    float ydiff = scrollY - y;
    float dist = sqrt(xdiff * xdiff + ydiff * ydiff);
    if(isVertical){
        if (dist < _width-2){
            imOver = true;
        }else{
            imOver = false;
        }
    }else{
        if (dist < _height-2){
            imOver = true;
        }else{
            imOver = false;
        }
    }
}

//--------------------------------------------------------
void scroller::mousePressed(float x, float y){
	
    float xdiff = scrollX - x;
    float ydiff = scrollY - y;
    float dist = sqrt(xdiff * xdiff + ydiff * ydiff);
    if(isVertical){
        if (dist < _width-2){
            imPressed = true;
        }else{
            imPressed = false;
        }
    }else{
        if (dist < _height-2){
            imPressed = true;
        }else{
            imPressed = false;
        }
    }

}

//--------------------------------------------------------
void scroller::mouseDragged(float x, float y){
	
    if(imPressed){
        if(!isVertical){
            if(x > backX && x < backX+_width){
                scrollX = x;
                normPos = (scrollX-backX)/_width;
            }
        }else{
            if(y > backY && y < backY+_height){
                scrollY = y;
                normPos = (scrollY-backY)/_height;
            }
        }
	}
}

//--------------------------------------------------------
void scroller::reset(float x, float y, float w, float h){
	_width 	    = w;
	_height     = h;
    backX       = x;
    backY       = y;
    scrollX     = x;
    scrollY     = y;
    imOver      = false;
    imPressed   = false;
    isVertical  = true;
}

//---------------------------------------------------------
void scroller::draw(){
	
    ofNoFill();
    ofSetColor(30,30,30);
    ofRect(backX,backY,_width,_height);
    
    ofFill();
    if(imOver){
        ofSetColor(216,64,64);
    }else if(!imOver){
        ofSetColor(216,216,216);
    }
    
    if(isVertical){
        ofRect(scrollX + 1,scrollY,_width-2,5);
    }else{
        ofRect(scrollX,scrollY+1,5,_height-2);
    }
    
    ofSetColor(255,255,255);
    
}