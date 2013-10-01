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

#ifndef LOGSTREAMXX_LOGSTREAM_H
#define LOGSTREAMXX_LOGSTREAM_H

#include <logstreamxx/logstreambuf.h>

#include <ostream>


namespace logstreamxx {

	/**
	*   @brief Log stream controller class
	*
	*   This is the log stream output controller class.
	*
	*/
	class logstream : public std::ostream {
	public:

		/**
		*   @brief constructor
		*
		*   Initialise a log output stream with standard output ( @c STDOUT )
		*   as the destination.
		*
		*/
		logstream();

		/**
		*   @brief destructor
		*
		*   Deallocate associated buffers.
		*
		*/
		virtual ~logstream();

	};

} /* end of namespace logstreamxx */

#endif /* !LOGSTREAMXX_LOGSTREAM_H */

