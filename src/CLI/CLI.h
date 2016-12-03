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
#include "../Interface/EntInstance.h"
#include "../Interface/EntsInterface.h"
#include "../Interface/TreeInstance.h"
#include "../TreeAnalysis/TreeAnalyzer.h"
#include "../Util/EntsFile.h"
#include "CLIExceptions.h"
#include "../Interface/InterfaceExceptions.h"

using namespace std;

class TreeInstance;
class EntInstance;
    
typedef enum {
    NO_PAIRS_FOUND,
    PAIR_RESOLVED,
    PAIR_UNRESOLVED,
    RESOLUTION_ERROR
} EstrangedChildrenResolution;

class CLI : public EntsInterface {
    
    /**
     * The Tree wrapper holding the tree being explored currently.
     */
    TreeInstance* tree = nullptr;
    /** Points to the current Ent of focus. */
    EntInstance focus;
    
    const bool isCommand(const string command, const string text, string *argument);
    
    EstrangedChildrenResolution checkForEstrangedChildren(Ent *parent);

    void parseCommand(string str, bool * exiting);
    
    void printHelp();
    
    void printFocus() {
        if (!focus.isEmpty())
            cout << "Focus: " << focus.getName() << endl;
        else
            cout << "No Ent is currently the focus.\n";
    }
    
    void setFocus(EntInstance ent) {
        focus = ent;
    }
    
    void setTree(TreeInstance* tr) {
        tree = tr;
    }
    

public:

    CLI();

    ~CLI();

    void listen();
    
    /********************************************************************
     * Virtual function implementations
     ********************************************************************/
    
    void queryUserForText(string* text, string message);

};



#endif /* CLI_H */

