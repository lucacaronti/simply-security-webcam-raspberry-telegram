#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <string>
#include <cmath>

int main(){
	std::string imageName = "image.jpg";
	int webCamHeight = 640;
	int webCamWidth = 480;
	double MSE_threshold = 1e+07;
	cv::Mat imageDataset[10];
	for(int i = 0 ; i < 10 ; i++){
		imageDataset[i] = cv::Mat(webCamWidth, webCamHeight, CV_8UC3, cv::Scalar(0,0,0));
	}
	int datasetCounter = 0;
	long int sendCount = 0;
	cv::VideoCapture cap;
	if(!cap.open(0)){
		std::cout<<"Error, no webcam found"<<std::endl;
		return 0;
	}
	cv::Mat image;
	while(1){
		cap >> image;
		sendCount++;
		image.copyTo(imageDataset[datasetCounter]);
		cv::Mat avgImg1_16(webCamWidth, webCamHeight, CV_16UC3, cv::Scalar(0,0,0));
		cv::Mat avgImg2_16(webCamWidth, webCamHeight, CV_16UC3, cv::Scalar(0,0,0));
		int count = datasetCounter;
		for(int i = 0; i < 5 ; i ++){
			cv::Mat tmpImg1_16(webCamWidth, webCamHeight, CV_16UC3);
			imageDataset[count].convertTo(tmpImg1_16, CV_16UC3);
			avgImg1_16+=tmpImg1_16;

			imageDataset[((count + 5) % 10)].convertTo(tmpImg1_16, CV_16UC3);
			avgImg2_16+=tmpImg1_16;

			count --;
			if(count == -1){
				count = 9;
			}
		}
		avgImg1_16 /= 5;
		avgImg2_16 /= 5;
		cv::Mat avgImg1_8(webCamWidth, webCamHeight, CV_8UC3);
		cv::Mat avgImg2_8(webCamWidth, webCamHeight, CV_8UC3);
		avgImg1_16.convertTo(avgImg1_8, CV_8UC3);
		avgImg2_16.convertTo(avgImg2_8, CV_8UC3);

		cv::Mat diffImg;
		diffImg = avgImg1_8 - avgImg2_8;
		cv::Mat diffImg_32F;
		diffImg.convertTo(diffImg_32F, CV_32F);
		diffImg_32F = diffImg_32F.mul(diffImg_32F);
		cv::Scalar s = cv::sum(diffImg_32F);
		double mse = s.val[0] + s.val[1] + s.val[3];
		if(mse > MSE_threshold and sendCount > 15){
			sendCount = 0;
			std::cout<<"Alarm!!"<<std::endl;
			cv::imwrite(imageName, image);
			system("python3 sendTelegram.py");
		}

		datasetCounter = ((datasetCounter + 1) % 10);
	}
	return 1;

}
