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

/* 
 * This file contains various exceptions in order to inform the user when
 * they don't follow the rules. Rules are important when dealing with logic!
 */

#ifndef INTERFACEEXCEPTIONS_H
#define INTERFACEEXCEPTIONS_H

#include <string>

using namespace std;

/**
 * The base exception in Ents.
 */
class EntsInterfaceException {
    
    friend class EntsInterface;
    
    /**
     * Private no-arg constructor so no other class can create one.
     */
    
public:
    
    EntsInterfaceException() {}
    
};

/**
 * An abstract type of exception which displays information to the user about
 * what they did wrong.
 */
class EntsInterfaceMessageException: public EntsInterfaceException {
    
    friend class EntsInterface;
    
    string message;
    
    //Important to have public access to certain exceptions in case they get
    //passed to derived classes.
public:
    
    EntsInterfaceMessageException(string m): message(m) {
        
    }
    
    string getMessage() {
        return message;
    }
    
    
};

/**
 * Thrown when a name provided by the user is not valid for a Tree.
 */
class InvalidTreeNameException: public EntsInterfaceMessageException {
    
    friend class EntsInterface;
    
    InvalidTreeNameException(string reason): EntsInterfaceMessageException(reason) { }
    
    
    
};


#endif /* INTERFACEEXCEPTIONS_H */

