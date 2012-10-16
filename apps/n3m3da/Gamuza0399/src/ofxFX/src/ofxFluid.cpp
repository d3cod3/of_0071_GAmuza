//
//  ofxFluid.cpp
//  GPU fluid
//
//  Created by Patricio González Vivo on 9/29/11.
//  Copyright 2011 http://PatricioGonzalezVivo.com All rights reserved.
//

#include "ofxFluid.h"

ofxFluid::ofxFluid()
{
    string fragmentAdvectShader = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable \n \
    \
    uniform sampler2DRect VelocityTexture;\
    uniform sampler2DRect SourceTexture;\
    uniform sampler2DRect Obstacles;\
    \
    uniform float TimeStep;\
    uniform float Dissipation;\
    \
    void main(){\
    vec2 st = gl_TexCoord[0].st;\
    \
    float solid = texture2DRect(Obstacles, st).r;\
    \
    if (solid > 0.1) {\
    gl_FragColor = vec4(0.0,0.0,0.0,0.0);\
    return;\
    }\
    \
    vec2 u = texture2DRect(VelocityTexture, st).rg;\
    vec2 coord =  st - TimeStep * u;\
    \
    gl_FragColor = Dissipation * texture2DRect(SourceTexture, coord);\
    }";
    advectShader.unload();
    advectShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentAdvectShader);
    advectShader.linkProgram();
    
    string fragmentJacobiShader = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable \n \
    \
    uniform sampler2DRect Pressure;\
    uniform sampler2DRect Divergence;\
    uniform sampler2DRect Obstacles;\
    \
    uniform float Alpha;\
    uniform float InverseBeta;\
    \
    void main() {\
    vec2 st = gl_TexCoord[0].st;\
    \
    vec4 pN = texture2DRect(Pressure, st + vec2(0.0, 1.0));\
    vec4 pS = texture2DRect(Pressure, st + vec2(0.0, -1.0));\
    vec4 pE = texture2DRect(Pressure, st + vec2(1.0, 0.0)); \
    vec4 pW = texture2DRect(Pressure, st + vec2(-1.0, 0.0));\
    vec4 pC = texture2DRect(Pressure, st);\
    \
    vec3 oN = texture2DRect(Obstacles, st + vec2(0.0, 1.0)).rgb;\
    vec3 oS = texture2DRect(Obstacles, st + vec2(0.0, -1.0)).rgb;\
    vec3 oE = texture2DRect(Obstacles, st + vec2(1.0, 0.0)).rgb;\
    vec3 oW = texture2DRect(Obstacles, st + vec2(-1.0, 0.0)).rgb;\
    \
    if (oN.x > 0.1) pN = pC;\
    if (oS.x > 0.1) pS = pC;\
    if (oE.x > 0.1) pE = pC;\
    if (oW.x > 0.1) pW = pC;\
    \
    vec4 bC = texture2DRect(Divergence, st );\
    gl_FragColor = (pW + pE + pS + pN + Alpha * bC) * InverseBeta;\
    }";
    jacobiShader.unload();
    jacobiShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentJacobiShader);
    jacobiShader.linkProgram();
    
    string fragmentSubtractGradientShader = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable \n \
    \
    uniform sampler2DRect Velocity;\
    uniform sampler2DRect Pressure;\
    uniform sampler2DRect Obstacles;\
    \
    uniform float GradientScale;\
    \
    void main(){\
    vec2 st = gl_TexCoord[0].st;\
    \
    vec3 oC = texture2DRect(Obstacles, st ).rgb;\
    if (oC.x > 0.1) {\
    gl_FragColor.gb = oC.yz;\
    return;\
    }\
    \
    float pN = texture2DRect(Pressure, st + vec2(0.0, 1.0)).r;\
    float pS = texture2DRect(Pressure, st + vec2(0.0, -1.0)).r;\
    float pE = texture2DRect(Pressure, st + vec2(1.0, 0.0)).r;\
    float pW = texture2DRect(Pressure, st + vec2(-1.0, 0.0)).r;\
    float pC = texture2DRect(Pressure, st).r;\
    \
    vec3 oN = texture2DRect(Obstacles, st + vec2(0.0, 1.0)).rgb;\
    vec3 oS = texture2DRect(Obstacles, st + vec2(0.0, -1.0)).rgb;\
    vec3 oE = texture2DRect(Obstacles, st + vec2(1.0, 0.0)).rgb;\
    vec3 oW = texture2DRect(Obstacles, st + vec2(-1.0, 0.0)).rgb;\
    \
    vec2 obstV = vec2(0.0,0.0);\
    vec2 vMask = vec2(1.0,1.0);\
    \
    if (oN.x > 0.1) { pN = pC; obstV.y = oN.z; vMask.y = 0.0; }\
    if (oS.x > 0.1) { pS = pC; obstV.y = oS.z; vMask.y = 0.0; }\
    if (oE.x > 0.1) { pE = pC; obstV.x = oE.y; vMask.x = 0.0; }\
    if (oW.x > 0.1) { pW = pC; obstV.x = oW.y; vMask.x = 0.0; }\
    \
    vec2 oldV = texture2DRect(Velocity, st).rg;\
    vec2 grad = vec2(pE - pW, pN - pS) * GradientScale;\
    vec2 newV = oldV - grad;\
    \
    gl_FragColor.rg = (vMask * newV) + obstV;\
    }";
    subtractGradientShader.unload();
    subtractGradientShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentSubtractGradientShader);
    subtractGradientShader.linkProgram();
    
    string fragmentComputeDivergenceShader = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable \n \
    \
    uniform sampler2DRect Velocity;\
    uniform sampler2DRect Obstacles;\
    uniform float HalfInverseCellSize;\
    \
    void main(){\
    vec2 st = gl_TexCoord[0].st;\
    \
    vec2 vN = texture2DRect(Velocity, st + vec2(0.0,1.0)).rg;\
    vec2 vS = texture2DRect(Velocity, st + vec2(0.0,-1.0)).rg;\
    vec2 vE = texture2DRect(Velocity, st + vec2(1.0,0.0)).rg;\
    vec2 vW = texture2DRect(Velocity, st + vec2(-1.0,0.0)).rg;\
    \
    vec3 oN = texture2DRect(Obstacles, st + vec2(0.0,1.0)).rgb;\
    vec3 oS = texture2DRect(Obstacles, st + vec2(0.0,-1.0)).rgb;\
    vec3 oE = texture2DRect(Obstacles, st + vec2(1.0,0.0)).rgb;\
    vec3 oW = texture2DRect(Obstacles, st + vec2(-1.0,0.0)).rgb;\
    \
    if (oN.x > 0.1) vN = oN.yz;\
    if (oS.x > 0.1) vS = oS.yz;\
    if (oE.x > 0.1) vE = oE.yz;\
    if (oW.x > 0.1) vW = oW.yz;\
    \
    gl_FragColor.r = HalfInverseCellSize * (vE.x - vW.x + vN.y - vS.y);\
    }";
    computeDivergenceShader.unload();
    computeDivergenceShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentComputeDivergenceShader);
    computeDivergenceShader.linkProgram();
    
    string fragmentApplyImpulseShader = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable \n \
    \
    uniform vec2    Point;\
    uniform float   Radius;\
    uniform vec3    Value;\
    \
    void main(){\
    float d = distance(Point, gl_TexCoord[0].st);\
    if (d < Radius) {\
    float a = (Radius - d) * 0.5;\
    a = min(a, 1.0);\
    gl_FragColor = vec4(Value, a);\
    } else {\
    gl_FragColor = vec4(0);\
    }\
    }";
    applyImpulseShader.unload();
    applyImpulseShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentApplyImpulseShader);
    applyImpulseShader.linkProgram();
    
    string fragmentApplyBuoyancyShader = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable \n \
    \
    uniform sampler2DRect Velocity;\
    uniform sampler2DRect Temperature;\
    uniform sampler2DRect Density;\
    \
    uniform float AmbientTemperature;\
    uniform float TimeStep;\
    uniform float Sigma;\
    uniform float Kappa;\
    \
    uniform vec2  Gravity;\
    \
    void main(){\
    vec2 st = gl_TexCoord[0].st;\
    \
    float T = texture2DRect(Temperature, st).r;\
    vec2 V = texture2DRect(Velocity, st).rg;\
    \
    gl_FragColor.rg = V;\
    \
    if (T > AmbientTemperature) {\
    float D = texture2DRect(Density, st).r;\
    gl_FragColor.rg += (TimeStep * (T - AmbientTemperature) * Sigma - D * Kappa ) * Gravity;\
    }\
    }";
    applyBuoyancyShader.unload();
    applyBuoyancyShader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragmentApplyBuoyancyShader);
    applyBuoyancyShader.linkProgram();
    
    cellSize            = 1.25f; 
    gradientScale       = 1.00f / cellSize;
    ambientTemperature  = 0.0f;
    numJacobiIterations = 40;
    timeStep            = 0.125f;
    smokeBuoyancy       = 1.0f;
    smokeWeight         = 0.05f;
    
    gForce.set(0,-0.98);
}

void ofxFluid::allocate(int _width, int _height, float _scale){
    width = _width; 
    height = _height; 
    scale = _scale;
    
    gridWidth = width * scale;
    gridHeight = height * scale;
    
    cout << "- fluid system at " << scale << " scale "<< endl;
    
    velocityBuffer.allocate(gridWidth,gridHeight,GL_RGB32F,0.9f);
    densityBuffer.allocate(gridWidth,gridHeight,GL_RGB32F,0.999f);
    temperatureBuffer.allocate(gridWidth,gridHeight,GL_RGB32F,0.99f);
    pressureBuffer.allocate(gridWidth,gridHeight,GL_RGB32F,0.9f);
    
    initFbo(divergenceFbo, gridWidth, gridHeight, GL_RGB16F);
    initFbo(obstaclesFbo, gridWidth, gridHeight, GL_RGB);
    initFbo(hiresObstaclesFbo, width, height, GL_RGB);
    
    temperatureBuffer.src->begin();
    ofClear( ambientTemperature );
    temperatureBuffer.src->end();
}

void ofxFluid::begin()
{
    hiresObstaclesFbo.begin();
}

void ofxFluid::end()
{
    hiresObstaclesFbo.end();
    obstaclesFbo.begin();
    hiresObstaclesFbo.draw(0,0,gridWidth,gridHeight);
    obstaclesFbo.end();
    update();
}

void ofxFluid::addTemporalForce(ofVec2f _pos, ofVec2f _vel, ofColor _col, float _rad, float _temp, float _den)
{
    punctualForce f;
    
    f.pos = _pos * scale;
    f.vel = _vel;
    f.color.set(_col.r,_col.g,_col.b);
    f.rad = _rad;
    f.temp = _temp;
    f.den = _den;

    temporalForces.push_back(f);
}

void ofxFluid::addConstantForce(ofVec2f _pos, ofVec2f _vel, ofColor _col, float _rad, float _temp, float _den)
{
    punctualForce f;
    
    f.pos = _pos * scale;
    f.vel = _vel;
    f.color.set(_col.r,_col.g,_col.b);
    f.rad = _rad;
    f.temp = _temp;
    f.den = _den;
    
    constantForces.push_back(f);
}

void ofxFluid::update()
{
    advect(velocityBuffer); 
    velocityBuffer.swap();
    
    advect(temperatureBuffer); 
    temperatureBuffer.swap();
    
    advect(densityBuffer); 
    densityBuffer.swap();
    
    applyBuoyancy();
    velocityBuffer.swap();
    
    if ( temporalForces.size() != 0){
        for(int i = 0; i < temporalForces.size(); i++){
            applyImpulse(temperatureBuffer, temporalForces[i].pos, temporalForces[i].temp, temporalForces[i].rad);
            if (temporalForces[i].color.length() != 0)
                applyImpulse(densityBuffer, temporalForces[i].pos, temporalForces[i].color * temporalForces[i].den, temporalForces[i].rad);
            if (temporalForces[i].vel.length() != 0)
                applyImpulse(velocityBuffer , temporalForces[i].pos, temporalForces[i].vel, temporalForces[i].rad);
        }
        temporalForces.clear();
    }
    
    if ( constantForces.size() != 0)
        for(int i = 0; i < constantForces.size(); i++){
            applyImpulse(temperatureBuffer, constantForces[i].pos, constantForces[i].temp, constantForces[i].rad);
            if (constantForces[i].color.length() != 0)
                applyImpulse(densityBuffer, constantForces[i].pos, constantForces[i].color * constantForces[i].den, constantForces[i].rad);
            if (constantForces[i].vel.length() != 0)
                applyImpulse(velocityBuffer , constantForces[i].pos, constantForces[i].vel, constantForces[i].rad);
        }
    
    computeDivergence();
    pressureBuffer.src->begin();
    ofClear(0);
    pressureBuffer.src->end();
    
    for (int i = 0; i < numJacobiIterations; i++) {
        jacobi();
        pressureBuffer.swap();
    }
    
    subtractGradient();
    velocityBuffer.swap();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofDisableBlendMode();
}

void ofxFluid::draw(int x, int y)
{
    glEnable(GL_BLEND);
    ofSetColor(255);
    densityBuffer.src->draw(x,y,width,height);
    hiresObstaclesFbo.draw(x,y,width,height);
    glDisable(GL_BLEND);
}

void ofxFluid::setTextureToBuffer(ofTexture & _tex, swapBuffer & _buffer){
    ofPushMatrix();
    ofScale(scale, scale);
    for(int i = 0; i < 2; i++){
        //_buffer.FBOs[i].begin();
        _buffer[i].begin();
        ofSetColor(255);
        _tex.draw(gridWidth*0.5-_tex.getWidth()*0.5 * scale,
                  gridHeight*0.5-_tex.getHeight()*0.5 * scale, 
                  _tex.getWidth()*scale,
                  _tex.getHeight()*scale);
        _buffer[i].end();
    }
    ofPopMatrix();
    
    update();
}

void ofxFluid::advect(swapBuffer& _buffer)
{
    _buffer.dst->begin();
    advectShader.begin();
    advectShader.setUniform1f("TimeStep", timeStep);
    advectShader.setUniform1f("Dissipation", _buffer.diss);
    advectShader.setUniformTexture("VelocityTexture", velocityBuffer.src->getTextureReference(), 0);
    advectShader.setUniformTexture("SourceTexture", _buffer.src->getTextureReference(), 1);
    advectShader.setUniformTexture("Obstacles", obstaclesFbo.getTextureReference(), 2);
    
    renderFrame(gridWidth,gridHeight);
    
    advectShader.end();
    _buffer.dst->end();
}

void ofxFluid::jacobi()
{
    pressureBuffer.dst->begin();
    jacobiShader.begin();
    jacobiShader.setUniform1f("Alpha", -cellSize * cellSize);
    jacobiShader.setUniform1f("InverseBeta", 0.25f);
    jacobiShader.setUniformTexture("Pressure", pressureBuffer.src->getTextureReference(), 0);
    jacobiShader.setUniformTexture("Divergence", divergenceFbo.getTextureReference(), 1);
    jacobiShader.setUniformTexture("Obstacles", obstaclesFbo.getTextureReference(), 2);
    
    renderFrame(gridWidth,gridHeight);
    
    jacobiShader.end();
    pressureBuffer.dst->end();
}

void ofxFluid::subtractGradient()
{
    velocityBuffer.dst->begin();
    subtractGradientShader.begin();
    subtractGradientShader.setUniform1f("GradientScale", gradientScale);
    
    subtractGradientShader.setUniformTexture("Velocity", velocityBuffer.src->getTextureReference(), 0);
    subtractGradientShader.setUniformTexture("Pressure", pressureBuffer.src->getTextureReference(), 1);
    subtractGradientShader.setUniformTexture("Obstacles", obstaclesFbo.getTextureReference(), 2);
    
    renderFrame(gridWidth,gridHeight);
    
    subtractGradientShader.end();
    velocityBuffer.dst->end();
    
    ofDisableBlendMode();
}

void ofxFluid::computeDivergence()
{
    divergenceFbo.begin();
    computeDivergenceShader.begin();
    computeDivergenceShader.setUniform1f("HalfInverseCellSize", 0.5f / cellSize);
    computeDivergenceShader.setUniformTexture("Velocity", velocityBuffer.src->getTextureReference(), 0);
    computeDivergenceShader.setUniformTexture("Obstacles", obstaclesFbo.getTextureReference(), 1);
    
    renderFrame(gridWidth,gridHeight);

    computeDivergenceShader.end();
    divergenceFbo.end();
}

void ofxFluid::applyImpulse(swapBuffer& _buffer, ofVec2f _force, ofVec3f _value, float _radio)
{
    glEnable(GL_BLEND);
    _buffer.src->begin();
    applyImpulseShader.begin();
    
    applyImpulseShader.setUniform2f("Point", (float)_force.x, (float)_force.y);
    applyImpulseShader.setUniform1f("Radius", (float) _radio );
    applyImpulseShader.setUniform3f("Value", (float)_value.x, (float)_value.y, (float)_value.z);
    
    renderFrame(gridWidth,gridHeight);
    
    applyImpulseShader.end();
    _buffer.src->end();
    glDisable(GL_BLEND);
}

void ofxFluid::applyBuoyancy()
{
    velocityBuffer.dst->begin();
    applyBuoyancyShader.begin();
    applyBuoyancyShader.setUniform1f("AmbientTemperature", ambientTemperature );
    applyBuoyancyShader.setUniform1f("TimeStep", timeStep );
    applyBuoyancyShader.setUniform1f("Sigma", smokeBuoyancy );
    applyBuoyancyShader.setUniform1f("Kappa", smokeWeight );
    
    applyBuoyancyShader.setUniform2f("Gravity", (float)gForce.x, (float)gForce.y );
    
    applyBuoyancyShader.setUniformTexture("Velocity", velocityBuffer.src->getTextureReference(), 0);
    applyBuoyancyShader.setUniformTexture("Temperature", temperatureBuffer.src->getTextureReference(), 1);
    applyBuoyancyShader.setUniformTexture("Density", densityBuffer.src->getTextureReference(), 2);
    
    renderFrame(gridWidth,gridHeight);
    
    applyBuoyancyShader.end();
    velocityBuffer.dst->end();
}