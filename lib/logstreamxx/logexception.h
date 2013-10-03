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

#ifndef LOGSTREAMXX_LOGEXCEPTION_H
#define LOGSTREAMXX_LOGEXCEPTION_H

#include <exception>
#include <cstddef>
#include <string>


namespace logstreamxx {

	/**
	*   @brief Log exception
	*
	*   This is the base class for all the exceptions used within
	*   @c logstreamxx namespace.
	*
	*/
	class logexception : public std::exception {
	public:

		/**
		*   @brief constructor
		*
		*   Create an instance with the passed in error message.
		*   If a message is not passed in or is equal to NULL then
		*   the system error message is used.
		*
		*   @param message (optional) user error message
		*/
		logexception( const char * message = NULL ) throw();

		virtual ~logexception() throw();   //!< destructor

		/**
		*   @brief Returns exception message
		*
		*   Returns a C-Style character string describing the
		*   exception.
		*
		*   @return exception message
		*   @sa logexception() constructor
		*/
		const char * what() const throw();

	protected:

		/** user exception message */
		std::string _message;

		/** system error number */
		int _errno;

		/** system error message */
		std::string _sys_msg;

	};

} /* end of namespace logstreamxx */

#endif /* !LOGSTREAMXX_LOGEXCEPTION_H */

