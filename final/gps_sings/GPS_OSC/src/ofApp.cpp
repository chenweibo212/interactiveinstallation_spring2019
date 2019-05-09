#include "ofApp.h"
using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofLog() << "listening for osc messages on port " << RECEIVE_PORT;
    ofLog() << "sending osc messages on port " << SEND_PORT;
    // open an outgoing connection to HOST:PORT
    sender.setup(HOST, SEND_PORT);
    receiver.setup(RECEIVE_PORT);
    
    bufferGPS_SATELLITES_ID = ofBufferFromFile("GPS_SATELLITES_ID.txt");
    for (auto lineX : bufferGPS_SATELLITES_ID.getLines()){
        GPS_SATELLITES_ID = ofSplitString(lineX, ";");
        GPS_SATELLITES_ID.push_back(lineX); //need to remove line break before each string
    }
    
    for (int i = 0; i < GPS_SATELLITES_ID.size()-2; i++){
        //total 31 satellites
        //get the location of all satelites in next 1 second from my current view point(41.702, -76.014)
        API_URL.push_back("https://www.n2yo.com/rest/v1/satellite/positions/" + GPS_SATELLITES_ID[i] + "/40.714/-74.005/0/1/&apiKey=" + API_KEY);
    }
    
    startTime = ofGetElapsedTimeMillis();
    endTime = 10000;
}

//--------------------------------------------------------------
void ofApp::update(){
    ofxOscMessage m_locationX;
    ofxOscMessage m_locationY;
    ofxOscMessage m_locationZ;
    
    currentTime = ofGetElapsedTimeMillis() - startTime;
    if (currentTime >= endTime){
        getSatelliteData();
        
        std::stringstream ss_locationX, ss_locationY, ss_locationZ;
        for(size_t i = 0; i < locationX.size(); ++i)
        {
            if(i != 0)
            ss_locationX << "/";
            ss_locationX << locationX[i];
        }
        for(size_t i = 0; i < locationY.size(); ++i){
            if(i != 0)
            ss_locationY << "/";
            ss_locationY << locationY[i];
        }
        for(size_t i = 0; i < locationZ.size(); ++i){
            if(i != 0)
            ss_locationZ << "/";
            ss_locationZ << locationZ[i];
        }
        std::string s_locationX = ss_locationX.str();
        std::string s_locationY = ss_locationY.str();
        std::string s_locationZ = ss_locationZ.str();
        
        
        ofLogNotice() << "X:" << s_locationX;
        ofLogNotice() << "Y:" << s_locationY;
        ofLogNotice() << "Z:" << s_locationZ;
        
        //send through osc
        m_locationX.setAddress("/location/0/");
        m_locationY.setAddress("/location/1/");
        m_locationZ.setAddress("/location/2/");
        m_locationX.addStringArg(s_locationX);
        m_locationY.addStringArg(s_locationY);
        m_locationZ.addStringArg(s_locationZ);
        sender.sendMessage(m_locationX, false);
        sender.sendMessage(m_locationY, false);
        sender.sendMessage(m_locationZ, false);
        
        ofLogNotice() << "message sent";
        
        //clear array
        clearSatelliteData();
        ofLogNotice() << "array cleared";
        
        //reset timer
        startTime = ofGetElapsedTimeMillis();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    currentTime = ofGetElapsedTimeMillis() - startTime;
//    if (currentTime >= endTime){
//        getSatelliteData();
//
//        for (int i = 0; i < locationX.size(); i++){
//            ofLogNotice() << locationX[i];
//        }
//        //send through osc
//
//        //clear array
//        clearSatelliteData();
//
//        //reset timer
//        startTime = ofGetElapsedTimeMillis();
//    }
}

//--------------------------------------------------------------

void ofApp::getSatelliteData(){
    //parsing JSON
    for (int i = 0; i < API_URL.size(); i++){
        parsingSuccessful.push_back(json[i].open(API_URL[i]));
    }
    
    for (int i = 0; i < parsingSuccessful.size(); i++){
        RAW_JSON.push_back(json[i].getRawString(true));
    }
    
    for (int j = 0; j < RAW_JSON.size(); j++){
        for (Json::ArrayIndex i = 0; i < json[j]["positions"].size(); ++i)
        {
            std::string sataltitude  = json[j]["positions"][i]["sataltitude"].asString();
            std::string satlatitude = json[j]["positions"][i]["satlatitude"].asString();
            std::string satlongitude   = json[j]["positions"][i]["satlongitude"].asString();
            std::string index = ofToString(j);
            std::string text = index + "satid: "  + GPS_SATELLITES_ID[j] + "sataltitude: " + sataltitude + " ; " + "satlatitude: " + satlatitude + " ; " + "satlongitude: " + satlongitude;
            
            float x = ofToFloat(satlongitude);
            float y = ofToFloat(satlatitude);
            float z = ofToFloat(sataltitude);
            locationX.push_back(x);
            locationY.push_back(y);
            locationZ.push_back(z);
        }
    }
}

//--------------------------------------------------------------

void ofApp::clearSatelliteData(){
    parsingSuccessful.clear();
    RAW_JSON.clear();
    locationX.clear();
    locationY.clear();
    locationZ.clear();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
