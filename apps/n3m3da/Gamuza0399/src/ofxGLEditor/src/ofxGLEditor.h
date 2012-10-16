/*
 *  ofxGLEditor.h
 *  LiveCoding
 *
 *  Created by Makira on 11/07/05.
 *  Copyright 2011 ・‥…―━━━―…‥・yesMAYBEno・‥…―━━━―…‥・. All rights reserved.
 *
 */

#pragma once

#define		GL_EDITOR_FONT		"fonts/Anonymous_Pro_B.ttf"

#include "ofMain.h"
#include "ofxKeyMap.h"
#include "GLEditor.h"
#include "Unicode.h"
#include "ClipBoard.h"

using namespace fluxus;

class ofxGLEditor {

public:
	
	void setup(string fontFile = GL_EDITOR_FONT);
    void update();
    void renderScript();
	void keyPressed(int key, bool editorOn);
	void draw();	
	void reShape();
	void reShape(int _w, int _h);
    void reShape(int _w, int _h, int _x, int _y);
	bool isAltPressed(); // should be used in keypress callback
	void pasteFromClipBoard();
	void pasteFromLuaScript(string _s);
    void cutToClipBoard();
	void copyToClipBoard();
	void saveToFile();
	void saveToFile(string _name,string _path);
    void saveToFile(string _path);
	
	
	ofxKeyMap kmap;	
	vector<GLEditor*> glEditor;
	int currentEditor;
    int currentLine;
	ClipBoard clipBoard;
	
	ofEvent<string> doCompileEvent;
	
};