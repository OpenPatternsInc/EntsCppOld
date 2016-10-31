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

void IO::saveFile(string fileName, string data) {
    
    //Put this stuff in a try/catch so we can use RAII.
    try {
    
        //For now, writing files to an external USB drive. In case things go wrong.
        const string fileDirectory = "/home/jstockwell/DatabaseTestDrive/";

        ofstream file(fileDirectory + fileName);
        if (!file.is_open()) {
            //cout << "Could not open file: \"" << fileName << "\".\n";
            throw std::runtime_error("Could not open file.");
        }
        file << data;
        //Done saving here.
        cout << "File \"" << fileName << "\" has been saved.\n";

        file.close();
    
    } catch (std::runtime_error error) {
        cout << error.what() << endl;
    }
}