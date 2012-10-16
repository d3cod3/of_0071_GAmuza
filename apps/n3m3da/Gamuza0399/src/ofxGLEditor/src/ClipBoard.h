/*
 *  ClipBoard.h
 *  ofxLuaLive
 *
 *  Created by Makira on 11/07/09.
 *  Copyright 2011 ・‥…―━━━―…‥・yesMAYBEno・‥…―━━━―…‥・. All rights reserved.
 *
 */

#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#ifdef TARGET_OSX
    #define GHOST_COCOA

    #include "GHOST_IEventConsumer.h"
    #include "GHOST_ISystem.h"
    #include "GHOST_IEvent.h"
#endif

#ifdef TARGET_LINUX
    //#include "GHOST_SystemX11.h"
#endif

#include "ofMain.h"


class ClipBoard{

public:

    ClipBoard();

    void            setupClipboard();
    void            updateClipboard();

    char*           getTextFromPasteboard();

    #ifdef TARGET_OSX
	OSStatus        setTextToPasteboard(const char* byteArrayIndex);
    #endif

    #ifdef TARGET_LINUX
    // TODO
    #endif

    //GHOST_ISystem*  ghostSystem;

};

#endif
