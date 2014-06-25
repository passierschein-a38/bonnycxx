/*
 Bonny C++ Library - libbonny

 Axel Sauerhoefer
 Beethovenring 20
 76761 Ruelzheim

 axel[at]willcodeqtforfood.de
 http://www.willcodeqtforfood.de

 This file is part of libbonny.

 Libbonny is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Libbonny is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with libbonny. If not, see <http://www.gnu.org/licenses/>.


	18:10:2008   22:54
*/

#ifndef _BONNYCXX_OSTREAMOUT_H_
#define _BONNYCXX_OSTREAMOUT_H_ 1

#include <iostream>
#include <boost/noncopyable.hpp>

namespace BonnyCxx{

/*
 * @brief IOStreamOut
 *
 * Template class for wrapping object to stream it out to an std::ostream.
 * The wrapped class must have a std::string ToString method implemented.
 *
 * @code
 *
 * class Foo 
 * {
 *  ...
 *  public:
 *		void ToString()
 *			{
				return "FooBar";
			}
 * }; //end class Foo
 *
 * ...
 * Foo obj;
 * std::cout << IOStreamOut<Foo>(obj); // the ToString method is called
 *
 * @endcode
 */

/*
 * Forwarder
 */
template<typename T>  
class IOStreamOut;  

template<typename T>  
std::ostream& operator<<(std::ostream& os, const IOStreamOut<T>& obj)
{
	std::string buffer = obj.Get().ToString();
	os.write( buffer.c_str(), static_cast<std::streamsize>(buffer.size()) );
	return os;
}

template<typename T>
class IOStreamOut 
{
public:

	/*
	* C'tor
	*/
	IOStreamOut( const T& obj )
		: m_obj( obj )
	{
	}

	/*
	 * D'tor
	 */
	virtual ~IOStreamOut(){};

	/*
	 * ostream operator
	 */
	friend std::ostream &operator<< <>(std::ostream &, const IOStreamOut<T>& obj);  

	/*
	 * Get the wrapped object
	 */
	T Get() const
	{
		return m_obj;
	}

private:

	/*
	 * C'tor
	 *
	 * Default constructor should never be called.
	 */
	IOStreamOut(){};

	/*
	 * The wrapped object
	 */
	T m_obj;

};//end class IOStreamOut

}//end namepsace BonnyCxx

#endif //_BONNYCXX_OSTREAMOUT_H_