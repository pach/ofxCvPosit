#include "testApp.h"
#include "GLDrawToolkit.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	
	selCal = 2 ; 
	
	printf("setup\n");
	
	calibrationMode = 0; 
	calibrationCount = 0;
	idDraggedPoint = 0;
	for (int i=0; i<4; i++) {
		calibrationPoint[i] = 0.;
	}
	
	//cal->setSize(ofGetWidth(), ofGetHeight());
	//cal->calcGLPersp(0.1, 1000);
	
	posit.initialize(1., ofGetWidth(), ofGetHeight(), 0.1, 1000);	
	eye[0] = 0.0;
	eye[1] = 0.0;
	eye[2] = 0.0;
	rot[0] = 0.;
	rot[1] = 0.0;
	rot[2] = 0.0 ;
	posit.buildRealPose( rot, eye );	
	posit.projectModelPoints( posit.poseReal, posit.srcImagePoints );
	posit.poseEstimation();
	posit.projectModelPoints( posit.posePOSIT, posit.estimatedImagePoints );
	
	move = false ; 
	
	printf("setup done\n");
}

//--------------------------------------------------------------
void testApp::update(){
	ofBackground(75, 75, 75);

}

//--------------------------------------------------------------
void testApp::draw(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	ofSetColor(255, 255, 255);

	ofSetColor(0xffffff);
	ofDrawBitmapString("fov : "+ofToString(posit.getFocal(), 0), 10, 10);

	ofSetColor(255, 255, 255);
	ofCircle(ofMap(calibrationPoint[0].x, -ofGetWidth()/2, ofGetWidth()/2, 0, ofGetWidth(), 0), ofMap(calibrationPoint[0].y, ofGetHeight()/2, -ofGetHeight()/2, 0, ofGetHeight(), 0), 2);
	ofSetColor(255, 255, 0);
	ofCircle(ofMap(calibrationPoint[1].x, -ofGetWidth()/2, ofGetWidth()/2, 0, ofGetWidth(), 0), ofMap(calibrationPoint[1].y, ofGetHeight()/2, -ofGetHeight()/2, 0, ofGetHeight(), 0), 2);
	ofSetColor(255, 0, 255);
	ofCircle(ofMap(calibrationPoint[2].x, -ofGetWidth()/2, ofGetWidth()/2, 0, ofGetWidth(), 0), ofMap(calibrationPoint[2].y, ofGetHeight()/2, -ofGetHeight()/2, 0, ofGetHeight(), 0), 2);
	ofSetColor(0, 255, 255);
	ofCircle(ofMap(calibrationPoint[3].x, -ofGetWidth()/2, ofGetWidth()/2, 0, ofGetWidth(), 0), ofMap(calibrationPoint[3].y, ofGetHeight()/2, -ofGetHeight()/2, 0, ofGetHeight(), 0), 2);
	
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf( posit.projectionMatrix );
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix() ; 
	
	//Draw the object with the estimated pose
	glLoadIdentity();
	glScalef( 1.0f, 1.0f, -1.0f);
	glMultMatrixf( posit.posePOSIT );
	

	// draw video sur plan xy
	ofSetColor(0xffffff);

	GLDrawToolkit::drawGrid();
	
	glPopMatrix();
	

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
	if(key == 'c'|| key == 'C')
	{	
		printf("entering calibration mode\n");
		calibrationMode = 1 ; 
		calibrationCount = 0 ;
	}
	


	if (key=='a')
	{
		int f = posit.getFocal();
		posit.setFocal(f+=10);
		printf("new focal : %i", f+100);
		runCalibration();
	}
	if (key=='A')
	{
		int f = posit.getFocal();
		posit.setFocal(f+=1);
		printf("new focal : %i", f+10);
		runCalibration();
	}
	if (key=='z')
	{
		int f = posit.getFocal();
		posit.setFocal(f-=10);
		printf("new focal : %i", f-100);
		runCalibration();
	}
	if (key=='Z')
	{
		int f = posit.getFocal();
		posit.setFocal(f-=1);
		printf("new focal : %i", f-10);
		runCalibration();
	}
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	printf("mouse dragged call\n");
	int px, py;
	px = ofMap(x, 0, ofGetWidth(), -ofGetWidth()/2., ofGetWidth()/2, 0);
	py = ofMap(y, 0, ofGetHeight(), ofGetHeight()/2., -ofGetHeight()/2., 0);
	if (!calibrationMode){
		calibrationPoint[idDraggedPoint] = ofPoint(px,py);
		switch (idDraggedPoint) {
			case 0:
			//	cal->setO(calibrationPoint[0].x, calibrationPoint[0].y);
				posit.srcImagePoints.at(0).x = px;
				posit.srcImagePoints.at(0).y = py;
				runCalibration();
				break;
			case 1:
			//	cal->setX(calibrationPoint[1].x, calibrationPoint[1].y);
				posit.srcImagePoints.at(1).x = px;
				posit.srcImagePoints.at(1).y = py;
				runCalibration();
				break;
			case 2:
			//	cal->setZ(calibrationPoint[2].x, calibrationPoint[2].y);
				posit.srcImagePoints.at(2).x = px;
				posit.srcImagePoints.at(2).y = py;
				runCalibration();
				break;
			case 3:
			//	cal->setY(calibrationPoint[3].x, calibrationPoint[3].y);
				posit.srcImagePoints.at(3).x = px;
				posit.srcImagePoints.at(3).y = py;
				runCalibration();
				break;
			case 4:
				//	cal->setY(calibrationPoint[3].x, calibrationPoint[3].y);
				posit.srcImagePoints.at(4).x = px;
				posit.srcImagePoints.at(4).y = py;
				runCalibration();
				break;
			case 5:
				//	cal->setY(calibrationPoint[3].x, calibrationPoint[3].y);
				posit.srcImagePoints.at(5).x = px;
				posit.srcImagePoints.at(5).y = py;
				runCalibration();
				break;
			case 6:
				//	cal->setY(calibrationPoint[3].x, calibrationPoint[3].y);
				posit.srcImagePoints.at(6).x = px;
				posit.srcImagePoints.at(6).y = py;
				runCalibration();
				break;
			default:
				break;
		}
	}
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	printf("mouse pressed called\n");
	
	int px, py;
	px = ofMap(x, 0, ofGetWidth(), -ofGetWidth()/2., ofGetWidth()/2, 0);
	py = ofMap(y, 0, ofGetHeight(), ofGetHeight()/2., -ofGetHeight()/2., 0);
	
	if (calibrationMode){
		printf("point : %i %i\n",x,y);

		calibrationPoint[calibrationCount] = ofPoint(px,py);
		calibrationCount ++;
		if (calibrationCount == 4) {
		//	cal->setO(calibrationPoint[0].x, calibrationPoint[0].y);
			posit.srcImagePoints.at(0).x = calibrationPoint[0].x;
			posit.srcImagePoints.at(0).y = calibrationPoint[0].y;
		//	cal->setX(calibrationPoint[1].x, calibrationPoint[1].y);
			posit.srcImagePoints.at(1).x = calibrationPoint[1].x;
			posit.srcImagePoints.at(1).y = calibrationPoint[1].y;
		//	cal->setY(calibrationPoint[3].x, calibrationPoint[3].y);
			posit.srcImagePoints.at(2).x = calibrationPoint[2].x;
			posit.srcImagePoints.at(2).y = calibrationPoint[2].y;
		//	cal->setZ(calibrationPoint[2].x, calibrationPoint[2].y);
			posit.srcImagePoints.at(3).x = calibrationPoint[3].x;
			posit.srcImagePoints.at(3).y = calibrationPoint[3].y;

			calibrationCount = 0 ; 
			calibrationMode = 0 ; 
			
			runCalibration();
		}
	}else {
		// recherche le point le plus pret
		float d1, d2, d3, d4, d5, d6, d7 ;
		d1 = ofDist(px, py, calibrationPoint[0].x, calibrationPoint[0].y);
		d2 = ofDist(px, py, calibrationPoint[1].x, calibrationPoint[1].y);
		d3 = ofDist(px, py, calibrationPoint[2].x, calibrationPoint[2].y);
		d4 = ofDist(px, py, calibrationPoint[3].x, calibrationPoint[3].y);

		float minPoint = d1; 
		int idMinPoint = 0 ; 
		
		if (minPoint > d2){
			minPoint = d2 ;
			idMinPoint = 1 ; 
		}
		if (minPoint > d3){
			minPoint = d3 ; 
			idMinPoint = 2 ; 
		}
		if (minPoint > d4) {
			minPoint = d4 ; 
			idMinPoint = 3 ;
		}

		idDraggedPoint = idMinPoint ; 
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	posit.initializeIntrinsics( w,h);
	posit.createOpenGLProjectionMatrix( w, h , 1.0, 1000.0 );
}

void testApp::runCalibration(){
	posit.poseEstimation();
}
