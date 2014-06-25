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


	3:6:2009   18:44
*/

#ifndef _BONNYCXX_SYSTEM_DLL_H
#define _BONNYCXX_SYSTEM_DLL_H 1

#include <vector>

#include <boost/tuple/tuple.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/function.hpp>

namespace BonnyCxx{
	namespace System {

/**
*  @brief DllVersion
*
* Typedef a simple tuple to store the dll version information.
*
* 1: The major version of the DLL. If the DLL's version is 4.0.950, this value will be 4. 
* 2: The minor version of the DLL. If the DLL's version is 4.0.950, this value will be 0. 
* 3: The build number of the DLL. If the DLL's version is 4.0.950, this value will be 950. 
*/
typedef	boost::tuple< std::wstring,  // The major version of the DLL
					  std::wstring,  // The minor version of the DLL
					  std::wstring  // The build number of the DLL
								  > DllVersion;

/**
* @brief forward and typedefs
*/
class Dll;
typedef boost::shared_ptr<Dll> DllPtr;

/**
* @brief Dll
*
* Simple dll class wrapper, simple working with dll's ( e.g. load, execute methods ... )
*
* @code
* 
* using namespace BonnyCxx::System;
*
* //Create an interface pointer
* DllPtr pDllInstance = Dll::Create( L"shdocvw.dll" );
*
* //Load the library
* if( pDllInstance->Load() == false )
* {
*	return false;
* }
*
* //Get the dll version if available
* DllVersion version = pDllInstance->GetVersion();
*	
* std::wcout << L"Dll Major version: " << version.get<0>() << std::endl;
* std::wcout << L"Dll Minor version: " << version.get<1>() << std::endl;
* std::wcout << L"Dll Build version: " << version.get<2>() << std::endl;
*
*  // Or resolve directly the method by using GetFunction function like this
* DLLGETVERSIONPROC pFunc = pDllInstance->Resolve<DLLGETVERSIONPROC>( L"DllGetVersion" );
*
* if( pFunc )
* {
*	DLLVERSIONINFO dvi = {};
*	dvi.cbSize = sizeof(dvi);
*            
*	const HRESULT hr = (*pFunc)(&dvi);	
*
*	if( SUCCEEDED( hr ) )
*	{
*		std::wcout << L"Dll Major version: " << dvi.dwMajorVersion << std::endl;
*		std::wcout << L"Dll Minor version: " << dvi.dwMinorVersion << std::endl;
*		std::wcout << L"Dll Build version: " << dvi.dwBuildNumber  << std::endl;
*	}
* }
* //Unlaod the dll
*	if( pDllInstance->UnLoad() == false )
*	{
*		return false;
*	}
*
* @endcode
*/
class Dll : public boost::noncopyable
{
public:

	/**
	* D'Tor
	*/
	~Dll(){};

	/**
	* Try to load the library
	*
	* @return bool true on success otherwise false
	*/
	bool Load();

	/**
	* Unload the library
	*
	* @return bool on success otherwise false
	*/
	bool UnLoad();

	/**
	* Check if the given dll is loaded or not.
	*
	* @return bool true if the dll was successfully loaded, otherwise false
	*/
	const bool IsLoaded() const;

	/**
	* Get version information about the dll
	*
	* @return DllVersion
	*/
	const DllVersion GetVersion() const;

	/**
	* Setup a list of search directories. This should be a fallback solution if 
	* a Dll is not found in the PATH env.
	*
	* @param std::vector< std::wstring > list of directories
	*/
	void SetSearchPath( const std::vector< std::wstring > & list );

	/**
	* Resolve a dll function/method by given signature, 
	* Must use ugly void*, virtual template functions not possible ;)
	*/
	template< typename Func >
	Func Resolve( const std::wstring& signature ) const
	{
		std::string ascii( signature.length(), ' ');
		std::copy( signature.begin(), signature.end(), ascii.begin() );
		return reinterpret_cast<Func>( GetProcAddress( m_handle, ascii.c_str() ) );
	}

	/**
	* Inplace factory, create an instance of DllPtr @see DllPtr
	*
	* @param std::wstring dll name
	* @return DllPtr object
	*/
	static DllPtr Create( const std::wstring& dll );

private:

	/**
	* C'tor
	*
	* Construct our Dll object, and store the given dll name into 
	* a member variable m_dllName.
	*/
	explicit Dll( const std::wstring& dll ) 
		: m_dllName( dll ),
		m_handle( NULL )
	{
	}

	/**
	* hold the dll name, e.g. path
	*/
	std::wstring m_dllName;

	/**
	* Dll handle
	*/
	HMODULE m_handle;

	/**
	* Where to search the dll
	*/
	std::vector< std::wstring > m_searchPath;

}; //end class IDll

	} //end namespace System
} //end namespace BonnyCxx


#endif //_BONNYCXX_SYSTEM_DLL_H