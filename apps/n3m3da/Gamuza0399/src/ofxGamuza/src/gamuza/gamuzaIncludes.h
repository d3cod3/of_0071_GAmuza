#ifdef TARGET_LINUX
	//-------------------------

	//-------------------------
#endif

#ifdef TARGET_OSX
	//-------------------------
	#include <mach/mach_time.h>
	//-------------------------
#endif

//////////////////////////////////////
// main core of OpenFrameworks
#include "ofMain.h"

// official addons
#include "ofx3DModelLoader.h"
#include "ofxNetwork.h"
#include "ofxOpenCv.h"				// computer vision library
#include "ofxOsc.h"					// Open Sound Control communication library
#include "ofxVectorGraphics.h"
#include "ofxXmlSettings.h"			// read/write on/to xml file library

//////////////////////////////////////
// experimental addons

// GUI
#include "ofxControlPanel.h"		// graphical user interface library [from Theo Watson]
#include "ofxTimeline.h"            // Lightweight SDK for creating graphic timeline tools

// OpenNI SensorKinect
#include "ofxOpenNI.h"				// Simple wrapper for OpenNI and SensorKinect

// live coding "fluxus" style
#include "ofxKeyMap.h"				// alt,ctrl,shift key detection
#include "ofxGLEditor.h"			// openGL text editor "fluxus" style <http://www.pawfal.org/fluxus/>

// live coding language
#include "ofxLua.h"					// Lua embedded scripting interpreter

// AUDIO
#include "ofxAudioSample.h"			// reading&writing audio sample from hard drive with libsndfile

// Midi input/output
#include "ofxMidi.h"                // MIDI input/output

// DMX input/output
#include "ofxDmx.h"                 // DMX input/output

// SYSTEM
#include "ofxMissing.h"				// Date/Time, INI Reader, Recursive file listing. Roxlu missing utils
#include "ofxStringEncoders.h"		// Html string encoders (UTF8, unquote)
#include "ofxSubtitles.h"           // load/save .srt subtitles files

// PHYSICS
#include "ofxVectorField.h"

// MATH
#include "ofxGaussian.h"            // A Gaussian random number generator

// Pixels manipulators
#include "ofxChromaKey.h"
#include "ofxDither.h"
#include "ofxFX.h"

// Text Font addons
#include "ofxArcText.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxTextSuite.h"

// Graphics
#include "ofxDelaunay.h"
#include "ofxSlitScan.h"            // simple utility for creating slit scan effects and video time delays

//////////////////////////////////////
// unofficial code

// GUI classes
#include "scroller.h"               // a simple scroller class

// webcam input classes
#include "sourceTracking.h"			// video input source class [from Emanuele Mazza]
#include "openniTracking.h"			// sensor kinect input source class [from Emanuele Mazza]
#include "matrixAreas.h"			// multiple points/areas mouse control, xml loading and saving [from Emanuele Mazza with great help from code fragment of Chris Sugrue]

// audio input [microphones, instruments, etc. routed via soundcard] class
#include "audioInputChannel.h"		// audio input source class [from Emanuele Mazza]

// audio Synthesis
#include "gaDsp.h"
#include "gaAmplifier.h"
#include "gaOscillator.h"
#include "audioSample.h"
#include "audioModule.h"
