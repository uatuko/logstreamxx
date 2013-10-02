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


namespace logstreamxx {

	logstream::logstream() : std::ostream( 0 ) {

		// log stream buffer instance
		logstreambuf * sb = new logstreambuf();

		// update output buffer
		rdbuf( sb );

	}


	logstream::~logstream() {

		// cleanup
		delete rdbuf();

	}


	std::ostream &logstream::operator <<( const priority::log_priority_t &p ) {

		// log stream buffer
		logstreambuf * sb = (logstreambuf *) rdbuf();

		// set priority for the log stream buffer
		sb->lpriority( p );

		return *this;

	}

} /* end of namespace logstreamxx */

