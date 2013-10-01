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

#include <streambuf>
#include <cstdio>

#ifndef LOGSTREAMBUF_SIZE
#define LOGSTREAMBUF_SIZE 1024
#endif


namespace logstreamxx {

	/**
	*   @brief Log stream buffer class
	*
	*/
	class logstreambuf : public std::streambuf {
	public:

		/** end-of-file type */
		enum eof_t {
			eof = EOF       /*!< end of file */
		};

		logstreambuf();
		virtual ~logstreambuf();

	protected:
		virtual int flush();
		virtual bool wprefix();
		virtual int overflow( int c = traits_type::eof() );
		virtual int sync();

	private:

		/** log file descriptor */
		int _logfd;

		/** log entry/line continuation flag */
		bool _continue;

		/** size of the internal buffer */
		size_t _bufsize;

	};

} /* end of namespace logstreamxx */

#endif /* !LOGSTREAMXX_LOGSTREAMBUF_H */

