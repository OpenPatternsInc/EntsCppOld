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

#include "EntsInterface.h"


EntsInterface::EntsInterface() {
    
}

EntsInterface::~EntsInterface() {
    
}



bool EntsInterface::saveTree(Tree* tree) {
    /*
    //Does the EntsFile have a file name?
    if (getEntsFile()->getFileName() != "") {
        //We have a filename already.
        getEntsFile()->save();
        return true;
    } else {
        bool hasName = false;
        //Give the user 3 chances to input a valid name.
        for (int count = 0; count < 3; count++) {
            if (queryFileName()) {
                hasName = true;
                break;
            }
        }
        if (!hasName) {
            cout << "File was not saved.\n";
            return false;
        }
        //OK, so we got a file name!
        getEntsFile()->save();
        return true;
    }
    */
    return false;
}

/**
 * Creates and returns a new Tree instance with the given name. We want to
 * encapsulate the creation of new Tree instances. Down the line we may want
 * to limit the number of Trees which can be instantiated at once.
 */
Tree* EntsInterface::generateNewTreeWithName(string name) {
    try {
        if (isValidTreeName(name))
            return new Tree(name);
    } catch (InvalidTreeNameException e) {
        //Include this re-throwing here to make it easier to spot.
        throw e;
    }
}


    
bool EntsInterface::isValidTreeName(const string name) {
    
    if (name.size() < 5) {
        throw InvalidTreeNameException("Name must be 5 or more characters.");
    } else {
        return true;
    }
    
    
    
}

/**
EntsFile* EntsInterface::getEntsFile() {
    return tree->getEntsFile();
}
 */