//
//  ofxFluid.h
//  GPU fluid
//
//  Created by Patricio González Vivo on 9/29/11.
//  Copyright 2011 http://PatricioGonzalezVivo.com All rights reserved.
//
//  Created ussing:
//
//    - Mark Harris article from GPU Gems 1
//      http://http.developer.nvidia.com/GPUGems/gpugems_ch38.html
//
//    - Phil Rideout
//      http://prideout.net/blog/?p=58

#ifndef OFXFLUID
#define OFXFLUID

#include "ofMain.h"
#include "ofxFXObject.h"

typedef struct  {
    ofVec3f color;
    ofVec2f pos;
    ofVec2f vel;
    float   rad;
    float   temp;
    float   den;
} punctualForce;

class ofxFluid : public ofxFXObject {
public:
    ofxFluid();
    
    void allocate(int _width, int _height, float _scale);
    
    ofxFluid&   setDensity(ofTexture & _tex){setTextureToBuffer(_tex, densityBuffer); return * this; };
    ofxFluid&   setVelocity(ofTexture & _tex){setTextureToBuffer(_tex, velocityBuffer); return * this; };
    ofxFluid&   setTemperature(ofTexture & _tex){setTextureToBuffer(_tex, temperatureBuffer); return * this; };
    ofxFluid&   setGravity(ofVec2f _force){ gForce = _force; return * this;};
    ofxFluid&   setDensityDissipation(float _diss){densityBuffer.diss = _diss; return * this;};
    ofxFluid&   setVelocityDissipation(float _diss){velocityBuffer.diss = _diss; return * this;};
    ofxFluid&   setTemperatureDissipation(float _diss){temperatureBuffer.diss = _diss; return * this;};
    
    void    addTemporalForce(ofVec2f _pos, ofVec2f _dir, ofColor _col, float _rad = 1.0f, float _temp = 10.f, float _den = 1.f );
    void    addConstantForce(ofVec2f _pos, ofVec2f _dir, ofColor _col, float _rad = 1.0f, float _temp = 10.f, float _den = 1.f );
    
    // FBO for obstables
    void    begin();
    void    end();
    
    void    update();
    void    draw(int x = 0, int y = 0);
    
private:
    void    setTextureToBuffer(ofTexture & _tex, swapBuffer & _buffer);
    
    void    advect(swapBuffer& buffer);
    void    jacobi();
    void    subtractGradient();
    void    computeDivergence();
    
    void    applyImpulse(swapBuffer& _buffer, ofVec2f _force, ofVec3f _value, float _radio = 3.f);
    void    applyBuoyancy();

    ofShader advectShader;
    ofShader jacobiShader;
    ofShader subtractGradientShader;
    ofShader computeDivergenceShader;
    ofShader applyImpulseShader;
    ofShader applyBuoyancyShader;
    
    swapBuffer  velocityBuffer;
    swapBuffer  densityBuffer;
    swapBuffer  temperatureBuffer;
    swapBuffer  pressureBuffer;
    
    ofFbo   divergenceFbo;
    ofFbo   obstaclesFbo;
    ofFbo   hiresObstaclesFbo;
    
    vector<punctualForce> constantForces;
    vector<punctualForce> temporalForces;
    ofVec2f gForce;
    
    float   smokeBuoyancy;
    float   smokeWeight;
    float   gradientScale;
    float   ambientTemperature;
    
    float   width,height;
    float   gridWidth,gridHeight;
    float   cellSize;
    float   timeStep;
    float   scale;
    
    int     numJacobiIterations;
};
#endif