# Setup

1. Install ffmpeg with x265 codec.
2. Add the command ffmpeg into PATH.

# Compile

```
g++ main.cpp -o main
```

# Run

Run the program as ```<program name> <input filename> <output filename> <number of frames> <width> <height> <downsampling factor>```

For example,

```
./main bus_cif.yuv bus_cif.mp4 300 352 288 4
```

# Notes

The program should only work with YUV with format YCbCr 4:2:0.
