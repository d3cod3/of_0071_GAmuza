#ifndef _GAMUZASETTINGSPANEL
#define _GAMUZASETTINGSPANEL

#include "gamuzaConstants.h"

#include "RtAudio.h"

//--------------------------------------------------------------
void gamuzaMain::setupSettingPanel(){
    
    glGetIntegerv(GL_MAX_SAMPLES, &_fboMaxSamples);
    
    setupSettingStrings();
    
    retrieveHardwaredata();
}

//--------------------------------------------------------------
void gamuzaMain::retrieveHardwaredata(){
    //////////////////////////////////////////////
    // retrieving midi devices info
    listMidiDevices();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // retrieving audio devices info
    listAudioDevices();
    //////////////////////////////////////////////
    
    //////////////////////////////////////////////
    // retrieving serial devices info
    listSerialDevices();
    //////////////////////////////////////////////
    
    logger.log(99, " -----------------------");
	logger.log(99, " SERIAL DEVICES:");
	logger.log(99, " __________________________");
	logger.log(99, " -----------------------");
    
	logger.log(99, " -----------------------");
	logger.log(99, " MAX_FBO_NUM_SAMPLES: %i", _fboMaxSamples);
	logger.log(99, " __________________________");
	logger.log(99, " -----------------------");
}

//--------------------------------------------------------------
void gamuzaMain::drawSettingPanel(){
    ////////////////////////////////////
	// OSC Text Field Input
    if(!gui.minimize){
        oscIPField.draw(462,224+110);
        oscPortField.draw(462,260+110);
        oscServerPortField.draw(462,296+110);
    }
    ////////////////////////////////////
}

//--------------------------------------------------------------
void gamuzaMain::setupSettingStrings(){
    // vector<string> of screenSizesMain list
    _screenSizesMain.push_back("1280x800 (16:10)");
    _screenSizesMain.push_back("1280x960 (4:3)");
	_screenSizesMain.push_back("1280x1024 (5:4)");
	_screenSizesMain.push_back("1366x768 (16:9)");
	_screenSizesMain.push_back("1440x900 (16:10)");
	_screenSizesMain.push_back("1600x1200 (4:3)");
	_screenSizesMain.push_back("1680x1050 (16:10)");
	_screenSizesMain.push_back("1920x1080 (16:9)");
	// vector<string> of screenSizesProj list
	_screenSizesProj.push_back("640x480 (4:3)");
	_screenSizesProj.push_back("720x400 (9:5)");
	_screenSizesProj.push_back("800x600 (4:3)");
	_screenSizesProj.push_back("832x624 (4:3)");
	_screenSizesProj.push_back("1024x768 (4:3)");
	_screenSizesProj.push_back("1152x864 (4:3)");
    _screenSizesProj.push_back("1280x720 (16:9)");
	_screenSizesProj.push_back("1280x800 (16:10)");
	_screenSizesProj.push_back("1280x960 (4:3)");
	_screenSizesProj.push_back("1280x1024 (5:4)");
	_screenSizesProj.push_back("1440x900 (16:10)");
    _screenSizesProj.push_back("1440x1050 (5:4)");
	_screenSizesProj.push_back("1600x1200 (4:3)");
	_screenSizesProj.push_back("1680x1050 (16:10)");
	_screenSizesProj.push_back("1920x1080 (16:9)");
    _screenSizesProj.push_back("1600x600 (dualhead 800x600)");
    _screenSizesProj.push_back("2048x768 (dualhead 1024x768)");
    _screenSizesProj.push_back("2560x1024 (dualhead 1280x1024)");
    _screenSizesProj.push_back("2400x600 (triplehead 800x600)");
    _screenSizesProj.push_back("3072x768 (triplehead 1024x768)");
    _screenSizesProj.push_back("3840x1024 (triplehead 1280x1024)");
    // vector<string> of oniLedState list
	_oniLedState.push_back("off");
	_oniLedState.push_back("green");
	_oniLedState.push_back("red");
	_oniLedState.push_back("yellow");
	_oniLedState.push_back("blink green");
	_oniLedState.push_back("blink red/yellow");
	// vector<string> of baudRate list
	_baudRateS.push_back("57600");
	_baudRateS.push_back("115200");
	// vector<string> of samplingRates list
	_samplingRates.push_back("44100");
	_samplingRates.push_back("48000");
	_samplingRates.push_back("96000");
	_samplingRates.push_back("192000");
	// vector<string> of bufferSizes list
	_bufferSizes.push_back("32");
	_bufferSizes.push_back("64");
	_bufferSizes.push_back("128");
	_bufferSizes.push_back("256");
	_bufferSizes.push_back("512");
	_bufferSizes.push_back("1024");
	_bufferSizes.push_back("2048");
	_bufferSizes.push_back("4096");
}

//--------------------------------------------------------------
void gamuzaMain::updateSettingScreens(){
    int ms = gui.getValueI("__MAIN_SCREEN_SIZE_SEL");
    int ss = gui.getValueI("__SECONDARY_SCREEN_SIZE_SEL");
    
    switch(ms){
            
        case 0:
            _mainScreenW = 1280;
            _mainScreenH = 800;
            break;
        case 1:
            _mainScreenW = 1280;
            _mainScreenH = 960;
            break;
        case 2:
            _mainScreenW = 1280;
            _mainScreenH = 1024;
            break;
        case 3:
            _mainScreenW = 1366;
            _mainScreenH = 768;
            break;
        case 4:
            _mainScreenW = 1440;
            _mainScreenH = 900;
            break;
        case 5:
            _mainScreenW = 1600;
            _mainScreenH = 1200;
            break;
        case 6:
            _mainScreenW = 1680;
            _mainScreenH = 1050;
            break;
        case 7:
            _mainScreenW = 1920;
            _mainScreenH = 1080;
            break;
            
        default:
            break;
    }
    
    switch(ss){
            
        case 0:
            _secondaryScreenW = 640;
            _secondaryScreenH = 480;
            break;
        case 1:
            _secondaryScreenW = 720;
            _secondaryScreenH = 400;
            break;
        case 2:
            _secondaryScreenW = 800;
            _secondaryScreenH = 600;
            break;
        case 3:
            _secondaryScreenW = 832;
            _secondaryScreenH = 624;
            break;
        case 4:
            _secondaryScreenW = 1024;
            _secondaryScreenH = 768;
            break;
        case 5:
            _secondaryScreenW = 1152;
            _secondaryScreenH = 864;
            break;
        case 6:
            _secondaryScreenW = 1280;
            _secondaryScreenH = 720;
            break;
        case 7:
            _secondaryScreenW = 1280;
            _secondaryScreenH = 800;
            break;
        case 8:
            _secondaryScreenW = 1280;
            _secondaryScreenH = 960;
            break;
        case 9:
            _secondaryScreenW = 1280;
            _secondaryScreenH = 1024;
            break;
        case 10:
            _secondaryScreenW = 1440;
            _secondaryScreenH = 900;
            break;
        case 11:
            _secondaryScreenW = 1440;
            _secondaryScreenH = 1050;
            break;
        case 12:
            _secondaryScreenW = 1600;
            _secondaryScreenH = 1200;
            break;
        case 13:
            _secondaryScreenW = 1680;
            _secondaryScreenH = 1050;
            break;
        case 14:
            _secondaryScreenW = 1920;
            _secondaryScreenH = 1080;
            break;
        case 15:
            _secondaryScreenW = 1600;
            _secondaryScreenH = 600;
            break;
        case 16:
            _secondaryScreenW = 2048;
            _secondaryScreenH = 768;
            break;
        case 17:
            _secondaryScreenW = 2560;
            _secondaryScreenH = 1024;
            break;
        case 18:
            _secondaryScreenW = 2400;
            _secondaryScreenH = 600;
            break;
        case 19:
            _secondaryScreenW = 3072;
            _secondaryScreenH = 768;
            break;
        case 20:
            _secondaryScreenW = 3840;
            _secondaryScreenH = 1024;
            break;
            
        default:
            break;
    }
    
}

//--------------------------------------------------------------
void gamuzaMain::listAudioDevices(){
    ofPtr<RtAudio> audioTemp;
    audioTemp = ofPtr<RtAudio>(new RtAudio());
 	int devices = audioTemp->getDeviceCount();
    
	RtAudio::DeviceInfo info;
    
	for (int i=devices-1; i>= 0; i--) {
        info = audioTemp->getDeviceInfo(i);
        
        logger.log(99, " -----------------------");
        ostringstream srate;
        for(unsigned int j=0;j<info.sampleRates.size();j++){
            srate << info.sampleRates[j] << ",";
        }
        string _sr = srate.str();
        logger.log(99, " sample rates: %s", ofToString(_sr).c_str());
		logger.log(99, " input channels: %s", ofToString(info.inputChannels).c_str());
		logger.log(99, " output channels: %s", ofToString(info.outputChannels).c_str());
		logger.log(99, " device: %i (%s)\n", i,ofToString(info.name).c_str());
        
	}
    
	for (int i=0; i<devices; i++) {
	    info = audioTemp->getDeviceInfo(i);
	    _audioDev.push_back(ofToString(info.name));
		_inputCH.push_back(ofToString(info.inputChannels));
		_outputCH.push_back(ofToString(info.outputChannels));
	}
    
    logger.log(99, " -----------------------");
	logger.log(99, " AUDIO DEVICES: ");
	logger.log(99, " __________________________");
	logger.log(99, " -----------------------");
}

//--------------------------------------------------------------
void gamuzaMain::listMidiDevices(){
    
	for(int i=midiIn.portNames.size()-1;i>=0;i--){
        logger.log(99, " -----------------------");
        logger.log(99, " device: %i (%s)", i,ofToString(midiIn.portNames[i]).c_str());
    }
    
    if(midiIn.portNames.size() > 0){
        for(int i=0;i<midiIn.portNames.size();i++){
            _midiDev.push_back(ofToString(midiIn.portNames[i]));
        }
    }else{
        _midiDev.push_back("NO MIDI DEVICE CONNECTED");
    }
    
    logger.log(99, " -----------------------");
	logger.log(99, " MIDI DEVICES: ");
	logger.log(99, " __________________________");
	logger.log(99, " -----------------------");
}

//--------------------------------------------------------------
void gamuzaMain::listSerialDevices(){
    char temp[128];
    
    _serial.listDevices();
	_deviceList = _serial.getDeviceList();
    
    for(int k = 0; k < (int)_deviceList.size(); k++){
		logger.log(99, " /dev/%s", _deviceList[k].getDeviceName().c_str());
	}
	for(int k = (int)_deviceList.size()-1; k >= 0; k--){
	    sprintf(temp,"/dev/%s",_deviceList[k].getDeviceName().c_str());
        _serialDev.push_back(temp);
	}
}

//--------------------------------------------------------------
void gamuzaMain::saveGamuzaSettings(){
    setting_data.loadFile(GAMUZA_SETTINGS);
    
    setting_data.setValue("openni_activated", _openniModule);
    setting_data.setValue("tracking_activated", _trackingModule);
    setting_data.setValue("audio_activated", _audioModule);
    setting_data.setValue("arduino_activated", _arduinoModule);
    setting_data.setValue("ms_width", _mainScreenW);
    setting_data.setValue("ms_height", _mainScreenH);
    setting_data.setValue("ps_width", _secondaryScreenW);
    setting_data.setValue("ps_height", _secondaryScreenH);
    setting_data.setValue("auto_pilot", _autoPilot);
    setting_data.setValue("autoload_script", _autoloadScript);
    setting_data.setValue("script_file", _scriptFile);
    
    //setting_data.setValue("fbo_num_samples", _fboMaxSamples);
    setting_data.setValue("fbo_num_samples", 1);
    setting_data.setValue("grid_res", _mappingGridRes);
    
    setting_data.setValue("video_test", _loadVideoTest);
    setting_data.setValue("video_test_file", _videoTestFile);
    setting_data.setValue("haar_finder_file", _haarCascadeFile);
    
    setting_data.setValue("use_infrared", _useInfrared);
    setting_data.setValue("led_state", _ledState);
    setting_data.setValue("audio_Dev_ID", _audioDevice);
    setting_data.setValue("midi_port", _midiDevice);
	setting_data.setValue("input_ch", _inputChannels);
	setting_data.setValue("output_ch", _outputChannels);
    setting_data.setValue("sampling_rate", _samplingRate);
    setting_data.setValue("buffer_size", _bufferSize);
    setting_data.setValue("baud_rate", _baudRate);
    setting_data.setValue("serial_device_name", _serialPort);
    setting_data.setValue("host_port", oscPortField.text);
    setting_data.setValue("host_ip", oscIPField.text);
    setting_data.setValue("server_port", oscServerPortField.text);
    
    setting_data.saveFile(GAMUZA_SETTINGS);
    
    receiving_port_editor.loadFile(GAMUZA_RECEIVING_PORT_XML);
    receiving_port_editor.setValue("server_port", oscServerPortField.text);
    receiving_port_editor.saveFile(GAMUZA_RECEIVING_PORT_XML);
    
}

#endif