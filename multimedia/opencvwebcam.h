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


	6:12:2008   14:22
*/

#ifndef _BONNYCXX_MULTIMEDIA_OPENCVWEBCAM_H_
#define _BONNYCXX_MULTIMEDIA_OPENCVWEBCAM_H_ 1

#ifdef _BONNYCXX_OPENCV_SUPPORT_

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include "policy/threading/locking/single.h"
#include "policy/multimedia/storage/opencvfilestorage.h"

namespace BonnyCxx{
	namespace Multimedia {

/*
 * @brief OpenCVWebCam
 *
 * Template class for working with opencv webcam c api. 
 * With this class you can start, stop a specific webcam in your system. Also
 * you can grab  and save a image from this cam.
 *
 *
 * @code
 *
 * OpenCVWebCam<> cam;
 *
 * if( cam.Start() == false )
 * {
 *   //custom error handling here
 * }
 * 
 * OpenCVWebCam<>::ImageType pImage = cam.GrabImage();
 *
 * if( !pImage )
 * {
 *	 //custom error handling here
 * }
 *
 * const std::string name = "webcam_tst.jpg";
 *
 * if ( cam.Store( name , pImage ) == false )
 * {
 *	//custom error handling here
 * }
 *
 * cam.Stop();
 *
 * @endcode
 *
 * You can use this class in a single / multi threaded environment.
 * At the momen the default policy specifieces single threaded.
 * This means that there is no locking. 
 *
 * It is also possible to put another storage policiy in this class.
 * The default is to store the image on the file system.
 *
 */
template < typename Locking = BonnyCxx::Policy::Threading::Locking::Single,
		   typename Storage = BonnyCxx::Policy::Multimedia::Storage::OpenCVFileStorage > 
class OpenCVWebCam : public boost::noncopyable, public Locking, public Storage
{

	/*
	 * @ImageDeletor
	 *
	 * Custom delete class, because we are not the owner
	 * of the image data ( IplImage *p ). We do nothing.
	 * Otherwise we provoke a crash
	 */
	class ImageDeletor
	{
		public:
			void operator()(IplImage *p){}
	}; //end class ImageDeletor

	/*
	 * our friend 
	 */
	friend class ImageDeletor;

public:

	/*
	 * C'tor
	 */
	explicit OpenCVWebCam(){};

	/*
	 * D'tor
	 */
	virtual ~OpenCVWebCam(){};

	/*
	 * tpyedef the image tpye within a boost::shared_ptr
	 */
	typedef boost::shared_ptr<IplImage> ImageType;

	/*
	 * Start the first webcam in the system, if some found.
	 * If you have multiple webcams in your system, you can specify by number
	 * wich webcam you want to start. Default is -1, this means the first found.
	 *
	 * @param int webcam number, default first found in system
	 * @return bool true on success otherwise false
	 */
	bool Start( int camNum = -1 )
	{
		Lock();
		m_pCapture = cvCaptureFromCAM( camNum );
		UnLock();

		if( !m_pCapture )
		{
			return false;
		}

		return true;
	}

	/*
	 * Stop the camera from captureing, only if really started
	 */
	void Stop()
	{
		if( m_pCapture )
		{
			Lock();
				cvReleaseCapture( &m_pCapture );
				m_pCapture = NULL;
			UnLock();
		}	
	}

	/*
	 * Try to grab an image from the cam,
	 * if a empty pointer is returned, this means that the cam is busy, depending
	 * on your Locking policy. Or an error has occured
	 */
	ImageType GrabImage()
	{
		ImageType pImg;

		if( TryLock() == false )
		{
			return pImg;
		}

		pImg.reset( cvQueryFrame( m_pCapture ), OpenCVWebCam::ImageDeletor() );
		UnLock();

		return pImg;
	}

private:
	/*
	 * OpenCV capture handle
	 */
	CvCapture*  m_pCapture;

};// end class WebCam


	} //end namespace Multimedia
} //end namespace BonnyCxx

#endif //_BONNYCXX_OPENCV_SUPPORT_

#endif //_BONNYCXX_MULTIMEDIA_OPENCVWEBCAM_H_