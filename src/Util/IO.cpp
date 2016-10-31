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

#include "IO.h"

using namespace std;

void IO::saveFile(string fileName, const string *dataStringPtr) {
        
        if (!dataStringPtr)
            cout << "ERROR: No data to be written.\n";
        
        //For now, writing files to an external USB drive. In case things go wrong.
        const string fileDirectory = "/home/jstockwell/DatabaseTestDrive/";

    //Put this stuff in a try/catch so we can use RAII.
    try {
        
        ofstream file(fileDirectory + fileName);
        if (!file.is_open()) {
            //cout << "Could not open file: \"" << fileName << "\".\n";
            throw std::runtime_error("Could not open file.");
        }
        file << *dataStringPtr;
        //Delete the string now.
        delete dataStringPtr;
        //Done saving here.
        cout << "File \"" << fileName << "\" has been saved.\n";

        file.close();
    
    } catch (std::runtime_error error) {
        cout << error.what() << endl;
        //If we're here, we probably didn't write the string to file, or delete it.
        delete dataStringPtr;
    }
}