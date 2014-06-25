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
 along with Libbonny.If not, see <http://www.gnu.org/licenses/>.


	6:12:2008   15:04
*/

#ifndef _BONNYCXX_POLICY_MULTIMEDIA_STORAGE_OPENCVFILESTORAGE_H 
#define _BONNYCXX_POLICY_MULTIMEDIA_STORAGE_OPENCVFILESTORAGE_H 1

#ifdef _BONNYCXX_OPENCV_SUPPORT_

#include <string>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

namespace BonnyCxx{
	namespace Policy {
		namespace Multimedia {
			namespace Storage {

/*
 * @OpenCVFileStorage
 *
 * Policy to store a opencv image on file system
 */
struct OpenCVFileStorage
{
	/* 
	* Store
	*
	* @param std::string name of the image in filesystem, relative or absolute path
	* @param  boost::shared_ptr<IplImage> the image data to store
	*/
	bool Store( const std::string& name, const boost::shared_ptr<IplImage>& m_pImageData )
	{
		return ( cvSaveImage( name.c_str(), m_pImageData.get()  ) != 0 );
	}

}; //end struct OpenCVFileStorage

			}//end namespace Storage
		}//end namespace Multimedia
	}//end namespace Policy
}//end namespace BonnyCxx


#endif //_BONNYCXX_OPENCV_SUPPORT_

#endif //_BONNYCXX_POLICY_MULTIMEDIA_STORAGE_OPENCVFILESTORAGE_H