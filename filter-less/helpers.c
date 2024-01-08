#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Calculate for every pixel average value
    int RGB = 3;
    int average;

    // Set each color value to the average value
    for (int i = 0; i < height; i++)
        {
        for (int j = 0; j < width; j++)
            {
                float Blue = image[i][j].rgbtBlue;
                float Green = image[i][j].rgbtGreen;
                float Red = image[i][j].rgbtRed;
                average = round((Blue + Green + Red) / RGB);
                image[i][j].rgbtBlue = average;
                image[i][j].rgbtGreen = average;
                image[i][j].rgbtRed = average;
            }
        }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
        {
        for (int j = 0; j < width; j++)
            {
                int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
                int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
                int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
                if (sepiaRed > 255)
                    {
                        sepiaRed = 255;
                    }
                if (sepiaGreen > 255)
                    {
                        sepiaGreen = 255;
                    }
                if (sepiaBlue > 255)
                    {
                        sepiaBlue = 255;
                    }
                image[i][j].rgbtRed = sepiaRed;
                image[i][j].rgbtGreen = sepiaGreen;
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempRed, tempGreen, tempBlue;
    int middle = width / 2;

    for (int i = 0; i < height; i++) {

        for (int j = 0; j < middle; j++) {

            tempRed = image[i][j].rgbtRed;
            tempGreen = image[i][j].rgbtGreen;
            tempBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = tempRed;
            image[i][width - j - 1].rgbtGreen = tempGreen;
            image[i][width - j - 1].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of the original image to avoid overwriting the original pixels
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            copy[row][column] = image[row][column];
        }
    }

    // Calculate the average color values of each pixel's 3x3 neighborhood
    float totalr, totalg, totalb;
    int count = 0;
    totalr = totalg = totalb = 0;
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            // Loop through the 3x3 neighborhood of the current pixel
            for (int matrix3row = row - 1; matrix3row <= row + 1; matrix3row++)
            {
                for (int matrix3column = column - 1; matrix3column <= column + 1; matrix3column++)
                {
                    // Only calculate the average color values for pixels within the image boundaries
                    if (matrix3column < width && matrix3row < height && matrix3column >= 0 && matrix3row >= 0)
                    {
                        totalr += copy[matrix3row][matrix3column].rgbtRed;
                        totalg += copy[matrix3row][matrix3column].rgbtGreen;
                        totalb += copy[matrix3row][matrix3column].rgbtBlue;
                        count++;
                    }
                }
            }

            // Set the current pixel's color values to the average color values of its 3x3 neighborhood
            image[row][column].rgbtRed = round(totalr / count);
            image[row][column].rgbtGreen = round(totalg / count);
            image[row][column].rgbtBlue = round(totalb / count);

            // Reset the color value and count variables for the next pixel
            count = 0;
            totalr = totalg = totalb = 0;
        }
    }

    // Exit the function
    return;
}