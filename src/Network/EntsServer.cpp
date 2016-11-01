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

#include "EntsServer.h"


using boost::asio::ip::tcp;


EntsServer::EntsServer() {
    
    int tcpPort = 13;
    
    
    try {
        
        boost::asio::io_service io_service;
        
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), tcpPort));
        
        for (;;) {
            
            tcp::socket socket(io_service);
            
            std::cout << "Waiting for client to connect...\n";
            
            acceptor.accept(socket);
            
            std::cout << "Server socket initiated!\n";
            
        }
        
    }catch (std::exception& e) {
        
        std::cerr << e.what() << std::endl;
        
    }
    
    
    
}