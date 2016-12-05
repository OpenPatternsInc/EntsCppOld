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

#ifndef CLI_H
#define CLI_H

#include <string>
#include <iostream>
#include <unordered_set>
#include "CLIExceptions.h"
#include "../Interface/Includes.h"
#include "../Util/EntsFile.h"

using namespace std;
    
//TODO Get rid of this thing...
typedef enum {
    NO_PAIRS_FOUND,
    PAIR_RESOLVED,
    PAIR_UNRESOLVED,
    RESOLUTION_ERROR
} EstrangedChildrenResolution;

/**
 * CLI is an implementation subclass of the abstract class EntsInterface.
 * It provides a Command Line Interface to explore and edit Tree objects.
 * 
 * CLI has access to handle classes TreeInstance and EntX. These objects can
 * be passed by value and hold only pointers to the objects they represent.
 * They provide a number of public functions available to subclasses of 
 * EntsInterface, like CLI, which request for changes to be made to the Tree
 * and Ents within it. These requests for changes make sure that no illegal
 * actions are performed which would put the Tree in a bad state.
 * 
 * CLI must implement certain virtual functions in order to be able to provide
 * adequate interface to the user for the specific protocols specified in
 * EntsInterface.
 */
class CLI : public EntsInterface {
    
    /**************************************************************************
     * Data Members
     **************************************************************************/
    
    /**
     * The Tree wrapper holding the tree being explored currently.
     */
    TreeInstance tree;
    /** Wrapper for the current Ent of focus. */
    EntX focus;
    
    /**************************************************************************
     * Private Functions for this specific implementation of EntsInterface.
     **************************************************************************/
    
    const bool isCommand(const string command, const string text, string *argument);
    
    EstrangedChildrenResolution checkForEstrangedChildren(Ent *parent);

    void parseCommand(string str, bool * exiting);
    
    void printHelp();
    
    void printFocus();
    
    void printEntList(string listDescription, vector<EntX> list);
    
    void printParents(EntX ent);
    
    void printChildren(EntX ent);
    
    void printSiblings(EntX ent);
    
    void setFocus(EntX ent) {
        focus = ent;
        printFocus();
    }
    
    void setTree(TreeInstance tr) {
        tree = tr;
    }
    

public:
    
    /**************************************************************************
     * Public constructors and destructors.
     **************************************************************************/

    CLI();

    ~CLI();
    
    /**************************************************************************
     * Public functions available to the owner of the CLI instance.
     **************************************************************************/

    void listen();
    
    /********************************************************************
     * Virtual function implementations (Should these be protected?)
     ********************************************************************/
    
    void queryUserForText(string* text, string message);
    
    void displayMessageToUser(string text);

};



#endif /* CLI_H */

