#include "gamuzaMain.h"
#include "gamuzaGui.h"
#include "gamuzaFBO.h"
#include "gamuzaAudio.h"
#include "gamuzaArduino.h"
#include "gamuzaMidi.h"
#include "gamuzaOSC.h"
#include "gamuzaSettingsPanel.h"

//--------------------------------------------------------------
void gamuzaMain::setup(){

	flagSystemLoaded	= false; // first line of gamuza setup

	//////////////////////////////////////////////
	// load settings from xml
	loadGamuzaSettings();
	// automation
    isFullscreen = false;
	if(autoPilot){
		gamuzaFullscreen();
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// init general openframeworks settings
    ofSetEscapeQuitsApp(false);
	ofSetFrameRate(200);
	ofEnableSmoothing();
	ofSetLogLevel(OF_LOG_VERBOSE);
	//////////////////////////////////////////////

    //////////////////////////////////////////////
	// OSC data sending @ host_number(IP),host_port
    gamuzaSetup.lock();
    setupOSC();
    gamuzaSetup.unlock();
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// AUDIO
	if(audioActivated){
		gamuzaSetup.lock();
		setupAudio();
		gamuzaSetup.unlock();
	}
	//////////////////////////////////////////////

    //////////////////////////////////////////////
	// MIDI
    gamuzaSetup.lock();
    setupMidi();
    gamuzaSetup.unlock();
    //////////////////////////////////////////////

	//////////////////////////////////////////////
	// OPENNI
	if(openniActivated){
		gamuzaSetup.lock();
		sensorKinect.setupDevice(workingW,workingH,useKinectInfrared,sensorKinectLedState);
		gamuzaSetup.unlock();
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// FBO second screen output texture
	gamuzaSetup.lock();
	setupFBO();
	gamuzaSetup.unlock();
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// ARDUINO
	if(arduinoActivated){
		gamuzaSetup.lock();
		setupArduino();
		gamuzaSetup.unlock();
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// GUI
	// include setup of webcams & audio inputs
	gamuzaSetup.lock();
    setupSettingPanel();
	setupGui();
	gamuzaSetup.unlock();
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// SYSTEM
	currentSavedFrame   = 0;
    gaFrameCounter      = 0;
    //////////////////////////////////////////////

	//////////////////////////////////////////////
	// set log level to error only
	ofSetLogLevel(OF_LOG_ERROR);
    sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
	//////////////////////////////////////////////

}

//--------------------------------------------------------------
void gamuzaMain::update(){

    char temp_message[512];

	//////////////////////////////////////////////
	// INIT PROGRAM | splash image control
	if(ofGetElapsedTimeMillis() > splashWait){
		splashFinish = true;
		if(flagSystemLoaded){
			flagSystemLoaded = false;
            sprintf(temp_message,"OpenGL version: %s", glGetString (GL_VERSION));
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, temp_message);
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
            if(GL_ARB_shader_objects){
                sprintf(temp_message,"GL_ARB_shader SUPPORTED by your Graphic Card: %s", glGetString (GL_RENDERER));
                sendPrivateMessage(GAMUZA_CONSOLE_LOG, temp_message);
                sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
            }else{
                sprintf(temp_message,"GL_ARB_shader NOT SUPPORTED by your Graphic Card: %s", glGetString (GL_RENDERER));
                sendPrivateMessage(GAMUZA_CONSOLE_LOG, temp_message);
                sendPrivateMessage(GAMUZA_CONSOLE_LOG, "switching to SHADER OFF MODE");
                sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
            }

			if(audioActivated){
				soundStream.start();
                sendPrivateMessage(GAMUZA_CONSOLE_LOG, "soundStream STARTED");
                sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
				for(unsigned int i = 0; i < audioInputChannels; i++){
					inputAudioCH[i].computeChannel = true;
				}
				computeAudioInput	= true;
				computeAudioOutput	= true;

			}
            if(arduinoActivated){
                sendPrivateMessage(GAMUZA_CONSOLE_LOG, "ARDUINO connection established");
                sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
            }
		}
		//////////////////////////////////////////////
		// Main settings control
		ofSetVerticalSync(useVSync);
		//////////////////////////////////////////////

		//////////////////////////////////////////////
		// GUI update
		updateGui();
		gui.update();
		//////////////////////////////////////////////

        //////////////////////////////////////////////
		// FBO Output Texture update
        updateFBO();
        //////////////////////////////////////////////

		//////////////////////////////////////////////
		// OPENNI
		if(openniActivated && sensorKinect.useKinect && sensorKinect.isOniConnected){
			sensorKinect.updateDevice();
		}
		//////////////////////////////////////////////

		//////////////////////////////////////////////
		// WEBCAM input devices update
		if(trackingActivated){
			for(unsigned int i=0;i<numCamInputs;i++){
				if(inputCam[i].captureVideo){
					inputCam[i].update();
				}
			}
		}
		//////////////////////////////////////////////

		//////////////////////////////////////////////
		// ARDUINO update
		if(arduinoActivated && useArduino){
			updateArduino();
		}
		//////////////////////////////////////////////

	}
	//////////////////////////////////////////////

    //////////////////////////////////////////////
    // OSC update
    updateOSC();
    // OSC messages receiving
    receiveOSC();
    //////////////////////////////////////////////

	//////////////////////////////////////////////
	// SYSTEM
	gamuzaRealFPS = ofGetFrameRate();
    gaFrameCounter++;
	//////////////////////////////////////////////

}

//--------------------------------------------------------------
void gamuzaMain::draw(){

	if(splashFinish){

		ofBackground(0,0,0);

		//////////////////////////////////////////////
		// GUI draw
		if(!liveCodingMode){
		    ofSetLineWidth(1.2);
			gui.draw();
            drawGui();
            ofSetLineWidth(1);
		}
		//////////////////////////////////////////////

        //////////////////////////////////////////////
		// FBO texture draw
        glColor4f(1.0,1.0,1.0,1.0);
		drawFBO();
		//////////////////////////////////////////////

        ////////////////////////////////////
        // TIMELINE
        if(showTimeline && !isFullscreen){
            ofEnableAlphaBlending();
            glColor4f(0.0,0.0,0.0,0.9);
            ofRect(0,0,MAIN_WINDOW_W-4,MAIN_WINDOW_H);
            ofDisableAlphaBlending();
        }else if(showTimeline && isFullscreen){
            ofEnableAlphaBlending();
            glColor4f(0.0,0.0,0.0,0.9);
            ofRect(0,0,mainScreenW-1,mainScreenH);
            ofDisableAlphaBlending();
        }

        timeline.draw();
        ////////////////////////////////////

	}else{
		ofBackground(20,20,20);
		ofEnableAlphaBlending();
		if(isFullscreen){
			// image
			glColor4f(1.0,1.0,1.0,1.0);
			splashImage.draw((mainScreenW/2) - 256,(mainScreenH/2) - 153);
			// loading bar
			ofSetColor(9,147,211,235);
			ofRect((mainScreenW/2) - 240,(mainScreenH/2) - 144,(ofGetElapsedTimeMillis()*1.0f/splashWait)*480.0f,6);
			ofDisableAlphaBlending();
		}else{
			// image
			glColor4f(1.0,1.0,1.0,1.0);
			splashImage.draw((MAIN_WINDOW_W/2) - 256,(MAIN_WINDOW_H/2) - 153);
			// loading bar
			ofSetColor(9,147,211,235);
			ofRect((MAIN_WINDOW_W/2) - 240,(MAIN_WINDOW_H/2) - 144,(ofGetElapsedTimeMillis()*1.0f/splashWait)*480.0f,6);
			ofDisableAlphaBlending();
		}
	}

}

//--------------------------------------------------------------
void gamuzaMain::keyPressed(int key){

    bool alt = gamuzaKmap.isAltDown();

    ///////////////////////////////////////////
    // MAPPING keyboard control
    if(!activateMouseMapping){
        if(alt && key == OF_KEY_RETURN){
            manualEditMappingPoint = true;

        }

        if(alt && key == OF_KEY_BACKSPACE){
            manualEditMappingPoint = false;

        }

        if(alt && key == OF_KEY_LEFT){
            if(!manualEditMappingPoint){
                if(actualMappingPoint > 0){
                    actualMappingPoint--;
                }else{
                    actualMappingPoint = totalMappingPoints-1;
                }
            }else{
                finalTextureMapping.points[actualMappingPoint].x--;
            }
        }else if(alt && key == OF_KEY_RIGHT){
            if(!manualEditMappingPoint){
                if(actualMappingPoint < totalMappingPoints){
                    actualMappingPoint++;
                }else{
                    actualMappingPoint = 0;
                }
            }else{
                finalTextureMapping.points[actualMappingPoint].x++;
            }
        }else if(alt && key == OF_KEY_UP){
            if(manualEditMappingPoint){
                finalTextureMapping.points[actualMappingPoint].y--;
            }
        }else if(alt && key == OF_KEY_DOWN){
            if(manualEditMappingPoint){
                finalTextureMapping.points[actualMappingPoint].y++;
            }
        }
    }
    ///////////////////////////////////////////

	// LIVE CODING
	if(activateLiveEditor){
        liveCoding.keyPressed(key,activateLiveEditor);
	}

	lua.scriptKeyPressed(key);
	liveKey= key;
}

//--------------------------------------------------------------
void gamuzaMain::keyReleased(int key){

	bool alt = gamuzaKmap.isAltDown();

    //////////////////////////////////////////////////////////
	// LIVE CODING
    if(alt && (key == 'j' || key == 'J')){
        liveCodingMode = !liveCodingMode;
        if(liveCodingMode && isFullscreen){
            scriptScroll.reset(lcPrevX-20,1,20,lcPrevH-1);
        }else if(!liveCodingMode && isFullscreen){
            scriptScroll.reset(224+guiPosX,previewY+guiPosY,20,previewH);
        }else if(liveCodingMode && !isFullscreen){
            scriptScroll.reset(lcPrevX-20,1,20,lcPrevH-1);
        }else{
            scriptScroll.reset(224,previewY,20,previewH);
        }
    }
    // show/hide script code
    if(alt && (key == 'w' || key == 'W')){
        viewCode = !viewCode;
    }
    // LUA
    lua.scriptKeyReleased(key);
    //////////////////////////////////////////////////////////


	// save frame
	if(alt && (key == 'o' || key == 'O')){
		saveFrame();
	}

	// print frame
	if(alt && (key == 'p' || key == 'P')){
		printFrame();
	}

    // switch between mouse/keyboard Mapping points control
    if(alt && (key == 'm' || key == 'M')){
        activateMouseMapping = !activateMouseMapping;
    }

    // TIMELINE
    if(alt && (key == 't' || key == 'T')){
        showTimeline = !showTimeline;
        if(showTimeline){
            timeline.show();
            timeline.enableMouse();
        }else{
            timeline.hide();
            timeline.disableMouse();
        }
    }
    // play/stop the timeline
    if(alt && (key == 'g' || key == 'G')){
        timeline.togglePlay();
    }

    // fullscreen toggle
	if(alt && (key == 'f' || key == 'F')){
		gamuzaFullscreen();
	}

    liveKey = key;

}

//--------------------------------------------------------------
void gamuzaMain::mouseMoved(int x, int y){

	//////////////////////////////TESTING
	//printf("%f - %f\n",scaledMouseX,scaledMouseY);
	//////////////////////////////TESTING

    // scaled mouse position
    if(liveCodingMode && !isFullscreen){
        scaledMouseX = (float) x*1.0 - lcPrevX;
        scaledMouseY = (float) y*1.0 - lcPrevY;
    }else if(liveCodingMode && isFullscreen){
        scaledMouseX = (float) (((x*1.0) - lcPrevX)/lcPrevW)*projectionScreenW;
        scaledMouseY = (float) (((y*1.0) - lcPrevY)/lcPrevH)*projectionScreenH;
    }else{
        scaledMouseX = (float) (((x*1.0) - 246.0 - guiPosX)/previewW)*projectionScreenW;
        scaledMouseY = (float) (((y*1.0) - previewY - guiPosY)/previewH)*projectionScreenH;
    }

	// mapping grid
	if(drawGrid){
		finalTextureMapping.mouseMoved(x, y);
	}

	// Live Coding
    lua.scriptMouseMoved(x, y);
    scriptScroll.mouseMoved(x,y);

    // Settings PANEL
    oscPortField.mouseMoved(x,y);
    oscIPField.mouseMoved(x,y);
    oscServerPortField.mouseMoved(x,y);

}

//--------------------------------------------------------------
void gamuzaMain::mouseDragged(int x, int y, int button){

	// gui interface
    if(!liveCodingMode && !showTimeline){
        gui.mouseDragged(x, y, button);
    }

	if(openniActivated && sensorKinect.isOniConnected){
		if(gui.getSelectedPanel() == sensorKinectIndex){
			sensorKinect.mouseDragged(x-guiPosX, y-guiPosY, button);
		}
	}

	if(trackingActivated){
		if(gui.getSelectedPanel() >= webcamsStartIndex && gui.getSelectedPanel() < webcamsStartIndex + numCamInputs){
			inputCam[gui.getSelectedPanel()-webcamsStartIndex].mouseDragged(x-guiPosX, y-guiPosY, button);
		}
	}

	// Mapping
	if(drawGrid){
		finalTextureMapping.mouseDragged(x, y);
	}

	// Live Coding
    lua.scriptMouseDragged(x, y, button);
    scriptScroll.mouseDragged(x,y);
    liveCoding.glEditor[liveCoding.currentEditor]->SetCurrentLine(floor(scriptScroll.normPos*liveCoding.glEditor[liveCoding.currentEditor]->getNumLines()));

}

//--------------------------------------------------------------
void gamuzaMain::mousePressed(int x, int y, int button){

	// gui interface
    if(!liveCodingMode  && !showTimeline){
        gui.mousePressed(x, y, button);
    }

	//////////////////////////////////////////////////
	// save EXTRA GUI settings
    if(gui.saveDown || gui.restoreDown){
        saveGamuzaSettings();
    }

	if(gui.saveDown && gui.getSelectedPanel() == 0){
        saveMappingSettings = true;
	}

	if(openniActivated && sensorKinect.isOniConnected){
		if(gui.getSelectedPanel() == sensorKinectIndex){
			sensorKinect.mousePressed(x-guiPosX, y-guiPosY, button);
			if(gui.saveDown){
				sensorKinect.saveAllSettings = true;
			}
		}
	}

	if(trackingActivated){
		if(gui.getSelectedPanel() >= webcamsStartIndex && gui.getSelectedPanel() < webcamsStartIndex + numCamInputs){
			inputCam[gui.getSelectedPanel()-webcamsStartIndex].mousePressed(x-guiPosX, y-guiPosY, button);
			if(gui.saveDown){
				inputCam[gui.getSelectedPanel()-webcamsStartIndex].saveAllSettings = true;
			}

		}
	}

	if(arduinoActivated){
		if(gui.saveDown && gui.getSelectedPanel() == arduinoIndex){
			if(useArduino){
				saveArduinoPinsState = true;
			}
		}
	}
	// save EXTRA GUI settings
	//////////////////////////////////////////////////

	// Mapping
	if(drawGrid){
		finalTextureMapping.mousePressed(x, y);
	}

	// Live Coding
    lua.scriptMousePressed(x, y, button);
    scriptScroll.mousePressed(x,y);

}

//--------------------------------------------------------------
void gamuzaMain::mouseReleased(int x, int y, int button){

	// gui interface
    if(!liveCodingMode  && !showTimeline){
        gui.mouseReleased();
    }

	if(openniActivated && sensorKinect.isOniConnected){
		if(gui.getSelectedPanel() == sensorKinectIndex){
			sensorKinect.mouseReleased(x-guiPosX, y-guiPosY, button);
		}
	}

	if(trackingActivated){
		if(gui.getSelectedPanel() >= webcamsStartIndex && gui.getSelectedPanel() < webcamsStartIndex + numCamInputs){
			inputCam[gui.getSelectedPanel()-webcamsStartIndex].mouseReleased(x-guiPosX, y-guiPosY, button);
		}
	}

	// Mapping
	if(drawGrid){
		finalTextureMapping.mouseReleased(x, y);
	}

    // SETTINGS Panel
    oscPortField.mouseReleased(x,y);
    oscIPField.mouseReleased(x,y);
    oscServerPortField.mouseReleased(x,y);

	// Live Coding
    lua.scriptMouseReleased(x, y, button);
}

//--------------------------------------------------------------
void gamuzaMain::receivedTrigger(ofxTLTriggerEventArgs& trigger){
	actualTriggerName = trigger.triggerName;
}

//--------------------------------------------------------------
void gamuzaMain::saveFrame(){

	string _d = getDateTimeAsString("%d_%m_%Y");
	string start = "export/frames/frame"+ofToString(currentSavedFrame);
	string fin = start+"_"+_d+".tif";

	currentSavedFrame++;

    if(useSecondaryScreen && useShader){
        finalTexture.readToPixels(outputPix);
    }else{
        drawingTexture.readToPixels(outputPix);
    }
    tempFrame.setFromPixels(outputPix);
	tempFrame.saveImage(fin.c_str());

    sendPrivateMessage(GAMUZA_CONSOLE_LOG, "Frame SAVED");
    sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
}

//--------------------------------------------------------------
void gamuzaMain::printFrame(){
	#if defined (TARGET_OSX) || defined(TARGET_LINUX)
		tempFrame.grabScreen(mainScreenW+1,0,projectionScreenW,projectionScreenH);
		tempFrame.saveImage("export/frames/printFrame.jpg");

		string commandStr = "lp ../../../data/export/frames/printFrame.jpg";
		system(commandStr.c_str());

        sendPrivateMessage(GAMUZA_CONSOLE_LOG, "Sending frame for Printing");
        sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
	#endif
}

//--------------------------------------------------------------
void gamuzaMain::loadGamuzaSettings(){

	setting_data.loadFile(GAMUZA_SETTINGS);

    oscPortField.enable();
    oscIPField.enable();
    oscServerPortField.enable();
    oscPortField.text        = setting_data.getValue("host_port"," ",0);
    oscIPField.text          = setting_data.getValue("host_ip"," ",0);
    oscServerPortField.text  = setting_data.getValue("server_port"," ",0);
    oscPortField.disable();
    oscIPField.disable();
    oscServerPortField.disable();

    _scriptFile               = setting_data.getValue("script_file"," ",0);
    _videoTestFile            = setting_data.getValue("video_test_file"," ",0);
    _haarCascadeFile          = setting_data.getValue("haar_finder_file"," ",0);

	//////////////////////////////////////////////
	// get SCREENS settings
	mainScreenW				= setting_data.getValue("ms_width",0,0);
	mainScreenH				= setting_data.getValue("ms_height",0,0);
	projectionScreenW		= setting_data.getValue("ps_width",0,0);
	projectionScreenH		= setting_data.getValue("ps_height",0,0);
	INVprojectionScreenW	= 1.0f/projectionScreenW;
	INVprojectionScreenH	= 1.0f/projectionScreenH;
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// get AUTOMATION settings
	autoPilot				= setting_data.getValue("auto_pilot",0,0);
	autoLoadScript			= setting_data.getValue("autoload_script",0,0);
	autoScriptFile			= setting_data.getValue("script_file"," ",0);
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// get SENSOR KINECT TRACKING settings
	useKinectInfrared		= setting_data.getValue("use_infrared",0,0);
	sensorKinectLedState	= setting_data.getValue("led_state",0,0);
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// get WEBCAM TRACKING settings
	trackingActivated		= setting_data.getValue("tracking_activated",0,0);
	openniActivated			= setting_data.getValue("openni_activated",0,0);
	useVideoTest			= setting_data.getValue("video_test",0,0);
	workingW				= setting_data.getValue("capture_width",0,0);
	workingH				= setting_data.getValue("capture_height",0,0);
	totPixels				= workingW*workingH;

	haarFinderFile			= setting_data.getValue("haar_finder_file"," ",0);
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// get MAPPING settings
	gridRes					= setting_data.getValue("grid_res",0,0);
	fboNumSamples			= setting_data.getValue("fbo_num_samples",0,0);

	if(gridRes > 20){
		gridRes = 20;
	}
	if(gridRes < 1){
		gridRes = 1;
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// get AUDIO settings
	audioActivated			= setting_data.getValue("audio_activated",0,0);
	audioDevID				= setting_data.getValue("audio_Dev_ID",0,0);
	audioOutputChannels		= setting_data.getValue("output_ch",0,0);
	audioInputChannels		= setting_data.getValue("input_ch",0,0);
	audioSamplingRate		= setting_data.getValue("sampling_rate",0,0);
	audioBufferSize			= setting_data.getValue("buffer_size",0,0);
	audioNumBuffers			= setting_data.getValue("num_buffers",0,0);
	fftWindowUse			= setting_data.getValue("fft_window",0,0);

	if(!audioActivated){
		audioInputChannels = 0;
		audioOutputChannels = 0;
	}
	//////////////////////////////////////////////

    //////////////////////////////////////////////
	// get MIDI settings
    midiPortNumber          = setting_data.getValue("midi_port",0,0);
    //////////////////////////////////////////////

	//////////////////////////////////////////////
	// get ARDUINO settings
	arduinoActivated		= setting_data.getValue("arduino_activated",0,0);
	serialDevice			= setting_data.getValue("serial_device_name"," ",0);
	baudRate				= setting_data.getValue("baud_rate",0,0);
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// get OSC settings
	host_number				= setting_data.getValue("host_ip"," ",0);
	host_port				= setting_data.getValue("host_port"," ",0);
    server_port             = setting_data.getValue("server_port"," ",0);
	//////////////////////////////////////////////

    //////////////////////////////////////////////
	// get SYSTEM settings
    gamuzaFont              = setting_data.getValue("ga_font"," ",0);
    gamuzaFontSize          = setting_data.getValue("ga_font_size",0,0);
    //////////////////////////////////////////////

}

