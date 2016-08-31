#include "PreProcess.h"

PreProcess::PreProcess(int w, int h) : char_max_width(w), char_max_height(h)
{
}

ProcessResult PreProcess::pre_process(const char* img_dir, const char* filename, const char* extname, bool toReverse)
{
    std::string s_filename = std::string(img_dir) + filename + extname;
    Mat src = imread(s_filename.c_str());

    if (!src.data)
    {
        return ProcessResult::Failed;
    }

    // window
    //namedWindow("window", CV_WINDOW_AUTOSIZE);

    // convert to gray
    cvtColor(src, src, CV_BGR2GRAY);

    // binarize
    threshold(src, src, 125, 255, CV_THRESH_BINARY);

    // reverse if needed
    if (toReverse)
        bitwise_not(src, src);

    // thinning
    Mat src_thin;
    thinner.Thinning_2(src, src_thin);

    // get the contours
    std::vector<std::vector<Point> > contours;
    findContours(src_thin.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    std::cout << "Count of contours: " << contours.size() << std::endl;

    std::vector<Rect> rects;
    for (std::vector<std::vector<Point> >::iterator it = contours.begin(); it != contours.end(); it++)
    {
        Rect r = boundingRect(*it);
        // only store large contours
        if (r.width > char_max_width && r.height > char_max_height)
        {
            rects.push_back(r);
        }
    }

    std::cout << "Count of rects available: " << rects.size() << std::endl;

    // sort contours from left to right
    std::sort(rects.begin(), rects.end(), [](Rect a, Rect b){ return a.x < b.x; });

    int i = 0;
    for (std::vector<Rect>::iterator it = rects.begin(); it != rects.end(); it++)
    {
        Rect r = *it;

        Range rg_row, rg_col;

        //std::cout << r.y << " " << r.height << " " << r.x << " " << r.width << std::endl;

        rg_row.start = r.y;
        rg_row.end = r.y + r.height;
        rg_col.start = r.x;
        rg_col.end = r.x + r.width;

        Mat tmp(src_thin, rg_row, rg_col);

        // normalization
        Mat tmp_resize;
        resize(tmp, tmp_resize, Size(CROP_WIDTH, CROP_HEIGHT));

        threshold(tmp_resize, tmp_resize, WHITE_THRESHOLD, 255, CV_THRESH_BINARY);

        //Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
        //erode(tmp, tmp, kernel);
        //dilate(tmp, tmp, 0);

        std::string s_filename = std::string(img_dir) + "crops/" + filename + "_cut_" + IntToString(i++) + ".jpg";
        imwrite(s_filename.c_str(), tmp_resize);

        //rectangle(src, r, Scalar(125), 1);
    }

    //imshow("window", src);

    //waitKey();

    return ProcessResult::Success;
}
