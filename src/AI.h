#pragma once
#include "Image.h"

class AI
{
public:
	// Initailize
	static void InitAI();
	// Train AI, generate (times) shapes and test
	static void TrainAI(int times);
	// Predicts what shape img is
	static ImageType PredictImage(Image* img);
	
	// Save and load to files
	static void SaveAI(const std::string& name);
	static void LoadAI(const std::string& name);
private:
	// Weights for every pixel
	static float weights[IMAGE_HEIGHT][IMAGE_WIDTH];
};