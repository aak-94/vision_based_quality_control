# vision_based_quality_control
 This is the source code for quality control of Vehicle identification number (VIN) using image processing algorithms
 
## Algorithm
step-1 : Take the input image & relavant library image 

step-2 : Extract each letter from input image

step-3 : apply FFT to the extracted letter and library image

step-4 : apply ORB feature matching algorithm

step-5 : define quality constraint to decide the product quality

## Repository structure
Repo
- Resuorces
  - contains smaple images in .png format

- src
  - dataloader.cpp
  - dataloader.h
  - fft.cpp
  - fft.h
  -  image_processing.cpp
  -  image_processing.h
  -  main.cpp
  -   utils.cpp
  -    utils.h
   
## dependancies
Opencv

## Refernces:
FFT processeing: [Fourier_Transform](https://github.com/Saleh-I/Fourier-Transform.git)
