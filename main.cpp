#include <opencv2/opencv.hpp>
#include <cmath>

using namespace cv;

Mat Sobel(Mat& src);

int main(int argc, char** argv) {
  Mat src, filtered;
  const char* window_name = "Sobel Edge Detector";
  src = imread(argv[1]);
  namedWindow("Original", WINDOW_AUTOSIZE);
  imshow("Original", src);

  filtered = imread(argv[1], IMREAD_GRAYSCALE);
  filtered = Sobel(filtered);

  namedWindow(window_name, WINDOW_AUTOSIZE);
  imshow(window_name, filtered);

  waitKey();
  return 0;
}

Mat Sobel(Mat& src) {
  int Gx[3][3] = {{-1, 0, 1},
                  {-2, 0, 2},
                  {-1, 0, 1}};
  int Gy[3][3] = {{-1, -2, -1},
                  {0, 0, 0},
                  {1, 2, 1}};
  int Gx_sum = 0;
  int Gy_sum = 0;
  int G = 0;
  Mat filtered = src.clone();
  for(int i = 1; i < src.rows-1; i++) {
    for(int j = 1; j < src.cols-1; j++) {
      for(int a = 0; a < 3; a++) {
        for(int b = 0; b < 3; b++) {
            Gx_sum += Gx[a][b]*src.at<uchar>(i + a - 1, j + b - 1);
            Gy_sum += Gy[a][b]*src.at<uchar>(i + a - 1, j + b - 1);
        }
      }
      G = abs(Gx_sum) + abs(Gy_sum);
      G = G > 255 ? 255:G;
      G = G < 0 ? 0:G;
      filtered.at<uchar>(i, j) = G;
      Gx_sum = 0;
      Gy_sum = 0;
    }
  }
  return filtered;
}