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

	logstreambuf::logstreambuf() throw() :
			_logfd( STDOUT_FILENO ), _continue( false ),
			_priority( priority::debug ), _mask( 1 ) {

		// initialise buffer space
		init_buf();

	}


	logstreambuf::logstreambuf( int output_fd ) throw( logexception ) :
			_logfd( output_fd ), _continue( false ),
			_priority( priority::debug ), _mask( 1 ) {

		// sanity check
		if ( _logfd < 0 ) {
			throw logexception( "Invalid file descriptor" );
		}

		// initialise buffer space
		init_buf();

	}


	logstreambuf::~logstreambuf() throw() {

		// sync
		sync();

		// cleanup output buffer
		delete [] pbase();

	}


	void logstreambuf::init_buf() throw() {

		// allocate output buffer space
		char * pbuf = new char[LOGSTREAMBUF_SIZE];

		// setup output buffer
		setp( pbuf, pbuf + ( LOGSTREAMBUF_SIZE - 1 ) );

	}


	const std::string logstreambuf::lstamp() const throw() {

		timeval tv;
		tm * ti;

		// current timestamp
		gettimeofday( &tv, 0 );
		ti = localtime( &tv.tv_sec );

		// format
		char buffer[23];
		int n = strftime( buffer, 16, "%b %e %T", ti );

		// append milliseconds
		sprintf( ( buffer + n ), ".%ld", (long int) tv.tv_usec );

		return buffer;

	}


	int logstreambuf::flush() throw() {

		int flush_size = pptr() - pbase();

		// sanity check - is there anything to flush?
		if ( flush_size > 0 ) {

			// check - logging enabled for the current priority?
			if ( ( ( 1 << _priority ) & ( _mask ) ) == 0 ) {

				// not enabled, update buffer pointers
				pbump( -flush_size );

				return flush_size;

			}

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


	bool logstreambuf::wprefix() throw() {

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


	int logstreambuf::overflow( int c ) throw() {

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


	int logstreambuf::sync() throw() {

		// flush buffer
		if ( flush() == eof ) {
			return eof;
		}

		// update continuation flag
		_continue = false;

		return 0;

	}


	logstreambuf * logstreambuf::setbuf( char * s, std::streamsize n ) throw() {

		// sanity check
		if ( ( s != 0 ) && ( n > 1 ) ) {

			// cleanup existing output buffer
			delete [] pbase();

			// setup new output buffer
			setp( s, s + ( n - 1 ) );

		}

		return this;

	}


	priority::log_priority_t logstreambuf::lpriority( const priority::log_priority_t &p ) throw() {

		// backup the current priority
		priority::log_priority_t prev_priority = _priority;

		// sync existing buffer content
		sync();

		// update
		_priority = p;

		return prev_priority;

	}


	int logstreambuf::setlogmask( int mask ) throw() {

		// backup the current mask
		int prev_mask = _mask;

		// sanity check
		if ( mask != 0 ) {

			// update
			_mask = mask;

		}

		return prev_mask;

	}

} /* end of namespace logstreamxx */

