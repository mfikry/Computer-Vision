#include <iostream>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <fstream>

using namespace cv;
using namespace std;

//Variable
int slide_position = 0;
int run				= 1;
int dontset			= 0;

VideoCapture cap;

void onTrackbarSlide(int pos, void*) {
	cap.set(CAP_PROP_POS_FRAMES, pos);
	if (!dontset)
		run = 1;
	dontset = 0;
}

int main() {
	namedWindow("Slider", WINDOW_NORMAL);
	cap.open("media/road_traffic.mp4");
	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "Video tidak ditemukan" << endl;
		return -1;
	}

	int frames = (int) cap.get(CAP_PROP_FRAME_COUNT);
	int tmpw  = (int) cap.get(CAP_PROP_FRAME_WIDTH);
	int tmph  = (int)cap.get(CAP_PROP_FRAME_HEIGHT);

	createTrackbar("Posisi", "Slider", &slide_position, frames, onTrackbarSlide);

	Mat frame;
	for (;;) {
		if (run != 0) {
			cap >> frame;
			int current_pos = (int) cap.get(CAP_PROP_POS_FRAMES);
			dontset = 1;
			setTrackbarPos("Position", "Slider", current_pos);
			imshow("Traffic camera", frame);
			run -= 1; // karna perframe maka frame berkurang
		}
		char c = (char) waitKey(10);
		if (c == 's') {
			run = 1;
			cout << "Jalan 1 step" << endl;
		}
		if (c == 'r') {
			run = -1;
			cout << "Di run biasa" << endl;
		}
		if (c == 27) break;
	}
	return 0;
}
