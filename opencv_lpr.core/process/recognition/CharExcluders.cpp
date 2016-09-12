#include "CharExcluders.h"

void CharExcluders::ByWhitePointsOnHorizontalMediumLine(const cv::Mat& mat, std::map<char, double>& cos_result, char to_remove)
{
    int white_pixel_points = 0;
    int height = mat.rows, width = mat.cols;

    for (int w = 0; w < width; w++)
    {
        int pixel = mat.at<uchar>(height / 2, w);
        if (pixel >= WHITE_THRESHOLD)
            white_pixel_points++;
    }

    if (white_pixel_points > 18)
        cos_result.erase(to_remove);
}

void CharExcluders::ByWhiteAreasOnVerticalMediumLine(const cv::Mat& mat, std::map<char, double>& cos_result, char to_remove)
{
    int height = mat.rows, width = mat.cols;

    int white_area_count = 0;
    int last_pixel = 0;
    for (int h = 0; h < height; h++)
    {
        int pixel = mat.at<uchar>(h, width / 2);
        if (pixel >= WHITE_THRESHOLD && last_pixel < WHITE_THRESHOLD)
            white_area_count++;
        last_pixel = pixel;
    }

    if (white_area_count < 3)
        cos_result.erase(to_remove);
}

void CharExcluders::ByWhiteAreasOnHorizontal3_4Line(const cv::Mat& mat, std::map<char, double>& cos_result, char to_remove)
{
    int height = mat.rows, width = mat.cols;

    int white_area_count = 0;
    int last_pixel = 0;
    for (int w = 0; w < width; w++)
    {
        int pixel = mat.at<uchar>(height * 3 / 4, w);
        if (pixel >= WHITE_THRESHOLD && last_pixel < WHITE_THRESHOLD)
            white_area_count++;
        last_pixel = pixel;
    }

    if (white_area_count > 1)
        cos_result.erase(to_remove);
}

void CharExcluders::ByWhiteAreasOnAllHorizontalLine(const cv::Mat& mat, std::map<char, double>& cos_result, char to_remove)
{
    int height = mat.rows, width = mat.cols;

    int h_with_one_white_area_start = 0;

    int white_area_count;
    int last_pixel;
    for (int h = 0; h < height; h++)
    {
        white_area_count = 0;
        last_pixel = 0;
        for (int w = 0; w < width; w++)
        {
            int pixel = mat.at<uchar>(h, w);
            if (pixel >= WHITE_THRESHOLD && last_pixel < WHITE_THRESHOLD)
                white_area_count++;
            last_pixel = pixel;
        }

        if (white_area_count < 2)
        {
            h_with_one_white_area_start = h;
            break;
        }
    }

    if (h_with_one_white_area_start > 30)
        cos_result.erase(to_remove);
}
