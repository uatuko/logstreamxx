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


namespace logstreamxx {

	logstreambuf::logstreambuf() : _fd( STDOUT_FILENO ) {

	}

	int logstreambuf::overflow( int c ) {

		if ( write( _fd, &c, 1 ) != 1 ) {
			return traits_type::eof();
		}

		return c;

	}

} /* end of namespace logstreamxx */

