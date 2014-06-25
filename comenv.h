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


	8:6:2009   21:59
*/

#ifdef _BONNYCXX_COM_SUPPORT_

#ifndef _BONNYCXX_COM_ENV_H_
#define _BONNYCXX_COM_ENV_H_ 1


#include <boost/noncopyable.hpp>

#include "policy/com/apartment/sta.h"
#include "policy/com/apartment/mta.h"

namespace BonnyCxx{
	namespace COM{

template< typename ApartmentModel >
class COMEnv : public ApartmentModel,
			   public boost::noncopyable
{
public:

	/**
	* C'Tor
	*
	* Call the policy init method with the hresult to store
	* if the init was successfully or not. Only if the m_hresult
	* has SUCCEEDED the DeInit is called in the D'tor
	*/
	explicit COMEnv( void ) :
		m_hresult( E_FAIL )
	{
		ApartmentModel::Init( m_hresult );
	}

	/**
	* D'Tor
	*
	* Call the DeInit method if the Init was successfully.
	*/
	 ~COMEnv()
	 {
		 if( SUCCEEDED( m_hresult ) )
		 {
			 ApartmentModel::DeInit( m_hresult );
		 }
	 }
		
private:

	/**
	* store the hresult from coinitialize
	*/
	HRESULT m_hresult;

}; //end class COMEnv

/**
* tpyedef the single threaded apartment class
*/
typedef COMEnv< BonnyCxx::Policy::COM::Apartment::SingleThreaded > COMStaEnv;

/**
* tpyedef the multi threaded apartment class
*/
typedef COMEnv< BonnyCxx::Policy::COM::Apartment::MultiThreaded > COMMtaEnv;

	}//end namespace COM
} //end namespace BonnyCxx


#endif //_BONNYCXX_COM_ENV_H_

#endif //_BONNYCXX_COM_SUPPORT_