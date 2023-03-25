#pragma once
/**
* @brief There are stored all the details about animations
*/
class Animation
{
public:
	/// <summary>
	///  The rows of the animation, the frames that the animation has and that speed that it will be played aat
	/// </summary>
	int row, frames, speed;
	/**
	* @brief The constructor of the class with everything null
	*/
	Animation();
	/**
	* @brief The constructor of the class that will initialize the row, frames and speed
	*/
	Animation(int row, int frames, int speed);
	/**
	* @brief Set a new speed for the animation
	* @param speed The new speed of the animation
	*/
	void setSpeed(int speed);
};

