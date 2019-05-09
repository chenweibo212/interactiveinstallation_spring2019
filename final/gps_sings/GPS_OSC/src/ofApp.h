#pragma once

#include "ofMain.h"
#include "ofxJSON.h"
#include "ofxOsc.h"

#define HOST "localhost"

//port
#define SEND_PORT 9001
#define RECEIVE_PORT 9002

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void getSatelliteData();
    void clearSatelliteData();
    
    ofxJSONElement *json = new ofxJSONElement[31];
    ofxJSONElement json1;
    string API_KEY = "C4VE3X-ZDRPGN-44N2AV-3ZOJ";
    vector <std::string> API_URL;
    vector <std::string> RAW_JSON;
    vector <bool> parsingSuccessful;
    
    ofBuffer bufferGPS_SATELLITES_ID;
    vector <string> GPS_SATELLITES_ID;
    
    bool gotData = false;
    bool vectorCleared = false;
    std::vector <float> locationX;
    std::vector <float> locationY;
    std::vector <float> locationZ;
//    std::vector <string> locationX, locationY;
    
    int startTime, endTime, currentTime;
    
    ofxOscSender sender;
    ofxOscReceiver receiver;
};
