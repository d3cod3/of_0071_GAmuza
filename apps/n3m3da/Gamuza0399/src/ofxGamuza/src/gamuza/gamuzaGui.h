#ifndef _GAMUZAGUI
#define _GAMUZAGUI

#include "gamuzaConstants.h"
#include "gamuzaFBO.h"

/* PALETA
 *
 * glColor4f(0.941,0.941,0.941,1.0);		// 240, 240, 240
 * glColor4f(0.863,0.863,0.863,1.0);		// 220, 220, 220
 * glColor4f(0.353,0.353,0.353,1.0);		// 90, 90, 90
 * glColor4f(0.0784,0.0784,0.0784,1.0);		// 20, 20, 20
 * glColor4f(1.0,0.906,0.463,1.0);			// 255, 231, 118
 * glColor4f(0.847,0.25,0.25,1.0);			// 213, 64, 64
 *
 */

//////////////////////////////////////////////
// GUI vars
ofTrueTypeFont				fontSmall;
ofVideoGrabber				fake;

vector<string>				bgSubTechniques;
vector<string>				sourceFlipUse;
vector<string>				cfDetailUse;
vector<string>				ardDigitalPinModes;
vector<string>				ardDigitalPinModesPWM;
vector<string>				ardAnalogPinModes;

ofImage						_empty;
ofImage						_empty_audio;
ofImage                     _hueWheel;
ofImage						gamuzaLogo;
ofImage						splashImage;
ofImage						arduinoGraphics;
simpleColor					gamuzaMainColor;
simpleColor					gamuzaWhiteColor;
simpleColor					gamuzaMarkColor;
simpleColor					gamuzaChartBackColor;
bool						splashFinish;
int							splashWait;
//////////////////////////////////////////////

//--------------------------------------------------------------
void gamuzaMain::setupGui(){

	char xml_name[256];
	char temp[128];

	///////////////////////////////////////////////
	// load fonts
	fontSmall.loadFont(gamuzaFont, gamuzaFontSize, true, true);
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	// activate fake video grabber to obtain devices info
	if(trackingActivated){
		fake.setVerbose(true);

        #ifdef TARGET_LINUX
            fake.initGrabber(320, 240);
            fake.listDevices();
        #endif
        #ifdef TARGET_OSX
            fake.listDevices();
            fake.initGrabber(320, 240);
        #endif

		// obtain cam devices available number
		numCamInputs = fake.getAvailableDevicesNum();

		camDevices	= new int[numCamInputs];
		deviceNames	= new string[numCamInputs];
		inputCam	= new sourceTracking[numCamInputs];

		// obtain cam devices id
		camDevices = fake.getAvailableIDs();

		// obtain cam devices names
		deviceNames = fake.getAvailableNames();

		fake.close();
	}else{
		numCamInputs = 0;
	}
	///////////////////////////////////////////////

	///////////////////////////////////////////////
	// retrieve dinamic multi panel(webcam & audio inputs) gui indexes
	if(!openniActivated || !sensorKinect.isOniConnected){
		webcamsStartIndex	 = 1;
		audioInputStartIndex = 1 + numCamInputs;
	}else if(openniActivated && sensorKinect.isOniConnected){
		sensorKinectIndex	 = 1;
		webcamsStartIndex	 = sensorKinectIndex + 1;
		audioInputStartIndex = webcamsStartIndex + numCamInputs;
	}

	if(arduinoActivated){
		arduinoIndex = audioInputStartIndex + audioInputChannels;
		oscIndex	 = arduinoIndex + 1;
	}else if(!arduinoActivated){
		oscIndex = audioInputStartIndex + audioInputChannels;
	}

	///////////////////////////////////////////////

	//////////////////////////////////////////////
	// init splash/intro image
	gamuzaLogo.loadImage(GAMUZA_LOGO);

	splashImage.loadImage(GAMUZA_SPLASH);
	if(trackingActivated && (!openniActivated || !sensorKinect.isOniConnected)){
		splashWait = 4000*numCamInputs;
	}else if(openniActivated && sensorKinect.isOniConnected && !trackingActivated){
		splashWait = 20000 + 1000*audioInputChannels;
	}else if(openniActivated && sensorKinect.isOniConnected && trackingActivated){
		splashWait = 4000*numCamInputs + 20000 + 1000*audioInputChannels;
	}else{
		splashWait = 1000*audioInputChannels;
	}
	splashFinish = false;

	// empty containers
	_empty.loadImage("img/empty.png");
    _empty_audio.loadImage("img/empty_audio.png");
    _hueWheel.loadImage("img/hueWheel.jpg");
	emptyTexture.allocate(workingW,workingH,GL_RGB);
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// gui string vectors init
	setupStringVec();
    //////////////////////////////////////////////

    //////////////////////////////////////////////
    // timeline init
    showTimeline = false;
    actualTriggerName = "";
    initTimeline();
    ofAddListener(ofxTLEvents.trigger, this, &gamuzaMain::receivedTrigger);
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// Main GUI setup
	gamuzaMainColor         = simpleColor(9,147,211,255);
	gamuzaWhiteColor        = simpleColor(240,240,240,255);
	gamuzaMarkColor         = simpleColor(255,231,118,255);
    gamuzaChartBackColor    = simpleColor(40, 40, 40, 255);

	gui.loadFont(gamuzaFont, gamuzaFontSize);
	gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
	gui.setTextColor(gamuzaWhiteColor,simpleColor(240, 240, 240, 225));
	gui.setOutlineColor(simpleColor(0,0,0,255));

	if(isFullscreen){
		guiPosX = ((mainScreenW - MAIN_WINDOW_W)/2.0) + 1.0;
		guiPosY = ((mainScreenH - MAIN_WINDOW_H)/2.0) + 3.0;
		if(projectionScreenW < mainScreenW){
			lcPrevW	 = (projectionScreenW*mainScreenH)/projectionScreenH;
			lcPrevH	 = mainScreenH;
			lcPrevX	 = (mainScreenW-lcPrevW)/2.0;
			lcPrevY  = 0;
		}else{
			lcPrevW	 = mainScreenW;
			lcPrevH	 = (projectionScreenH*mainScreenW)/projectionScreenW;
			lcPrevX	 = 0;
			lcPrevY  = (mainScreenH-lcPrevH)/2.0;
		}
	}else{
		guiPosX = 0.0;
		guiPosY = 0.0;
		if(projectionScreenW < MAIN_WINDOW_W){
			lcPrevW	 = (projectionScreenW*MAIN_WINDOW_H)/projectionScreenH;
			lcPrevH	 = MAIN_WINDOW_H;
			lcPrevX	 = (MAIN_WINDOW_W-lcPrevW)/2.0;
			lcPrevY  = 0;
		}else{
			lcPrevW	 = MAIN_WINDOW_W;
			lcPrevH	 = (projectionScreenH*MAIN_WINDOW_W)/projectionScreenW;
			lcPrevX	 = 0;
			lcPrevY  = (MAIN_WINDOW_H-lcPrevH)/2.0;
		}
	}
	gui.setup("   ", guiPosX, guiPosY, MAIN_WINDOW_W-2, MAIN_WINDOW_H-6);
	gui.setDraggable(false);
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// Live Coding GUI
	gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
	gui.setOutlineColor(simpleColor(0,0,0,255));
	sprintf(temp," LIVE CODING [SECOND SCREEN FULLSCREEN OUTPUT @ %i x %i]",projectionScreenW,projectionScreenH);
	gui.addPanel(temp, 5);
	gui.setWhichPanel(temp);

	gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
	gui.setOutlineColor(simpleColor(0,0,0,255));
	gui.setWhichColumn(0);
	//////////////////////////////////////////////
	gui.setTextColor(gamuzaMainColor);
	gui.addLabel("MAPPING SETTINGS");
	gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

	sprintf(xml_name,"DRAW_FBO_GRID");
	gui.addToggle("DRAW MAPPING GRID", xml_name, false);
    sprintf(xml_name,"RESET_FBO_MAPPING_COORDS");
	gui.addToggle("RESET MAPPING POINTS", xml_name, false);
    sprintf(xml_name,"LOAD_FBO_MAPPING_COORDS");
	gui.addToggle("LOAD MAPPING SETTING", xml_name, false);
    sprintf(xml_name,"SAVE_FBO_MAPPING_COORDS");
	gui.addToggle("SAVE MAPPING SETTING", xml_name, false);
	//////////////////////////////////////////////
	if(useShader){
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("COLOR CORRECTION SETTINGS");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		sprintf(xml_name,"OUTPUT_FBO_GAMMA");
		gui.addSlider("GAMMA CORRECTION",xml_name,fbo_gammaCorrection,1.0f,4.0f,false);
		sprintf(xml_name,"OUTPUT_FBO_BRIGHTNESS");
		gui.addSlider("BRIGHTNESS",xml_name,fbo_brightness,0.0f,4.0f,false);
		sprintf(xml_name,"OUTPUT_FBO_SATURATION");
		gui.addSlider("SATURATION",xml_name,fbo_saturation,0.0f,4.0f,false);
		sprintf(xml_name,"OUTPUT_FBO_CONTRAST");
		gui.addSlider("CONTRAST",xml_name,fbo_contrast,0.0f,2.0f,false);
		sprintf(xml_name,"OUTPUT_FBO_FILMBLEACH");
		gui.addSlider("FILM BLEACH",xml_name,fbo_filmBleach,0.0f,2.0f,false);
		sprintf(xml_name,"OUTPUT_FBO_FILM_TECHNICOLOR");
		gui.addSlider("FILM TECHNICOLOR",xml_name,fbo_techniColor,0.0f,2.0f,false);
		sprintf(xml_name,"OUTPUT_FBO_FILM_WHITEDIFFUSION");
		gui.addSlider("FILM FORCE B&W",xml_name,fbo_whiteDiffusion,0.0f,1.0f,false);
		sprintf(xml_name,"OUTPUT_FBO_FILM_EXPOSURE");
		gui.addSlider("FILM WHITE EXPOSURE",xml_name,fbo_exposure,0.0f,10.0f,false);
		sprintf(xml_name,"OUTPUT_FBO_FILM_DIFFUSION");
		gui.addSlider("FILM WHITE DIFFUSION",xml_name,fbo_diffusion,0.0f,4.0f,false);
	}
	//////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
    gui.addLabel("VIDEO OUTPUT SETTINGS");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    sprintf(xml_name,"USE_SECONDARY_SCREEN");
	gui.addToggle("ACTIVATE SECONDARY SCREEN", xml_name, true);
	sprintf(xml_name,"ACTIVATE_LIVE_EDITOR");
	gui.addToggle("ACTIVATE EDITOR", xml_name, false);
    sprintf(xml_name,"USE_VSYNC");
	gui.addToggle("USE VERTICAL SYNC", xml_name, false);
    //////////////////////////////////////////////

	gui.setWhichColumn(1);
	//////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
	gui.addDrawableRect(" ", &kuro,800, 580); // 800 x (projectionScreenH*800.0f)/projectionScreenW  | 512, 384
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    //////////////////////////////////////////////
    gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
    gui.addChartPlotter("FPS", guiStatVarPointer("FPS", &gamuzaRealFPS, GUI_VAR_FLOAT, true, 2), 800, 50, 200, 1, 200);
	//////////////////////////////////////////////

	gui.setWhichColumn(2);
	//////////////////////////////////////////////

    gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
    scriptsLister.listDir("scripts/");
	gui.addFileLister("SCRIPT EXAMPLES", &scriptsLister, 180, 580);
	gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
	sprintf(xml_name,"OPEN_SCRIPT_FILE_DIALOG");
	gui.addToggle("OPEN SCRIPT", xml_name, false);
	sprintf(xml_name,"SAVE_SCRIPT_FILE_DIALOG");
	gui.addToggle("SAVE SCRIPT", xml_name, false);
    //////////////////////////////////////////////

	//////////////////////////////////////////////
	// OpenNI SensorKinect GUI
	if(openniActivated && sensorKinect.isOniConnected){
		gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
		gui.setOutlineColor(simpleColor(0,0,0,255));
		sprintf(temp," OPENNI SENSOR KINECT DEVICE");
		gui.addPanel(temp, 5);
		gui.setWhichPanel(temp);

		gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
        gui.setOutlineColor(simpleColor(0,0,0,255));
		gui.setWhichColumn(0);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		gui.addDrawableRect("RECORD IMAGE", &_empty, 320, 240);
		gui.setTextColor(gamuzaMarkColor);
		sprintf(xml_name,"COMPUTE_SENSOR_KINECT");
		gui.addToggle("COMPUTE SENSOR KINECT", xml_name, true);
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
		gui.addDrawableRect("RECORD DEPTH", &_empty, 320, 240);
		sprintf(xml_name,"NEAR_THRESHOLD_SENSOR_KINECT");
		gui.addSlider("NEAR TRESHOLD",xml_name,sensorKinect.nearThreshold,300,1000,true);
		sprintf(xml_name,"FAR_THRESHOLD_SENSOR_KINECT");
		gui.addSlider("FAR TRESHOLD",xml_name,sensorKinect.farThreshold,1000,3000,true);

		gui.setWhichColumn(1);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		gui.addDrawableRect("DEPTH RANGE MASK", &sensorKinect.cleanImage, 320, 240);
		sprintf(xml_name,"USE_TRACKING_HANDS_SENSOR_KINECT");
		gui.addToggle("USE KINECT HANDS TRACKING", xml_name, true);
		gui.addDrawableRect("ALL USERS MASK", &_empty, 320, 240);

		gui.setWhichColumn(2);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("GENERAL SETTINGS");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		sprintf(xml_name,"CI_BLUR_SENSOR_KINECT");
		gui.addSlider("SENSOR KINECT BLUR", xml_name, sensorKinect.ciBlur, 0, 33, true);
		sprintf(xml_name,"CI_ERODE_SENSOR_KINECT");
		gui.addSlider("ERODE", xml_name, sensorKinect.ciErode, 0, 10, true);
		sprintf(xml_name,"CI_DILATE_SENSOR_KINECT");
		gui.addSlider("DILATE", xml_name, sensorKinect.ciDilate, 0, 10, true);

		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("MOTION DETECTION SETTINGS");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		sprintf(xml_name,"M_THRESHOLD_SENSOR_KINECT");
		gui.addSlider("MOTION THRESHOLD", xml_name, sensorKinect.mThreshold, 1, 300, true);
		sprintf(xml_name,"MOTION_ON_HORIZON_SENSOR_KINECT");
		gui.addSlider("MOTION TRIGGER LOW LIMIT", xml_name, sensorKinect.onHorizon, 1, 100, true);
		sprintf(xml_name,"MOTION_OFF_HORIZON_SENSOR_KINECT");
		gui.addSlider("MOTION TRIGGER RANGE LIMIT", xml_name, sensorKinect.offHorizon, 0, 200, true);
		gui.addDrawableRect("MOTION IMAGE", &sensorKinect.motionImg, 160, 120);
		//////////////////////////////////////////////

		gui.setWhichColumn(3);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("BLOB TRACKING SETTINGS");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		sprintf(xml_name,"MIN_BLOB_AREA_SENSOR_KINECT");
		gui.addSlider("MIN BLOB",xml_name,sensorKinect.minBlobArea,2,5000,true);
		sprintf(xml_name,"MAX_BLOB_AREA_SENSOR_KINECT");
		gui.addSlider("MAX BLOB",xml_name,sensorKinect.maxBlobArea,0,100000,true);
		sprintf(xml_name,"CF_DETAIL_SENSOR_KINECT");
        gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
        gui.addTextDropDown("CONTOUR DETAIL", xml_name, 0, cfDetailUse);
        gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
		sprintf(xml_name,"CF_SMOOTH_PCT_SENSOR_KINECT");
		gui.addSlider("CONTOUR SMOOTH FACTOR", xml_name,sensorKinect.smoothPct,0.01f,0.99f,false);
		sprintf(xml_name,"CF_TOLERANCE_SENSOR_KINECT");
		gui.addSlider("CONTOUR SIMPLE TOLERANCE", xml_name,sensorKinect.tolerance,0.01f,20.0f,false);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("COMPUTING ALGORITHM SELECTOR");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		sprintf(xml_name,"COMPUTE_CF_SENSOR_KINECT");
		gui.addToggle("COMPUTE CONTOUR FINDER", xml_name, false);
		sprintf(xml_name,"COMPUTE_CG_SENSOR_KINECT");
		gui.addToggle("COMPUTE CONTOUR GEOMETRY", xml_name, false);
		sprintf(xml_name,"COMPUTE_OF_SENSOR_KINECT");
		gui.addToggle("COMPUTE OPTICAL FLOW", xml_name, false);
		sprintf(xml_name,"COMPUTE_TA_SENSOR_KINECT");
		gui.addToggle("COMPUTE TRIGGER AREAS", xml_name, false);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("OSC DATA SETTINGS");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		sprintf(xml_name,"USE_KALMAN_FILTER_SENSOR_KINECT");
		gui.addToggle("USE KALMAN FILTER", xml_name, false);
		sprintf(xml_name,"SMOOTHING_FACTOR_SENSOR_KINECT");
		gui.addSlider("SMOOTHING FACTOR",xml_name,sensorKinect._smoothingFactor,0.01f,0.99f,false);

		gui.setWhichColumn(4);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("SENSOR KINECT HARDWARE");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

        gui.setBackgroundColor(gamuzaChartBackColor);
		sprintf(temp,"SENSOR TILT");
		gui.addChartPlotter(temp, guiStatVarPointer("ANGLE", &sensorKinect._osc_sensorTilt, GUI_VAR_FLOAT, true, 2), 110, 80, 200, 0.0f, 1.0f);
		sprintf(temp,"ACCELEROMETER X");
		gui.addChartPlotter(temp, guiStatVarPointer("X", &sensorKinect._osc_sensorAcc.x, GUI_VAR_FLOAT, true, 2), 110, 80, 200, 0.0f, 1.0f);
		sprintf(temp,"ACCELEROMETER Y");
		gui.addChartPlotter(temp, guiStatVarPointer("Y", &sensorKinect._osc_sensorAcc.y, GUI_VAR_FLOAT, true, 2), 110, 80, 200, 0.0f, 1.0f);
		sprintf(temp,"ACCELEROMETER Z");
		gui.addChartPlotter(temp, guiStatVarPointer("Z", &sensorKinect._osc_sensorAcc.z, GUI_VAR_FLOAT, true, 2), 110, 80, 200, 0.0f, 1.0f);

	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// Video Tracking multi-panel GUI
	if(trackingActivated){
		for(unsigned int i=0;i<numCamInputs;i++){
			if(useVideoTest){
				inputCam[i].setupCam(i,workingW,workingH,camDevices[i],true,haarFinderFile,_videoTestFile);
			}else{
				inputCam[i].setupCam(i,workingW,workingH,camDevices[i],false,haarFinderFile,_videoTestFile);
			}

			gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
			gui.setOutlineColor(simpleColor(0,0,0,255));
			sprintf(temp," CAM DEVICE [%i] | %s",camDevices[i],deviceNames[i].c_str());
			gui.addPanel(temp, 5);

			gui.setWhichPanel(temp);
			gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
            gui.setOutlineColor(simpleColor(0,0,0,255));

			gui.setWhichColumn(0);
			gui.addDrawableRect("COLOR INPUT", &inputCam[i].colorImg, 240, 180);

			gui.setTextColor(gamuzaMarkColor);
			sprintf(xml_name,"USE_DEVICE_%i",camDevices[i]);
			gui.addToggle("USE DEVICE", xml_name, true);
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
			sprintf(xml_name,"UNDISTORT_INPUT_%i",camDevices[i]);
			gui.addToggle("UNDISTORT [LENS CORRECTION]", xml_name, false);
			gui.addDrawableRect("MOTION DETECTION", &inputCam[i].motionGUI, 160, 120);
			sprintf(xml_name,"RESET_INPUT_WARPING_DEV_%i",camDevices[i]);
			gui.addToggle("RESET QUAD WARPING", xml_name, false);

			gui.setWhichColumn(1);
			gui.addDrawableRect("BALANCED TRACKING", &inputCam[i].balancedTracking, 240, 180);
			sprintf(xml_name,"BG_CAPTURE_%i",camDevices[i]);
			gui.addToggle("CAPTURE BACKGROUND", xml_name, true);
			sprintf(xml_name,"BG_USE_STRECH_%i",camDevices[i]);
			gui.addToggle("USE CONTRAST STRETCH", xml_name, true);
			gui.addDrawableRect("BACKGROUND SUBTRACTION", &inputCam[i].grayThresh, 160, 120);
			sprintf(xml_name,"USE_COLOR_TRACKING_%i",camDevices[i]);
			gui.addToggle("USE COLOR TRACKING", xml_name, true);
			gui.addDrawableRect("COLOR TRACKING", &inputCam[i].hsvTracking, 160, 120);

			gui.setWhichColumn(2);
			gui.setTextColor(gamuzaMainColor);
			gui.addLabel("GENERAL SETTINGS");
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

			//////////////////////////////////////////////
			sprintf(xml_name,"FLIP_SOURCE_USE_%i",camDevices[i]);
            gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
			gui.addTextDropDown("FLIP SOURCE IMAGE ", xml_name, 1, sourceFlipUse);
            gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
			//////////////////////////////////////////////
			sprintf(xml_name,"INPUT_BLUR_%i",camDevices[i]);
			gui.addSlider("SOURCE BLUR", xml_name, inputCam[i].colorImgBlur, 0, 33, true);
			sprintf(xml_name,"CONTRAST_%i",camDevices[i]);
			gui.addSlider("CONTRAST", xml_name, inputCam[i].contrast, 0.0, 1.0f, false);
			sprintf(xml_name,"BRIGHTNESS_%i",camDevices[i]);
			gui.addSlider("BRIGHTNESS", xml_name, inputCam[i].brightness, -1.0, 3.0f, false);
			//////////////////////////////////////////////
			gui.setTextColor(gamuzaMainColor);
			gui.addLabel("BACKGROUND SUBTRACTION SETTINGS");
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

			sprintf(xml_name,"BGSUB_TECH_%i",camDevices[i]);
            gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
            gui.addTextDropDown("SUBTRACTION TECHNIQUE ", xml_name, 3, bgSubTechniques);
            gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
			sprintf(xml_name,"BGSUB_THRESHOLD_%i",camDevices[i]);
			gui.addSlider("SUBTRACTION THRESHOLD", xml_name, inputCam[i].threshold, 1, 254, true);
			sprintf(xml_name,"BGSUB_BLUR_%i",camDevices[i]);
			gui.addSlider("BLUR", xml_name, inputCam[i].bgSubBlur, 0, 33, true);
			sprintf(xml_name,"BGSUB_ERODE_%i",camDevices[i]);
			gui.addSlider("ERODE", xml_name, inputCam[i].bgSubErode, 0, 10, true);
			sprintf(xml_name,"BGSUB_DILATE_%i",camDevices[i]);
			gui.addSlider("DILATE", xml_name, inputCam[i].bgSubDilate, 0, 10, true);
			//////////////////////////////////////////////
			gui.setTextColor(gamuzaMainColor);
			gui.addLabel("OSC DATA SETTINGS");
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
			sprintf(xml_name,"USE_KALMAN_FILTER_%i",camDevices[i]);
			gui.addToggle("USE KALMAN FILTER", xml_name, false);
			sprintf(xml_name,"SMOOTHING_FACTOR_%i",camDevices[i]);
			gui.addSlider("SMOOTHING FACTOR",xml_name,inputCam[i]._smoothingFactor,0.01f,0.99f,false);
			//////////////////////////////////////////////

			gui.setWhichColumn(3);
			//////////////////////////////////////////////
			gui.setTextColor(gamuzaMainColor);
			gui.addLabel("COLOR TRACKING SETTINGS");
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

            gui.addDrawableRect(" ", &_hueWheel,180, 8);
			sprintf(xml_name,"HUE_%i",camDevices[i]);
			gui.addSlider("HUE", xml_name, inputCam[i].hue, 0.0, 1.0f, false);
			sprintf(xml_name,"HUE_WIDTH_%i",camDevices[i]);
			gui.addSlider("HUE RANGE", xml_name, inputCam[i].hueWidth, 0.0, 1.0f, false);
			sprintf(xml_name,"SAT_%i",camDevices[i]);
			gui.addSlider("SATURATION", xml_name, inputCam[i].sat, 0.0, 1.0f, false);
			sprintf(xml_name,"SAT_WIDTH_%i",camDevices[i]);
			gui.addSlider("SATURATION RANGE", xml_name, inputCam[i].satWidth, 0.0, 1.0f, false);
			sprintf(xml_name,"VAL_%i",camDevices[i]);
			gui.addSlider("VALUE", xml_name, inputCam[i].val, 0.0, 1.0f, false);
			sprintf(xml_name,"VAL_WIDTH_%i",camDevices[i]);
			gui.addSlider("VALUE RANGE", xml_name, inputCam[i].valWidth, 0.0, 1.0f, false);
			sprintf(xml_name,"HSV_BLUR_%i",camDevices[i]);
			gui.addSlider("HSV BLUR", xml_name, inputCam[i].hsvBlur, 0, 33, true);
			sprintf(xml_name,"HSV_ERODE_%i",camDevices[i]);
			gui.addSlider("ERODE", xml_name, inputCam[i].hsvErode, 0, 10, true);
			sprintf(xml_name,"HSV_DILATE_%i",camDevices[i]);
			gui.addSlider("DILATE", xml_name, inputCam[i].hsvDilate, 0, 10, true);
			//////////////////////////////////////////////
			gui.setTextColor(gamuzaMainColor);
			gui.addLabel("MOTION DETECTION SETTINGS");
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

			sprintf(xml_name,"M_THRESHOLD_%i",camDevices[i]);
			gui.addSlider("MOTION THRESHOLD", xml_name, inputCam[i].mThreshold, 1, 300, true);
			sprintf(xml_name,"M_NOISE_COMP_%i",camDevices[i]);
			gui.addSlider("MOTION NOISE COMPENSATION", xml_name, inputCam[i].mNoiseComp, 0, 1000, true);
			sprintf(xml_name,"MOTION_ON_HORIZON_%i",camDevices[i]);
			gui.addSlider("MOTION TRIGGER LOW LIMIT", xml_name, inputCam[i].onHorizon, 1, 100, true);
			sprintf(xml_name,"MOTION_OFF_HORIZON_%i",camDevices[i]);
			gui.addSlider("MOTION TRIGGER RANGE LIMIT", xml_name, inputCam[i].offHorizon, 0, 200, true);
			//////////////////////////////////////////////

			gui.setWhichColumn(4);
			//////////////////////////////////////////////
            gui.setTextColor(gamuzaMainColor);
			gui.addLabel("BLOB TRACKING SETTINGS");
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

			sprintf(xml_name,"MIN_BLOB_AREA_%i",camDevices[i]);
			gui.addSlider("MIN BLOB",xml_name,inputCam[i].minBlobArea,2,5000,true);
			sprintf(xml_name,"MAX_BLOB_AREA_%i",camDevices[i]);
			gui.addSlider("MAX BLOB",xml_name,inputCam[i].maxBlobArea,0,100000,true);
			sprintf(xml_name,"CF_DETAIL_%i",camDevices[i]);
            gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
            gui.addTextDropDown("CONTOUR DETAIL", xml_name, 0, cfDetailUse);
            gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
			sprintf(xml_name,"CF_SMOOTH_PCT_%i",camDevices[i]);
			gui.addSlider("CONTOUR SMOOTH FACTOR", xml_name,inputCam[i].smoothPct,0.01f,0.99f,false);
			sprintf(xml_name,"CF_TOLERANCE_%i",camDevices[i]);
			gui.addSlider("CONTOUR SIMPLE TOLERANCE", xml_name,inputCam[i].tolerance,0.01f,20.0f,false);
			//////////////////////////////////////////////
			gui.setTextColor(gamuzaMainColor);
			gui.addLabel("BALANCED TRACKING SETTINGS");
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

			sprintf(xml_name,"BT_BLUR_%i",camDevices[i]);
			gui.addSlider("BALANCED TRACKING BLUR", xml_name, inputCam[i].btBlur, 0, 33, true);
			sprintf(xml_name,"BT_ERODE_%i",camDevices[i]);
			gui.addSlider("ERODE", xml_name, inputCam[i].btErode, 0, 10, true);
			sprintf(xml_name,"BT_DILATE_%i",camDevices[i]);
			gui.addSlider("DILATE", xml_name, inputCam[i].btDilate, 0, 10, true);
			//////////////////////////////////////////////
			gui.setTextColor(gamuzaMainColor);
			gui.addLabel("COMPUTING ALGORITHM SELECTOR");
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

			sprintf(xml_name,"COMPUTE_CF_%i",camDevices[i]);
			gui.addToggle("COMPUTE CONTOUR FINDER", xml_name, false);
			sprintf(xml_name,"COMPUTE_CG_%i",camDevices[i]);
			gui.addToggle("COMPUTE CONTOUR GEOMETRY", xml_name, false);
			sprintf(xml_name,"COMPUTE_OF_%i",camDevices[i]);
			gui.addToggle("COMPUTE OPTICAL FLOW", xml_name, false);
			sprintf(xml_name,"COMPUTE_FT_%i",camDevices[i]);
			gui.addToggle("COMPUTE HAAR FINDER", xml_name, false);
			sprintf(xml_name,"COMPUTE_TA_%i",camDevices[i]);
			gui.addToggle("COMPUTE TRIGGER AREAS", xml_name, false);
			//////////////////////////////////////////////

		}
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// Audio Source multi-panel GUI
	if(audioActivated){
		for(unsigned int i=0;i<audioInputChannels;i++){

			inputAudioCH[i].loadNoiseFilter();
			sprintf(temp," AUDIO INPUT [CHANNEL %i]",i);
			gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
			gui.setOutlineColor(simpleColor(0,0,0, 255));
			gui.addPanel(temp, 5);
			gui.setWhichPanel(temp);
			gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
            gui.setOutlineColor(simpleColor(0,0,0,255));

			gui.setWhichColumn(0);
			//////////////////////////////////////////////
			gui.setTextColor(gamuzaMainColor);
			gui.addLabel("GENERAL SETTINGS");

			gui.setTextColor(gamuzaMarkColor);
			sprintf(xml_name,"USE_AUDIO_INPUT_%i",i);
			gui.addToggle("USE INPUT CHANNEL", xml_name, false);
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

			sprintf(xml_name,"VOLUME_AUDIO_INPUT_%i",i);
			gui.addSlider("VOLUME", xml_name, inputAudioCH[i]._volume,0.01f,1.0f,false);
			sprintf(xml_name,"MUTE_AUDIO_INPUT_%i",i);
			gui.addToggle("MUTE", xml_name, false);
			//////////////////////////////////////////////
			gui.setTextColor(gamuzaMainColor);
			gui.addLabel("NOISE REDUCTION SETTINGS");
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

			sprintf(xml_name,"REC_NOISE_FILTER_%i",i);
			gui.addToggle("REC NOISE", xml_name, false);
			sprintf(xml_name,"NOISE_REDUX_FACTOR_%i",i);
			gui.addSlider("REDUX FACTOR", xml_name, inputAudioCH[i].reduxFactor,1.0f,10.0f,false);
			//////////////////////////////////////////////
			gui.setTextColor(gamuzaMainColor);
			gui.addLabel("PARAMETRIC EQUALIZATION");
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);


			sprintf(xml_name,"EQ_BAND1_CENTER_%i",i);
			gui.addSlider("BAND 1 CENTER [BIN]", xml_name, inputAudioCH[i].eqLOWCenter,0.0f,audioBufferSize/2.0f,false);
			sprintf(xml_name,"EQ_BAND1_AMPLITUDE_%i",i);
			gui.addSlider("BAND 1 AMPLITUDE [DB]", xml_name, inputAudioCH[i].eqLOWAmplitude,-3.0f,6.0f,false);
			sprintf(xml_name,"EQ_BAND1_WIDTH_%i",i);
			gui.addSlider("BAND 1 WIDTH [Q]", xml_name, inputAudioCH[i].eqLOWWidth,0.01f,audioBufferSize/4.0f,false);
			//////////////////////////////////////////////
			sprintf(xml_name,"EQ_BAND2_CENTER_%i",i);
			gui.addSlider("BAND 2 CENTER [BIN]", xml_name, inputAudioCH[i].eqMIDCenter,0.0f,audioBufferSize/2.0f,false);
			sprintf(xml_name,"EQ_BAND2_AMPLITUDE_%i",i);
			gui.addSlider("BAND 2 AMPLITUDE [DB]", xml_name, inputAudioCH[i].eqMIDAmplitude,-3.0f,6.0f,false);
			sprintf(xml_name,"EQ_BAND2_WIDTH_%i",i);
			gui.addSlider("BAND 2 WIDTH [Q]", xml_name, inputAudioCH[i].eqMIDWidth,0.01f,audioBufferSize/4.0f,false);
			//////////////////////////////////////////////
			sprintf(xml_name,"EQ_BAND3_CENTER_%i",i);
			gui.addSlider("BAND 3 CENTER [BIN]", xml_name, inputAudioCH[i].eqHICenter,0.0f,audioBufferSize/2.0f,false);
			sprintf(xml_name,"EQ_BAND3_AMPLITUDE_%i",i);
			gui.addSlider("BAND 3 AMPLITUDE [DB]", xml_name, inputAudioCH[i].eqHIAmplitude,-3.0f,6.0f,false);
			sprintf(xml_name,"EQ_BAND3_WIDTH_%i",i);
			gui.addSlider("BAND 3 WIDTH [Q]", xml_name, inputAudioCH[i].eqHIWidth,0.01f,audioBufferSize/4.0f,false);
			//////////////////////////////////////////////

			gui.setWhichColumn(1);
			//////////////////////////////////////////////
			gui.setTextColor(gamuzaMainColor);
			gui.addLabel("OSC DATA SETTINGS");
			gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

			sprintf(xml_name,"USE_KALMAN_FILTER_AUDIOCH_%i",i);
			gui.addToggle("USE KALMAN FILTER", xml_name, false);
			sprintf(xml_name,"SMOOTHING_FACTOR_AUDIOCH_%i",i);
			gui.addSlider("SMOOTHING FACTOR",xml_name,inputAudioCH[i]._smoothingFactor,0.01f,0.99f,false);
			//////////////////////////////////////////////
            gui.setBackgroundColor(gamuzaChartBackColor);
			gui.addChartPlotter("VOLUME CHART", guiStatVarPointer("CHANNEL VOLUME", &inputAudioCH[i]._osc_chVolume, GUI_VAR_FLOAT, true, 2), 180, 80, 200, 0.0f, 1.0f);
			gui.addChartPlotter("PITCH CHART", guiStatVarPointer("CHANNEL PITCH", &inputAudioCH[i]._s_chPitch, GUI_VAR_FLOAT, true, 2), 180, 80, 200, 20.0f, 20000.0f);

		}
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// Serial GUI [Arduino]
	if(arduinoActivated){

		arduinoGraphics.loadImage("img/arduino.png");

		gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
		gui.setOutlineColor(simpleColor(0,0,0, 255));
		sprintf(temp," ARDUINO DEVICE CONNECTED AT SERIAL PORT %s | WITH BAUDRATE %i", serialDevice.c_str(), baudRate);
		gui.addPanel(temp, 5);
		gui.setWhichPanel(temp);
		gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
		gui.setOutlineColor(simpleColor(0,0,0,255));

		gui.setWhichColumn(0);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("ANALOG VALUES READING [0 | 5]");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

        gui.setBackgroundColor(gamuzaChartBackColor);
		for(unsigned int i=0;i<6;i++){
			sprintf(temp,"ANALOG PIN %i ",i);
			gui.addChartPlotter(temp, guiStatVarPointer("READING", &_s_analogPinValues[i], GUI_VAR_FLOAT, true, 2), 180, 80, 200, 0.0, 1023.0);
		}
        gui.setBackgroundColor(simpleColor(90, 90, 90, 255));

		gui.setWhichColumn(1);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("ANALOG PINS CONTROL [0 | 5]");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

        gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
		for(unsigned int i=0;i<6;i++){
			sprintf(xml_name,"ARDUINO_ANALOG_PIN_%i_MODE",i);
			sprintf(temp,"PIN %i ",i);
            gui.addTextDropDown(temp, xml_name, 1, ardAnalogPinModes);
		}
        gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));

		gui.setWhichColumn(2);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("ARDUINO BOARD");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		gui.setTextColor(gamuzaMarkColor);
		sprintf(xml_name,"USE_ARDUINO");
		gui.addToggle("USE ARDUINO", xml_name, true);
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
		gui.addDrawableRect(" ", &arduinoGraphics, 360, 475);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("OSC DATA SETTINGS");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		sprintf(xml_name,"USE_KALMAN_FILTER_ARDUINO");
		gui.addToggle("USE KALMAN FILTER", xml_name, false);
		sprintf(xml_name,"SMOOTHING_FACTOR_ARDUINO");
		gui.addSlider("SMOOTHING FACTOR",xml_name,arduino_smoothingFactor,0.01f,0.99f,false);

		gui.setWhichColumn(3);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("DIGITAL PINS CONTROL [2 | 13]");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		//////////////////////////////////////////////
        gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
		for(unsigned int i=2;i<14;i++){
			sprintf(xml_name,"ARDUINO_DIGITAL_PIN_%i_MODE",i);
			if(i == 3 || i == 5 || i == 6 || i == 9 || i == 10 || i == 11){
				sprintf(temp,"PIN [PWM] %i ",i);
				gui.addTextDropDown(temp, xml_name, 0, ardDigitalPinModesPWM);
			}else{
				sprintf(temp,"PIN %i ",i);
				gui.addTextDropDown(temp, xml_name, 0, ardDigitalPinModes);
			}
		}
        gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));

		gui.setWhichColumn(4);
		//////////////////////////////////////////////
		gui.setTextColor(gamuzaMainColor);
		gui.addLabel("DIGITAL VALUES WRITING [2 | 13]");
		gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

		//////////////////////////////////////////////
		for(unsigned int i=2;i<14;i++){
			sprintf(xml_name,"ARDUINO_DIGITAL_PIN_%i_VALUE",i);
			if(i == 3 || i == 5 || i == 6 || i == 9 || i == 10 || i == 11){
				sprintf(temp,"PIN %i PWM [0 254]",i);
				gui.panels.at(gui.currentPanel)->setElementYSpacing(-5);
				gui.addSlider(temp,xml_name,digitalPinValuesOutput[i-2],0,254,true);
				gui.setTextColor(simpleColor(0,0,0, 0));
				gui.setForegroundColor(simpleColor(90, 90, 90, 100),simpleColor(0, 255, 20, 255));
                gui.setBackgroundColor(simpleColor(90, 90, 90, 55));
				gui.panels.at(gui.currentPanel)->setElementYSpacing(15);
				gui.addChartPlotter(temp, guiStatVarPointer(" ", &digitalPinValuesInput[i-2], GUI_VAR_INT, true, 2), 180, 8, 200, 0, 255);
                gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
                gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
                gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
			}else{
				sprintf(temp,"PIN %i LOW | HIGH",i);
				gui.panels.at(gui.currentPanel)->setElementYSpacing(-5);
				gui.addToggle(temp, xml_name, true);
				gui.setTextColor(simpleColor(0,0,0, 0));
				gui.setForegroundColor(simpleColor(90, 90, 90, 100),simpleColor(0, 255, 20, 255));
                gui.setBackgroundColor(simpleColor(90, 90, 90, 55));
				gui.panels.at(gui.currentPanel)->setElementYSpacing(15);
				gui.addChartPlotter(temp, guiStatVarPointer(" ", &digitalPinValuesInput[i-2], GUI_VAR_INT, true, 2), 180, 8, 200, 0, 1);
                gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
                gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
                gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
			}
		}


	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// OSC GUI [Open Sound Control Output DATA]
    gui.setBackgroundColor(simpleColor(20, 20, 20, 255));
    gui.setOutlineColor(simpleColor(0,0,0,255));
    sprintf(temp," OSC DATA SENDING AT HOST %s : PORT %s ",host_number.c_str(),host_port.c_str());
    gui.addPanel(temp, 5);
    gui.setWhichPanel(temp);
    gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
    gui.setOutlineColor(simpleColor(0,0,0,255));

    gui.setWhichColumn(0);

    if(openniActivated && sensorKinect.isOniConnected){
        //////////////////////////////////////////////
        gui.setTextColor(gamuzaMainColor);
        gui.addLabel("OPENNI SENSOR KINECT OSC DATA");
        gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_BD");
        gui.addToggle("SEND BLOB DETECTION DATA", xml_name, true);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_CF");
        gui.addToggle("SEND CONTOUR FINDER DATA", xml_name, true);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_CG");
        gui.addToggle("SEND CONTOUR GEOMETRY DATA", xml_name, true);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_OF");
        gui.addToggle("SEND OPTICAL FLOW LK DATA", xml_name, true);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_TA");
        gui.addToggle("SEND TRIGGER AREAS DATA", xml_name, true);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_HT");
        gui.addToggle("SEND HAND TRACKING DATA", xml_name, true);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_HW");
        gui.addToggle("SEND SENSOR HARDWARE DATA", xml_name, true);

    }
    //////////////////////////////////////////////

    if(arduinoActivated){
        //////////////////////////////////////////////
        gui.setTextColor(gamuzaMainColor);
        gui.addLabel("ARDUINO [SERIAL PORT]");
        gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

        sprintf(xml_name,"ARDUINO_SEND_OSC_AAP");
        gui.addToggle("SEND ANALOG PINS DATA", xml_name, true);
        sprintf(xml_name,"ARDUINO_SEND_OSC_ADP");
        gui.addToggle("SEND DIGITAL PINS DATA", xml_name, true);

    }
    //////////////////////////////////////////////

    if(trackingActivated){
        for(unsigned int i=0;i<numCamInputs;i++){
            gui.setWhichColumn(i+1);
            //////////////////////////////////////////////
            gui.setTextColor(gamuzaMainColor);
            sprintf(temp,"DEV.[%i] | %s",camDevices[i],deviceNames[i].c_str());
            gui.addLabel(temp);
            gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_MD",camDevices[i]);
            gui.addToggle("SEND MOTION DETECTION DATA", xml_name, true);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_BD",camDevices[i]);
            gui.addToggle("SEND BLOB DETECTION DATA", xml_name, true);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_CF",camDevices[i]);
            gui.addToggle("SEND CONTOUR FINDER DATA", xml_name, true);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_CG",camDevices[i]);
            gui.addToggle("SEND CONTOUR GEOMETRY DATA", xml_name, true);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_OF",camDevices[i]);
            gui.addToggle("SEND OPTICAL FLOW LK DATA", xml_name, true);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_HF",camDevices[i]);
            gui.addToggle("SEND HAAR FINDER DATA", xml_name, true);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_TA",camDevices[i]);
            gui.addToggle("SEND TRIGGER AREAS DATA", xml_name, true);

        }

    }
    //////////////////////////////////////////////

    if(audioActivated){
        for(unsigned int i=0;i<audioInputChannels;i++){
            gui.setWhichColumn(i+1);
            //////////////////////////////////////////////
            gui.setTextColor(gamuzaMainColor);
            sprintf(temp,"AUDIO INPUT [CHANNEL %i]",i);
            gui.addLabel(temp);
            gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);

            sprintf(xml_name,"AUDIO_INPUT_CH%i_SEND_OSC_VD",i);
            gui.addToggle("SEND VOLUME DETECTION DATA", xml_name, true);
            sprintf(xml_name,"AUDIO_INPUT_CH%i_SEND_OSC_PD",i);
            gui.addToggle("SEND PITCH DETECTION DATA", xml_name, true);
            sprintf(xml_name,"AUDIO_INPUT_CH%i_SEND_OSC_BK",i);
            gui.addToggle("SEND BARK SCALE DATA", xml_name, true);

        }

    }
    //////////////////////////////////////////////

	//////////////////////////////////////////////
	// Gamuza Setting Manager GUI
	gui.setBackgroundColor(simpleColor(20, 20, 20, 255));

	sprintf(temp," GAMUZA SETTING MANAGER");
	gui.addPanel(temp, 4);
	gui.setWhichPanel(temp);
    gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
    gui.setOutlineColor(simpleColor(0,0,0,255));
    gui.setWhichColumn(0);
	//////////////////////////////////////////////
    gui.setTextColor(gamuzaMarkColor);
    sprintf(xml_name,"RESTART_GAMUZA");
    gui.addToggle("RESTART", xml_name, true);
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
	gui.addLabel("MODULES");
	gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
	sprintf(xml_name,"__OPENNI_MODULE");
	gui.addToggle("SENSOR KINECT", xml_name, false);
	sprintf(xml_name,"__VIDEO_TRACKING_MODULE");
	gui.addToggle("COMPUTER VISION", xml_name, false);
	sprintf(xml_name,"__AUDIO_INPUT_MODULE");
	gui.addToggle("AUDIO STREAM (INPUT/OUTPUT)", xml_name, false);
	sprintf(xml_name,"__ARDUINO_MODULE");
	gui.addToggle("ARDUINO", xml_name, false);
	//////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
	gui.addLabel("SCREENS");
	gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
	gui.setBackgroundColor(simpleColor(0, 0, 0, 255));
	sprintf(xml_name,"__MAIN_SCREEN_SIZE_SEL");
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
	gui.addTextDropDown("MAIN SCREEN", xml_name, 2, _screenSizesMain);
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	sprintf(xml_name,"__SECONDARY_SCREEN_SIZE_SEL");
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
	gui.addTextDropDown("SECONDARY SCREEN", xml_name, 2, _screenSizesProj);
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
	//////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
	gui.addLabel("OUTPUT VIDEO MAPPING");
	gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    sprintf(xml_name,"__MAPPING_GRID_RES");
    gui.addSlider("MAPPING GRID RESOLUTION",xml_name,_mappingGridRes,1,20,true);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
	gui.addLabel("AUTOMATION (INSTALLATION MODE)");
	gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    sprintf(xml_name,"__AUTO_PILOT");
	gui.addToggle("AUTO FULLSCREEN", xml_name, false);
    sprintf(xml_name,"__AUTOLOAD_SCRIPT");
	gui.addToggle("AUTOLOAD SCRIPT ON START", xml_name, false);
    sprintf(xml_name,"__CHOOSE_SCRIPT");
    gui.addToggle("CHOOSE SCRIPT", xml_name, false);

    gui.setWhichColumn(1);
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
	gui.addLabel("COMPUTER VISION");
	gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    sprintf(xml_name,"__USE_VIDEO_TEST");
	gui.addToggle("USE TESTING VIDEO", xml_name, false);
    sprintf(xml_name,"__VIDEO_TEST_TRACK_FILE");
	gui.addToggle("CHOOSE VIDEO", xml_name, false);
    sprintf(xml_name,"__HAAR_FINDER_FILE");
	gui.addToggle("CHOOSE HAAR FINDER FILE", xml_name, false);
	//////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
	gui.addLabel("SENSOR KINECT");
	gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
	sprintf(xml_name,"__OPENNI_USE_INFRARED");
	gui.addToggle("USE INFRARED", xml_name, false);
	gui.setBackgroundColor(simpleColor(0, 0, 0, 255));
	sprintf(xml_name,"__OPENNI_LED_STATE");
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
	gui.addTextDropDown("LED STATE", xml_name, 2, _oniLedState);
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
	//////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
	gui.addLabel("AUDIO STREAM (INPUT/OUTPUT)");
	gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    gui.setBackgroundColor(simpleColor(0, 0, 0, 255));
	sprintf(xml_name,"__AUDIO_DEV");
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
	gui.addTextDropDown("AUDIO DEVICE", xml_name, 0, _audioDev);
	sprintf(xml_name,"__AUDIO_SAMPLING_RATE");
	gui.addTextDropDown("SAMPLING RATE", xml_name, 0, _samplingRates);
	sprintf(xml_name,"__AUDIO_BUFFER_SIZE");
	gui.addTextDropDown("BUFFER SIZE", xml_name, 0, _bufferSizes);
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
    //////////////////////////////////////////////
    gui.setTextColor(gamuzaMainColor);
	gui.addLabel("MIDI INPUT");
	gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    gui.setBackgroundColor(simpleColor(0, 0, 0, 255));
	sprintf(xml_name,"__MIDI_DEV");
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
	gui.addTextDropDown("MIDI DEVICE", xml_name, 0, _midiDev);
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	gui.setBackgroundColor(simpleColor(90, 90, 90, 255));

	gui.setWhichColumn(2);
	//////////////////////////////////////////////
	gui.setTextColor(gamuzaMainColor);
	gui.addLabel("ARDUINO");
	gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
	gui.setBackgroundColor(simpleColor(0, 0, 0, 255));
	sprintf(xml_name,"__ARDUINO_BAUDRATE");
    gui.setForegroundColor(simpleColor(90, 90, 90, 200),simpleColor(220, 220, 220, 160));
	gui.addTextDropDown("BAUDRATE", xml_name, 0, _baudRateS);
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
	sprintf(xml_name,"__ARDUINO_SERIAL_PORT");
    gui.setForegroundColor(simpleColor(70, 70, 70, 255),simpleColor(220, 220, 220, 160));
	gui.addTextDropDown("SERIAL PORT", xml_name, 0, _serialDev);
    gui.setForegroundColor(gamuzaMainColor,simpleColor(220, 220, 220, 160));
    gui.setBackgroundColor(simpleColor(90, 90, 90, 255));
    gui.addDrawableRect(" ", &_empty_audio,80, 60);

    gui.setTextColor(gamuzaMainColor);
	gui.addLabel("OSC ENGINE");
    gui.setTextColor(gamuzaWhiteColor,gamuzaMarkColor);
    oscIPField.setup("SENDING TO IP");
    oscPortField.setup("SENDING TO PORT");
    oscServerPortField.setup("RECEIVING AT PORT");

    gui.setWhichColumn(3);
    gui.setBackgroundColor(simpleColor(255, 255, 255, 20));
	//////////////////////////////////////////////
	gui.enableIgnoreLayoutFlag();
	gui.addLogger("events logger", &logger, 560, 560);
	gui.disableIgnoreLayoutFlag();
	//////////////////////////////////////////////

	gui.loadSettings(GAMUZAGUI_SETTINGS);

	//////////////////////////////////////////////
	// GUI Events
	gui.setupEvents();
	gui.enableEvents();

	// enable all events for gui logger
	ofAddListener(gui.guiEvent, this, &gamuzaMain::eventsIn);

    // create events for SETTING MANAGER
    sprintf(temp,"RESTART_GAMUZA");
    ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::restartGAmuza);
    sprintf(temp,"__CHOOSE_SCRIPT");
    ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::openAutoScriptDialog);
    sprintf(temp,"__VIDEO_TEST_TRACK_FILE");
    ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::openTrackVideoDialog);
    sprintf(temp,"__HAAR_FINDER_FILE");
	ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::openHaarTrackingDialog);

	// openNI sensor kinect GUI
	if(openniActivated && sensorKinect.isOniConnected){
		// create events to force contour finder computing
		sprintf(temp,"COMPUTE_CG_SENSOR_KINECT");
		ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::activateTrackingCF);
		sprintf(temp,"COMPUTE_TA_SENSOR_KINECT");
		ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::activateTrackingCF);
	}

	// Video Tracking multi-panel GUI
	if(trackingActivated){
		for(unsigned int i=0;i<numCamInputs;i++){ // for each input camera
			// create event for capture background
			sprintf(temp,"BG_CAPTURE_%i",camDevices[i]);
			ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::grabBackgroundEvent);
			// create event for reset input warping points
			sprintf(temp,"RESET_INPUT_WARPING_DEV_%i",camDevices[i]);
			ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::resetInputWarping);
			// create events to force contour finder computing
			sprintf(temp,"COMPUTE_CG_%i",camDevices[i]);
			ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::activateTrackingCF);
			sprintf(temp,"COMPUTE_TA_%i",camDevices[i]);
			ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::activateTrackingCF);
		}
	}

	// Audio Source multi-panel GUI
	if(audioActivated){
		for(unsigned int i=0;i<audioInputChannels;i++){ // for each audio input channel
			// create event for noise filtering
			sprintf(temp,"REC_NOISE_FILTER_%i",i);
			ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::recordNoise);
		}
	}

	// Arduino GUI
	if(arduinoActivated){
		// Serial GUI [Arduino] ANALOG PINS
		for(unsigned int i=0;i<6;i++){
			sprintf(temp,"ARDUINO_ANALOG_PIN_%i_MODE",i);
			ofAddListener(gui.createEventGroup(temp),this, &gamuzaMain::changeAnalogPinMode);
		}

		// Serial GUI [Arduino] DIGITAL PINS
		for(unsigned int i=2;i<14;i++){
			sprintf(temp,"ARDUINO_DIGITAL_PIN_%i_MODE",i);
			ofAddListener(gui.createEventGroup(temp),this, &gamuzaMain::changeDigitalPinMode);
			sprintf(temp,"ARDUINO_DIGITAL_PIN_%i_VALUE",i);
			ofAddListener(gui.createEventGroup(temp),this, &gamuzaMain::sendDigitalValue);
		}
	}

	// create event for output texture warping points functions
	sprintf(temp,"RESET_FBO_MAPPING_COORDS");
	ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::resetMappingPoints);
    sprintf(temp,"LOAD_FBO_MAPPING_COORDS");
    ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::loadMappingPoints);
    sprintf(temp,"SAVE_FBO_MAPPING_COORDS");
    ofAddListener(gui.createEventGroup(temp), this, &gamuzaMain::saveMappingPoints);
	//////////////////////////////////////////////

	// last line of gamuza setup
	flagSystemLoaded = true;
	ofSeedRandom();

}

//--------------------------------------------------------------
void gamuzaMain::setupStringVec(){

	// vector<string> of bgSubTechniques list
	bgSubTechniques.push_back("COLOR ABS");
	bgSubTechniques.push_back("B&W ABS");
	bgSubTechniques.push_back("LIGHTER THAN");
	bgSubTechniques.push_back("DARKER THAN");
	// vector<string> of sourceFlipUse list
	sourceFlipUse.push_back("OFF");
	sourceFlipUse.push_back("VERTICAL");
	sourceFlipUse.push_back("HORIZONTAL");
	sourceFlipUse.push_back("VERTICAL + HORIZONTAL");
	// vector<string> of cfDetailUse list
	cfDetailUse.push_back("RAW");
	cfDetailUse.push_back("SMOOTH");
	cfDetailUse.push_back("SIMPLE");
	// vector<string> of ardDigitalPinModes list
	ardDigitalPinModes.push_back("INPUT");
	ardDigitalPinModes.push_back("OUTPUT");
	// vector<string> of ardDigitalPinModesPWM list
	ardDigitalPinModesPWM.push_back("INPUT");
	ardDigitalPinModesPWM.push_back("OUTPUT");
	ardDigitalPinModesPWM.push_back("PWM");
	// vector<string> of ardAnalogPinModes list
	ardAnalogPinModes.push_back("REPORT ON");
	ardAnalogPinModes.push_back("REPORT OFF");

}

//--------------------------------------------------------------
void gamuzaMain::updateGui(){

	char xml_name[256];

	//////////////////////////////////////////////
	// FBO Mapping texture preview & control
	sprintf(xml_name,"USE_SECONDARY_SCREEN");
	useSecondaryScreen = gui.getValueI(xml_name);
	sprintf(xml_name,"DRAW_FBO_GRID");
	drawGrid = gui.getValueI(xml_name);
	//////////////////////////////////////////////
	if(useShader){
		sprintf(xml_name,"OUTPUT_FBO_GAMMA");
		fbo_gammaCorrection = gui.getValueF(xml_name);
		sprintf(xml_name,"OUTPUT_FBO_BRIGHTNESS");
		fbo_brightness = gui.getValueF(xml_name);
		sprintf(xml_name,"OUTPUT_FBO_SATURATION");
		fbo_saturation = gui.getValueF(xml_name);
		sprintf(xml_name,"OUTPUT_FBO_CONTRAST");
		fbo_contrast = gui.getValueF(xml_name);
		//////////////////////////////////////////////
		sprintf(xml_name,"OUTPUT_FBO_FILMBLEACH");
		fbo_filmBleach = gui.getValueF(xml_name);
		sprintf(xml_name,"OUTPUT_FBO_FILM_TECHNICOLOR");
		fbo_techniColor = gui.getValueF(xml_name);
		sprintf(xml_name,"OUTPUT_FBO_FILM_WHITEDIFFUSION");
		fbo_whiteDiffusion = gui.getValueF(xml_name);
		sprintf(xml_name,"OUTPUT_FBO_FILM_EXPOSURE");
		fbo_exposure = gui.getValueF(xml_name);
		sprintf(xml_name,"OUTPUT_FBO_FILM_DIFFUSION");
		fbo_diffusion = gui.getValueF(xml_name);
	}
	//////////////////////////////////////////////
	sprintf(xml_name,"ACTIVATE_LIVE_EDITOR");
	activateLiveEditor = gui.getValueI(xml_name);
	sprintf(xml_name,"USE_VSYNC");
	useVSync = gui.getValueI(xml_name);
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// OpenNI SensorKinect GUI
	if(openniActivated && sensorKinect.isOniConnected){
		sprintf(xml_name,"COMPUTE_SENSOR_KINECT");
		sensorKinect.useKinect = gui.getValueI(xml_name);
		sprintf(xml_name,"USE_TRACKING_HANDS_SENSOR_KINECT");
		sensorKinect.isTrackingHands = gui.getValueI(xml_name);
		sprintf(xml_name,"NEAR_THRESHOLD_SENSOR_KINECT");
		sensorKinect.nearThreshold = gui.getValueF(xml_name);
		sprintf(xml_name,"FAR_THRESHOLD_SENSOR_KINECT");
		sensorKinect.farThreshold = gui.getValueF(xml_name);
		//////////////////////////////////////////////
		sprintf(xml_name,"CI_BLUR_SENSOR_KINECT");
		sensorKinect.ciBlur = gui.getValueI(xml_name);
		sprintf(xml_name,"CI_ERODE_SENSOR_KINECT");
		sensorKinect.ciErode = gui.getValueF(xml_name);
		sprintf(xml_name,"CI_DILATE_SENSOR_KINECT");
		sensorKinect.ciDilate = gui.getValueF(xml_name);
		sprintf(xml_name,"M_THRESHOLD_SENSOR_KINECT");
		sensorKinect.mThreshold = gui.getValueI(xml_name);
		sprintf(xml_name,"MOTION_ON_HORIZON_SENSOR_KINECT");
		sensorKinect.onHorizon = gui.getValueI(xml_name);
		sprintf(xml_name,"MOTION_OFF_HORIZON_SENSOR_KINECT");
		sensorKinect.offHorizon = gui.getValueI(xml_name);
		sprintf(xml_name,"USE_KALMAN_FILTER_SENSOR_KINECT");
		sensorKinect.useKalmanFilter = gui.getValueI(xml_name);
		sprintf(xml_name,"SMOOTHING_FACTOR_SENSOR_KINECT");
		sensorKinect._smoothingFactor = gui.getValueF(xml_name);
		//////////////////////////////////////////////
		sprintf(xml_name,"MIN_BLOB_AREA_SENSOR_KINECT");
		sensorKinect.minBlobArea = gui.getValueI(xml_name);
		sprintf(xml_name,"MAX_BLOB_AREA_SENSOR_KINECT");
		sensorKinect.maxBlobArea = gui.getValueI(xml_name);
		sprintf(xml_name,"CF_DETAIL_SENSOR_KINECT");
		sensorKinect.cfDetail = gui.getValueI(xml_name);
		sprintf(xml_name,"CF_SMOOTH_PCT_SENSOR_KINECT");
		sensorKinect.smoothPct = gui.getValueF(xml_name);
		sprintf(xml_name,"CF_TOLERANCE_SENSOR_KINECT");
		sensorKinect.tolerance = gui.getValueF(xml_name);
		sprintf(xml_name,"COMPUTE_CF_SENSOR_KINECT");
		sensorKinect.computeContourFinder = gui.getValueI(xml_name);
		sprintf(xml_name,"COMPUTE_CG_SENSOR_KINECT");
		sensorKinect.computeContourGeometry = gui.getValueI(xml_name);
		sprintf(xml_name,"COMPUTE_OF_SENSOR_KINECT");
		sensorKinect.computeOpticalFlow = gui.getValueI(xml_name);
		sprintf(xml_name,"COMPUTE_TA_SENSOR_KINECT");
		sensorKinect.computeTriggerAreas = gui.getValueI(xml_name);
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// Video Tracking multi-panel GUI
	if(trackingActivated){
		for(unsigned int i=0;i<numCamInputs;i++){
			sprintf(xml_name,"USE_DEVICE_%i",camDevices[i]);
			inputCam[i].captureVideo = gui.getValueI(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"FLIP_SOURCE_USE_%i",camDevices[i]);
			inputCam[i]._sourceFlipUse = gui.getValueI(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"UNDISTORT_INPUT_%i",camDevices[i]);
			inputCam[i].undistortInput = gui.getValueI(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"INPUT_BLUR_%i",camDevices[i]);
			inputCam[i].colorImgBlur = gui.getValueI(xml_name);
			sprintf(xml_name,"CONTRAST_%i",camDevices[i]);
			inputCam[i].contrast = gui.getValueF(xml_name);
			sprintf(xml_name,"BRIGHTNESS_%i",camDevices[i]);
			inputCam[i].brightness = gui.getValueF(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"USE_COLOR_TRACKING_%i",camDevices[i]);
			inputCam[i].useHsvTracking = gui.getValueI(xml_name);
			sprintf(xml_name,"HUE_%i",camDevices[i]);
			inputCam[i].hue = gui.getValueF(xml_name);
			sprintf(xml_name,"HUE_WIDTH_%i",camDevices[i]);
			inputCam[i].hueWidth = gui.getValueF(xml_name);
			sprintf(xml_name,"SAT_%i",camDevices[i]);
			inputCam[i].sat = gui.getValueF(xml_name);
			sprintf(xml_name,"SAT_WIDTH_%i",camDevices[i]);
			inputCam[i].satWidth = gui.getValueF(xml_name);
			sprintf(xml_name,"VAL_%i",camDevices[i]);
			inputCam[i].val = gui.getValueF(xml_name);
			sprintf(xml_name,"VAL_WIDTH_%i",camDevices[i]);
			inputCam[i].valWidth = gui.getValueF(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"MOTION_ON_HORIZON_%i",camDevices[i]);
			inputCam[i].onHorizon = gui.getValueI(xml_name);
			sprintf(xml_name,"MOTION_OFF_HORIZON_%i",camDevices[i]);
			inputCam[i].offHorizon = gui.getValueI(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"BGSUB_TECH_%i",camDevices[i]);
			inputCam[i].bgSubTech = gui.getValueI(xml_name);
			sprintf(xml_name,"BGSUB_THRESHOLD_%i",camDevices[i]);
			inputCam[i].threshold = gui.getValueI(xml_name);
			sprintf(xml_name,"BG_USE_STRECH_%i",camDevices[i]);
			inputCam[i].bgUseContrastStrech = gui.getValueI(xml_name);
			sprintf(xml_name,"BGSUB_BLUR_%i",camDevices[i]);
			inputCam[i].bgSubBlur = gui.getValueI(xml_name);
			sprintf(xml_name,"BGSUB_ERODE_%i",camDevices[i]);
			inputCam[i].bgSubErode = gui.getValueI(xml_name);
			sprintf(xml_name,"BGSUB_DILATE_%i",camDevices[i]);
			inputCam[i].bgSubDilate = gui.getValueI(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"HSV_BLUR_%i",camDevices[i]);
			inputCam[i].hsvBlur = gui.getValueI(xml_name);
			sprintf(xml_name,"HSV_ERODE_%i",camDevices[i]);
			inputCam[i].hsvErode = gui.getValueI(xml_name);
			sprintf(xml_name,"HSV_DILATE_%i",camDevices[i]);
			inputCam[i].hsvDilate = gui.getValueI(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"M_THRESHOLD_%i",camDevices[i]);
			inputCam[i].mThreshold = gui.getValueI(xml_name);
			sprintf(xml_name,"M_NOISE_COMP_%i",camDevices[i]);
			inputCam[i].mNoiseComp = gui.getValueI(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"BT_BLUR_%i",camDevices[i]);
			inputCam[i].btBlur = gui.getValueI(xml_name);
			sprintf(xml_name,"BT_ERODE_%i",camDevices[i]);
			inputCam[i].btErode = gui.getValueI(xml_name);
			sprintf(xml_name,"BT_DILATE_%i",camDevices[i]);
			inputCam[i].btDilate = gui.getValueI(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"MIN_BLOB_AREA_%i",camDevices[i]);
			inputCam[i].minBlobArea = gui.getValueI(xml_name);
			sprintf(xml_name,"MAX_BLOB_AREA_%i",camDevices[i]);
			inputCam[i].maxBlobArea = gui.getValueI(xml_name) + inputCam[i].minBlobArea;
			sprintf(xml_name,"CF_DETAIL_%i",camDevices[i]);
			inputCam[i].cfDetail = gui.getValueI(xml_name);
			sprintf(xml_name,"CF_SMOOTH_PCT_%i",camDevices[i]);
			inputCam[i].smoothPct = gui.getValueF(xml_name);
			sprintf(xml_name,"CF_TOLERANCE_%i",camDevices[i]);
			inputCam[i].tolerance = gui.getValueF(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"COMPUTE_CF_%i",camDevices[i]);
			inputCam[i].computeContourFinder = gui.getValueI(xml_name);
			sprintf(xml_name,"COMPUTE_CG_%i",camDevices[i]);
			inputCam[i].computeContourGeometry = gui.getValueI(xml_name);
			sprintf(xml_name,"COMPUTE_OF_%i",camDevices[i]);
			inputCam[i].computeOpticalFlow = gui.getValueI(xml_name);
			sprintf(xml_name,"COMPUTE_FT_%i",camDevices[i]);
			inputCam[i].computeHaarFinder = gui.getValueI(xml_name);
			sprintf(xml_name,"COMPUTE_TA_%i",camDevices[i]);
			inputCam[i].computeTriggerAreas = gui.getValueI(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"USE_KALMAN_FILTER_%i",camDevices[i]);
			inputCam[i].useKalmanFilter = gui.getValueI(xml_name);
			sprintf(xml_name,"SMOOTHING_FACTOR_%i",camDevices[i]);
			inputCam[i]._smoothingFactor = gui.getValueF(xml_name);
			//////////////////////////////////////////////

			inputCam[i].drawInfoGraphics = !gui.minimize;

		}
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// Audio Source multi-panel GUI
	if(audioActivated){
		for(unsigned int i=0;i<audioInputChannels;i++){
			sprintf(xml_name,"USE_AUDIO_INPUT_%i",i);
			inputAudioCH[i].captureAudio = gui.getValueI(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"VOLUME_AUDIO_INPUT_%i",i);
			inputAudioCH[i]._volume = gui.getValueF(xml_name);
			sprintf(xml_name,"MUTE_AUDIO_INPUT_%i",i);
			inputAudioCH[i]._mute = gui.getValueI(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"NOISE_REDUX_FACTOR_%i",i);
			inputAudioCH[i].reduxFactor = gui.getValueF(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"EQ_BAND1_CENTER_%i",i);
			inputAudioCH[i].eqLOWCenter = gui.getValueF(xml_name);
			sprintf(xml_name,"EQ_BAND1_AMPLITUDE_%i",i);
			inputAudioCH[i].eqLOWAmplitude = gui.getValueF(xml_name);
			sprintf(xml_name,"EQ_BAND1_WIDTH_%i",i);
			inputAudioCH[i].eqLOWWidth = gui.getValueF(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"EQ_BAND2_CENTER_%i",i);
			inputAudioCH[i].eqMIDCenter = gui.getValueF(xml_name);
			sprintf(xml_name,"EQ_BAND2_AMPLITUDE_%i",i);
			inputAudioCH[i].eqMIDAmplitude = gui.getValueF(xml_name);
			sprintf(xml_name,"EQ_BAND2_WIDTH_%i",i);
			inputAudioCH[i].eqMIDWidth = gui.getValueF(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"EQ_BAND3_CENTER_%i",i);
			inputAudioCH[i].eqHICenter = gui.getValueF(xml_name);
			sprintf(xml_name,"EQ_BAND3_AMPLITUDE_%i",i);
			inputAudioCH[i].eqHIAmplitude = gui.getValueF(xml_name);
			sprintf(xml_name,"EQ_BAND3_WIDTH_%i",i);
			inputAudioCH[i].eqHIWidth = gui.getValueF(xml_name);
			//////////////////////////////////////////////
			sprintf(xml_name,"USE_KALMAN_FILTER_AUDIOCH_%i",i);
			inputAudioCH[i].useKalmanFilter = gui.getValueI(xml_name);
			sprintf(xml_name,"SMOOTHING_FACTOR_AUDIOCH_%i",i);
			inputAudioCH[i]._smoothingFactor = gui.getValueF(xml_name);

			inputAudioCH[i].drawGraphics = !gui.minimize;

		}
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// Serial GUI [Arduino]
	if(arduinoActivated){
		sprintf(xml_name,"USE_ARDUINO");
		useArduino = gui.getValueI(xml_name);
		//////////////////////////////////////////////
		sprintf(xml_name,"USE_KALMAN_FILTER_ARDUINO");
		useKalmanFilterArduino = gui.getValueI(xml_name);
		sprintf(xml_name,"SMOOTHING_FACTOR_ARDUINO");
		arduino_smoothingFactor = gui.getValueF(xml_name);

	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// OSC GUI [Open Sound Control Output DATA]
    //////////////////////////////////////////////
    if(openniActivated && sensorKinect.isOniConnected){
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_BD");
        sensorKinect.sendOsc_BD = gui.getValueI(xml_name);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_CF");
        sensorKinect.sendOsc_CF = gui.getValueI(xml_name);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_CG");
        sensorKinect.sendOsc_CG = gui.getValueI(xml_name);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_OF");
        sensorKinect.sendOsc_OF = gui.getValueI(xml_name);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_TA");
        sensorKinect.sendOsc_TA = gui.getValueI(xml_name);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_HT");
        sensorKinect.sendOsc_HT = gui.getValueI(xml_name);
        sprintf(xml_name,"SENSOR_KINECT_SEND_OSC_HW");
        sensorKinect.sendOsc_HW = gui.getValueI(xml_name);
    }
    //////////////////////////////////////////////
    if(trackingActivated){
        for(unsigned int i=0;i<numCamInputs;i++){
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_MD",camDevices[i]);
            inputCam[i].sendOsc_MD = gui.getValueI(xml_name);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_BD",camDevices[i]);
            inputCam[i].sendOsc_BD = gui.getValueI(xml_name);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_CF",camDevices[i]);
            inputCam[i].sendOsc_CF = gui.getValueI(xml_name);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_CG",camDevices[i]);
            inputCam[i].sendOsc_CG = gui.getValueI(xml_name);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_OF",camDevices[i]);
            inputCam[i].sendOsc_OF = gui.getValueI(xml_name);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_HF",camDevices[i]);
            inputCam[i].sendOsc_HF = gui.getValueI(xml_name);
            sprintf(xml_name,"WEBCAM_ID%i_SEND_OSC_TA",camDevices[i]);
            inputCam[i].sendOsc_TA = gui.getValueI(xml_name);
    }
    }
    //////////////////////////////////////////////
    if(audioActivated){
        for(unsigned int i=0;i<audioInputChannels;i++){
            sprintf(xml_name,"AUDIO_INPUT_CH%i_SEND_OSC_VD",i);
            inputAudioCH[i].sendOsc_VD = gui.getValueI(xml_name);
            sprintf(xml_name,"AUDIO_INPUT_CH%i_SEND_OSC_PD",i);
            inputAudioCH[i].sendOsc_PD = gui.getValueI(xml_name);
            sprintf(xml_name,"AUDIO_INPUT_CH%i_SEND_OSC_BK",i);
            inputAudioCH[i].sendOsc_BK = gui.getValueI(xml_name);
        }
    }
    //////////////////////////////////////////////
    if(arduinoActivated){
        sprintf(xml_name,"ARDUINO_SEND_OSC_AAP");
        sendOsc_AAP = gui.getValueI(xml_name);
        sprintf(xml_name,"ARDUINO_SEND_OSC_ADP");
        sendOsc_ADP = gui.getValueI(xml_name);
    }
	//////////////////////////////////////////////

    //////////////////////////////////////////////
	// SETTING MANAGER PANEL
    //////////////////////////////////////////////

    ////////////////////////////////////////////// MODULES
	sprintf(xml_name,"__OPENNI_MODULE");
	_openniModule = gui.getValueI(xml_name);
	sprintf(xml_name,"__VIDEO_TRACKING_MODULE");
	_trackingModule = gui.getValueI(xml_name);
	sprintf(xml_name,"__AUDIO_INPUT_MODULE");
	_audioModule = gui.getValueI(xml_name);
	sprintf(xml_name,"__ARDUINO_MODULE");
	_arduinoModule = gui.getValueI(xml_name);
	////////////////////////////////////////////// SCREENS
	updateSettingScreens();
	////////////////////////////////////////////// MAPPING FBO TEXTURE
    sprintf(xml_name,"__MAPPING_GRID_RES");
    _mappingGridRes = gui.getValueI(xml_name);
    ////////////////////////////////////////////// AUTOMATION
    sprintf(xml_name,"__AUTO_PILOT");
	_autoPilot = gui.getValueI(xml_name);
    sprintf(xml_name,"__AUTOLOAD_SCRIPT");
	_autoloadScript = gui.getValueI(xml_name);
	////////////////////////////////////////////// OPENNI SENSOR KINECT
    sprintf(xml_name,"__OPENNI_USE_INFRARED");
	_useInfrared = gui.getValueI(xml_name);
	sprintf(xml_name,"__OPENNI_LED_STATE");
	if(gui.getValueI(xml_name) != 5){
	    _ledState = gui.getValueI(xml_name);
	}else{
	    _ledState = 6;
	}
	////////////////////////////////////////////// VIDEO TRACKING
	sprintf(xml_name,"__USE_VIDEO_TEST");
    _loadVideoTest = gui.getValueI(xml_name);
	////////////////////////////////////////////// AUDIO
    sprintf(xml_name,"__AUDIO_DEV");
	_audioDevice  = gui.getValueI(xml_name);
	_inputChannels = _inputCH[gui.getValueI(xml_name)];
	_outputChannels = _outputCH[gui.getValueI(xml_name)];
	sprintf(xml_name,"__AUDIO_SAMPLING_RATE");
	_samplingRate = _samplingRates[gui.getValueI(xml_name)];
	sprintf(xml_name,"__AUDIO_BUFFER_SIZE");
	_bufferSize = _bufferSizes[gui.getValueI(xml_name)];
    ////////////////////////////////////////////// MIDI
    sprintf(xml_name,"__MIDI_DEV");
	_midiDevice  = gui.getValueI(xml_name);
	////////////////////////////////////////////// ARDUINO
    sprintf(xml_name,"__ARDUINO_BAUDRATE");
	_baudRate = _baudRateS[gui.getValueI(xml_name)];
	sprintf(xml_name,"__ARDUINO_SERIAL_PORT");
	_serialPort = _serialDev[gui.getValueI(xml_name)];
    //////////////////////////////////////////////

    //////////////////////////////////////////////
}

//--------------------------------------------------------------
void gamuzaMain::drawGui(){

	char temp[128];
	string temp1;
	ostringstream temp2;

	glColor3f(1.0,1.0,1.0);
	ofNoFill();

	////////////////////////////////////
	// panel tabs colorize
	if(!gui.minimize){
		ofEnableAlphaBlending();

		ofFill();
		// live Coding
		glColor4f(1.0,1.0,1.0,1.0);
		ofRect(gui.panelTabs[0].x+1, gui.panelTabs[0].y+1, gui.panelTabs[0].width-2, gui.panelTabs[0].height-2);
		// sensor kinect
		if(openniActivated && sensorKinect.isOniConnected){
			glColor4f(0.0,1.0,0.0,1.0);
			ofRect(gui.panelTabs[1].x+1, gui.panelTabs[1].y+1, gui.panelTabs[1].width-2, gui.panelTabs[1].height-2);
		}
		// webcams
		if(trackingActivated){
			glColor4f(0.847,0.25,0.25,1.0);
			for(unsigned int i=0;i<numCamInputs;i++){
				ofRect(gui.panelTabs[webcamsStartIndex+i].x+1, gui.panelTabs[webcamsStartIndex+i].y+1, gui.panelTabs[webcamsStartIndex+i].width-2, gui.panelTabs[webcamsStartIndex+i].height-2);
			}
		}
		// audio input
		if(audioActivated){
			glColor4f(1.0,0.906,0.463,1.0);
			for(unsigned int i=0;i<audioInputChannels;i++){
				ofRect(gui.panelTabs[audioInputStartIndex+i].x+1, gui.panelTabs[audioInputStartIndex+i].y+1, gui.panelTabs[audioInputStartIndex+i].width-2, gui.panelTabs[audioInputStartIndex+i].height-2);
			}
		}
		// arduino
		if(arduinoActivated){
			glColor4f(0.0,0.2,1.0,1.0);
			ofRect(gui.panelTabs[arduinoIndex].x+1, gui.panelTabs[arduinoIndex].y+1, gui.panelTabs[arduinoIndex].width-2, gui.panelTabs[arduinoIndex].height-2);
		}
		// osc
        glColor4f(0.4,0.4,0.4,1.0);
        ofRect(gui.panelTabs[oscIndex].x+1, gui.panelTabs[oscIndex].y+1, gui.panelTabs[oscIndex].width-2, gui.panelTabs[oscIndex].height-2);
		// credits
		glColor4f(1.0,1.0,1.0,1.0);
		ofRect(gui.panelTabs[gui.panelTabs.size()-1].x+1, gui.panelTabs[gui.panelTabs.size()-1].y+1, gui.panelTabs[gui.panelTabs.size()-1].width-2, gui.panelTabs[gui.panelTabs.size()-1].height-2);

		ofDisableAlphaBlending();
	}
	////////////////////////////////////

	glPushMatrix();
	glTranslatef(guiPosX, guiPosY, 0.0f);

    ////////////////////////////////////
	// MAIN TITLE
	sprintf(temp," GAMUZA [%s] 'SILENT SHORE' BETA | <HTTP://WWW.GAMUZA.CC> | <HTTP://WWW.D3COD3.ORG>",GAMUZA_RELEASE);
	ofSetColor(9,147,211);
	fontSmall.drawString(temp,8,14);
	////////////////////////////////////

	//////////////////////////////////////////////
	// OPENNI
	if(openniActivated && sensorKinect.isOniConnected){
		if(gui.getSelectedPanel() == sensorKinectIndex && !gui.minimize){
			if(sensorKinect.useKinect){
				sensorKinect.drawDevice();
				if(sensorKinect.computeContourFinder && sensorKinect.computeTriggerAreas){
					temp2 << "TRIGGER AREAS: ";
					for(unsigned int t=0;t<TRIGGER_AREAS_NUM;t++){
						temp2 << t;
						temp2 << "[";
						sprintf(temp,"%i",sensorKinect.triggerState[t]);
						temp2 << temp;
						temp2 << "] ";
					}
					temp2 << endl;
					temp1 = temp2.str();
					sprintf(temp,"%s",temp1.c_str());
					glColor3f(1.0,1.0,1.0);
					fontSmall.drawString(temp, 370,334);
				}
			}else{
				ofEnableAlphaBlending();
				glColor4f(0.0,0.0,0.0,0.7);
				ofFill();
				ofRect(11,42,gui.boundingBox.width - gui.borderWidth*2 - 2, gui.boundingBox.height - gui.topSpacing*3 - 1);
				ofDisableAlphaBlending();
			}
		}
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// Video Tracking Additional GUI
	if(trackingActivated){
		for(unsigned int i=0;i<numCamInputs;i++){
			sprintf(temp," CAM DEVICE [%i] | %s",camDevices[i],deviceNames[i].c_str());
			if(gui.getSelectedPanelName() == temp && !gui.minimize){
				if(inputCam[gui.getSelectedPanel()-webcamsStartIndex].captureVideo){
					inputCam[gui.getSelectedPanel()-webcamsStartIndex].draw();
					if(inputCam[gui.getSelectedPanel()-webcamsStartIndex].drawInfoGraphics){
						sprintf(temp,"MOTION QUANTITY : %i",inputCam[gui.getSelectedPanel()-webcamsStartIndex].numPixelsChanged);
						glColor3f(1.0,1.0,1.0);
						fontSmall.drawString(temp, 30, 490);
						if(inputCam[gui.getSelectedPanel()-webcamsStartIndex].computeContourFinder && inputCam[gui.getSelectedPanel()-webcamsStartIndex].computeTriggerAreas){
							temp2 << "TRIGGERS: ";
							for(unsigned int t=0;t<TRIGGER_AREAS_NUM;t++){
								temp2 << t;
								temp2 << "[";
								sprintf(temp,"%i",inputCam[gui.getSelectedPanel()-webcamsStartIndex].triggerState[t]);
								temp2 << temp;
								temp2 << "] ";
							}
							temp2 << endl;
							temp1 = temp2.str();
							sprintf(temp,"%s",temp1.c_str());
							fontSmall.drawString(temp, 286,280);
						}
					}
				}else{
					ofEnableAlphaBlending();
						glColor4f(0.0,0.0,0.0,0.7);
						ofFill();
						ofRect(11,42,gui.boundingBox.width - gui.borderWidth*2 - 2, gui.boundingBox.height - gui.topSpacing*3 - 1);
					ofDisableAlphaBlending();
				}
			}
		}
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// AUDIO input  Additional GUI
	if(audioActivated){
		for(unsigned int i=0;i<audioInputChannels;i++){
			sprintf(temp," AUDIO INPUT [CHANNEL %i]",i);
			if(gui.getSelectedPanelName() == temp && inputAudioCH[i].drawGraphics && !gui.minimize){
				if(inputAudioCH[i].noiseRec){
					ofSetColor(216, 64, 64);
					fontSmall.drawString("RECORDING NOISE", 882,102);
					fontSmall.drawString("RECORDING | CLICK TO STOP", 106,251);
				}
				inputAudioCH[i].drawChannel(463,47,320,120);
				if(!inputAudioCH[i].captureAudio){
					ofEnableAlphaBlending();
					glColor4f(0.0,0.0,0.0,0.7);
					ofFill();
					ofRect(11,42,gui.boundingBox.width - gui.borderWidth*2 - 2, gui.boundingBox.height - gui.topSpacing*3 - 1);
					ofDisableAlphaBlending();
				}
			}
		}
	}
	//////////////////////////////////////////////

	//////////////////////////////////////////////
	// Serial GUI [Arduino]
	if(arduinoActivated){
		if(gui.getSelectedPanel() == arduinoIndex && !gui.minimize){
			if(!useArduino){
				ofEnableAlphaBlending();
				glColor4f(0.0,0.0,0.0,0.7);
				ofFill();
				ofRect(11,42,gui.boundingBox.width - gui.borderWidth*2 - 2, gui.boundingBox.height - gui.topSpacing*3 - 1);
				ofDisableAlphaBlending();
			}
		}
	}
	//////////////////////////////////////////////

    //////////////////////////////////////////////
    if(gui.getSelectedPanel() == gui.panelTabs.size()-1){
        // text input fields in SETTING MANAGER PANEL
        ofEnableAlphaBlending();
        glColor4f(1.0,1.0,1.0,1.0);
        drawSettingPanel();
        ofDisableAlphaBlending();
    }
    //////////////////////////////////////////////

	glPopMatrix();
}

//--------------------------------------------------------------
void gamuzaMain::gamuzaFullscreen(){

	ofToggleFullscreen();
	if(isFullscreen){
        char temp[256];

		isFullscreen = false;
		if(projectionScreenW < MAIN_WINDOW_W){
			lcPrevW	 = (projectionScreenW*MAIN_WINDOW_H)/projectionScreenH;
			lcPrevH	 = MAIN_WINDOW_H;
			lcPrevX	 = (MAIN_WINDOW_W-lcPrevW)/2.0;
			lcPrevY  = 0;
		}else{
			lcPrevW	 = MAIN_WINDOW_W;
			lcPrevH	 = (projectionScreenH*MAIN_WINDOW_W)/projectionScreenW;
			lcPrevX	 = 0;
			lcPrevY  = (MAIN_WINDOW_H-lcPrevH)/2.0;
		}
		guiPosX = 0.0;
		guiPosY = 0.0;
		gui.setPosition(guiPosX, guiPosY);
		gui.setDimensions(MAIN_WINDOW_W-2, MAIN_WINDOW_H-6);
        timeline.setWidth(MAIN_WINDOW_W-4);

        sprintf(temp,"GAmuza | %s",GAscriptFileName.c_str());
        ofSetWindowTitle(temp);
	}else{
		isFullscreen = true;
		if(projectionScreenW < mainScreenW){
			lcPrevW	 = (projectionScreenW*mainScreenH)/projectionScreenH;
			lcPrevH	 = mainScreenH;
			lcPrevX	 = (mainScreenW-lcPrevW)/2.0;
			lcPrevY  = 0;
		}else{
			lcPrevW	 = mainScreenW;
			lcPrevH	 = (projectionScreenH*mainScreenW)/projectionScreenW;
			lcPrevX	 = 0;
			lcPrevY  = (mainScreenH-lcPrevH)/2.0;
		}
		guiPosX = ((mainScreenW - MAIN_WINDOW_W)/2.0) + 1.0;
		guiPosY = ((mainScreenH - MAIN_WINDOW_H)/2.0) + 3.0;
		gui.setPosition(guiPosX, guiPosY);
		gui.setDimensions(MAIN_WINDOW_W-2, MAIN_WINDOW_H-6);
        timeline.setWidth(mainScreenW-6);
	}

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

//--------------------------------------------------------------
void gamuzaMain::initTimeline(){
    ofVec2f offset;
    offset.set(4,0);

    timeline.setup();
    timeline.setPageName("TIMELINE");
    timeline.setOffset(offset);
    if(isFullscreen){
        timeline.setWidth(mainScreenW-10);
    }else{
        timeline.setWidth(MAIN_WINDOW_W-8);
    }
    if(showTimeline){
        timeline.show();
        timeline.enableMouse();

    }else{
        timeline.hide();
        timeline.disableMouse();
    }

}

//--------------------------------------------------------------
void gamuzaMain::resetWarpingPoints(int actualPanel){

	inputCam[actualPanel].sourceFrame.points[0].x = 0.0f;
	inputCam[actualPanel].sourceFrame.points[0].y = 0.0f;
	inputCam[actualPanel].sourceFrame.points[1].x = 240.0f;
	inputCam[actualPanel].sourceFrame.points[1].y = 0.0f;
	inputCam[actualPanel].sourceFrame.points[2].x = 240.0f;
	inputCam[actualPanel].sourceFrame.points[2].y = 180.0f;
	inputCam[actualPanel].sourceFrame.points[3].x = 0.0f;
	inputCam[actualPanel].sourceFrame.points[3].y = 180.0f;

}

//////////////////////////////////////////////////////////////// GUI Events
//--------------------------------------------------------------
void gamuzaMain::eventsIn(guiCallbackData & data){

	//lets send all events to our logger
	if( !data.isElement( "events logger" ) ){
		/*string logStr = data.getXmlName();

		for(int k = 0; k < data.getNumValues(); k++){
			logStr += " | " + data.getString(k);
		}

		logger.log(OF_LOG_NOTICE, " %s", logStr.c_str());*/

		if(data.isElement("SCRIPT EXAMPLES")){
			loadScript(scriptsLister.getSelectedPath());
			liveCoding.glEditor[liveCoding.currentEditor]->clearEditor();
			liveCoding.pasteFromLuaScript(readScript(scriptsLister.getSelectedPath(),false));
		}

		if(data.isElement("OPEN_SCRIPT_FILE_DIALOG")){
			openFileDialog();
			gui.setValueB("OPEN_SCRIPT_FILE_DIALOG", false);
		}

		if(data.isElement("SAVE_SCRIPT_FILE_DIALOG")){
			saveFileDialog();
			gui.setValueB("SAVE_SCRIPT_FILE_DIALOG", false);
		}

		if(data.isElement("RENDER_SCRIPT") && data.getInt(0) == 1){
            liveCoding.renderScript();
			gui.setValueB("RENDER_SCRIPT", false);
		}

	}

}

//--------------------------------------------------------------
void gamuzaMain::restartGAmuza(guiCallbackData & data){
    char temp[256];
	sprintf(temp,"RESTART_GAMUZA");
	if(data.isElement(temp) && data.getInt(0) == 1 ){
        gui.setValueB(temp, false);
		system("sh /usr/local/share/GAmuza/restart.sh");
	}
}

//--------------------------------------------------------------
void gamuzaMain::openFileDialog(){
    ofFileDialogResult res = ofSystemLoadDialog("Open Script", false);

    if(res.bSuccess == true) {
        _scriptFile = res.getPath();
        loadScript(_scriptFile);
        logger.log(99, " %s", _scriptFile.c_str());
        logger.log(99, " CHOOSED SCRIPT:");
        liveCoding.glEditor[liveCoding.currentEditor]->ClearAllText();
        liveCoding.pasteFromLuaScript(readScript(_scriptFile,true));
    }else{
        logger.log(99, " CHOOSE SCRIPT Canceled.");
    }
}

//--------------------------------------------------------------
void gamuzaMain::saveFileDialog(){
    string fileURL;
    string fileName;

    ofFileDialogResult res = ofSystemSaveDialog(fileURL,"Save File");

    if(res.bSuccess == true) {
        fileURL = res.getPath();
        fileName = res.getName();
        logger.log(99, " %s", fileName.c_str());
        logger.log(99, " SAVE SCRIPT:");
        liveCoding.saveToFile(fileURL);
        scriptsLister.refreshDir();
    }else{
        logger.log(99, " CHOOSE SCRIPT Canceled.");
    }
}

//--------------------------------------------------------------
void gamuzaMain::openAutoScriptDialog(guiCallbackData & data){
    ofFileDialogResult res = ofSystemLoadDialog("Open Script", false);

    if(res.bSuccess == true) {
        _scriptFile = res.getPath();
        logger.log(99, " %s", _scriptFile.c_str());
        logger.log(99, " CHOOSED SCRIPT:");
    }else{
        logger.log(99, " CHOOSE SCRIPT Canceled.");
    }
    char temp[256];
	sprintf(temp,"__CHOOSE_SCRIPT");
    gui.setValueB(temp, false);
}

//--------------------------------------------------------------
void gamuzaMain::openTrackVideoDialog(guiCallbackData & data){
    ofFileDialogResult res = ofSystemLoadDialog("Open Video", false);

    if(res.bSuccess == true) {
        _videoTestFile = res.getPath();
        logger.log(99, " %s", _videoTestFile.c_str());
        logger.log(99, " CHOOSED VIDEO TEST:");
    }else{
        logger.log(99, " CHOOSE VIDEO TEST Canceled.");
    }
    char temp[256];
	sprintf(temp,"__VIDEO_TEST_TRACK_FILE");
    gui.setValueB(temp, false);
}

//--------------------------------------------------------------
void gamuzaMain::openHaarTrackingDialog(guiCallbackData & data){
    ofFileDialogResult res = ofSystemLoadDialog("Open Haar Tracking File", false);

    if(res.bSuccess == true) {
        _haarCascadeFile = res.getPath();
        logger.log(99, " %s", _haarCascadeFile.c_str());
        logger.log(99, " CHOOSED HAAR TRACKING FILE:");
    }else{
        logger.log(99, " CHOOSE HAAR TRACKING FILE Canceled.");
    }
    char temp[256];
	sprintf(temp,"__HAAR_FINDER_FILE");
    gui.setValueB(temp, false);
}

//--------------------------------------------------------------
void gamuzaMain::grabBackgroundEvent(guiCallbackData & data){

	if(gui.getSelectedPanel() >= webcamsStartIndex && gui.getSelectedPanel() < webcamsStartIndex + numCamInputs){
		char temp[256];
		sprintf(temp,"BG_CAPTURE_%i",camDevices[gui.getSelectedPanel()-webcamsStartIndex]);
		if(data.isElement(temp) && data.getInt(0) == 1 ){
			inputCam[gui.getSelectedPanel()-webcamsStartIndex].bLearnBackground = true;
			gui.setValueB(temp, false);
		}
	}

}

//--------------------------------------------------------------
void gamuzaMain::resetMappingPoints(guiCallbackData & data){

	char temp[256];
	sprintf(temp,"RESET_FBO_MAPPING_COORDS");
	if(data.isElement(temp) && data.getInt(0) == 1 ){
		// warped grid reset
		finalTextureMapping.reset(projectionScreenW,projectionScreenH);
        saveMappingSettings = true;
        finalTextureMapping.saveSettings(GAMUZA_MAPPING_FILE);
        saveMappingSettings = false;
		gui.setValueB(temp, false);
	}

}

//--------------------------------------------------------------
void gamuzaMain::loadMappingPoints(guiCallbackData & data){

	char temp[256];
	sprintf(temp,"LOAD_FBO_MAPPING_COORDS");
	if(data.isElement(temp) && data.getInt(0) == 1 ){
		// warped grid load points
        string URL;

        ofFileDialogResult res = ofSystemLoadDialog("Open Script", false);
        if(res.bSuccess == true){
            URL = res.getPath();
            finalTextureMapping.loadSettings(URL);
            sprintf(temp,"OPEN MAPPING FILE: %s", URL.c_str());
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, temp);
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
            finalTextureMapping.saveSettings(GAMUZA_MAPPING_FILE);
        }else{
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, "OPEN MAPPING FILE Canceled");
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
        }

		gui.setValueB(temp, false);
	}

}

//--------------------------------------------------------------
void gamuzaMain::saveMappingPoints(guiCallbackData & data){

	char temp[256];
	sprintf(temp,"SAVE_FBO_MAPPING_COORDS");
	if(data.isElement(temp) && data.getInt(0) == 1 ){
        saveMappingSettings = true;
		// warped grid save points
		string folderURL;
        string fileName;

        ofFileDialogResult res = ofSystemSaveDialog(folderURL, "Save Mapping");
        if(res.bSuccess == true){
            folderURL = res.getPath();
            sprintf(temp,"SAVE MAPPING FILE: %s", folderURL.c_str());
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, temp);
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
            finalTextureMapping.saveSettings(folderURL);
            finalTextureMapping.saveSettings(GAMUZA_MAPPING_FILE);
        }else{
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, "SAVE MAPPING FILE Canceled");
            sendPrivateMessage(GAMUZA_CONSOLE_LOG, " ");
        }
        sprintf(temp,"SAVE_FBO_MAPPING_COORDS");
        saveMappingSettings = false;
		gui.setValueB(temp, false);
	}

}

//--------------------------------------------------------------
void gamuzaMain::activateTrackingCF(guiCallbackData & data){

	if(gui.getSelectedPanel() >= webcamsStartIndex && gui.getSelectedPanel() < webcamsStartIndex + numCamInputs){
		char temp[256], temp2[256],temp3[256];
		sprintf(temp,"COMPUTE_CG_%i",camDevices[gui.getSelectedPanel()-webcamsStartIndex]);
		sprintf(temp2,"COMPUTE_TA_%i",camDevices[gui.getSelectedPanel()-webcamsStartIndex]);
		sprintf(temp3,"COMPUTE_CF_%i",camDevices[gui.getSelectedPanel()-webcamsStartIndex]);
		if((data.isElement(temp) || data.isElement(temp2)) && data.getInt(0) == 1 ){
			gui.setValueB(temp3, true);
		}
	}

	if(gui.getSelectedPanel() == sensorKinectIndex){
		char temp[256], temp2[256],temp3[256];
		sprintf(temp,"COMPUTE_CG_SENSOR_KINECT");
		sprintf(temp2,"COMPUTE_TA_SENSOR_KINECT");
		sprintf(temp3,"COMPUTE_CF_SENSOR_KINECT");
		if((data.isElement(temp) || data.isElement(temp2)) && data.getInt(0) == 1 ){
			gui.setValueB(temp3, true);
		}
	}

}

//--------------------------------------------------------------
void gamuzaMain::resetInputWarping(guiCallbackData & data){

	char temp[256];
	if(gui.getSelectedPanel() >= webcamsStartIndex && gui.getSelectedPanel() < webcamsStartIndex + numCamInputs){
		sprintf(temp,"RESET_INPUT_WARPING_DEV_%i",camDevices[gui.getSelectedPanel()-webcamsStartIndex]);
		if(data.isElement(temp) && data.getInt(0) == 1){
			resetWarpingPoints(gui.getSelectedPanel()-webcamsStartIndex);
			gui.setValueB(temp, false);
		}
	}
}

//--------------------------------------------------------------
void gamuzaMain::recordNoise(guiCallbackData & data){

	if(gui.getSelectedPanel() >= audioInputStartIndex && gui.getSelectedPanel() < (audioInputStartIndex+audioInputChannels)){
		char temp[256];
		sprintf(temp,"REC_NOISE_FILTER_%i",gui.getSelectedPanel()-audioInputStartIndex);
		if(data.isElement(temp) && data.getInt(0) == 1 ){
			inputAudioCH[gui.getSelectedPanel()-audioInputStartIndex].recNoiseFilter();
			gui.setValueB(temp, false);
		}
	}

}

//--------------------------------------------------------------
void gamuzaMain::changeAnalogPinMode(guiCallbackData & data){

	char temp[256];
	for(unsigned int i=0;i<6;i++){
		sprintf(temp,"ARDUINO_ANALOG_PIN_%i_MODE",i);
		if(data.isElement(temp)){
			if(atoi(data.getString(0).c_str()) == 0){
				analogPinModes[i] = ARD_ON;
			}else if(atoi(data.getString(0).c_str()) == 1){
				analogPinModes[i] = ARD_OFF;
			}
			arduino.sendAnalogPinReporting(i, analogPinModes[i]);
		}
	}
}

//--------------------------------------------------------------
void gamuzaMain::changeDigitalPinMode(guiCallbackData & data){

	char temp[256];
	for(unsigned int i=2;i<14;i++){
		sprintf(temp,"ARDUINO_DIGITAL_PIN_%i_MODE",i);
		if(data.isElement(temp)){
			if(i == 3 || i == 5 || i == 6 || i == 9 || i == 10 || i == 11){
				if(atoi(data.getString(0).c_str()) == 0){
					digitalPinModes[i-2] = ARD_INPUT;
				}else if(atoi(data.getString(0).c_str()) == 1){
					digitalPinModes[i-2] = ARD_OUTPUT;
				}else if(atoi(data.getString(0).c_str()) == 2){
					digitalPinModes[i-2] = ARD_PWM;
				}
			}else{
				if(atoi(data.getString(0).c_str()) == 0){
					digitalPinModes[i-2] = ARD_INPUT;
				}else if(atoi(data.getString(0).c_str()) == 1){
					digitalPinModes[i-2] = ARD_OUTPUT;
				}
			}
			arduino.sendDigitalPinMode(i, digitalPinModes[i-2]);
		}
	}
}

//--------------------------------------------------------------
void gamuzaMain::sendDigitalValue(guiCallbackData & data){
	char temp[256];
	for(unsigned int i=2;i<14;i++){
		sprintf(temp,"ARDUINO_DIGITAL_PIN_%i_VALUE",i);
		if(data.isElement(temp)){
			if(digitalPinModes[i-2] == ARD_OUTPUT){
				if(i == 3 || i == 5 || i == 6 || i == 9 || i == 10 || i == 11){
					if(data.getInt(0) == 0){
						digitalPinValuesOutput[i-2] = data.getInt(0);
					}else{
						digitalPinValuesOutput[i-2] = 1;
					}
					arduino.sendDigital(i, digitalPinValuesOutput[i-2]);
				}else{
					digitalPinValuesOutput[i-2] = data.getInt(0);
					arduino.sendDigital(i, digitalPinValuesOutput[i-2]);
				}
			}else if(digitalPinModes[i-2] == ARD_PWM){
				digitalPinValuesOutput[i-2] = data.getInt(0);
				arduino.sendPwm(i, digitalPinValuesOutput[i-2]);
			}
		}
	}
}

//////////////////////////////////////////////////////////////// GUI Events

#endif
