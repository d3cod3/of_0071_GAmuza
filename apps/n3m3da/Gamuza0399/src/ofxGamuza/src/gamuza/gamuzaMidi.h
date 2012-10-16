#ifndef _GAMUZAMIDI
#define _GAMUZAMIDI

#include "gamuzaConstants.h"

//////////////////////////////////////////////
// MIDI vars

//////////////////////////////////////////////

//--------------------------------------------------------------
void gamuzaMain::setupMidi(){
	midiIn.listPorts();
	midiIn.openPort(midiPortNumber);
	midiIn.addListener(this);
}

//--------------------------------------------------------------
void gamuzaMain::newMidiMessage(ofxMidiEventArgs& eventArgs) {
    midi_valueOne   = eventArgs.byteOne;
    midi_valueTwo   = eventArgs.byteTwo;
    midi_id         = eventArgs.channel;
    midi_port       = eventArgs.port;
    midi_timestamp  = eventArgs.timestamp;
    
    bool exist = false;
    
    for(int i=0; i<midiMapping.size();i++){
        if(midiMapping[i].x == midi_id && midiMapping[i].y == midi_valueOne){
            exist = true;
            break;
        }
    }
    
    if(exist){
        for(int i=0; i<midiMapping.size();i++){
            if(midiMapping[i].x == midi_id && midiMapping[i].y == midi_valueOne){
                midiMapping[i].z = midi_valueTwo;
                break;
            }
        }
    }else{
        ofVec3f _temp;
        _temp.set(midi_id,midi_valueOne,midi_valueTwo);
        midiMapping.push_back(_temp);
    }
    
}

#endif
