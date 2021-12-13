# Two-view-Geometry-and-Correspondence-Matching
---
To establish correspondences between two calibrated camera pictures, we used epipolar geometry and normalized cross correlation (NCC). The objective was to create a program capable of automatically determining their relationship utilizing basic matrix transformation and NCC matching on two pictures recorded by two cameras.

<p align="center">
<img width="500" alt="image" src="https://user-images.githubusercontent.com/63264063/145907016-e01495ad-dc98-45e1-996d-c0f3063460bd.png">
</p>

The picture above illustrates the view collected simultaneously by the left and right cameras. By picking a pixel on the right picture, the epipoloar line from the left image is automatically located and the correlation is determined by NCC (indicated by the blue circle).  


<p align="center">
 <img width="860" alt="image" src="https://user-images.githubusercontent.com/63264063/145906479-590836a4-cf6b-4692-9b94-bf4fe00f98ae.png">
</p>

This sample illustrates the intrinsic and extrinsic characteristics of two cameras:  
fc left - the focal length of the left camera (fx and fy)  
cc left - the offset of the left camera's center (cx and cy)  

Rotation vector - the angle at which the left and right cameras are rotated relative to one another.  
Translation vector - the location of the left and right cameras in relation to one another.  

## Equation to solve it 

Step 1: Calibration  [F= k^(1^(-T) ) 〖[t]〗_x Rk^(-1)]  
Fc_left = [fx.fy]  
Cc_left = [cx cy]  
Rotate vectore  
Translation vectore [t] -> 〖[t]〗_(x_3x1 )  

0	-a_3	a_2  
a_3	0	-a_1  
-a_2	a_1	0  

Step 2: Selection of Points   
Step 3: plug it in  
Generate [a,d,c]^T  

Step 4: Perform a loop from 0 to 640 and you will get y by calculating x  

Step 5: Do NCC (normalized Cross Correlation)  
cos⁡〖θ= ((a.) ̅  (b.) ̅)/(|a ̅ |.|b ̅|)〗  
