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


	14.10.2009 19:54
*/


#ifndef _BONNYCXX_POLICY_NETWORK_STARTUP_WSA_H_
#define _BONNYCXX_POLICY_NETWORK_STARTUP_WSA_H_ 1

namespace BonnyCxx{
	namespace Policy{
		namespace Network{
			namespace Startup{

/**
* @brief WindowsSocket
*
* Policy to initialize the windows socket environment and also cleanup at the end.
*
* @see COMEnv policy host
*/
struct WindowsSocket
{
	bool Init( WORD dVersion, LPWSADATA pWSAData = NULL )
	{	
		int code = 0;

		if( pWSAData == NULL )
		{
			WSADATA localWSA;
			code = WSAStartup( dVersion, &localWSA );
		}else{
			code = WSAStartup( dVersion, pWSAData );
		}

		 if( code != 0 )
		{
			return false;
		}

		return true;
	}

	void DeInit( )
	{
		WSACleanup();
	}

}; //end struct WindowsSocket

			} //end namespace Startup
		} //end namespace Network
	} //end namespace Policy
} //end namespace BonnyCxx


#endif //_BONNYCXX_POLICY_NETWORK_STARTUP_WSA_H_