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

#ifndef CLIEXCEPTIONS_H
#define CLIEXCEPTIONS_H

#include <string>

using namespace std;

/**
 * The base type of Exception for the Ents CLI. Perhaps unnecessary, but
 * aesthetically pleasing.
 */
class CLIException {
    
    friend class CLI;
    
protected:
    
    CLIException() {}
    
};

/**
 * A type of exception which holds a message.
 */
class CLIMessageException: public CLIException {
    
    friend class CLI;
    
    string message;
    
    CLIMessageException(string m): message(m) {}
    
    
    
    
    
};

/**
 * Exception called for when an input is empty. Should be from when the user
 * simply presses enter/return without typing anything.
 */
class NoInputException: public CLIException {
    
    friend class CLI;
    
public:
    
    NoInputException() {}
    
    
};



#endif /* CLIEXCEPTIONS_H */

