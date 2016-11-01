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

#ifndef ENTSFILE_H
#define ENTSFILE_H

#include <string>
#include "../Core/Tree.h"
 
/**
 * Holds all we need for an Ents file, including the file name, the
 * Tree instance it represents, and other various options.
 */
class EntsFile {
    
    /**
     * The directory where this hierarchy is located.
     */
    string directory;
    /**
     * The name of this hierarchy's file.
     */
    string fileName;
    /**
     * The tree which is being saved and loaded.
     */
    Tree *tree;
    /**
     * Files will be .ents files.
     */
    const static string FILE_POSTFIX;
    
    const string* generateSaveData();
    
    
public:
    
    EntsFile(Tree *tr);
    
    void save();
    
    void setFileName(string newName) {
        fileName = newName;
    }
    
    const string getFileName() {
        return fileName;
    }
    
    Tree* getTree() {
        return tree;
    } 
    
    static const string getPostfix() {
        return FILE_POSTFIX;
    }
    
    


};

#endif /* ENTSFILE_H */

