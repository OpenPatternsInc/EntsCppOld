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

#ifndef HIERARCHY_H
#define HIERARCHY_H

#include <vector>
#include "Ent.h"
#include "Root.h"

using namespace std;

class Hierarchy
{
public:

    /**
     * Create a new Hierarchy and add a root Ent to it.
     */
    Hierarchy();
    /**
     * What do do when the Hierarchy is removed from memory. Maybe save to file?
     */
    ~Hierarchy();
    /**
     * Adds an Ent to the Hierarchy without checking anything about it.
     * @param ent
     */
    inline void addEnt(Ent ent) { m_ents.push_back(ent); }
    
    inline Root* getRoot() { return &m_root; }

private:

    vector<Ent> m_ents;
    
    Root m_root;
    
    




};


#endif /* HIERARCHY_H */

