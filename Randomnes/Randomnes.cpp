// Randomnes.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//


#include <iostream>
#include <chrono>
#include <random>
#include "lodepng.h"
#include "Perlin.h"

double octave(size_t octaves, double x, double y, double freq, double amp, osn_context *ctx){
	double output = 0.f;
	double frequency = 1/freq;
	double amplitude = amp;

	for (size_t i = 0; i < octaves; i++) {
		output += (amplitude * open_simplex_noise2(ctx, x * frequency, y * frequency));

		frequency *= 2;
		amplitude *= 0.5;
	}

	return output;
}

int main()
{
	
	unsigned width = 512*2 , height = 512;
	double FEATURE_SIZE = 15;

	std::vector<unsigned char> image;
	image.resize(width * height * 4);

	struct osn_context *ctx;

	open_simplex_noise(77374, &ctx);

	for (unsigned y = 0; y < height; y++) {
		for (unsigned x = 0; x < width; x++)
		{
			double output = 0.f;
			double frequency = 0.1 ;
			double amplitude = 1.0;

			for (size_t i = 0; i < 128; i++) {
				double change = (amplitude * open_simplex_noise2(ctx, x * frequency, y * frequency));
				if (output + change > 1.0 || output + change < -1.0)
					change *= -0.3;
				output += change;

				frequency *= 2;
				amplitude *= 0.5;
			}
			double value = output;
			char c = value * 128 + 128;

			image[4 * width * y + 4 * x + 0] = c;
			image[4 * width * y + 4 * x + 1] = c;
			image[4 * width * y + 4 * x + 2] = c;
			image[4 * width * y + 4 * x + 3] = 255;
		}
	}
	std::vector<unsigned char> png;
	unsigned error = lodepng::encode(png, image, width, height);
	char file[255];
	sprintf(file, "img.jpg");
	if (!error) lodepng::save_file(png, file);
	
	return 0;
}
//3946540168