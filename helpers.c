#include "helpers.h"

#include <math.h>

#include <stdbool.h>

RGBTRIPLE custom(int i, int j, int height, int width, RGBTRIPLE image[height][width]);
const int Gx[3][3] = {
  {
    -1, 0, 1
  },
  {
    -2,
    0,
    2
  },
  {
    -1,
    0,
    1
  }
};
const int Gy[3][3] = {
  {
    -1, -2, -1
  },
  {
    0,
    0,
    0
  },
  {
    1,
    2,
    1
  }
};

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {

    for (int j = 0; j < width; j++) {
      int avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
      //avg = round(avg);
      image[i][j].rgbtRed = avg;
      image[i][j].rgbtGreen = avg;
      image[i][j].rgbtBlue = avg;
    }

  }
  return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {
    int halfWidth = round((float) 1 / 2 * width);
    for (int j = 0, k = width; j < width; j++, k--) {

      while (j < halfWidth) {
        RGBTRIPLE temp = image[i][j];
        image[i][j] = image[i][k];
        image[i][k] = temp;
        break;
      }

    }
  }
  return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
  for (int i = 0; i < height; i++) {

    for (int j = 0; j < width; j++) {

      int tempR = 0, tempG = 0, tempB = 0;
      int avgR = 0, avgG = 0, avgB = 0;
      if (i != height - 1 && i != 0 && j != 0 && j != width - 1) {

        for (int k = i - 1; k < i + 2; k++) {

          tempR = image[k][j - 1].rgbtRed + image[k][j].rgbtRed + image[k][j + 1].rgbtRed + tempR;
          tempG = (image[k][j - 1].rgbtGreen + image[k][j].rgbtGreen + image[k][j + 1].rgbtGreen) + tempG;
          tempB = (image[k][j - 1].rgbtBlue + image[k][j].rgbtBlue + image[k][j + 1].rgbtBlue) + tempB;

        }

        avgR = round(tempR / 9);
        avgG = round(tempG / 9);
        avgB = round(tempB / 9);

      } else if (j == width - 1 && i != 0 && i != height - 1) {

        for (int k = i - 1; k < i + 2; k++) {
          tempR = image[k][j - 1].rgbtRed + image[k][j].rgbtRed + tempR;
          tempG = image[k][j - 1].rgbtGreen + image[k][j].rgbtGreen + tempG;
          tempB = image[k][j - 1].rgbtBlue + image[k][j].rgbtBlue + tempB;
        }
        avgR = round(tempR / 6);
        avgG = round(tempG / 6);
        avgB = round(tempB / 6);
      } else if (j == 0 && i != 0 && i != height - 1) {

        for (int k = i - 1; k < i + 2; k++) {
          tempR = image[k][j].rgbtRed + image[k][j + 1].rgbtRed + tempR;
          tempG = image[k][j].rgbtGreen + image[k][j + 1].rgbtGreen + tempG;
          tempB = image[k][j].rgbtBlue + image[k][j + 1].rgbtBlue + tempB;
        }
        avgR = round(tempR / 6);
        avgG = round(tempG / 6);
        avgB = round(tempB / 6);
      } else if (i == 0 && j != 0 && j != width - 1) {

        for (int k = i; k < i + 2; k++) {
          tempR = image[k][j - 1].rgbtRed + image[k][j].rgbtRed + image[k][j + 1].rgbtRed + tempR;
          tempG = (image[k][j - 1].rgbtGreen + image[k][j].rgbtGreen + image[k][j + 1].rgbtGreen) + tempG;
          tempB = (image[k][j - 1].rgbtBlue + image[k][j].rgbtBlue + image[k][j + 1].rgbtBlue) + tempB;
        }
        avgR = round(tempR / 6);
        avgG = round(tempG / 6);
        avgB = round(tempB / 6);
      } else if (i == height - 1 && j != 0 && j != width - 1) {

        for (int k = i - 1; k < i + 1; k++) {
          tempR = image[k][j - 1].rgbtRed + image[k][j].rgbtRed + image[k][j + 1].rgbtRed + tempR;
          tempG = image[k][j - 1].rgbtGreen + image[k][j].rgbtGreen + image[k][j + 1].rgbtGreen + tempG;
          tempB = image[k][j - 1].rgbtBlue + image[k][j].rgbtBlue + image[k][j + 1].rgbtBlue + tempB;
        }
        avgR = round(tempR / 6);
        avgG = round(tempG / 6);
        avgB = round(tempB / 6);
      } else if (i == 0 && j == 0) {

        for (int k = i; k < i + 2; k++) {
          tempR = image[k][j].rgbtRed + image[k][j + 1].rgbtRed + tempR;
          tempG = image[k][j].rgbtGreen + image[k][j + 1].rgbtGreen + tempG;
          tempB = image[k][j].rgbtBlue + image[k][j + 1].rgbtBlue + tempB;
        }
        avgR = round(tempR / 4);
        avgG = round(tempG / 4);
        avgB = round(tempB / 4);
      } else if (i == 0 && j == width - 1) {

        for (int k = i; k < i + 2; k++) {
          tempR = image[k][j - 1].rgbtRed + image[k][j].rgbtRed + tempR;
          tempG = image[k][j - 1].rgbtGreen + image[k][j].rgbtGreen + tempG;
          tempB = image[k][j - 1].rgbtBlue + image[k][j].rgbtBlue + tempB;
        }
        avgR = round(tempR / 4);
        avgG = round(tempG / 4);
        avgB = round(tempB / 4);
      } else if (i == height - 1 && j == 0) {

        for (int k = i - 1; k < i + 1; k++) {
          tempR = image[k][j].rgbtRed + image[k][j + 1].rgbtRed + tempR;
          tempG = image[k][j].rgbtGreen + image[k][j + 1].rgbtGreen + tempG;
          tempB = image[k][j].rgbtBlue + image[k][j + 1].rgbtBlue + tempB;
        }
        avgR = round(tempR / 4);
        avgG = round(tempG / 4);
        avgB = round(tempB / 4);
      } else if (i == height - 1 && j == width - 1) {

        for (int k = i - 1; k < i + 1; k++) {
          tempR = image[k][j - 1].rgbtRed + image[k][j].rgbtRed + tempR;
          tempG = image[k][j - 1].rgbtGreen + image[k][j].rgbtGreen + tempG;
          tempB = image[k][j - 1].rgbtBlue + image[k][j].rgbtBlue + tempB;
        }

        avgR = round(tempR / 4);
        avgG = round(tempG / 4);
        avgB = round(tempB / 4);
      }

      image[i][j].rgbtRed = avgR;
      image[i][j].rgbtGreen = avgG;
      image[i][j].rgbtBlue = avgB;

    }

  }
  return;
}

bool valid_pixel(int i, int j, int height, int width) {
  return i >= 0 && i < height && j >= 0 && j < width;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {

  RGBTRIPLE new_image[height][width];
  for (int i = 0; i < height; i++) {

    for (int j = 0; j < width; j++) {

      new_image[i][j] = custom(i, j, height, width, image);

    }
  }

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      image[i][j] = new_image[i][j];
    }
  }
  return;
}

int cap(int value) {
  return value < 255 ? value : 255;
}

RGBTRIPLE custom(int i, int j, int height, int width, RGBTRIPLE image[height][width]) {
  int tempRx = 0, tempGx = 0, tempBx = 0, tempRy = 0, tempGy = 0, tempBy = 0;
  for (int k = -1; k <= 1; k++) {
    for (int f = -1; f <= 1; f++) {
      if (valid_pixel(i + k, i + f, height, width)) {
        tempRx += Gx[k + 1][f + 1] * image[i + k][j + k].rgbtRed;
        tempGx += Gx[k + 1][f + 1] * image[i + k][j + k].rgbtGreen;
        tempBx += Gx[k + 1][f + 1] * image[i + k][j + k].rgbtBlue;
        tempRy += Gy[k + 1][f + 1] * image[i + k][j + k].rgbtRed;
        tempGy += Gy[k + 1][f + 1] * image[i + k][j + k].rgbtGreen;
        tempBy += Gy[k + 1][f + 1] * image[i + k][j + k].rgbtBlue;
      }
    }
  }

  RGBTRIPLE pixel;
  pixel.rgbtRed = cap(round(sqrt(tempRx * tempRx + tempRy * tempRy)));
  pixel.rgbtGreen = cap(round(sqrt(tempGx * tempGx + tempGy * tempGy)));
  pixel.rgbtBlue = cap(round(sqrt(tempBx * tempBx + tempBy * tempBy)));
  return pixel;
}