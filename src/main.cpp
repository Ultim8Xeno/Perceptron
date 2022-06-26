#include <iostream>
#include "Image.h"
#include "AI.h"

int main()
{
	// Random Seed
	srand(time(NULL));

	// Initialize all weights to 0
	AI::InitAI();

	// Loads previous AI
	AI::LoadAI("AI.ppm");

	// Trains AI with 500 shapes
	AI::TrainAI(500);

	// Saves after training
	AI::SaveAI("AI.ppm");
}