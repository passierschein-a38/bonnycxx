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

18:10:2008   22:51
*/

#ifndef _BONNYCXX_BONNY_H_
#define _BONNYCXX_BONNY_H_ 1

#include <winsock2.h>
#include <windows.h>
#include <shlwapi.h>

/*
 * Global configurations, setup here all defines
 * before including header files
 */

/*
 * do we have opencv ?!? if yes, we can use the
 * webcam stuff from opencv
 */
#define _BONNYCXX_OPENCV_SUPPORT_ 1

/*
 * define if we should complie the windows 
 * component object model stuff ( COM )
 */
#define _BONNYCXX_COM_SUPPORT_ 1

#include "multimedia/opencvwebcam.h"
#include "ostreamout.h"
#include "threadworker.h"
#include "system/dll.h"
#include "comenv.h"
#include "system/cpla.h"
#include "wsaenv.h"

#include "library.h"

/*
* Include all headers available
*/
namespace BonnyCxx{

/*
 * Library version
 */
static const double Version = 0.1;

}//end namespace BonnyCxx


#endif //_BONNYCXX_BONNY_H_