#pragma once
#include <iostream>
#include <fstream>

// Image dimensions
const int IMAGE_WIDTH = 128;
const int IMAGE_HEIGHT = 128;

// 2 types of shapes
enum class ImageType
{
	Circle, Rectangle
};

class Image
{
public:
	// Construct image based on parameters
	Image(ImageType p_type, int x, int y, int w, int h)
	{
		// Initialize member variables
		type = p_type;
		for (int i = 0; i < IMAGE_HEIGHT; i++)
		{
			for (int j = 0; j < IMAGE_WIDTH; j++)
				pixels[i][j] = 0;
		}
		
		if (type == ImageType::Rectangle)
		{
			// Loop through every pixel in box range and convert to white (1)
			for (int i = y-h/2.0f; i < y+h/2.0f; i++)
			{
				if (i >= IMAGE_HEIGHT || i < 0)
					continue;
				for (int j = x-w/2.0f; j < x+w/2.0f; j++)
				{
					if (j >= IMAGE_WIDTH || j < 0)
						continue;
					pixels[i][j] = 1;
				}
			}
		}

		if (type == ImageType::Circle)
		{
			// radius = w = h
			h = w;
			// Loop through every pixel in box range and if close enough to origin of circle, convert to white (1)
			for (int i = y - h / 2; i < y + h / 2; i++)
			{
				if (i >= IMAGE_HEIGHT || i < 0)
					continue;
				for (int j = x - w / 2; j < x + w / 2; j++)
				{
					if (j >= IMAGE_WIDTH || j < 0)
						continue;
					if ((j-x)*(j-x)+(i-y)*(i-y)<=w*w/4.0f)
						pixels[i][j] = 1;
				}
			}
		}
	}

	// For debug purposes, output image as ppm file
	void OutputPPM(const std::string& name)
	{
		std::ofstream file;
		file.open(name);

		// specify ppm and image dimensions
		file << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

		// set values in ppm file
		for (int i = 0; i < IMAGE_HEIGHT; i++)
		{
			for (int j = 0; j < IMAGE_WIDTH; j++)
			{
				int val = static_cast<int>(pixels[i][j] * 255.999);
				file << val << ' ' << val << ' ' << val << '\n';
			}
		}

		file.close();
	}
public:
	// Type of shape
	ImageType type;
	// All pixel data, float but for now can only be either 1 or 0
	float pixels[IMAGE_HEIGHT][IMAGE_WIDTH];
};