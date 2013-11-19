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
#include <sys/stat.h>


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
		logstream() throw();

		/**
		*   @brief overloaded constructor
		*   @param filename log destination filename
		*   @param append boolean flag to indicate whether to append to
		*                 the log file or truncate the file if already
		*                 exists
		*
		*   @param mode file mode to open the log file with
		*
		*   Initialise a log output stream with @c filename as the output
		*   destination. Destination file will be created if it doesn't exist.
		*
		*/
		logstream( const char * filename, bool append = true, mode_t mode = 00644 ) throw( logexception );

		/**
		*   @brief destructor
		*
		*   Deallocate associated buffers.
		*
		*/
		virtual ~logstream() throw();

		/**
		*   @brief overloaded output stream operator for log priorities
		*/
		std::ostream &operator <<( const priority::log_priority_t &p ) throw();

		/**
		*   @brief set log output level
		*   @param level log output level
		*   @return log priority bit mask
		*
		*   This enables logging up to @c level by setting the log
		*   priority bit mask at the log stream buffer and returns the
		*   log-mask set.
		*
		*/
		int loglevel( const priority::log_priority_t &level ) throw();

		/**
		*   @brief set an extra prefix for the log lines
		*   @param p prefix
		*
		*   This sets (or clears) an extra prefix to be added to the
		*   log lines written out. This can be helpful to distinguish
		*   logs from different processes if they are logged to the same
		*   destination.
		*
		*/
		void logprefix( const std::string &p ) throw();


	private:

		/** file descriptor */
		int _fd;

	};

} /* end of namespace logstreamxx */

#endif /* !LOGSTREAMXX_LOGSTREAM_H */

