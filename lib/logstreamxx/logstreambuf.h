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

#ifndef LOGSTREAMXX_LOGSTREAMBUF_H
#define LOGSTREAMXX_LOGSTREAMBUF_H

#include <logstreamxx/priority.h>

#include <streambuf>
#include <cstdio>
#include <string>

#ifndef LOGSTREAMBUF_SIZE
#define LOGSTREAMBUF_SIZE 1024
#endif


namespace logstreamxx {

	/**
	*   @brief Log stream buffer class
	*
	*   Stream buffer class with only an output sequence and the output
	*   sequence will be associated with a file destination.
	*
	*/
	class logstreambuf : public std::streambuf {
	public:

		/** end-of-file type */
		enum eof_t {
			eof = EOF       /*!< end of file */
		};

		/**
		*   @brief constructor
		*
		*   Initialise a log stream buffer with standard output ( @c STDOUT )
		*   as the log output destination.
		*
		*/
		logstreambuf();

		/**
		*   @brief destructor
		*
		*   Deallocate output buffer space.
		*
		*/
		virtual ~logstreambuf();

		/**
		*   @brief change the log priority
		*   @param p log priority
		*   @return previous log priority
		*
		*   Change the log priority for this buffer instance.
		*
		*   @note Log priority defaults to priority::debug on initialisation.
		*
		*/
		priority::log_priority_t lpriority( const priority::log_priority_t &p );


	protected:

		/**
		*   @brief flush the log buffer to the destination
		*   @return number of characters flushed or logstreambuf::eof
		*           to indicate failure
		*
		*   Flush the log stream buffer by writing the content to the
		*   associated destination.
		*
		*/
		virtual int flush();

		/**
		*   @brief write the log line prefix to destination
		*   @return boolean @c true or @c false to indicate success or
		*           failure
		*
		*   Write the log line prefix to the associated destination only
		*   if needed. i.e. continuation flag is not set.
		*
		*   @note This will set the continuation flag after writing the
		*   prefix.
		*
		*/
		virtual bool wprefix();

		/**
		*   @brief consume the buffer
		*   @param c additional character to consume
		*   @return logstreambuf::eof on failure or @a c on success
		*
		*   Consumes the buffer content by writing out to the destination.
		*   if @a c is not logstreambuf::eof then @a c is also consumed.
		*
		*   @note If the buffer overflow then the written out log lines
		*         could be out of order on a multi-threaded environment.
		*
		*/
		virtual int overflow( int c = eof );

		/**
		*   @brief sync data with the destination
		*   @return 0 on success or logstreambuf::eof on failure
		*
		*   Synchronise the buffer content with the destination by flushing
		*   the content using flush().
		*
		*   @note This will clear the continuation flag on success
		*
		*/
		virtual int sync();

		/**
		*   @brief get the log timestamp value
		*   @return log timestamp
		*
		*   This is a helper method to return the current log timestamp
		*   value as a std::string object.
		*
		*/
		const std::string lstamp() const throw();

	private:

		/** log file descriptor */
		int _logfd;

		/** log entry/line continuation flag */
		bool _continue;

		/** size of the internal buffer */
		size_t _bufsize;

		/** log priority */
		priority::log_priority_t _priority;

	};

} /* end of namespace logstreamxx */

#endif /* !LOGSTREAMXX_LOGSTREAMBUF_H */

