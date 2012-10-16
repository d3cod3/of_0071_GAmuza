#ifndef _GAMUZAGETTERS
#define _GAMUZAGETTERS

// constants
#include "gamuzaConstants.h"
#include "gamuza.h"

extern gamuza * gapp; // external reference to gamuza app, declared in main.cpp

//--------------------------------------------------------------
// SYSTEM SECTION
//--------------------------------------------------------------
void gaSaveFrame(string _name){
    if(gapp->gamuzaBase.useSecondaryScreen && gapp->gamuzaBase.useShader){
        gapp->gamuzaBase.finalTexture.readToPixels(gapp->gamuzaBase.outputPix);
    }else{
        gapp->gamuzaBase.drawingTexture.readToPixels(gapp->gamuzaBase.outputPix);
    }
    gapp->gamuzaBase.tempFrame.setFromPixels(gapp->gamuzaBase.outputPix);
    gapp->gamuzaBase.tempFrame.saveImage(_name.c_str());
}

void gaLog(string _log){
    gapp->gamuzaBase.sendPrivateMessage(GAMUZA_CONSOLE_LOG, _log);
}

string gaGetOSCSendingIP(){
    return gapp->gamuzaBase.host_number;
}

int gaGetFrameNum(){
    return gapp->gamuzaBase.gaFrameCounter;
}

string gaGetLocalDataPath(string _file){
    #ifdef TARGET_OSX
    string correctedPath;

    string path = gapp->gamuzaBase.GAscriptFileName;

    size_t cutPos = path.find_last_of("/");

    correctedPath = path.substr(0,cutPos);
    finalPath = "../../../../.."+correctedPath+"/data/"+_file;
    #endif

    #ifdef TARGET_LINUX
    string finalPath;
    string isGA = ".ga";
    size_t found;
    found = _file.find(isGA);

    if(found!=string::npos){
        finalPath = "data/scripts_data/"+_file;
    }else{
        finalPath = "scripts_data/"+_file;
    }

    #endif

    return finalPath;
}

//--------------------------------------------------------------
// GRAPHICS SECTION
//--------------------------------------------------------------
void gaBackground(float g, float a){
	ofFill();
	glColor4f(g,g,g,a);
	ofRect(0,0,gapp->gamuzaBase.projectionScreenW,gapp->gamuzaBase.projectionScreenH);
}

void gaBackground(float r, float g, float b, float a){
	ofFill();
	glColor4f(r,g,b,a);
	ofRect(0,0,gapp->gamuzaBase.projectionScreenW,gapp->gamuzaBase.projectionScreenH);
}

ofTexture gaGetWebcamTexture(int _id){
	if(_id < gapp->gamuzaBase.numCamInputs && _id >= 0 && gapp->gamuzaBase.trackingActivated && gapp->gamuzaBase.inputCam[_id].captureVideo){
		return gapp->gamuzaBase.inputCam[_id].camTexture;
	}else{
		return gapp->gamuzaBase.emptyTexture;
	}
}

ofTexture gaGetONITexture(){
	if(gapp->gamuzaBase.openniActivated && gapp->gamuzaBase.sensorKinect.useKinect){
		return gapp->gamuzaBase.sensorKinect.camTexture;
	}else{
		return gapp->gamuzaBase.emptyTexture;
	}
}

unsigned char* gaGetWebcamPixels(int _id){
	if(_id < gapp->gamuzaBase.numCamInputs && _id >= 0 && gapp->gamuzaBase.trackingActivated && gapp->gamuzaBase.inputCam[_id].captureVideo){
		return gapp->gamuzaBase.inputCam[_id].vidGrabber.getPixels();
	}
}

ofPixelsRef gaGetWebcamPixelsRef(int _id){
	if(_id < gapp->gamuzaBase.numCamInputs && _id >= 0 && gapp->gamuzaBase.trackingActivated && gapp->gamuzaBase.inputCam[_id].captureVideo){
		return gapp->gamuzaBase.inputCam[_id].vidGrabber.getPixelsRef();
	}
}

//--------------------------------------------------------------
// 3D SECTION
//--------------------------------------------------------------

void gaDrawAxis(float _size, ofColor _color, bool posNeg){
    ofPushStyle();
	ofSetLineWidth(3);

    if(posNeg){
        ofSetColor(_color);
        ofLine(0, 0, 0, _size, 0, 0);
        ofLine(0, 0, 0, 0, _size, 0);
        ofLine(0, 0, 0, 0, 0, _size);
        ofSetColor(127,127,127);
        ofLine(-_size, 0, 0, 0, 0, 0);
        ofLine(0, -_size, 0, 0, 0, 0);
        ofLine(0, 0, -_size, 0, 0, 0);
    }else{
        ofSetColor(_color);
        ofLine(0, 0, 0, _size, 0, 0);
        ofLine(0, 0, 0, 0, _size, 0);
        ofLine(0, 0, 0, 0, 0, _size);
    }

    ofPopStyle();
}

void gaDrawXAxis(float _size, ofColor _color, bool posNeg){
    ofPushStyle();
	ofSetLineWidth(3);

	// draw x axis
    if(posNeg){
        ofSetColor(_color);
        ofLine(0, 0, 0, _size, 0, 0);
        ofSetColor(127,127,127);
        ofLine(-_size, 0, 0, 0, 0, 0);
    }else{
        ofSetColor(_color);
        ofLine(0, 0, 0, _size, 0, 0);
    }

    ofPopStyle();
}

void gaDrawYAxis(float _size, ofColor _color, bool posNeg){
    ofPushStyle();
	ofSetLineWidth(3);

	// draw y axis
    if(posNeg){
        ofSetColor(_color);
        ofLine(0, 0, 0, 0, _size, 0);
        ofSetColor(127,127,127);
        ofLine(0, -_size, 0, 0, 0, 0);
    }else{
        ofSetColor(_color);
        ofLine(0, 0, 0, 0, _size, 0);
    }

    ofPopStyle();
}

void gaDrawZAxis(float _size, ofColor _color, bool posNeg){
    ofPushStyle();
	ofSetLineWidth(3);

	// draw z axis
    if(posNeg){
        ofSetColor(_color);
        ofLine(0, 0, 0, 0, 0, _size);
        ofSetColor(127,127,127);
        ofLine(0, 0, -_size, 0, 0, 0);
    }else{
        ofSetColor(_color);
        ofLine(0, 0, 0, 0, 0, _size);
    }

    ofPopStyle();
}

//--------------------------------------------------------------
// PIXELS MANIPULATION SECTION
//--------------------------------------------------------------
ofTexture gaGetWebcamMiller(int _id, int _black, float _sigma1, float _sigma2, float _tau, float _thresh){
    if(_id < gapp->gamuzaBase.numCamInputs && _id >= 0 && gapp->gamuzaBase.trackingActivated && gapp->gamuzaBase.inputCam[_id].captureVideo){
        gapp->gamuzaBase.inputCam[_id].computeCLD(_black, _sigma1, _sigma2, _tau, _thresh);
		return gapp->gamuzaBase.inputCam[_id].effectedTexture;
	}else{
		return gapp->gamuzaBase.emptyTexture;
	}
}

//--------------------------------------------------------------
// TIMELINE SECTION
//--------------------------------------------------------------
void gaPlayTimeline(){
    gapp->gamuzaBase.timeline.play();
}

void gaStopTimeline(){
    gapp->gamuzaBase.timeline.stop();
}

void gaSetTimelineDurationInFrames(int frames){
    gapp->gamuzaBase.timeline.setDurationInFrames(frames);
}

void gaSetTimelineLoopType(int _type){
    if(_type == OF_LOOP_NONE){
        gapp->gamuzaBase.timeline.setLoopType(OF_LOOP_NONE);
    }else if(_type == OF_LOOP_NORMAL){
        gapp->gamuzaBase.timeline.setLoopType(OF_LOOP_NORMAL);
    }
}

void gaAddTimelineKeyframes(string _name, string _file, float _min, float _max){
    char temp[256];
    sprintf(temp,"settings/timeline/keyframes/%s",_file.c_str());
    gapp->gamuzaBase.timeline.addKeyframes(_name, temp, ofRange(_min, _max));

}

float gaGetTimelineKeyframeValue(string _name){
    return gapp->gamuzaBase.timeline.getKeyframeValue(_name);
}

string gaGetTimelineTrigger(){
    return gapp->gamuzaBase.actualTriggerName;
}

//--------------------------------------------------------------
// MIDI SECTION
//--------------------------------------------------------------
int gaGetMidiChannel(){
    return gapp->gamuzaBase.midi_id;
}

int gaGetMidiByteOne(){
    return gapp->gamuzaBase.midi_valueOne;
}

int gaGetMidiByteTwo(){
    return gapp->gamuzaBase.midi_valueTwo;
}

float gaGetMidiValue(int _channel, int _index){ // _index is midi byteOne
    for(int i=0; i<gapp->gamuzaBase.midiMapping.size();i++){
        if(gapp->gamuzaBase.midiMapping[i].x == _channel && gapp->gamuzaBase.midiMapping[i].y == _index){
            return gapp->gamuzaBase.midiMapping[i].z/127.0f;
            break;
        }
    }
}

//--------------------------------------------------------------
// OSC SECTION
//--------------------------------------------------------------
void gaReceiveOSCMessage(string _oscLabel){
    gapp->gamuzaBase.oscReceivingLabels.push_back(_oscLabel);
    gapp->gamuzaBase.oscReceivingValues.push_back("");
}

string gaGetOSCValue(string _oscLabel){
    for(int i=0;i<gapp->gamuzaBase.oscReceivingLabels.size();i++){
        if(_oscLabel == gapp->gamuzaBase.oscReceivingLabels[i]){
            return gapp->gamuzaBase.oscReceivingValues[i];
            break;
        }
    }
}

void gaSendOSCMessage(string _oscLabel,int _type){
    gapp->gamuzaBase.oscSendingLabels.push_back(_oscLabel);
    gapp->gamuzaBase.oscSendingTypes.push_back(_type);
    gapp->gamuzaBase.oscSendingValues.push_back("");
}

void gaSetOSCValue(string _oscLabel,string _value){
    for(int i=0;i<gapp->gamuzaBase.oscSendingLabels.size();i++){
        if(_oscLabel == gapp->gamuzaBase.oscSendingLabels[i]){
            gapp->gamuzaBase.oscSendingValues[i] = _value;
        }
    }
}

//--------------------------------------------------------------
// AUDIO INPUT RECORDING SECTION
//--------------------------------------------------------------
void gaStartInputRecording(int _ch){
	if(gapp->gamuzaBase.audioActivated && _ch < gapp->gamuzaBase.audioInputChannels && gapp->gamuzaBase.audioInputChannels > 0){
		if(gapp->gamuzaBase.inputAudioCH[_ch].captureAudio && gapp->gamuzaBase.recordingInput == false){
            gapp->gamuzaBase.recChannel = _ch;
			gapp->gamuzaBase.recordingInput = true;
		}
	}
}

void gaStopInputRecording(){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioInputChannels > 0){
		gapp->gamuzaBase.recordingInput = false;
        gapp->gamuzaBase.addInputRecording();
	}
}

void gaInputRecPlay(int _pos){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		if(_pos < gapp->gamuzaBase.inputRecSamples.size()){
			gapp->gamuzaBase.inputRecSamples[_pos].play();
		}
	}
}

void gaInputRecStop(int _pos){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		if(_pos < gapp->gamuzaBase.inputRecSamples.size()){
			gapp->gamuzaBase.inputRecSamples[_pos].stop();
		}
	}
}

void gaSetInputRecVolume(int _pos, float _vol){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		if(_pos < gapp->gamuzaBase.inputRecSamples.size()){
			if(_vol > 1.0 || _vol < -1.0){
				gapp->gamuzaBase.inputRecSamples[_pos].setVolume(1.0);
			}else{
				gapp->gamuzaBase.inputRecSamples[_pos].setVolume(_vol);
			}
		}
	}
}

void gaSetInputRecLooping(int _pos, bool _l){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		if(_pos < gapp->gamuzaBase.inputRecSamples.size()){
			gapp->gamuzaBase.inputRecSamples[_pos].setLooping(_l);
		}
	}
}

void gaSetInputRecPaused(int _pos, bool _l){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		if(_pos < gapp->gamuzaBase.inputRecSamples.size()){
			gapp->gamuzaBase.inputRecSamples[_pos].setPaused(_l);
		}
	}
}

void gaSetInputRecSpeed(int _pos, float _speed){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		if(_pos < gapp->gamuzaBase.inputRecSamples.size()){
			if(_speed > 1.0){
				gapp->gamuzaBase.inputRecSamples[_pos].setSpeed(1.0);
			}else if(_speed < -1.0){
                gapp->gamuzaBase.inputRecSamples[_pos].setSpeed(-1.0);
            }else{
				gapp->gamuzaBase.inputRecSamples[_pos].setSpeed(_speed);
			}
		}
	}
}

void gaDrawInputRecHead(int _pos, int x, int y, int w, int h){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		if(_pos < gapp->gamuzaBase.inputRecSamples.size()){
			gapp->gamuzaBase.inputRecSamples[_pos].drawHead(x,y,w,h);
		}
	}
}

//--------------------------------------------------------------
// AUDIO SYNTH SECTION
//--------------------------------------------------------------
void gaSetupOSC(int _wt, float _freq){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		gapp->gamuzaBase.addAudioModule(_wt, _freq);
	}
}

void gaSetupMonoOSC(int _wt, float _freq, int _channel){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		gapp->gamuzaBase.addAudioModule(_wt, _freq, _channel);
	}
}

void gaSetOscVolume(int _pos, float _vol){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		if(_pos < gapp->gamuzaBase.audioModules.size()){
			if(_vol > 1.0 || _vol < -1.0){
				gapp->gamuzaBase.audioModules[_pos].setVolume(1.0);
			}else{
				gapp->gamuzaBase.audioModules[_pos].setVolume(_vol);
			}
		}
	}
}

void gaSetOscFrequency(int _pos, float _freq){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		if(_pos < gapp->gamuzaBase.audioModules.size()){
			gapp->gamuzaBase.audioModules[_pos].setFrequency(_freq);
		}
	}
}

void gaSetOscWaveType(int _pos, int _wt){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		if(_pos < gapp->gamuzaBase.audioModules.size()){
			gapp->gamuzaBase.audioModules[_pos].setWave(_wt);
		}
	}
}

void gaSetOscTuning(int _pos, int _tuning){
	if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0){
		if(_pos < gapp->gamuzaBase.audioModules.size()){
			if(_tuning <= 1.0 && _tuning >= 0.0){
				gapp->gamuzaBase.audioModules[_pos].setTuning(_tuning);
			}
		}
	}
}

float gaNote(int _note){
	if(_note <= SI_8 && _note >= DO_0){
		return noteToHarmonicFrequency(_note);
	}else{
		return 0.0f;
	}
}

//--------------------------------------------------------------
// OPENNI SENSOR KINECT SECTION
//--------------------------------------------------------------
int gaONIRunningBlob(){
	if(gapp->gamuzaBase.openniActivated && gapp->gamuzaBase.sensorKinect.useKinect){
		return gapp->gamuzaBase.sensorKinect.runningBlobs;
	}else{
		return 0;
	}
}

float gaONIBlobX(int _bId){
	if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < MAX_USERS_HARDLIMIT){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder){
			for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
				if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId){
					return gapp->gamuzaBase.sensorKinect._osc_blobInfo[e].center.x;
				}
			}
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}

}

float gaONIBlobY(int _bId){
	if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < MAX_USERS_HARDLIMIT){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder){
			for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
				if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId){
					return gapp->gamuzaBase.sensorKinect._osc_blobInfo[e].center.y;
				}
			}
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}

}

float gaONIBlobW(int _bId){
	if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < MAX_USERS_HARDLIMIT){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder){
			for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
				if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId){
					return gapp->gamuzaBase.sensorKinect._osc_blobInfo[e].size.width;
				}
			}
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}

}

float gaONIBlobH(int _bId){
	if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < MAX_USERS_HARDLIMIT){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder){
			for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
				if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId){
					return gapp->gamuzaBase.sensorKinect._osc_blobInfo[e].size.height;
				}
			}
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}

}

float gaONIBlobAngle(int _bId){
	if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < MAX_USERS_HARDLIMIT){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder){
			for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
				if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId){
					return gapp->gamuzaBase.sensorKinect._osc_blobInfo[e].angle;
				}
			}
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}

}

int gaONIBlobContourSize(int _bId){
	if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < gapp->gamuzaBase.sensorKinect.runningBlobs){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder){
            if(gapp->gamuzaBase.sensorKinect.cfDetail == 0 || gapp->gamuzaBase.sensorKinect.cfDetail == 1){
                for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
                    if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId){
                        return gapp->gamuzaBase.sensorKinect.contourSmooth[e].size();
                    }
                }
            }else if(gapp->gamuzaBase.sensorKinect.cfDetail == 2){
                for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
                    if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId){
                        return gapp->gamuzaBase.sensorKinect.contourSimple[e].size();
                    }
                }
            }
        }else{
			return 0;
		}
    }else{
        return 0;
    }
}

float gaONIBlobCPointX(int _bId, int _cPoint){
	if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < gapp->gamuzaBase.sensorKinect.runningBlobs){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder){
            if(gapp->gamuzaBase.sensorKinect.cfDetail == 0 || gapp->gamuzaBase.sensorKinect.cfDetail == 1){
                for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
                    if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId && _cPoint < gapp->gamuzaBase.sensorKinect.contourSmooth[e].size()){
                        return gapp->gamuzaBase.sensorKinect.contourSmooth[e].at(_cPoint).x;
                    }
                }
            }else if(gapp->gamuzaBase.sensorKinect.cfDetail == 2){
                for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
                    if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId && _cPoint < gapp->gamuzaBase.sensorKinect.contourSmooth[e].size()){
                        return gapp->gamuzaBase.sensorKinect.contourSimple[e].at(_cPoint).x;
                    }
                }
            }
        }else{
			return 0.0f;
		}
    }else{
        return 0.0f;
    }
}

float gaONIBlobCPointY(int _bId, int _cPoint){
	if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < gapp->gamuzaBase.sensorKinect.runningBlobs){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder){
            if(gapp->gamuzaBase.sensorKinect.cfDetail == 0 || gapp->gamuzaBase.sensorKinect.cfDetail == 1){
                for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
                    if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId && _cPoint < gapp->gamuzaBase.sensorKinect.contourSmooth[e].size()){
                        return gapp->gamuzaBase.sensorKinect.contourSmooth[e].at(_cPoint).y;
                    }
                }
            }else if(gapp->gamuzaBase.sensorKinect.cfDetail == 2){
                for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
                    if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId && _cPoint < gapp->gamuzaBase.sensorKinect.contourSmooth[e].size()){
                        return gapp->gamuzaBase.sensorKinect.contourSimple[e].at(_cPoint).y;
                    }
                }
            }
        }else{
			return 0.0f;
		}
    }else{
        return 0.0f;
    }
}

int gaONIBlobGeometrySize(int _bId){
	if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < gapp->gamuzaBase.sensorKinect.runningBlobs){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder && gapp->gamuzaBase.sensorKinect.computeContourGeometry){
            for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
				if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId){
                    return gapp->gamuzaBase.sensorKinect.geomLines[e].size();
                }
            }
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

float gaONIBlobGLineX1(int _bId, int _gLine){
    if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < gapp->gamuzaBase.sensorKinect.runningBlobs){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder && gapp->gamuzaBase.sensorKinect.computeContourGeometry){
            for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
				if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId && _gLine < gapp->gamuzaBase.sensorKinect._osc_blobGeom[e].size()){
                    return gapp->gamuzaBase.sensorKinect.geomLines[e].at(_gLine).x;
                }
            }
        }else{
			return 0.0f;
		}
    }else{
        return 0.0f;
    }
}

float gaONIBlobGLineY1(int _bId, int _gLine){
    if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < gapp->gamuzaBase.sensorKinect.runningBlobs){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder && gapp->gamuzaBase.sensorKinect.computeContourGeometry){
            for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
				if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId && _gLine < gapp->gamuzaBase.sensorKinect._osc_blobGeom[e].size()){
                    return gapp->gamuzaBase.sensorKinect.geomLines[e].at(_gLine).y;
                }
            }
        }else{
			return 0.0f;
		}
    }else{
        return 0.0f;
    }
}

float gaONIBlobGLineX2(int _bId, int _gLine){
    if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < gapp->gamuzaBase.sensorKinect.runningBlobs){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder && gapp->gamuzaBase.sensorKinect.computeContourGeometry){
            for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
				if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId && _gLine < gapp->gamuzaBase.sensorKinect._osc_blobGeom[e].size()){
                    return gapp->gamuzaBase.sensorKinect.geomLines[e].at(_gLine).z;
                }
            }
        }else{
			return 0.0f;
		}
    }else{
        return 0.0f;
    }
}

float gaONIBlobGLineY2(int _bId, int _gLine){
    if(gapp->gamuzaBase.openniActivated && _bId >= 0 && _bId < gapp->gamuzaBase.sensorKinect.runningBlobs){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder && gapp->gamuzaBase.sensorKinect.computeContourGeometry){
            for(unsigned int e = 0; e < gapp->gamuzaBase.sensorKinect.runningBlobs; e++){
				if(gapp->gamuzaBase.sensorKinect.blobsOrder[e] == _bId && _gLine < gapp->gamuzaBase.sensorKinect._osc_blobGeom[e].size()){
                    return gapp->gamuzaBase.sensorKinect.geomLines[e].at(_gLine).w;
                }
            }
        }else{
			return 0.0f;
		}
    }else{
        return 0.0f;
    }
}

float gaONIOpticalFlowX(int _index){
	if(gapp->gamuzaBase.openniActivated){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeOpticalFlow){
			return gapp->gamuzaBase.sensorKinect._osc_opfVel[_index].x;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaONIOpticalFlowY(int _index){
	if(gapp->gamuzaBase.openniActivated){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeOpticalFlow){
			return gapp->gamuzaBase.sensorKinect._osc_opfVel[_index].y;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaONIOpticalFlowVX(int _index){
	if(gapp->gamuzaBase.openniActivated){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeOpticalFlow){
			return gapp->gamuzaBase.sensorKinect._osc_opfVel[_index].z;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaONIOpticalFlowVY(int _index){
	if(gapp->gamuzaBase.openniActivated){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeOpticalFlow){
			return gapp->gamuzaBase.sensorKinect._osc_opfVel[_index].w;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

bool gaONITrigger(int _aID){
	if(gapp->gamuzaBase.openniActivated && _aID < TRIGGER_AREAS_NUM){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.computeContourFinder && gapp->gamuzaBase.sensorKinect.computeTriggerAreas){
			return gapp->gamuzaBase.sensorKinect.triggerState[_aID];
		}else{
			return -1;
		}
	}else{
		return -1;
	}
}

float gaONIHandX(int hand){
	if(gapp->gamuzaBase.openniActivated && hand < 4){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.isTrackingHands){
			return gapp->gamuzaBase.sensorKinect._osc_hands_Pos[hand].x;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaONIHandY(int hand){
	if(gapp->gamuzaBase.openniActivated && hand < 4){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.isTrackingHands){
			return gapp->gamuzaBase.sensorKinect._osc_hands_Pos[hand].y;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaONIHandZ(int hand){
	if(gapp->gamuzaBase.openniActivated && hand < 4){
		if(gapp->gamuzaBase.sensorKinect.useKinect && gapp->gamuzaBase.sensorKinect.isTrackingHands){
			return gapp->gamuzaBase.sensorKinect._osc_hands_Pos[hand].z;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaONIAccelerometerX(){
	if(gapp->gamuzaBase.openniActivated){
		if(gapp->gamuzaBase.sensorKinect.useKinect){
			return gapp->gamuzaBase.sensorKinect._osc_sensorAcc.x;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaONIAccelerometerY(){
	if(gapp->gamuzaBase.openniActivated){
		if(gapp->gamuzaBase.sensorKinect.useKinect){
			return gapp->gamuzaBase.sensorKinect._osc_sensorAcc.y;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaONIAccelerometerZ(){
	if(gapp->gamuzaBase.openniActivated){
		if(gapp->gamuzaBase.sensorKinect.useKinect){
			return gapp->gamuzaBase.sensorKinect._osc_sensorAcc.z;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaONITilt(){
	if(gapp->gamuzaBase.openniActivated){
		if(gapp->gamuzaBase.sensorKinect.useKinect){
			return gapp->gamuzaBase.sensorKinect._osc_sensorTilt;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

//--------------------------------------------------------------
// WEBCAM TRACKING SECTION
//--------------------------------------------------------------
float gaCamMotionQ(int _dID){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs  && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo){
			return gapp->gamuzaBase.inputCam[_dID]._osc_MDQ;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaCamMotionX(int _dID){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs  && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo){
			return gapp->gamuzaBase.inputCam[_dID]._osc_MDCM.x;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaCamMotionY(int _dID){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs  && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo){
			return gapp->gamuzaBase.inputCam[_dID]._osc_MDCM.y;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

int gaCamRunningBlob(int _dID){
	if(gapp->gamuzaBase.trackingActivated && gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs  && _dID >= 0 && gapp->gamuzaBase.inputCam[_dID].computeContourFinder){
		return gapp->gamuzaBase.inputCam[_dID].runningBlobs;
	}else{
		return 0;
	}
}

float gaCamBlobX(int _dID,int _bId){
	if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs  && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder){
			for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
				if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId){
					return gapp->gamuzaBase.inputCam[_dID]._osc_blobInfo[e].center.x;
				}
			}
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}

}

float gaCamBlobY(int _dID,int _bId){
	if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder){
			for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
				if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId){
					return gapp->gamuzaBase.inputCam[_dID]._osc_blobInfo[e].center.y;
				}
			}
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}

}

float gaCamBlobW(int _dID,int _bId){
	if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder){
			for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
				if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId){
					return gapp->gamuzaBase.inputCam[_dID]._osc_blobInfo[e].size.width;
				}
			}
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}

}


float gaCamBlobH(int _dID,int _bId){
	if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder){
			for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
				if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId){
					return gapp->gamuzaBase.inputCam[_dID]._osc_blobInfo[e].size.height;
				}
			}
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}

}

float gaCamBlobAngle(int _dID,int _bId){
	if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder){
			for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
				if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId){
					return gapp->gamuzaBase.inputCam[_dID]._osc_blobInfo[e].angle;
				}
			}
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}

}

int gaCamBlobContourSize(int _dID, int _bId){
    if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder){
            if(gapp->gamuzaBase.inputCam[_dID].cfDetail == 0 || gapp->gamuzaBase.inputCam[_dID].cfDetail == 1){
                for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
                    if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId){
                        return gapp->gamuzaBase.inputCam[_dID].contourSmooth[e].size();
                    }
                }
            }else if(gapp->gamuzaBase.inputCam[_dID].cfDetail == 2){
                for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
                    if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId){
                        return gapp->gamuzaBase.inputCam[_dID].contourSimple[e].size();
                    }
                }
            }
        }else{
			return 0;
		}
    }else{
        return 0;
    }
}

float gaCamBlobCPointX(int _dID, int _bId, int _cPoint){
    if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder){
            if(gapp->gamuzaBase.inputCam[_dID].cfDetail == 0 || gapp->gamuzaBase.inputCam[_dID].cfDetail == 1){
                for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
                    if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId && _cPoint < gapp->gamuzaBase.inputCam[_dID].contourSmooth[e].size()){
                        return gapp->gamuzaBase.inputCam[_dID].contourSmooth[e].at(_cPoint).x;
                    }
                }
            }else if(gapp->gamuzaBase.inputCam[_dID].cfDetail == 2){
                for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
                    if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId && _cPoint < gapp->gamuzaBase.inputCam[_dID].contourSimple[e].size()){
                        return gapp->gamuzaBase.inputCam[_dID].contourSimple[e].at(_cPoint).x;
                    }
                }
            }
        }else{
			return 0.0f;
		}
    }else{
        return 0.0f;
    }
}

float gaCamBlobCPointY(int _dID, int _bId, int _cPoint){
    if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder){
            if(gapp->gamuzaBase.inputCam[_dID].cfDetail == 0 || gapp->gamuzaBase.inputCam[_dID].cfDetail == 1){
                for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
                    if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId && _cPoint < gapp->gamuzaBase.inputCam[_dID].contourSmooth[e].size()){
                        return gapp->gamuzaBase.inputCam[_dID].contourSmooth[e].at(_cPoint).y;
                    }
                }
            }else if(gapp->gamuzaBase.inputCam[_dID].cfDetail == 2){
                for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
                    if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId && _cPoint < gapp->gamuzaBase.inputCam[_dID].contourSimple[e].size()){
                        return gapp->gamuzaBase.inputCam[_dID].contourSimple[e].at(_cPoint).y;
                    }
                }
            }
        }else{
			return 0.0f;
		}
    }else{
        return 0.0f;
    }
}

int gaCamBlobGeometrySize(int _dID,int _bId){
	if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder && gapp->gamuzaBase.inputCam[_dID].computeContourGeometry){
            for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
				if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId){
                    return gapp->gamuzaBase.inputCam[_dID].geomLines[e].size();
                }
            }
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

float gaCamBlobGLineX1(int _dID, int _bId, int _gLine){
    if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder && gapp->gamuzaBase.inputCam[_dID].computeContourGeometry){
            for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
				if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId && _gLine < gapp->gamuzaBase.inputCam[_dID]._osc_blobGeom[e].size()){
                    return gapp->gamuzaBase.inputCam[_dID].geomLines[e].at(_gLine).x;
                }
            }
        }else{
			return 0.0f;
		}
    }else{
        return 0.0f;
    }
}

float gaCamBlobGLineY1(int _dID, int _bId, int _gLine){
    if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder && gapp->gamuzaBase.inputCam[_dID].computeContourGeometry){
            for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
				if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId && _gLine < gapp->gamuzaBase.inputCam[_dID]._osc_blobGeom[e].size()){
                    return gapp->gamuzaBase.inputCam[_dID].geomLines[e].at(_gLine).y;
                }
            }
        }else{
           return 0.0f;
       }
   }else{
       return 0.0f;
   }
}

float gaCamBlobGLineX2(int _dID, int _bId, int _gLine){
    if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder && gapp->gamuzaBase.inputCam[_dID].computeContourGeometry){
            for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
				if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId && _gLine < gapp->gamuzaBase.inputCam[_dID]._osc_blobGeom[e].size()){
                    return gapp->gamuzaBase.inputCam[_dID].geomLines[e].at(_gLine).z;
                }
           }
       }else{
           return 0.0f;
       }
   }else{
       return 0.0f;
   }
}

float gaCamBlobGLineY2(int _dID, int _bId, int _gLine){
    if(gapp->gamuzaBase.trackingActivated && _bId >= 0 && _bId < gapp->gamuzaBase.inputCam[_dID].runningBlobs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && gapp->gamuzaBase.inputCam[_dID].computeContourFinder && gapp->gamuzaBase.inputCam[_dID].computeContourGeometry){
            for(unsigned int e = 0; e < gapp->gamuzaBase.inputCam[_dID].runningBlobs; e++){
				if(gapp->gamuzaBase.inputCam[_dID].blobsOrder[e] == _bId && _gLine < gapp->gamuzaBase.inputCam[_dID]._osc_blobGeom[e].size()){
                    return gapp->gamuzaBase.inputCam[_dID].geomLines[e].at(_gLine).w;
                }
            }
        }else{
            return 0.0f;
        }
   }else{
       return 0.0f;
   }
}

float gaCamOpticalFlowX(int _dID, int _index){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && gapp->gamuzaBase.inputCam[_dID].computeOpticalFlow){
			return gapp->gamuzaBase.inputCam[_dID]._osc_opfVel[_index].x;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaCamOpticalFlowY(int _dID, int _index){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && gapp->gamuzaBase.inputCam[_dID].computeOpticalFlow){
			return gapp->gamuzaBase.inputCam[_dID]._osc_opfVel[_index].y;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaCamOpticalFlowVX(int _dID, int _index){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && gapp->gamuzaBase.inputCam[_dID].computeOpticalFlow){
			return gapp->gamuzaBase.inputCam[_dID]._osc_opfVel[_index].z;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaCamOpticalFlowVY(int _dID, int _index){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && gapp->gamuzaBase.inputCam[_dID].computeOpticalFlow){
			return gapp->gamuzaBase.inputCam[_dID]._osc_opfVel[_index].w;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

int gaCamRunningHaar(int _dID){
	if(gapp->gamuzaBase.trackingActivated && gapp->gamuzaBase.inputCam[_dID].captureVideo && _dID < gapp->gamuzaBase.numCamInputs && _dID >= 0 && gapp->gamuzaBase.inputCam[_dID].computeHaarFinder){
		return gapp->gamuzaBase.inputCam[_dID].numFace;
	}else{
		return 0;
	}
}

float gaCamHaarX(int _dID, int _hID){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _hID < gapp->gamuzaBase.inputCam[_dID].numFace && gapp->gamuzaBase.inputCam[_dID].computeHaarFinder){
			return gapp->gamuzaBase.inputCam[_dID]._osc_ftInfo[_hID].x;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaCamHaarY(int _dID, int _hID){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _hID < gapp->gamuzaBase.inputCam[_dID].numFace && gapp->gamuzaBase.inputCam[_dID].computeHaarFinder){
			return gapp->gamuzaBase.inputCam[_dID]._osc_ftInfo[_hID].y;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaCamHaarW(int _dID, int _hID){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _hID < gapp->gamuzaBase.inputCam[_dID].numFace && gapp->gamuzaBase.inputCam[_dID].computeHaarFinder){
			return gapp->gamuzaBase.inputCam[_dID]._osc_ftInfo[_hID].z;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaCamHaarH(int _dID, int _hID){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs && _dID >= 0){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && _hID < gapp->gamuzaBase.inputCam[_dID].numFace && gapp->gamuzaBase.inputCam[_dID].computeHaarFinder){
			return gapp->gamuzaBase.inputCam[_dID]._osc_ftInfo[_hID].w;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

bool gaCamTrigger(int _dID, int _aID){
	if(gapp->gamuzaBase.trackingActivated && _dID < gapp->gamuzaBase.numCamInputs && _dID >= 0 && _aID < TRIGGER_AREAS_NUM){
		if(gapp->gamuzaBase.inputCam[_dID].captureVideo && gapp->gamuzaBase.inputCam[_dID].computeContourFinder && gapp->gamuzaBase.inputCam[_dID].computeTriggerAreas){
			return gapp->gamuzaBase.inputCam[_dID].triggerState[_aID];
		}else{
			return -1;
		}
	}else{
		return -1;
	}
}

//--------------------------------------------------------------
// AUDIO INPUT SECTION
//--------------------------------------------------------------
float gaGetVolume(int _ch){
	if(gapp->gamuzaBase.audioActivated && _ch < gapp->gamuzaBase.audioInputChannels){
		if(gapp->gamuzaBase.inputAudioCH[_ch].captureAudio){
			return gapp->gamuzaBase.inputAudioCH[_ch]._osc_chVolume;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaGetPitch(int _ch){
	if(gapp->gamuzaBase.audioActivated && _ch < gapp->gamuzaBase.audioInputChannels){
		if(gapp->gamuzaBase.inputAudioCH[_ch].captureAudio){
			return gapp->gamuzaBase.inputAudioCH[_ch]._osc_chPitch;
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaGetFFTBand(int _ch, int _pos){
	if(gapp->gamuzaBase.audioActivated && _ch < gapp->gamuzaBase.audioInputChannels && _pos < BARK_SCALE_CRITICAL_BANDS){
		if(gapp->gamuzaBase.inputAudioCH[_ch].captureAudio){
			return gapp->gamuzaBase.inputAudioCH[_ch]._osc_barkBins[_pos];
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}

}

float gaGetFFTBin(int _ch, int _pos){
	if(gapp->gamuzaBase.audioActivated && _ch < gapp->gamuzaBase.audioInputChannels && _pos < gapp->gamuzaBase.audioBufferSize){
		if(gapp->gamuzaBase.inputAudioCH[_ch].captureAudio){
			return  gapp->gamuzaBase.inputAudioCH[_ch].binsFiltered[_pos];
		}else{
			return 0.0f;
		}
	}else{
		return 0.0f;
	}
}

float gaGetSoundGetSpectrum(int _index, int nBands){
    float *buf = ofSoundGetSpectrum(nBands);
    if(_index < nBands){
        return buf[_index];
    }else{
        return 0.0f;
    }
}

float gaGetAudioInputBuffer(int _ch, int _pos){
    if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioInputChannels > 0 && _pos < gapp->gamuzaBase.audioBufferSize && _ch < gapp->gamuzaBase.audioInputChannels){
        return gapp->gamuzaBase.inputAudioCH[_ch].chRaw[_pos];
    }else{
		return 0.0f;
	}
}

float gaGetAudioOutputBuffer(int _pos){
    if(gapp->gamuzaBase.audioActivated && gapp->gamuzaBase.audioOutputChannels > 0 && _pos < gapp->gamuzaBase.audioBufferSize*gapp->gamuzaBase.audioOutputChannels){
        return gapp->gamuzaBase.outputBufferCopy[_pos];
    }else{
		return 0.0f;
	}
}

//--------------------------------------------------------------
// ARDUINO SECTION
//--------------------------------------------------------------
string gaGetSerialDevName(){
	return gapp->gamuzaBase.serialDevice;
}

float gaGetAArduinoPin(int _pin){
	if(gapp->gamuzaBase.arduinoActivated && _pin >= 0 && _pin <= 5){
		return gapp->gamuzaBase._osc_analogPinValues[_pin];
	}else{
		return 0.0f;
	}
}

int gaGetDArduinoPin(int _pin){
	if(gapp->gamuzaBase.arduinoActivated && _pin >= 2 && _pin <= 13){
		return gapp->gamuzaBase._osc_digitalPinValuesInput[_pin-2];
	}
}

void gaSetDArduinoPin(int _pin,int val){
	if(gapp->gamuzaBase.arduinoActivated && _pin >= 2 && _pin <= 13){
		if(gapp->gamuzaBase.digitalPinModes[_pin-2] == ARD_OUTPUT){
			if(val > 1){
				val = 1;
			}
			gapp->gamuzaBase.digitalPinValuesOutput[_pin-2] = val;
			gapp->gamuzaBase.arduino.sendDigital(_pin, gapp->gamuzaBase.digitalPinValuesOutput[_pin-2]);
		}else  if(gapp->gamuzaBase.digitalPinModes[_pin-2] == ARD_PWM){
			gapp->gamuzaBase.digitalPinValuesOutput[_pin-2] = val;
			gapp->gamuzaBase.arduino.sendPwm(_pin, gapp->gamuzaBase.digitalPinValuesOutput[_pin-2]);
		}
	}
}

#endif
