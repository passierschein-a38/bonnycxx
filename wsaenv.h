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


	14.10.2009 20:05
*/

#ifndef _BONNYCXX_WSA_ENV_H_
#define _BONNYCXX_WSA_ENV_H_ 1

#include <boost/noncopyable.hpp>
#include "policy/network/startup/wsa.h"

namespace BonnyCxx{
	namespace Network{

template< typename Startup >
class WSAEnv : public Startup,
			   private boost::noncopyable
{
public:

	/**
	* C'Tor
	*
	* Call the policy init method with the hresult to store
	* if the init was successfully or not. Only if the m_hresult
	* has SUCCEEDED the DeInit is called in the D'tor
	*/
	explicit WSAEnv( bool& bSuccess,const WORD dVersion, LPWSADATA pWSAData = 0 ) 
	{
		bSuccess = Startup::Init( dVersion, pWSAData );
	}

	/**
	* D'Tor
	*
	* Call the DeInit method if the Init was successfully.
	*/
	 ~WSAEnv()
	 {
		 Startup::DeInit();
	 }

}; //end class WSAEnv



/**
* tpyedef the single threaded apartment class
*/
typedef WSAEnv< BonnyCxx::Policy::Network::Startup::WindowsSocket > WSAInit;

	}//end namespace Network
} //end namespace BonnyCxx


#endif //_BONNYCXX_WSA_ENV_H_