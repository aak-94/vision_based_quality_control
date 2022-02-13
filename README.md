# vision_based_quality_control
 This is the source code for quality control of Vehicle identification number (VIN) using image processing algorithms
 
# Purpose:
VIN is an alphanumeric entity used to distinguish between the two vehicles. This differentiates the vehicles with indentical specifications. Correct and clear VIN is an leagal requiremnt. Any manufacturing error in this number would lead to leagal challenges. To avoid any quality issues with the VIN,  many industries prefer high automation which needs high investments. Simpler automation methods are cost effective but lacks robust qaulity inspection system. This projects provides the software prototype for such cost effective quality inspection system.

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
