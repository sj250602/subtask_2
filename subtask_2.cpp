#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

vector<Point2f> pts_src;
vector<Point2f> pts_dst;
Rect box;


Mat crop_frame(Mat im_src)
{
	Mat im_out; 
	Mat h = findHomography(pts_src, pts_dst);
	warpPerspective(im_src, im_out, h, im_src.size());
	String str_out_save = "Projected Frame.jpg";
	bool check = imwrite(str_out_save,im_out);
	Mat read_proj = imread(str_out_save);
	Mat crop(read_proj,box);
    	return crop;
}

int main(int argc, char* argv[])
{

	pts_dst.push_back(Point2f(472, 52));
	pts_dst.push_back(Point2f(472,830));
	pts_dst.push_back(Point2f(800, 830));
	pts_dst.push_back(Point2f(800, 52));

	pts_src.push_back(Point2f(969,233));
	pts_src.push_back(Point2f(614,974));
	pts_src.push_back(Point2f(1406,995));
	pts_src.push_back(Point2f(1254,230));

	box.width=(410);
	box.height=(1000);
	box.x=(430);
	box.y=(32);
	//open the video file for reading
	VideoCapture cap("trafficvideo.mp4"); 
	
	Mat emptyframe = imread("empty.jpg");
	
	// if not success, exit program
	if (cap.isOpened() == false)  
	{
		cout << "Cannot open the video file" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	//get the frames rate of the video
	double fps = cap.get(CAP_PROP_FPS); 
	cout << "Frames per seconds : " << fps << endl;

	double frames= cap.get(CAP_PROP_FRAME_COUNT);
	cout <<"No of frames="<< frames << "\n";
 	
 	String window_name = "Traffic_Density";

 	namedWindow(window_name, WINDOW_NORMAL); //create a window
	Mat crop_emp = crop_frame(emptyframe);
	
	while (true)
	{
		Mat curr_frame
		bool bSuccess = cap.read(curr_frame); // read a new frame from video
		//Breaking the while loop at the end of the video
		if (bSuccess == false)
  		{
   			cout << "Found the end of the video" << endl;
   			break;
  		}
  		
  		Mat curr_crop_frm = crop_frame(curr_frame);

		
  		//wait for for 10 ms until any key is pressed.  
  		//If the 'Esc' key is pressed, break the while loop.
  		//If the any other key is pressed, continue the loop 
  		//If any key is not pressed withing 10 ms, continue the loop
  		if (waitKey(40) == 27)
  		{
   			cout << "Esc key is pressed by user. Stopping the video" << endl;
   			break;
  		}
 	}
 
 	return 0;

}
