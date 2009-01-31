#ifndef _OFX_BAZAR_DETECTOR_
#define _OFX_BAZAR_DETECTOR_

#include "ofMain.h"
#include "ofxBazAR.h"

struct ofxBazARModel
{
	bool 	isActive, isTrained, isDetected;
	int		deadTick, deadTickMAX;
	string	nameID;
	planar_object_recognizer		por;
	ofxCvGrayscaleImage 			mImage;

	void load_classifier(string _dirname) {
		isActive = false;
		isTrained = false;
		if( por.load( ofToDataPath(nameID) ) ) {
			isTrained = true;
			isActive = true;
		}
		
	}
	
	void create_classifier(ofxCvGrayscaleImage & _newImage) {
		isActive = false;
		isTrained = false;
		mImage = _newImage;

		if( por.build(
					mImage.getCvImage(), 		// mode image file name
					400,               			// maximum number of keypoints on the model
					32,                			// patch size in pixels
					3,                 			// yape radius. Use 3,5 or 7.
					16,                			// number of trees for the classifier. Somewhere between 12-50
					3                  			// number of levels in the gaussian pyramid
					))
		{
			// printf("detector trained..\n");
			por.save(nameID + ".classifier");
			isTrained = true;
			isActive = true;
		} else {
			// printf("detector load error..\n");
		}
	}
	
	void init() {
		por.match_score_threshold=.03f;
		por.ransac_dist_threshold = 5;
		por.max_ransac_iterations = 500;
		por.non_linear_refine_threshold = 1.5;
		por.min_view_rate=.2;
		por.views_number = 100;
		deadTick = 0;
		deadTickMAX = 3;
		
		mImage.allocate(320, 240);
		isTrained = false;
	}
};

struct ofxBazARGroundModel
{
	bool 	isActive, isTrained, isDetected;
	string	nameID;
	planar_object_recognizer		por;
	ofxCvGrayscaleImage 			mImage;
	ofxCvGrayscaleImage 			mImageCache;
	CamCalibration					calib;
	// static vector<CamCalibration::s_struct_points> 	pts;
	vector<CamCalibration::s_struct_points> 	pts;

	bool							doHomographies;
	int								nbHomography;
	bool							isCalibrated;


	void resetGround() {
		isActive = true;
		nbHomography = 0;
		doHomographies = false;
		// ..
	}

	bool add_detected_homography(planar_object_recognizer &detector, CamCalibration &calib) {
		// static std::vector<CamCalibration::s_struct_points> pts;
		pts.clear();
    
		for (int i=0; i<detector.match_number; ++i) {
				image_object_point_match * match = detector.matches+i;
				if (match->inlier) {
					pts.push_back(CamCalibration::s_struct_points(
						PyrImage::convCoordf(match->image_point->u, int(match->image_point->scale), 0),
						PyrImage::convCoordf(match->image_point->v, int(match->image_point->scale), 0),
						PyrImage::convCoordf((float)match->object_point->M[0], int(match->object_point->scale), 0),
						PyrImage::convCoordf((float)match->object_point->M[1], int(match->object_point->scale), 0)));
				}
		}
		return calib.AddHomography(0, pts, detector.H);
	}
	
	// void processNextImage(ofxCvGrayscaleImage _newImage) {
	void processNextImage(ofImage* _newImage) {
		//  mImageCache = _newImage;
		mImageCache = (*_newImage).getPixels();
		if (nbHomography != -1) {
            
			if (!doHomographies) {
				if (isActive) {

					printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!! train\n\n\n");
					isTrained = false;
					mImage = mImageCache;
					
					if( por.build(
								mImage.getCvImage(), 		// mode image file name
								400,               			// maximum number of keypoints on the model
								32,                			// patch size in pixels
								3,                 			// yape radius. Use 3,5 or 7.
								16,                			// number of trees for the classifier. Somewhere between 12-50
								3                  			// number of levels in the gaussian pyramid
								))
					{
						isTrained = true;
					}

					por.match_score_threshold=.03f;
					doHomographies = true;

				}
				
			} else {
				printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!! %i homographies\n\n\n", nbHomography);
				
				if (por.detect( mImageCache.getCvImage() ) ) {
				// if (por.detect( _newImage.getCvImage() ) ) {
            	
					add_detected_homography(por, calib);
					
					nbHomography++;
					printf("\n\n\n!!!!!!!--NEW--!!!!!!!!!!!! %i homographies\n\n\n", nbHomography);
            	
					if (nbHomography >=70) {
						if (calib.Calibrate(
									50, // max hom
									2,   // random
									3,
									3,   // padding ratio 1/2
									0,
									0,
									0.0078125,	//alpha
									0.9,		//beta
									0.001953125,//gamma
									12,	  // iter
									0.05, //eps
									3   //postfilter eps
								   )) {

							calib.PrintOptimizedResultsToFile1();
							isCalibrated = true;
							nbHomography = -1;
							printf("\n\n\n!!!!!!!!!!!!!!!!!!!!!!!!!! isCalibrated :)\n\n\n");
							// break;
							
						}
					}
            	
				}
				
				
			}
        
			
		}

	}
	
	
	
	void init() {
		por.ransac_dist_threshold = 5;
		por.max_ransac_iterations = 800;
		por.non_linear_refine_threshold = 1.5;
		
		por.match_score_threshold=.03f;
		por.ransac_dist_threshold = 5;
		por.max_ransac_iterations = 500;
		por.non_linear_refine_threshold = 1.5;
		por.min_view_rate=.2;
		por.views_number = 100;
		
		doHomographies = false;
		isCalibrated = false;
		nbHomography = 0;
		isActive = true;

		mImage.allocate(320, 240);
		mImageCache.allocate(320, 240);
		calib.AddCamera(320, 240);
		isTrained = false;
	}
};


class ofxBazARDetector {
	
	public:

		bool	isPaused;
		int		width, height, frameSkip, frameTick;

		ofImage						tmpImg;
		ofxCvColorImage				colorImg;
		ofxCvGrayscaleImage			detectImage;

		vector <ofxBazARModel*>		mBazARModels;

		void setup(int _width, int _height) {
			width = _width;
			height = _height;
			isPaused  = false;
			colorImg.allocate(width,height);
			detectImage.allocate(width, height);
			frameSkip = 3;
			frameTick = 0;
		}

		void load_classifier(string _classifier_dirname) {
			int _id = mBazARModels.size();
			mBazARModels.push_back( new ofxBazARModel() );
			mBazARModels[_id]->init();
			mBazARModels[_id]->nameID = _classifier_dirname;
			
			tmpImg.loadImage(_classifier_dirname + "/original_image.bmp");
			tmpImg.setImageType( OF_IMAGE_GRAYSCALE );
			detectImage = tmpImg.getPixels();

			mBazARModels[_id]->mImage = detectImage.getPixels();
			mBazARModels[_id]->load_classifier( _classifier_dirname );
		}

		void create_new_classifier() {
			int _id = mBazARModels.size();
			mBazARModels.push_back( new ofxBazARModel() );
			mBazARModels[_id]->init();
			mBazARModels[_id]->nameID = "model-" + ofToString(_id);
			mBazARModels[_id]->create_classifier( detectImage );
		}
		
		void processNextImage(unsigned char * _pixels, int _w, int _h, int _type=OF_IMAGE_COLOR) {
		if (frameTick >= frameSkip) {
				frameTick = 0;

				colorImg.setFromPixels( _pixels, 320,240);
				detectImage = colorImg;

				for( int i = 0; i < mBazARModels.size(); i += 1 ) {
					if ( mBazARModels[i]->isActive ) {
						if ( mBazARModels[i]->por.detect( detectImage.getCvImage() ) ) {
							mBazARModels[i]->isDetected = true;
							mBazARModels[i]->deadTick = 0;
						} else {
							if (mBazARModels[i]->deadTick >= mBazARModels[i]->deadTickMAX) {
								mBazARModels[i]->isDetected = false;
							} else {
								mBazARModels[i]->deadTick++;
							}
						}
					} else {
						printf("\n\n%s is paused and not updated..\n\n", mBazARModels[i]->nameID.c_str() );
					}
				}
				
		} else {
			frameTick++;
		}
		}

};


struct ofxBazARAugmentation {
	CamAugmentation 	augment;
	ofxBazARDetector 	detectors;
	ofxBazARGroundModel	mGround;
	
	bool				doGround;
	
	// static std::vector<CamCalibration::s_struct_points> pts;
	vector<CamCalibration::s_struct_points> pts;
	ofxCvGrayscaleImage 			detectImage;
	
	void setup() {
		augment.LoadOptimalStructureFromFile("camera_c.txt", "camera_r_t.txt");
		detectors.setup(320,240);
		mGround.init();
	}

	void generateGround(ofImage* _newImage) {
		mGround.processNextImage( _newImage );
		if (mGround.nbHomography == -1) {
			augment.LoadOptimalStructureFromFile("camera_c.txt", "camera_r_t.txt");
			// augment.Clear();		
		}
	}
	
	void updateGround(ofImage* _newImage) {
		// if ( mGround.por.detect( detectImage.getCvImage() ) ) {
		// 	add_detected_homography(mGround.por, augment);
		// }
	}

	void processNextImage(ofImage* _newImage) {
		detectImage = (*_newImage).getPixels();
		// augment.Clear();
		
		if (mGround.nbHomography != -1)			generateGround( _newImage );
		else if (mGround.nbHomography == -1)	updateGround( _newImage );

		for( int i = 0; i < detectors.mBazARModels.size(); i += 1 ) {
			
			if (detectors.mBazARModels[i]->isActive) {
				if ( detectors.mBazARModels[i]->por.detect( detectImage.getCvImage() ) ) {
        
					add_detected_homography(detectors.mBazARModels[i]->por, augment);
					// augment.Accomodate(4, 1e-4);
					detectors.mBazARModels[i]->isDetected = true;                         
        
				} else {
					detectors.mBazARModels[i]->isDetected = false;
				}
				
			}
        
		}
		
		
		augment.Accomodate(4, 1e-4);

	}
	
	bool add_detected_homography(planar_object_recognizer &detector, CamAugmentation &a)
	{
		pts.clear();

		for (int i=0; i<detector.match_number; ++i) {
				image_object_point_match * match = detector.matches+i;
				if (match->inlier) {
					pts.push_back(CamCalibration::s_struct_points(
						PyrImage::convCoordf(match->image_point->u, int(match->image_point->scale), 0),
						PyrImage::convCoordf(match->image_point->v, int(match->image_point->scale), 0),
						PyrImage::convCoordf(match->object_point->M[0], int(match->object_point->scale), 0),
						PyrImage::convCoordf(match->object_point->M[1], int(match->object_point->scale), 0)));
				}
		}

		a.AddHomography(pts, detector.H);
		return true;
	}
	
	void render_matrix() {
		
		CvMat *m = augment.GetProjectionMatrix(0);
		if (!m) return;

		double w =320/2.0;
		double h =240/2.0;

		// 3D coordinates of an object
		double pts[4][4] = {
			{w,h,0, 1},
			{2*w,h,0, 1},
			{w,2*h,0, 1},
			{w,h,-w-h, 1}
		};
		double projected[3][4];
		CvMat ptsMat, projectedMat;
		cvInitMatHeader(&ptsMat, 4, 4, CV_64FC1, pts);
		cvInitMatHeader(&projectedMat, 3, 4, CV_64FC1, projected);

		cvGEMM(m, &ptsMat, 1, 0, 0, &projectedMat, CV_GEMM_B_T );
		for (int i=0; i<4; i++) {
			projected[0][i] /= projected[2][i];
			projected[1][i] /= projected[2][i];
		}

		// draw the projected lines
        ofSetColor(0,255,0);
		ofLine( (int)projected[0][0], (int)projected[1][0], (int)projected[0][1], (int)projected[1][1] );
		// cvLine(*dst, cvPoint((int)projected[0][0], (int)projected[1][0]),
		// 		cvPoint((int)projected[0][1], (int)projected[1][1]), CV_RGB(0,255,0));

        ofSetColor(255,0,0);
		ofLine( (int)projected[0][0], (int)projected[1][0], (int)projected[0][2], (int)projected[1][2] );
		// cvLine(*dst, cvPoint((int)projected[0][0], (int)projected[1][0]),
		// 		cvPoint((int)projected[0][2], (int)projected[1][2]), CV_RGB(255,0,0));

        ofSetColor(0,0,255);		
		ofLine( (int)projected[0][0], (int)projected[1][0], (int)projected[0][3], (int)projected[1][3] );
		// cvLine(*dst, cvPoint((int)projected[0][0], (int)projected[1][0]),
		// 		cvPoint((int)projected[0][3], (int)projected[1][3]), CV_RGB(0,0,255));
	
		cvReleaseMat(&m);
		
	}

	
};



#endif	

