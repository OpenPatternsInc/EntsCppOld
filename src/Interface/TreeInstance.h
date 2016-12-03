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

/* 
 * 
 */

#ifndef TREEINSTANCE_H
#define TREEINSTANCE_H

#include "EntInstance.h"
#include "../Core/Ent.h"
#include "../Core/Tree.h"
#include "EntsInterface.h"

class EntInstance;
class Tree;
class Ent;

class TreeInstance {
    
    friend class EntsInterface;
    
    Tree* tree;
    
    /*
     * Only let the abstract class EntsInterface access the constructor.
     * 
     * The creation of TreeWrappers will also be handled privately by 
     * EntsInterface in order to encapsulate from subclasses via sanitized
     * functions.
     */
    TreeInstance(Tree*);
    
    /*
     * Also private to EntsInterface because we want EntsInterface to handle
     * destruction via calls to virtual methods of the subclass.
     */
    ~TreeInstance();
    
    /*
     * Explicit inline function for getting the Tree instance.
     * Only accessible to abstract EntsInterface class.
     */
    Tree* getTree() {
        return tree;
    }
    
    void addEnt(Ent* ent, Ent* parent = nullptr);
    
    void rename(string newName);
    
public:
    
    /**************************************************************************
     * Public functions that subclasses of EntsInterface may call.
     * Functions are sanitized so that they don't screw stuff up.
     **************************************************************************/
    
    EntInstance* getRoot();
    
    EntInstance* getEntByName(string name);
    
    bool isEntNameFree(string name);
    
    string getName();
    
};



#endif /* TREEINSTANCE_H */

