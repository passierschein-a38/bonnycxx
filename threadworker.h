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


	20:10:2008   20:09
*/

#ifndef _BONNYCXX_THREADWORKER_H_
#define _BONNYCXX_THREADWORKER_H_ 1

#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

namespace BonnyCxx{

/*
 * @brief ThreadWorker
 *
 * Template based class thread worker class. For moving blocking operations into a seperate
 * thread. The moved object must implement the following methods to be used with this template
 * 
 *  void StartThreadWork();
 *  void StopThreadWork();
 *  bool IsRunning();
 *
 * Howto use:
 *
 * @code
 *
 * boost::shared_ptr<CThreadAble> pMyObject;
 * pMyObject.reset( new CThreadAble() );
 *
 * ThreadWorker<CThreadAble> wrapper( pMyObject );
 * wrapper.Start();
 * ....
 * wrapper.Stop();
 *
 * @endcode
 *
 * CThreadAble is our class to work in a seperate thread.
 */
template<typename T>
class ThreadWorker : public boost::noncopyable
{
public:

	/*
	 * C'tor
	 *
	 * @param a const shared pointer to the wrapped object
	 */
	explicit ThreadWorker( const boost::shared_ptr<T>& obj )
	{
		m_pWrappedObject = obj;
	}

	/*
	 * D'tor
	 */
	virtual ~ThreadWorker()
	{
		CleanShutdown();
	}

	/*
	 * Get a reference to the wrapped object
	 *
	 * @return T
	 */
	boost::shared_ptr<T> &Get()
	{
		return m_pWrappedObject;
	}

	/*
	 * Start the thread worker, e.g. create a new thread and 
	 * start the work. 
	 */
	void Start()
	{
		m_pWorkerThread.reset( new boost::thread( boost::bind( &ThreadWorker::Callback, this ) ) );
	}

	/*
	 * Stop the threadworker
	 */
	void Stop()
	{
		CleanShutdown();
	}

	/*
	 * Check if the thread is running.
	 *
	 * @return bool return true if the wrapped object is still working, otherwise false
	 */
	bool IsRunning()
	{
		if( m_pWrappedObject )
		{
			return m_pWrappedObject->IsRunning();
		}
		
		return false;
	}

	/*
	 * Static Callback method, is called from the boost library
	 * after thread creating.
	 *
	 * @param ThreadWrapper<T>* a pointer to our self
	 */
	static void Callback( ThreadWorker<T>* ptr )
	{
		ThreadWorker<T>* obj = dynamic_cast<ThreadWorker<T>*>(ptr);

		if( obj )
		{
			obj->Get()->StartThreadWork();
		}
	}

private:

	/*
	 * Clean shutdown
	 *
	 * At first call the wrapped object to stop the work,
	 * after this wait until the thread is finished, than delete the
	 * thread object.
	 */
	void CleanShutdown()
	{
		if( m_pWrappedObject )
		{
			m_pWrappedObject->StopThreadWork();
		}

		if( m_pWorkerThread )
		{
			m_pWorkerThread->join();
			m_pWorkerThread.reset();
		}
	}

	/* 
	 * C'tor
	 *
	 * This should never be called so make it private
	 */
	ThreadWorker()
	{

	}

	/* 
	 * A shared pointer to the wrapped object
	 */
	boost::shared_ptr<T> m_pWrappedObject;

	/* 
	 * The interal boost::thread object
	 */
	boost::shared_ptr<boost::thread> m_pWorkerThread;

};//end class ThreadWrapper



}//end namespace BonnyCxx


#endif //_BONNYCXX_THREADWORKER_H_