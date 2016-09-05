#include "include/recog/JudgeChar.h"
#include "include/PreProcess.h"
#include "include/recog/GetCos.hpp"
#include "include/recog/Distinguishers.hpp"

//#define CHAR_MAX_WIDTH  1
//#define CHAR_MAX_HEIGHT 20

int main()
{


#ifdef __GET_STD_CHAR_IMAGE__
    PreProcess pre;   // binary threshold set to 140
    const char* img_dir = "./images/standard/chars/";
    for (int i = 0; i < 34; i++)
    {
        ProcessResult result = pre.pre_process(img_dir, IntToString(i).c_str(), ".bmp", true);
        if (result != ProcessResult::Success)
            break;
    }

#else
    PreProcess pre;
    const char* img_dir = "./images/";
    const char* filename = "chepai2";

    ProcessResult result = pre.pre_process(img_dir, filename, ".jpg", false);
    //ProcessResult result = ProcessResult::Success;

    if (result != ProcessResult::Success)
    {
        std::cout << "Process image failed." << std::endl;
        return 0;
    }

    std::cout << std::endl;

#ifdef __GET_EDGE_DATA__
    std::cout << "Edge data included." << std::endl;
#else
    std::cout << "Edge data not included." << std::endl;
#endif // __GET_EDGE_DATA__

    JudgeChar jc(img_dir);
    for (int i = 0; true; i++)
    {
        std::string s_filename = std::string(img_dir) + "crops/" + filename + "_cut_" + IntToString(i) + ".jpg";
        Mat char_mat = imread(s_filename, 0);

        if (!char_mat.data)
            break;

        std::cout << "Reading cropped image " << i << "..." << std::endl;

        // begin recognition
        char recommend;
        std::string possible_chars = jc.GetPossibleChars(char_mat, recommend);

        // when met some hard-recognized chars
        char recog = '\0';
        //if (possible_chars.find('0') != std::string::npos || possible_chars.find('8') != std::string::npos || possible_chars.find('Q') != std::string::npos)
        if (recommend == '0' || recommend == '8' || recommend == 'B' || recommend == 'D' || recommend == 'Q')
        {
            recog = Distinguish_0_8_B_D_Q(char_mat);
        }
        //else if (possible_chars.find('2') != std::string::npos || possible_chars.find('Z') != std::string::npos)
        else if (recommend == '2' || recommend == 'Z')
        {
            recog = Distinguish_2_Z(char_mat);
        }
        //else if (possible_chars.find('E') != std::string::npos ||
        //    possible_chars.find('F') != std::string::npos ||
        //    possible_chars.find('H') != std::string::npos ||
        //    possible_chars.find('L') != std::string::npos ||
        //    possible_chars.find('T') != std::string::npos)
//        else if (recommend == 'E' || recommend == 'F' || recommend == 'H' || recommend == 'L' || recommend == 'T')
//        {
//            recog = Distinguish_E_F_H_L_T(char_mat);
//        }
//        else if (recommend == '7' || recommend == 'J')
//        {
//            recog = Distinguish_7_J(char_mat);
//        }

        std::cout << "Possible chars: ";
        for (int i = 0; i < possible_chars.size(); i++)
        {
            std::cout << possible_chars.at(i) << " ";
        }

        if (recog != '\0')
        {
            std::cout << std::endl << "Recognized as: " << recog;
        }
        else if (recommend != '\0')
        {
            std::cout << std::endl << "Recommend: " << recommend;
        }

        std::cout << std::endl << std::endl;
    }
#endif // __GET_STD_CHAR_IMAGE__

    return 0;
}
