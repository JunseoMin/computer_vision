// #include <opencv/opencv.hpp>

// int main() {
//     // 이미지 크기 설정
//     int width = 640;
//     int height = 480;

//     // 그라데이션 시작 색상과 끝 색상 설정
//     cv::Scalar startColor(0, 0, 0);    // 검은색
//     cv::Scalar endColor(255, 255, 255); // 흰색

//     // 이미지 생성
//     cv::Mat gradientImage(height, width, CV_8UC3);

//     // 그라데이션 생성
//     for (int y = 0; y < height; y++) {
//         // 현재 행의 색상 계산
//         cv::Scalar rowColor = startColor + (endColor - startColor) * (static_cast<double>(y) / height);

//         // 현재 행에 색상 적용
//         gradientImage.row(y).setTo(rowColor);
//     }

//     // 윈도우 생성 및 이미지 표시
//     cv::namedWindow("Gradient Image", cv::WINDOW_NORMAL);
//     cv::imshow("Gradient Image", gradientImage);

//     // 키 입력 대기
//     cv::waitKey(0);

//     return 0;
// }