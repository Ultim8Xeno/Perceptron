#include "AI.h"
#include <fstream>
#include <string>
#include <random>
#include <array>

float AI::weights[IMAGE_HEIGHT][IMAGE_WIDTH];

void AI::InitAI()
{
	// Set every vlaue in weights to 0
	for (int i = 0; i < IMAGE_HEIGHT; i++)
	{
		for (int j = 0; j < IMAGE_WIDTH; j++)
		{
			weights[i][j] = 0;
		}
	}
}

void AI::TrainAI(int tests)
{
	// images holds all shapes to test
	std::vector<Image*> images;
	images.resize(tests);

	// Generate all shapes
	for (int i = 0; i < tests; i++)
	{
		// type can be either rectangle or circle
		ImageType type = (rand() % 2 ? ImageType::Rectangle : ImageType::Circle);
		// x and y pos [0, 128], width and height [1, 128]
		// If circle, radius can not be less than 2 (otherwise it will be indentical to a rectangle)
		images[i] = new Image(type, rand() % 129, rand() % 129, (rand() % 129) + (type == ImageType::Circle ? 2 : 1), (rand() % 129) + 1);
	}

	// Go through every shape and adjust values when incorrect
	// Proven to converge (according to Veritasium)
	int amountWrong = 1;
	while (amountWrong)
	{
		amountWrong = 0;

		for (int k = 0; k < tests; k++)
		{
			if (PredictImage(images[k]) == images[k]->type)
			{
				continue;
			}
			amountWrong++;

			// Readjust Weights
			for (int i = 0; i < IMAGE_HEIGHT; i++)
			{
				for (int j = 0; j < IMAGE_WIDTH; j++)
				{
					// if pixel is black nothing changes
					// if pixel is white, changes based on shape
					weights[i][j] += images[k]->pixels[i][j] * (images[k]->type == ImageType::Rectangle ? 0.5f : -0.5f);
				}
			}
		}
		// Progress update
		std::cout << amountWrong << std::endl;
	}

	// Free up memory
	for (int i = 0; i < tests; i++)
	{
		delete images[i];
	}
}

ImageType AI::PredictImage(Image* img)
{
	// value = sum of weights of all white pixels
	float value = 0.0f;
	for (int i = 0; i < IMAGE_HEIGHT; i++)
	{
		for (int j = 0; j < IMAGE_WIDTH; j++)
		{
			value += img->pixels[i][j] * weights[i][j];
		}
	}

	// Return predicted shape
	if (value > 0.5f)
	{
		return ImageType::Rectangle;
	}
	return ImageType::Circle;
}

void AI::SaveAI(const std::string& name)
{
	// Save AI in ppm format
	std::ofstream file(name);

	// specify ppm and correct dimensions
	file << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

	for (int i = 0; i < IMAGE_HEIGHT; i++)
	{
		for (int j = 0; j < IMAGE_WIDTH; j++)
		{
			// r = g = b = weight * multiplier
			int val = static_cast<int>(weights[i][j] * 100.0f);
			file << val << ' ' << val << ' ' << val << '\n';
		}
	}

	file.close();
}

void AI::LoadAI(const std::string& name)
{
	// Load AI in ppm format
	std::ifstream file(name);

	// If file does not exist, end
	if (!file.is_open())
	{
		file.close();
		return;
	}

	// discard lines for specifying ppm
	std::string line("");
	std::getline(file, line);
	std::getline(file, line);
	std::getline(file, line);

	// Get every value and convert back to weight by dividing by multiplier
	for (int i = 0; i < IMAGE_HEIGHT; i++)
	{
		for (int j = 0; j < IMAGE_WIDTH; j++)
		{
			std::getline(file, line);
			weights[i][j] = std::atoi(line.substr(0, line.find(' ')).c_str())/100.0f;
		}
	}
	file.close();
}