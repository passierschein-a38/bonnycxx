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


	6:12:2008   14:41
*/

#ifndef _BONNYCXX_POLICY_THREADING_LOCKING_SINGLE_H_
#define _BONNYCXX_POLICY_THREADING_LOCKING_SINGLE_H_

namespace BonnyCxx{
	namespace Policy {
		namespace Threading {
			namespace Locking {

/*
 * @Single
 *
 * Threading locking policy, which represents single threaded application
 */
struct Single
{

	/*
	 * Lock the current thread, nothing todo
	 * we are single threaded 
	 */
	void Lock()
	{

	}

	/*
	* UnLock the current thread, nothing todo
	* we are single threaded 
	*/
	void UnLock()
	{

	}

	/*
	* TryLock the current thread, return every time true
	* we are single threaded 
	*/
	bool TryLock()
	{
		return true;
	}

}; //end struct Single


			} //end namespace Locking
		} //end namespace Threading
	} //end namespace Policy
}//end namespace BonnyCxx


#endif //_BONNYCXX_POLICY_THREADING_LOCKING_SINGLE_H_