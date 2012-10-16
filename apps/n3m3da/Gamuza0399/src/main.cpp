#include <iostream>

#include "ofMain.h"
#include "gamuza.h"
#include "gamuzaConstants.h"
#include "ofAppGlutWindow.h"

#ifdef TARGET_OSX
    #include <Cocoa/Cocoa.h>
    #include <AppKit/AppKit.h>
#endif

gamuza * gapp;

//========================================================================
int main( ){

    ofAppGlutWindow window;

    // antialiasing hacks
    // window.setGlutDisplayString("rgba double samples>=4 depth");

	ofSetupOpenGL(&window,MAIN_WINDOW_W,MAIN_WINDOW_H,OF_WINDOW);

    // modify cocoa standard menu
    #ifdef TARGET_OSX
    if(NSApp){
        NSMenu *menubar = [NSApp mainMenu];
        [menubar removeItemAtIndex:1]; // removing file menu
        [menubar removeItemAtIndex:1]; // removing edit menu
    }
    #endif

	ofSetWindowTitle("GAmuza");

	gapp = new gamuza();
	ofRunApp(gapp);

}
