#pragma once
#include <iostream>

/**
	* @brief 2D vector class
	* @details This class is used to represent 2D vectors and points
*/
class Vector2D
{
public:
	/// <summary>
	///  x and y coordinate stored as float in the vector
	/// </summary>
	float x, y;
	/**
		* @brief Default constructor
		* @details Creates a vector with x and y set to 0
	*/
	Vector2D();
	/**
		* @brief Constructor
		* @details Creates a vector with x and y set to the given values
		* @param x x coordinate
		* @param y y coordinate
	*/
	Vector2D(float x, float y);
	/**
		* @brief Constructor
		* @details Creates a vector with y set to the given values and x centered to the given width
		* @param w entity width for center
		* @param scr_w screen width(or section witdh)
		* @param y y coordinate
	*/
	Vector2D(int w, int scr_w, float y);
	/**
		* @brief Constructor
		* @details Creates a vector with x set to the given values and y centered to the given height
		* @param x x coordinate
		* @param h entity height for center
		* @param scr_h screen height(or section height)
	*/
	Vector2D(float x, int h, int scr_h);
	/**
		* @brief Constructor
		* @details Creates a vector with x and y centered in the given section 
		* @param w entity width for center
		* @param h entity height for center
		* @param scr_w screen width(or section witdh)
		* @param scr_h screen height(or section height)
	*/
	Vector2D(int w, int scr_w, int h, int scr_h);

	/**
		* @brief Adds every member of the vectors
		* @param vec the vector you want to add to the stored vector
	*/
	Vector2D& add(const Vector2D& vec);
	/**
		* @brief Subs every member of the vectors
		* @param vec the vector you want to subs to the stored vector
	*/
	Vector2D& sub(const Vector2D& vec);
	/**
		* @brief Multiply every member of the vectors
		* @param vec the vector you want to multiply to the stored vector
	*/
	Vector2D& mul(const Vector2D& vec);
	/**
		* @brief Divides every member of the vectors
		* @param vec the vector you want to divides to the stored vector
	*/
	Vector2D& div(const Vector2D& vec);

	/**
		* @brief Adds an constant valeu to every coordonat of the vector
		* @param val the added constant
	*/
	Vector2D& add(const float& val);
	/**
		* @brief Subs an constant valeu to every coordonat of the vector
		* @param val the subed constant
	*/
	Vector2D& sub(const float& val);
	/**
		* @brief Multiply an constant valeu to every coordonat of the vector
		* @param val the multiplied constant
	*/
	Vector2D& mul(const float& val);
	/**
		* @brief Divides an constant valeu to every coordonat of the vector
		* @param val the divided constant
	*/
	Vector2D& div(const float& val);

	/**
		* @brief The lenght of the vector
	*/
	double length();
	/**
		* @brief Normalized vector
	*/
	Vector2D& normalize();

	/**
		* @brief Overload of the + operator
		* @param vec1 the vector you want to add to the stored vector
		* @param vec2 is the vector that is added
	*/
	friend Vector2D& operator+(Vector2D& vec1, const Vector2D& vec2);
	/**
		* @brief Overload of the - operator
		* @param vec1 the vector you want to subs to the stored vector
		* @param vec2 is the vector that is subs
	*/
	friend Vector2D& operator-(Vector2D& vec1, const Vector2D& vec2);
	/**
		* @brief Overload of the * operator
		* @param vec1 the vector you want to multiply to the stored vector
		* @param vec2 is the vector that is multiplied
	*/
	friend Vector2D& operator*(Vector2D& vec1, const Vector2D& vec2);
	/**
		* @brief Overload of the / operator
		* @param vec1 the vector you want to divides to the stored vector
		* @param vec2 is the vector that is divided
	*/
	friend Vector2D& operator/(Vector2D& vec1, const Vector2D& vec2);

	/**
		* @brief Overload of the + operator
		* @param vec1 the vector you want to add to the stored vector
		* @param val is the constant that is added
	*/
	friend Vector2D& operator+(Vector2D& vec1, const float& val);
	/**
		* @brief Overload of the - operator
		* @param vec1 the vector you want to subs to the stored vector
		* @param val is the constant that is subs
	*/
	friend Vector2D& operator-(Vector2D& vec1, const float& val);
	/**
		* @brief Overload of the * operator
		* @param vec1 the vector you want to multiply to the stored vector
		* @param val is the constant that is multiplied
	*/
	friend Vector2D& operator*(Vector2D& vec1, const float& val);
	/**
		* @brief Overload of the / operator
		* @param vec1 the vector you want to divides to the stored vector
		* @param val is the constant that is divided
	*/
	friend Vector2D& operator/(Vector2D& vec1, const float& val);

	/**
		* @brief Overload of the += operator
		* @param vec the vector you want to add to the stored vector
	*/
	Vector2D& operator+=(const Vector2D& vec);
	/**
		* @brief Overload of the -= operator
		* @param vec the vector you want to subs to the stored vector
	*/
	Vector2D& operator-=(const Vector2D& vec);
	/**
		* @brief Overload of the *= operator
		* @param vec the vector you want to multiply to the stored vector
	*/
	Vector2D& operator*=(const Vector2D& vec);
	/**
		* @brief Overload of the /= operator
		* @param vec the vector you want to divides to the stored vector
	*/
	Vector2D& operator/=(const Vector2D& vec);

	/**
		* @brief Overload of the += operator
		* @param val the constant you want to add to the stored vector
	*/
	Vector2D& operator+=(const float& val);
	/**
		* @brief Overload of the -= operator
		* @param val the constant you want to subs to the stored vector
	*/
	Vector2D& operator-=(const float& val);
	/**
		* @brief Overload of the *= operator
		* @param val the constant you want to multiply to the stored vector
	*/
	Vector2D& operator*=(const float& val);
	/**
		* @brief Overload of the /= operator
		* @param val the constant you want to divides to the stored vector
	*/
	Vector2D& operator/=(const float& val);

	/**
		* @brief Overload of the << operator
		* @details Prints the vector in the format (x, y)
		* @param out the output stream
		* @param vec the vector you want to print
	*/
	friend std::ostream& operator<<(std::ostream& out, const Vector2D& vec);
};