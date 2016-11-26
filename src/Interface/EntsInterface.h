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

#ifndef ENTSINTERFACE_H
#define ENTSINTERFACE_H

#include "InterfaceExceptions.h"
//TODO: Probably don't need these includes?
#include "../Core/Tree.h"
#include "../Util/EntsFile.h"

class Tree;
class EntsFile;

/**
 * This abstract class provides a standard way for derived UIs to interface properly
 * with an Ents Tree Hierarchy. It allows for the manipulation of a Tree, as
 * well as ensures that the UI can respond to actions required by the user.
 * 
 * Common actions are defined in this base class, which are passed onto CLIs
 * and GUIs which may use and display them in different ways.
 */
class EntsInterface {
    
    friend class Tree;
    
    /*********************************************************************
     * Private data members.
     *********************************************************************/
    
    /**
     * The trees available to explore and edit.
     */
    vector<Tree*> trees;
    
    
    /*********************************************************************
     * Private methods for internal use.
     *********************************************************************/
    
    bool isValidTreeName(string name);
    
    
    /*********************************************************************
     * Protected methods available to derivatives.
     *********************************************************************/
    
protected:
    
    /**
     * We never want to actually create an instance of EntsInterface, so only
     * make the constructor available to derivatives.
     */
    EntsInterface();
    
    ~EntsInterface();
    
    
    
    bool saveTree(Tree *tree);
    
    Tree* generateNewTreeWithName(string name);
    
    void setFileName(string fileName);
    
    
    /*********************************************************************
     * Virtual functions the derived interface must implement.
     *********************************************************************/
    
    virtual bool queryFileName() = 0;
    
    //virtual bool queryTreeName(string **response) = 0;
    
    /**
     * Derived classes should implement this method as a way to ask the user
     * input regarding the creation of a new Tree instance. Perhaps this isn't
     * the best way to do things because it isn't necessary for polymerization,
     * but it makes sense to encourage it, for now.
     */
    virtual Tree* createNewTree() = 0;
    
};



#endif /* ENTSINTERFACE_H */

