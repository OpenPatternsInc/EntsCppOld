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

#ifndef IO_H
#define IO_H

#include <string>
#include "../Tree.h"

class IO {
    
    /**
     * The directory the user is currently using to load and save files.
     */
    string fileDirectory;
    /**
     * Files will be .ents files.
     */
    const string FILE_POSTFIX = "ents";
    
    /**
     * Holds all we need for an Ents file, including the file name, the
     * Tree instance it represents, and other various options.
     */
    class EntsFile {
        
        string fileName;
        
        Tree *tree;
        
        
        
    };
    
    
    
    
    
};





#endif /* IO_H */

