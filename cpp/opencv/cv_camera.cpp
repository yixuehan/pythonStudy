#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <ctime>

using namespace cv;

int main()
{
    // cv::utils::logging::setLogLevel(utils::logging::LOG_LEVEL_VERBOSE);
    // std::string videosrc = "rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1";
    // std::string videosrc = "v4l2src device=/dev/video0 ! video/x-raw,format=YUY2,width=640,height=480,framerate=30/1 ! videoconvert ! video/x-raw,format=(string)BGR ! videoconvert ! appsink";
    // std::string videosrc = "v4l2src device=/dev/video0 ! video/x-raw,format=YUY2,width=640,height=480,framerate=30/1 ! videoconvert ! video/x-raw,format=(string)BGRx ! videoconvert ! video/x-raw,format=(string)BGR ! videoconvert ! appsink";
    std::string videosrc = "v4l2src device=/dev/video0 ! videoconvert ! appsink";
    // std::string videosrc= "rtspsrc location=rtsp://admin:admin123456@192.168.1.108:554/cam/realmonitor?channel=1&subtype=1 ! videoconvert ! appsink";
    cv::VideoCapture capture;
    // int videosrc = 0;
    // std::string videosrc = "/dev/video4";
    // capture.setExceptionMode(true);
    capture.open(videosrc, CAP_GSTREAMER);
    if (!capture.isOpened()) {
        std::cout << "open fail:" << std::endl;
        return -1;
    }
    cv::Mat mat;
    int fps = 0;
    int last_second = time(nullptr);
    while(capture.read(mat)) {
        // cv::Mat out;
        // cv::cvtColor(mat, out, cv::COLOR_GRAY2BGR);
        // mat = out;
        imshow("img", mat);
        auto second = time(nullptr);
        ++fps;
        if (second - last_second >= 1) {
            last_second = second;
            printf("fps:%d\n", fps);
            fps = 0;
        }
        auto key = cv::waitKey(1);
        if (key == 'q') break;
    }
}
