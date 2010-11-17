#ifndef POSIT_H
#define POSIT_H

/****************************************
*										*
*			OPENCV POSIT TUTORIAL		*
*		Javier Barandiaran Martirena	*
*			       2006					*
*										*
****************************************/


#include <OpenCV/OpenCV.h>
#include <vector>


//#define FOCAL_LENGTH 760
//#define FOCAL_LENGTH 2500
#define _DEBUG 1

class ofxCvPosit  
{
public:
	ofxCvPosit();
	virtual ~ofxCvPosit();

	void initialize( const double &cubeSize,
						const double &aWidth, const double &aHeight,
						const double &nearPlane, const double &farPlane );
	void initializeIntrinsics( const double &aWidth, const double &aHeight );
	void poseEstimation();
	void createOpenGLMatrixFrom( const CvMatr32f &rotationMatrix, const CvVect32f &translationVector);
	void createOpenGLProjectionMatrix(	const double &width, const double &height,
										const double &nearPlane, const double &farPlane );
	void projectModelPoints( float *pose, std::vector<CvPoint2D32f> &projectedPoints );

	void buildRealPose( float *rot, float *trans );
	
	double width, height; //Image size
	CvMat *intrinsics;
	float posePOSIT[16];
	float poseReal[16];
	float projectionMatrix[16];

	std::vector<CvPoint3D32f> modelPoints;
	std::vector<CvPoint2D32f> srcImagePoints;
	std::vector<CvPoint2D32f> estimatedImagePoints;

	CvPOSITObject* positObject;
	
	int focalLength ; 
	double near, far ; 
	int getFocal() ; 
	void setFocal (int focal); 
};

#endif