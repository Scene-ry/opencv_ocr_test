#include "JudgeChar.h"

JudgeChar::JudgeChar(const char* img_dir) : fvec(CROP_WIDTH, CROP_HEIGHT)
{
    for (int i = 0; i <= 9; i++)
    {
        std::string std_img_file = std::string(img_dir) + "standard/20x40/" + IntToString(i) + ".jpg";
        Mat std_img = imread(std_img_file.c_str());

        fvec.AddSampleDepthVectorLeft(std_img, StdCharVectorsLeft[i]);
        fvec.AddSampleDepthVectorRight(std_img, StdCharVectorsRight[i]);
        fvec.AddSampleDepthVectorUp(std_img, StdCharVectorsUp[i]);
        fvec.AddSampleDepthVectorDown(std_img, StdCharVectorsDown[i]);
    }

    for (int i = 10; i < 36; i++)
    {
        char ch = 'A' + i - 10;

        if (ch == 'O' || ch == 'I')
        {
            continue;
        }

        std::string std_img_file = std::string(img_dir) + "standard/20x40/" + ch + ".jpg";
        Mat std_img = imread(std_img_file.c_str());

        fvec.AddSampleDepthVectorLeft(std_img, StdCharVectorsLeft[i]);
        fvec.AddSampleDepthVectorRight(std_img, StdCharVectorsRight[i]);
        fvec.AddSampleDepthVectorUp(std_img, StdCharVectorsUp[i]);
        fvec.AddSampleDepthVectorDown(std_img, StdCharVectorsDown[i]);
    }
}

std::string JudgeChar::GetPossibleChars(const Mat& mat)
{
    std::string res;
    std::map<char, double> char_cos_values;

    std::vector<double> mat_vec_left, mat_vec_right, mat_vec_up, mat_vec_down;
    fvec.AddSampleDepthVectorLeft(mat, mat_vec_left);
    fvec.AddSampleDepthVectorRight(mat, mat_vec_right);
    fvec.AddSampleDepthVectorUp(mat, mat_vec_up);
    fvec.AddSampleDepthVectorDown(mat, mat_vec_down);

    double min_value = 1;
//    char res = '\0';
    for (int i = 0; i < 36; i++)
    {
        double cos_value_left = GetCos::GetVectorCos(mat_vec_left, StdCharVectorsLeft[i]);
        double cos_value_right = GetCos::GetVectorCos(mat_vec_right, StdCharVectorsRight[i]);
        double cos_value_up = GetCos::GetVectorCos(mat_vec_up, StdCharVectorsUp[i]);
        double cos_value_down = GetCos::GetVectorCos(mat_vec_down, StdCharVectorsDown[i]);

        double cos_value = (0.8 * cos_value_left + 0.8 * cos_value_up + 0.7 * cos_value_right + 0.9 * cos_value_down) / 4.0;
        if (i >= 0 && i <= 9)
        {
            char_cos_values.insert(std::make_pair('0' + i, cos_value));
            if (1 - cos_value <= SIMILAR_THRESHOLD)
                res.append(1, '0' + i);
        }
        else
        {
            char_cos_values.insert(std::make_pair('A' + i - 10, cos_value));
            if (1 - cos_value <= SIMILAR_THRESHOLD)
                res.append(1, 'A' + i - 10);
        }
    }

    // increase threshold until a char matches
    for (double higher_th = SIMILAR_THRESHOLD - 0.01; res.length() <= 0; higher_th += 0.01)
    {
        for (std::map<char, double>::iterator it = char_cos_values.begin(); it != char_cos_values.end(); it++)
        {
            if (1 - it->second <= higher_th)
                res.append(1, it->first);
        }
    }

//    if (res == '0' || res == 'Q' || res == '8')
//    {
//        return Distinguish_0_8_Q(mat);
//    }
//    if (res == '2' || res == 'Z')
//    {
//
//    }

    return res;
}
