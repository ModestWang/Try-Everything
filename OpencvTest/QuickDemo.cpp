#include "QuickDemo.h"

/// <summary>
/// 1.Colors the space demo.
/// </summary>
/// <param name="image">The image.</param>
void QuickDemo::colorSpace_Demo(Mat& image) {
    Mat gray, hsv, ycrcb, lab;
    cvtColor(image, gray, COLOR_BGR2GRAY);
    cvtColor(image, hsv, COLOR_BGR2HSV);
    imshow("gray", gray);
    imshow("hsv", hsv);
}

/// <summary>
/// 2.Mats the creation demo.
/// </summary>
void QuickDemo::matCreation_Demo() {
    // 创建空白图像
    Mat m1 = Mat::zeros(Size(16, 16), CV_8UC3);
    m1 = Scalar(100, 0, 255);
    cout << "width: " << m1.cols << ", height: "
        << m1.rows << ", channels: " << m1.channels()
        << endl;
    cout << m1 << endl;

    // 克隆
    Mat m2 = m1.clone();

    // 复制
    Mat m3;
    m1.copyTo(m3);

    Mat kernel = (Mat_<char>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0);

    imshow("m1", m1);
    imshow("m2", m2);
    imshow("m3", m3);
}

/// <summary>
/// 3.Pixels the visit demo.
/// </summary>
/// <param name="image">The image.</param>
void QuickDemo::pixel_visit_Demo(Mat& image) {
    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            if (image.channels() == 1) {// 灰度图
                uchar pixel = image.at<uchar>(y, x);
                image.at<uchar>(y, x) = 255 - pixel;
            } else if (true) {          // 彩色图
                Vec3b pixel = image.at<Vec3b>(y, x);
                pixel[0] = 255 - pixel[0];
                pixel[1] = 255 - pixel[1];
                pixel[2] = 255 - pixel[2];
                image.at<Vec3b>(y, x) = pixel;
            }
        }
    }
    imshow("像素读写", image);
}

/// <summary>
/// 4.Operatorses the demo.
/// </summary>
/// <param name="image">The image.</param>
void QuickDemo::operators_Demo(Mat& image) {
    Mat dst;
    /*
    dst = image + Scalar(50, 50, 50);
    imshow("加法操作", dst);
    dst = image - Scalar(50, 50, 50);
    imshow("减法操作", dst);
    dst = image * 1.5;
    imshow("乘法操作", dst);
    dst = image / 1.5;
    imshow("除法操作", dst);
    dst = image + image;
    imshow("图像相加", dst);
    dst = image - image;
    imshow("图像相减", dst);
    */
    add(image, Scalar(50, 50, 50), dst);
    imshow("加法操作", dst);
    subtract(image, Scalar(50, 50, 50), dst);
    imshow("减法操作", dst);
    multiply(image, 1.5, dst);
    imshow("乘法操作", dst);
    divide(image, 1.5, dst);
    imshow("除法操作", dst);
}

static int alpha_value = 100;
static int beta_value = 100;
static int gamma_value = 100;
/// <summary>
/// 5.Ons the change.
/// </summary>
/// <param name="value">The value.</param>
/// <param name="userdata">The userdata.</param>
static void on_change(int value, void* userdata) {
    double a = alpha_value / 100.0;
    double b = beta_value / 100.0;
    double g = gamma_value / 100.0;
    Mat image = *(Mat*)userdata;
    Mat dst;
    addWeighted(image, a, Scalar(50, 50, 50), b, g, dst);
    imshow("TrackBar", dst);
}
/// <summary>
/// Tracks the bar demo.
/// </summary>
/// <param name="image">The image.</param>
void QuickDemo::trackBar_Demo(Mat& image) {
    namedWindow("TrackBar", WINDOW_AUTOSIZE);
    createTrackbar("Alpha", "TrackBar", &alpha_value, 100, on_change, &image);
    createTrackbar("Beta", "TrackBar", &beta_value, 100, on_change, &image);
    createTrackbar("Gamma", "TrackBar", &gamma_value, 100, on_change, &image);
}

/// <summary>
/// 6.Detects the face demo.
/// </summary>
void QuickDemo::detectFace_Demo() {
    string pb_file = "./models/face_detector/opencv_face_detector_uint8.pb";
    string pbtxt_file = "./models/face_detector/opencv_face_detector.pbtxt";
    cv::dnn::Net net = cv::dnn::readNetFromTensorflow(pb_file, pbtxt_file);
    //VideoCapture cap(0);
    VideoCapture cap(1);
    Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            break;
        }
        Mat blob = cv::dnn::blobFromImage(
            frame, 1.0, Size(300, 300), Scalar(104, 177, 123), false, false
        );
        net.setInput(blob);
        Mat output = net.forward();
        Mat detection(output.size[2], output.size[3], CV_32F, output.ptr<float>());
        for (int i = 0; i < detection.rows; i++) {
            float confidence = detection.at<float>(i, 2);
            if (confidence > 0.7) {
                int x1 = static_cast<int>(detection.at<float>(i, 3) * frame.cols);
                int y1 = static_cast<int>(detection.at<float>(i, 4) * frame.rows);
                int x2 = static_cast<int>(detection.at<float>(i, 5) * frame.cols);
                int y2 = static_cast<int>(detection.at<float>(i, 6) * frame.rows);
                rectangle(frame, Point(x1, y1), Point(x2, y2), Scalar(0, 255, 0), 2);
            }
        }
        imshow("Face Detection", frame);
        if (waitKey(10) == 27) {
            break;
        }
    }
}

/// <summary>
/// 7.Colors the map demo.
/// </summary>
/// <param name="image">The image.</param>
void QuickDemo::colorMap_Demo(Mat& image) {
    int colormap[] = {
        COLORMAP_AUTUMN,
        COLORMAP_BONE,
        COLORMAP_JET,
        COLORMAP_WINTER,
        COLORMAP_RAINBOW,
        COLORMAP_OCEAN,
        COLORMAP_SUMMER,
        COLORMAP_SPRING,
        COLORMAP_COOL,
        COLORMAP_PINK,
        COLORMAP_HOT,
        COLORMAP_PARULA,
        COLORMAP_MAGMA,
        COLORMAP_INFERNO,
        COLORMAP_PLASMA,
        COLORMAP_VIRIDIS,
        COLORMAP_CIVIDIS,
        COLORMAP_TWILIGHT,
        COLORMAP_TWILIGHT_SHIFTED
    };
    int index = 0;
    while (true) {
        Mat dst;
        applyColorMap(image, dst, colormap[index++ % 19]);
        imshow("ColorMap", dst);
        waitKey(1000);
    }
}

/// <summary>
/// 8.Bitwises the demo.
/// </summary>
/// <param name="image">The image.</param>
void QuickDemo::bitwise_Demo(Mat& image) {
    Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
    Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
    rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
    rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
    imshow("m1", m1);
    imshow("m2", m2);
    Mat dst;
    //bitwise_and(m1, m2, dst);
    //bitwise_or(m1, m2, dst);
    //bitwise_xor(m1, m2, dst);
    bitwise_not(m1, dst);
    imshow("像素位操作", dst);
}

/// <summary>
/// 9.Channelses the demo.
/// </summary>
/// <param name="image">The image.</param>
void QuickDemo::channels_Demo(Mat& image) {
    std::vector<Mat> bgr;
    split(image, bgr); // 分离通道
    imshow("B", bgr[0]);
    imshow("G", bgr[1]);
    imshow("R", bgr[2]);

    Mat dst;

    bgr[0] = 0;
    merge(bgr, dst); // 合并通道
    imshow("merge", dst);

    int from_to[] = { 0, 0, 1, 1, 2, 2 };
    mixChannels(&image, 1, &dst, 1, from_to, 3);
    imshow("mixChannels", dst);
}
