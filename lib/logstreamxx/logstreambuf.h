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
#include <logstreamxx/logexception.h>

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
		logstreambuf() throw();

		/**
		*   @brief overloaded constructor
		*   @param output_fd log output file descriptor
		*
		*   Initialise a log stream buffer with @c output_fd as the log
		*   output destination.
		*
		*/
		logstreambuf( int output_fd ) throw( logexception );

		/**
		*   @brief destructor
		*
		*   Deallocate output buffer space.
		*
		*/
		virtual ~logstreambuf() throw();

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
		priority::log_priority_t lpriority( const priority::log_priority_t &p ) throw();

		/**
		*   @brief set log priority mask
		*   @param mask log priority mask
		*   @return previous log priority mask
		*
		*   This method sets the log-mask for the log stream buffer
		*   instance and returns the previous log-mask. If the @c mask
		*   is 0 then the current log-mask is not modified.
		*
		*   Once a log-mask is set only the priorities that have the
		*   corresponding bit set will be enabled for logging.
		*
		*   @note The log-mask defaults to 1 (log only priority::emerg)
		*         on initialisation.
		*
		*/
		int setlogmask( int mask ) throw();

		/**
		*   @brief set an additional prefix for the log lines
		*   @param prefix log prefix
		*   @return previous log prefix
		*
		*   Set an additional log prefix that will be added to each log
		*   line written out. This can be helpful to distinguish logs from
		*   different processes if they are logged to the same destination.
		*
		*/
		std::string lprefix( const std::string &prefix ) throw();


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
		virtual int flush() throw();

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
		virtual bool wlprefix() throw();

		/**
		*   @brief consume the buffer
		*   @param c additional character to consume
		*   @return logstreambuf::eof on failure or @a c on success
		*
		*   Consumes the buffer content by writing out to the destination.
		*   if @a c is not logstreambuf::eof then @a c is also consumed.
		*
		*   @note If the buffer overflows then the written out log lines
		*         could be out of order on a multi-process environment.
		*
		*/
		virtual int overflow( int c = eof ) throw();

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
		virtual int sync() throw();

		/**
		*   @brief get the log timestamp value
		*   @return log timestamp
		*
		*   This is a helper method to return the current log timestamp
		*   value as a std::string object.
		*
		*/
		const std::string lstamp() const throw();

		/**
		*   @brief set buffer space
		*   @param s pointer to a allocated buffer space
		*   @param n allocated buffer size
		*   @return @c this
		*
		*   Set the array of @c n characters pointed by @c s as the internal
		*   character sequence to be used by the log stream buffer object.
		*   If @c s is 0 or @n is less than 2, this method has no effect.
		*
		*   @note The buffer space pointed by @c s will be deallocated
		*         by the destructor and any successive calls to this method.
		*
		*/
		virtual logstreambuf * setbuf( char * s, std::streamsize n ) throw();


	private:

		/** log file descriptor */
		int _logfd;

		/** log entry/line continuation flag */
		bool _continue;

		/** log priority */
		priority::log_priority_t _priority;

		/** log priority mask */
		int _mask;

		/** additional log prefix to add to the log lines */
		std::string _prefix;

		/** initialise buffer space */
		void init_buf() throw();

	};

} /* end of namespace logstreamxx */

#endif /* !LOGSTREAMXX_LOGSTREAMBUF_H */

