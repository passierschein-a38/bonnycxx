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


	3:6:2009   19:04
*/

#include <windows.h>
#include <shlwapi.h>

#include <boost/lexical_cast.hpp>
#include "system/dll.h"

namespace BonnyCxx {
	namespace System {

bool Dll::Load()
{	
	m_handle = LoadLibrary( m_dllName.c_str() );

	//if found, return 
	if( m_handle != NULL )
	{
		return true;
	}

	//try in directories if given
	for( int idx=0; idx < m_searchPath.size(); ++idx )
	{
		std::wstring dll = m_searchPath.at( idx );
		dll.append( m_dllName );

		m_handle =  LoadLibrary( dll.c_str() );

		//if found, return 
		if( m_handle != NULL )
		{
			return true;
		}
	}

	return false;
}


bool Dll::UnLoad()
{
	//check if it is loaded
	if( false == IsLoaded() )
	{
		return false;
	}

	if( FreeLibrary( m_handle ) == NULL )
	{
		return false;
	}

	m_handle = NULL;

	return true;
}

const bool Dll::IsLoaded() const
{
	if( NULL != m_handle )
	{
		return true;
	}

	return false;
}

void Dll::SetSearchPath( const std::vector< std::wstring > & list )
{
	m_searchPath = list;
}

const DllVersion Dll::GetVersion() const
{
	DLLGETVERSIONPROC pDllGetVersion = Resolve<DLLGETVERSIONPROC>( L"DllGetVersion" );

	if( pDllGetVersion == NULL )
	{
		return DllVersion( L"", L"", L"" );
	}

	DLLVERSIONINFO dvi = {};
	dvi.cbSize = sizeof(dvi);
            
	//execute functor
    const HRESULT hr = (*pDllGetVersion)(&dvi);

	if( SUCCEEDED( hr ) )
	{
		std::wstring major = L"";
		std::wstring minor = L"";
		std::wstring build = L"";

		try{
			major = boost::lexical_cast<std::wstring>( dvi.dwMajorVersion );
			minor = boost::lexical_cast<std::wstring>( dvi.dwMinorVersion );
			build = boost::lexical_cast<std::wstring>( dvi.dwBuildNumber );
		}catch( boost::bad_lexical_cast )
		{
			//something went wrong
		}

		return DllVersion( major, minor, build );

	}

	return DllVersion( L"", L"", L"" );
}


DllPtr Dll::Create( const std::wstring& dll )
{
	DllPtr ptr;
	ptr.reset( new Dll( dll ) );
	return ptr;
}

	} //end namespace System
} //end namespace BonnyCxx