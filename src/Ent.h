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

#ifndef ENT_H
#define ENT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

class Ent
{
public:

    Ent();
    ~Ent();

    //Prints the name of the Ent to the stdout.
    void printName();
    //Sets the name of the Ent without checking its uniqueness.
    void setName(std::string);

private:

    //The name of the given Ent. Should ideally be unique.
    std::string m_name;
    //The unique identifier of the Ent.
    unsigned int m_uid;
    //The uids of it's parents.
    std::vector<unsigned int> m_parents;
    //The uids of it's children.
    std::vector<unsigned int> m_children;

};



#endif /* ENT_H */

