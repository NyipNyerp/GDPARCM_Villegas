#include "RTImage.h"
#include <opencv2/imgcodecs.hpp>

RTImage::RTImage(const int imageWidth, const int imageHeight)
{
	this->imageWidth = imageWidth;
	this->imageHeight = imageHeight;

	this->pixels = std::make_unique<cv::Mat>(cv::Mat::zeros(this->imageHeight, this->imageWidth, CV_8UC3));

	/*for (int i = 0; i < this->imageWidth; i++)
	{
		std::vector<Color> rows;
		this->pixels.pushback(rows);
		for (int j = 0; j < this->imageHeight; j++)
		{
			this->pixels[i].pushback(Color(0.0f, 0.0f, 0.0f));
		}
	}*/
}

void RTImage::setPixel(int x, int y, float r, float g, float b, int samplesPerPixel)
{
	//gamma correction
	float scale = 1.0f / samplesPerPixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	int rInt = static_cast<uchar>(256 * clamp(r, 0.0, 0.999f));
	int gInt = static_cast<uchar>(256 * clamp(g, 0.0, 0.999f));
	int bInt = static_cast<uchar>(256 * clamp(b, 0.0, 0.999f));

	cv::Mat imgChannels[3];
	cv::split(*this->pixels, imgChannels);

	//std::cout << "Pixels: " << this->pixels->size << " " << this->pixels->channels() << " " << x << " " << y << " " << std::endl;

	// Update the y-coordinate to reflect the correct orientation
	int newY = this->imageHeight - 1 - y;

	// Assign the pixel values to the correct position
	imgChannels[0].at<uchar>(newY, x) = bInt;
	imgChannels[1].at<uchar>(newY, x) = gInt;
	imgChannels[2].at<uchar>(newY, x) = rInt;

	imgChannels[0].at<uchar>(this->imageHeight - 1 - y, x) = bInt;
	imgChannels[1].at<uchar>(this->imageHeight - 1 - y, x) = gInt;
	imgChannels[2].at<uchar>(this->imageHeight - 1 - y, x) = rInt;

	cv::merge(imgChannels, 3, *this->pixels);
}

//std::vector <std::vector<Color>> RTImage::returnImage()
//{
//	return this->pixels;
//}

void RTImage::saveImage(cv::String& fileName) const
{
	cv::Mat flippedImage;
	cv::flip(*this->pixels, flippedImage, 0);  // Flip the image around the horizontal axis

	cv::imwrite(fileName, flippedImage);

	//cv::imwrite(fileName, *this->pixels);
}

float RTImage::clamp(float value, float min, float max)
{
	return (value < min) ? min : (value > max) ? max : value;
}
