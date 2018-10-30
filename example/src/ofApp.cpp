#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    stepperManager.setup("MotorsNEW.json");
    stepperManager.setupGui();
}

//--------------------------------------------------------------
void ofApp::update(){

    stepperManager.motors[0].goToPosition(stepperManager.motors[0].position);
    stepperManager.motors[0].setVelocity(stepperManager.motors[0].velocity);
    stepperManager.motors[0].setAcceleration(stepperManager.motors[0].acceleration);

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofDrawBitmapString(stepperManager.motors[0].getPositionAsString(), ofGetWidth()-100,100);
    stepperManager.guiMotors.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    stepperManager.motors[0].goToPosition(500);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}