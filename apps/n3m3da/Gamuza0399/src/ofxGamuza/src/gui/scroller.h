#ifndef _SCROLLER
#define _SCROLLER


#include "ofMain.h"
#include "gamuzaConstants.h"

class scroller{

	public:

		scroller();
        ~scroller();

		int         _width, _height;
    
        float       backX, backY, scrollX, scrollY, normPos;
	
        bool        imOver, imPressed;
    
        bool        isVertical;

		//--------------------------------------------------------
		void        setup(float x, float y, float w, float h);
        void        reset(float x, float y, float w, float h);
        void        draw();

		void 		mouseMoved(float x, float y);
		void 		mousePressed(float x, float y);
		void 		mouseDragged(float x, float y);
		//--------------------------------------------------------


};

#endif
