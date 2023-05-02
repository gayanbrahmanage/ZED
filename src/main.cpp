#include "opencv2/opencv.hpp"
#include <iostream>
#include "calibration.hpp"

using namespace std;
using namespace cv;

int main(){

  // ----> Initialize calibration
  std::string calibration_file="../calib/SN000021374.conf";
  int h=720;
  int w=2560;
  cv::Mat map_left_x, map_left_y;
  cv::Mat map_right_x, map_right_y;
  cv::Mat cameraMatrix_left, cameraMatrix_right;
  sl_oc::tools::initCalibration(calibration_file, cv::Size(w/2,h), map_left_x, map_left_y, map_right_x, map_right_y,cameraMatrix_left, cameraMatrix_right);

  cv::Mat left_rect, right_rect;
  cv::Mat frame, left_image, right_image;
  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  cv::VideoCapture cap("/dev/video0");

  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }

  // Set the video resolution to HD720 (2560*720)
  cap.set(CAP_PROP_FRAME_WIDTH, w);
  cap.set(CAP_PROP_FRAME_HEIGHT, h);

  while(1){

    // Get a new frame from camera
    cap >> frame;
    // Extract left and right images from side-by-side
    left_image = frame(cv::Rect(0, 0, frame.cols / 2, frame.rows));
    right_image = frame(cv::Rect(frame.cols / 2, 0, frame.cols / 2, frame.rows));

    // ----> Apply rectification
    cv::remap(left_image, left_rect, map_left_x, map_left_y, cv::INTER_LINEAR );
    cv::remap(right_image, right_rect, map_right_x, map_right_y, cv::INTER_LINEAR );
    // Display images
    //cv::imshow("frame", frame);
    cv::imshow("left", left_rect);
    cv::imshow("right", right_rect);
    cv::waitKey(1);

  }

  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  cv::destroyAllWindows();

  return 0;
}
