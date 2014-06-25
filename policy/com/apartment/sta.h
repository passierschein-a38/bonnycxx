/*
 Bonny C++ Library - libbonny

 Axel Sauerhoefer
 Jockgrimerstr. 13
 76764 Rheinzabern

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


	8:6:2009   22:08
*/

#ifdef _BONNYCXX_COM_SUPPORT_

#ifndef _BONNYCXX_POLICY_COM_APARTMENT_STA_H_
#define _BONNYCXX_POLICY_COM_APARTMENT_STA_H_ 1

namespace BonnyCxx{
	namespace Policy{
		namespace COM{
			namespace Apartment{

/**
* @brief SingleThreaded
*
* Single threaded com apartment policy.
*
* @see COMEnv policy host
*/
struct SingleThreaded
{
	void Init( HRESULT& hr )
	{
		hr = CoInitializeEx( NULL, COINIT_APARTMENTTHREADED );
	}

	void DeInit( const HRESULT& hr )
	{
		if( SUCCEEDED( hr ) )
		{
			CoUninitialize();
		}
	}
}; //end struct SingleThreaded

			} //end namespace Apartment
		} // end namespace COM
	} //end namespace Policy
} //end namespace  BonnyCxx


#endif //_BONNYCXX_POLICY_COM_APARTMENT_STA_H_

#endif //_BONNYCXX_COM_SUPPORT_