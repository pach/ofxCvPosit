#include "ofxCvPosit.h"
#include <iostream>
#include "ofMain.h"

using namespace std;

ofxCvPosit::ofxCvPosit()
{
	focalLength = 2100    ; 
}

ofxCvPosit::~ofxCvPosit()
{
	cvReleasePOSITObject(&positObject);
	cvReleaseMat(&intrinsics);
}

void ofxCvPosit::initialize( const double &cubeSize,
							const double &aWidth, const double &aHeight,
							const double &nearPlane, const double &farPlane )
{
	width = aWidth;
	height = aHeight;
	near = nearPlane ;
	far = farPlane ;

	//Generate four model points
	//The first one must be (0,0,0)
	modelPoints.push_back(cvPoint3D32f(0.0f, 0.0f, 0.0f));
	//modelPoints.push_back(cvPoint3D32f(cubeSize, 0.0f, -cubeSize));
	modelPoints.push_back(cvPoint3D32f(cubeSize, 0.0f, 0.0f));
	modelPoints.push_back(cvPoint3D32f(0.0f, cubeSize, 0.0f));
	modelPoints.push_back(cvPoint3D32f(0.0f, 0.0f, -cubeSize));
/*	modelPoints.push_back(cvPoint3D32f(cubeSize, cubeSize, 0.0f));
	modelPoints.push_back(cvPoint3D32f(0.0f, cubeSize, -cubeSize));
	modelPoints.push_back(cvPoint3D32f(cubeSize, 0.0f, -cubeSize));
*/	
	//Create the POSIT object with the model points
	positObject = cvCreatePOSITObject( &modelPoints[0], (int)modelPoints.size() );

	intrinsics = cvCreateMat( 3, 3, CV_32F );
	initializeIntrinsics( width, height );
	createOpenGLProjectionMatrix( width, height, near, far );
}

void ofxCvPosit::initializeIntrinsics( const double &aWidth, const double &aHeight )
{	
	width = aWidth;
	height = aHeight;
	cvSetZero( intrinsics );
	cvmSet( intrinsics , 0, 0, focalLength );
	cvmSet( intrinsics , 1, 1, focalLength );
	cvmSet( intrinsics , 0, 2, width * 0.5 );//principal point in the centre of the image
	cvmSet( intrinsics , 1, 2, height * 0.5 );
	cvmSet( intrinsics , 2, 2, 1.0 );
}

void ofxCvPosit::poseEstimation()
{
	CvMatr32f rotation_matrix = new float[9];
	CvVect32f translation_vector = new float[3];
	//set posit termination criteria: 100 max iterations, convergence epsilon 1.0e-5
	CvTermCriteria criteria = cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 1000, 1.0e-4f);
	cvPOSIT( positObject, &srcImagePoints[0], focalLength, criteria, rotation_matrix, translation_vector );	

	createOpenGLMatrixFrom( rotation_matrix, translation_vector);
	
	//Show the results
	#ifdef _DEBUG		
		cout << "\n\n-......- POSE ESTIMATED -......-\n";
		cout << "\n-.- MODEL POINTS -.-\n";
		for ( size_t  p=0; p<modelPoints.size(); p++ )
			cout << modelPoints[p].x << ", " << modelPoints[p].y << ", " << modelPoints[p].z << "\n";

		cout << "\n-.- IMAGE POINTS -.-\n";
		for ( size_t p=0; p<modelPoints.size(); p++ )
			cout << srcImagePoints[p].x << ", " << srcImagePoints[p].y << " \n";

		cout << "\n-.- REAL POSE\n";
		for ( size_t p=0; p<4; p++ )
			cout << poseReal[p] << " | " << poseReal[p+4] << " | " << poseReal[p+8] << " | " << poseReal[p+12] << "\n";

		cout << "\n-.- ESTIMATED POSE\n";
		for ( size_t p=0; p<4; p++ )
			cout << posePOSIT[p] << " | " << posePOSIT[p+4] << " | " << posePOSIT[p+8] << " | " << posePOSIT[p+12] << "\n";
	#endif

	delete rotation_matrix;
	delete translation_vector;
}

void ofxCvPosit::createOpenGLMatrixFrom(const CvMatr32f &rotationMatrix, const CvVect32f &translationVector)
{
	//coordinate system returned is relative to the first 3D input point	
	for (int f=0; f<3; f++)
	{
		for (int c=0; c<3; c++)
		{
			posePOSIT[c*4+f] = rotationMatrix[f*3+c];	//transposed
		}
	}	
	posePOSIT[3] = 0.0;
	posePOSIT[7] = 0.0;	
	posePOSIT[11] = 0.0;
	posePOSIT[12] = translationVector[0];
	posePOSIT[13] = translationVector[1]; 
	posePOSIT[14] = translationVector[2];
	posePOSIT[15] = 1.0;	
}

void ofxCvPosit::createOpenGLProjectionMatrix( const double &width, const double &height,
									const double &nearPlane, const double &farPlane )
{
	projectionMatrix[0] = 2.0 * cvmGet( intrinsics, 0, 0 ) / width;
	projectionMatrix[1] = 0.0;
	projectionMatrix[2] = 0.0;
	projectionMatrix[3] = 0.0;

	projectionMatrix[4] = 0.0;
	projectionMatrix[5] = 2.0 * cvmGet( intrinsics, 1, 1 ) / height;
	projectionMatrix[6] = 0.0;
	projectionMatrix[7] = 0.0;
	
	projectionMatrix[8] = 2.0 * ( cvmGet( intrinsics, 0, 2 ) / width) - 1.0;
	projectionMatrix[9] = 2.0 * ( cvmGet( intrinsics, 1, 2 ) / height ) - 1.0;	
	projectionMatrix[10] = -( farPlane+nearPlane ) / ( farPlane - nearPlane );
	projectionMatrix[11] = -1.0;

	projectionMatrix[12] = 0.0;
	projectionMatrix[13] = 0.0;
	projectionMatrix[14] = -2.0 * farPlane * nearPlane / ( farPlane - nearPlane );		
	projectionMatrix[15] = 0.0;
}

void ofxCvPosit::projectModelPoints( float *pose, vector<CvPoint2D32f> &projectedPoints )
{
	// The origin of the coordinates system is in the centre of the image
	projectedPoints.clear();
	CvMat poseMatrix = cvMat( 4, 4, CV_32F, pose );
	for ( size_t  p=0; p<modelPoints.size(); p++ )
	{
		float modelPoint[] =  { modelPoints[p].x, modelPoints[p].y, modelPoints[p].z, 1.0f };
		CvMat modelPointMatrix = cvMat( 4, 1, CV_32F, modelPoint );
		float point3D[4];
		CvMat point3DMatrix = cvMat( 4, 1, CV_32F, point3D );
		cvGEMM( &poseMatrix, &modelPointMatrix, 1.0, NULL, 0.0, &point3DMatrix, CV_GEMM_A_T );

		//Project the transformed 3D points
		CvPoint2D32f point2D = cvPoint2D32f( 0.0, 0.0 );
		if ( point3D[2] != 0 )
		{
			point2D.x = cvmGet( intrinsics, 0, 0 ) * point3D[0] / point3D[2]; 
			point2D.y = cvmGet( intrinsics, 1, 1 ) * point3D[1] / point3D[2];	
		}
		projectedPoints.push_back( point2D );
	}
}

void ofxCvPosit::buildRealPose( float *rot, float *trans )
{
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glTranslatef( trans[0], trans[1], trans[2] );
	glRotatef( rot[0], 1.0f, 0.0f, 0.0f );
	glRotatef( rot[1], 0.0f, 1.0f, 0.0f );
	glRotatef( rot[2], 0.0f, 0.0f, 1.0f );
	glGetFloatv(GL_MODELVIEW_MATRIX, poseReal );
}

int ofxCvPosit::getFocal() {
	return focalLength;
} 

void ofxCvPosit::setFocal (int focal) {
	focalLength = focal;
	initializeIntrinsics( width, height );
	createOpenGLProjectionMatrix( width, height, near, far );
} 
