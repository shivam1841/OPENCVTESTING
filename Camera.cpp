
#include "opencv2/opencv.hpp"

using namespace cv;

class Camera {

public:
	int play()
	{
		VideoCapture cap(0); // open the default camera
		if (!cap.isOpened())  // check if we succeeded
			return -1;
		int H_MIN = 0;
		int H_MAX = 255;
		int S_MIN = 0;
		int S_MAX = 255;
		int V_MIN = 0;
		int V_MAX = 255;
		Mat edges;
		Mat hsv_frame;
		
		/// Create Trackbars
		char TrackbarName1[50] = "hmin";
		char TrackbarName2[50] = "hmax";
		char TrackbarName3[50] = "smin";
		char TrackbarName4[50] = "smax";
		char TrackbarName5[50] = "vmin";
		char TrackbarName6[50] = "vmax";	
		
		//namedWindow("edges", 1);
		namedWindow("camera", 1);
		//namedWindow("hsv", 1);
		
		namedWindow("colour", 1);
		for (;;)
		{
			Mat frame;
			Mat redframe_threshold;
			Mat blueframe_threshold;
			Mat frame_threshold;
			cap >> frame; // get a new frame from camera
			cvtColor(frame, hsv_frame, COLOR_BGR2HSV);


			//For callibration purposes
			namedWindow("h", 1);
			createTrackbar(TrackbarName1, "h", &H_MIN, H_MAX, NULL);
			createTrackbar(TrackbarName2, "h", &H_MAX, H_MAX, NULL);

			createTrackbar(TrackbarName3, "h", &S_MIN, S_MAX, NULL);
			createTrackbar(TrackbarName4, "h", &S_MAX, S_MAX, NULL);

			createTrackbar(TrackbarName5, "h", &V_MIN, V_MAX, NULL);
			createTrackbar(TrackbarName6, "h", &V_MAX, V_MAX, NULL);

			
			inRange(hsv_frame, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), frame_threshold);
			//inRange(hsv_frame, Scalar(145, 0, 0), Scalar(256, 256, 256), redframe_threshold);
			//inRange(hsv_frame, Scalar(0,112, 100), Scalar(256, 256, 256), blueframe_threshold);
			//bitwise_or(redframe_threshold,blueframe_threshold,frame_threshold);
			//cvSmooth(&frame_threshold, &frame_threshold, CV_GAUSSIAN, 9, 9);
			/*
			erode(frame_threshold, frame_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
			dilate(frame_threshold, frame_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

			erode(frame_threshold, frame_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
			dilate(frame_threshold, frame_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

			erode(frame_threshold, frame_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));
			dilate(frame_threshold, frame_threshold, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)));

			std::vector<cv::Vec3f> circles;
			HoughCircles(frame_threshold, circles, HOUGH_GRADIENT, 1, frame_threshold.rows / 2, 20, 15);
			for (size_t i = 0; i < circles.size(); i++)
			{
				cv::Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
				int radius = cvRound(circles[i][2]);
				cv::circle(frame, center, 3, cv::Scalar(255, 0, 255), -1);
				cv::circle(frame, center, radius, cv::Scalar(0, 0, 255), 1);
			}

			*/
			//cvSmooth(&frame_threshold, &frame_threshold, CV_GAUSSIAN, 9, 9);
			imshow("colour", frame_threshold);
			imshow("camera", frame);
			imshow("hsv", hsv_frame);
			if (waitKey(30) >= 0) break;
		}
		// the camera will be deinitialized automatically in VideoCapture destructor
		return 0;
	}


};


int main(int, char**)
{
	Camera cp;
	int i = cp.play();
	return i;
}


