/*
 * Copyright (c) 2011 Dan Wilcox <danomatika@gmail.com>
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 * See https://github.com/danomatika/ofxLua for documentation
 *
 * This project uses the following libraries:
 *
 * Lua, Copyright (c) 1994–2011 Lua.org, PUC-Rio using the MIT License.
 * See the file "COPYRIGHT" in src/lua.
 * See http://www.lua.org/docs.html for documentation
 *
 * Luabind, Copyright (c) 2003 Daniel Wallin and Arvid Norberg using the
 * MIT License. See the file "LICENSE" in src/luabind.
 * See http://www.rasterbar.com/products/luabind/docs.html for documentation
 *
 */
#include "ofxLua.h"

#include "ofUtils.h"
#include <Poco/Path.h>

using namespace std;

// local pointer for static functions
ofxLua* luaPtr;

//--------------------------------------------------------------------
ofxLua::ofxLua()
{
	L = NULL;
	bAbortOnError = false;

	luaPtr = this;
}

//--------------------------------------------------------------------
ofxLua::~ofxLua() {
	clear();
}

//--------------------------------------------------------------------
bool ofxLua::init(bool abortOnError, bool openLibs) {
	
	clear();
	
	L = luaL_newstate();
	if(L == NULL) {
		ofLog(OF_LOG_ERROR, "ofxLua: Error initializing lua");
		lastError = "error initializing lua";
		return false;
	}
	
	// open libs
	if(openLibs) {
		luaL_openlibs(L);
	}
	luabind::open(L);
	
	// set the panic function
	lua_atpanic(L, &atPanic);
	
	bAbortOnError = abortOnError;
	ofLog(OF_LOG_VERBOSE, "ofxLua: Initialized");
	
}
	

void ofxLua::clear() {
	if(L != NULL) {
		lua_close(L);
		L = NULL;
		ofLog(OF_LOG_VERBOSE, "ofxLua: Cleared");
	}
}

bool ofxLua::isValid() {
	return (L != NULL);
}

//--------------------------------------------------------------------
bool ofxLua::doString(const std::string& text) {
	
	lastError = "Script has no errors";
	
	if(L == NULL) {
		ofLog(OF_LOG_ERROR, "ofxLua: Cannot do string, lua state not inited!");
		return false;
	}

	ofLog(OF_LOG_VERBOSE, "ofxLua: Doing string: \"%s\"", text.substr(0,40).c_str());
	
	// load the string
	int ret = luaL_loadstring(L, text.c_str());
	if(ret != 0) {
		switch(ret) {
			case LUA_ERRSYNTAX:
			{
				string msg = "Syntax error in string \""
					 +text.substr(0,40)+"\": "
					 +(string) lua_tostring(L, -1);
				lastError = (string) lua_tostring(L, -1);
				errorOccurred(msg);
				break;
			}
			case LUA_ERRMEM:
			{
				string msg = "String \""+text.substr(0,40)+"\" memory error",
				errorOccurred(msg);
				lastError = "memory error";
				break;
			}
		}
				
		return false;
	}
	
	// run the string
	ret = lua_pcall(L, 0, LUA_MULTRET, 0);
	if(ret != 0) {
		string msg = "Runtime error in string \""+text.substr(0,40)+"\": "
					 +(string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
		return false;
	}
	
	return true;
}

//--------------------------------------------------------------------
bool ofxLua::doScript(const std::string& script) {
	
	lastError = "Script has no errors";

	if(L == NULL) {
		ofLog(OF_LOG_ERROR, "ofxLua: Cannot do script, lua state not inited!");
		return false;
	}

	Poco::Path path(ofToDataPath(script));
	string folder = path.parent().toString();
	
	// trim the trailing slash Poco::Path always adds ... blarg
	if(folder.size() > 0 && folder.at(folder.size()-1) == '/') {
		folder.erase(folder.end()-1);
	}
	
	ofLog(OF_LOG_VERBOSE, "ofxLua: Doing script: \"%s\" path: \"%s\"",
		path.getFileName().c_str(), folder.c_str());

	// load the script
	int ret = luaL_loadfile(L, path.toString().c_str());
	if(ret != 0) {
		switch(ret) {
			case LUA_ERRFILE:
			{
				string msg = (string)"Script \""+path.getFileName()+"\" not found or unreadable";
				lastError = "script not found or unreadable";
				errorOccurred(msg);
				break;
			}
			case LUA_ERRSYNTAX:
			{
				string msg = "Syntax error: "+(string) lua_tostring(L, -1);
				lastError = (string) lua_tostring(L, -1);
				errorOccurred(msg);
				break;
			}
			case LUA_ERRMEM:
			{
				string msg = "Script \""+path.getFileName()+"\" memory error";
				lastError = "memory error";
				errorOccurred(msg);
				break;
			}
		}
		return false;
	}
	
	// run the script
	ret = lua_pcall(L, 0, LUA_MULTRET, 0);
	if(ret != 0) {			
		string msg = "Runtime error: "+(string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
		return false;
	}
	
	return true;
}

//--------------------------------------------------------------------		
bool ofxLua::funcExists(const std::string& name) {
	
	if(L == NULL) {
		ofLog(OF_LOG_ERROR, "ofxLua: Cannot check func, lua state not inited!");
		return false;
	}
		
	using namespace luabind;

	object g = globals(L);
	object func = g[name];

	if(func) {
		if(type(func) == LUA_TFUNCTION)
			return true;
	}
	return false;
}

//--------------------------------------------------------------------		
void ofxLua::addListener(ofxLuaListener& listener) {
	// exists?
	for(int i = 0; i < listeners.size(); ++i) {
		if(listeners[i] == &listener) {
			ofLog(OF_LOG_WARNING, "ofxLua: addListener(): ignoring duplicate listener");
			return;
		}
	}
	listeners.push_back(&listener);
}
		
//--------------------------------------------------------------------		
void ofxLua::removeListener(ofxLuaListener& listener) {
	for(int i = 0; i < listeners.size(); ++i) {
		if(listeners[i] == &listener) {
			listeners.erase(listeners.begin()+i);
			return;
		}
	}
	ofLog(OF_LOG_WARNING, "ofxLua: removeListener(): listener not found");
}
		
//--------------------------------------------------------------------		
void ofxLua::clearListeners() {
	listeners.clear();
}

//--------------------------------------------------------------------		
void ofxLua::scriptSetup() {
	if(L == NULL || !funcExists("setup"))
		return;
	lua_getglobal(L, "setup");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running setup(): " + (string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptUpdate() {
	if(L == NULL || !funcExists("update"))
		return;
	lua_getglobal(L, "update");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running update(): " + (string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptDraw() {
	if(L == NULL || !funcExists("draw"))
		return;
	lua_getglobal(L, "draw");
	if(lua_pcall(L, 0, 0, 0) != 0) {			
		string msg = "Error running draw(): " + (string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptExit() {
	if(L == NULL || !funcExists("exit"))
		return;
	lua_getglobal(L, "exit");
	if(lua_pcall(L, 0, 0, 0) != 0) {
		string msg = "Error running exit(): " + (string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

//--------------------------------------------------------------------
void ofxLua::scriptKeyPressed(int key) {
	if(L == NULL || !funcExists("keyPressed"))
		return;
	lua_getglobal(L, "keyPressed");
	lua_pushinteger(L, key);
	if(lua_pcall(L, 1, 0, 0) != 0) {
		string msg = "Error running keyPressed(): "
					 + (string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptKeyReleased(int key) {
	if(L == NULL || !funcExists("keyReleased"))
		return;
	lua_getglobal(L, "keyReleased");
	lua_pushinteger(L, key);
	if(lua_pcall(L, 1, 0, 0) != 0) {
		string msg = "Error running keyReleased(): "
        + (string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMouseMoved(int x, int y ) {
	if(L == NULL || !funcExists("mouseMoved"))
		return;
	lua_getglobal(L, "mouseMoved");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	if(lua_pcall(L, 2, 0, 0) != 0) {
		string msg = "Error running mouseMoved(): "
					 + (string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMouseDragged(int x, int y, int button) {
	if(L == NULL || !funcExists("mouseDragged"))
		return;
	lua_getglobal(L, "mouseDragged");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	lua_pushinteger(L, button);
	if(lua_pcall(L, 3, 0, 0) != 0) {
		string msg = "Error running mouseDragged(): "
					 + (string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMousePressed(int x, int y, int button) {
	if(L == NULL || !funcExists("mousePressed"))
		return;
	lua_getglobal(L, "mousePressed");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	lua_pushinteger(L, button);
	if(lua_pcall(L, 3, 0, 0) != 0) {			
		string msg = "Error running mousePressed(): "
					 + (string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

void ofxLua::scriptMouseReleased(int x, int y, int button) {
	if(L == NULL || !funcExists("mouseReleased"))
		return;
	lua_getglobal(L, "mouseReleased");
	lua_pushinteger(L, x);
	lua_pushinteger(L, y);
	lua_pushinteger(L, button);
	if(lua_pcall(L, 3, 0, 0) != 0) {
		string msg = "Error running mouseReleased(): "
					 + (string) lua_tostring(L, -1);
		lastError = (string) lua_tostring(L, -1);
		errorOccurred(msg);
	}
}

//--------------------------------------------------------------------
void ofxLua::errorOccurred(const std::string& msg) {
	
	// print
	for(int i = 0; i < listeners.size(); ++i) {
		listeners[i]->errorReceived(msg);
	}
	ofLog(OF_LOG_ERROR, "ofxLua: %s", msg.c_str());
	
	// find error line number
	size_t _pos, _pos2;
	string _temp,_temp2;
	
	_pos = msg.find("]:");
	_temp = msg.substr(_pos+2);
	_pos2 = _temp.find(": ");
	_temp2 = _temp.substr(0,_pos2);
	errorLine = atoi(_temp2.c_str());
	
	// close the state?
	if(bAbortOnError) {
		ofLog(OF_LOG_ERROR, "ofxLua: Closing state");
		clear();
	}
	
}

//--------------------------------------------------------------------
int ofxLua::atPanic(lua_State *L) {
	ofLog(OF_LOG_ERROR, "ofxLua: Lua panic ocurred! : %s",
			lua_tostring(L, -1));
	ofLog(OF_LOG_ERROR, "ofxLua: Closing state");
	luaPtr->clear();
	return 0;
}
