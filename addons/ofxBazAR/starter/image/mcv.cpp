/*
Copyright 2005, 2006 Computer Vision Lab, 
Ecole Polytechnique Federale de Lausanne (EPFL), Switzerland. 
All rights reserved.

This file is part of BazAR.

BazAR is free software; you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

BazAR is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
BazAR; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA 
*/
#include <iostream>
#include <math.h>

#include <cv.h>
// #include <highgui.h>

#include "mcv.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////

CvSize mcvSize(IplImage * image)
{
  return cvSize(image->width, image->height);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void mcvSmooth(IplImage * image, IplImage * smoothed_image, int smooth_type, int aperture)
{
  if (smooth_type != CV_GAUSSIAN)
  {
    cerr << "mcvSmooth: only for CV_GAUSSIAN" << endl;
    return;
  }

  IplImage * image_to_smooth = image;
  while(aperture > 0)
  {
    if (aperture >= 7)
    {
      cvSmooth(image_to_smooth, smoothed_image, CV_GAUSSIAN, 7);
      image_to_smooth = smoothed_image;
      aperture -= 7;
    }
    else if (aperture >= 5)
    {
      cvSmooth(image_to_smooth, smoothed_image, CV_GAUSSIAN, 5);
      image_to_smooth = smoothed_image;
      aperture -= 5;
    }
    else // if (aperture >= 3)
    {
      cvSmooth(image_to_smooth, smoothed_image, CV_GAUSSIAN, 3);
      image_to_smooth = smoothed_image;
      aperture -= 3;
    }
  }
}

float mcvGaussianDerivative(IplImage * image, int x, int y, int order_x, int order_y, float sigma)
{
  int half_size = int(3 * sqrt(2.) * sigma + 0.5);

  float result = 0;

  for(int i = -half_size; i <= +half_size; i++)
    for(int j = -half_size; j <= +half_size; j++)
    {
      float c = 0.;
      float e = exp(-(i*i+j*j) / (2 * sigma * sigma));

      if (order_x == 2 && order_y == 0)
        c = (i * i / (sigma * sigma * sigma * sigma) - 1 / (sigma * sigma)) * e;
      else if (order_x == 0 && order_y == 2)
        c = (j * j / (sigma * sigma * sigma * sigma) - 1 / (sigma * sigma)) * e;
      else if (order_x == 1 && order_y == 1)
        c = i * j / (sigma * sigma * sigma * sigma) * e;
      else
      {
        c = -1;
        cerr << "error when calling mcvGaussianDerivative" << endl;
      }

      int nx = x + i, ny = y + j;
      if (nx < 0 || nx >= image->width || ny < 0 || ny >= image->height)
        result += c * 128;
      else
      {
        if (image->depth == int(IPL_DEPTH_8U))
          result += c * mcvGet2D(image, nx, ny, unsigned char);
        else if (image->depth == int(IPL_DEPTH_16S))
          result += c * mcvGet2D(image, nx, ny, short);
        else if (image->depth == int(IPL_DEPTH_32F))
          result += c * mcvGet2D(image, nx, ny, float);
        else
          cerr << "mcvGaussianDerivative: wrong image format." << endl;
      }
    }

  return result;
}

IplImage * mcvGradientNorm2(IplImage * image, int aperture)
{
  IplImage * image_32f = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_32F, 1);
  cvCvtScale(image, image_32f);

  IplImage * image_32f_x = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_32F, 1);
  IplImage * image_32f_y = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_32F, 1);

  cvSobel(image_32f, image_32f_x, 1, 0, aperture);
  cvSobel(image_32f, image_32f_y, 1, 0, aperture);

  IplImage * result_32f = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_32F, 1);
  cvMul(image_32f_x, image_32f_x, image_32f_x);
  cvMul(image_32f_y, image_32f_y, image_32f_y);
  cvAdd(image_32f_x, image_32f_y, result_32f);

  IplImage * result = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);

  mcvScaleTo0_255(result_32f, result);

  cvReleaseImage(&image_32f);
  cvReleaseImage(&image_32f_x);
  cvReleaseImage(&image_32f_y);
  cvReleaseImage(&result_32f);

  return result;
}

void mcvSetBorder(IplImage * image, int border, int value)
{
  if (image->depth == int(IPL_DEPTH_16S))
  {
    for(int y = 0; y < image->height; y++)
      for(int x = 0; x < image->width; x++)
        if (x < border || y < border || x >= image->width - border || y >= image->height - border)
          mcvGet2D(image, x, y, short) = short(value);
  }
  else if (image->depth == int(IPL_DEPTH_32F))
  {
    for(int y = 0; y < image->height; y++)
      for(int x = 0; x < image->width; x++)
        if (x < border || y < border || x >= image->width - border || y >= image->height - border)
          mcvGet2D(image, x, y, float) = float(value);
  }
  else
    cerr << "mcvSetBorder: wrong image format." << endl;
}

void mcvSetBorder(IplImage * image, int border_size)
{
  if (image->depth != IPL_DEPTH_32F)
  {
    cerr << "Error when calling mcvAddBorder: image should be 32F" << endl;
    return;
  }

  double sum = 0;
  unsigned int N = 0;
  for(int j = border_size + 1; j < image->height - border_size - 1; j++)
  {
    float * row = mcvRow(image, j, float);
    for(int i = border_size + 1; i < image->width - border_size - 1; i++)
    {
      sum += double(row[i]);
      N++;
    }
  }
  float mean = float(sum / double(N));
  for(int j = 0; j < image->height; j++)
  {
    float * row = mcvRow(image, j, float);
    for(int i = 0; i < image->width; i++)
    {
      if (i <= border_size || i >= image->width  - border_size - 1 ||
          j <= border_size || j >= image->height - border_size - 1)
        row[i] = mean;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

IplImage * mcvColorToGray(IplImage * colorImage)
{
  IplImage * result = cvCreateImage(cvSize(colorImage->width, colorImage->height), IPL_DEPTH_8U, 1);

  cvCvtColor(colorImage, result, CV_RGB2GRAY);

  return result;
}

IplImage * mcvGrayToColor(IplImage * grayImage)
{
  IplImage * result = cvCreateImage(cvSize(grayImage->width, grayImage->height), IPL_DEPTH_8U, 3);

  if (grayImage->depth == IPL_DEPTH_32F)
    {
      IplImage * tempImage;
      
      double min = 255, max = 0;
      CvPoint Pmin, Pmax;
      cvMinMaxLoc(grayImage, &min, &max, &Pmin, &Pmax);
      tempImage = cvCreateImage(cvSize(grayImage->width, grayImage->height), IPL_DEPTH_8U, 1);
      cvConvertScale(grayImage, tempImage, 255. / (max - min), -min * 255 / (max - min));
      cvCvtColor(tempImage, result, CV_GRAY2RGB);      
      cvReleaseImage(&tempImage);      
    }
  else
    cvCvtColor(grayImage, result, CV_GRAY2RGB);

  return result;
}

void mcvHSV2RGB(float H, float S, float V, int & R, int & G, int & B)
{
  if (S == 0) //HSV values = 0..1
  {
    R = int( V * 255.f );
    G = int( V * 255.f );
    B = int( V * 255.f );
  }
  else
  {
    float var_h = H * 6;
    if ( var_h >= 6 ) var_h -= 6; // H must be < 1
    int var_i = int( var_h );
    float var_1 = V * ( 1 - S );
    float var_2 = V * ( 1 - S * ( var_h - var_i ) );
    float var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

    float var_r, var_g, var_b;
    if      ( var_i == 0 ) { var_r = V     ; var_g = var_3 ; var_b = var_1; }
    else if ( var_i == 1 ) { var_r = var_2 ; var_g = V     ; var_b = var_1; }
    else if ( var_i == 2 ) { var_r = var_1 ; var_g = V     ; var_b = var_3; }
    else if ( var_i == 3 ) { var_r = var_1 ; var_g = var_2 ; var_b = V;     }
    else if ( var_i == 4 ) { var_r = var_3 ; var_g = var_1 ; var_b = V;     }
    else                   { var_r = V     ; var_g = var_1 ; var_b = var_2; }

    R = int( var_r * 255.f ); // RGB results =0..255
    G = int( var_g * 255.f );
    B = int( var_b * 255.f );
  }
}

IplImage * mcvFloatToHue(IplImage * floatImage, int curve_number)
{
  if (floatImage->depth != IPL_DEPTH_32F)
    return 0;

  IplImage * result = cvCreateImage(cvSize(floatImage->width, floatImage->height), 
                                    IPL_DEPTH_8U, 3);
  double min = 255, max = 0;
  CvPoint Pmin, Pmax;
  cvMinMaxLoc(floatImage, &min, &max, &Pmin, &Pmax);

  for(int y = 0; y < result->height; y++)
  {
    float * row = mcvRow(floatImage, y, float);
    unsigned char * rowH = mcvRow(result, y, unsigned char);
    for(int x = 0; x < result->width; x++)
    {
      bool use_color = true;
      if (x < result->width - 1 && y < result->height - 1)
      {
        int l1 = int( ((log(row[x]) - log(min)) / (log(max) - log(min))) * curve_number );
        int l2 = int( ((log(row[x + 1]) - log(min)) / (log(max) - log(min))) * curve_number );
        int l3 = int( ((log(row[x + floatImage->width]) - log(min)) / (log(max) - log(min))) * curve_number );
        if (l1 != l2 || l1 != l3) 
          use_color = false;
      }

      if (use_color)
      {
        int r, g, b;
        mcvHSV2RGB(float( (row[x] - min) / (max - min) ), 1.f, 1.f,  r, g, b);
        rowH[3 * x]     = (unsigned char)(r);
        rowH[3 * x + 1] = (unsigned char)(g);
        rowH[3 * x + 2] = (unsigned char)(b);
      }
      else
      {
        rowH[3 * x]     = 0;
        rowH[3 * x + 1] = 0;
        rowH[3 * x + 2] = 0;
      }
    }
  }

  return result;
}

IplImage * mcvFloatToGray(IplImage * floatImage, int curve_number)
{
  if (floatImage->depth != IPL_DEPTH_32F)
    return 0;

  IplImage * result = cvCreateImage(cvSize(floatImage->width, floatImage->height), 
                                    IPL_DEPTH_8U, 3);
  double min = 255, max = 0;
  CvPoint Pmin, Pmax;
  cvMinMaxLoc(floatImage, &min, &max, &Pmin, &Pmax);

  for(int y = 0; y < result->height; y++)
  {
    float * row = mcvRow(floatImage, y, float);
    unsigned char * rowH = mcvRow(result, y, unsigned char);
    for(int x = 0; x < result->width; x++)
    {
      bool use_gray = true;
      if (x < result->width - 1 && y < result->height - 1)
      {
        int l1 = int( (row[x] - min) / (max - min) * curve_number );
        int l2 = int( (row[x + 1] - min) / (max - min) * curve_number );
        int l3 = int( (row[x + floatImage->width] - min) / (max - min) * curve_number );
        if (l1 != l2 || l1 != l3) 
          use_gray = false;
      }

      if (use_gray)
      {
        rowH[3 * x]     = (unsigned char)( 255. * (row[x] - min) / (max - min) );
        rowH[3 * x + 1] = (unsigned char)( 255. * (row[x] - min) / (max - min) );
        rowH[3 * x + 2] = (unsigned char)( 255. * (row[x] - min) / (max - min) );
      }
      else
      {
        rowH[3 * x]     = 0;
        rowH[3 * x + 1] = 0;
        rowH[3 * x + 2] = 255;
      }
    }
  }

  return result;
}

IplImage * showLocalMinima(IplImage * image)
{
  IplImage * result = mcvGrayToColor(image);

  int dy = image->widthStep / sizeof(float);

  for(int y = 1; y < image->height - 1; y++)
  {
    float * row = mcvRow(image, y, float);
    unsigned char * row_r = mcvRow(result, y, unsigned char);
    for(int x = 1; x < image->width - 1; x++)
    {
      if (row[x] < row[x - 1] && row[x] < row[x + 1] &&
        row[x] < row[x - dy] && row[x] < row[x + dy] && 
        row[x] < row[x - dy - 1] && row[x] < row[x + dy - 1] &&
        row[x] < row[x - dy + 1] && row[x] < row[x + dy + 1])
      {
        row_r[3 * x] = 0;
        row_r[3 * x + 1] = 0;
        row_r[3 * x + 2] = 255;
      }
    }
  }

  return result;
}

IplImage * showLocalMaxima(IplImage * image)
{
  IplImage * result = mcvGrayToColor(image);

  int dy = image->widthStep / sizeof(float);

  for(int y = 1; y < image->height - 1; y++)
  {
    float * row = mcvRow(image, y, float);
    unsigned char * row_r = mcvRow(result, y, unsigned char);
    for(int x = 1; x < image->width - 1; x++)
    {
      if (row[x] > row[x - 1] && row[x] > row[x + 1] &&
          row[x] > row[x - dy] && row[x] > row[x + dy] && 
          row[x] > row[x - dy - 1] && row[x] > row[x + dy - 1] && 
          row[x] > row[x - dy + 1] && row[x] > row[x + dy + 1])
      {
        row_r[3 * x] = 0;
        row_r[3 * x + 1] = 0;
        row_r[3 * x + 2] = 255;
      }
    }
  }

  return result;
}

void mcvSwapRandB(IplImage * image)
{
  for(int l = 0; l < image->height; l++)
  {
    unsigned char * line = (unsigned char *)image->imageData + l * image->widthStep;

    for(int c = 0; c < image->nChannels * image->width; c += 3)
    {
      char r = line[c];
      line[c] = line[c + 2];
      line[c + 2] = r;
    }
  }
}

void mcvScaleTo0_255(IplImage * original, IplImage * scaled)
{
  double min = 255, max = 0;
  CvPoint Pmin, Pmax;

  cvMinMaxLoc(original, &min, &max, &Pmin, &Pmax);
  cvConvertScale(original, scaled, 255. / (max - min), -min * 255 / (max - min));
}

/////////////////////////////////////////////////////////////////////////////////////////////////

int mcvSaveImage(const char * filename, IplImage * image, bool verbose)
{
  if (verbose)
    cout << "(saving " << filename << "..." << flush;

  int result;

  if (image->depth == IPL_DEPTH_8U) {

	  ofImage _img = ofImage();
	  _img.setFromPixels( ((unsigned char*) image->imageData) , 320, 240, OF_IMAGE_GRAYSCALE, true );
	  // _img.saveImage( ofToDataPath(filename) );
	  _img.saveImage( filename );
	  printf("saved pixels set!");
	  result = true;
  }
  else
  {
    IplImage * tempImage;

    double min = 255, max = 0;
    CvPoint Pmin, Pmax;
    cvMinMaxLoc(image, &min, &max, &Pmin, &Pmax);

    if (verbose)
      cout << "[" << min << " : " << max << "] " << flush;

    tempImage = cvCreateImage(cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
    cvConvertScale(image, tempImage, 255. / (max - min), -min * 255 / (max - min));

//    result = cvSaveImage(filename, tempImage);
	  result = true;

    cvReleaseImage(&tempImage);
  }

  if (verbose && !result)
    cout << "ERROR !" << endl;

  if (verbose && result)
    cout << "ok)" << endl;

  return result;
}

int mcvSaveImage(const char * generic_filename, int index, IplImage * image, bool verbose)
{
  char filename[1000];

  sprintf(filename, generic_filename, index);

  return mcvSaveImage(filename, image, verbose);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

IplImage * mcvCreateSimilarImage(IplImage * image)
{
  return cvCreateImage(cvSize(image->width, image->height), image->depth, image->nChannels);
}

IplImage * mcvLoadImage(const char * filename, int code, bool verbose)
{
  if (verbose)
    cout << "(loading " << filename << "..." << flush;

//  IplImage * result = cvLoadImage(filename, code);
	ofImage _img = ofImage();
	// _img.loadImage( ofToDataPath(filename) );
	_img.loadImage( filename );
	ofxCvColorImage _im = ofxCvColorImage();
	_im = _img.getPixels();
	IplImage * result = _im.getCvImage();
		

  if (verbose && !result)
    cout << "ERROR !" << endl;

  if (verbose && result)
    cout << "ok)" << endl;

  return result;
}

IplImage * mcvLoadImage(const char * generic_filename, int index, int code, bool verbose)
{
  char filename[1000];

  sprintf(filename, generic_filename, index);

  return mcvLoadImage(filename, code, verbose);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void mcvSquare(IplImage * image, int x, int y, int size, CvScalar color, int width)
{
  cvLine(image, cvPoint(x - size / 2, y - size / 2), cvPoint(x + size / 2, y - size / 2), color, width);
  cvLine(image, cvPoint(x + size / 2, y - size / 2), cvPoint(x + size / 2, y + size / 2), color, width);
  cvLine(image, cvPoint(x + size / 2, y + size / 2), cvPoint(x - size / 2, y + size / 2), color, width);
  cvLine(image, cvPoint(x - size / 2, y + size / 2), cvPoint(x - size / 2, y - size / 2), color, width);
}

void mcvX(IplImage * image, int x, int y, int size, CvScalar color, int width)
{
  cvLine(image, cvPoint(x - size / 2, y - size / 2), cvPoint(x + size / 2, y + size / 2), color, width);
  cvLine(image, cvPoint(x + size / 2, y - size / 2), cvPoint(x - size / 2, y + size / 2), color, width);
}

void mcvCross(IplImage * image, int x, int y, int size, CvScalar color, int width)
{
  cvLine(image, cvPoint(x - size / 2, y), cvPoint(x + size / 2, y), color, width);
  cvLine(image, cvPoint(x, y - size / 2), cvPoint(x, y + size / 2), color, width);
}

void mcvCircle(IplImage * image, int x, int y, int size, CvScalar color, int thickness)
{
  cvCircle(image, cvPoint(x, y), size / 2, color, thickness);
}

void mcvVisibleLine(IplImage * image, int x1, int y1, int x2, int y2, int thickness)
{
  cvLine(image, cvPoint(x1, y1), cvPoint(x2, y2), cvScalar(0, 0, 0), thickness + 2);
  cvLine(image, cvPoint(x1, y1), cvPoint(x2, y2), cvScalar(255, 255, 255), thickness);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

IplImage * mcvCreateRandomImage(CvSize size, int depth, int nChannels)
{
  IplImage * result = cvCreateImage(size, depth, nChannels);

  if (nChannels == 1)
    for(int l = 0; l < size.height; l++)
    {
      unsigned char * line = (unsigned char *)result->imageData + l * result->widthStep;
      for(int c = 0; c < nChannels * size.width; c++)
        line[c] = (unsigned char)(rand() % 256);
    }
  else
    for(int l = 0; l < size.height; l++)
    {
      unsigned char * line = (unsigned char *)result->imageData + l * result->widthStep;
      for(int c = 0; c < nChannels * size.width; c += 3)
        line[c] = line[c + 1] = line[c + 2] = (unsigned char)(rand() % 256);
    }

  return result;
}

void mcvReplace(IplImage * image, int old_value, int new_value)
{
  for(int l = 0; l < image->height; l++)
  {
    unsigned char * line = mcvRow(image, l, unsigned char);

    for(int c = 0; c < image->width; c++)
      if (int(line[c]) == old_value)
        line[c] = (unsigned char)new_value;
  }
}

void mcvReplaceByNoise(IplImage * image, int value)
{
  for(int l = 0; l < image->height; l++)
  {
    unsigned char * line = mcvRow(image, l, unsigned char);

    for(int c = 0; c < image->width; c++)
      if (int(line[c]) == value)
        line[c] = (unsigned char)(rand() % 256);
  }
}

void mcvAddWhiteNoise(const IplImage * image, const int minNoise, const int maxNoise)
{
  int deltaNoise = maxNoise - minNoise;

  for(int y = 0; y < image->height; y++)
  {
    unsigned char * line = mcvRow(image, y, unsigned char);

    for(int x = 0; x < image->width; x++)
    {
      int p = line[x];
      int noise = rand() % (2 * deltaNoise + 1) - deltaNoise;

      if (noise < 0) 
        noise -= minNoise;
      else
        noise += minNoise;

      p += noise;
      if (p > 255) p = 255;
      if (p < 0)   p = 0;

      line[x] = (unsigned char)p;
    }
  }
}

void mcvAddWhiteNoise(const IplImage * image, const int maxNoise)
{
  for(int y = 0; y < image->height; y++)
  {
    unsigned char * line = (unsigned char *)(image->imageData + y * image->widthStep);

    for(int x = 0; x < image->width; x++)
    {
      int p = line[x];

      p += rand() % (2 * maxNoise + 1) - maxNoise;

      if (p > 255) 
        p = 255;
      else if (p < 0)
        p = 0;

      line[x] = (unsigned char)p;
    }
  }
}

// I -> 255 * (I / 255) ^ gamma
void mcvChangeGamma(IplImage * image, float gamma)
{
  for(int y = 0; y < image->height; y++)
  {
    unsigned char * line = (unsigned char *)(image->imageData + y * image->widthStep);

    for(int x = 0; x < image->width; x++)
    {
      int I = int(255 * pow(line[x] / 255.0f, gamma));
      if (I < 0) I = 0;
      if (I > 256) I = 255;
      line[x] = (unsigned char)I;
    }
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void mcvCrop(IplImage * image, int x, int y, IplImage * croppedImage)
{
  IplROI * originalROI = image->roi;
  int width = croppedImage->width;
  int height = croppedImage->height;

  if (x < 0 || y < 0) return;
  if (x + width >= image->width || y + height >= image->height) return;

  IplROI roi;

  roi.xOffset = x;
  roi.yOffset = y;
  roi.width = width;
  roi.height = height;
  roi.coi = 0;

  image->roi = &roi;
  cvCopy(image, croppedImage);
  image->roi = originalROI;
}

IplImage * mcvCrop(IplImage * image, int x, int y, int width, int height)
{
  IplImage * result = cvCreateImage(cvSize(width, height), image->depth, image->nChannels);

  mcvCrop(image, x, y, result);

  return result;
}

/////////////////////////////////////////////////////////////////////////////////////////////////

IplImage * mcvResize(IplImage * original_image, int new_width, int new_height)
{
  if (new_height < 0)
    new_height = int(float(new_width * original_image->height) / original_image->width);
  IplImage * result = cvCreateImage(cvSize(new_width, new_height), original_image->depth, original_image->nChannels);
  cvResize(original_image, result, CV_INTER_LINEAR);
  return result;
}

IplImage * mcvZoom(IplImage * source, int xc, int yc, float zoom)
{
  IplImage * temp = cvCreateImage(cvSize(int(source->width * zoom), int(source->height * zoom)), IPL_DEPTH_8U, 1);
  IplImage * result = cvCreateImage(cvSize(source->width, source->height), IPL_DEPTH_8U, 1);

  cvResize(source, temp, CV_INTER_LINEAR);
  CvRect roi;
  int nxc = int(xc * zoom);
  int nyc = int(yc * zoom);
  roi = cvRect(nxc - source->width / 2, nyc - source->height / 2, source->width, source->height);
  cvSetImageROI(temp, roi);
  cvCopy(temp, result);
  cvReleaseImage(&temp);

  return result;
}

void mcvPut(IplImage * destImage, IplImage * imageToCopy, int x, int y)
{
  IplROI roi;
  roi.xOffset = x;
  roi.yOffset = y;
  roi.width = imageToCopy->width;
  roi.height = imageToCopy->height;
  roi.coi = 0;

  IplROI * tempRoi = destImage->roi;

  destImage->roi = &roi;

  if (imageToCopy->nChannels == 1 && destImage->nChannels == 3)
  {
    IplImage * colorImageToCopy = mcvGrayToColor(imageToCopy);
    cvCopy(colorImageToCopy, destImage);
    cvReleaseImage(&colorImageToCopy);
  }
  else
    cvCopy(imageToCopy, destImage);

  destImage->roi = tempRoi;
}

void mcvDeinterlace(IplImage * image)
{
  unsigned char * line = (unsigned char *)(image->imageData + image->widthStep);
  int width = image->nChannels * image->width;

  for(int y = 1; y < image->height; y += 2)
  {
    unsigned char * previous = line - image->widthStep;
    unsigned char * next = line + image->widthStep;

    for(int x = 0; x < width; x++)
      line[x] = (unsigned char)((int(previous[x]) + int(next[x])) >> 1);

    line += 2 * image->widthStep;
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////

IplImage * mcvGetPatch(IplImage * image, int u, int v, int width, int height)
{
  return mcvCrop(image, u - width / 2, v - height / 2, width, height);
}

void mcvGetPatch(IplImage * image, IplImage * patch, int u, int v)
{
  mcvCrop(image, u - patch->width / 2, v - patch->height / 2, patch);
}

void imcvR3z(double Rz[3][3], double angle)
{
  Rz[0][0] = cos(angle); Rz[0][1] = -sin(angle); Rz[0][2] = 0.;
  Rz[1][0] = sin(angle); Rz[1][1] =  cos(angle); Rz[1][2] = 0.;
  Rz[2][0] = 0.;         Rz[2][1] =  0.;         Rz[2][2] = 1.;
}

void imcvDiag3(double D[3][3], double d1, double d2, double d3)
{
  D[0][0] = d1; D[0][1] = 0.; D[0][2] = 0.; 
  D[1][0] = 0.; D[1][1] = d2; D[1][2] = 0.; 
  D[2][0] = 0.; D[2][1] = 0.; D[2][2] = d3; 
}

void imcvTransl3(double T[3][3], double tx, double ty)
{
  T[0][0] = 1.; T[0][1] = 0.; T[0][2] = tx; 
  T[1][0] = 0.; T[1][1] = 1.; T[1][2] = ty; 
  T[2][0] = 0.; T[2][1] = 0.; T[2][2] = 1.; 
}

void imcvMul_MN3(double A[3][3], double B[3][3], double AB[3][3])
{
  double copy[3][3];

  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
    {
      copy[i][j] = 0.;
      for(int k = 0; k < 3; k++)
        copy[i][j] += A[i][k] * B[k][j];
    }
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      AB[i][j] = copy[i][j];
}

void imcvMul_MNt3(double A[3][3], double B[3][3], double ABt[3][3])
{
  double copy[3][3];

  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
    {
      copy[i][j] = 0.;
      for(int k = 0; k < 3; k++)
        copy[i][j] += A[i][k] * B[j][k];
    }
  for(int i = 0; i < 3; i++)
    for(int j = 0; j < 3; j++)
      ABt[i][j] = copy[i][j];
}

void imcvMul_MNMt3(double M[3][3], double N[3][3], double MNMt[3][3])
{
  double NMt[3][3];

  imcvMul_MNt3(N, M, NMt);
  imcvMul_MN3(M, NMt, MNMt);
}

/////////////////////////////////////////////////////////////////////////////////////////////////

/* 
cf Multiple view geometry, p. 19
A = T(tx, ty) R(theta) R(-phi) D(lambda1, lambda2) R(phi)

!!! actually compute the inverse of A to be opencv complient 
*/

void mcvComputeAffineTransfo(float * a, 
                             int u, int v, 
                             float theta, float phi, 
                             float lambda1, float lambda2, 
                             float tx, float ty)
{
  double K[3][3];
  double A[3][3];

  imcvTransl3(A, -tx, -ty);
  imcvR3z(K, -theta);
  imcvMul_MN3(K, A, A);

  imcvR3z(K, phi);
  imcvMul_MN3(K, A, A);

  imcvDiag3(K, 1. / lambda1, 1. / lambda2, 1);
  imcvMul_MN3(K, A, A);

  imcvR3z(K, -phi);
  imcvMul_MN3(K, A, A);

  a[0] = (float)A[0][0];
  a[1] = (float)A[0][1];
  a[2] = (float)u + (float)A[0][2];
  a[3] = (float)A[1][0];
  a[4] = (float)A[1][1];
  a[5] = (float)v + (float)A[1][2];
}

CvScalar mcvRainbowColor(int index, float coeff)
{
  if (index == -1)
    index = rand() % 6;
  else
    index = index % 6;

  switch(index)
  {
  case 0: return CV_RGB(255 * coeff, 0, 0);
  case 1: return CV_RGB(0, 255 * coeff, 0);
  case 2: return CV_RGB(0, 0, 255 * coeff);

  case 3: return CV_RGB(255 * coeff, 255 * coeff, 0);
  case 4: return CV_RGB(0, 255 * coeff, 255 * coeff);
  case 5: return CV_RGB(255 * coeff, 0, 255 * coeff);

  default: return CV_RGB(128, 128, 128);
  }
}

