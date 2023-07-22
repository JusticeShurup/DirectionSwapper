#include <opencv2/opencv.hpp>
#include <fstream>
#include <vector>

std::vector<std::string> inputFileDirections;
std::vector<std::string> outputFileDirections;
cv::Mat image;
cv::Size imageSize;
cv::Size textureSize;

std::map<std::string, cv::Mat> matByDirection; 

void loadInputFile()
{
    std::ifstream file("files//input.txt");
    
    while(!file.eof())
    {
        std::string direction;
        file >> direction;
        inputFileDirections.push_back(direction);
    }

    file.close();
}

void loadOutputFile()
{
    std::ifstream file("files//output.txt");
    
    while(!file.eof())
    {
        std::string direction;
        file >> direction;
        outputFileDirections.push_back(direction);
    }

    file.close();
}

void loadTextureSize()
{
    std::ifstream file("files//framesize.txt");  
    file >> textureSize.width >> textureSize.height;
    file.close();
}

void loadImageAndCrops()
{
    image = cv::imread("files//input.png", cv::IMREAD_UNCHANGED);
    cv::cvtColor(image, image, cv::COLOR_BGR2BGRA);
    if (!image.data)
    {
        std::cout << "Can't load image" << std::endl;
    }
    imageSize = image.size();

    for (int i = 0; i < inputFileDirections.size(); i++)
    {
        cv::Mat crop = image(cv::Rect(0, textureSize.height * i, image.size().width, textureSize.height));
        matByDirection[inputFileDirections[i]] = crop;
    }
}

void MakeResultFile()
{
    cv::Mat result;
    for (int i = 0; i < outputFileDirections.size(); i++)
    {
        result.push_back(matByDirection[outputFileDirections[i]]);
    }

    //clearTrashPixels(result);

    std::cout << "Direction swapped into output.png" << std::endl;
    cv::imwrite("files//output.png", result);
}

int main(int argc, char* argv[])
{

    loadInputFile();
    loadOutputFile();
    loadTextureSize();
    loadImageAndCrops();
    MakeResultFile();

    std::cin.get();
    return EXIT_SUCCESS;
}