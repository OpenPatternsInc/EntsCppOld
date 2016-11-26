/*
 * This file is part of the Ents Hierarchy Database Project.
 * Copyright (C) 2016 OpenPatterns Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef SOCKETCLIENT_H
#define SOCKETCLIENT_H

#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>



void send_something(std::string host, int port, std::string message)
{
	boost::asio::io_service ios;
			
        boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);

        boost::asio::ip::tcp::socket socket(ios);

	socket.connect(endpoint);

	boost::array<char, 128> buf;
        std::copy(message.begin(),message.end(),buf.begin());
	boost::system::error_code error;
	socket.write_some(boost::asio::buffer(buf, message.size()), error);
        socket.close();
}




#endif /* SOCKETCLIENT_H */

