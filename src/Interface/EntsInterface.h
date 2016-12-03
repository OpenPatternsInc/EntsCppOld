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

#include "EntInstance.h"
#include "TreeInstance.h"
#include "InterfaceExceptions.h"
#include "../Core/Tree.h"
#include "../Util/EntsFile.h"
#include "Tests.h"

class Tree;
class EntsFile;
class TreeInstance;
class EntInstance;

using namespace std;

/**
 * This abstract class provides a standard way for derived UIs to interface properly
 * with an Ents Tree Hierarchy. It allows for the manipulation of a Tree, as
 * well as ensures that the UI can respond to actions required by the user.
 * 
 * Common actions are defined in this base class, which are passed onto CLIs
 * and GUIs which may use and display them in different ways.
 */
    

//TODO Rename to Interface, the Ents part is redundant.
class EntsInterface {
    
    friend class Tree;
    
    /*********************************************************************
     * Private data members.
     *********************************************************************/
    
    /**
     * The trees available to explore and edit.
     */
    vector<TreeInstance*> trees;
    
    
    /*********************************************************************
     * Private methods for internal use.
     *********************************************************************/
    
    
    
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
    
    EntInstance* getEmptyEntInstance();
    
    /*
     * Creates and returns a new TreeInstance, which will be used by subclasses
     * to refer to Tree instances.
     */
    void getNewEmptyTreeInstance(TreeInstance** treePtr);
    /*
     * Subclasses call this when the user indicates they want to add a new Ent.
     */
    void requestToCreateNewEnt(TreeInstance* tree, EntInstance** entPointerFromUI);
    
    void requestToRenameTree(TreeInstance* tree);
    
    
    /*********************************************************************
     * Virtual functions the derived interface must implement.
     * These functions will be specific to the UI implementation,
     * and are necessary for the UI to adhere to the Interface protocol.
     *********************************************************************/
    
    /*
     * Called when text input is needed from the user.
     */
    virtual void queryUserForText(string* text, string message) = 0;
    
    
    virtual void displayMessageToUser(string text) = 0;
    
};



#endif /* ENTSINTERFACE_H */

