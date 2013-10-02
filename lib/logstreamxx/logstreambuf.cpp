/*
*  logstreamxx - C++ logging library based on standard stream classes
*  Copyright (C) 2013 Uditha Atukorala
*
*  This software library is free software; you can redistribute it and/or modify
*  it under the terms of the GNU Lesser General Public License as published by
*  the Free Software Foundation; either version 3 of the License, or
*  (at your option) any later version.
*
*  This software library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public License
*  along with this software library. If not, see <http://www.gnu.org/licenses/>.
*
*/

#include "logstreambuf.h"

#include <unistd.h>
#include <sstream>
#include <ctime>
#include <sys/time.h>


namespace logstreamxx {

	logstreambuf::logstreambuf() :
			_logfd( STDOUT_FILENO ), _bufsize( LOGSTREAMBUF_SIZE ),
			_continue( false ), _priority( priority::debug ) {

		// allocate output buffer space
		char * pbuf = new char[_bufsize];

		// setup output buffer
		setp( pbuf, pbuf + ( _bufsize - 1 ) );

	}


	logstreambuf::~logstreambuf() {

		// sync
		sync();

		// cleanup output buffer
		delete [] pbase();

	}


	const std::string logstreambuf::lstamp() const throw() {

		timeval tv;
		tm * ti;

		// current timestamp
		gettimeofday( &tv, NULL );
		ti = localtime( &tv.tv_sec );

		// format
		char buffer[23];
		int n = strftime( buffer, 16, "%b %e %T", ti );

		// append milliseconds
		sprintf( ( buffer + n ), ".%ld", (long int) tv.tv_usec );

		return buffer;

	}


	int logstreambuf::flush() {

		int flush_size = pptr() - pbase();

		// sanity check - is there anything to flush?
		if ( flush_size > 0 ) {

			// write prefix
			if ( wprefix() ) {

				//  write buffer content
				if ( write( _logfd, pbase(), flush_size ) == flush_size ) {

					// update buffer pointers
					pbump( -flush_size );

					return flush_size;

				}

			}

		}

		return eof;

	}


	bool logstreambuf::wprefix() {

		// check - do we need to write the prefix
		if (! _continue ) {

			// populate prefix
			std::stringstream ss;
			ss  << lstamp() << " [" << priority::text( _priority ) << "] ";

			// write prefix
			if ( write( _logfd, ss.str().c_str(), ss.str().length() ) != ss.str().length() ) {
				return false;
			}

		}

		// update continuation flag
		_continue = true;

		return true;

	}


	int logstreambuf::overflow( int c ) {

		if ( c != eof ) {

			// insert the overflowed char into the buffer
			*pptr() = c;
			pbump( 1 );

		}

		// flush buffer content
		if ( flush() == eof ) {
			return eof;
		}

		return c;

	}


	int logstreambuf::sync() {

		// flush buffer
		if ( flush() == eof ) {
			return eof;
		}

		// update continuation flag
		_continue = false;

		return 0;

	}


	priority::log_priority_t logstreambuf::lpriority( const priority::log_priority_t &p ) {

		// backup the current priority
		priority::log_priority_t prev_priority = _priority;

		// update
		_priority = p;

		return prev_priority;

	}

} /* end of namespace logstreamxx */

