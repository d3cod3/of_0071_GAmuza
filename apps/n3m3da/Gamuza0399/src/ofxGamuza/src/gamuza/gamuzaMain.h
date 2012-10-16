#ifndef _GAMUZA_MAIN
#define _GAMUZA_MAIN

// includes
#include "gamuzaIncludes.h"

// constants
#include "gamuzaConstants.h"


class gamuzaMain : public ofBaseApp, public ofxMidiListener{

	public:

		/////////////////////////////
		// standard OF functions
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		/////////////////////////////

		// audio functions
		void setupAudio();
		void audioIn(float *input, int bufferSize, int nChannels);
		void audioOut(float *output, int bufferSize, int nChannels);
		void addAudioModule(int _wT, float _freq);
		void addAudioModule(int _wT, float _freq, int _ch);
        void addAudioSample(string _file);
        void addInputRecording();
		void resetAudioOutput();

        // MIDI functions
        void setupMidi();
        void updateMidi();
        void newMidiMessage(ofxMidiEventArgs& eventArgs);

		// loading settings from XML
		void loadGamuzaSettings();

		// GUI functions
		void setupGui();
		void setupStringVec();
		void updateGui();
		void drawGui();
		void gamuzaFullscreen();
		void resetWarpingPoints(int actualPanel);
        void initTimeline();
        void receivedTrigger(ofxTLTriggerEventArgs& trigger);

		// EXPORT function
		void saveFrame();
		void printFrame();

		// GUI Events
		void eventsIn(guiCallbackData & data);
        void restartGAmuza(guiCallbackData & data);
		void grabBackgroundEvent(guiCallbackData & data);
		void resetInputWarping(guiCallbackData & data);
		void activateTrackingCF(guiCallbackData & data);
		void recordNoise(guiCallbackData & data);
		void changeAnalogPinMode(guiCallbackData & data);
		void changeDigitalPinMode(guiCallbackData & data);
		void sendDigitalValue(guiCallbackData & data);
		void resetMappingPoints(guiCallbackData & data);
        void loadMappingPoints(guiCallbackData & data);
        void saveMappingPoints(guiCallbackData & data);
        void openFileDialog();
        void saveFileDialog();

		// FBO functions
		void setupFBO();
        void updateFBO();
		void drawFBO();
		void drawIntoFBO(int w, int h);
		void cvHomographyFBO();
		void glGridMeshFBO(int xCalib, int yCalib, int w, int h);

		// Live Coding functions
		void    loadScript(string _script);
		void    renderScript(string & _script);
		string  readScript(string _scriptFile,bool dialog);
        void    checkErrors();

        ofEvent<string> doCompileEvent;

		// ARDUINO functions
		void setupArduino();
		void updateArduino();
		void prepareArduinoOscData();
		void loadArduinoSetting();
		void saveArduinoSetting();

		// OSC functions
		void setupOSC();
		void updateOSC();
        void receiveOSC();
        void resetIncomingOSC();
        void resetOutgoingOSC();
		void sendBuffer();
		void cleanBuffer();
        void sendPrivateMessage(int _type, string _message);
        void receiveScript(string script);

		//////////////////////////////////////////////
		// SETTINGS vars from XML

		// SCREENS settings
		int						mainScreenW;
		int						mainScreenH;
		int						projectionScreenW;
		int						projectionScreenH;
		float					INVprojectionScreenW;
		float					INVprojectionScreenH;

		// AUTOMATION settings
		bool					autoPilot;
		bool					autoLoadScript;
		string					autoScriptFile;

		// FBO settings
		int						gridRes;
		int						fboNumSamples;

		// TRACKING settings
		bool					trackingActivated;
		bool					openniActivated;
		bool					useVideoTest;
		int						workingW;
		int						workingH;
		int						totPixels;
		string					haarFinderFile;

		// AUDIO settings
		bool					audioActivated;
		int						audioDevID;
		int						audioOutputChannels;
		int						audioInputChannels;
		int						audioSamplingRate;
		int						audioBufferSize;
		int						audioNumBuffers;
		int						fftWindowUse;

		// ARDUINO settings
		bool					arduinoActivated;
		string					serialDevice;
		int						baudRate;

		// OSC settings
		string					host_number;
		string					host_port;
        string                  server_port;

        // MIDI settings
        int                     midiPortNumber;

		//////////////////////////////////////////////

		//////////////////////////////////////////////
		// GUI
		ofxControlPanel			gui;
        simpleFileLister		scriptsLister;
		ofxKeyMap				gamuzaKmap;
		ofTexture				emptyTexture;
        ofxTimeline             timeline;
        string                  actualTriggerName;

        float					previewW,previewH,previewY;
        float					lcPrevW, lcPrevH, lcPrevX, lcPrevY;
		float					guiPosX;
		float					guiPosY;
        float                   scaledMouseX,scaledMouseY;
		bool					isFullscreen;
        bool                    showTimeline;
		//////////////////////////////////////////////

		//////////////////////////////////////////////
		// FBO texture with mapping structure vars
		ofFbo					drawingFbo;
		ofFbo					finalTexture;
		ofTexture				drawingTexture;
        ofPixels                outputPix;
		ofShader				shaderColorCorrection;
        float                   fboClearR;
        float                   fboClearG;
        float                   fboClearB;
        float                   fboClearA;
		bool					useShader;
        bool					useSecondaryScreen;
		matrixAreas				finalTextureMapping;
        int                     totalMappingPoints;
        int                     actualMappingPoint;
        bool                    manualEditMappingPoint;
        bool                    activateMouseMapping;

        ofImage					tempFrame;
		//////////////////////////////////////////////

		//////////////////////////////////////////////
		// Live Coding vars
		ofxGLEditor				liveCoding;
		ofxLua					lua;
		scroller                scriptScroll;
        int                     liveKey;
        string                  GAscriptFileName;

        int                     gaFrameCounter;
		//////////////////////////////////////////////

		//////////////////////////////////////////////
		// OpenNI sensor Kinect vars
		openniTracking			sensorKinect;
		int						sensorKinectIndex;
		int						sensorKinectLedState;
		bool					useKinectInfrared;
		//////////////////////////////////////////////

		//////////////////////////////////////////////
		// Video Tracking vars
		sourceTracking			*inputCam;
		int						numCamInputs;
		int*					camDevices;
		string*					deviceNames;
		int						webcamsStartIndex;
		//////////////////////////////////////////////

		//////////////////////////////////////////////
		// Audio INPUT/OUTPUT stream vars
		ofSoundStream			soundStream;
		audioInputChannel		*inputAudioCH;
		int						audioInputStartIndex;

		gaDsp					gamuzaDSP;
		gaAmplifier				gamuzaAMP;

		vector<audioModule>		audioModules;
		int						audioModulesNum;

        vector<audioSample>     inputRecSamples;
        int                     inputRecordingsNum;
        vector<float>           recBuffer;
        int                     recChannel;
        bool                    recordingInput;

		float					*outputBufferCopy;

		bool					flagSystemLoaded;
		bool					computeAudioInput;
		bool					computeAudioOutput;
		//////////////////////////////////////////////

		//////////////////////////////////////////////
		// Arduino vars
		ofArduino				arduino;
		bool					useArduino;
		int						arduinoIndex;
		int						*digitalPinModes;
		int						*analogPinModes;
		int						*digitalPinValuesInput;
		int						*digitalPinValuesOutput;
		int						*analogPinValues;

		bool					useKalmanFilterArduino;
		float					arduino_smoothingFactor;

		ofxCvKalman				*kanalogPinValues[6];
		float					*_kalman_analogPinValues;
		float					*_s_analogPinValues;
		float					*_osc_analogPinValues;
		int						*_osc_digitalPinValuesInput;
		bool					sendOsc_AAP;
		bool					sendOsc_ADP;
		//////////////////////////////////////////////

        //////////////////////////////////////////////
        // MIDI vars
        ofxMidiOut              midiOut;
        ofxMidiIn               midiIn;
        vector<ofVec3f>         midiMapping;
        char                    midi_msg[255];
        int                     midi_port;
        int                     midi_id;
        int                     midi_valueOne;
        int                     midi_valueTwo;
        double                  midi_timestamp;
        //////////////////////////////////////////////

		//////////////////////////////////////////////
		// OSC vars
        vector<string>          oscReceivingLabels;
        vector<string>          oscReceivingValues;
        vector<string>          oscSendingLabels;
        vector<string>          oscSendingValues;
        vector<int>             oscSendingTypes;
		int						oscIndex;
		//////////////////////////////////////////////

        //////////////////////////////////////////////
        // SETTINGS PANEL vars
        void                    setupSettingPanel();
        void                    retrieveHardwaredata();
        void                    drawSettingPanel();

        void                    openAutoScriptDialog(guiCallbackData & data);
        void                    openTrackVideoDialog(guiCallbackData & data);
        void                    openHaarTrackingDialog(guiCallbackData & data);

        void                    listAudioDevices();
        void                    listMidiDevices();
        void                    listSerialDevices();
        void                    setupSettingStrings();
        void                    updateSettingScreens();
        void                    saveGamuzaSettings();

        ofxTextInputField       oscPortField;
        ofxTextInputField       oscIPField;
        ofxTextInputField       oscServerPortField;
        simpleLogger			logger;

        // Retrieving hardware data
        ofSerial	                _serial;
        vector<ofSerialDeviceInfo>  _deviceList;
        vector<string>			    _screenSizesMain;
        vector<string>			    _screenSizesProj;
        int                         _autoPilot;
        int                         _autoloadScript;
        string                      _scriptFile;
        vector<string>			    _oniLedState;
        vector<string>			    _serialDev;
        vector<string>			    _baudRateS;
        vector<string>			    _audioDev;
        vector<string>			    _midiDev;
        vector<string>				_inputCH;
        vector<string>				_outputCH;
        vector<string>			    _samplingRates;
        vector<string>			    _bufferSizes;
        int                         _openniModule;
        int                         _trackingModule;
        int                         _audioModule;
        int                         _arduinoModule;
        int                         _mainScreenW;
        int                         _mainScreenH;
        int                         _secondaryScreenW;
        int                         _secondaryScreenH;
        int                         _fboMaxSamples;
        int                         _mappingGridRes;
        int                         _loadVideoTest;
        string                      _videoTestFile;
        string                      _haarCascadeFile;
        int                         _useInfrared;
        int                         _ledState;
        int                         _audioDevice;
        int                         _midiDevice;
        string						_inputChannels;
        string						_outputChannels;
        string                      _samplingRate;
        string                      _bufferSize;
        string                      _baudRate;
        string                      _serialPort;
        //////////////////////////////////////////////

	private:

		ofMutex					gamuzaSetup;
		ofxXmlSettings			setting_data;
        ofxXmlSettings			receiving_port_editor;
        string                  gamuzaFont;
        int                     gamuzaFontSize;

		int						currentSavedFrame;
		float					gamuzaRealFPS;
		bool					useVSync;


};

#endif
