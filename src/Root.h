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

#ifndef ROOT_H
#define ROOT_H

#include "Ent.h"

/**
 * The Root class is a special type of Ent which is at the top of the hierarchy.
 */
class Root : public Ent
{
public:

    /**
     * Initialize a root Ent.
     */
    Root();
    
    ~Root();

private:
    
    /**
     * We don't want to add any parents to root.
     * @param parent
     */
    void addParent(Ent parent);

};



#endif /* ROOT_H */

