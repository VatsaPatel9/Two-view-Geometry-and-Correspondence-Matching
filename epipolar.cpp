#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include <fstream>
#include<iostream>
#include <typeinfo>
using namespace cv;
using namespace std;

string number;
string s("Focal Length");
vector<std::string> strVec;
Mat K1, K2, T, R, X, F, temp, camera_left, camera_right, BLUE, GREEN, RED, blue, green, red;
int x_1 = 0, y_1 = 0, cnt = 0;
int val[1024][2];
double norm_cos[1024];
float fx_1, fy_1, cx_1, cy_1, fx_2, fy_2, cx_2, cy_2, tx, ty, tz, r[9], a, b, c;
int pixel_x, pixel_y;
double Max = 0;

double NCC(Mat& img1, Mat& img2) {
    Mat mag2 = img2.mul(img2);
    Mat mag1 = img1.mul(img1);
    Mat zeros = Mat(3, 3, CV_64FC1);

    Scalar avg1 = mean(img1);
    Scalar avg2 = mean(img2);

    img1 = img1 - avg1[0];
    img2 = img2 - avg2[0];

    zeros = 0.0;

    double sum1 = sqrt(sum(mag1)[0]);
    double sum2 = sqrt(sum(mag2)[0]);
    double innerProduct = sum(img1.mul(img2))[0];
    double ncc = innerProduct / (sum1 * sum2);

    if (ncc < 0) {
        ncc = ncc * -1;
    }

    return ncc;
}
void getMaximum(int i) 
{
    
   
    
    if (norm_cos[i] > Max)
    {
        Max = norm_cos[i];
        pixel_x = val[i][0];
        pixel_y = val[i][1];
        circle(camera_right, Point(pixel_x, pixel_y), 3, (0, 0, 255), 3);
    }
    

}

void locatePixel(int x, int y, int i)
{
    double bl[9] = { (double)camera_right.ptr<uchar>(y - 1)[(x - 1) * 3],(double)camera_right.ptr<uchar>(y - 1)[(x) * 3],(double)camera_right.ptr<uchar>(y - 1)[(x + 1) * 3],(double)camera_right.ptr<uchar>(y)[(x - 1) * 3],(double)camera_right.ptr<uchar>(y)[(x) * 3],(double)camera_right.ptr<uchar>(y)[(x + 1) * 3],(double)camera_right.ptr<uchar>(y + 1)[(x - 1) * 3],(double)camera_right.ptr<uchar>(y + 1)[(x) * 3],(double)camera_right.ptr<uchar>(y + 1)[(x + 1) * 3] };

    blue = Mat(3, 3, CV_64FC1, bl);
    double b[9] = { (double)camera_left.ptr<uchar>(y_1 - 1)[(x_1 - 1) * 3],(double)camera_left.ptr<uchar>(y_1 - 1)[(x_1) * 3],(double)camera_left.ptr<uchar>(y_1 - 1)[(x_1 + 1) * 3],(double)camera_left.ptr<uchar>(y_1)[(x_1 - 1) * 3],(double)camera_left.ptr<uchar>(y_1)[(x_1) * 3],(double)camera_left.ptr<uchar>(y_1)[(x_1 + 1) * 3],(double)camera_left.ptr<uchar>(y_1 + 1)[(x_1 - 1) * 3],(double)camera_left.ptr<uchar>(y_1 + 1)[(x_1) * 3],(double)camera_left.ptr<uchar>(y_1 + 1)[(x_1 + 1) * 3] };

    BLUE = Mat(3, 3, CV_64FC1, b);

    double gr[9] = { (double)camera_right.ptr<uchar>(y - 1)[((x - 1) * 3) + 1],(double)camera_right.ptr<uchar>(y - 1)[((x) * 3) + 1],(double)camera_right.ptr<uchar>(y - 1)[((x + 1) * 3) + 1],(double)camera_right.ptr<uchar>(y)[((x - 1) * 3) + 1],(double)camera_right.ptr<uchar>(y)[((x) * 3) + 1], (double)camera_right.ptr<uchar>(y)[((x + 1) * 3) + 1],(double)camera_right.ptr<uchar>(y + 1)[((x - 1) * 3) + 1],(double)camera_right.ptr<uchar>(y + 1)[((x) * 3) + 1],(double)camera_right.ptr<uchar>(y + 1)[((x + 1) * 3) + 1] };
    green = Mat(3, 3, CV_64FC1, gr);
    double g[9] = { (double)camera_left.ptr<uchar>(y_1 - 1)[((x_1 - 1) * 3) + 1],(double)camera_left.ptr<uchar>(y_1 - 1)[((x_1) * 3) + 1],(double)camera_left.ptr<uchar>(y_1 - 1)[((x_1 + 1) * 3) + 1],(double)camera_left.ptr<uchar>(y_1)[((x_1 - 1) * 3) + 1],(double)camera_left.ptr<uchar>(y_1)[((x_1) * 3) + 1],(double)camera_left.ptr<uchar>(y_1)[((x_1 + 1) * 3) + 1], (double)camera_left.ptr<uchar>(y_1 + 1)[((x_1 - 1) * 3) + 1],(double)camera_left.ptr<uchar>(y_1 + 1)[((x_1) * 3) + 1],(double)camera_left.ptr<uchar>(y_1 + 1)[((x_1 + 1) * 3) + 1] };
    GREEN = Mat(3, 3, CV_64FC1, g);

    double re[9] = { (double)camera_right.ptr<uchar>(y - 1)[((x - 1) * 3) + 2],(double)camera_right.ptr<uchar>(y - 1)[((x) * 3) + 2],(double)camera_right.ptr<uchar>(y - 1)[((x + 1) * 3) + 2],(double)camera_right.ptr<uchar>(y)[((x - 1) * 3) + 2],(double)camera_right.ptr<uchar>(y)[((x) * 3) + 2],(double)camera_right.ptr<uchar>(y)[((x + 1) * 3) + 2],(double)camera_right.ptr<uchar>(y + 1)[((x - 1) * 3) + 2],(double)camera_right.ptr<uchar>(y + 1)[((x) * 3) + 2],(double)camera_right.ptr<uchar>(y + 1)[((x + 1) * 3) + 2] };
    red = Mat(3, 3, CV_64FC1, re);
    double r[9] = { (double)camera_left.ptr<uchar>(y_1 - 1)[((x_1 - 1) * 3) + 2],(double)camera_left.ptr<uchar>(y_1 - 1)[((x_1) * 3) + 2],(double)camera_left.ptr<uchar>(y_1 - 1)[((x_1 + 1) * 3) + 2],(double)camera_left.ptr<uchar>(y_1)[((x_1 - 1) * 3) + 2],(double)camera_left.ptr<uchar>(y_1)[((x_1) * 3) + 2],(double)camera_left.ptr<uchar>(y_1)[((x_1 + 1) * 3) + 2],(double)camera_left.ptr<uchar>(y_1 + 1)[((x_1 - 1) * 3) + 2],(double)camera_left.ptr<uchar>(y_1 + 1)[((x_1) * 3) + 2],(double)camera_left.ptr<uchar>(y_1 + 1)[((x_1 + 1) * 3) + 2] };

    RED = Mat(3, 3, CV_64FC1, r);
    double RCC = NCC(red, RED);
    double GCC = NCC(green, GREEN);
    double BCC = NCC(blue, BLUE);

    double tCC = RCC + GCC + BCC;
    norm_cos[i] = tCC;
    val[i][0] = x;
    val[i][1] = y;


    getMaximum(i);
    


}
void onClickMouse(int event, int x, int y, int flags, void* userdata)
{
    if (event == EVENT_LBUTTONDOWN)
    {
        x_1 = x;
        y_1 = y;
    }
}

void getValuesFromFile() {
    ifstream file;
    string n = "";
    file.open("Calibration.txt");

    int line_no = 1;
    while (getline(file, n)) {
        if (line_no == 3)
        {
            fx_1 = stof(n.substr(35, 12));
            fy_1 = stof(n.substr(47, 12));
        }
        if (line_no == 4)
        {
            cx_1 = stof(n.substr(35, 8));
            cy_1 = stof(n.substr(47, 8));

        }
        if (line_no == 11)
        {
            fx_2 = stof(n.substr(35, 8));
            fy_2 = stof(n.substr(47, 8));
        }
        if (line_no == 12)
        {
            cx_2 = stof(n.substr(35, 8));
            cy_2 = stof(n.substr(47, 8));
        }
        if (line_no == 19)
        {
            r[0] = stof(n.substr(35, 8));
            r[1] = stof(n.substr(43, 8));
            r[2] = stof(n.substr(52, 8));
            r[3] = stof(n.substr(60, 8));
            r[4] = stof(n.substr(68, 8));
            r[5] = stof(n.substr(76, 8));
            r[6] = stof(n.substr(82, 8));
            r[7] = stof(n.substr(89, 8));
            r[8] = stof(n.substr(96, 8));
        }
        if (line_no == 20)
        {
            tx = stof(n.substr(35, 8));
            ty = stof(n.substr(47, 8));
            tz = stof(n.substr(57, 8));
            break;
        }
        line_no++;
    }
}

int main(int argc, char** argv)
{
    camera_right = imread("path");
    camera_left = imread("path");
    getValuesFromFile();

    float rotation[3][3] = { {r[0], r[1] , r[2]},{r[3], r[4] , r[5]},{r[6], r[7] , r[8]} };
    R = Mat(3, 3, CV_32FC1, rotation);

    float k1[3][3] = { {fx_1, 0, cx_1}, {0, fy_1, cy_1}, {0, 0, 1} };
    K1 = Mat(3, 3, CV_32FC1, k1);

    float k2[3][3] = { {fx_2, 0, cx_2}, {0, fy_2, cy_2}, {0, 0, 1} };
    K2 = Mat(3, 3, CV_32FC1, k2);

    float T[3] = { tx,ty,tz };
    float skewMatrix[3][3] = { {0, -T[2], T[1]}, {T[2], 0, -T[0] }, {-T[1], T[0], 0} };
    Mat Tx = cv::Mat(3, 3, CV_32FC1, skewMatrix);

    Mat K2T;
    Mat K2i = K2.inv();
    transpose(K2i, K2T);

    F = (K2T)*Tx * R * K1.inv();

    while (true) {
        int i = 0;
        imshow("Right Image", camera_right);
        imshow("Left Image", camera_left);

        setMouseCallback("Left Image", onClickMouse, NULL);

        X = (Mat_<float>(3, 1) << x_1, y_1, 1);
        temp = F * X;
        a = temp.ptr<float>(0)[0];
        b = temp.ptr<float>(1)[0];
        c = temp.ptr<float>(2)[0];

        if (x_1 != 0 && y_1 != 0)
        {
            for (int x = 0; x < camera_right.cols; x++)
            {
                int y = (int)(-((a * x) + c) / b);
                int co_x[3] = { x - 1,x,x + 1 };
                int co_y[3] = { y - 1,y,y + 1 };
                locatePixel(x, y , i);
                circle(camera_right, Point(x, y), 1, (0, 0, 255), 1);
                i = i + 1;
            } 
        }
        //circle(camera_right, Point(pixel_x, pixel_y), 3, (0, 0, 255), 3);
        uchar c = waitKey(1);

        if (c == 27) {
            break;
        }
    }

    return 1;
}
