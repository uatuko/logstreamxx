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

#include "logstream.h"

#include <fcntl.h>
#include <unistd.h>


namespace logstreamxx {

	logstream::logstream() throw() : std::ostream( 0 ), _fd( -1 ) {

		// log stream buffer instance
		logstreambuf * sb = new logstreambuf();

		// update output buffer
		rdbuf( sb );

	}


	logstream::logstream( const char * filename, bool append, mode_t mode ) throw( logexception ) :
			std::ostream ( 0 ), _fd( -1 ) {

		// set file open flags
		int flags = O_WRONLY | O_CREAT | O_APPEND;

		// truncate file?
		if (! append ) {
			flags |= O_TRUNC;
		}

		// open file
		_fd = ::open( filename, flags, mode );

		// check - was the open file successful?
		if ( _fd == -1 ) {
			// throw a log exception with system message
			throw logexception();
		}

		// log stream buffer instance
		logstreambuf * sb = new logstreambuf( _fd );

		// update output buffer
		rdbuf( sb );

	}


	logstream::~logstream() throw() {

		// close any open files
		if ( _fd != 0 ) {
			::close( _fd );
		}

		// cleanup
		delete rdbuf();

	}


	std::ostream &logstream::operator <<( const priority::log_priority_t &p ) throw() {

		// log stream buffer
		logstreambuf * sb = (logstreambuf *) rdbuf();

		// set priority for the log stream buffer
		sb->lpriority( p );

		return *this;

	}


	int logstream::loglevel( const priority::log_priority_t &level ) throw() {

		// create bit mask
		int mask = 1 << level;
		mask = ( mask - 1 ) | mask;

		// log stream buffer
		logstreambuf * sb = (logstreambuf *) rdbuf();

		// set mask
		sb->setlogmask( mask );

		return mask;

	}


	void logstream::logprefix( const std::string &p ) throw() {

		// log stream buffer
		logstreambuf * sb = (logstreambuf *) rdbuf();

		sb->lprefix( p );

	}

} /* end of namespace logstreamxx */

