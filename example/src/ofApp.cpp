#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    gui.setup("Phidgets");
    
    myMotor.setup("motor1.xml", true);
    gui.add(myMotor.setupGui());
    
}

//--------------------------------------------------------------
void ofApp::update(){

    myMotor.goToPosition(myMotor.position);
    myMotor.setVelocity(myMotor.velocity);
    myMotor.setAcceleration(myMotor.acceleration);

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofDrawBitmapString(myMotor.getPositionAsString(), 100,100);
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    myMotor.goToPosition(150000);
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