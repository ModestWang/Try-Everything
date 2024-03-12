#include "QuickDemo.h"

/// <summary>
/// Mains this instance.
/// </summary>
/// <returns></returns>
int main() {
    // ========== Init ========== //
    QuickDemo qd;
    Mat image = imread("./Images/flower.png");
    //imshow("image", image);

    // ========== Demo ========== //
    //qd.colorSpace_Demo(image);
    //qd.matCreation_Demo();
    //qd.pixel_visit_Demo(image);
    //qd.operators_Demo(image);
    //qd.trackBar_Demo(image);
    qd.detectFace_Demo();
    //qd.colorMap_Demo(image);
    //qd.bitwise_Demo(image);
    //qd.channels_Demo(image);

    // ========== Ends ========== //
    waitKey(0);
    destroyAllWindows();
    return 0;
}
