#include "FeatureVectorHelper.h"

FeatureVectorHelper::FeatureVectorHelper(int w, int h) : width(w), height(h)
{
}

void FeatureVectorHelper::AddFeatureVectors(const Mat& mat, std::vector<double>& result)
{
    AddSlopeVector(mat, result);
    AddDepthVector(mat, result);
    AddInflexionVector(mat, result);
    AddInnerPixelsVector(mat, result);
}

void FeatureVectorHelper::AddSampleDepthVectorLeft(const Mat& mat, std::vector<double>& result)
{
    int h_incr = height / 10;

    for (int h = h_incr; h < height; h += h_incr)
    {
        for (int w = 0; w < width; w++)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                result.push_back(w);
                break;
            }
        }
        result.push_back(width);
    }
}

void FeatureVectorHelper::AddSampleDepthVectorRight(const Mat& mat, std::vector<double>& result)
{
    int h_incr = height / 10;

    for (int h = h_incr; h < height; h += h_incr)
    {
        for (int w = width - 1; w >= 0; w--)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                result.push_back(width - w);
                break;
            }
        }
        result.push_back(width);
    }
}

void FeatureVectorHelper::AddSampleDepthVectorUp(const Mat& mat, std::vector<double>& result)
{
    int w_incr = width / 10;

    for (int w = w_incr; w < width; w += w_incr)
    {
        for (int h = 0; h < height; h++)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                result.push_back(h);
                break;
            }
        }
        result.push_back(height);
    }
}

void FeatureVectorHelper::AddSampleDepthVectorDown(const Mat& mat, std::vector<double>& result)
{
    int w_incr = width / 10;

    for (int w = w_incr; w < width; w += w_incr)
    {
        for (int h = height - 1; h >= 0; h--)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                result.push_back(height - h);
                break;
            }
        }
        result.push_back(height);
    }
}

void FeatureVectorHelper::AddSlopeVector(const Mat& mat, std::vector<double>& result)
{
    // left
    double l_pos = 0, l_neg = 0, l_zerocount = 0;
    int h_prev = -1, w_prev = -1;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                if (h_prev != -1)
                {
                    if (w == w_prev)
                    {
                        // slope is not exist
                        h_prev = h;
                        w_prev = w;
                        break;
                    }
                    if (h == h_prev)
                    {
                        // slope is zero
                        l_zerocount++;
                    }
                    else
                    {
                        double k = (h - h_prev) / (double)(w - w_prev);
                        if (k > 0) l_pos += k;
                        else l_neg += k;
                    }

                }
                h_prev = h;
                w_prev = w;
                break;
            }
        }
    }
    result.push_back(l_pos);
    result.push_back(l_neg);
    result.push_back(l_zerocount);

    // up
    double u_pos = 0, u_neg = 0, u_zerocount = 0;
    h_prev = -1; w_prev = -1;
    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                if (h_prev != -1)
                {
                    if (w == w_prev)
                    {
                        // slope is not exist
                        h_prev = h;
                        w_prev = w;
                        break;
                    }
                    if (h == h_prev)
                    {
                        // slope is zero
                        u_zerocount++;
                    }
                    else
                    {
                        double k = (h - h_prev) / (double)(w - w_prev);
                        if (k > 0) u_pos += k;
                        else u_neg += k;
                    }

                }
                h_prev = h;
                w_prev = w;
                break;
            }
        }
    }
    result.push_back(u_pos);
    result.push_back(u_neg);
    result.push_back(u_zerocount);

    // right
    double r_pos = 0, r_neg = 0, r_zerocount = 0;
    h_prev = -1; w_prev = -1;
    for (int h = 0; h < height; h++)
    {
        for (int w = width - 1; w >= 0; w--)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                if (h_prev != -1)
                {
                    if (w == w_prev)
                    {
                        // slope is not exist
                        h_prev = h;
                        w_prev = w;
                        break;
                    }
                    if (h == h_prev)
                    {
                        // slope is zero
                        r_zerocount++;
                    }
                    else
                    {
                        double k = (h - h_prev) / (double)(w - w_prev);
                        if (k > 0) r_pos += k;
                        else r_neg += k;
                    }

                }
                h_prev = h;
                w_prev = w;
                break;
            }
        }
    }
    result.push_back(r_pos);
    result.push_back(r_neg);
    result.push_back(r_zerocount);

    // down
    double d_pos = 0, d_neg = 0, d_zerocount = 0;
    h_prev = -1; w_prev = -1;
    for (int w = 0; w < width; w++)
    {
        for (int h = height - 1; h >= 0; h--)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                if (h_prev != -1)
                {
                    if (w == w_prev)
                    {
                        // slope is not exist
                        h_prev = h;
                        w_prev = w;
                        break;
                    }
                    if (h == h_prev)
                    {
                        // slope is zero
                        d_zerocount++;
                    }
                    else
                    {
                        double k = (h - h_prev) / (double)(w - w_prev);
                        if (k > 0) d_pos += k;
                        else d_neg += k;
                    }

                }
                h_prev = h;
                w_prev = w;
                break;
            }
        }
    }
    result.push_back(d_pos);
    result.push_back(d_neg);
    result.push_back(d_zerocount);
}

void FeatureVectorHelper::AddDepthVector(const Mat& mat, std::vector<double>& result)
{
    // left
    double depth_sum = 0;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                depth_sum += w;// / (double)width;
                break;
            }
        }
    }
    result.push_back(depth_sum);

    // up
    depth_sum = 0;
    for (int w = 0; w < width; w++)
    {
        for (int h = 0; h < height; h++)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                depth_sum += h;// / (double)height;
                break;
            }
        }
    }
    result.push_back(depth_sum);

    // right
    depth_sum = 0;
    for (int h = 0; h < height; h++)
    {
        for (int w = width - 1; w >= 0; w--)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                depth_sum += (width - w);// / (double)width;
                break;
            }
        }
    }
    result.push_back(depth_sum);

    // down
    depth_sum = 0;
    for (int w = 0; w < width; w++)
    {
        for (int h = height - 1; h >= 0; h--)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                depth_sum += (height - h);// / (double)height;
                break;
            }
        }
    }
    result.push_back(depth_sum);
}

void FeatureVectorHelper::AddInflexionVector(const Mat& mat, std::vector<double>& result)
{

}

void FeatureVectorHelper::AddInnerPixelsVector(const Mat& mat, std::vector<double>& result)
{
    int area1_pixel_count = 0;
    int area2_pixel_count = 0;

    int area1_start_w = 5;
    int area1_start_h = 10;
    int area1_end_w = 15;
    int area1_end_h = 30;

    int area2_start_w = 0;
    int area2_start_h = 30;
    int area2_end_w = 20;
    int area2_end_h = 40;

    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            if ((int)mat.data[h * width + w] >= 125)
            {
                if (w >= area1_start_w && w < area1_end_w && h >= area1_start_h && h < area1_end_h)
                {
                    area1_pixel_count++;
                }
                if (w >= area2_start_w && w < area2_end_w && h >= area2_start_h && h < area2_end_h)
                {
                    area2_pixel_count++;
                }
            }
        }
    }

    result.push_back(area1_pixel_count);
    result.push_back(area2_pixel_count);
}
