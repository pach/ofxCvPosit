#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxCvPosit.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
	
	void runCalibration();
	
	private : 
	int camWidth, camHeight ; 
	ofVideoGrabber vidGrabber;
	ofTexture videoTexture;

	
	//CvCal *cal ; 
	ofxCvPosit posit ; 
	
	float eye[3] ;
	float rot[3] ;
	
	int selCal ; // 0 pas de cal, 1 cvcal, 2 posit
	
	int calibrationMode ; 
	int calibrationCount ; 
	ofPoint calibrationPoint[7] ; 
	int idDraggedPoint ; 

	bool move ; 
	
	ofImage image ;
	ofTexture tex ; 
};

#endif
