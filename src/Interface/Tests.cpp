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

#include "Tests.h"
#include <string>

using namespace std;

bool Tests::isValidTreeName(const string name, string* mess) {
    
    if (name.size() == 0) {
        *mess = "The name can't be blank!";
    } else if (name.size() < 4) {
        *mess = "The name must be at least 4 characters.";
    } else if (name.size() > 25) {
        *mess = "The name must be 25 characters or less.";
    } else {
        return true;
    }
    return false;
} //end of isValidTreeName


bool Tests::isValidEntName(const string name, string* mess) {
    
    if (name.size() == 0) {
        *mess = "Name can't be blank.";
    } else if (name.size() < 4) {
        *mess = "Name must be at least 4 characters.";
    } else if (name.size() > 20) {
        *mess = "Name must 20 characters or less.";
    } else {
        return true;
    }
    return false;
} //end of isValidEntName