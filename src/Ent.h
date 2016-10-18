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

//#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Ent
{
public:

    /**
     * Initialize an Ent with no properties yet.
     */
    Ent();
    /**
     * Initialize an Ent with the given name. Doesn't check if that name is unique.
     * @param name
     */
    Ent(string);
    /**
     * What to do when an Ent object is removed from memory. Probably nothing now.
     */
    ~Ent();

    /**
     * Prints the name of the Ent to the stdout.
     */
    inline void printName() { cout << "Ent name: \"" << m_name << "\"\n"; }
    /**
     * Sets the name of the Ent without checking its uniqueness.
     */
    inline void setName(string name) { m_name = name; }
    
    inline string getName() {
        return m_name;
    }
    /**
     * Gets the Ent's unique identifier.
     * @return 
     */
    inline unsigned int getUID() { return m_uid; }
    /**
     * Adds an Ent as a parent of this one, but doesn't check anything.
     * @param parent
     */
    inline void addParent(Ent parent) { m_parents.push_back(parent.getUID()); }
    /**
     * Adds an Ent as a child of this one, but doesn't check anything.
     * @param child
     */
    inline void addChild(Ent child) { m_children.push_back(child.getUID()); }

private:

    /**
     * The name of the given Ent. Should ideally be unique.
     */
    string m_name;
    /**
     * The unique identifier of the Ent.
     */
    unsigned int m_uid;
    /**
     * The uids of it's parents.
     */
    vector<unsigned int> m_parents;
    /**
     * The uids of it's children.
     */
    vector<unsigned int> m_children;

};



#endif /* ENT_H */

