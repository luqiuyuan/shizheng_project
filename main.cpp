#include <iostream>
#include <cstdlib>
#include <string>

#include "downsample.h"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 7) {
    cout << "Run the program as <program name> <input filename> <output filename> <number of frames> <width> <height> <downsampling factor>" << endl;

    return 1;
  }

  // Get input filename and output filename from command line
  string input_filename = argv[1], output_filename = argv[2];

  // Get width, height and downsampling factor from command line
  int NUMBER_OF_FRAMES = atoi(argv[3]), WIDTH = atoi(argv[4]), HEIGHT = atoi(argv[5]), DOWNSAMPLING_FACTOR = atoi(argv[6]);
  if (NUMBER_OF_FRAMES == 0) { cout << "number of frames is invalid" << endl; return 1; }
  if (WIDTH == 0) { cout << "width is invalid" << endl; return 1; }
  if (HEIGHT == 0) { cout << "height is invalid" << endl; return 1; }
  if (DOWNSAMPLING_FACTOR == 0) { cout << "downsampling factor is invalid" << endl; return 1; }

  downsample(input_filename, "middle.yuv", NUMBER_OF_FRAMES, WIDTH, HEIGHT, DOWNSAMPLING_FACTOR);

  system(("ffmpeg -y -f rawvideo -vcodec rawvideo -s " + to_string(WIDTH / DOWNSAMPLING_FACTOR) + "x" + to_string(HEIGHT / DOWNSAMPLING_FACTOR) + " -r 25 -pix_fmt yuv420p -i middle.yuv -c:v libx265 -an -x265-params crf=25 " + output_filename).c_str());

  return 0;
}
