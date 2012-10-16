/*
 * Extending ofxLuaWrapper for GAmuza 0.3 | ALMOST ENTIRE OF 007 Wrapper + GAmuza Wrapper + SOME FUNCTIONS FROM OPENGL 2.1 Wrapper
 *
 * ORIGINAL FILE FROM:
 * Dan Wilcox <danomatika@gmail.com>
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
#pragma once

#include "ofMain.h"
#include "ofxLua.h"

#include "gamuzaGetters.h"
#include "gamuzaIncludes.h"

class ofGamuzaWrapper{

	public:

	/// static function called when binding
	static void bind(ofxLua& lua) {

		using namespace luabind;

        //////////////////////////////////////////////////////////////
		///////////////////////////////
		/// OpenFrameworks 007 api wrapper
		///
		module(lua, "of")
		[

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section arduino [ofArduino]

         // NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM, MANAGED FROM GUI (arduino module)


         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section 3D [ofNode, ofEasyCam, ofMesh, ofCamera]

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofNode

         class_<ofNode>("node")
		 .def(constructor<>())
		 .def("setParent", (void(ofNode::*)(ofNode&)) &ofNode::setParent)
         .def("clearParent", (void(ofNode::*)(void)) &ofNode::clearParent)
         .def("getParent", (ofNode(ofNode::*)(void)) &ofNode::getParent)
         .def("getPosition", (ofVec3f(ofNode::*)(void)) &ofNode::getPosition)
         .def("getX", (float(ofNode::*)(void)) &ofNode::getX)
         .def("getY", (float(ofNode::*)(void)) &ofNode::getY)
         .def("getZ", (float(ofNode::*)(void)) &ofNode::getZ)
         .def("getXAxis", (ofVec3f(ofNode::*)(void)) &ofNode::getXAxis)
         .def("getYAxis", (ofVec3f(ofNode::*)(void)) &ofNode::getYAxis)
         .def("getZAxis", (ofVec3f(ofNode::*)(void)) &ofNode::getZAxis)
         .def("getSideDir", (ofVec3f(ofNode::*)(void)) &ofNode::getSideDir)
         .def("getLookAtDir", (ofVec3f(ofNode::*)(void)) &ofNode::getLookAtDir)
         .def("getUpDir", (ofVec3f(ofNode::*)(void)) &ofNode::getUpDir)
         .def("getPitch", (float(ofNode::*)(void)) &ofNode::getPitch)
         .def("getHeading", (float(ofNode::*)(void)) &ofNode::getHeading)
         .def("getRoll", (float(ofNode::*)(void)) &ofNode::getRoll)
         .def("getOrientationQuat", (ofQuaternion(ofNode::*)(void)) &ofNode::getOrientationQuat)
         .def("getOrientationEuler", (ofVec3f(ofNode::*)(void)) &ofNode::getOrientationEuler)
         .def("getScale", (ofVec3f(ofNode::*)(void)) &ofNode::getScale)
         .def("getLocalTransformMatrix", (ofMatrix4x4(ofNode::*)(void)) &ofNode::getLocalTransformMatrix)
         .def("getGlobalTransformMatrix", (ofMatrix4x4(ofNode::*)(void)) &ofNode::getGlobalTransformMatrix)
         .def("getGlobalPosition", (ofVec3f(ofNode::*)(void)) &ofNode::getGlobalPosition)
         .def("getGlobalOrientation", (ofQuaternion(ofNode::*)(void)) &ofNode::getGlobalOrientation)
         .def("setTransformMatrix", (void(ofNode::*)(const ofMatrix4x4&)) &ofNode::setTransformMatrix)
         .def("setPosition", (void(ofNode::*)(float,float,float)) &ofNode::setPosition)
         .def("setPosition", (void(ofNode::*)(const ofVec3f&)) &ofNode::setPosition)
         .def("setGlobalPosition", (void(ofNode::*)(float,float,float)) &ofNode::setGlobalPosition)
         .def("setGlobalPosition", (void(ofNode::*)(const ofVec3f&)) &ofNode::setGlobalPosition)
         .def("setOrientation", (void(ofNode::*)(const ofQuaternion&)) &ofNode::setOrientation)
         .def("setOrientation", (void(ofNode::*)(const ofVec3f&)) &ofNode::setOrientation)
         .def("setGlobalOrientation", (void(ofNode::*)(const ofQuaternion&)) &ofNode::setGlobalOrientation)
         .def("setScale", (void(ofNode::*)(float,float,float)) &ofNode::setScale)
         .def("setScale", (void(ofNode::*)(const ofVec3f&)) &ofNode::setScale)
         .def("move", (void(ofNode::*)(float,float,float)) &ofNode::move)
         .def("move", (void(ofNode::*)(const ofVec3f&)) &ofNode::move)
         .def("truck", (void(ofNode::*)(float)) &ofNode::truck)
         .def("boom", (void(ofNode::*)(float)) &ofNode::boom)
         .def("dolly", (void(ofNode::*)(float)) &ofNode::dolly)
         .def("tilt", (void(ofNode::*)(float)) &ofNode::tilt)
         .def("pan", (void(ofNode::*)(float)) &ofNode::pan)
         .def("roll", (void(ofNode::*)(float)) &ofNode::roll)
         .def("rotate", (void(ofNode::*)(const ofQuaternion&)) &ofNode::rotate)
         .def("rotate", (void(ofNode::*)(float,const ofVec3f&)) &ofNode::rotate)
         .def("rotate", (void(ofNode::*)(float,float,float,float)) &ofNode::rotate)
         .def("rotateAround", (void(ofNode::*)(const ofQuaternion&,const ofVec3f&)) &ofNode::rotateAround)
         .def("rotateAround", (void(ofNode::*)(float,const ofVec3f&,const ofVec3f&)) &ofNode::rotateAround)
         .def("lookAt", (void(ofNode::*)(const ofVec3f&,ofVec3f)) &ofNode::lookAt)
         .def("lookAt", (void(ofNode::*)(ofNode&,const ofVec3f&)) &ofNode::lookAt)
         .def("orbit", (void(ofNode::*)(float,float,float,const ofVec3f&)) &ofNode::orbit)
         .def("orbit", (void(ofNode::*)(float,float,float,ofNode&)) &ofNode::orbit)
         .def("transformGL", (void(ofNode::*)(void)) &ofNode::transformGL)
         .def("restoreTransformGL", (void(ofNode::*)(void)) &ofNode::restoreTransformGL)
         .def("resetTransform", (void(ofNode::*)(void)) &ofNode::resetTransform)
         .def("draw", (void(ofNode::*)(void)) &ofNode::draw),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofEasyCam

         class_<ofEasyCam>("easyCam")
		 .def(constructor<>())
         .def("beginCamera", (void(ofEasyCam::*)(ofRectangle)) &ofEasyCam::begin)
         .def("endCamera", (void(ofEasyCam::*)(void)) &ofEasyCam::end)
         .def("reset", (void(ofEasyCam::*)(void)) &ofEasyCam::reset)
         .def("setTarget", (void(ofEasyCam::*)(const ofVec3f&)) &ofEasyCam::setTarget)
         .def("setTarget", (void(ofEasyCam::*)(ofNode&)) &ofEasyCam::setTarget)
         .def("getTarget", (ofNode(ofEasyCam::*)(void)) &ofEasyCam::getTarget)
         .def("setDistance", (void(ofEasyCam::*)(float)) &ofEasyCam::setDistance)
         .def("getDistance", (float(ofEasyCam::*)(void)) &ofEasyCam::getDistance)
         .def("setDrag", (void(ofEasyCam::*)(float)) &ofEasyCam::setDrag)
         .def("getDrag", (float(ofEasyCam::*)(void)) &ofEasyCam::getDrag)
         .def("enableMouseInput", (void(ofEasyCam::*)(void)) &ofEasyCam::enableMouseInput)
         .def("disableMouseInput", (void(ofEasyCam::*)(void)) &ofEasyCam::disableMouseInput)
         .def("getMouseInputEnabled", (bool(ofEasyCam::*)(void)) &ofEasyCam::getMouseInputEnabled),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofMesh

         class_<ofMesh>("mesh")
		 .def(constructor<>())
         .def("setMode", (void(ofMesh::*)(ofPrimitiveMode)) &ofMesh::setMode)
         .def("getMode", (ofPrimitiveMode(ofMesh::*)(void)) &ofMesh::getMode)
         .def("clear", (void(ofMesh::*)(void)) &ofMesh::clear)
         .def("setupIndicesAuto", (void(ofMesh::*)(void)) &ofMesh::setupIndicesAuto)
         .def("getVertex", (ofVec3f(ofMesh::*)(int)) &ofMesh::getVertex)
         //.def("removeVertex", (void(ofMesh::*)(int)) &ofMesh::removeVertex)
         .def("clearVertices", (void(ofMesh::*)(void)) &ofMesh::clearVertices)
         .def("getNormal", (ofVec3f(ofMesh::*)(int)) &ofMesh::getNormal)
         //.def("removeNormal", (void(ofMesh::*)(int)) &ofMesh::removeNormal)
         .def("clearNormals", (void(ofMesh::*)(void)) &ofMesh::clearNormals)
         .def("getColor", (ofFloatColor(ofMesh::*)(int)) &ofMesh::getColor)
         //.def("removeColor", (void(ofMesh::*)(int)) &ofMesh::removeColor)
         .def("clearColors", (void(ofMesh::*)(void)) &ofMesh::clearColors)
         .def("getTexCoord", (ofVec2f(ofMesh::*)(int)) &ofMesh::getTexCoord)
         //.def("removeTexCoord", (void(ofMesh::*)(int)) &ofMesh::removeTexCoord)
         .def("clearTexCoords", (void(ofMesh::*)(void)) &ofMesh::clearTexCoords)
         .def("getIndex", (ofIndexType(ofMesh::*)(int)) &ofMesh::getTexCoord)
         .def("addIndex", (void(ofMesh::*)(ofIndexType)) &ofMesh::addIndex)
         //.def("removeIndex", (void(ofMesh::*)(int)) &ofMesh::removeIndex)
         .def("setIndex", (void(ofMesh::*)(int,ofIndexType)) &ofMesh::setIndex)
         .def("clearIndices", (void(ofMesh::*)(void)) &ofMesh::clearIndices)
         .def("addTriangle", (void(ofMesh::*)(ofIndexType,ofIndexType,ofIndexType)) &ofMesh::addTriangle)
         .def("getNumVertices", (int(ofMesh::*)(void)) &ofMesh::getNumVertices)
         .def("getNumColors", (int(ofMesh::*)(void)) &ofMesh::getNumColors)
         .def("getNumNormals", (int(ofMesh::*)(void)) &ofMesh::getNumNormals)
         .def("getNumTexCoords", (int(ofMesh::*)(void)) &ofMesh::getNumTexCoords)
         .def("getNumIndices", (int(ofMesh::*)(void)) &ofMesh::getNumIndices)
         .def("getVerticesPointer", (ofVec3f*(ofMesh::*)(void)) &ofMesh::getVerticesPointer)
         .def("getColorsPointer", (ofFloatColor*(ofMesh::*)(void)) &ofMesh::getColorsPointer)
         .def("getNormalsPointer", (ofVec3f*(ofMesh::*)(void)) &ofMesh::getNormalsPointer)
         .def("getTexCoordsPointer", (ofVec2f*(ofMesh::*)(void)) &ofMesh::getTexCoordsPointer)
         .def("getIndexPointer", (ofIndexType*(ofMesh::*)(void)) &ofMesh::getIndexPointer)
         //.def("getVertices", (ofVec3f(ofMesh::*)(void)) &ofMesh::getVertices)
         //.def("getColors", (ofFloatColor(ofMesh::*)(void)) &ofMesh::getColors)
         //.def("getNormals", (ofVec3f(ofMesh::*)(void)) &ofMesh::getNormals)
         //.def("getTexCoords", (ofVec2f(ofMesh::*)(void)) &ofMesh::getTexCoords)
         //.def("getIndices", (ofIndexType(ofMesh::*)(void)) &ofMesh::getIndices)
         .def("setName", (void(ofMesh::*)(string)) &ofMesh::setName)
         .def("haveVertsChanged", (bool(ofMesh::*)(void)) &ofMesh::haveVertsChanged)
         .def("haveColorsChanged", (bool(ofMesh::*)(void)) &ofMesh::haveColorsChanged)
         .def("haveNormalsChanged", (bool(ofMesh::*)(void)) &ofMesh::haveNormalsChanged)
         .def("haveTexCoordsChanged", (bool(ofMesh::*)(void)) &ofMesh::haveTexCoordsChanged)
         .def("haveIndicesChanged", (bool(ofMesh::*)(void)) &ofMesh::haveIndicesChanged)
         .def("hasVertices", (bool(ofMesh::*)(void)) &ofMesh::hasVertices)
         .def("hasColors", (bool(ofMesh::*)(void)) &ofMesh::hasColors)
         .def("hasNormals", (bool(ofMesh::*)(void)) &ofMesh::hasNormals)
         .def("hasTexCoords", (bool(ofMesh::*)(void)) &ofMesh::hasTexCoords)
         .def("hasIndices", (bool(ofMesh::*)(void)) &ofMesh::hasIndices)
         .def("drawVertices", (void(ofMesh::*)(void)) &ofMesh::drawVertices)
         .def("drawWireframe", (void(ofMesh::*)(void)) &ofMesh::drawWireframe)
         .def("drawFaces", (void(ofMesh::*)(void)) &ofMesh::drawFaces)
         .def("draw", (void(ofMesh::*)(void)) &ofMesh::draw)
         .def("addVertex", (void(ofMesh::*)(const ofVec3f&)) &ofMesh::addVertex)
         .def("setVertex", (void(ofMesh::*)(int,const ofVec3f&)) &ofMesh::setVertex)
         .def("addNormal", (void(ofMesh::*)(const ofVec3f&)) &ofMesh::addNormal)
         .def("setNormal", (void(ofMesh::*)(int,const ofVec3f&)) &ofMesh::setNormal)
         .def("addColor", (void(ofMesh::*)(const ofFloatColor&)) &ofMesh::addColor)
         .def("setColor", (void(ofMesh::*)(int,const ofFloatColor&)) &ofMesh::setColor)
         .def("addTexCoord", (void(ofMesh::*)(const ofVec2f&)) &ofMesh::addTexCoord)
         .def("setTexCoord", (void(ofMesh::*)(int,const ofVec2f&)) &ofMesh::setTexCoord)
         .def("addIndices", (void(ofMesh::*)(const ofIndexType*,int)) &ofMesh::addIndices),
         //.def("getCentroid", (ofVec3f(ofMesh::*)(void)) &ofMesh::getCentroid)

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofCamera

         class_<ofCamera>("camera")
		 .def(constructor<>())
		 .def("setFov", (void(ofCamera::*)(float)) &ofCamera::setFov)
         .def("setNearClip", (void(ofCamera::*)(float)) &ofCamera::setNearClip)
		 .def("setFarClip", (void(ofCamera::*)(float)) &ofCamera::setFarClip)
         .def("enableOrtho", (void(ofCamera::*)(void)) &ofCamera::enableOrtho)
         .def("disableOrtho", (void(ofCamera::*)(void)) &ofCamera::disableOrtho)
         .def("getOrtho", (bool(ofCamera::*)(void)) &ofCamera::getOrtho)
         .def("getModelViewMatrix", (ofMatrix4x4(ofCamera::*)(void)) &ofCamera::getModelViewMatrix)
         //.def("getFov", (float(ofCamera::*)(void)) &ofCamera::getFov)
         .def("setPosition", (void(ofCamera::*)(float,float,float)) &ofCamera::setPosition)
         .def("setPosition", (void(ofCamera::*)(const ofVec3f&)) &ofCamera::setPosition)
         .def("setScale", (void(ofCamera::*)(float)) &ofCamera::setScale)
         .def("setScale", (void(ofCamera::*)(float,float,float)) &ofCamera::setScale)
         .def("setScale", (void(ofCamera::*)(const ofVec3f&)) &ofCamera::setScale)
         .def("move", (void(ofCamera::*)(float,float,float)) &ofCamera::move)
         .def("move", (void(ofCamera::*)(const ofVec3f&)) &ofCamera::move)
         .def("truck", (void(ofCamera::*)(float)) &ofCamera::truck)
         .def("boom", (void(ofCamera::*)(float)) &ofCamera::boom)
         .def("dolly", (void(ofCamera::*)(float)) &ofCamera::dolly)
         .def("tilt", (void(ofCamera::*)(float)) &ofCamera::tilt)
         .def("pan", (void(ofCamera::*)(float)) &ofCamera::pan)
         .def("roll", (void(ofCamera::*)(float)) &ofCamera::roll)
         .def("rotate", (void(ofCamera::*)(float,const ofVec3f&)) &ofCamera::rotate)
         .def("rotate", (void(ofCamera::*)(float,float,float,float)) &ofCamera::rotate)
         .def("lookAt", (void(ofCamera::*)(const ofVec3f&,ofVec3f)) &ofCamera::lookAt)
         .def("orbit", (void(ofCamera::*)(float,float,float,const ofVec3f&)) &ofCamera::orbit)
         .def("transformGL", (void(ofCamera::*)(void)) &ofCamera::transformGL)
         .def("restoreTransformGL", (void(ofCamera::*)(void)) &ofCamera::restoreTransformGL)
         .def("resetTransform", (void(ofCamera::*)(void)) &ofCamera::resetTransform)
         .def("draw", (void(ofCamera::*)(void)) &ofCamera::draw)
         .def("getImagePlaneDistance", (float(ofCamera::*)(ofRectangle)) &ofCamera::getImagePlaneDistance)
         //.def("cacheMatrices", (void(ofCamera::*)(bool)) &ofCamera::cacheMatrices)

         .def("getProjectionMatrix", (ofMatrix4x4(ofCamera::*)(ofRectangle)) &ofCamera::getProjectionMatrix)
         .def("getModelViewProjectionMatrix", (ofMatrix4x4(ofCamera::*)(ofRectangle)) &ofCamera::getModelViewProjectionMatrix)
         .def("worldToScreen", (ofVec3f(ofCamera::*)(ofVec3f,ofRectangle)) &ofCamera::worldToScreen)
         .def("screenToWorld", (ofVec3f(ofCamera::*)(ofVec3f,ofRectangle)) &ofCamera::screenToWorld)
         .def("worldToCamera", (ofVec3f(ofCamera::*)(ofVec3f,ofRectangle)) &ofCamera::worldToCamera)
         .def("cameraToWorld", (ofVec3f(ofCamera::*)(ofVec3f,ofRectangle)) &ofCamera::cameraToWorld)

         .def("beginCamera", (void(ofCamera::*)(ofRectangle)) &ofCamera::begin)
         .def("endCamera", (void(ofCamera::*)(void)) &ofCamera::end),

         def("drawAxis", (void(*)(float)) &ofDrawAxis),

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section math [ofMath, ofMatrix3x3, ofMatrix4x4, ofQuaternion, ofVec2f, ofVec3f, ofVec4f]

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofMath

         def("seedRandom", (void(*)(void)) &ofSeedRandom),
		 def("seedRandom", (void(*)(int)) &ofSeedRandom),
         def("random", (float(*)(float)) &ofRandom),
		 def("random", (float(*)(float,float)) &ofRandom),
		 def("randomf", (float(*)(void)) &ofRandomf),
		 def("randomuf", (float(*)(void)) &ofRandomuf),
         def("nextPow2", (int(*)(int)) &ofNextPow2),
		 def("normalize", &ofNormalize),
		 def("map", (float(*)(float,float,float,float,float,bool)) &ofMap),
         def("map", &map5),
		 def("clamp", &ofClamp),
		 def("lerp", &ofLerp),
		 def("dist", &ofDist),
		 def("distSquared", &ofDistSquared),
		 def("sign", &ofSign),
		 def("inRange", &ofInRange),
		 def("radToDeg", &ofRadToDeg),
		 def("degToRad", &ofDegToRad),
		 def("lerpDegrees", &ofLerpDegrees),
		 def("lerpRadians", &ofLerpRadians),
		 def("angleDifferenceDegrees", &ofAngleDifferenceDegrees),
		 def("angleDifferenceRadians", &ofAngleDifferenceRadians),
         //def("angleSumRadians", (float(*)(float,float)) &ofAngleSumRadians),
		 def("wrapRadians", &ofWrapRadians),
		 def("wrapDegrees", &ofWrapDegrees),
		 def("noise", (float(*)(float)) &ofNoise),
		 def("noise", (float(*)(float,float)) &ofNoise),
		 def("noise", (float(*)(float,float,float)) &ofNoise),
		 def("noise", (float(*)(float,float,float,float)) &ofNoise),
		 def("signedNoise", (float(*)(float)) &ofSignedNoise),
		 def("signedNoise", (float(*)(float,float)) &ofSignedNoise),
		 def("signedNoise", (float(*)(float,float,float)) &ofSignedNoise),
		 def("signedNoise", (float(*)(float,float,float,float)) &ofSignedNoise),
         def("insidePoly", (bool(*)(float,float,const vector<ofPoint>&)) &ofInsidePoly),
         def("insidePoly", (bool(*)(const ofPoint&,const vector<ofPoint>&)) &ofInsidePoly),
         def("lineSegmentIntersection", (bool(*)(ofPoint,ofPoint,ofPoint,ofPoint,ofPoint)) &ofLineSegmentIntersection),
         def("bezierPoint", (ofPoint(*)(ofPoint,ofPoint,ofPoint,ofPoint,float)) &ofBezierPoint),
         def("curvePoint", (ofPoint(*)(ofPoint,ofPoint,ofPoint,ofPoint,float)) &ofCurvePoint),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofMatrix3x3

         class_<ofMatrix3x3>("matrix3x3")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float,float,float,float,float,float>())
         .def("set", (void(ofMatrix3x3::*)(float,float,float,float,float,float,float,float,float)) &ofMatrix3x3::set)
         .def("transpose", (void(ofMatrix3x3::*)(void)) &ofMatrix3x3::transpose)
         //.def("transpose", (void(ofMatrix3x3::*)(const ofMatrix3x3&)) &ofMatrix3x3::transpose)
         //.def("determinant", (float(ofMatrix3x3::*)(void)) &ofMatrix3x3::determinant)
         .def("determinant", (float(ofMatrix3x3::*)(const ofMatrix3x3&)) &ofMatrix3x3::determinant)
         .def("invert", (void(ofMatrix3x3::*)(void)) &ofMatrix3x3::invert)
         .def("inverse", (ofMatrix3x3(ofMatrix3x3::*)(const ofMatrix3x3&)) &ofMatrix3x3::inverse)
         .def(self + other<const ofMatrix3x3&>())
         .def(self - other<const ofMatrix3x3&>())
         .def(self * other<const ofMatrix3x3&>())
         .def(self + other<float>())
         .def(self - other<float>())
         .def(self * other<float>())
         .def(self / other<float>())
         .def_readonly("a", &ofMatrix3x3::a)
		 .def_readonly("b", &ofMatrix3x3::b)
         .def_readonly("c", &ofMatrix3x3::c)
		 .def_readonly("d", &ofMatrix3x3::d)
         .def_readonly("e", &ofMatrix3x3::e)
		 .def_readonly("f", &ofMatrix3x3::f)
         .def_readonly("g", &ofMatrix3x3::g)
		 .def_readonly("h", &ofMatrix3x3::h)
         .def_readonly("i", &ofMatrix3x3::i),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofMatrix4x4

         class_<ofMatrix4x4>("matrix4x4")
		 .def(constructor<>())
         .def(constructor<const ofMatrix4x4&>())
         .def(constructor<const ofQuaternion&>())
         //.def(constructor<float,float,float,float,float,float,float,float,float,float,float,float,float,float,float,float>())
         .def("getRowAsVec3f", (ofVec3f(ofMatrix4x4::*)(int)) &ofMatrix4x4::getRowAsVec3f)
         .def("getRowAsVec4f", (ofVec4f(ofMatrix4x4::*)(int)) &ofMatrix4x4::getRowAsVec4f)
         .def("isValid", (bool(ofMatrix4x4::*)(void)) &ofMatrix4x4::isValid)
         .def("isNaN", (bool(ofMatrix4x4::*)(void)) &ofMatrix4x4::isNaN)
         .def("set", (void(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::set)
         .def("isIdentity", (bool(ofMatrix4x4::*)(void)) &ofMatrix4x4::isIdentity)
         .def("makeIdentityMatrix", (void(ofMatrix4x4::*)(void)) &ofMatrix4x4::makeIdentityMatrix)
         .def("makeScaleMatrix", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::makeScaleMatrix)
         .def("makeScaleMatrix", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::makeScaleMatrix)
         .def("makeTranslationMatrix", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::makeTranslationMatrix)
         .def("makeTranslationMatrix", (void(ofMatrix4x4::*)(float,float,float)) &ofMatrix4x4::makeTranslationMatrix)
         .def("makeRotationMatrix", (void(ofMatrix4x4::*)(float,const ofVec3f&)) &ofMatrix4x4::makeRotationMatrix)
         .def("makeRotationMatrix", (void(ofMatrix4x4::*)(float,float,float,float)) &ofMatrix4x4::makeRotationMatrix)
         .def("makeRotationMatrix", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::makeRotationMatrix)
         .def("makeRotationMatrix", (void(ofMatrix4x4::*)(float,const ofVec3f&,float,const ofVec3f&,float,const ofVec3f&)) &ofMatrix4x4::makeRotationMatrix)
         .def("makeInvertOf", (bool(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::makeInvertOf)
         .def("makeOrthoNormalOf", (void(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::makeOrthoNormalOf)
         .def("makeFromMultiplicationOf", (void(ofMatrix4x4::*)(const ofMatrix4x4&,const ofMatrix4x4&)) &ofMatrix4x4::makeFromMultiplicationOf)
         .def("getInverse", (void(ofMatrix4x4::*)(void)) &ofMatrix4x4::getInverse)
         .def("makeOrthoMatrix", (void(ofMatrix4x4::*)(double,double,double,double,double,double)) &ofMatrix4x4::makeOrthoMatrix)
         .def("makeOrtho2DMatrix", (void(ofMatrix4x4::*)(double,double,double,double)) &ofMatrix4x4::makeOrtho2DMatrix)
         .def("makeFrustumMatrix", (void(ofMatrix4x4::*)(double,double,double,double,double,double)) &ofMatrix4x4::makeFrustumMatrix)
         .def("makePerspectiveMatrix", (void(ofMatrix4x4::*)(double,double,double,double)) &ofMatrix4x4::makePerspectiveMatrix)
         .def("makeLookAtMatrix", (void(ofMatrix4x4::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofMatrix4x4::makeLookAtMatrix)
         .def("makeLookAtViewMatrix", (void(ofMatrix4x4::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofMatrix4x4::makeLookAtViewMatrix)
         .def("getOrtho", (bool(ofMatrix4x4::*)(double&,double&,double&,double&,double&,double&)) &ofMatrix4x4::getOrtho)
         .def("getFrustum", (bool(ofMatrix4x4::*)(double&,double&,double&,double&,double&,double&)) &ofMatrix4x4::getFrustum)
         .def("getPerspective", (bool(ofMatrix4x4::*)(double&,double&,double&,double&)) &ofMatrix4x4::getPerspective)
         .def("getLookAt", (void(ofMatrix4x4::*)(ofVec3f&,ofVec3f&,ofVec3f&,float)) &ofMatrix4x4::getLookAt)
         .def("decompose", (void(ofMatrix4x4::*)(ofVec3f&,ofQuaternion&,ofVec3f&,ofQuaternion&)) &ofMatrix4x4::decompose)
         //.def("postMult", (ofVec3f(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::postMult)
         //.def("postMult", (ofVec4f(ofMatrix4x4::*)(const ofVec4f&)) &ofMatrix4x4::postMult)
         .def(self * other<const ofVec3f&>())
         .def(self * other<const ofVec4f&>())
         .def(self * other<const ofMatrix4x4&>())
         //.def("preMult", (ofVec3f(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::preMult)
         //.def("preMult", (ofVec4f(ofMatrix4x4::*)(const ofVec4f&)) &ofMatrix4x4::preMult)
         .def("setRotate", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::setRotate)
         .def("setTranslation", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::setTranslation)
         .def("rotate", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::rotate)
         .def("translate", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::translate)
         .def("scale", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::scale)
         .def("glRotate", (void(ofMatrix4x4::*)(const ofQuaternion&)) &ofMatrix4x4::glRotate)
         .def("glTranslate", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::glTranslate)
         .def("glScale", (void(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::glScale)
         .def("getRotate", (ofQuaternion(ofMatrix4x4::*)(void)) &ofMatrix4x4::getRotate)
         .def("getTranslation", (ofVec3f(ofMatrix4x4::*)(void)) &ofMatrix4x4::getTranslation)
         .def("getScale", (ofVec3f(ofMatrix4x4::*)(void)) &ofMatrix4x4::getScale)
         //.def("newIdentityMatrix", (ofMatrix4x4(ofMatrix4x4::*)(void)) &ofMatrix4x4::newIdentityMatrix)
         //.def("newScaleMatrix", (ofMatrix4x4(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::newScaleMatrix)
         //.def("newTranslationMatrix", (ofMatrix4x4(ofMatrix4x4::*)(const ofVec3f&)) &ofMatrix4x4::newTranslationMatrix)
         //.def("newRotationMatrix", (ofMatrix4x4(ofMatrix4x4::*)(const ofVec3f&,const ofVec3f&)) &ofMatrix4x4::newRotationMatrix)
         //.def("newRotationMatrix", (ofMatrix4x4(ofMatrix4x4::*)(float,float,float,float)) &ofMatrix4x4::newRotationMatrix)
         //.def("newRotationMatrix", (ofMatrix4x4(ofMatrix4x4::*)(float,const ofVec3f&)) &ofMatrix4x4::newRotationMatrix)
         //.def("newRotationMatrix", (ofMatrix4x4(ofMatrix4x4::*)(float,const ofVec3f&,float,const ofVec3f&,float,const ofVec3f&)) &ofMatrix4x4::newRotationMatrix)
         //.def("getInverseOf", (ofMatrix4x4(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::getInverseOf)
         //.def("getTransposedOf", (ofMatrix4x4(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::getTransposedOf)
         //.def("getOrthoNormalOf", (ofMatrix4x4(ofMatrix4x4::*)(const ofMatrix4x4&)) &ofMatrix4x4::getOrthoNormalOf)
         //def("newOrthoMatrix", (ofMatrix4x4(ofMatrix4x4::*)(double,double,double,double,double,double)) &ofMatrix4x4::newOrthoMatrix)
         //.def("newOrtho2DMatrix", (ofMatrix4x4(ofMatrix4x4::*)(double,double,double,double)) &ofMatrix4x4::newOrtho2DMatrix)
         //.def("newFrustumMatrix", (ofMatrix4x4(ofMatrix4x4::*)(double,double,double,double,double,double)) &ofMatrix4x4::newFrustumMatrix)
         //.def("newPerspectiveMatrix", (ofMatrix4x4(ofMatrix4x4::*)(double,double,double,double)) &ofMatrix4x4::newPerspectiveMatrix)
         //.def("newLookAtMatrix", (ofMatrix4x4(ofMatrix4x4::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofMatrix4x4::newLookAtMatrix)
         //.def("transform3x3", (ofVec3f(ofMatrix4x4::*)(const ofVec3f&,const ofMatrix4x4&)) &ofMatrix4x4::transform3x3)
         //.def("transform3x3", (ofVec3f(ofMatrix4x4::*)(const ofMatrix4x4&,const ofVec3f&)) &ofMatrix4x4::transform3x3)
         .def_readonly("_mat", &ofMatrix4x4::_mat),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofQuaternion

         class_<ofQuaternion>("quaternion")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float>())
		 .def(constructor<const ofVec4f&>())
         .def(constructor<float,const ofVec3f&>())
         .def(constructor<float,const ofVec3f&,float,const ofVec3f&,float,const ofVec3f&>())
         .def(self == other<const ofQuaternion&>())
         .def(self + other<const ofQuaternion&>())
         .def(self - other<const ofQuaternion&>())
         .def(self * other<const ofQuaternion&>())
         .def(self / other<const ofQuaternion&>())
         .def(self * other<const ofVec3f&>())
         .def(self * other<float>())
         .def(self / other<float>())
         .def("asVec4", (ofVec4f(ofQuaternion::*)(void)) &ofQuaternion::asVec4)
         .def("asVec3", (ofVec3f(ofQuaternion::*)(void)) &ofQuaternion::asVec3)
         .def("set", (void(ofQuaternion::*)(float,float,float,float)) &ofQuaternion::set)
         .def("set", (void(ofQuaternion::*)(const ofVec4f&)) &ofQuaternion::set)
         .def("set", (void(ofQuaternion::*)(const ofMatrix4x4&)) &ofQuaternion::set)
         .def("get", (void(ofQuaternion::*)(const ofMatrix4x4&)) &ofQuaternion::get)
         //.def("x", (float(ofQuaternion::*)(void)) &ofQuaternion::x)
         //.def("y", (float(ofQuaternion::*)(void)) &ofQuaternion::y)
         //.def("z", (float(ofQuaternion::*)(void)) &ofQuaternion::z)
         //.def("w", (float(ofQuaternion::*)(void)) &ofQuaternion::w)
         .def("zeroRotation", (bool(ofQuaternion::*)(void)) &ofQuaternion::zeroRotation)
         .def("length", (float(ofQuaternion::*)(void)) &ofQuaternion::length)
         .def("length2", (float(ofQuaternion::*)(void)) &ofQuaternion::length2)
         .def("conj", (ofQuaternion(ofQuaternion::*)(void)) &ofQuaternion::conj)
         .def("inverse", (ofQuaternion(ofQuaternion::*)(void)) &ofQuaternion::inverse)
         .def("makeRotate", (void(ofQuaternion::*)(float,float,float,float)) &ofQuaternion::makeRotate)
         .def("makeRotate", (void(ofQuaternion::*)(float,const ofVec3f&)) &ofQuaternion::makeRotate)
         .def("makeRotate", (void(ofQuaternion::*)(float,const ofVec3f&,float,const ofVec3f&,float,const ofVec3f&)) &ofQuaternion::makeRotate)
         .def("makeRotate", (void(ofQuaternion::*)(const ofVec3f&,const ofVec3f&)) &ofQuaternion::makeRotate)
         .def("makeRotate_original", (void(ofQuaternion::*)(const ofVec3f&,const ofVec3f&)) &ofQuaternion::makeRotate_original)
         //.def("getRotate", (void(ofQuaternion::*)(float&,float&,float&,float&)) &ofQuaternion::getRotate)
         //.def("getRotate", (void(ofQuaternion::*)(float&,ofVec3f&)) &ofQuaternion::getRotate)
         .def("getEuler", (void(ofQuaternion::*)(void)) &ofQuaternion::getEuler)
         .def("slerp", (void(ofQuaternion::*)(float,const ofQuaternion&,const ofQuaternion&)) &ofQuaternion::slerp)
         .def_readonly("_v", &ofQuaternion::_v),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVec2f

         class_<ofVec2f>("vec2f")
		 .def(constructor<>())
		 .def(constructor<float,float>())
		 .def(constructor<const ofVec3f&>())
		 .def(constructor<const ofVec4f&>())
		 .def("set", (void(ofVec2f::*)(float,float)) &ofVec2f::set)
         .def("set", (void(ofVec2f::*)(const ofVec2f&)) &ofVec2f::set)
         .def(self == other<const ofVec2f&>())
         .def("match", (bool(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::match)
         .def("align", (bool(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::align)
         .def("alignRad", (bool(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::alignRad)
         .def(self + other<const ofVec2f&>())
         .def(self - other<const ofVec2f&>())
         .def(self * other<const ofVec2f&>())
         .def(self / other<const ofVec2f&>())
         .def(self + other<const float>())
         .def(self - other<const float>())
         .def(self * other<const float>())
         .def(self / other<const float>())
         .def("getScaled", (ofVec2f(ofVec2f::*)(const float)) &ofVec2f::getScaled)
         .def("scale", (ofVec2f&(ofVec2f::*)(const float)) &ofVec2f::scale)
         //.def("getRotated", (ofVec2f(ofVec2f::*)(float)) &ofVec2f::getRotated)
         //.def("getRotatedRad", (ofVec2f(ofVec2f::*)(float)) &ofVec2f::getRotatedRad)
         .def("rotate", (ofVec2f&(ofVec2f::*)(float)) &ofVec2f::rotate)
         .def("rotateRad", (ofVec2f&(ofVec2f::*)(float)) &ofVec2f::rotateRad)
         //.def("getRotated", (ofVec2f(ofVec2f::*)(float,const ofVec2f&)) &ofVec2f::getRotated)
         //.def("getRotatedRad", (ofVec2f(ofVec2f::*)(float,const ofVec2f&)) &ofVec2f::getRotatedRad)
         .def("rotate", (ofVec2f&(ofVec2f::*)(float,const ofVec2f&)) &ofVec2f::rotate)
         .def("rotateRad", (ofVec2f&(ofVec2f::*)(float,const ofVec2f&)) &ofVec2f::rotateRad)
		 //.def("rotated", (ofVec2f(ofVec2f::*)(float,const ofVec2f&)) &ofVec2f::rotated)
         .def("getMapped", (ofVec2f(ofVec2f::*)(const ofVec2f&,const ofVec2f&,const ofVec2f&)) &ofVec2f::getMapped)
         .def("map", (ofVec2f&(ofVec2f::*)(const ofVec2f&,const ofVec2f&,const ofVec2f&)) &ofVec2f::map)
         .def("distance", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::distance)
         .def("squareDistance", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::squareDistance)
         .def("getInterpolated", (ofVec2f(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::getInterpolated)
         .def("interpolate", (ofVec2f&(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::interpolate)
         .def("getMiddle", (ofVec2f(ofVec2f::*)(const ofVec2f&)) &ofVec2f::getMiddle)
         .def("middle", (ofVec2f&(ofVec2f::*)(const ofVec2f&)) &ofVec2f::middle)
         .def("average", (ofVec2f&(ofVec2f::*)(const ofVec2f&,int)) &ofVec2f::average)
         .def("getNormalized", (ofVec2f(ofVec2f::*)(void)) &ofVec2f::getNormalized)
         .def("normalize", (ofVec2f&(ofVec2f::*)(void)) &ofVec2f::normalize)
         .def("getLimited", (ofVec2f(ofVec2f::*)(float)) &ofVec2f::getLimited)
         .def("limit", (ofVec2f&(ofVec2f::*)(float)) &ofVec2f::limit)
         .def("getPerpendicular", (ofVec2f(ofVec2f::*)(void)) &ofVec2f::getPerpendicular)
         .def("perpendicular", (ofVec2f&(ofVec2f::*)(void)) &ofVec2f::perpendicular)
         .def("length", (float(ofVec2f::*)(void)) &ofVec2f::length)
         .def("squareLength", (float(ofVec2f::*)(void)) &ofVec2f::squareLength)
         .def("angle", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::angle)
         .def("angleRad", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::angleRad)
         .def("dot", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::dot)
         .def("rescaled", (ofVec2f(ofVec2f::*)(const float)) &ofVec2f::rescaled)
         .def("rescale", (ofVec2f&(ofVec2f::*)(const float)) &ofVec2f::rescale)
         //.def("rotated", (ofVec2f(ofVec2f::*)(float)) &ofVec2f::rotated)
         .def("normalized", (ofVec2f(ofVec2f::*)(void)) &ofVec2f::normalized)
         .def("limited", (ofVec2f(ofVec2f::*)(float)) &ofVec2f::limited)
         .def("perpendiculared", (ofVec2f(ofVec2f::*)(void)) &ofVec2f::perpendiculared)
         .def("lengthSquared", (float(ofVec2f::*)(void)) &ofVec2f::lengthSquared)
         .def("interpolated", (ofVec2f(ofVec2f::*)(const ofVec2f&,float)) &ofVec2f::interpolated)
         .def("middled", (ofVec2f(ofVec2f::*)(const ofVec2f&)) &ofVec2f::middled)
         .def("mapped", (ofVec2f(ofVec2f::*)(const ofVec2f&,const ofVec2f&,const ofVec2f&)) &ofVec2f::mapped)
         .def("distanceSquared", (float(ofVec2f::*)(const ofVec2f&)) &ofVec2f::distanceSquared)
         .def_readwrite("x", &ofVec2f::x)
		 .def_readwrite("y", &ofVec2f::y),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVec3f

         class_<ofVec3f>("vec3f")
		 .def(constructor<>())
		 .def(constructor<float,float,float>())
		 .def(constructor<const ofVec2f&>())
		 .def(constructor<const ofVec4f&>())
		 .def("set", (void(ofVec3f::*)(float,float,float)) &ofVec3f::set)
		 .def("set", (void(ofVec3f::*)(const ofVec3f&)) &ofVec3f::set)
         .def(self == other<const ofVec3f&>())
         .def("match", (bool(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::match)
         .def("align", (bool(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::align)
         .def("alignRad", (bool(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::alignRad)
         .def(self + other<const ofVec3f&>())
         .def(self - other<const ofVec3f&>())
         .def(self * other<const ofVec3f&>())
         .def(self / other<const ofVec3f&>())
         .def(self + other<const float>())
         .def(self - other<const float>())
         .def(self * other<const float>())
         .def(self / other<const float>())
         .def("getScaled", (ofVec3f(ofVec3f::*)(const float)) &ofVec3f::getScaled)
         .def("scale", (ofVec3f&(ofVec3f::*)(const float)) &ofVec3f::scale)
         //.def("getRotated", (ofVec3f(ofVec3f::*)(float,float,float)) &ofVec3f::getRotated)
         //.def("getRotatedRad", (ofVec3f(ofVec3f::*)(float,float,float)) &ofVec3f::getRotatedRad)
         .def("rotate", (ofVec3f&(ofVec3f::*)(float,float,float)) &ofVec3f::rotate)
         .def("rotateRad", (ofVec3f&(ofVec3f::*)(float,float,float)) &ofVec3f::rotateRad)
         //.def("getRotated", (ofVec3f(ofVec3f::*)(float,const ofVec3f&)) &ofVec3f::getRotated)
         //.def("getRotatedRad", (ofVec3f(ofVec3f::*)(float,const ofVec3f&)) &ofVec3f::getRotatedRad)
         .def("rotate", (ofVec3f&(ofVec3f::*)(float,const ofVec3f&)) &ofVec3f::rotate)
         .def("rotateRad", (ofVec3f&(ofVec3f::*)(float,const ofVec3f&)) &ofVec3f::rotateRad)
		 //.def("rotated", (ofVec3f(ofVec3f::*)(float,const ofVec3f&)) &ofVec3f::rotated)
         .def("getMapped", (ofVec3f(ofVec3f::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofVec3f::getMapped)
         .def("map", (ofVec3f&(ofVec3f::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofVec3f::map)
         .def("distance", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::distance)
         .def("squareDistance", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::squareDistance)
         .def("getInterpolated", (ofVec3f(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::getInterpolated)
         .def("interpolate", (ofVec3f&(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::interpolate)
         .def("getMiddle", (ofVec3f(ofVec3f::*)(const ofVec3f&)) &ofVec3f::getMiddle)
         .def("middle", (ofVec3f&(ofVec3f::*)(const ofVec3f&)) &ofVec3f::middle)
         .def("average", (ofVec3f&(ofVec3f::*)(const ofVec3f&,int)) &ofVec3f::average)
         .def("getNormalized", (ofVec3f(ofVec3f::*)(void)) &ofVec3f::getNormalized)
         .def("normalize", (ofVec3f&(ofVec3f::*)(void)) &ofVec3f::normalize)
         .def("getLimited", (ofVec3f(ofVec3f::*)(float)) &ofVec3f::getLimited)
         .def("limit", (ofVec3f&(ofVec3f::*)(float)) &ofVec3f::limit)
         .def("getCrossed", (ofVec3f(ofVec3f::*)(const ofVec3f&)) &ofVec3f::getCrossed)
         .def("cross", (ofVec3f&(ofVec3f::*)(const ofVec3f&)) &ofVec3f::cross)
         .def("getPerpendicular", (ofVec3f(ofVec3f::*)(void)) &ofVec3f::getPerpendicular)
         .def("perpendicular", (ofVec3f&(ofVec3f::*)(void)) &ofVec3f::perpendicular)
         .def("length", (float(ofVec3f::*)(void)) &ofVec3f::length)
         .def("squareLength", (float(ofVec3f::*)(void)) &ofVec3f::squareLength)
         .def("angle", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::angle)
         .def("angleRad", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::angleRad)
         .def("dot", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::dot)
         .def("rescaled", (ofVec3f(ofVec3f::*)(const float)) &ofVec3f::rescaled)
         .def("rescale", (ofVec3f&(ofVec3f::*)(const float)) &ofVec3f::rescale)
         //.def("rotated", (ofVec3f(ofVec3f::*)(float)) &ofVec3f::rotated)
         .def("normalized", (ofVec3f(ofVec3f::*)(void)) &ofVec3f::normalized)
         .def("limited", (ofVec3f(ofVec3f::*)(float)) &ofVec3f::limited)
         .def("perpendiculared", (ofVec3f(ofVec3f::*)(void)) &ofVec3f::perpendiculared)
         .def("lengthSquared", (float(ofVec3f::*)(void)) &ofVec3f::lengthSquared)
         .def("interpolated", (ofVec3f(ofVec3f::*)(const ofVec3f&,float)) &ofVec3f::interpolated)
         .def("middled", (ofVec3f(ofVec3f::*)(const ofVec3f&)) &ofVec3f::middled)
         .def("mapped", (ofVec3f(ofVec3f::*)(const ofVec3f&,const ofVec3f&,const ofVec3f&)) &ofVec3f::mapped)
         .def("distanceSquared", (float(ofVec3f::*)(const ofVec3f&)) &ofVec3f::distanceSquared)
         .def_readwrite("x", &ofVec3f::x)
		 .def_readwrite("y", &ofVec3f::y)
         .def_readwrite("z", &ofVec3f::z),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVec4f

         class_<ofVec4f>("vec4f")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float>())
		 .def(constructor<const ofVec2f&>())
		 .def(constructor<const ofVec3f&>())
		 .def("set", (void(ofVec4f::*)(float,float,float,float)) &ofVec4f::set)
		 .def("set", (void(ofVec4f::*)(const ofVec4f&)) &ofVec4f::set)
         .def(self == other<const ofVec4f&>())
         .def("match", (bool(ofVec4f::*)(const ofVec4f&,float)) &ofVec4f::match)
         .def(self + other<const ofVec4f&>())
         .def(self - other<const ofVec4f&>())
         .def(self * other<const ofVec4f&>())
         .def(self / other<const ofVec4f&>())
         .def(self + other<const float>())
         .def(self - other<const float>())
         .def(self * other<const float>())
         .def(self / other<const float>())
         .def("getScaled", (ofVec4f(ofVec4f::*)(const float)) &ofVec4f::getScaled)
         .def("scale", (ofVec4f&(ofVec4f::*)(const float)) &ofVec4f::scale)
         //.def("getRotated", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::getRotated)
         //.def("getRotatedRad", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::getRotatedRad)
         //.def("rotate", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::rotate)
         //.def("rotateRad", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::rotateRad)
         //.def("getRotated", (ofVec4f(ofVec4f::*)(float,const ofVec4f&)) &ofVec4f::getRotated)
         //.def("getRotatedRad", (ofVec4f(ofVec4f::*)(float,const ofVec4f&)) &ofVec4f::getRotatedRad)
         //.def("rotate", (ofVec4f(ofVec4f::*)(float,const ofVec4f&)) &ofVec4f::rotate)
         //.def("rotateRad", (ofVec4f(ofVec4f::*)(float,const ofVec4f&)) &ofVec4f::rotateRad)
		 //.def("rotated", (ofVec4f(ofVec4f::*)(float,const ofVec4f&)) &ofVec4f::rotated)
         .def("distance", (float(ofVec4f::*)(const ofVec4f&)) &ofVec4f::distance)
         .def("squareDistance", (float(ofVec4f::*)(const ofVec4f&)) &ofVec4f::squareDistance)
         .def("getInterpolated", (ofVec4f(ofVec4f::*)(const ofVec4f&,float)) &ofVec4f::getInterpolated)
         .def("interpolate", (ofVec4f&(ofVec4f::*)(const ofVec4f&,float)) &ofVec4f::interpolate)
         .def("getMiddle", (ofVec4f(ofVec4f::*)(const ofVec4f&)) &ofVec4f::getMiddle)
         .def("middle", (ofVec4f&(ofVec4f::*)(const ofVec4f&)) &ofVec4f::middle)
         .def("average", (ofVec4f&(ofVec4f::*)(const ofVec4f&,int)) &ofVec4f::average)
         .def("getNormalized", (ofVec4f(ofVec4f::*)(void)) &ofVec4f::getNormalized)
         .def("normalize", (ofVec4f&(ofVec4f::*)(void)) &ofVec4f::normalize)
         .def("getLimited", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::getLimited)
         .def("limit", (ofVec4f&(ofVec4f::*)(float)) &ofVec4f::limit)
         .def("length", (float(ofVec4f::*)(void)) &ofVec4f::length)
         .def("squareLength", (float(ofVec4f::*)(void)) &ofVec4f::squareLength)
         .def("dot", (float(ofVec4f::*)(const ofVec4f&)) &ofVec4f::dot)
         .def("rescaled", (ofVec4f(ofVec4f::*)(const float)) &ofVec4f::rescaled)
         .def("rescale", (ofVec4f&(ofVec4f::*)(const float)) &ofVec4f::rescale)
         .def("normalized", (ofVec4f(ofVec4f::*)(void)) &ofVec4f::normalized)
         .def("limited", (ofVec4f(ofVec4f::*)(float)) &ofVec4f::limited)
         .def("lengthSquared", (float(ofVec4f::*)(void)) &ofVec4f::lengthSquared)
         .def("interpolated", (ofVec4f(ofVec4f::*)(const ofVec4f&,float)) &ofVec4f::interpolated)
         .def("middled", (ofVec4f(ofVec4f::*)(const ofVec4f&)) &ofVec4f::middled)
         .def("distanceSquared", (float(ofVec4f::*)(const ofVec4f&)) &ofVec4f::distanceSquared)
         .def_readwrite("x", &ofVec4f::x)
		 .def_readwrite("y", &ofVec4f::y)
         .def_readwrite("z", &ofVec4f::z)
         .def_readwrite("w", &ofVec4f::w),

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section gl [ofMaterials, ofFbo, ofGLRenderer, ofVbo, ofTextureData, ofShader, ofVboMesh, ofTexture, ofGLUtils, ofLight]

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofMaterial

         class_<ofMaterial>("material")
		 .def(constructor<>())
         .def("setColors", (void(ofMaterial::*)(ofFloatColor,ofFloatColor,ofFloatColor,ofFloatColor)) &ofMaterial::setColors)
         .def("setDiffuseColor", (void(ofMaterial::*)(ofFloatColor)) &ofMaterial::setDiffuseColor)
         .def("setAmbientColor", (void(ofMaterial::*)(ofFloatColor)) &ofMaterial::setAmbientColor)
         .def("setSpecularColor", (void(ofMaterial::*)(ofFloatColor)) &ofMaterial::setSpecularColor)
         .def("setEmissiveColor", (void(ofMaterial::*)(ofFloatColor)) &ofMaterial::setEmissiveColor)
         .def("setShininess", (void(ofMaterial::*)(float)) &ofMaterial::setShininess)
         .def("getDiffuseColor", (ofFloatColor(ofMaterial::*)(void)) &ofMaterial::getDiffuseColor)
         .def("getAmbientColor", (ofFloatColor(ofMaterial::*)(void)) &ofMaterial::getAmbientColor)
         .def("getSpecularColor", (ofFloatColor(ofMaterial::*)(void)) &ofMaterial::getSpecularColor)
         .def("getEmissiveColor", (ofFloatColor(ofMaterial::*)(void)) &ofMaterial::getEmissiveColor)
         .def("getShininess", (float(ofMaterial::*)(void)) &ofMaterial::getShininess)
         .def("beginMaterial", (void(ofMaterial::*)(void)) &ofMaterial::begin)
		 .def("endMaterial", (void(ofMaterial::*)(void)) &ofMaterial::end),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFbo

         class_<ofFbo>("fbo")
		 .def(constructor<>())
         .def(constructor<const ofFbo&>())
		 .def("allocate", (void(ofFbo::*)(int,int,int,int)) &ofFbo::allocate) // int width, int height, int internalformat, int numSamples
         .def("draw", (void(ofFbo::*)(float,float)) &ofFbo::draw)
         .def("draw", (void(ofFbo::*)(float,float,float,float)) &ofFbo::draw)
         .def("setAnchorPercent", (void(ofFbo::*)(float,float)) &ofFbo::setAnchorPercent)
         .def("setAnchorPoint", (void(ofFbo::*)(float,float)) &ofFbo::setAnchorPoint)
         .def("resetAnchor", (void(ofFbo::*)(void)) &ofFbo::resetAnchor)
         .def("setDefaultTextureIndex", (void(ofFbo::*)(int)) &ofFbo::setDefaultTextureIndex)
         .def("getDefaultTextureIndex", (int(ofFbo::*)(void)) &ofFbo::getDefaultTextureIndex)
         //.def("getTextureReference", (ofTexture(ofFbo::*)(void)) &ofFbo::getTextureReference)
         //.def("getTextureReference", (ofTexture(ofFbo::*)(int)) &ofFbo::getTextureReference)
         .def("setUseTexture", (void(ofFbo::*)(bool)) &ofFbo::setUseTexture)
         .def("beginFbo", (void(ofFbo::*)(void)) &ofFbo::begin)
		 .def("endFbo", (void(ofFbo::*)(void)) &ofFbo::end)
         .def("readToPixels", (void(ofFbo::*)(ofPixels&,int)) &ofFbo::readToPixels)
         .def("getWidth", (float(ofFbo::*)(void)) &ofFbo::getWidth)
		 .def("getHeight", (float(ofFbo::*)(void)) &ofFbo::getHeight)
         .def("bind", (void(ofFbo::*)(void)) &ofFbo::bind)
		 .def("unbind", (void(ofFbo::*)(void)) &ofFbo::unbind)
         .def("getNumTextures", (int(ofFbo::*)(void)) &ofFbo::getNumTextures)
         .def("getFbo", (GLuint(ofFbo::*)(void)) &ofFbo::getFbo)
         .def("getDepthBuffer", (GLuint(ofFbo::*)(void)) &ofFbo::getDepthBuffer)
         .def("getStencilBuffer", (GLuint(ofFbo::*)(void)) &ofFbo::getStencilBuffer)
         .def("checkGLSupport", (bool(*)(void)) &ofFbo::checkGLSupport)
         .def("maxColorAttachments", (int(*)(void)) &ofFbo::maxColorAttachments)
         .def("maxDrawBuffers", (int(*)(void)) &ofFbo::maxDrawBuffers)
         .def("maxSamples", (int(*)(void)) &ofFbo::maxSamples),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofGLRenderer

         class_<ofGLRenderer>("GLRenderer")
		 .def(constructor<bool>())
         .def("getType", (string(ofGLRenderer::*)(void)) &ofGLRenderer::getType)
         .def("setCurrentFBO", (void(ofGLRenderer::*)(ofFbo*)) &ofGLRenderer::setCurrentFBO)
         .def("update", (void(ofGLRenderer::*)(void)) &ofGLRenderer::update)
         //.def("drawMesh", (void(ofGLRenderer::*)(ofMesh&)) &ofGLRenderer::draw)
         //.def("drawMesh", (void(ofGLRenderer::*)(ofMesh&,ofPolyRenderMode)) &ofGLRenderer::draw)
         .def("drawPoly", (void(ofGLRenderer::*)(ofPolyline&)) &ofGLRenderer::draw)
         .def("drawPath", (void(ofGLRenderer::*)(ofPath&)) &ofGLRenderer::draw)
         //.def("drawImage", (void(ofGLRenderer::*)(ofImage&,float,float,float,float,float)) &ofGLRenderer::draw)
         .def("rendersPathPrimitives", (bool(ofGLRenderer::*)(void)) &ofGLRenderer::rendersPathPrimitives)
         .def("pushView", (void(ofGLRenderer::*)(void)) &ofGLRenderer::pushView)
         .def("popView", (void(ofGLRenderer::*)(void)) &ofGLRenderer::popView)
         .def("viewport", (void(ofGLRenderer::*)(ofRectangle)) &ofGLRenderer::viewport)
         .def("viewport", (void(ofGLRenderer::*)(float,float,float,float,bool)) &ofGLRenderer::viewport)
         .def("setupScreenPerspective", (void(ofGLRenderer::*)(float,float,ofOrientation,bool,float,float,float)) &ofGLRenderer::setupScreenPerspective)
         .def("setupScreenOrtho", (void(ofGLRenderer::*)(float,float,ofOrientation,bool,float,float)) &ofGLRenderer::setupScreenOrtho)
         .def("getCurrentViewport", (ofRectangle(ofGLRenderer::*)(void)) &ofGLRenderer::getCurrentViewport)
         .def("getViewportWidth", (int(ofGLRenderer::*)(void)) &ofGLRenderer::getViewportWidth)
         .def("getViewportHeight", (int(ofGLRenderer::*)(void)) &ofGLRenderer::getViewportHeight)
         .def("pushMatrix", (void(ofGLRenderer::*)(void)) &ofGLRenderer::pushMatrix)
         .def("popMatrix", (void(ofGLRenderer::*)(void)) &ofGLRenderer::popMatrix)
         .def("translate", (void(ofGLRenderer::*)(const ofPoint&)) &ofGLRenderer::translate)
         .def("translate", (void(ofGLRenderer::*)(float,float,float)) &ofGLRenderer::translate)
         .def("scale", (void(ofGLRenderer::*)(float,float,float)) &ofGLRenderer::scale)
         .def("rotate", (void(ofGLRenderer::*)(float,float,float,float)) &ofGLRenderer::rotate)
         .def("rotate", (void(ofGLRenderer::*)(float)) &ofGLRenderer::rotate)
         .def("rotateX", (void(ofGLRenderer::*)(float)) &ofGLRenderer::rotateX)
         .def("rotateY", (void(ofGLRenderer::*)(float)) &ofGLRenderer::rotateY)
         .def("rotateZ", (void(ofGLRenderer::*)(float)) &ofGLRenderer::rotateZ)
         .def("setupGraphicDefaults", (void(ofGLRenderer::*)(void)) &ofGLRenderer::setupGraphicDefaults)
         .def("setupScreen", (void(ofGLRenderer::*)(void)) &ofGLRenderer::setupScreen)
         .def("setFillMode", (void(ofGLRenderer::*)(ofFillFlag)) &ofGLRenderer::setFillMode)
         .def("getFillMode", (ofFillFlag(ofGLRenderer::*)(void)) &ofGLRenderer::getFillMode)
         .def("setCircleResolution", (void(ofGLRenderer::*)(int)) &ofGLRenderer::setCircleResolution)
         .def("setRectMode", (void(ofGLRenderer::*)(ofRectMode)) &ofGLRenderer::setRectMode)
         .def("getRectMode", (ofRectMode(ofGLRenderer::*)(void)) &ofGLRenderer::getRectMode)
         .def("setLineWidth", (void(ofGLRenderer::*)(float)) &ofGLRenderer::setLineWidth)
         .def("setLineSmoothing", (void(ofGLRenderer::*)(bool)) &ofGLRenderer::setLineSmoothing)
         .def("setBlendMode", (void(ofGLRenderer::*)(ofBlendMode)) &ofGLRenderer::setBlendMode)
         .def("enablePointSprites", (void(ofGLRenderer::*)(void)) &ofGLRenderer::enablePointSprites)
         .def("disablePointSprites", (void(ofGLRenderer::*)(void)) &ofGLRenderer::disablePointSprites)
         .def("setColor", (void(ofGLRenderer::*)(int,int,int)) &ofGLRenderer::setColor)
         .def("setColor", (void(ofGLRenderer::*)(int,int,int,int)) &ofGLRenderer::setColor)
         .def("setColor", (void(ofGLRenderer::*)(const ofColor&)) &ofGLRenderer::setColor)
         .def("setColor", (void(ofGLRenderer::*)(const ofColor&,int)) &ofGLRenderer::setColor)
         .def("setColor", (void(ofGLRenderer::*)(int)) &ofGLRenderer::setColor)
         .def("setHexColor", (void(ofGLRenderer::*)(int)) &ofGLRenderer::setHexColor)
         .def("getBgColor", (ofFloatColor(ofGLRenderer::*)(void)) &ofGLRenderer::getBgColor)
         .def("bClearBg", (bool(ofGLRenderer::*)(void)) &ofGLRenderer::bClearBg)
         .def("background", (void(ofGLRenderer::*)(const ofColor&)) &ofGLRenderer::background)
         .def("background", (void(ofGLRenderer::*)(float)) &ofGLRenderer::background)
         .def("background", (void(ofGLRenderer::*)(int,float)) &ofGLRenderer::background)
         .def("background", (void(ofGLRenderer::*)(int,int,int,int)) &ofGLRenderer::background)
         .def("setBackgroundAuto", (void(ofGLRenderer::*)(bool)) &ofGLRenderer::setBackgroundAuto)
         .def("clear", (void(ofGLRenderer::*)(float,float,float,float)) &ofGLRenderer::clear)
         .def("clear", (void(ofGLRenderer::*)(float,float)) &ofGLRenderer::clear)
         .def("clearAlpha", (void(ofGLRenderer::*)(void)) &ofGLRenderer::clearAlpha)
         .def("drawLine", (void(ofGLRenderer::*)(float,float,float,float,float,float)) &ofGLRenderer::drawLine)
         .def("drawRectangle", (void(ofGLRenderer::*)(float,float,float,float,float)) &ofGLRenderer::drawRectangle)
         .def("drawTriangle", (void(ofGLRenderer::*)(float,float,float,float,float,float,float,float,float)) &ofGLRenderer::drawTriangle)
         .def("drawCircle", (void(ofGLRenderer::*)(float,float,float,float)) &ofGLRenderer::drawCircle)
         .def("drawEllipse", (void(ofGLRenderer::*)(float,float,float,float,float)) &ofGLRenderer::drawEllipse)
         .def("drawString", (void(ofGLRenderer::*)(string,float,float,float,ofDrawBitmapMode)) &ofGLRenderer::drawString),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVbo

         class_<ofVbo>("vbo")
		 .def(constructor<>())
         .def(constructor<const ofVbo&>())
         .def("getVertId", (GLuint(ofVbo::*)(void)) &ofVbo::getVertId)
         .def("getColorId", (GLuint(ofVbo::*)(void)) &ofVbo::getColorId)
         .def("getNormalId", (GLuint(ofVbo::*)(void)) &ofVbo::getNormalId)
         .def("getTexCoordId", (GLuint(ofVbo::*)(void)) &ofVbo::getTexCoordId)
         .def("getIndexId", (GLuint(ofVbo::*)(void)) &ofVbo::getIndexId)
         .def("getIsAllocated", (bool(ofVbo::*)(void)) &ofVbo::getIsAllocated)
         .def("getUsingVerts", (bool(ofVbo::*)(void)) &ofVbo::getUsingVerts)
         .def("getUsingColors", (bool(ofVbo::*)(void)) &ofVbo::getUsingColors)
         .def("getUsingNormals", (bool(ofVbo::*)(void)) &ofVbo::getUsingNormals)
         .def("getUsingTexCoords", (bool(ofVbo::*)(void)) &ofVbo::getUsingTexCoords)
         .def("getUsingIndices", (bool(ofVbo::*)(void)) &ofVbo::getUsingIndices)
         .def("draw", (void(ofVbo::*)(int,int,int)) &ofVbo::draw)
         .def("drawElements", (void(ofVbo::*)(int,int)) &ofVbo::drawElements)
         .def("bind", (void(ofVbo::*)(void)) &ofVbo::bind)
         .def("unbind", (void(ofVbo::*)(void)) &ofVbo::unbind)
         .def("clear", (void(ofVbo::*)(void)) &ofVbo::clear)
         .def("setMesh", (void(ofVbo::*)(const ofMesh&,int)) &ofVbo::setMesh)
         .def("setVertex3Data", (void(ofVbo::*)(const ofVec3f*,int,int)) &ofVbo::setVertexData)
         .def("setVertex2Data", (void(ofVbo::*)(const ofVec2f*,int,int)) &ofVbo::setVertexData)
         .def("setColorData", (void(ofVbo::*)(const ofFloatColor*,int,int)) &ofVbo::setColorData)
         .def("setNormalData", (void(ofVbo::*)(const ofVec3f*,int,int)) &ofVbo::setNormalData)
         .def("setTexCoordData", (void(ofVbo::*)(const ofVec2f*,int,int)) &ofVbo::setTexCoordData)
         .def("setIndexData", (void(ofVbo::*)(const ofIndexType*,int,int)) &ofVbo::setIndexData)
         //.def("setVertexData", (void(ofVbo::*)(const float*,int,int,int,int)) &ofVbo::setColorData)
         //.def("setColorData", (void(ofVbo::*)(const ofFloatColor*,int,int,int)) &ofVbo::setColorData)
         //.def("setNormalData", (void(ofVbo::*)(const ofVec3f*,int,int,int)) &ofVbo::setNormalData)
         //.def("setTexCoordData", (void(ofVbo::*)(const ofVec2f*,int,int,int)) &ofVbo::setTexCoordData)
         .def("updateMesh", (void(ofVbo::*)(const ofMesh&)) &ofVbo::updateMesh)
         .def("updateVertex3Data", (void(ofVbo::*)(const ofVec3f*,int)) &ofVbo::updateVertexData)
         .def("updateVertex2Data", (void(ofVbo::*)(const ofVec2f*,int)) &ofVbo::updateVertexData)
         .def("updateColorData", (void(ofVbo::*)(const ofFloatColor*,int)) &ofVbo::updateColorData)
         .def("updateNormalData", (void(ofVbo::*)(const ofVec3f*,int)) &ofVbo::updateNormalData)
         .def("updateTexCoordDataF", (void(ofVbo::*)(const ofVec2f*,int)) &ofVbo::updateTexCoordData)
         .def("updateIndexData", (void(ofVbo::*)(const ofIndexType*,int)) &ofVbo::updateIndexData)
         .def("updateVertexDataF", (void(ofVbo::*)(const float*,int)) &ofVbo::updateVertexData)
         .def("updateColorDataF", (void(ofVbo::*)(const float*,int)) &ofVbo::updateColorData)
         .def("updateNormalDataF", (void(ofVbo::*)(const float*,int)) &ofVbo::updateNormalData)
         .def("updateTexCoordDataF", (void(ofVbo::*)(const float*,int)) &ofVbo::updateTexCoordData),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofTextureData

         class_<ofTextureData>("textureData")
		 .def(constructor<>())
         .def_readonly("textureID", &ofTextureData::textureID)
         .def_readonly("textureTarget", &ofTextureData::textureTarget)
         .def_readonly("glTypeInternal", &ofTextureData::glTypeInternal)
         .def_readonly("glType", &ofTextureData::glType)
         .def_readonly("pixelType", &ofTextureData::pixelType)
         .def_readonly("tex_t", &ofTextureData::tex_t)
         .def_readonly("tex_u", &ofTextureData::tex_u)
         .def_readonly("tex_w", &ofTextureData::tex_w)
         .def_readonly("tex_h", &ofTextureData::tex_h)
         .def_readonly("width", &ofTextureData::width)
         .def_readonly("height", &ofTextureData::height)
         .def_readonly("bFlipTexture", &ofTextureData::bFlipTexture)
         .def_readonly("compressionType", &ofTextureData::compressionType)
         .def_readonly("bAllocated", &ofTextureData::bAllocated),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofShader

         class_<ofShader>("shader")
		 .def(constructor<>())
         .def("load", (bool(ofShader::*)(string)) &ofShader::load)
         .def("load", (bool(ofShader::*)(string,string,string)) &ofShader::load)
         .def("beginShader", (void(ofShader::*)(void)) &ofShader::begin)
         .def("endShader", (void(ofShader::*)(void)) &ofShader::end)
         .def("setUniformTexture", (void(ofShader::*)(const char*,ofBaseHasTexture&,int)) &ofShader::setUniformTexture)
         .def("setUniformTexture", (void(ofShader::*)(const char*,ofTexture&,int)) &ofShader::setUniformTexture)
         .def("setUniform1i", (void(ofShader::*)(const char*,int)) &ofShader::setUniform1i)
         .def("setUniform2i", (void(ofShader::*)(const char*,int,int)) &ofShader::setUniform2i)
         .def("setUniform3i", (void(ofShader::*)(const char*,int,int,int)) &ofShader::setUniform3i)
         .def("setUniform4i", (void(ofShader::*)(const char*,int,int,int,int)) &ofShader::setUniform4i)
         .def("setUniform1f", (void(ofShader::*)(const char*,float)) &ofShader::setUniform1f)
         .def("setUniform2f", (void(ofShader::*)(const char*,float,float)) &ofShader::setUniform2f)
         .def("setUniform3f", (void(ofShader::*)(const char*,float,float,float)) &ofShader::setUniform3f)
         .def("setUniform4f", (void(ofShader::*)(const char*,float,float,float,float)) &ofShader::setUniform4f)
         .def("unload", (void(ofShader::*)(void)) &ofShader::unload),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVboMesh

         class_<ofVboMesh>("vboMesh")
		 .def(constructor<>())
         .def(constructor<const ofMesh&>())
         .def("setUsage", (void(ofVboMesh::*)(int)) &ofVboMesh::setUsage)

         .def("setMode", (void(ofVboMesh::*)(ofPrimitiveMode)) &ofVboMesh::setMode)
         .def("getMode", (ofPrimitiveMode(ofVboMesh::*)(void)) &ofVboMesh::getMode)
         .def("clear", (void(ofVboMesh::*)(void)) &ofVboMesh::clear)
         .def("setupIndicesAuto", (void(ofVboMesh::*)(void)) &ofVboMesh::setupIndicesAuto)
         .def("getVertex", (ofVec3f(ofVboMesh::*)(int)) &ofVboMesh::getVertex)
         //.def("removeVertex", (void(ofVboMesh::*)(int)) &ofVboMesh::removeVertex)
         .def("clearVertices", (void(ofVboMesh::*)(void)) &ofVboMesh::clearVertices)
         .def("getNormal", (ofVec3f(ofVboMesh::*)(int)) &ofVboMesh::getNormal)
         //.def("removeNormal", (void(ofVboMesh::*)(int)) &ofVboMesh::removeNormal)
         .def("clearNormals", (void(ofVboMesh::*)(void)) &ofVboMesh::clearNormals)
         .def("getColor", (ofFloatColor(ofVboMesh::*)(int)) &ofVboMesh::getColor)
         //.def("removeColor", (void(ofVboMesh::*)(int)) &ofVboMesh::removeColor)
         .def("clearColors", (void(ofVboMesh::*)(void)) &ofVboMesh::clearColors)
         .def("getTexCoord", (ofVec2f(ofVboMesh::*)(int)) &ofVboMesh::getTexCoord)
         //.def("removeTexCoord", (void(ofVboMesh::*)(int)) &ofVboMesh::removeTexCoord)
         .def("clearTexCoords", (void(ofVboMesh::*)(void)) &ofVboMesh::clearTexCoords)
         .def("getIndex", (ofIndexType(ofVboMesh::*)(int)) &ofVboMesh::getTexCoord)
         .def("addIndex", (void(ofVboMesh::*)(ofIndexType)) &ofVboMesh::addIndex)
         //.def("removeIndex", (void(ofVboMesh::*)(int)) &ofVboMesh::removeIndex)
         .def("setIndex", (void(ofVboMesh::*)(int,ofIndexType)) &ofVboMesh::setIndex)
         .def("clearIndices", (void(ofVboMesh::*)(void)) &ofVboMesh::clearIndices)
         .def("addTriangle", (void(ofVboMesh::*)(ofIndexType,ofIndexType,ofIndexType)) &ofVboMesh::addTriangle)
         .def("getNumVertices", (int(ofVboMesh::*)(void)) &ofVboMesh::getNumVertices)
         .def("getNumColors", (int(ofVboMesh::*)(void)) &ofVboMesh::getNumColors)
         .def("getNumNormals", (int(ofVboMesh::*)(void)) &ofVboMesh::getNumNormals)
         .def("getNumTexCoords", (int(ofVboMesh::*)(void)) &ofVboMesh::getNumTexCoords)
         .def("getNumIndices", (int(ofVboMesh::*)(void)) &ofVboMesh::getNumIndices)
         .def("getVerticesPointer", (ofVec3f*(ofVboMesh::*)(void)) &ofVboMesh::getVerticesPointer)
         .def("getColorsPointer", (ofFloatColor*(ofVboMesh::*)(void)) &ofVboMesh::getColorsPointer)
         .def("getNormalsPointer", (ofVec3f*(ofVboMesh::*)(void)) &ofVboMesh::getNormalsPointer)
         .def("getTexCoordsPointer", (ofVec2f*(ofVboMesh::*)(void)) &ofVboMesh::getTexCoordsPointer)
         .def("getIndexPointer", (ofIndexType*(ofVboMesh::*)(void)) &ofVboMesh::getIndexPointer)
         //.def("getVertices", (ofVec3f(ofVboMesh::*)(void)) &ofVboMesh::getVertices)
         //.def("getColors", (ofFloatColor(ofVboMesh::*)(void)) &ofVboMesh::getColors)
         //.def("getNormals", (ofVec3f(ofVboMesh::*)(void)) &ofVboMesh::getNormals)
         //.def("getTexCoords", (ofVec2f(ofVboMesh::*)(void)) &ofVboMesh::getTexCoords)
         //.def("getIndices", (ofIndexType(ofVboMesh::*)(void)) &ofVboMesh::getIndices)
         .def("setName", (void(ofVboMesh::*)(string)) &ofVboMesh::setName)
         .def("haveVertsChanged", (bool(ofVboMesh::*)(void)) &ofVboMesh::haveVertsChanged)
         .def("haveColorsChanged", (bool(ofVboMesh::*)(void)) &ofVboMesh::haveColorsChanged)
         .def("haveNormalsChanged", (bool(ofVboMesh::*)(void)) &ofVboMesh::haveNormalsChanged)
         .def("haveTexCoordsChanged", (bool(ofVboMesh::*)(void)) &ofVboMesh::haveTexCoordsChanged)
         .def("haveIndicesChanged", (bool(ofVboMesh::*)(void)) &ofVboMesh::haveIndicesChanged)
         .def("hasVertices", (bool(ofVboMesh::*)(void)) &ofVboMesh::hasVertices)
         .def("hasColors", (bool(ofVboMesh::*)(void)) &ofVboMesh::hasColors)
         .def("hasNormals", (bool(ofVboMesh::*)(void)) &ofVboMesh::hasNormals)
         .def("hasTexCoords", (bool(ofVboMesh::*)(void)) &ofVboMesh::hasTexCoords)
         .def("hasIndices", (bool(ofVboMesh::*)(void)) &ofVboMesh::hasIndices)
         .def("drawVertices", (void(ofVboMesh::*)(void)) &ofVboMesh::drawVertices)
         .def("drawWireframe", (void(ofVboMesh::*)(void)) &ofVboMesh::drawWireframe)
         .def("drawFaces", (void(ofVboMesh::*)(void)) &ofVboMesh::drawFaces)
         .def("draw", (void(ofVboMesh::*)(void)) &ofVboMesh::draw)
         .def("addVertex", (void(ofVboMesh::*)(const ofVec3f&)) &ofVboMesh::addVertex)
         .def("setVertex", (void(ofVboMesh::*)(int,const ofVec3f&)) &ofVboMesh::setVertex)
         .def("addNormal", (void(ofVboMesh::*)(const ofVec3f&)) &ofVboMesh::addNormal)
         .def("setNormal", (void(ofVboMesh::*)(int,const ofVec3f&)) &ofVboMesh::setNormal)
         .def("addColor", (void(ofVboMesh::*)(const ofFloatColor&)) &ofVboMesh::addColor)
         .def("setColor", (void(ofVboMesh::*)(int,const ofFloatColor&)) &ofVboMesh::setColor)
         .def("addTexCoord", (void(ofVboMesh::*)(const ofVec2f&)) &ofVboMesh::addTexCoord)
         .def("setTexCoord", (void(ofVboMesh::*)(int,const ofVec2f&)) &ofVboMesh::setTexCoord)
         .def("addIndices", (void(ofVboMesh::*)(const ofIndexType*,int)) &ofVboMesh::addIndices),
         //.def("getCentroid", (ofVec3f(ofVboMesh::*)(void)) &ofVboMesh::getCentroid),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofTexture

         class_<ofTexture>("texture")
		 .def(constructor<>())
		 .def("allocate", (void(ofTexture::*)(int,int,int)) &ofTexture::allocate)
		 .def("clear", (void(ofTexture::*)(void)) &ofTexture::clear)
		 .def("loadData", (void(ofTexture::*)(const float*,int,int,int)) &ofTexture::loadData)
		 .def("loadData", &loadDataOLD)
		 //.def("loadData", (void(ofTexture::*)(unsigned short*,int,int,int)) &ofTexture::loadData)
		 .def("loadData", (void(ofTexture::*)(const ofPixels&)) &ofTexture::loadData)
         .def("loadScreenData", (void(ofTexture::*)(int,int,int,int)) &ofTexture::loadScreenData)
		 .def("setAnchorPercent", (void(ofTexture::*)(float,float)) &ofTexture::setAnchorPercent)
		 .def("setAnchorPoint", (void(ofTexture::*)(float,float)) &ofTexture::setAnchorPoint)
		 .def("resetAnchor", (void(ofTexture::*)(void)) &ofTexture::resetAnchor)
         .def("readToPixels", (void(ofTexture::*)(ofPixels&)) &ofTexture::readToPixels)
		 .def("draw", (void(ofTexture::*)(const ofRectangle&)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(const ofPoint&)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(const ofPoint&, float, float)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(float,float)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(float,float,float)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(float,float,float,float)) &ofTexture::draw)
		 .def("draw", (void(ofTexture::*)(float,float,float,float,float)) &ofTexture::draw)
		 //.def("draw", (void(ofTexture::*)(ofPoint,ofPoint,ofPoint,ofPoint)) &ofTexture::draw)
         .def("bAllocated", (bool(ofTexture::*)(void)) &ofTexture::bAllocated)
         .def("getCoordFromPoint", (ofPoint(ofTexture::*)(float,float)) &ofTexture::getCoordFromPoint)
         .def("getCoordFromPercent", (ofPoint(ofTexture::*)(float,float)) &ofTexture::getCoordFromPercent)
         .def("setTextureWrap", (void(ofTexture::*)(GLint,GLint)) &ofTexture::setTextureWrap)
         .def("setTextureMinMagFilter", (void(ofTexture::*)(GLint,GLint)) &ofTexture::setTextureMinMagFilter)
         .def("setCompression", (void(ofTexture::*)(ofTexCompression)) &ofTexture::setCompression)
         .def("isAllocated", (bool(ofTexture::*)(void)) &ofTexture::isAllocated)
         .def("bind", &ofTexture::bind)
         .def("unbind", &ofTexture::unbind)
		 .def("getWidth", &ofTexture::getWidth)
		 .def("getHeight", &ofTexture::getHeight),

         def("getGlInternalFormat", (int(*)(const ofPixels&)) &ofGetGlInternalFormat),
         def("getGlFormatAndType", (void(*)(int,int&,int&)) &ofGetGlFormatAndType),
         def("getImageTypeFromGLType", (ofImage(*)(int)) &ofGetImageTypeFromGLType),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofGLUtils

         def("getGLPolyMode", (GLuint(*)(ofPolyRenderMode)) &ofGetGLPolyMode),
         def("getOFPolyMode", (ofPolyRenderMode(*)(GLuint)) &ofGetOFPolyMode),
         def("getGLPrimitiveMode", (GLuint(*)(ofPolyRenderMode)) &ofGetGLPrimitiveMode),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofLight

         class_<ofLight>("light")
		 .def(constructor<>())
         .def(constructor<const ofLight&>())
         .def("destroy", (void(ofLight::*)(void)) &ofLight::destroy)
         .def("enable", (void(ofLight::*)(void)) &ofLight::enable)
         .def("disable", (void(ofLight::*)(void)) &ofLight::disable)
         .def("getIsEnabled", (bool(ofLight::*)(void)) &ofLight::getIsEnabled)
         .def("setDirectional", (void(ofLight::*)(void)) &ofLight::setDirectional)
         .def("getIsDirectional", (bool(ofLight::*)(void)) &ofLight::getIsDirectional)
         .def("setSpotlight", (void(ofLight::*)(float,float)) &ofLight::setSpotlight)
         .def("getIsSpotlight", (bool(ofLight::*)(void)) &ofLight::getIsSpotlight)
         .def("setSpotlightCutOff", (void(ofLight::*)(float)) &ofLight::setSpotlightCutOff)
         .def("setSpotConcentration", (void(ofLight::*)(float)) &ofLight::setSpotConcentration)
         .def("setPointLight", (void(ofLight::*)(void)) &ofLight::setPointLight)
         .def("getIsPointLight", (bool(ofLight::*)(void)) &ofLight::getIsPointLight)
         .def("setAttenuation", (void(ofLight::*)(float,float,float)) &ofLight::setAttenuation)
         .def("getType", (int(ofLight::*)(void)) &ofLight::getType)
         .def("setAmbientColor", (void(ofLight::*)(const ofFloatColor&)) &ofLight::setAmbientColor)
         .def("setDiffuseColor", (void(ofLight::*)(const ofFloatColor&)) &ofLight::setDiffuseColor)
         .def("setSpecularColor", (void(ofLight::*)(const ofFloatColor&)) &ofLight::setSpecularColor)
         .def("getAmbientColor", (ofFloatColor(ofLight::*)(void)) &ofLight::getAmbientColor)
         .def("getDiffuseColor", (ofFloatColor(ofLight::*)(void)) &ofLight::getDiffuseColor)
         .def("getSpecularColor", (ofFloatColor(ofLight::*)(void)) &ofLight::getSpecularColor)
         .def("getLightID", (int(ofLight::*)(void)) &ofLight::getLightID)
         .def("customDraw", (void(ofLight::*)(void)) &ofLight::customDraw)

         // from ofNode, transform functionality
         .def("getPosition", (ofVec3f(ofLight::*)(void)) &ofLight::getPosition)
         .def("getX", (float(ofLight::*)(void)) &ofLight::getX)
         .def("getY", (float(ofLight::*)(void)) &ofLight::getY)
         .def("getZ", (float(ofLight::*)(void)) &ofLight::getZ)
         .def("getXAxis", (ofVec3f(ofLight::*)(void)) &ofLight::getXAxis)
         .def("getYAxis", (ofVec3f(ofLight::*)(void)) &ofLight::getYAxis)
         .def("getZAxis", (ofVec3f(ofLight::*)(void)) &ofLight::getZAxis)
         .def("getSideDir", (ofVec3f(ofLight::*)(void)) &ofLight::getSideDir)
         .def("getLookAtDir", (ofVec3f(ofLight::*)(void)) &ofLight::getLookAtDir)
         .def("getUpDir", (ofVec3f(ofLight::*)(void)) &ofLight::getUpDir)
         .def("getPitch", (float(ofLight::*)(void)) &ofLight::getPitch)
         .def("getHeading", (float(ofLight::*)(void)) &ofLight::getHeading)
         .def("getRoll", (float(ofLight::*)(void)) &ofLight::getRoll)
         .def("getOrientationQuat", (ofQuaternion(ofLight::*)(void)) &ofLight::getOrientationQuat)
         .def("getOrientationEuler", (ofVec3f(ofLight::*)(void)) &ofLight::getOrientationEuler)
         .def("getScale", (ofVec3f(ofLight::*)(void)) &ofLight::getScale)
         .def("getLocalTransformMatrix", (ofMatrix4x4(ofLight::*)(void)) &ofLight::getLocalTransformMatrix)
         .def("getGlobalTransformMatrix", (ofMatrix4x4(ofLight::*)(void)) &ofLight::getGlobalTransformMatrix)
         .def("getGlobalPosition", (ofVec3f(ofLight::*)(void)) &ofLight::getGlobalPosition)
         .def("getGlobalOrientation", (ofQuaternion(ofLight::*)(void)) &ofLight::getGlobalOrientation)
         .def("setTransformMatrix", (void(ofLight::*)(const ofMatrix4x4&)) &ofLight::setTransformMatrix)
         .def("setPosition", (void(ofLight::*)(float,float,float)) &ofLight::setPosition)
         .def("setPosition", (void(ofLight::*)(const ofVec3f&)) &ofLight::setPosition)
         .def("setGlobalPosition", (void(ofLight::*)(float,float,float)) &ofLight::setGlobalPosition)
         .def("setGlobalPosition", (void(ofLight::*)(const ofVec3f&)) &ofLight::setGlobalPosition)
         .def("setOrientation", (void(ofLight::*)(const ofQuaternion&)) &ofLight::setOrientation)
         .def("setOrientation", (void(ofLight::*)(const ofVec3f&)) &ofLight::setOrientation)
         .def("setGlobalOrientation", (void(ofLight::*)(const ofQuaternion&)) &ofLight::setGlobalOrientation)
         .def("setScale", (void(ofLight::*)(float,float,float)) &ofLight::setScale)
         .def("setScale", (void(ofLight::*)(const ofVec3f&)) &ofLight::setScale)
         .def("move", (void(ofLight::*)(float,float,float)) &ofLight::move)
         .def("move", (void(ofLight::*)(const ofVec3f&)) &ofLight::move)
         .def("truck", (void(ofLight::*)(float)) &ofLight::truck)
         .def("boom", (void(ofLight::*)(float)) &ofLight::boom)
         .def("dolly", (void(ofLight::*)(float)) &ofLight::dolly)
         .def("tilt", (void(ofLight::*)(float)) &ofLight::tilt)
         .def("pan", (void(ofLight::*)(float)) &ofLight::pan)
         .def("roll", (void(ofLight::*)(float)) &ofLight::roll)
         .def("rotate", (void(ofLight::*)(const ofQuaternion&)) &ofLight::rotate)
         .def("rotate", (void(ofLight::*)(float,const ofVec3f&)) &ofLight::rotate)
         .def("rotate", (void(ofLight::*)(float,float,float,float)) &ofLight::rotate)
         .def("rotateAround", (void(ofLight::*)(const ofQuaternion&,const ofVec3f&)) &ofLight::rotateAround)
         .def("rotateAround", (void(ofLight::*)(float,const ofVec3f&,const ofVec3f&)) &ofLight::rotateAround)
         .def("lookAt", (void(ofLight::*)(const ofVec3f&,ofVec3f)) &ofLight::lookAt)
         .def("lookAt", (void(ofLight::*)(ofNode&,const ofVec3f&)) &ofLight::lookAt)
         .def("orbit", (void(ofLight::*)(float,float,float,const ofVec3f&)) &ofLight::orbit)
         .def("orbit", (void(ofLight::*)(float,float,float,ofNode&)) &ofLight::orbit),

         def("enableLighting", (void(*)(void)) &ofEnableLighting),
         def("disableLighting", (void(*)(void)) &ofDisableLighting),
         def("enableSeparateSpecularLight", (void(*)(void)) &ofEnableSeparateSpecularLight),
         def("disableSeparateSpecularLight", (void(*)(void)) &ofDisableSeparateSpecularLight),
         def("getLightingEnabled", (bool(*)(void)) &ofGetLightingEnabled),

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section utils [ofDirectory, ofHttpResponse, ofFileDialogResult, ofLogError, ofLogWarning, ofSystemUtils,
         ///                    ofBuffer, ofFile, ofLogNotice, ofFileUtils, ofFilePath, ofHttpRequest, ofLogVerbose, ofLog,
         ///                    ofPtr, ofUtils, ofThread, ofLogFatalError, ofURLFileLoader]

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofDirectory

         class_<ofDirectory>("directory")
		 .def(constructor<>())
         .def(constructor<string>())
         .def("open", (void(ofDirectory::*)(string)) &ofDirectory::open)
         .def("close", (void(ofDirectory::*)(void)) &ofDirectory::close)
         .def("create", (bool(ofDirectory::*)(bool)) &ofDirectory::create)
         .def("exists", (bool(ofDirectory::*)(void)) &ofDirectory::exists)
         .def("path", (string(ofDirectory::*)(void)) &ofDirectory::path)
         //.def("canRead", (bool(ofDirectory::*)(void)) &ofDirectory::canRead)
         //.def("canWrite", (bool(ofDirectory::*)(void)) &ofDirectory::canWrite)
         //.def("canExecute", (bool(ofDirectory::*)(void)) &ofDirectory::canExecute)
         .def("isDirectory", (bool(ofDirectory::*)(void)) &ofDirectory::isDirectory)
         .def("isHidden", (bool(ofDirectory::*)(void)) &ofDirectory::isHidden)
         .def("setWriteable", (void(ofDirectory::*)(bool)) &ofDirectory::setWriteable)
         .def("setReadOnly", (void(ofDirectory::*)(bool)) &ofDirectory::setReadOnly)
         .def("setExecutable", (void(ofDirectory::*)(bool)) &ofDirectory::setExecutable)
         .def("setShowHidden", (void(ofDirectory::*)(bool)) &ofDirectory::setShowHidden)
         .def("copyTo", (bool(ofDirectory::*)(string,bool,bool)) &ofDirectory::copyTo)
         .def("moveTo", (bool(ofDirectory::*)(string,bool,bool)) &ofDirectory::moveTo)
         .def("renameTo", (bool(ofDirectory::*)(string,bool,bool)) &ofDirectory::renameTo)
         .def("remove", (bool(ofDirectory::*)(bool)) &ofDirectory::remove)
         .def("allowExt", (void(ofDirectory::*)(string)) &ofDirectory::allowExt)
         .def("listDir", (int(ofDirectory::*)(string)) &ofDirectory::listDir)
         .def("listDir", (int(ofDirectory::*)(void)) &ofDirectory::listDir)
         .def("getName", (string(ofDirectory::*)(unsigned int)) &ofDirectory::getName)
         .def("getPath", (string(ofDirectory::*)(unsigned int)) &ofDirectory::getPath)
         .def("getFile", (ofFile(ofDirectory::*)(unsigned int,ofFile)) &ofDirectory::getFile)
         .def("getFiles", (ofFile(ofDirectory::*)(void)) &ofDirectory::getFiles)
         .def("getShowHidden", (bool(ofDirectory::*)(void)) &ofDirectory::getShowHidden)
         .def("reset", (void(ofDirectory::*)(void)) &ofDirectory::reset)
         .def("sort", (void(ofDirectory::*)(void)) &ofDirectory::sort)
         .def("size", (unsigned int(ofDirectory::*)(void)) &ofDirectory::size)
         .def("numFiles", (int(ofDirectory::*)(void)) &ofDirectory::numFiles)
         .def("createDirectory", (bool(*)(string,bool,bool)) &ofDirectory::createDirectory)
         .def("isDirectoryEmpty", (bool(*)(string,bool)) &ofDirectory::isDirectoryEmpty)
         .def("doesDirectoryExist", (bool(*)(string,bool)) &ofDirectory::doesDirectoryExist)
         .def("removeDirectory", (bool(*)(string,bool,bool)) &ofDirectory::removeDirectory)
         //.def("getOriginalDirectory", (string(*)(void)) &ofDirectory::getOriginalDirectory)
         .def("getFile", (ofFile(ofDirectory::*)(unsigned int,ofFile)) &ofDirectory::getFile),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofHttpResponse

         class_<ofHttpResponse>("httpResponse")
		 .def(constructor<>())
         .def(constructor<ofHttpRequest,const ofBuffer&,int,string>())
         .def(constructor<ofHttpRequest,int,string>())
         .def_readonly("request", &ofHttpResponse::request)
		 .def_readonly("data", &ofHttpResponse::data)
         .def_readonly("status", &ofHttpResponse::status)
		 .def_readonly("error", &ofHttpResponse::error),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFileDialogResult

         class_<ofFileDialogResult>("fileDialogResult")
		 .def(constructor<>())
         .def("getName", (string(ofFileDialogResult::*)(void)) &ofFileDialogResult::getName)
         .def("getPath", (string(ofFileDialogResult::*)(void)) &ofFileDialogResult::getPath)
         .def_readonly("filePath", &ofFileDialogResult::filePath)
		 .def_readonly("fileName", &ofFileDialogResult::fileName)
         .def_readonly("bSuccess", &ofFileDialogResult::bSuccess),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofSystemUtils

         def("systemAlertDialog", (void(*)(string)) &ofSystemAlertDialog),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofBuffer

         class_<ofBuffer>("buffer")
		 .def(constructor<>())
         .def(constructor<const char*,int>())
         .def(constructor<const ofBuffer&>())
         .def("set", (void(ofBuffer::*)(const char*,int)) &ofBuffer::set)
         .def("set", (bool(ofBuffer::*)(istream&)) &ofBuffer::set)
         .def("writeTo", (bool(ofBuffer::*)(ostream&)) &ofBuffer::writeTo)
         .def("clear", (void(ofBuffer::*)(void)) &ofBuffer::clear)
         .def("allocate", (void(ofBuffer::*)(long)) &ofBuffer::allocate)
         .def("setBinaryBuffer", (char(ofBuffer::*)(int,char)) &ofBuffer::setBinaryBuffer)
         .def("getBinaryBuffer", (char(ofBuffer::*)(int)) &ofBuffer::getBinaryBuffer)
         .def("getBinaryBuffer", (char*(ofBuffer::*)(void)) &ofBuffer::getBinaryBuffer)
         .def("getText", (string(ofBuffer::*)(void)) &ofBuffer::getText)
         .def("size", (long(ofBuffer::*)(void)) &ofBuffer::size)
         .def("getNextLine", (string(ofBuffer::*)(void)) &ofBuffer::getNextLine)
         .def("getFirstLine", (string(ofBuffer::*)(void)) &ofBuffer::getFirstLine)
         .def("isLastLine", (bool(ofBuffer::*)(void)) &ofBuffer::isLastLine)
         .def("resetLineReader", (void(ofBuffer::*)(void)) &ofBuffer::resetLineReader),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFile

         class_<ofFile>("file")
		 .def(constructor<>())
         .def(constructor<const ofFile&>())
         .def("open", &openFile) // file:open("test/test.txt")
         .def("close", (void(ofFile::*)(void)) &ofFile::close)
         .def("create", (bool(ofFile::*)(void)) &ofFile::create)
         .def("exists", (bool(ofFile::*)(void)) &ofFile::exists)
         .def("path", (string(ofFile::*)(void)) &ofFile::path)
         .def("getExtension", (string(ofFile::*)(void)) &ofFile::getExtension)
         .def("getFileName", (string(ofFile::*)(void)) &ofFile::getFileName)
         .def("getBaseName", (string(ofFile::*)(void)) &ofFile::getBaseName)
         .def("getEnclosingDirectory", (string(ofFile::*)(void)) &ofFile::getEnclosingDirectory)
         .def("getAbsolutePath", (string(ofFile::*)(void)) &ofFile::getAbsolutePath)
         .def("canRead", (bool(ofFile::*)(void)) &ofFile::canRead)
         .def("canWrite", (bool(ofFile::*)(void)) &ofFile::canWrite)
         .def("canExecute", (bool(ofFile::*)(void)) &ofFile::canExecute)
         .def("isFile", (bool(ofFile::*)(void)) &ofFile::isFile)
         .def("isLink", (bool(ofFile::*)(void)) &ofFile::isLink)
         .def("isDirectory", (bool(ofFile::*)(void)) &ofFile::isDirectory)
         .def("isDevice", (bool(ofFile::*)(void)) &ofFile::isDevice)
         .def("isHidden", (bool(ofFile::*)(void)) &ofFile::isHidden)
         .def("setWriteable", (void(ofFile::*)(bool)) &ofFile::setWriteable)
         .def("setReadOnly", (void(ofFile::*)(bool)) &ofFile::setReadOnly)
         .def("setExecutable", (void(ofFile::*)(bool)) &ofFile::setExecutable)
         .def("copyTo", (bool(ofFile::*)(string,bool,bool)) &ofFile::copyTo)
         .def("moveTo", (bool(ofFile::*)(string,bool,bool)) &ofFile::moveTo)
         .def("renameTo", (bool(ofFile::*)(string,bool,bool)) &ofFile::renameTo)
         .def("remove", (bool(ofFile::*)(bool)) &ofFile::remove)
         .def("getSize", (uint64_t(ofFile::*)(void)) &ofFile::getSize)
         .def("readToBuffer", (ofBuffer(ofFile::*)(void)) &ofFile::readToBuffer)
         .def("writeFromBuffer", (bool(ofFile::*)(ofBuffer)) &ofFile::writeFromBuffer)
         .def("copyFromTo", (bool(*)(string,string,bool,bool)) &ofFile::copyFromTo)
         .def("moveFromTo", (bool(*)(string,string,bool,bool)) &ofFile::moveFromTo)
         .def("doesFileExist", (bool(*)(string,bool)) &ofFile::moveFromTo)
         .def("removeFile", (bool(*)(string,bool)) &ofFile::removeFile),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFileUtils

         def("bufferFromFile", &ofBufferFromFile),
         def("bufferToFile", &ofBufferToFile),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofHttpRequest

         class_<ofHttpRequest>("httpRequest")
		 .def(constructor<>())
         .def(constructor<string,string,bool>())
         .def("getID", (int(ofHttpRequest::*)(void)) &ofHttpRequest::getID)
         .def_readonly("url", &ofHttpRequest::url)
         .def_readonly("name", &ofHttpRequest::name)
         .def_readonly("saveTo", &ofHttpRequest::saveTo),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofUtils

         def("getElapsedTimeMillis", (int(*)(void)) &ofGetElapsedTimeMillis),
         def("getElapsedTimeMicros", (unsigned long(*)(void)) &ofGetElapsedTimeMicros),
         def("getElapsedTimef", (float(*)(void)) &ofGetElapsedTimef),
         //def("getFrameNum", (int(*)(void)) &ofGetFrameNum),
         def("getSeconds", (int(*)(void)) &ofGetSeconds),
		 def("getMinutes", (int(*)(void)) &ofGetMinutes),
		 def("getHours", (int(*)(void)) &ofGetHours),
         def("launchBrowser", &ofLaunchBrowser),
         def("getVersionInfo", &ofGetVersionInfo),
         def("toInt", (int(*)(const string&)) &ofToInt),
         def("toFloat", (float(*)(const string&)) &ofToFloat),
         def("saveScreen", &ofSaveScreen),
         //def("saveFrame", &ofSaveFrame),
         def("splitString", (vector<string>(*)(const string&, const string&, bool)) &ofSplitString),
         def("getYear", (int(*)(void)) &ofGetYear),
		 def("getMonth", (int(*)(void)) &ofGetMonth),
		 def("getDay", (int(*)(void)) &ofGetDay),
		 def("getWeekday", (int(*)(void)) &ofGetWeekday),
         def("resetElapsedTimeCounter", (void(*)(void)) &ofResetElapsedTimeCounter),
         def("getUnixTime", (unsigned int(*)(void)) &ofGetUnixTime),
         def("getSystemTime", (unsigned long(*)(void)) &ofGetSystemTime),
         def("getSystemTimeMicros", (unsigned long(*)(void)) &ofGetSystemTimeMicros),
         def("getTimestampString", (string(*)(void)) &ofGetTimestampString),
		 def("getTimestampString", (string(*)(string)) &ofGetTimestampString),
         def("toChar", (char(*)(const string&)) &ofToChar),
		 def("toBool", (bool(*)(const string&)) &ofToBool),
		 def("toBinary", (string(*)(const string&)) &ofToBinary),
		 def("toBinary", (string(*)(const char*)) &ofToBinary),
		 def("binaryToInt", (int(*)(const string&)) &ofBinaryToInt),
		 def("binaryToChar", (char(*)(const string&)) &ofBinaryToChar),
		 def("binaryToFloat", (float(*)(const string&)) &ofBinaryToFloat),
		 def("binaryToString", (string(*)(const string&)) &ofBinaryToString),
		 def("joinString", (string(*)(vector<string>, const string&)) &ofJoinString),
		 def("stringReplace", (void(*)(string&, string, string)) &ofStringReplace),
		 def("isStringInString", (bool(*)(string, string)) &ofIsStringInString),
		 def("getFrameRate", &ofGetFrameRate),
		 //def("setFrameRate", &ofSetFrameRate),
		 def("sleepMillis", &ofSleepMillis),
		 def("getLastFrameTime", &ofGetLastFrameTime),
		 def("getFrameNum", &ofGetFrameNum),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofThread

         class_<ofThread>("thread")
		 .def(constructor<>())
         .def("isThreadRunning", (bool(ofThread::*)(void)) &ofThread::isThreadRunning)
         .def("startThread", (void(ofThread::*)(bool,bool)) &ofThread::startThread)
         .def("lock", (void(ofThread::*)(void)) &ofThread::lock)
         .def("unlock", (void(ofThread::*)(void)) &ofThread::unlock)
         .def("stopThread", (void(ofThread::*)(bool)) &ofThread::stopThread)
         .def("waitForThread", (void(ofThread::*)(bool)) &ofThread::waitForThread),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofURLFileLoader

         class_<ofURLFileLoader>("URLFileLoader")
		 .def(constructor<>())
         .def("get", (ofHttpResponse(ofURLFileLoader::*)(string)) &ofURLFileLoader::get)
         .def("getAsync", (int(ofURLFileLoader::*)(string,string)) &ofURLFileLoader::getAsync)
         .def("saveTo", (ofHttpResponse(ofURLFileLoader::*)(string,string)) &ofURLFileLoader::saveTo)
         .def("saveAsync", (int(ofURLFileLoader::*)(string,string)) &ofURLFileLoader::saveAsync)
         .def("remove", (void(ofURLFileLoader::*)(int)) &ofURLFileLoader::remove)
         .def("clear", (void(ofURLFileLoader::*)(void)) &ofURLFileLoader::clear),

         def("loadURL", (ofHttpResponse(*)(string)) &ofLoadURL),
         def("loadURLAsync", (int(*)(string,string)) &ofLoadURLAsync),
         def("saveURLTo", (ofHttpResponse(*)(string,string)) &ofSaveURLTo),
         def("saveURLAsync", (int(*)(string,string)) &ofSaveURLAsync),
         def("removeURLRequest", (void(*)(int)) &ofRemoveURLRequest),
         def("removeAllURLRequests", (void(*)(void)) &ofRemoveAllURLRequests),

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section Video [ofVideoPlayer, ofVideoGrabber]


         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVideoPlayer

         class_<ofVideoPlayer>("videoPlayer")
		 .def(constructor<>())
		 .def("loadMovie", (bool(ofVideoPlayer::*)(string)) &ofVideoPlayer::loadMovie)
		 .def("closeMovie", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::closeMovie)
		 .def("close", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::close)
		 .def("update", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::update)
		 .def("idleMovie", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::idleMovie)
		 .def("play", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::play)
		 .def("stop", (void(ofVideoPlayer::*)(void)) &ofVideoPlayer::stop)
		 .def("isFrameNew", &ofVideoPlayer::isFrameNew)
		 .def("getPixels", (unsigned char*(ofVideoPlayer::*)(void)) &ofVideoPlayer::getPixels)
		 .def("getPosition", &ofVideoPlayer::getPosition)
		 .def("getSpeed", &ofVideoPlayer::getSpeed)
		 .def("getDuration", &ofVideoPlayer::getDuration)
		 .def("getIsMovieDone", &ofVideoPlayer::getIsMovieDone)
		 .def("setPosition", (void(ofVideoPlayer::*)(float)) &ofVideoPlayer::setPosition)
		 .def("setVolume", (void(ofVideoPlayer::*)(int)) &ofVideoPlayer::setVolume)
		 .def("setLoopState", &ofVideoPlayer::setLoopState)
		 .def("getLoopState", &ofVideoPlayer::getLoopState)
		 .def("setSpeed", (void(ofVideoPlayer::*)(float)) &ofVideoPlayer::setSpeed)
		 .def("setFrame", (void(ofVideoPlayer::*)(int)) &ofVideoPlayer::setFrame)
		 .def("setUseTexture", &ofVideoPlayer::setUseTexture)
		 .def("getTextureReference", &ofVideoPlayer::getTextureReference)
		 .def("draw", (void(ofVideoPlayer::*)(float,float)) &ofVideoPlayer::draw)
		 .def("draw", (void(ofVideoPlayer::*)(float,float,float,float)) &ofVideoPlayer::draw)
		 .def("draw", (void(ofVideoPlayer::*)(const ofPoint&)) &ofVideoPlayer::draw)
		 .def("draw", (void(ofVideoPlayer::*)(const ofRectangle&)) &ofVideoPlayer::draw)
		 .def("setAnchorPercent", (void(ofVideoPlayer::*)(float,float)) &ofVideoPlayer::setAnchorPercent)
		 .def("setAnchorPoint", (void(ofVideoPlayer::*)(float,float)) &ofVideoPlayer::setAnchorPoint)
		 .def("resetAnchor", &ofVideoPlayer::resetAnchor)
		 .def("setPaused", (void(ofVideoPlayer::*)(bool)) &ofVideoPlayer::setPaused)
		 .def("getCurrentFrame", &ofVideoPlayer::getCurrentFrame)
		 .def("getTotalNumFrames", &ofVideoPlayer::getTotalNumFrames)
		 .def("firstFrame", &ofVideoPlayer::firstFrame)
		 .def("nextFrame", &ofVideoPlayer::nextFrame)
		 .def("previousFrame", &ofVideoPlayer::previousFrame)
		 .def("getHeight", &ofVideoPlayer::getHeight)
		 .def("getWidth", &ofVideoPlayer::getWidth)
		 .def("isPaused", &ofVideoPlayer::isPaused)
		 .def("isLoaded", &ofVideoPlayer::isLoaded)
		 .def("isPlaying", &ofVideoPlayer::isPlaying)
		 .def_readonly("width", &ofVideoPlayer::width)
		 .def_readonly("height", &ofVideoPlayer::height),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofVideoGrabber

         // LIMITED, ofVideoGrabber NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM
         // &
         // MANAGED FROM GUI (video tracking module) & FROM gamuza LIVE CODING FUNCTIONS (ga. module)


		 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section graphics [ofPath, ofImage, ofFloatImage, ofPixels, ofGraphics, ofPixelUtils, ofTrueTypeFont, ofTTFCharacter, ofPolyline, ofTessellator, ofRendererCollection]

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofPath

         class_<ofPath>("path")
		 .def(constructor<>())
		 .def("clear", (void(ofPath::*)(void)) &ofPath::clear)
         .def("newSubPath", (void(ofPath::*)(void)) &ofPath::newSubPath)
         .def("close", (void(ofPath::*)(void)) &ofPath::close)
         .def("lineTo", (void(ofPath::*)(const ofPoint&)) &ofPath::lineTo)
         .def("lineTo", (void(ofPath::*)(float,float,float)) &ofPath::lineTo)
         .def("moveTo", (void(ofPath::*)(const ofPoint&)) &ofPath::moveTo)
         .def("moveTo", (void(ofPath::*)(float,float,float)) &ofPath::moveTo)
         .def("curveTo", (void(ofPath::*)(const ofPoint&)) &ofPath::curveTo)
         .def("curveTo", (void(ofPath::*)(float,float)) &ofPath::curveTo)
         .def("curveTo", (void(ofPath::*)(float,float,float)) &ofPath::curveTo)
         .def("bezierTo", (void(ofPath::*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofPath::bezierTo)
         .def("bezierTo", (void(ofPath::*)(float,float,float,float,float,float)) &ofPath::bezierTo)
         .def("bezierTo", (void(ofPath::*)(float,float,float,float,float,float,float,float,float)) &ofPath::bezierTo)
         .def("quadBezierTo", (void(ofPath::*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofPath::quadBezierTo)
         .def("quadBezierTo", (void(ofPath::*)(float,float,float,float,float,float)) &ofPath::quadBezierTo)
         .def("quadBezierTo", (void(ofPath::*)(float,float,float,float,float,float,float,float,float)) &ofPath::quadBezierTo)
         .def("arc", (void(ofPath::*)(const ofPoint&,float,float,float,float)) &ofPath::arc)
         .def("arc", (void(ofPath::*)(float,float,float,float,float,float)) &ofPath::arc)
         .def("arc", (void(ofPath::*)(float,float,float,float,float,float,float)) &ofPath::arc)
         .def("setPolyWindingMode", (void(ofPath::*)(ofPolyWindingMode)) &ofPath::setPolyWindingMode)
         .def("setFilled", (void(ofPath::*)(bool)) &ofPath::setFilled)
         .def("setStrokeWidth", (void(ofPath::*)(float)) &ofPath::setStrokeWidth)
         .def("setColor", (void(ofPath::*)(const ofColor&)) &ofPath::setColor)
         .def("setHexColor", (void(ofPath::*)(int)) &ofPath::setHexColor)
         .def("setFillColor", (void(ofPath::*)(const ofColor&)) &ofPath::setFillColor)
         .def("setFillHexColor", (void(ofPath::*)(int)) &ofPath::setFillHexColor)
         .def("setStrokeColor", (void(ofPath::*)(const ofColor&)) &ofPath::setStrokeColor)
         .def("setStrokeHexColor", (void(ofPath::*)(int)) &ofPath::setStrokeHexColor)
         .def("getWindingMode", (ofPolyWindingMode(ofPath::*)(void)) &ofPath::getWindingMode)
         .def("isFilled", (bool(ofPath::*)(void)) &ofPath::isFilled)
         .def("getFillColor", (ofColor(ofPath::*)(void)) &ofPath::getFillColor)
         .def("getStrokeColor", (ofColor(ofPath::*)(void)) &ofPath::getStrokeColor)
         .def("getStrokeWidth", (float(ofPath::*)(void)) &ofPath::getStrokeWidth)
         .def("hasOutline", (bool(ofPath::*)(void)) &ofPath::hasOutline)
         .def("draw", (void(ofPath::*)(float,float)) &ofPath::draw)
         .def("draw", (void(ofPath::*)(void)) &ofPath::draw)
         //.def("getSubPaths", (ofSubPath(ofPath::*)(void)) &ofPath::getSubPaths)               NOT AVAILABLE
         .def("getOutline", (ofPolyline(ofPath::*)(void)) &ofPath::getOutline)
         .def("getTessellation", (ofMesh(ofPath::*)(void)) &ofPath::getTessellation)
         .def("simplify", (void(ofPath::*)(float)) &ofPath::simplify)
         .def("flagShapeChanged", (void(ofPath::*)(void)) &ofPath::flagShapeChanged)
         //.def("setMode", (void(ofPath::*)(Mode)) &ofPath::setMode)                            NOT AVAILABLE
         .def("setCurveResolution", (void(ofPath::*)(int)) &ofPath::setCurveResolution)
         .def("getCurveResolution", (int(ofPath::*)(void)) &ofPath::getCurveResolution)
         .def("setArcResolution", (void(ofPath::*)(int)) &ofPath::setArcResolution)
         .def("getArcResolution", (int(ofPath::*)(void)) &ofPath::getArcResolution)
         .def("setUseShapeColor", (void(ofPath::*)(bool)) &ofPath::setUseShapeColor)
         .def("getUseShapeColor", (bool(ofPath::*)(void)) &ofPath::getUseShapeColor)
         .def("tessellate", (void(ofPath::*)(void)) &ofPath::tessellate)
         .def("translate", (void(ofPath::*)(const ofPoint&)) &ofPath::translate)
         .def("rotate", (void(ofPath::*)(float,const ofVec3f&)) &ofPath::rotate)
         .def("scale", (void(ofPath::*)(float,float)) &ofPath::scale),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofImage

		 class_<ofImage>("image")
		 .def(constructor<>())
		 .def(constructor<const string&>())
		 .def("allocate", (void(ofImage::*)(int,int,int)) &ofImage::allocate)
		 .def("clear", (void(ofImage::*)(void)) &ofImage::clear)
         .def("clone", (void(ofImage::*)(const ofImage&)) &ofImage::clone)
         .def("setUseTexture", (void(ofImage::*)(bool)) &ofImage::setUseTexture)
         .def("getTextureReference", (ofTexture&(ofImage::*)(void)) &ofImage::getTextureReference)
		 .def("loadImage", (bool(ofImage::*)(string)) &ofImage::loadImage)
         .def("saveImage", (void(ofImage::*)(string, ofImageQualityType)) &ofImage::saveImage)
         .def("saveImageBuffer", (void(ofImage::*)(ofBuffer&, ofImageQualityType)) &ofImage::saveImage)
		 .def("getPixels", (unsigned char*(ofImage::*)(void)) &ofImage::getPixels)
         .def("getPixelsRef", (ofPixels&(ofImage::*)(void)) &ofImage::getPixelsRef)
         .def("setFromPixels", (void(ofImage::*)(const ofPixels&)) &ofImage::setFromPixels)
		 .def("setImageType", (void(ofImage::*)(int)) &ofImage::setImageType)
         .def("resize", (void(ofImage::*)(int,int)) &ofImage::resize)
         .def("grabScreen", (void(ofImage::*)(int,int,int,int)) &ofImage::grabScreen)
         .def("update", (void(ofImage::*)(void)) &ofImage::update)
		 .def("draw", (void(ofImage::*)(float,float)) &ofImage::draw)
		 .def("draw", (void(ofImage::*)(float,float,float,float)) &ofImage::draw)
         .def("getWidth", (float(ofImage::*)(void)) &ofImage::getWidth)
         .def("getHeight", (float(ofImage::*)(void)) &ofImage::getHeight)
		 .def("getColor", (ofColor(ofImage::*)(int,int)) &ofImage::getColor)
		 .def("setColor", (void(ofImage::*)(int,int,ofColor)) &ofImage::setColor)
         .def("setImageType", (void(ofImage::*)(ofImageType)) &ofImage::setImageType)
         .def("crop", (void(ofImage::*)(int,int,int,int)) &ofImage::crop)
         .def("cropFrom", (void(ofImage::*)(ofImage&,int,int,int,int)) &ofImage::cropFrom)
         .def("rotate90", (void(ofImage::*)(int)) &ofImage::rotate90)
		 .def("mirror", (void(ofImage::*)(bool,bool)) &ofImage::mirror)
		 .def("setAnchorPoint", (void(ofImage::*)(float,float)) &ofImage::setAnchorPoint)
         .def("draw", (void(ofImage::*)(const ofRectangle&)) &ofImage::draw)
         .def("draw", (void(ofImage::*)(const ofPoint&,float,float)) &ofImage::draw)
         .def("draw", (void(ofImage::*)(float,float,float)) &ofImage::draw)
         .def("draw", (void(ofImage::*)(const ofPoint&)) &ofImage::draw)
         .def("draw", (void(ofImage::*)(float,float,float,float,float)) &ofImage::draw)
		 .def("bAllocated", (void(ofImage::*)(bool)) &ofImage::bAllocated)
         .def("reloadTexture", (void(ofImage::*)(void)) &ofImage::reloadTexture)
		 .def_readonly("width", &ofImage::width)
		 .def_readonly("height", &ofImage::height)
         .def_readonly("type", &ofImage::type)
		 .def_readonly("bpp", &ofImage::bpp),

         def("loadImage",	(bool(*)(ofPixels&,string)) &ofLoadImage),
         //def("loadImage",	(bool(*)(ofPixels&,const ofBuffer&)) &ofLoadImage),
         //def("loadImage",	(bool(*)(ofTexture&,string)) &ofLoadImage),
         //def("loadImage",	(bool(*)(ofTexture&,const ofBuffer&)) &ofLoadImage),
         def("saveImage",	(void(*)(ofPixels&,string,ofImageQualityType)) &ofSaveImage),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFloatImage

		 class_<ofFloatImage>("floatImage")
		 .def(constructor<>())
		 .def(constructor<const string&>())
		 .def("allocate", (void(ofFloatImage::*)(int,int,int)) &ofFloatImage::allocate)
		 .def("clear", (void(ofFloatImage::*)(void)) &ofFloatImage::clear)
         .def("clone", (void(ofFloatImage::*)(const ofFloatImage&)) &ofFloatImage::clone)
         .def("setUseTexture", (void(ofFloatImage::*)(bool)) &ofFloatImage::setUseTexture)
         .def("getTextureReference", (ofTexture&(ofFloatImage::*)(void)) &ofFloatImage::getTextureReference)
		 .def("loadImage", (bool(ofFloatImage::*)(string)) &ofFloatImage::loadImage)
         .def("saveImage", (void(ofFloatImage::*)(string, ofImageQualityType)) &ofFloatImage::saveImage)
         .def("saveImageBuffer", (void(ofFloatImage::*)(ofBuffer&, ofImageQualityType)) &ofFloatImage::saveImage)
		 .def("getPixels", (unsigned char*(ofFloatImage::*)(void)) &ofFloatImage::getPixels)
         .def("setFromPixels", (void(ofImage::*)(const ofPixels&)) &ofImage::setFromPixels)
		 .def("setImageType", (void(ofFloatImage::*)(int)) &ofFloatImage::setImageType)
         .def("resize", (void(ofFloatImage::*)(int,int)) &ofFloatImage::resize)
         .def("grabScreen", (void(ofFloatImage::*)(int,int,int,int)) &ofFloatImage::grabScreen)
         .def("update", (void(ofFloatImage::*)(void)) &ofFloatImage::update)
		 .def("draw", (void(ofFloatImage::*)(float,float)) &ofFloatImage::draw)
		 .def("draw", (void(ofFloatImage::*)(float,float,float,float)) &ofFloatImage::draw)
         .def("getWidth", (float(ofFloatImage::*)(void)) &ofFloatImage::getWidth)
         .def("getHeight", (float(ofFloatImage::*)(void)) &ofFloatImage::getHeight)
		 .def("getColor", (ofColor(ofFloatImage::*)(int,int)) &ofFloatImage::getColor)
		 .def("setColor", (void(ofFloatImage::*)(int,int,ofColor)) &ofFloatImage::setColor)
         .def("setImageType", (void(ofFloatImage::*)(ofImageType)) &ofFloatImage::setImageType)
         .def("crop", (void(ofFloatImage::*)(int,int,int,int)) &ofFloatImage::crop)
         .def("cropFrom", (void(ofFloatImage::*)(ofFloatImage&,int,int,int,int)) &ofFloatImage::cropFrom)
         .def("rotate90", (void(ofFloatImage::*)(int)) &ofFloatImage::rotate90)
		 .def("mirror", (void(ofFloatImage::*)(bool,bool)) &ofFloatImage::mirror)
		 .def("setAnchorPoint", (void(ofFloatImage::*)(float,float)) &ofFloatImage::setAnchorPoint)
         .def("draw", (void(ofFloatImage::*)(const ofRectangle&)) &ofFloatImage::draw)
         .def("draw", (void(ofFloatImage::*)(const ofPoint&,float,float)) &ofFloatImage::draw)
         .def("draw", (void(ofFloatImage::*)(float,float,float)) &ofFloatImage::draw)
         .def("draw", (void(ofFloatImage::*)(const ofPoint&)) &ofFloatImage::draw)
         .def("draw", (void(ofFloatImage::*)(float,float,float,float,float)) &ofFloatImage::draw)
		 .def("bAllocated", (void(ofFloatImage::*)(bool)) &ofFloatImage::bAllocated)
         .def("reloadTexture", (void(ofFloatImage::*)(void)) &ofFloatImage::reloadTexture)
		 .def_readonly("width", &ofFloatImage::width)
		 .def_readonly("height", &ofFloatImage::height)
         .def_readonly("type", &ofFloatImage::type)
		 .def_readonly("bpp", &ofFloatImage::bpp),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofPixels

		 class_<ofPixels>("pixels")
		 .def(constructor<>())
		 .def("allocate", (void(ofPixels::*)(int,int,int)) &ofPixels::allocate)
		 .def("set", (void(ofPixels::*)(unsigned char)) &ofPixels::set)
         .def("setFromPixels", (void(ofPixels::*)(const unsigned char*,int,int,int)) &ofPixels::setFromPixels)
         .def("setFromPixels", (void(ofPixels::*)(const unsigned char*,int,int,ofImageType)) &ofPixels::setFromPixels)
         .def("setFromExternalPixels", (void(ofPixels::*)(unsigned char*,int,int,int)) &ofPixels::setFromExternalPixels)
         .def("setFromAlignedPixels", (void(ofPixels::*)(const unsigned char*,int,int,int,int)) &ofPixels::setFromAlignedPixels)
         .def("swapRgb", (void(ofPixels::*)(void)) &ofPixels::swapRgb)
         .def("clear", (void(ofPixels::*)(void)) &ofPixels::clear)
         .def("getPixels", (unsigned char*(ofPixels::*)(void)) &ofPixels::getPixels)
         .def("getPixelIndex", (int(ofPixels::*)(int,int)) &ofPixels::getPixelIndex)
         .def("getColor", (ofColor(ofPixels::*)(int,int)) &ofPixels::getColor)
		 .def("setColor", (void(ofPixels::*)(int,int,ofColor)) &ofPixels::setColor)
         .def("isAllocated", (bool(ofPixels::*)(void)) &ofPixels::isAllocated)
         .def("getWidth", (int(ofPixels::*)(void)) &ofPixels::getWidth)
		 .def("getHeight", (int(ofPixels::*)(void)) &ofPixels::getHeight)
         .def("getBytesPerPixel", (int(ofPixels::*)(void)) &ofPixels::getBytesPerPixel)
         .def("getBitsPerPixel", (int(ofPixels::*)(void)) &ofPixels::getBitsPerPixel)
         .def("getImageType", (ofImageType(ofPixels::*)(void)) &ofPixels::getImageType)

         // from ofPixelUtils, useful here because of the live-coding lua system wrapper
         .def("crop", (void(ofPixels::*)(int,int,int,int)) &ofPixels::crop)
         .def("rotate90", (void(ofPixels::*)(int)) &ofPixels::rotate90)
         .def("mirror", (void(ofPixels::*)(bool,bool)) &ofPixels::mirror)
         .def("resize", (void(ofPixels::*)(int,int)) &ofPixels::resize),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofGraphics

		 def("background",	(void(*)(int)) &background),
		 def("background",	(void(*)(int,int)) &ofBackground),
		 def("background",	(void(*)(int,int,int)) &background),
		 def("background",	(void(*)(int,int,int,int)) &ofBackground),
         // float * ofBgColorPtr(void)              NOT AVAILABLE
         // void ofSetBackgroundAuto(bool)          NOT AVAILABLE
         // bool ofbClearBg()(void)                 NOT AVAILABLE
         def("setCircleResolution", (void(*)(int)) &ofSetCircleResolution),
         def("setRectMode", (void(*)(int)) &ofSetRectMode),                     // of.setCircleResolution(OF_RECTMODE_CENTER || OF_RECTMODE_CORNER)
         def("getRectMode", (ofRectMode(*)(void)) &ofGetRectMode),
         def("rect", (void(*)(float,float,float,float)) &ofRect),
		 def("triangle", (void(*)(float,float,float,float,float,float)) &ofTriangle),
		 def("circle", (void(*)(float,float,float)) &ofCircle),
		 def("ellipse",	(void(*)(float,float,float,float)) &ofEllipse),
         def("line", (void(*)(float,float,float,float)) &ofLine),
         def("curve", (void(*)(float,float,float,float,float,float,float,float)) &ofCurve),
		 def("bezier", (void(*)(float,float,float,float,float,float,float,float)) &ofBezier),
         def("setPolyMode", (void(*)(int)) &ofSetPolyMode),
         def("beginShape", (void(*)(void)) &ofBeginShape),
         def("vertex",	(void(*)(float,float)) &ofVertex),
		 def("curveVertex", (void(*)(float,float)) &ofCurveVertex),
		 def("bezierVertex", (void(*)(float,float,float,float,float,float)) &ofBezierVertex),
		 def("nextContour", (void(*)(bool)) &ofNextContour),
         def("endShape", (void(*)(bool)) &ofEndShape),
         def("noFill", (void(*)(void)) &ofNoFill),
		 def("fill", (void(*)(void)) &ofFill),
         def("setColor", (void(*)(int)) &setColor1),
         def("setColor", (void(*)(int,int)) &setColor2),
         def("setColor", (void(*)(int,int,int)) &ofSetColor),
		 def("setColor", (void(*)(int,int,int,int)) &ofSetColor),
		 def("setHexColor", (void(*)(int)) &ofSetHexColor),
         def("enableAlphaBlending", (void(*)(void)) &ofEnableAlphaBlending),
		 def("disableAlphaBlending", (void(*)(void)) &ofDisableAlphaBlending),
         def("enableSmoothing", (void(*)(void)) &ofEnableSmoothing),
		 def("disableSmoothing", (void(*)(void)) &ofDisableSmoothing),
         def("drawBitmapString", (void(*)(string,float,float)) &ofDrawBitmapString),
         def("rotate", (void(*)(float,float,float,float)) &ofRotate),
         def("rotateX", (void(*)(float)) &ofRotateX),
		 def("rotateY", (void(*)(float)) &ofRotateY),
		 def("rotateZ", (void(*)(float)) &ofRotateZ),
         def("pushStyle", (void(*)(void)) &ofPushStyle),
         def("popStyle", (void(*)(void)) &ofPopStyle),
         def("setStyle", (void(*)(ofStyle)) &ofSetStyle),
         def("getStyle", (void(*)(ofStyle)) &ofGetStyle),
         def("setLineWidth", (void(*)(float)) &ofSetLineWidth),
         def("pushMatrix", (void(*)(void)) &ofPushMatrix),
		 def("popMatrix", (void(*)(void)) &ofPopMatrix),
         def("translate", (void(*)(float,float,float)) &ofTranslate),
		 def("scale", (void(*)(float,float,float)) &ofScale),
         // void ofSetCurrentRenderer(ofPtr< ofBaseRenderer >)              NOT AVAILABLE
         // ofPtr ofGetCurrentRenderer(void)                                NOT AVAILABLE
         // ofPtr ofGetGLRenderer(void)                                     NOT AVAILABLE
         def("beginSaveScreenAsPDF", (void(*)(string,bool,bool,ofRectangle)) &ofBeginSaveScreenAsPDF), // ofBeginSaveScreenAsPDF(filename, bMultipage=false, b3D=false, viewport)
         def("endSaveScreenAsPDF", (void(*)(void)) &ofEndSaveScreenAsPDF),
         def("pushView", (void(*)(void)) &ofPushView),
		 def("popView", (void(*)(void)) &ofPopView),
         def("viewport", (void(*)(ofRectangle)) &ofViewport),
         def("viewport", (void(*)(float,float,float,float,bool)) &ofViewport), // ofViewport(x=0,y=0,width=0,height=0,invertY=true)
         //def("setupScreenPerspective", (void(*)(float,float,ofOrientation,bool,float,float,float)) &ofSetupScreenPerspective),        NOT AVAILABLE
         //def("setupScreenOrtho", (void(*)(float,float,ofOrientation,bool,float,float)) &ofSetupScreenOrtho),                          NOT AVAILABLE
         def("getCurrentViewport", (ofRectangle(*)(void)) &ofGetCurrentViewport),
         def("getViewportWidth", (int(*)(void)) &ofGetViewportWidth),
         def("getViewportHeight", (int(*)(void)) &ofGetViewportHeight),
         //def("orientationToDegrees", (int(*)(ofOrientation)) &ofOrientationToDegrees),                                                NOT AVAILABLE
         //def("setCoordHandedness", (void(*)(ofHandednessType)) &ofSetCoordHandedness),                                                NOT AVAILABLE
         //def("getCoordHandedness", (ofHandednessType(*)(void)) &ofGetCoordHandedness),                                                NOT AVAILABLE
         def("translate", (void(*)(const ofPoint&)) &ofTranslate),
         def("rotate", (void(*)(float)) &ofRotate),
         // def("setupScreen", (void(*)(void)) &ofSetupScreen),                                                                         NOT AVAILABLE
		 def("setCurveResolution", (void(*)(int)) &ofSetCurveResolution),
         def("setSphereResolution", (void(*)(int)) &ofSetSphereResolution),
         def("getFill", (ofFillFlag(*)(void)) &ofGetFill),
         def("setColor", (void(*)(const ofColor&)) &ofSetColor),
         def("setColor", (void(*)(const ofColor&,int)) &ofSetColor),
         def("enableBlendMode", (void(*)(ofBlendMode)) &ofEnableBlendMode),
		 def("disableBlendMode", (void(*)(void)) &ofDisableBlendMode),
         def("enablePointSprites", (void(*)(void)) &ofEnablePointSprites),
		 def("disablePointSprites", (void(*)(void)) &ofDisablePointSprites),
         //def("setPolyMode", (void(*)(ofPolyWindingMode)) &ofSetPolyMode),     NOT AVAILABLE
         //def("setRectMode", (void(*)(ofRectMode)) &ofSetRectMode),            NOT AVAILABLE
         // void ofBackground(int r, int g, int b, int a=255)                   NOT AVAILABLE
         // void ofBackground(int brightness, int alpha=255)                    NOT AVAILABLE
         // void ofBackground(const ofColor &c)                                 NOT AVAILABLE
         // void ofBackgroundHex(int hexColor, int alpha=255)                   NOT AVAILABLE
         // void ofSetBackgroundColor(int r, int g, int b, int a=255)           NOT AVAILABLE
         // void ofSetBackgroundColor(int brightness, int alpha=255)            NOT AVAILABLE
         // void ofSetBackgroundColor(const ofColor &c)                         NOT AVAILABLE
         // void ofSetBackgroundColorHex(int hexColor, int alpha=255)           NOT AVAILABLE
		 def("clear", (void(*)(float,float,float,float)) &ofClear),
         def("clear", (void(*)(float,float)) &ofClear),
		 def("clearAlpha", (void(*)(void)) &ofClearAlpha),
         def("triangle", (void(*)(float,float,float,float,float,float,float,float,float)) &ofTriangle),
         def("triangle", (void(*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofTriangle),
         def("circle", (void(*)(float,float,float,float)) &ofCircle),
         def("circle", (void(*)(const ofPoint&,float)) &ofCircle),
         def("ellipse",	(void(*)(float,float,float,float,float)) &ofEllipse),
         def("ellipse",	(void(*)(const ofPoint&,float,float)) &ofEllipse),
         def("line", (void(*)(float,float,float,float,float,float)) &ofLine),
         def("line", (void(*)(const ofPoint&,const ofPoint&)) &ofLine),
         def("rect", (void(*)(const ofRectangle&)) &ofRect),
         def("rect", (void(*)(const ofPoint&,float,float)) &ofRect),
         def("rect", (void(*)(float,float,float,float,float)) &ofRect),
         // def("curve", (void(*)(float,float,float,float,float,float,float,float,float,float,float,float)) &ofCurve),
         // def("bezier", (void(*)(float,float,float,float,float,float,float,float,float,float,float,float)) &ofBezier),
         //def("vertex", (void(*)(float,float,float)) &ofVertex),
         def("vertex", (void(*)(ofPoint&)) &ofVertex),
         // void ofVertexes(const vector< ofPoint > &polyPoints)                NOT AVAILABLE
         def("curveVertex",	(void(*)(ofPoint&)) &ofCurveVertex),
         // void ofCurveVertexes(const vector< ofPoint > &curvePoints)          NOT AVAILABLE
         def("bezierVertex", (void(*)(const ofPoint&,const ofPoint&,const ofPoint&)) &ofBezierVertex),
         def("bezierVertex", (void(*)(float,float,float,float,float,float,float,float,float)) &ofBezierVertex),
         def("sphere", (void(*)(float,float,float,float)) &ofSphere),
         def("sphere", (void(*)(float,float,float)) &ofSphere),
         def("sphere", (void(*)(const ofPoint&,float)) &ofSphere),
         def("sphere", (void(*)(float)) &ofSphere),
         def("box", (void(*)(float,float,float,float)) &ofBox),
         def("box", (void(*)(float,float,float)) &ofBox),
         def("box", (void(*)(const ofPoint&,float)) &ofBox),
         def("box", (void(*)(float)) &ofBox),
         // void ofSetDrawBitmapMode(ofDrawBitmapMode mode)                     NOT AVAILABLE

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofPixelsUtils

         // NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM


         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofTrueTypeFont

		 class_<ofTrueTypeFont>("trueTypeFont")
		 .def(constructor<>())
         .def("loadFont", &loadFont2)
		 .def("loadFont", &loadFont4)
         .def("loadFont", &loadFont5)
         .def("loadFont", &loadFont7)
		 .def("getLineHeight", (float(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getLineHeight)
		 .def("setLineHeight", (void(ofTrueTypeFont::*)(float)) &ofTrueTypeFont::setLineHeight)
         .def("stringWidth", (float(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::stringWidth)
		 .def("stringHeight", (float(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::stringHeight)
         .def("getStringBoundingBox", (ofRectangle(ofTrueTypeFont::*)(string,float,float)) &ofTrueTypeFont::getStringBoundingBox)
         .def("drawString", (void(ofTrueTypeFont::*)(string,float,float)) &ofTrueTypeFont::drawString)
         .def("drawStringAsShapes", (void(ofTrueTypeFont::*)(string,float,float)) &ofTrueTypeFont::drawStringAsShapes)
         .def("isLoaded", (bool(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::isLoaded)
         .def("isAntiAliased", (bool(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::isAntiAliased)
         .def("hasFullCharacterSet", (bool(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::hasFullCharacterSet)
         .def("getSize", (int(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getSize)
		 .def("getLetterSpacing", (float(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getLetterSpacing)
		 .def("setLetterSpacing", (void(ofTrueTypeFont::*)(float)) &ofTrueTypeFont::setLetterSpacing)
		 .def("getSpaceSize", (float(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getSpaceSize)
		 .def("setSpaceSize", (void(ofTrueTypeFont::*)(float)) &ofTrueTypeFont::setSpaceSize)
		 .def("getNumCharacters", (int(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getNumCharacters)
         .def("getCharacterAsPoints", (ofPath(ofTrueTypeFont::*)(int)) &ofTrueTypeFont::getCharacterAsPoints)
		 .def("getStringAsPoints", (vector<ofPath>(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::getStringAsPoints)
         .def("bind", (void(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::bind)
         .def("unbind", (void(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::unbind),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofPolyLine

		 class_<ofPolyline>("polyline")
		 .def(constructor<>())
         .def("clear", (void(ofPolyline::*)(void)) &ofPolyline::clear)
         .def("addVertex", (void(ofPolyline::*)(float,float,float)) &ofPolyline::addVertex)
         .def("addVertexes", (void(ofPolyline::*)(const vector<ofPoint>&)) &ofPolyline::addVertexes)
         .def("lineTo", (void(ofPolyline::*)(const ofPoint&)) &ofPolyline::lineTo)
         .def("lineTo", (void(ofPolyline::*)(float,float,float)) &ofPolyline::lineTo)
         .def("arc", (void(ofPolyline::*)(const ofPoint&,float,float,float,float,int)) &ofPolyline::arc)
         .def("arc", (void(ofPolyline::*)(float,float,float,float,float,float,int)) &ofPolyline::arc)
         .def("arc", (void(ofPolyline::*)(float,float,float,float,float,float,float,int)) &ofPolyline::arc)
         .def("curveTo", (void(ofPolyline::*)(const ofPoint&,int)) &ofPolyline::curveTo)
         .def("curveTo", (void(ofPolyline::*)(float,float,float,int)) &ofPolyline::curveTo) // float x, float y, float z, int curveResolution
         .def("bezierTo", (void(ofPolyline::*)(const ofPoint&,const ofPoint&,const ofPoint&,int)) &ofPolyline::bezierTo)
         .def("bezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,int)) &ofPolyline::bezierTo)
         .def("bezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,float,float,float,int)) &ofPolyline::bezierTo)
         .def("quadBezierTo", (void(ofPolyline::*)(const ofPoint&,const ofPoint&,const ofPoint&,int)) &ofPolyline::quadBezierTo)
         .def("quadBezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,int)) &ofPolyline::quadBezierTo)
         .def("quadBezierTo", (void(ofPolyline::*)(float,float,float,float,float,float,float,float,float,int)) &ofPolyline::quadBezierTo)
         .def("getSmoothed", (ofPolyline(ofPolyline::*)(int,float)) &ofPolyline::getSmoothed) // int smoothingSize
         .def("getResampledBySpacing", (ofPolyline(ofPolyline::*)(float)) &ofPolyline::getResampledBySpacing) // float spacing
         .def("getResampledByCount", (ofPolyline(ofPolyline::*)(int)) &ofPolyline::getResampledByCount) // int count
         .def("getBoundingBox", (ofRectangle(ofPolyline::*)(void)) &ofPolyline::getBoundingBox)
         .def("getClosestPoint", (ofPoint(ofPolyline::*)(const ofPoint&,unsigned int*)) &ofPolyline::getClosestPoint)
         .def("simplify", (void(ofPolyline::*)(float)) &ofPolyline::simplify)
         .def("size", (size_t(ofPolyline::*)(void)) &ofPolyline::size)
         .def("resize", (void(ofPolyline::*)(size_t)) &ofPolyline::resize)
         .def("setClosed", (void(ofPolyline::*)(bool)) &ofPolyline::setClosed)
         .def("isClosed", (bool(ofPolyline::*)(void)) &ofPolyline::isClosed)
         .def("close", (void(ofPolyline::*)(void)) &ofPolyline::close)
         .def("hasChanged", (bool(ofPolyline::*)(void)) &ofPolyline::hasChanged)
         .def("getVertices", (vector<ofPoint>&(ofPolyline::*)(void)) &ofPolyline::getVertices)
         .def("getPerimeter", (float(ofPolyline::*)(void)) &ofPolyline::getPerimeter)
         .def("draw", (void(ofPolyline::*)(void)) &ofPolyline::draw),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofTessellator

         class_<ofTessellator>("tessellator")
		 .def(constructor<>())
         .def(constructor<const ofTessellator&>()),
         // void ofTessellator::tessellateToMesh(const vector< ofPolyline > &src, ofPolyWindingMode polyWindingMode, ofMesh &dstmesh, bool bIs2D=false)
         //.def("tessellateToMesh", (float(ofTessellator::*)(const ofPolyline&, ofPolyWindingMode, ofMesh&,bool)) &ofTessellator::tessellateToMesh),
         // void ofTessellator::tessellateToPolylines(const vector< ofPolyline > &src, ofPolyWindingMode polyWindingMode, vector< ofPolyline > &dstpoly, bool bIs2D=false)
         // void ofTessellator::tessellateToPolylines(const ofPolyline &src, ofPolyWindingMode polyWindingMode, vector< ofPolyline > &dstpoly, bool bIs2D=false)

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofRendererCollection

         // NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM


         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section types [ofColor, ofStyle, ofTypes, ofRectangle, ofPoint]

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofColor

		 class_<ofColor>("color")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float>())
         .def(constructor<ofColor const&>())
         .def(constructor<ofColor const&,float>())
		 .def(constructor<float,float>())
         .def("getHex", (int(ofColor::*)(void)) &ofColor::getHex)
         .def("clamp", (ofColor(ofColor::*)(void)) &ofColor::clamp)
         .def("invert", (ofColor(ofColor::*)(void)) &ofColor::invert)
         .def("normalize", (ofColor(ofColor::*)(void)) &ofColor::normalize)
         .def("getClamped", (ofColor(ofColor::*)(void)) &ofColor::getClamped)
         .def("getInverted", (ofColor(ofColor::*)(void)) &ofColor::getInverted)
         .def("getNormalized", (ofColor(ofColor::*)(void)) &ofColor::getNormalized)
         .def("getHue", (float(ofColor::*)(void)) &ofColor::getHue)
		 .def("getSaturation", (float(ofColor::*)(void)) &ofColor::getSaturation)
		 .def("getBrightness", (float(ofColor::*)(void)) &ofColor::getBrightness)
         .def("getLightness", (float(ofColor::*)(void)) &ofColor::getLightness)
         .def("setHue", (void(ofColor::*)(float)) &ofColor::setHue)
		 .def("setSaturation", (void(ofColor::*)(float)) &ofColor::setSaturation)
		 .def("setBrightness", (void(ofColor::*)(float)) &ofColor::setBrightness)
         .def("setHsb", (void(ofColor::*)(float,float,float,float)) &ofColor::setHsb)
         .def("setHsb", (void(ofColor::*)(float,float,float)) &ofColor::setHsb)
		 .def("set", (void(ofColor::*)(float,float,float,float)) &ofColor::set)
		 .def("set", (void(ofColor::*)(float,float)) &ofColor::set)
         .def("set", (void(ofColor::*)(ofColor const&)) &ofColor::set)
		 .def("setHex", (void(ofColor::*)(int,float)) &ofColor::setHex)
		 .def("lerp", (ofColor(ofColor::*)(const ofColor&, float)) &ofColor::lerp)
         .def("getLerped", (ofColor(ofColor::*)(const ofColor&, float)) &ofColor::getLerped)
		 .def("getHsb", (void(ofColor::*)(float&,float&,float&)) &ofColor::getHsb)
         .def_readonly("r", &ofColor::r)
		 .def_readonly("g", &ofColor::g)
		 .def_readonly("b", &ofColor::b)
		 .def_readonly("a", &ofColor::a),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofFloatColor

		 class_<ofFloatColor>("floatColor")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float>())
         .def(constructor<ofFloatColor const&>())
         .def(constructor<ofFloatColor const&,float>())
		 .def(constructor<float,float>())
         .def("getHex", (int(ofFloatColor::*)(void)) &ofFloatColor::getHex)
         .def("clamp", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::clamp)
         .def("invert", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::invert)
         .def("normalize", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::normalize)
         .def("getClamped", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::getClamped)
         .def("getInverted", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::getInverted)
         .def("getNormalized", (ofFloatColor(ofFloatColor::*)(void)) &ofFloatColor::getNormalized)
         .def("getHue", (float(ofFloatColor::*)(void)) &ofFloatColor::getHue)
		 .def("getSaturation", (float(ofFloatColor::*)(void)) &ofFloatColor::getSaturation)
		 .def("getBrightness", (float(ofFloatColor::*)(void)) &ofFloatColor::getBrightness)
         .def("getLightness", (float(ofFloatColor::*)(void)) &ofFloatColor::getLightness)
         .def("setHue", (void(ofFloatColor::*)(float)) &ofFloatColor::setHue)
		 .def("setSaturation", (void(ofFloatColor::*)(float)) &ofFloatColor::setSaturation)
		 .def("setBrightness", (void(ofFloatColor::*)(float)) &ofFloatColor::setBrightness)
         .def("setHsb", (void(ofFloatColor::*)(float,float,float,float)) &ofFloatColor::setHsb)
         .def("setHsb", (void(ofFloatColor::*)(float,float,float)) &ofFloatColor::setHsb)
		 .def("set", (void(ofFloatColor::*)(float,float,float,float)) &ofFloatColor::set)
		 .def("set", (void(ofFloatColor::*)(float,float)) &ofFloatColor::set)
         .def("set", (void(ofFloatColor::*)(ofFloatColor const&)) &ofFloatColor::set)
		 .def("setHex", (void(ofFloatColor::*)(int,float)) &ofFloatColor::setHex)
		 .def("lerp", (ofFloatColor(ofFloatColor::*)(const ofFloatColor&, float)) &ofFloatColor::lerp)
         .def("getLerped", (ofFloatColor(ofFloatColor::*)(const ofFloatColor&, float)) &ofFloatColor::getLerped)
		 .def("getHsb", (void(ofFloatColor::*)(float&,float&,float&)) &ofFloatColor::getHsb)
		 //.def("fromHsb", (ofFloatColor(ofFloatColor::*)(float,float,float,float)) &ofFloatColor::fromHsb)    NOT AVAILABLE
		 //.def("fromHex", (ofFloatColor(ofFloatColor::*)(int,float)) &ofFloatColor::fromHex)                  NOT AVAILABLE
         .def_readonly("r", &ofFloatColor::r)
		 .def_readonly("g", &ofFloatColor::g)
		 .def_readonly("b", &ofFloatColor::b)
		 .def_readonly("a", &ofFloatColor::a),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofShortColor

		 class_<ofShortColor>("shortColor")
		 .def(constructor<>())
		 .def(constructor<float,float,float,float>())
         .def(constructor<ofShortColor const&>())
         .def(constructor<ofShortColor const&,float>())
		 .def(constructor<float,float>())
         .def("getHex", (int(ofShortColor::*)(void)) &ofShortColor::getHex)
         .def("clamp", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::clamp)
         .def("invert", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::invert)
         .def("normalize", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::normalize)
         .def("getClamped", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::getClamped)
         .def("getInverted", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::getInverted)
         .def("getNormalized", (ofShortColor(ofShortColor::*)(void)) &ofShortColor::getNormalized)
         .def("getHue", (float(ofShortColor::*)(void)) &ofShortColor::getHue)
		 .def("getSaturation", (float(ofShortColor::*)(void)) &ofShortColor::getSaturation)
		 .def("getBrightness", (float(ofShortColor::*)(void)) &ofShortColor::getBrightness)
         .def("getLightness", (float(ofShortColor::*)(void)) &ofShortColor::getLightness)
         .def("setHue", (void(ofShortColor::*)(float)) &ofShortColor::setHue)
		 .def("setSaturation", (void(ofShortColor::*)(float)) &ofShortColor::setSaturation)
		 .def("setBrightness", (void(ofShortColor::*)(float)) &ofShortColor::setBrightness)
         .def("setHsb", (void(ofShortColor::*)(float,float,float,float)) &ofShortColor::setHsb)
         .def("setHsb", (void(ofShortColor::*)(float,float,float)) &ofShortColor::setHsb)
		 .def("set", (void(ofShortColor::*)(float,float,float,float)) &ofShortColor::set)
		 .def("set", (void(ofShortColor::*)(float,float)) &ofShortColor::set)
         .def("set", (void(ofShortColor::*)(ofShortColor const&)) &ofShortColor::set)
		 .def("setHex", (void(ofShortColor::*)(int,float)) &ofShortColor::setHex)
		 .def("lerp", (ofShortColor(ofShortColor::*)(const ofShortColor&, float)) &ofShortColor::lerp)
         .def("getLerped", (ofShortColor(ofShortColor::*)(const ofShortColor&, float)) &ofShortColor::getLerped)
		 .def("getHsb", (void(ofShortColor::*)(float&,float&,float&)) &ofShortColor::getHsb)
		 //.def("fromHsb", (ofShortColor(ofShortColor::*)(float,float,float,float)) &ofShortColor::fromHsb)    NOT AVAILABLE
		 //.def("fromHex", (ofShortColor(ofShortColor::*)(int,float)) &ofShortColor::fromHex)                  NOT AVAILABLE
         .def_readonly("r", &ofShortColor::r)
		 .def_readonly("g", &ofShortColor::g)
		 .def_readonly("b", &ofShortColor::b)
		 .def_readonly("a", &ofShortColor::a),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofStyle

         class_<ofStyle>("style")
		 .def(constructor<>())
         .def_readwrite("color", &ofStyle::color)
         .def_readwrite("polyMode", &ofStyle::polyMode)
         .def_readwrite("rectMode", &ofStyle::rectMode)
         .def_readwrite("bFill", &ofStyle::bFill)
         // .def_readwrite("blending", &ofStyle::blending)                              NOT AVAILABLE
         .def_readwrite("smoothing", &ofStyle::smoothing)
         .def_readwrite("circleResolution", &ofStyle::circleResolution)
         .def_readwrite("lineWidth", &ofStyle::lineWidth)
         .def_readwrite("bgColor", &ofStyle::bgColor)
         .def_readwrite("drawBitmapMode", &ofStyle::drawBitmapMode)
         .def_readwrite("blendingMode", &ofStyle::blendingMode)
         .def_readwrite("sphereResolution", &ofStyle::sphereResolution)
         .def_readwrite("curveResolution", &ofStyle::curveResolution),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofTypes

         ////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofRectangle

         class_<ofRectangle>("rectangle")
		 .def(constructor<>())
         .def(constructor<float,float,float,float>())
         //.def(constructor<ofPoint,float,float>())                                     NOT AVAILABLE
		 .def(constructor<ofRectangle const&>())
		 .def("set", (void(ofRectangle::*)(float,float,float,float)) &ofRectangle::set)
         .def("set", (void(ofRectangle::*)(ofPoint,float,float)) &ofRectangle::set)
		 .def("set", (void(ofRectangle::*)(const ofRectangle&)) &ofRectangle::set)
		 .def("setFromCenter", (void(ofRectangle::*)(float,float,float,float)) &ofRectangle::setFromCenter)
         .def("setFromCenter", (void(ofRectangle::*)(ofPoint,float,float)) &ofRectangle::setFromCenter)
         .def("getCenter", (ofPoint(ofRectangle::*)(void)) &ofRectangle::getCenter)
         .def("inside", (bool(ofRectangle::*)(ofPoint)) &ofRectangle::inside)
		 .def("inside", (bool(ofRectangle::*)(float,float)) &ofRectangle::inside)
		 .def_readonly("x", &ofRectangle::x)
		 .def_readonly("y", &ofRectangle::y)
		 .def_readonly("width", &ofRectangle::width)
		 .def_readonly("height", &ofRectangle::height),

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofPoint


         // NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM
         //
         // Use instead ofVec2f --> in live coding of.vec2f()


         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section events [ofKeyEventArgs, ofAudioEventArgs, ofCoreEvents, ofEventArgs, ofEvent, ofMouseEventArgs, ofResizeEventArgs, ofEvents, ofEventUtils]


         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofEvents

         def("getMousePressed", &ofGetMousePressed),
         def("getKeyPressed", &ofGetKeyPressed),
         def("getMouseX", &ofGetMouseX),
         def("getMouseY", &ofGetMouseY),
         def("getPreviousMouseX", &ofGetPreviousMouseX),
         def("getPreviousMouseY", &ofGetPreviousMouseY),


         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section sound [ofSoundPlayer, ofSoundStream]

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofSoundPlayer

         def("soundUpdate", &ofSoundUpdate),
         def("soundGetSpectrum", &ofSoundGetSpectrum),

		 class_<ofSoundPlayer>("soundPlayer")
		 .def(constructor<>())
		 .def("loadSound", (void(ofSoundPlayer::*)(string,bool)) &ofSoundPlayer::loadSound)
		 .def("unloadSound", (void(ofSoundPlayer::*)(void)) &ofSoundPlayer::unloadSound)
		 .def("play", (void(ofSoundPlayer::*)(void)) &ofSoundPlayer::play)
		 .def("stop", (void(ofSoundPlayer::*)(void)) &ofSoundPlayer::stop)
		 .def("setVolume", (void(ofSoundPlayer::*)(float)) &ofSoundPlayer::setVolume)
		 .def("setPan", (void(ofSoundPlayer::*)(float)) &ofSoundPlayer::setPan)
		 .def("setSpeed", (void(ofSoundPlayer::*)(float)) &ofSoundPlayer::setSpeed)
		 .def("setPaused", (void(ofSoundPlayer::*)(bool)) &ofSoundPlayer::setPaused)
		 .def("setLoop", (void(ofSoundPlayer::*)(bool)) &ofSoundPlayer::setLoop)
		 .def("setMultiPlay", (void(ofSoundPlayer::*)(bool)) &ofSoundPlayer::setMultiPlay)
		 .def("setPosition", (void(ofSoundPlayer::*)(float)) &ofSoundPlayer::setPosition)
		 .def("getPosition", (float(ofSoundPlayer::*)(void)) &ofSoundPlayer::getPosition)
		 .def("getIsPlaying", (bool(ofSoundPlayer::*)(void)) &ofSoundPlayer::getIsPlaying)
		 .def("getSpeed", (float(ofSoundPlayer::*)(void)) &ofSoundPlayer::getSpeed)
		 .def("getPan", (float(ofSoundPlayer::*)(void)) &ofSoundPlayer::getPan)
         //.def("setPositionMS", (void(ofSoundPlayer::*)(int)) &ofSoundPlayer::setPositionMS)
         //.def("getPositionMS", (int(ofSoundPlayer::*)(void)) &ofSoundPlayer::getPositionMS)
         //.def_readonly("isStreaming", &ofSoundPlayer::isStreaming)
		 //.def_readonly("bMultiPlay", &ofSoundPlayer::bMultiPlay)
		 //.def_readonly("bLoop", &ofSoundPlayer::bLoop)
		 //.def_readonly("bLoadedOk", &ofSoundPlayer::bLoadedOk)
         //.def_readonly("bPaused", &ofSoundPlayer::bPaused)
		 //.def_readonly("pan", &ofSoundPlayer::pan)
		 //.def_readonly("volume", &ofSoundPlayer::volume)
		 //.def_readonly("speed", &ofSoundPlayer::speed)
         //.def_readonly("length", &ofSoundPlayer::length)

         ///////////////////////////////////////////////////////////////////////////////////
		 /// \section ofSoundStream

         // LIMITED, ofSoundStream NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM
         // &
         // MANAGED FROM GUI (audio module) & FROM gamuza LIVE CODING FUNCTIONS (ga. module)


         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section application [ofAppBaseWindow, ofDragInfo, ofAppRunner, ofBaseApp]

         // NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM, DUE TO THE HYBRID LIVE-CODING NATURE OF GAMUZA


         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		 /// \section serial

         // NOT AVAILABLE IN GAMUZA 0.3 IN THE LIVE CODING SYSTEM, MANAGED FROM GUI (arduino module)


         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		];

        //////////////////////////////////////////////////////////////
		///////////////////////////////
		/// OpenFrameworks 007 addons api wrapper
		module(lua, "ofx")
		[

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFX3DMODELLOADER

         ///////////////////////////////
         // ofx3DBaseLoader
         class_<ofx3DBaseLoader>("BaseLoader3D")
         .def(constructor<>())
         .def("loadModel", (void(ofx3DBaseLoader::*)(string,float)) &ofx3DBaseLoader::loadModel)
         .def("loadModel", (void(ofx3DBaseLoader::*)(string)) &ofx3DBaseLoader::loadModel)
         .def("draw", (void(ofx3DBaseLoader::*)(void)) &ofx3DBaseLoader::draw)
         .def_readonly("hasTexture", &ofx3DBaseLoader::hasTexture),

         ///////////////////////////////
         // ofx3DModelLoader
         class_<ofx3DModelLoader>("ModelLoader3D")
         .def(constructor<>())
         .def("loadModel", (void(ofx3DModelLoader::*)(string,float)) &ofx3DModelLoader::loadModel)
         .def("setPosition", (void(ofx3DModelLoader::*)(float,float,float)) &ofx3DModelLoader::setPosition)
         .def("setScale", (void(ofx3DModelLoader::*)(float,float,float)) &ofx3DModelLoader::setScale)
         .def("setRotation", (void(ofx3DModelLoader::*)(int,float,float,float,float)) &ofx3DModelLoader::setRotation)
         .def("draw", (void(ofx3DModelLoader::*)(void)) &ofx3DModelLoader::draw)
         .def_readonly("rotAngle", &ofx3DModelLoader::rotAngle)
         .def_readonly("rotAxis", &ofx3DModelLoader::rotAxis)
         .def_readonly("scale", &ofx3DModelLoader::scale)
         .def_readonly("pos", &ofx3DModelLoader::pos)
         .def_readonly("numRotations", &ofx3DModelLoader::numRotations)
         .def_readonly("model", &ofx3DModelLoader::model),

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXASSIMPMODELLOADER
         /*class_<ofxAssimpModelLoader>("assimpModelLoader")
         .def(constructor<>())
         .def("loadModel", (bool(ofxAssimpModelLoader::*)(string,bool)) &ofxAssimpModelLoader::loadModel)
         .def("loadModel", (bool(ofxAssimpModelLoader::*)(ofBuffer&,bool,const char*)) &ofxAssimpModelLoader::loadModel)
         .def("createEmptyModel", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::createEmptyModel)
         .def("createLightsFromAiModel", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::createLightsFromAiModel)
         .def("optimizeScene", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::optimizeScene)
         .def("clear", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::clear)
         .def("setScale", (void(ofxAssimpModelLoader::*)(float,float,float)) &ofxAssimpModelLoader::setScale)
         .def("setPosition", (void(ofxAssimpModelLoader::*)(float,float,float)) &ofxAssimpModelLoader::setPosition)
         .def("setRotation", (void(ofxAssimpModelLoader::*)(int,float,float,float,float)) &ofxAssimpModelLoader::setRotation)
         .def("setScaleNomalization", (void(ofxAssimpModelLoader::*)(bool)) &ofxAssimpModelLoader::setScaleNomalization)
         .def("setNormalizationFactor", (void(ofxAssimpModelLoader::*)(float)) &ofxAssimpModelLoader::setNormalizationFactor)
         .def("getAnimationCount", (unsigned int(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getAnimationCount)
         .def("setAnimation", (void(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::setAnimation)
         .def("setNormalizedTime", (void(ofxAssimpModelLoader::*)(float)) &ofxAssimpModelLoader::setNormalizedTime)
         .def("setTime", (void(ofxAssimpModelLoader::*)(float)) &ofxAssimpModelLoader::setTime)
         .def("getDuration", (float(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getDuration)
         .def("getMeshNames", (vector<string>(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getMeshNames)
         .def("getNumMeshes", (int(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getNumMeshes)
         .def("getMesh", (ofMesh(ofxAssimpModelLoader::*)(string)) &ofxAssimpModelLoader::getMesh)
         .def("getMesh", (ofMesh(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getMesh)
         .def("getCurrentAnimatedMesh", (ofMesh(ofxAssimpModelLoader::*)(string)) &ofxAssimpModelLoader::getCurrentAnimatedMesh)
         .def("getCurrentAnimatedMesh", (ofMesh(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getCurrentAnimatedMesh)
         .def("getMaterialForMesh", (ofMaterial(ofxAssimpModelLoader::*)(string)) &ofxAssimpModelLoader::getMaterialForMesh)
         .def("getMaterialForMesh", (ofMaterial(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getMaterialForMesh)
         .def("getTextureForMesh", (ofTexture(ofxAssimpModelLoader::*)(string)) &ofxAssimpModelLoader::getTextureForMesh)
         .def("getTextureForMesh", (ofTexture(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getTextureForMesh)
         .def("drawWireframe", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::drawWireframe)
         .def("drawFaces", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::drawFaces)
         .def("drawVertices", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::drawVertices)
         .def("enableTextures", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::enableTextures)
         .def("disableTextures", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::disableTextures)
         .def("enableNormals", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::enableNormals)
         .def("enableMaterials", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::enableMaterials)
         .def("disableNormals", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::disableNormals)
         .def("enableColors", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::enableColors)
         .def("disableColors", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::disableColors)
         .def("disableMaterials", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::disableMaterials)
         .def("draw", (void(ofxAssimpModelLoader::*)(ofPolyRenderMode)) &ofxAssimpModelLoader::draw)
         .def("getPosition", (ofPoint(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getPosition)
         .def("getSceneCenter", (ofPoint(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getSceneCenter)
         .def("getNormalizedScale", (float(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getNormalizedScale)
         .def("getScale", (ofPoint(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getScale)
         .def("getSceneMin", (ofPoint(ofxAssimpModelLoader::*)(bool)) &ofxAssimpModelLoader::getSceneMin)
         .def("getSceneMax", (ofPoint(ofxAssimpModelLoader::*)(bool)) &ofxAssimpModelLoader::getSceneMax)
         .def("getNumRotations", (int(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getNumRotations)
         .def("getRotationAxis", (ofPoint(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getRotationAxis)
         .def("getRotationAngle", (float(ofxAssimpModelLoader::*)(int)) &ofxAssimpModelLoader::getRotationAngle)
         .def("calculateDimensions", (void(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::calculateDimensions)
         .def("getAssimpScene", (const aiScene*(ofxAssimpModelLoader::*)(void)) &ofxAssimpModelLoader::getAssimpScene),
            */
         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXNETWORK

         ///////////////////////////////
         // ofxTCPClient
         class_<ofxTCPClient>("TCPClient")
         .def(constructor<>())
         .def("setVerbose", (void(ofxTCPClient::*)(bool)) &ofxTCPClient::setVerbose)
         .def("setup", (bool(ofxTCPClient::*)(string,int,bool)) &ofxTCPClient::setup)
         .def("setMessageDelimiter", (void(ofxTCPClient::*)(string)) &ofxTCPClient::setMessageDelimiter)
         .def("close", (bool(ofxTCPClient::*)(void)) &ofxTCPClient::close)
         .def("send", (bool(ofxTCPClient::*)(string)) &ofxTCPClient::send)
         .def("sendRaw", (bool(ofxTCPClient::*)(string)) &ofxTCPClient::sendRaw)
         .def("getNumReceivedBytes", (int(ofxTCPClient::*)(void)) &ofxTCPClient::getNumReceivedBytes)
         .def("sendRawBytes", (bool(ofxTCPClient::*)(const char*, const int)) &ofxTCPClient::sendRawBytes)
         .def("receive", (string(ofxTCPClient::*)(void)) &ofxTCPClient::receive)
         .def("receiveRaw", (string(ofxTCPClient::*)(void)) &ofxTCPClient::receiveRaw)
         .def("receiveRawBytes", (int(ofxTCPClient::*)(const char*,int)) &ofxTCPClient::receiveRawBytes)
         .def("isConnected", (bool(ofxTCPClient::*)(void)) &ofxTCPClient::isConnected)
         .def("getPort", (int(ofxTCPClient::*)(void)) &ofxTCPClient::getPort)
         .def("getIP", (string(ofxTCPClient::*)(void)) &ofxTCPClient::getIP)
         .def("setup", (bool(ofxTCPClient::*)(int,bool)) &ofxTCPClient::setup)
         .def_readonly("TCPClient", &ofxTCPClient::TCPClient),

         ///////////////////////////////
         // ofxUDPManager
         class_<ofxUDPManager>("UDPManager")
         .def(constructor<>())
         .def("Close", (bool(ofxUDPManager::*)(void)) &ofxUDPManager::Close)
         .def("Create", (bool(ofxUDPManager::*)(void)) &ofxUDPManager::Create)
         .def("Connect", (bool(ofxUDPManager::*)(const char*,unsigned short)) &ofxUDPManager::Connect)
         .def("ConnectMcast", (bool(ofxUDPManager::*)(const char*,unsigned short)) &ofxUDPManager::ConnectMcast)
         .def("Bind", (bool(ofxUDPManager::*)(unsigned short)) &ofxUDPManager::Bind)
         .def("BindMcast", (bool(ofxUDPManager::*)(const char*,unsigned short)) &ofxUDPManager::BindMcast)
         .def("Send", (int(ofxUDPManager::*)(const char*,const int)) &ofxUDPManager::Send)
         .def("SendAll", (int(ofxUDPManager::*)(const char*,const int)) &ofxUDPManager::SendAll)
         .def("Receive", (int(ofxUDPManager::*)(const char*,const int)) &ofxUDPManager::Receive)
         .def("SetTimeoutSend", (void(ofxUDPManager::*)(int)) &ofxUDPManager::SetTimeoutSend)
         .def("SetTimeoutReceive", (void(ofxUDPManager::*)(int)) &ofxUDPManager::SetTimeoutReceive)
         .def("GetTimeoutSend", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetTimeoutSend)
         .def("GetTimeoutReceive", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetTimeoutReceive)
         .def("GetRemoteAddr", (bool(ofxUDPManager::*)(const char*)) &ofxUDPManager::GetRemoteAddr)
         .def("SetReceiveBufferSize", (bool(ofxUDPManager::*)(int)) &ofxUDPManager::SetReceiveBufferSize)
         .def("SetSendBufferSize", (bool(ofxUDPManager::*)(int)) &ofxUDPManager::SetSendBufferSize)
         .def("GetReceiveBufferSize", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetReceiveBufferSize)
         .def("GetSendBufferSize", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetSendBufferSize)
         .def("SetReuseAddress", (bool(ofxUDPManager::*)(bool)) &ofxUDPManager::SetReuseAddress)
         .def("SetEnableBroadcast", (bool(ofxUDPManager::*)(bool)) &ofxUDPManager::SetEnableBroadcast)
         .def("SetNonBlocking", (bool(ofxUDPManager::*)(bool)) &ofxUDPManager::SetNonBlocking)
         .def("GetMaxMsgSize", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetMaxMsgSize)
         .def("GetTTL", (int(ofxUDPManager::*)(void)) &ofxUDPManager::GetTTL)
         .def("SetTTL", (bool(ofxUDPManager::*)(int)) &ofxUDPManager::SetTTL),

         ///////////////////////////////
         // ofxTCPManager
         class_<ofxTCPManager>("TCPManager")
         .def(constructor<>())
         .def("Close", (bool(ofxTCPManager::*)(void)) &ofxTCPManager::Close)
         .def("Create", (bool(ofxTCPManager::*)(void)) &ofxTCPManager::Create)
         .def("Listen", (bool(ofxTCPManager::*)(int)) &ofxTCPManager::Listen)
         .def("Connect", (bool(ofxTCPManager::*)(const char*,unsigned short)) &ofxTCPManager::Connect)
         .def("Bind", (bool(ofxTCPManager::*)(unsigned short)) &ofxTCPManager::Bind)
         .def("Accept", (bool(ofxTCPManager::*)(ofxTCPManager&)) &ofxTCPManager::Accept)
         .def("Send", (int(ofxTCPManager::*)(const char*,const int)) &ofxTCPManager::Send)
         .def("SendAll", (int(ofxTCPManager::*)(const char*,const int)) &ofxTCPManager::SendAll)
         .def("Receive", (int(ofxTCPManager::*)(const char*,const int)) &ofxTCPManager::Receive)
         .def("ReceiveAll", (int(ofxTCPManager::*)(const char*,const int)) &ofxTCPManager::ReceiveAll)
         .def("Write", (int(ofxTCPManager::*)(const char*,const int)) &ofxTCPManager::Write)
         .def("GetRemoteAddr", &ofxTCPManager::GetRemoteAddr)
         .def("GetInetAddr", &ofxTCPManager::GetInetAddr)
         .def("SetTimeoutSend", (void(ofxTCPManager::*)(int)) &ofxTCPManager::SetTimeoutSend)
         .def("SetTimeoutReceive", (void(ofxTCPManager::*)(int)) &ofxTCPManager::SetTimeoutReceive)
         .def("SetTimeoutAccept", (void(ofxTCPManager::*)(int)) &ofxTCPManager::SetTimeoutAccept)
         .def("GetTimeoutSend", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetTimeoutSend)
         .def("GetTimeoutReceive", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetTimeoutReceive)
         .def("GetTimeoutAccept", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetTimeoutAccept)
         .def("SetReceiveBufferSize", (bool(ofxTCPManager::*)(int)) &ofxTCPManager::SetReceiveBufferSize)
         .def("SetSendBufferSize", (bool(ofxTCPManager::*)(int)) &ofxTCPManager::SetSendBufferSize)
         .def("GetReceiveBufferSize", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetReceiveBufferSize)
         .def("GetSendBufferSize", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetSendBufferSize)
         .def("GetMaxConnections", (int(ofxTCPManager::*)(void)) &ofxTCPManager::GetMaxConnections)
         .def("SetNonBlocking", (bool(ofxTCPManager::*)(bool)) &ofxTCPManager::SetNonBlocking)
         .def("CheckHost", (bool(ofxTCPManager::*)(const char*)) &ofxTCPManager::CheckHost)
         .def("CleanUp", (void(ofxTCPManager::*)(void)) &ofxTCPManager::CleanUp),

         ///////////////////////////////
         // ofxTCPServer
         class_<ofxTCPServer>("TCPServer")
         .def(constructor<>())
         .def("setVerbose", (void(ofxTCPServer::*)(bool)) &ofxTCPServer::setVerbose)
         .def("setup", (bool(ofxTCPServer::*)(int,bool)) &ofxTCPServer::setup)
         .def("setMessageDelimiter", (void(ofxTCPServer::*)(string)) &ofxTCPServer::setMessageDelimiter)
         .def("close", (bool(ofxTCPServer::*)(void)) &ofxTCPServer::close)
         .def("disconnectClient", (bool(ofxTCPServer::*)(int)) &ofxTCPServer::disconnectClient)
         .def("getNumClients", (int(ofxTCPServer::*)(void)) &ofxTCPServer::getNumClients)
         .def("getLastID", (int(ofxTCPServer::*)(void)) &ofxTCPServer::getLastID)
         .def("getPort", (int(ofxTCPServer::*)(void)) &ofxTCPServer::getPort)
         .def("isConnected", (bool(ofxTCPServer::*)(void)) &ofxTCPServer::isConnected)
         .def("getClientPort", (int(ofxTCPServer::*)(int)) &ofxTCPServer::getClientPort)
         .def("getClientIP", (string(ofxTCPServer::*)(int)) &ofxTCPServer::getClientIP)
         .def("isClientSetup", (bool(ofxTCPServer::*)(int)) &ofxTCPServer::isClientSetup)
         .def("isClientConnected", (bool(ofxTCPServer::*)(int)) &ofxTCPServer::isClientConnected)
         .def("send", (bool(ofxTCPServer::*)(int,string)) &ofxTCPServer::send)
         .def("sendToAll", (bool(ofxTCPServer::*)(string)) &ofxTCPServer::sendToAll)
         .def("sendRawBytes", (bool(ofxTCPServer::*)(int, const char*, const int)) &ofxTCPServer::sendRawBytes)
         .def("sendRawBytesToAll", (bool(ofxTCPServer::*)(const char*, const int)) &ofxTCPServer::sendRawBytesToAll)
         .def("getNumReceivedBytes", (int(ofxTCPServer::*)(int)) &ofxTCPServer::getNumReceivedBytes)
         .def("receive", (string(ofxTCPServer::*)(int)) &ofxTCPServer::receive)
         .def("receiveRawBytes", (void(ofxTCPServer::*)(int, const char*, int)) &ofxTCPServer::receiveRawBytes)
         .def_readonly("TCPServer", &ofxTCPServer::TCPServer)
		 .def_readonly("TCPConnections", &ofxTCPServer::TCPConnections),

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXVECTORGRAPHICS

         class_<ofxVectorGraphics>("vectorGraphics")
         .def(constructor<>())
         .def("beginEPS", (void(ofxVectorGraphics::*)(string,int,int,int,int)) &ofxVectorGraphics::beginEPS)
         .def("endEPS", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::endEPS)
         .def("enableDraw", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::enableDraw)
         .def("disableDraw", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::disableDraw)
         .def("enableCenterRect", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::enableCenterRect)
         .def("disableCenterRect", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::disableCenterRect)
         .def("fill", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::fill)
         .def("noFill", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::noFill)
         .def("setLineWidth", (void(ofxVectorGraphics::*)(float)) &ofxVectorGraphics::setLineWidth)
         .def("setColor", (void(ofxVectorGraphics::*)(int,int,int)) &ofxVectorGraphics::setColor)
         .def("setColor", (void(ofxVectorGraphics::*)(int)) &ofxVectorGraphics::setColor)
         .def("changeColor", (void(ofxVectorGraphics::*)(float,float,float)) &ofxVectorGraphics::changeColor)
         .def("rect", (void(ofxVectorGraphics::*)(float,float,float,float)) &ofxVectorGraphics::rect)
         .def("triangle", (void(ofxVectorGraphics::*)(float,float,float,float,float,float)) &ofxVectorGraphics::triangle)
         .def("circle", (void(ofxVectorGraphics::*)(float,float,float)) &ofxVectorGraphics::circle)
         .def("ellipse", (void(ofxVectorGraphics::*)(float,float,float,float)) &ofxVectorGraphics::ellipse)
         .def("line", (void(ofxVectorGraphics::*)(float,float,float,float)) &ofxVectorGraphics::line)
         .def("arc", (void(ofxVectorGraphics::*)(float,float,float,float,float)) &ofxVectorGraphics::arc)
         .def("bezier", (void(ofxVectorGraphics::*)(float,float,float,float,float,float,float,float)) &ofxVectorGraphics::bezier)
         .def("curve", (void(ofxVectorGraphics::*)(float,float,float,float,float,float,float,float)) &ofxVectorGraphics::curve)
         .def("beginShape", (void(ofxVectorGraphics::*)(void)) &ofxVectorGraphics::beginShape)
         .def("polyVertex", (void(ofxVectorGraphics::*)(float,float)) &ofxVectorGraphics::polyVertex)
         .def("bezierVertex", (void(ofxVectorGraphics::*)(float,float,float,float,float,float)) &ofxVectorGraphics::bezierVertex)
         .def("curveVertex", (void(ofxVectorGraphics::*)(float,float)) &ofxVectorGraphics::curveVertex)
         .def("endShape", (void(ofxVectorGraphics::*)(bool)) &ofxVectorGraphics::endShape)
         .def_readonly("creeps", &ofxVectorGraphics::creeps),

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXOPENCV

         ///////////////////////////////
         // ofxCvColorImage

         class_<ofxCvColorImage>("cvColorImage")
         .def(constructor<>())
         .def(constructor<const ofxCvColorImage&>())

         .def("allocate", (void(ofxCvColorImage::*)(int,int)) &ofxCvColorImage::allocate)
         .def("clear", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::clear)
         .def("getWidth", (float(ofxCvColorImage::*)(void)) &ofxCvColorImage::getWidth)
         .def("getHeight", (float(ofxCvColorImage::*)(void)) &ofxCvColorImage::getHeight)
         .def("setUseTexture", (void(ofxCvColorImage::*)(bool)) &ofxCvColorImage::setUseTexture)
         .def("getTextureReference", (ofTexture&(ofxCvColorImage::*)(void)) &ofxCvColorImage::getTextureReference)
         .def("flagImageChanged", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::flagImageChanged)
         .def("setROI", (void(ofxCvColorImage::*)(int,int,int,int)) &ofxCvColorImage::setROI)
         .def("setROI", (void(ofxCvColorImage::*)(const ofRectangle&)) &ofxCvColorImage::setROI)
         .def("getROI", (ofRectangle(ofxCvColorImage::*)(void)) &ofxCvColorImage::getROI)
         .def("resetROI", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::resetROI)
         .def("getIntersectionROI", (ofRectangle(ofxCvColorImage::*)(const ofRectangle&,const ofRectangle&)) &ofxCvColorImage::getIntersectionROI)
         .def("setFromPixels", (void(ofxCvColorImage::*)(const ofPixels&)) &ofxCvColorImage::setFromPixels)
         .def("setRoiFromPixels", (void(ofxCvColorImage::*)(const ofPixels&)) &ofxCvColorImage::setRoiFromPixels)
         .def("updateTexture", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::updateTexture)
         .def("draw", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::draw)
         .def("draw", (void(ofxCvColorImage::*)(float,float,float,float)) &ofxCvColorImage::draw)
         .def("draw", (void(ofxCvColorImage::*)(const ofRectangle&)) &ofxCvColorImage::draw)
         .def("drawROI", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::drawROI)
         .def("drawROI", (void(ofxCvColorImage::*)(float,float,float,float)) &ofxCvColorImage::drawROI)
         .def("setAnchorPercent", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::setAnchorPercent)
         .def("setAnchorPoint", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::setAnchorPoint)
         .def("resetAnchor", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::resetAnchor)
         .def("erode", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::erode)
         .def("dilate", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::dilate)
         .def("blur", (void(ofxCvColorImage::*)(int)) &ofxCvColorImage::blur)
         .def("blurGaussian", (void(ofxCvColorImage::*)(int)) &ofxCvColorImage::blurGaussian)
         .def("invert", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::invert)
         .def("mirror", (void(ofxCvColorImage::*)(bool,bool)) &ofxCvColorImage::mirror)
         .def("translate", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::translate)
         .def("rotate", (void(ofxCvColorImage::*)(float,float,float)) &ofxCvColorImage::rotate)
         .def("scale", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::scale)
         .def("transform", (void(ofxCvColorImage::*)(float,float,float,float,float,float,float)) &ofxCvColorImage::transform)
         .def("undistort", (void(ofxCvColorImage::*)(float,float,float,float,float,float,float,float)) &ofxCvColorImage::undistort)
         .def("warpPerspective", (void(ofxCvColorImage::*)(const ofPoint&,const ofPoint&,const ofPoint&,const ofPoint&)) &ofxCvColorImage::warpPerspective)
         .def("warpIntoMe", (void(ofxCvColorImage::*)(ofxCvImage&,const ofPoint,const ofPoint)) &ofxCvColorImage::warpIntoMe)
         .def("countNonZeroInRegion", (void(ofxCvColorImage::*)(int,int,int,int)) &ofxCvColorImage::countNonZeroInRegion)

         .def("set", (void(ofxCvColorImage::*)(float)) &ofxCvColorImage::set)
         .def("set", (void(ofxCvColorImage::*)(int,int,int)) &ofxCvColorImage::set)
         .def("setFromGrayscalePlanarImages", (void(ofxCvColorImage::*)(ofxCvGrayscaleImage&,ofxCvGrayscaleImage&,ofxCvGrayscaleImage&)) &ofxCvColorImage::setFromGrayscalePlanarImages)
         .def("convertToGrayscalePlanarImages", (void(ofxCvColorImage::*)(ofxCvGrayscaleImage&,ofxCvGrayscaleImage&,ofxCvGrayscaleImage&)) &ofxCvColorImage::convertToGrayscalePlanarImages)
         .def("convertToGrayscalePlanarImages", (void(ofxCvColorImage::*)(ofxCvGrayscaleImage&,int)) &ofxCvColorImage::convertToGrayscalePlanarImages)
         .def("contrastStretch", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::contrastStretch)
         .def("convertToRange", (void(ofxCvColorImage::*)(float,float)) &ofxCvColorImage::convertToRange)
         .def("resize", (void(ofxCvColorImage::*)(int,int)) &ofxCvColorImage::resize)
         .def("scaleIntoMe", &scaleIntoMeColor)
         .def("convertRgbToHsv", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::convertRgbToHsv)
         .def("convertHsvToRgb", (void(ofxCvColorImage::*)(void)) &ofxCvColorImage::convertHsvToRgb)
         .def_readonly("width", &ofxCvColorImage::width)
		 .def_readonly("height", &ofxCvColorImage::height)
         .def_readonly("bAllocated", &ofxCvColorImage::bAllocated),

         ///////////////////////////////
         // ofxCvGrayscaleImage

         class_<ofxCvGrayscaleImage>("cvGrayscaleImage")
         .def(constructor<>())
         .def(constructor<const ofxCvGrayscaleImage&>())

         .def("allocate", (void(ofxCvGrayscaleImage::*)(int,int)) &ofxCvGrayscaleImage::allocate)
         .def("clear", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::clear)
         .def("getWidth", (float(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::getWidth)
         .def("getHeight", (float(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::getHeight)
         .def("setUseTexture", (void(ofxCvGrayscaleImage::*)(bool)) &ofxCvGrayscaleImage::setUseTexture)
         .def("getTextureReference", (ofTexture&(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::getTextureReference)
         .def("flagImageChanged", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::flagImageChanged)
         .def("setROI", (void(ofxCvGrayscaleImage::*)(int,int,int,int)) &ofxCvGrayscaleImage::setROI)
         .def("setROI", (void(ofxCvGrayscaleImage::*)(const ofRectangle&)) &ofxCvGrayscaleImage::setROI)
         .def("getROI", (ofRectangle(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::getROI)
         .def("resetROI", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::resetROI)
         .def("getIntersectionROI", (ofRectangle(ofxCvGrayscaleImage::*)(const ofRectangle&,const ofRectangle&)) &ofxCvGrayscaleImage::getIntersectionROI)
         .def("setFromPixels", (void(ofxCvGrayscaleImage::*)(const ofPixels&)) &ofxCvGrayscaleImage::setFromPixels)
         .def("setRoiFromPixels", (void(ofxCvGrayscaleImage::*)(const ofPixels&)) &ofxCvGrayscaleImage::setRoiFromPixels)
         .def("updateTexture", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::updateTexture)
         .def("draw", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::draw)
         .def("draw", (void(ofxCvGrayscaleImage::*)(float,float,float,float)) &ofxCvGrayscaleImage::draw)
         .def("draw", (void(ofxCvGrayscaleImage::*)(const ofRectangle&)) &ofxCvGrayscaleImage::draw)
         .def("drawROI", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::drawROI)
         .def("drawROI", (void(ofxCvGrayscaleImage::*)(float,float,float,float)) &ofxCvGrayscaleImage::drawROI)
         .def("setAnchorPercent", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::setAnchorPercent)
         .def("setAnchorPoint", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::setAnchorPoint)
         .def("resetAnchor", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::resetAnchor)
         .def("erode", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::erode)
         .def("dilate", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::dilate)
         .def("blur", (void(ofxCvGrayscaleImage::*)(int)) &ofxCvGrayscaleImage::blur)
         .def("blurGaussian", (void(ofxCvGrayscaleImage::*)(int)) &ofxCvGrayscaleImage::blurGaussian)
         .def("invert", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::invert)
         .def("mirror", (void(ofxCvGrayscaleImage::*)(bool,bool)) &ofxCvGrayscaleImage::mirror)
         .def("translate", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::translate)
         .def("rotate", (void(ofxCvGrayscaleImage::*)(float,float,float)) &ofxCvGrayscaleImage::rotate)
         .def("scale", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::scale)
         .def("transform", (void(ofxCvGrayscaleImage::*)(float,float,float,float,float,float,float)) &ofxCvGrayscaleImage::transform)
         .def("undistort", (void(ofxCvGrayscaleImage::*)(float,float,float,float,float,float,float,float)) &ofxCvGrayscaleImage::undistort)
         .def("warpPerspective", (void(ofxCvGrayscaleImage::*)(const ofPoint&,const ofPoint&,const ofPoint&,const ofPoint&)) &ofxCvGrayscaleImage::warpPerspective)
         .def("warpIntoMe", (void(ofxCvGrayscaleImage::*)(ofxCvImage&,const ofPoint,const ofPoint)) &ofxCvGrayscaleImage::warpIntoMe)
         .def("countNonZeroInRegion", (void(ofxCvGrayscaleImage::*)(int,int,int,int)) &ofxCvGrayscaleImage::countNonZeroInRegion)

         .def("set", (void(ofxCvGrayscaleImage::*)(float)) &ofxCvGrayscaleImage::set)
         .def("setFromCvColorImage", (void(ofxCvGrayscaleImage::*)(ofxCvColorImage&)) &ofxCvGrayscaleImage::setFromCvColorImage)
         .def("absDiff", (void(ofxCvGrayscaleImage::*)(ofxCvGrayscaleImage&)) &ofxCvGrayscaleImage::absDiff)
         .def("absDiff", (void(ofxCvGrayscaleImage::*)(ofxCvGrayscaleImage&,ofxCvGrayscaleImage&)) &ofxCvGrayscaleImage::absDiff)
         .def("contrastStretch", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::contrastStretch)
         .def("convertToRange", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::convertToRange)
         .def("threshold", (void(ofxCvGrayscaleImage::*)(int,bool)) &ofxCvGrayscaleImage::threshold)
         .def("adaptiveThreshold", (void(ofxCvGrayscaleImage::*)(int,int,bool,bool)) &ofxCvGrayscaleImage::adaptiveThreshold)
         .def("brightnessContrast", (void(ofxCvGrayscaleImage::*)(float,float)) &ofxCvGrayscaleImage::brightnessContrast)
         .def("resize", (void(ofxCvGrayscaleImage::*)(int,int)) &ofxCvGrayscaleImage::resize)
         .def("scaleIntoMe", &scaleIntoMeGray)
         .def("blurHeavily", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::blurHeavily)
         .def("erode_3x3", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::erode_3x3)
         .def("dilate_3x3", (void(ofxCvGrayscaleImage::*)(void)) &ofxCvGrayscaleImage::dilate_3x3)
         .def("setFromColorImage", (void(ofxCvGrayscaleImage::*)(ofxCvFloatImage&)) &ofxCvGrayscaleImage::setFromColorImage)
         .def_readonly("width", &ofxCvGrayscaleImage::width)
		 .def_readonly("height", &ofxCvGrayscaleImage::height)
         .def_readonly("bAllocated", &ofxCvGrayscaleImage::bAllocated),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXARCTEXT --> extending ofTrueTypeFont
         class_<ofxArcText>("arcText")
         .def(constructor<>())
         .def(constructor<bool>())

         .def("loadFont", &loadArcFont2)
		 .def("loadFont", &loadArcFont4)
         .def("stringWidth", (float(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::stringWidth)
		 .def("stringHeight", (float(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::stringHeight)
         .def("getStringBoundingBox", (ofRectangle(ofTrueTypeFont::*)(string,float,float)) &ofTrueTypeFont::getStringBoundingBox)
         .def("getSize", (int(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getSize)
		 .def("getLetterSpacing", (float(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getLetterSpacing)
		 .def("setLetterSpacing", (void(ofTrueTypeFont::*)(float)) &ofTrueTypeFont::setLetterSpacing)
		 .def("getSpaceSize", (float(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getSpaceSize)
		 .def("setSpaceSize", (void(ofTrueTypeFont::*)(float)) &ofTrueTypeFont::setSpaceSize)
		 .def("getNumCharacters", (int(ofTrueTypeFont::*)(void)) &ofTrueTypeFont::getNumCharacters)
		 .def("getStringAsPoints", (ofTTFCharacter(ofTrueTypeFont::*)(string)) &ofTrueTypeFont::getStringAsPoints)

         .def("drawString", (void(ofxArcText::*)(string,float,float,float)) &ofxArcText::drawString)
         .def("getCharacterWidth", (float(ofxArcText::*)(char)) &ofxArcText::getCharacterWidth),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXCHROMAKEY --> extending ofImage
         class_<ofxChromaKey>("chromaKey")
         .def(constructor<>())
         .def("setPixels", (void(ofxChromaKey::*)(ofPixelsRef)) &ofxChromaKey::setPixels)
         .def("setPixels", (void(ofxChromaKey::*)(unsigned char*,int,int)) &ofxChromaKey::setPixels)
         .def("learnBgColor", (void(ofxChromaKey::*)(ofPixelsRef)) &ofxChromaKey::learnBgColor)
         .def("setBgColor", (void(ofxChromaKey::*)(ofColor)) &ofxChromaKey::setBgColor)
         .def("getBgColor", (ofColor(ofxChromaKey::*)(void)) &ofxChromaKey::getBgColor)
         .def("setThreshold", (void(ofxChromaKey::*)(float)) &ofxChromaKey::setThreshold)
         .def("drawBgColor", (void(ofxChromaKey::*)(int,int,int,int)) &ofxChromaKey::drawBgColor)
         .def("draw", (void(ofxChromaKey::*)(int,int,int,int,bool)) &ofxChromaKey::draw)
         .def("getThreshold", (float(ofxChromaKey::*)(void)) &ofxChromaKey::getThreshold),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXDELAUNAY
         class_<ofxDelaunay>("delaunay")
         .def(constructor<>())
         .def("setMaxPoints", (void(ofxDelaunay::*)(int)) &ofxDelaunay::setMaxPoints)
         .def("reset", (void(ofxDelaunay::*)(void)) &ofxDelaunay::reset)
         .def("addPoint", (int(ofxDelaunay::*)(const ofPoint&)) &ofxDelaunay::addPoint)
         .def("addPoint", (int(ofxDelaunay::*)(float,float,float)) &ofxDelaunay::addPoint)
         .def("triangulate", (int(ofxDelaunay::*)(void)) &ofxDelaunay::triangulate)
         .def("draw", (void(ofxDelaunay::*)(void)) &ofxDelaunay::draw)
         .def("drawTriangle", (void(ofxDelaunay::*)(int)) &ofxDelaunay::drawTriangle)
         .def("drawCenter", (void(ofxDelaunay::*)(int)) &ofxDelaunay::drawCenter),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXDITHER
         class_<ofxDither>("dither")
         .def(constructor<>())
         .def("ordered", &ditherOrdered)
         .def("floyd_steinberg", (void(ofxDither::*)(ofImage&,ofImage&)) &ofxDither::dither_floyd_steinberg)
         .def("atkinson", (void(ofxDither::*)(ofImage&,ofImage&)) &ofxDither::dither_atkinson),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXDMX
         class_<ofxDmx>("dmx")
         .def(constructor<>())
         .def("connect", (bool(ofxDmx::*)(int,unsigned int)) &ofxDmx::connect)
         .def("connect", (bool(ofxDmx::*)(string,unsigned int)) &ofxDmx::connect)
         .def("disconnect", (void(ofxDmx::*)(void)) &ofxDmx::disconnect)
         .def("setLevel", (bool(ofxDmx::*)(unsigned int,unsigned char)) &ofxDmx::setLevel)
         .def("clear", (void(ofxDmx::*)(void)) &ofxDmx::clear)
         .def("getLevel", (unsigned char(ofxDmx::*)(unsigned int)) &ofxDmx::getLevel)
         .def("update", (void(ofxDmx::*)(bool)) &ofxDmx::update)
         .def("setChannels", (void(ofxDmx::*)(unsigned int)) &ofxDmx::setChannels)
         .def("isConnected", (bool(ofxDmx::*)(void)) &ofxDmx::isConnected),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXFX

         class_<ofxBloom>("bloom")
         .def(constructor<>())
         .def("allocate", (void(ofxBloom::*)(int,int)) &ofxBloom::allocate)
         .def("getTextureReference", (ofTexture&(ofxBloom::*)(void)) &ofxBloom::getTextureReference)
         .def("beginFx", (void(ofxBloom::*)(void)) &ofxBloom::begin)
         .def("endFx", (void(ofxBloom::*)(bool)) &ofxBloom::end)
         .def("draw", (void(ofxBloom::*)(int,int)) &ofxBloom::draw),

         class_<ofxBlur>("blur")
         .def(constructor<>())
         .def("allocate", (void(ofxBlur::*)(int,int)) &ofxBlur::allocate)
         .def("setPasses", (ofxBlur&(ofxBlur::*)(int)) &ofxBlur::setPasses)
         .def("setRadius", (ofxBlur&(ofxBlur::*)(float)) &ofxBlur::setRadius)
         .def("getTextureReference", (ofTexture&(ofxBlur::*)(void)) &ofxBlur::getTextureReference)
         .def("beginFx", (void(ofxBlur::*)(void)) &ofxBlur::begin)
         .def("endFx", (void(ofxBlur::*)(bool)) &ofxBlur::end)
         .def("draw", (void(ofxBlur::*)(int,int)) &ofxBlur::draw),

         class_<ofxBlurFast>("blurFast")
         .def(constructor<>())
         .def("allocate", (void(ofxBlurFast::*)(int,int)) &ofxBlurFast::allocate)
         .def("setPasses", (ofxBlurFast&(ofxBlurFast::*)(int)) &ofxBlurFast::setPasses)
         .def("setFade", (ofxBlurFast&(ofxBlurFast::*)(float)) &ofxBlurFast::setFade)
         .def("getTextureReference", (ofTexture&(ofxBlurFast::*)(void)) &ofxBlurFast::getTextureReference)
         .def("beginFx", (void(ofxBlurFast::*)(void)) &ofxBlurFast::begin)
         .def("endFx", (void(ofxBlurFast::*)(bool)) &ofxBlurFast::end)
         .def("draw", (void(ofxBlurFast::*)(int,int)) &ofxBlurFast::draw),

         class_<ofxConway>("conway")
         .def(constructor<>())
         .def("allocate", (void(ofxConway::*)(int,int)) &ofxConway::allocate)
         .def("getTextureReference", (ofTexture&(ofxConway::*)(void)) &ofxConway::getTextureReference)
         .def("beginFx", (void(ofxConway::*)(void)) &ofxConway::begin)
         .def("endFx", (void(ofxConway::*)(bool)) &ofxConway::end)
         .def("update", (void(ofxConway::*)(void)) &ofxConway::update)
         .def("draw", (void(ofxConway::*)(int,int)) &ofxConway::draw),

         class_<ofxFlocking>("flocking")
         .def(constructor<>())
         .def("allocate", (void(ofxFlocking::*)(int,int,int)) &ofxFlocking::allocate)
         .def("setParticleSize", (ofxFlocking&(ofxFlocking::*)(float)) &ofxFlocking::setParticleSize)
         .def("setTimpeStep", (ofxFlocking&(ofxFlocking::*)(float)) &ofxFlocking::setTimpeStep)
         .def("getTextureReference", (ofTexture&(ofxFlocking::*)(void)) &ofxFlocking::getTextureReference)
         .def("beginFx", (void(ofxFlocking::*)(void)) &ofxFlocking::begin)
         .def("endFx", (void(ofxFlocking::*)(void)) &ofxFlocking::end)
         .def("update", (void(ofxFlocking::*)(void)) &ofxFlocking::update)
         .def("draw", (void(ofxFlocking::*)(int,int)) &ofxFlocking::draw),

         class_<ofxFluid>("fluid")
         .def(constructor<>())
         .def("allocate", (void(ofxFluid::*)(int,int,float)) &ofxFluid::allocate)
         .def("setDensity", (ofxFluid&(ofxFluid::*)(ofTexture&)) &ofxFluid::setDensity)
         .def("setVelocity", (ofxFluid&(ofxFluid::*)(ofTexture&)) &ofxFluid::setVelocity)
         .def("setTemperature", (ofxFluid&(ofxFluid::*)(ofTexture&)) &ofxFluid::setTemperature)
         .def("setGravity", (ofxFluid&(ofxFluid::*)(ofVec2f)) &ofxFluid::setGravity)
         .def("setDensityDissipation", (ofxFluid&(ofxFluid::*)(float)) &ofxFluid::setDensityDissipation)
         .def("setVelocityDissipation", (ofxFluid&(ofxFluid::*)(float)) &ofxFluid::setVelocityDissipation)
         .def("setTemperatureDissipation", (ofxFluid&(ofxFluid::*)(float)) &ofxFluid::setTemperatureDissipation)
         .def("addTemporalForce", &addTemporalForce)
         .def("addConstantForce", &addConstantForce)
         .def("beginFx", (void(ofxFluid::*)(void)) &ofxFluid::begin)
         .def("endFx", (void(ofxFluid::*)(void)) &ofxFluid::end)
         .def("update", (void(ofxFluid::*)(void)) &ofxFluid::update)
         .def("draw", (void(ofxFluid::*)(int,int)) &ofxFluid::draw),

         class_<ofxGlow>("glow")
         .def(constructor<>())
         .def("allocate", (void(ofxGlow::*)(int,int)) &ofxGlow::allocate)
         .def("setPasses", (ofxGlow&(ofxGlow::*)(int)) &ofxGlow::setPasses)
         .def("setRadius", (ofxGlow&(ofxGlow::*)(float)) &ofxGlow::setRadius)
         .def("getTextureReference", (ofTexture&(ofxGlow::*)(void)) &ofxGlow::getTextureReference)
         .def("beginFx", (void(ofxGlow::*)(void)) &ofxGlow::begin)
         .def("endFx", (void(ofxGlow::*)(bool)) &ofxGlow::end)
         .def("draw", (void(ofxGlow::*)(int,int)) &ofxGlow::draw),

         class_<ofxGrayScott>("grayScott")
         .def(constructor<>())
         .def("allocate", (void(ofxGrayScott::*)(int,int)) &ofxGrayScott::allocate)
         .def("setIterations", (ofxGrayScott&(ofxGrayScott::*)(int)) &ofxGrayScott::setIterations)
         .def("setDiffU", (ofxGrayScott&(ofxGrayScott::*)(float)) &ofxGrayScott::setDiffU)
         .def("setDiffV", (ofxGrayScott&(ofxGrayScott::*)(float)) &ofxGrayScott::setDiffV)
         .def("setK", (ofxGrayScott&(ofxGrayScott::*)(float)) &ofxGrayScott::setK)
         .def("setF", (ofxGrayScott&(ofxGrayScott::*)(float)) &ofxGrayScott::setF)
         .def("getTextureReference", (ofTexture&(ofxGrayScott::*)(void)) &ofxGrayScott::getTextureReference)
         .def("getDiffU", (float(ofxGrayScott::*)(void)) &ofxGrayScott::getDiffU)
         .def("getDiffV", (float(ofxGrayScott::*)(void)) &ofxGrayScott::getDiffV)
         .def("getK", (float(ofxGrayScott::*)(void)) &ofxGrayScott::getK)
         .def("getF", (float(ofxGrayScott::*)(void)) &ofxGrayScott::getF)
         .def("beginFx", (void(ofxGrayScott::*)(void)) &ofxGrayScott::begin)
         .def("endFx", (void(ofxGrayScott::*)(bool)) &ofxGrayScott::end)
         .def("update", (void(ofxGrayScott::*)(void)) &ofxGrayScott::update)
         .def("draw", (void(ofxGrayScott::*)(int,int)) &ofxGrayScott::draw),

         class_<ofxMask>("mask")
         .def(constructor<>())
         .def("allocate", (void(ofxMask::*)(int,int)) &ofxMask::allocate)
         .def("getTextureReference", (ofTexture&(ofxMask::*)(void)) &ofxMask::getTextureReference)
         .def("beginMask", (void(ofxMask::*)(void)) &ofxMask::beginMask)
         .def("endMask", (void(ofxMask::*)(void)) &ofxMask::endMask)
         .def("beginFx", (void(ofxMask::*)(void)) &ofxMask::begin)
         .def("endFx", (void(ofxMask::*)(bool)) &ofxMask::end)
         .def("draw", (void(ofxMask::*)(int,int)) &ofxMask::draw),

         class_<ofxOldTv>("oldTv")
         .def(constructor<>())
         .def("allocate", (void(ofxOldTv::*)(int,int)) &ofxOldTv::allocate)
         .def("setBrightness", (ofxOldTv&(ofxOldTv::*)(float)) &ofxOldTv::setBrightness)
         .def("setRows", (ofxOldTv&(ofxOldTv::*)(float)) &ofxOldTv::setRows)
         .def("getTextureReference", (ofTexture&(ofxOldTv::*)(void)) &ofxOldTv::getTextureReference)
         .def("beginFx", (void(ofxOldTv::*)(void)) &ofxOldTv::begin)
         .def("endFx", (void(ofxOldTv::*)(bool)) &ofxOldTv::end)
         .def("draw", (void(ofxOldTv::*)(int,int)) &ofxOldTv::draw),

         class_<ofxWater>("water")
         .def(constructor<>())
         .def("allocate", (ofxWater&(ofxWater::*)(int,int)) &ofxWater::allocate)
         .def("loadBackground", (ofxWater&(ofxWater::*)(string)) &ofxWater::loadBackground)
         .def("linkBackground", (ofxWater&(ofxWater::*)(ofTexture*)) &ofxWater::linkBackground)
         .def("setThreshold", (ofxWater&(ofxWater::*)(float)) &ofxWater::setThreshold)
         .def("setDensity", (ofxWater&(ofxWater::*)(float)) &ofxWater::setDensity)
         .def("setFade", (ofxWater&(ofxWater::*)(float)) &ofxWater::setFade)
         .def("getTextureReference", (ofTexture&(ofxWater::*)(void)) &ofxWater::getTextureReference)
         .def("beginFx", (void(ofxWater::*)(void)) &ofxWater::begin)
         .def("endFx", (void(ofxWater::*)(bool)) &ofxWater::end)
         .def("update", (void(ofxWater::*)(void)) &ofxWater::update)
         .def("draw", (void(ofxWater::*)(int,int)) &ofxWater::draw),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXGAUSSIAN
         def("gaussian", (float(*)(void)) &ofxGaussian),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXMISSING
         def("getDateTimeAsString", (string(*)(string)) &getDateTimeAsString),
         def("MD5", (string(*)(string)) &md5),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXSUBTITLES
         class_<ofxSubtitles>("subtitles")
         .def(constructor<>())
         .def("load", (void(ofxSubtitles::*)(const string&)) &ofxSubtitles::load)
         .def("save", (void(ofxSubtitles::*)(const string&)) &ofxSubtitles::save)
         .def("add", (void(ofxSubtitles::*)(float,string)) &ofxSubtitles::add)
         .def("add", (void(ofxSubtitles::*)(float,float,string)) &ofxSubtitles::add)
         .def("getHowMany", (int(ofxSubtitles::*)(float,float)) &ofxSubtitles::getHowMany)
         .def("getFirstSubN", (int(ofxSubtitles::*)(float)) &ofxSubtitles::getFirstSubN)
         .def("getLineAt", (string(ofxSubtitles::*)(float)) &ofxSubtitles::getLineAt)
         .def("isStringAt", (bool(ofxSubtitles::*)(string,float)) &ofxSubtitles::isStringAt)
         .def("replace", (void(ofxSubtitles::*)(string,string,float)) &ofxSubtitles::replace)
         .def("loadfont", (void(ofxSubtitles::*)(string,int)) &ofxSubtitles::loadfont)
         .def("setScreen", (void(ofxSubtitles::*)(int,int)) &ofxSubtitles::setScreen)
         .def("setColor", (void(ofxSubtitles::*)(int,int,int)) &ofxSubtitles::setColor)
         .def("setColor", (void(ofxSubtitles::*)(int,int,int,int)) &ofxSubtitles::setColor)
         .def("draw", (void(ofxSubtitles::*)(float)) &ofxSubtitles::draw)
         .def("draw", (void(ofxSubtitles::*)(int,int,float)) &ofxSubtitles::draw)
         .def("draw", (void(ofxSubtitles::*)(int,int,int,int,float)) &ofxSubtitles::draw),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXTEXTSUITE
         class_<ofxTextBlock>("textBlock")
         .def(constructor<>())
         .def("init", (void(ofxTextBlock::*)(string,float)) &ofxTextBlock::init)
         .def("setText", (void(ofxTextBlock::*)(string)) &ofxTextBlock::setText)
		 .def("wrapTextX", (int(ofxTextBlock::*)(float)) &ofxTextBlock::wrapTextX)
         .def("wrapTextArea", (void(ofxTextBlock::*)(float,float)) &ofxTextBlock::wrapTextArea)
         .def("wrapTextForceLines", (bool(ofxTextBlock::*)(int)) &ofxTextBlock::wrapTextForceLines)
         .def("setLineHeight", (void(ofxTextBlock::*)(float)) &ofxTextBlock::setLineHeight)
         .def("setColor", (void(ofxTextBlock::*)(int,int,int,int)) &ofxTextBlock::setColor)
         .def("draw", (void(ofxTextBlock::*)(float,float)) &ofxTextBlock::draw)
         .def("drawLeft", (void(ofxTextBlock::*)(float,float)) &ofxTextBlock::drawLeft)
         .def("drawRight", (void(ofxTextBlock::*)(float,float)) &ofxTextBlock::drawRight)
         .def("drawCenter", (void(ofxTextBlock::*)(float,float)) &ofxTextBlock::drawCenter)
         .def("drawJustified", (void(ofxTextBlock::*)(float,float,float)) &ofxTextBlock::drawJustified)
         .def("forceScale", (void(ofxTextBlock::*)(float)) &ofxTextBlock::forceScale)
         .def("getWidth", (float(ofxTextBlock::*)(void)) &ofxTextBlock::getWidth)
		 .def("getHeight", (float(ofxTextBlock::*)(void)) &ofxTextBlock::getHeight),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXTRUETYPEFONTUC
         class_<ofxTrueTypeFontUC>("trueTypeFontUC")
         .def(constructor<>())
         .def("loadFont", &loadFont2UC)
		 .def("loadFont", &loadFont4UC)
         .def("loadFont", (void(ofxTrueTypeFontUC::*)(string,int,bool,bool,bool,float,int)) &ofxTrueTypeFontUC::loadFont)
		 .def("isLoaded", (bool(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::isLoaded)
         .def("isAntiAliased", (bool(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::isAntiAliased)
         .def("hasFullCharacterSet", (bool(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::hasFullCharacterSet)
		 .def("getSize", (int(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::getSize)
		 .def("getLineHeight", (float(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::getLineHeight)
		 .def("setLineHeight", (void(ofxTrueTypeFontUC::*)(float)) &ofxTrueTypeFontUC::setLineHeight)
		 .def("getLetterSpacing", (float(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::getLetterSpacing)
		 .def("setLetterSpacing", (void(ofxTrueTypeFontUC::*)(float)) &ofxTrueTypeFontUC::setLetterSpacing)
		 .def("getSpaceSize", (float(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::getSpaceSize)
		 .def("setSpaceSize", (void(ofxTrueTypeFontUC::*)(float)) &ofxTrueTypeFontUC::setSpaceSize)
         .def("stringWidth", (float(ofxTrueTypeFontUC::*)(string)) &ofxTrueTypeFontUC::stringWidth)
		 .def("stringHeight", (float(ofxTrueTypeFontUC::*)(string)) &ofxTrueTypeFontUC::stringHeight)
         .def("getStringBoundingBox", (ofRectangle(ofxTrueTypeFontUC::*)(string,float,float)) &ofxTrueTypeFontUC::getStringBoundingBox)
         .def("drawString", (void(ofxTrueTypeFontUC::*)(string,float,float)) &ofxTrueTypeFontUC::drawString)
		 .def("drawStringAsShapes", (void(ofxTrueTypeFontUC::*)(string,float,float)) &ofxTrueTypeFontUC::drawStringAsShapes)
		 .def("getNumCharacters", (int(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::getNumCharacters)
		 .def("getNumMaxCharacters", (int(ofxTrueTypeFontUC::*)(void)) &ofxTrueTypeFontUC::getNumMaxCharacters)
		 .def("setNumMaxCharacters", (void(ofxTrueTypeFontUC::*)(int)) &ofxTrueTypeFontUC::setNumMaxCharacters),
         //////////////////////////////////////////////////////////////////////////////////////////////////

         ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         // OFXVECTORFIELD
         class_<ofxVectorField>("vectorField")
         .def(constructor<>())
         .def("setup", (void(ofxVectorField::*)(int,int,int)) &ofxVectorField::setup)
         .def("deallocate", (void(ofxVectorField::*)(void)) &ofxVectorField::deallocate)
         .def("draw", (void(ofxVectorField::*)(void)) &ofxVectorField::draw)
         .def("setFromImage", (void(ofxVectorField::*)(ofImage&)) &ofxVectorField::setFromImage)
         .def("randomize", (void(ofxVectorField::*)(void)) &ofxVectorField::randomize)
         .def("animate", (void(ofxVectorField::*)(float)) &ofxVectorField::animate)
         .def("getVector", (ofVec2f(ofxVectorField::*)(int,int)) &ofxVectorField::getVector)
         .def("getVectorInterpolated", (ofVec2f(ofxVectorField::*)(int,int,int,int)) &ofxVectorField::getVectorInterpolated)
         .def("normalize", (void(ofxVectorField::*)(bool)) &ofxVectorField::normalize)
         .def("map", (void(ofxVectorField::*)(float,float,bool)) &ofxVectorField::map)
         .def("scale", (void(ofxVectorField::*)(float)) &ofxVectorField::scale)
         .def("bias", (void(ofxVectorField::*)(float)) &ofxVectorField::bias)
         .def("bias", (void(ofxVectorField::*)(float,float)) &ofxVectorField::bias)
         .def("blur", (void(ofxVectorField::*)(void)) &ofxVectorField::blur)
         .def("smudge", (void(ofxVectorField::*)(ofVec2f,ofVec2f)) &ofxVectorField::smudge)
         .def_readwrite("width", &ofxVectorField::width)
         .def_readwrite("height", &ofxVectorField::height)
         //////////////////////////////////////////////////////////////////////////////////////////////////

        ];

        // addons CONSTANTS


		//////////////////////////////////////////////////////////////
		///////////////////////////////
		/// gamuza core api wrapper
		module(lua, "ga")
		[

         ///////////////////////////////
		 // app section
         def("key", &getKey), // ga.key()
         def("mouseX", &getMouseX),  // ga.mouseX()
		 def("mouseY", &getMouseY),  // ga.mouseY()
         def("system", &system),
         def("log", (void(*)(string)) &gaLog),
         def("importFile", (string(*)(string)) &gaGetLocalDataPath),
         def("sendingOscTo", (string(*)(void)) &gaGetOSCSendingIP),
         def("getFrameNum", (int(*)(void)) &gaGetFrameNum),

         ///////////////////////////////
		 // string section
         def("stringReplace", (int(*)(string&,string,string)) &gaStringReplace),

		 ///////////////////////////////
		 // graphics section
		 def("background", (void(*)(float,float)) &gaBackground),
		 def("background", (void(*)(float,float,float,float)) &gaBackground),
		 def("cameraTexture", (ofTexture(*)(int)) &gaGetWebcamTexture),
         def("oniTexture", (ofTexture(*)(void)) &gaGetONITexture),
         def("cameraPixels", (unsigned char*(*)(int)) &gaGetWebcamPixels),
         def("cameraPixelsRef", (ofPixelsRef(*)(int)) &gaGetWebcamPixelsRef),
         def("saveFrame", (void(*)(string)) &gaSaveFrame),

         ///////////////////////////////
		 // 3D section
         def("drawAxis", (void(*)(float,ofColor,bool)) &gaDrawAxis),
         def("drawXAxis", (void(*)(float,ofColor,bool)) &gaDrawXAxis),
         def("drawYAxis", (void(*)(float,ofColor,bool)) &gaDrawYAxis),
         def("drawZAxis", (void(*)(float,ofColor,bool)) &gaDrawZAxis),

         ///////////////////////////////
		 // timeline section
         def("playTimeline", (void(*)(void)) &gaPlayTimeline),
         def("stopTimeline", (void(*)(void)) &gaStopTimeline),
         def("setTimelineFrames", (void(*)(int)) &gaSetTimelineDurationInFrames),
         def("setTimelineLoop", (void(*)(int)) &gaSetTimelineLoopType),
         def("addTimelineKeyframes", (void(*)(string,string,float,float)) &gaAddTimelineKeyframes),
         def("getTimelineValue", (float(*)(string)) &gaGetTimelineKeyframeValue),
         def("getTimelineTrigger", (string(*)(void)) &gaGetTimelineTrigger),

         ///////////////////////////////
		 // pixel manipulation section
         def("cameraMiller", (ofTexture(*)(int,int,float,float,float,float)) &gaGetWebcamMiller),

         ///////////////////////////////
		 // audio input
		 def("getVolume", (float(*)(int)) &gaGetVolume),
		 def("getPitch", (float(*)(int)) &gaGetPitch),
		 def("getBin", (float(*)(int,int)) &gaGetFFTBand),
		 def("getFFT", (float(*)(int,int)) &gaGetFFTBin),
         def("getInputBuffer", (float(*)(int,int)) &gaGetAudioInputBuffer),
         def("getOutputBuffer", (float(*)(int)) &gaGetAudioOutputBuffer),
         def("getSoundSpectrum", (float(*)(int,int)) &gaGetSoundGetSpectrum),

		 ///////////////////////////////
		 // audio synth section
		 def("wave", &gaSetupOSC),
		 def("monoWave", &gaSetupMonoOSC),
		 def("waveVolume", &gaSetOscVolume),
		 def("waveFrequency", &gaSetOscFrequency),
		 def("waveType", &gaSetOscWaveType),
		 def("waveTuning,", &gaSetOscTuning),
		 def("nToF", &gaNote),

         ///////////////////////////////
		 // audio input recording section
         def("startRec", (void(*)(int)) &gaStartInputRecording),
         def("stopRec", (void(*)(void)) &gaStopInputRecording),
         def("recSamplePlay", (void(*)(int)) &gaInputRecPlay),
         def("recSampleStop", (void(*)(int)) &gaInputRecStop),
		 def("recSampleVolume", (void(*)(int,float)) &gaSetInputRecVolume),
		 def("recSampleLooping", (void(*)(int,bool)) &gaSetInputRecLooping),
		 def("recSamplePaused", (void(*)(int,bool)) &gaSetInputRecPaused),
         def("recSampleSpeed", (void(*)(int,float)) &gaSetInputRecSpeed),
         def("drawRecHead", (void(*)(int,int,int,int,int)) &gaDrawInputRecHead),

         ///////////////////////////////
		 // midi section
         def("getMidiChannel", (int(*)(void)) &gaGetMidiChannel),
         def("getMidiByteOne", (int(*)(void)) &gaGetMidiByteOne),
         def("getMidiByteTwo", (int(*)(void)) &gaGetMidiByteTwo),
         def("getMidiValue", (float(*)(int,int)) &gaGetMidiValue),

         ///////////////////////////////
		 // OSC section
         def("getOSCMessage", (void(*)(string)) &gaReceiveOSCMessage),
         def("getOSCValue", (string(*)(string)) &gaGetOSCValue),
         def("setOSCMessage", (void(*)(string,int)) &gaSendOSCMessage),
         def("setOSCValue", (void(*)(string,string)) &gaSetOSCValue),

		 ///////////////////////////////
		 // openni sensor kinect
		 def("oniBlobs", (int(*)(void)) &gaONIRunningBlob),
		 def("oniBlobX", (float(*)(int)) &gaONIBlobX),
		 def("oniBlobY", (float(*)(int)) &gaONIBlobY),
		 def("oniBlobW", (float(*)(int)) &gaONIBlobW),
		 def("oniBlobH", (float(*)(int)) &gaONIBlobH),
		 def("oniBlobAngle", (float(*)(int)) &gaONIBlobAngle),
		 def("oniBlobContourSize", (int(*)(int)) &gaONIBlobContourSize),
         def("oniBlobCPointX", (float(*)(int,int)) &gaONIBlobCPointX),
         def("oniBlobCPointY", (float(*)(int,int)) &gaONIBlobCPointY),
		 def("oniBlobGeometrySize", (int(*)(int)) &gaONIBlobGeometrySize),
         def("oniBlobGLineX1", (float(*)(int,int)) &gaONIBlobGLineX1),
         def("oniBlobGLineY1", (float(*)(int,int)) &gaONIBlobGLineY1),
         def("oniBlobGLineX2", (float(*)(int,int)) &gaONIBlobGLineX2),
         def("oniBlobGLineY2", (float(*)(int,int)) &gaONIBlobGLineY2),
		 def("oniOpticalFlowX", (float(*)(int)) &gaONIOpticalFlowX),
         def("oniOpticalFlowY", (float(*)(int)) &gaONIOpticalFlowY),
         def("oniOpticalFlowVX", (float(*)(int)) &gaONIOpticalFlowVX),
         def("oniOpticalFlowVY", (float(*)(int)) &gaONIOpticalFlowVY),
		 def("oniTrigger", (bool(*)(int)) &gaONITrigger),
		 def("oniHandX", (float(*)(int)) &gaONIHandX),
         def("oniHandY", (float(*)(int)) &gaONIHandY),
         def("oniHandZ", (float(*)(int)) &gaONIHandZ),
		 def("oniAccelerometerX", (float(*)(void)) &gaONIAccelerometerX),
         def("oniAccelerometerY", (float(*)(void)) &gaONIAccelerometerY),
         def("oniAccelerometerZ", (float(*)(void)) &gaONIAccelerometerZ),
		 def("oniTilt", (float(*)(void)) &gaONITilt),

		 ///////////////////////////////
		 // webcam tracking
		 def("camMotionQ", (float(*)(int)) &gaCamMotionQ),
		 def("camMotionX", (float(*)(int)) &gaCamMotionX),
		 def("camMotionY", (float(*)(int)) &gaCamMotionY),
		 def("camBlobs", (int(*)(int)) &gaCamRunningBlob),
		 def("camBlobX", (float(*)(int,int)) &gaCamBlobX),
		 def("camBlobY", (float(*)(int,int)) &gaCamBlobY),
		 def("camBlobW", (float(*)(int,int)) &gaCamBlobW),
		 def("camBlobH", (float(*)(int,int)) &gaCamBlobH),
		 def("camBlobAngle", (float(*)(int,int)) &gaCamBlobAngle),
         def("camBlobContourSize", (int(*)(int,int)) &gaCamBlobContourSize),
         def("camBlobCPointX", (float(*)(int,int,int)) &gaCamBlobCPointX),
         def("camBlobCPointY", (float(*)(int,int,int)) &gaCamBlobCPointY),
		 def("camBlobGeometrySize", (int(*)(int,int)) &gaCamBlobGeometrySize),
         def("camBlobGLineX1", (float(*)(int,int,int)) &gaCamBlobGLineX1),
         def("camBlobGLineY1", (float(*)(int,int,int)) &gaCamBlobGLineY1),
         def("camBlobGLineX2", (float(*)(int,int,int)) &gaCamBlobGLineX2),
         def("camBlobGLineY2", (float(*)(int,int,int)) &gaCamBlobGLineY2),
		 def("camOpticalFlowX", (float(*)(int,int)) &gaCamOpticalFlowX),
         def("camOpticalFlowY", (float(*)(int,int)) &gaCamOpticalFlowY),
         def("camOpticalFlowVX", (float(*)(int,int)) &gaCamOpticalFlowVX),
         def("camOpticalFlowVY", (float(*)(int,int)) &gaCamOpticalFlowVY),
         def("camHaars", (int(*)(int)) &gaCamRunningHaar),
		 def("camHaarX", (float(*)(int,int)) &gaCamHaarX),
         def("camHaarY", (float(*)(int,int)) &gaCamHaarY),
         def("camHaarW", (float(*)(int,int)) &gaCamHaarW),
         def("camHaarH", (float(*)(int,int)) &gaCamHaarH),
		 def("camTrigger", (bool(*)(int,int)) &gaCamTrigger),

		 ///////////////////////////////
		 // arduino
         def("serialDevice", (string(*)(void)) &gaGetSerialDevName),
		 def("analogRead", (float(*)(int)) &gaGetAArduinoPin),
		 def("digitalRead", (int(*)(int)) &gaGetDArduinoPin),
		 def("digitalWrite", (void(*)(int,int)) &gaSetDArduinoPin)


		];
		//////////////////////////////////////////////////////////////

		///////////////////////////////
		/// \section CONSTANTS

		/// OF math constants
		lua.doString("HALF_PI = "+ofToString(HALF_PI));
		lua.doString("PI = "+ofToString(PI));
		lua.doString("TWO_PI = "+ofToString(TWO_PI));
        lua.doString("FOUR_PI = "+ofToString(FOUR_PI));
        lua.doString("DEG_TO_RAD = "+ofToString(DEG_TO_RAD));
        lua.doString("RAD_TO_DEG = "+ofToString(RAD_TO_DEG));

        // OF key constants
        lua.doString("OF_KEY_RETURN = "+ofToString(OF_KEY_RETURN));
        lua.doString("OF_KEY_ESC = "+ofToString(OF_KEY_ESC));
        lua.doString("OF_KEY_F1 = "+ofToString(OF_KEY_F1));
        lua.doString("OF_KEY_F2 = "+ofToString(OF_KEY_F2));
        lua.doString("OF_KEY_F3 = "+ofToString(OF_KEY_F3));
        lua.doString("OF_KEY_F4 = "+ofToString(OF_KEY_F4));
        lua.doString("OF_KEY_F5 = "+ofToString(OF_KEY_F5));
        lua.doString("OF_KEY_F6 = "+ofToString(OF_KEY_F6));
        lua.doString("OF_KEY_F7 = "+ofToString(OF_KEY_F7));
        lua.doString("OF_KEY_F8 = "+ofToString(OF_KEY_F8));
        lua.doString("OF_KEY_F9 = "+ofToString(OF_KEY_F9));
        lua.doString("OF_KEY_F10 = "+ofToString(OF_KEY_F10));
        lua.doString("OF_KEY_F11 = "+ofToString(OF_KEY_F11));
        lua.doString("OF_KEY_F12 = "+ofToString(OF_KEY_F11));
        lua.doString("OF_KEY_LEFT = "+ofToString(OF_KEY_LEFT));
        lua.doString("OF_KEY_UP = "+ofToString(OF_KEY_UP));
        lua.doString("OF_KEY_RIGHT = "+ofToString(OF_KEY_RIGHT));
        lua.doString("OF_KEY_DOWN = "+ofToString(OF_KEY_DOWN));
        lua.doString("OF_KEY_PAGE_UP = "+ofToString(OF_KEY_PAGE_UP));
        lua.doString("OF_KEY_PAGE_DOWN = "+ofToString(OF_KEY_PAGE_DOWN));
        lua.doString("OF_KEY_HOME = "+ofToString(OF_KEY_HOME));
        lua.doString("OF_KEY_END = "+ofToString(OF_KEY_END));
        lua.doString("OF_KEY_INSERT = "+ofToString(OF_KEY_INSERT));
        lua.doString("OF_KEY_BACKSPACE = "+ofToString(OF_KEY_BACKSPACE));
        lua.doString("OF_KEY_DEL = "+ofToString(OF_KEY_DEL));

        // OF RECTMODES
        lua.doString("OF_RECTMODE_CENTER = "+ofToString(OF_RECTMODE_CENTER));
        lua.doString("OF_RECTMODE_CORNER = "+ofToString(OF_RECTMODE_CORNER));

        // OF loop constants
        lua.doString("OF_LOOP_NONE = "+ofToString(OF_LOOP_NONE));
        lua.doString("OF_LOOP_NORMAL = "+ofToString(OF_LOOP_NORMAL));
        lua.doString("OF_LOOP_PALINDROME = "+ofToString(OF_LOOP_PALINDROME));

        // OF pixel formats
        lua.doString("OF_PIXELS_MONO = "+ofToString(OF_PIXELS_MONO));
        lua.doString("OF_PIXELS_RGB = "+ofToString(OF_PIXELS_RGB));
        lua.doString("OF_PIXELS_RGBA = "+ofToString(OF_PIXELS_RGBA));
        lua.doString("OF_PIXELS_BGRA = "+ofToString(OF_PIXELS_BGRA));

        // OF image type
        lua.doString("OF_IMAGE_GRAYSCALE = "+ofToString(OF_IMAGE_GRAYSCALE));
        lua.doString("OF_IMAGE_COLOR = "+ofToString(OF_IMAGE_COLOR));
        lua.doString("OF_IMAGE_COLOR_ALPHA = "+ofToString(OF_IMAGE_COLOR_ALPHA));
        lua.doString("OF_IMAGE_UNDEFINED = "+ofToString(OF_IMAGE_UNDEFINED));

        // OF image quality type
        lua.doString("OF_IMAGE_QUALITY_BEST = "+ofToString(OF_IMAGE_QUALITY_BEST));
        lua.doString("OF_IMAGE_QUALITY_HIGH = "+ofToString(OF_IMAGE_QUALITY_HIGH));
        lua.doString("OF_IMAGE_QUALITY_MEDIUM = "+ofToString(OF_IMAGE_QUALITY_MEDIUM));
        lua.doString("OF_IMAGE_QUALITY_LOW = "+ofToString(OF_IMAGE_QUALITY_LOW));
        lua.doString("OF_IMAGE_QUALITY_WORST = "+ofToString(OF_IMAGE_QUALITY_WORST));

        // OF image format
        lua.doString("OF_IMAGE_FORMAT_BMP = "+ofToString(OF_IMAGE_FORMAT_BMP));
        lua.doString("OF_IMAGE_FORMAT_ICO = "+ofToString(OF_IMAGE_FORMAT_ICO));
        lua.doString("OF_IMAGE_FORMAT_JPEG = "+ofToString(OF_IMAGE_FORMAT_JPEG));
        lua.doString("OF_IMAGE_FORMAT_JNG = "+ofToString(OF_IMAGE_FORMAT_JNG));
        lua.doString("OF_IMAGE_FORMAT_KOALA = "+ofToString(OF_IMAGE_FORMAT_KOALA));
        lua.doString("OF_IMAGE_FORMAT_LBM = "+ofToString(OF_IMAGE_FORMAT_LBM));
        lua.doString("OF_IMAGE_FORMAT_IFF = "+ofToString(OF_IMAGE_FORMAT_IFF));
        lua.doString("OF_IMAGE_FORMAT_MNG = "+ofToString(OF_IMAGE_FORMAT_MNG));
        lua.doString("OF_IMAGE_FORMAT_PBM = "+ofToString(OF_IMAGE_FORMAT_PBM));
        lua.doString("OF_IMAGE_FORMAT_PBMRAW = "+ofToString(OF_IMAGE_FORMAT_PBMRAW));
        lua.doString("OF_IMAGE_FORMAT_PCD = "+ofToString(OF_IMAGE_FORMAT_PCD));
        lua.doString("OF_IMAGE_FORMAT_PCX = "+ofToString(OF_IMAGE_FORMAT_PCX));
        lua.doString("OF_IMAGE_FORMAT_PGM = "+ofToString(OF_IMAGE_FORMAT_PGM));
        lua.doString("OF_IMAGE_FORMAT_PGMRAW = "+ofToString(OF_IMAGE_FORMAT_PGMRAW));
        lua.doString("OF_IMAGE_FORMAT_PNG = "+ofToString(OF_IMAGE_FORMAT_PNG));
        lua.doString("OF_IMAGE_FORMAT_PPM = "+ofToString(OF_IMAGE_FORMAT_PPM));
        lua.doString("OF_IMAGE_FORMAT_PPMRAW = "+ofToString(OF_IMAGE_FORMAT_PPMRAW));
        lua.doString("OF_IMAGE_FORMAT_RAS = "+ofToString(OF_IMAGE_FORMAT_RAS));
        lua.doString("OF_IMAGE_FORMAT_TARGA = "+ofToString(OF_IMAGE_FORMAT_TARGA));
        lua.doString("OF_IMAGE_FORMAT_TIFF = "+ofToString(OF_IMAGE_FORMAT_TIFF));
        lua.doString("OF_IMAGE_FORMAT_WBMP = "+ofToString(OF_IMAGE_FORMAT_WBMP));
        lua.doString("OF_IMAGE_FORMAT_PSD = "+ofToString(OF_IMAGE_FORMAT_PSD));
        lua.doString("OF_IMAGE_FORMAT_CUT = "+ofToString(OF_IMAGE_FORMAT_CUT));
        lua.doString("OF_IMAGE_FORMAT_XBM = "+ofToString(OF_IMAGE_FORMAT_XBM));
        lua.doString("OF_IMAGE_FORMAT_XPM = "+ofToString(OF_IMAGE_FORMAT_XPM));
        lua.doString("OF_IMAGE_FORMAT_DDS = "+ofToString(OF_IMAGE_FORMAT_DDS));
        lua.doString("OF_IMAGE_FORMAT_GIF = "+ofToString(OF_IMAGE_FORMAT_GIF));
        lua.doString("OF_IMAGE_FORMAT_HDR = "+ofToString(OF_IMAGE_FORMAT_HDR));
        lua.doString("OF_IMAGE_FORMAT_FAXG3 = "+ofToString(OF_IMAGE_FORMAT_FAXG3));
        lua.doString("OF_IMAGE_FORMAT_SGI = "+ofToString(OF_IMAGE_FORMAT_SGI));
        lua.doString("OF_IMAGE_FORMAT_EXR = "+ofToString(OF_IMAGE_FORMAT_EXR));
        lua.doString("OF_IMAGE_FORMAT_J2K = "+ofToString(OF_IMAGE_FORMAT_J2K));
        lua.doString("OF_IMAGE_FORMAT_JP2 = "+ofToString(OF_IMAGE_FORMAT_JP2));
        lua.doString("OF_IMAGE_FORMAT_PFM = "+ofToString(OF_IMAGE_FORMAT_PFM));
        lua.doString("OF_IMAGE_FORMAT_PICT = "+ofToString(OF_IMAGE_FORMAT_PICT));
        lua.doString("OF_IMAGE_FORMAT_RAW = "+ofToString(OF_IMAGE_FORMAT_RAW));

        // OF polyline winding mode
        lua.doString("OF_POLY_WINDING_ODD = "+ofToString(OF_POLY_WINDING_ODD));
        lua.doString("OF_POLY_WINDING_NONZERO = "+ofToString(OF_POLY_WINDING_NONZERO));
        lua.doString("OF_POLY_WINDING_POSITIVE = "+ofToString(OF_POLY_WINDING_POSITIVE));
        lua.doString("OF_POLY_WINDING_NEGATIVE = "+ofToString(OF_POLY_WINDING_NEGATIVE));
        lua.doString("OF_POLY_WINDING_ABS_GEQ_TWO = "+ofToString(OF_POLY_WINDING_ABS_GEQ_TWO));

        // OF primitives
        lua.doString("OF_PRIMITIVE_TRIANGLES = "+ofToString(OF_PRIMITIVE_TRIANGLES));
        lua.doString("OF_PRIMITIVE_TRIANGLE_STRIP = "+ofToString(OF_PRIMITIVE_TRIANGLE_STRIP));
        lua.doString("OF_PRIMITIVE_TRIANGLE_FAN = "+ofToString(OF_PRIMITIVE_TRIANGLE_FAN));
        lua.doString("OF_PRIMITIVE_LINES = "+ofToString(OF_PRIMITIVE_LINES));
        lua.doString("OF_PRIMITIVE_LINE_STRIP = "+ofToString(OF_PRIMITIVE_LINE_STRIP));
        lua.doString("OF_PRIMITIVE_LINE_LOOP = "+ofToString(OF_PRIMITIVE_LINE_LOOP));
        lua.doString("OF_PRIMITIVE_POINTS = "+ofToString(OF_PRIMITIVE_POINTS));

        // OF gl legacy
        lua.doString("OF_TRIANGLES_MODE = "+ofToString(OF_TRIANGLES_MODE));
        lua.doString("OF_TRIANGLE_STRIP_MODE = "+ofToString(OF_TRIANGLE_STRIP_MODE));
        lua.doString("OF_TRIANGLE_FAN_MODE = "+ofToString(OF_TRIANGLE_FAN_MODE));
        lua.doString("OF_LINES_MODE = "+ofToString(OF_LINES_MODE));
        lua.doString("OF_LINE_STRIP_MODE = "+ofToString(OF_LINE_STRIP_MODE));
        lua.doString("OF_LINE_LOOP_MODE = "+ofToString(OF_LINE_LOOP_MODE));
        lua.doString("OF_POINTS_MODE = "+ofToString(OF_POINTS_MODE));

        // OF mesh modes
        lua.doString("OF_MESH_POINTS = "+ofToString(OF_MESH_POINTS));
        lua.doString("OF_MESH_WIREFRAME = "+ofToString(OF_MESH_WIREFRAME));
        lua.doString("OF_MESH_FILL = "+ofToString(OF_MESH_FILL));

        // OF blending modes
        lua.doString("OF_BLENDMODE_DISABLED = "+ofToString(OF_BLENDMODE_DISABLED));
        lua.doString("OF_BLENDMODE_ALPHA = "+ofToString(OF_BLENDMODE_ALPHA));
        lua.doString("OF_BLENDMODE_ADD = "+ofToString(OF_BLENDMODE_ADD));
        lua.doString("OF_BLENDMODE_SUBTRACT = "+ofToString(OF_BLENDMODE_SUBTRACT));
        lua.doString("OF_BLENDMODE_MULTIPLY = "+ofToString(OF_BLENDMODE_MULTIPLY));
        lua.doString("OF_BLENDMODE_SCREEN = "+ofToString(OF_BLENDMODE_SCREEN));

        // OF bitmap draw modes
        lua.doString("OF_BITMAPMODE_SIMPLE = "+ofToString(OF_BITMAPMODE_SIMPLE));
        lua.doString("OF_BITMAPMODE_SCREEN = "+ofToString(OF_BITMAPMODE_SCREEN));
        lua.doString("OF_BITMAPMODE_VIEWPORT = "+ofToString(OF_BITMAPMODE_VIEWPORT));
        lua.doString("OF_BITMAPMODE_MODEL = "+ofToString(OF_BITMAPMODE_MODEL));
        lua.doString("OF_BITMAPMODE_MODEL_BILLBOARD = "+ofToString(OF_BITMAPMODE_MODEL_BILLBOARD));

		// graphics
		lua.doString("OUTPUT_W = "+ofToString(gapp->gamuzaBase.projectionScreenW));
		lua.doString("OUTPUT_H = "+ofToString(gapp->gamuzaBase.projectionScreenH));
		lua.doString("CAPTURE_W = "+ofToString(gapp->gamuzaBase.workingW));
		lua.doString("CAPTURE_H = "+ofToString(gapp->gamuzaBase.workingH));
		lua.doString("CAPTURE_PIX = "+ofToString(gapp->gamuzaBase.totPixels));

        // OSC messages
        lua.doString("OSC_SENDING_PORT = "+ofToString(atoi(gapp->gamuzaBase.host_port.c_str())));
        lua.doString("OSC_RECEIVING_PORT = "+ofToString(atoi(gapp->gamuzaBase.server_port.c_str())));
        lua.doString("OSC_INT = "+ofToString(OFXOSC_TYPE_INT32));
		lua.doString("OSC_FLOAT = "+ofToString(OFXOSC_TYPE_FLOAT));
		lua.doString("OSC_STRING = "+ofToString(OFXOSC_TYPE_STRING));

		// video tracking
		lua.doString("MAX_BLOBS = "+ofToString(MAX_USERS_HARDLIMIT));
        lua.doString("OPTICAL_FLOW_GRID_X = "+ofToString((int)(gapp->gamuzaBase.workingW/OPTICAL_FLOW_COLS_STEP)));
        lua.doString("OPTICAL_FLOW_GRID_Y = "+ofToString((int)(gapp->gamuzaBase.workingH/OPTICAL_FLOW_ROWS_STEP)));

		// audio analysis
        lua.doString("AUDIO_INPUT_CHANNELS = "+ofToString(gapp->gamuzaBase.audioInputChannels));
        lua.doString("AUDIO_OUTPUT_CHANNELS = "+ofToString(gapp->gamuzaBase.audioOutputChannels));
        lua.doString("BUFFER_SIZE = "+ofToString(gapp->gamuzaBase.audioBufferSize));
		lua.doString("FFT_BANDS = "+ofToString(BARK_SCALE_CRITICAL_BANDS));

		// audio synth
		lua.doString("GA_SINE = "+ofToString(OSC_SINE_WAVE));
		lua.doString("GA_COSINE = "+ofToString(OSC_COSINE_WAVE));
		lua.doString("GA_SAW = "+ofToString(OSC_SAWTOOTH_WAVE));
		lua.doString("GA_TRI = "+ofToString(OSC_TRIANGLE_WAVE));
		lua.doString("GA_RECT = "+ofToString(OSC_RECT_WAVE));
		lua.doString("GA_NOISE = "+ofToString(OSC_WHITE_NOISE));
		lua.doString("GA_PINK = "+ofToString(OSC_PINK_NOISE));
		lua.doString("GA_BROWN = "+ofToString(OSC_BROWN_NOISE));
		lua.doString("GA_PHASOR = "+ofToString(OSC_PHASOR));
		lua.doString("GA_PULSE = "+ofToString(OSC_PULSE));
		// notes
		lua.doString("DO_0 = "+ofToString(DO_0));
		lua.doString("DOB_0 = "+ofToString(DOB0));
		lua.doString("RE_0 = "+ofToString(RE_0));
		lua.doString("REB_0 = "+ofToString(REB_0));
		lua.doString("MI_0 = "+ofToString(MI_0));
		lua.doString("FA_0 = "+ofToString(FA_0));
		lua.doString("FAB_0 = "+ofToString(FAB_0));
		lua.doString("SOL_0 = "+ofToString(SOL_0));
		lua.doString("SOLB_0 = "+ofToString(SOLB_0));
		lua.doString("LA_0 = "+ofToString(LA_0));
		lua.doString("LAB_0 = "+ofToString(LAB_0));
		lua.doString("SI_0 = "+ofToString(SI_0));
		lua.doString("DO_1 = "+ofToString(DO_1));
		lua.doString("DOB_1 = "+ofToString(DOB1));
		lua.doString("RE_1 = "+ofToString(RE_1));
		lua.doString("REB_1 = "+ofToString(REB_1));
		lua.doString("MI_1 = "+ofToString(MI_1));
		lua.doString("FA_1 = "+ofToString(FA_1));
		lua.doString("FAB_1 = "+ofToString(FAB_1));
		lua.doString("SOL_1 = "+ofToString(SOL_1));
		lua.doString("SOLB_1 = "+ofToString(SOLB_1));
		lua.doString("LA_1 = "+ofToString(LA_1));
		lua.doString("LAB_1 = "+ofToString(LAB_1));
		lua.doString("SI_1 = "+ofToString(SI_1));
		lua.doString("DO_2 = "+ofToString(DO_2));
		lua.doString("DOB_2 = "+ofToString(DOB2));
		lua.doString("RE_2 = "+ofToString(RE_2));
		lua.doString("REB_2 = "+ofToString(REB_2));
		lua.doString("MI_2 = "+ofToString(MI_2));
		lua.doString("FA_2 = "+ofToString(FA_2));
		lua.doString("FAB_2 = "+ofToString(FAB_2));
		lua.doString("SOL_2 = "+ofToString(SOL_2));
		lua.doString("SOLB_2 = "+ofToString(SOLB_2));
		lua.doString("LA_2 = "+ofToString(LA_2));
		lua.doString("LAB_2 = "+ofToString(LAB_2));
		lua.doString("SI_2 = "+ofToString(SI_2));
		lua.doString("DO_3 = "+ofToString(DO_3));
		lua.doString("DOB_3 = "+ofToString(DOB3));
		lua.doString("RE_3 = "+ofToString(RE_3));
		lua.doString("REB_3 = "+ofToString(REB_3));
		lua.doString("MI_3 = "+ofToString(MI_3));
		lua.doString("FA_3 = "+ofToString(FA_3));
		lua.doString("FAB_3 = "+ofToString(FAB_3));
		lua.doString("SOL_3 = "+ofToString(SOL_3));
		lua.doString("SOLB_3 = "+ofToString(SOLB_3));
		lua.doString("LA_3 = "+ofToString(LA_3));
		lua.doString("LAB_3 = "+ofToString(LAB_3));
		lua.doString("SI_3 = "+ofToString(SI_3));
		lua.doString("DO_4 = "+ofToString(DO_4));
		lua.doString("DOB_4 = "+ofToString(DOB4));
		lua.doString("RE_4 = "+ofToString(RE_4));
		lua.doString("REB_4 = "+ofToString(REB_4));
		lua.doString("MI_4 = "+ofToString(MI_4));
		lua.doString("FA_4 = "+ofToString(FA_4));
		lua.doString("FAB_4 = "+ofToString(FAB_4));
		lua.doString("SOL_4 = "+ofToString(SOL_4));
		lua.doString("SOLB_4 = "+ofToString(SOLB_4));
		lua.doString("LA_4 = "+ofToString(LA_4));
		lua.doString("LAB_4 = "+ofToString(LAB_4));
		lua.doString("SI_4 = "+ofToString(SI_4));
		lua.doString("DO_5 = "+ofToString(DO_5));
		lua.doString("DOB_5 = "+ofToString(DOB5));
		lua.doString("RE_5 = "+ofToString(RE_5));
		lua.doString("REB_5 = "+ofToString(REB_5));
		lua.doString("MI_5 = "+ofToString(MI_5));
		lua.doString("FA_5 = "+ofToString(FA_5));
		lua.doString("FAB_5 = "+ofToString(FAB_5));
		lua.doString("SOL_5 = "+ofToString(SOL_5));
		lua.doString("SOLB_5 = "+ofToString(SOLB_5));
		lua.doString("LA_5 = "+ofToString(LA_5));
		lua.doString("LAB_5 = "+ofToString(LAB_5));
		lua.doString("SI_5 = "+ofToString(SI_5));
		lua.doString("DO_6 = "+ofToString(DO_6));
		lua.doString("DOB_6 = "+ofToString(DOB6));
		lua.doString("RE_6 = "+ofToString(RE_6));
		lua.doString("REB_6 = "+ofToString(REB_6));
		lua.doString("MI_6 = "+ofToString(MI_6));
		lua.doString("FA_6 = "+ofToString(FA_6));
		lua.doString("FAB_6 = "+ofToString(FAB_6));
		lua.doString("SOL_6 = "+ofToString(SOL_6));
		lua.doString("SOLB_6 = "+ofToString(SOLB_6));
		lua.doString("LA_6 = "+ofToString(LA_6));
		lua.doString("LAB_6 = "+ofToString(LAB_6));
		lua.doString("SI_6 = "+ofToString(SI_6));
		lua.doString("DO_7 = "+ofToString(DO_7));
		lua.doString("DOB_7 = "+ofToString(DOB7));
		lua.doString("RE_7 = "+ofToString(RE_7));
		lua.doString("REB_7 = "+ofToString(REB_7));
		lua.doString("MI_7 = "+ofToString(MI_7));
		lua.doString("FA_7 = "+ofToString(FA_7));
		lua.doString("FAB_7 = "+ofToString(FAB_7));
		lua.doString("SOL_7 = "+ofToString(SOL_7));
		lua.doString("SOLB_7 = "+ofToString(SOLB_7));
		lua.doString("LA_7 = "+ofToString(LA_7));
		lua.doString("LAB_7 = "+ofToString(LAB_7));
		lua.doString("SI_7 = "+ofToString(SI_7));
		lua.doString("DO_8 = "+ofToString(DO_8));
		lua.doString("DOB_8 = "+ofToString(DOB8));
		lua.doString("RE_8 = "+ofToString(RE_8));
		lua.doString("REB_8 = "+ofToString(REB_8));
		lua.doString("MI_8 = "+ofToString(MI_8));
		lua.doString("FA_8 = "+ofToString(FA_8));
		lua.doString("FAB_8 = "+ofToString(FAB_8));
		lua.doString("SOL_8 = "+ofToString(SOL_8));
		lua.doString("SOLB_8 = "+ofToString(SOLB_8));
		lua.doString("LA_8 = "+ofToString(LA_8));
		lua.doString("LAB_8 = "+ofToString(LAB_8));
		lua.doString("SI_8 = "+ofToString(SI_8));

	}

	////////////////////////////////////////////////////////
	/// \section Function & Object Wrappers

	/// ofGraphics
	static void background(int brightness)                                  {ofBackground(brightness);}
	static void background(int r, int g, int b)                             {ofBackground(r, g, b);}
    static void setColor1(int gray)                                         {ofSetColor(gray,gray,gray);}
    static void setColor2(int gray, int alpha)                              {ofSetColor(gray,gray,gray,alpha);}
    static void map5(float v,float iMin,float iMax,float oMin,float oMax)   {ofMap(v,iMin,iMax,oMin,oMax,false);}

    /// ofTrueTypeFont
	static void loadFont2(ofTrueTypeFont* font, string filename, int fontsize) {
		font->loadFont(filename, fontsize);
	}
	static void loadFont4(ofTrueTypeFont* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet) {
		font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet);
	}
    static void loadFont5(ofTrueTypeFont* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours) {
		font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet,makeContours);
	}
    static void loadFont7(ofTrueTypeFont* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet, bool makeContours, float simplifyAmt, float dpi) {
		font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet,makeContours,simplifyAmt,dpi);
	}

    /// ofTrueTypeFontUC
	static void loadFont2UC(ofxTrueTypeFontUC* font, string filename, int fontsize) {
		font->loadFont(filename, fontsize,true,false,0.3,0);
	}
	static void loadFont4UC(ofxTrueTypeFontUC* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet) {
		font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet,0.3,0);
	}

    /// ofxArcText
	static void loadArcFont2(ofxArcText* font, string filename, int fontsize) {
		font->loadFont(filename, fontsize);
	}
	static void loadArcFont4(ofxArcText* font, string filename, int fontsize, bool _bAntiAliased, bool _bFullCharacterSet) {
		font->loadFont(filename, fontsize, _bAntiAliased, _bFullCharacterSet);
	}

    /// ofxDither
    static void ditherOrdered(ofxDither* d, ofImage& imageIn, ofImage& imageOut) {
        d->dither_ordered(imageIn,imageOut);
    }

    /// ofFile
    static void openFile(ofFile* file,string path){
        file->open(path);
    }

    /// ofxFx --> ofxFluid
    static void addTemporalForce(ofxFluid* fluid, ofVec2f _pos, ofVec2f _dir, ofColor _col, float _rad){
        fluid->addTemporalForce(_pos,_dir,_col,_rad);
    }

    static void addConstantForce(ofxFluid* fluid, ofVec2f _pos, ofVec2f _dir, ofColor _col, float _rad){
        fluid->addConstantForce(_pos,_dir,_col,_rad);
    }

    /// ofxOpenCv
    static void scaleIntoMeGray(ofxCvGrayscaleImage* src, ofxCvImage& img){
        src->scaleIntoMe(img);
    }

    static void scaleIntoMeColor(ofxCvColorImage* src, ofxCvImage& img){
        src->scaleIntoMe(img);
    }

    /// ofTexture
    static void loadDataOLD(ofTexture* tex, unsigned char* pix, int w, int h, int _type) {
		tex->loadData(pix, w, h, _type);
	}

	/// global mouse vars
	static float getMouseX() {return (float)gapp->gamuzaBase.scaledMouseX;}
	static float getMouseY() {return (float)gapp->gamuzaBase.scaledMouseY;}

    /// global key vars
    static int getKey() {return (int)gapp->gamuzaBase.liveKey;}

};
