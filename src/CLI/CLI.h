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
#include "../Core/Ent.h"
#include "../Core/Root.h"
#include "../Core/Tree.h"
#include "../TreeAnalysis/TreeAnalyzer.h"
#include "../Util/EntsFile.h"

using namespace std;
    
typedef enum {
    NO_PAIRS_FOUND,
    PAIR_RESOLVED,
    PAIR_UNRESOLVED,
    RESOLUTION_ERROR
} EstrangedChildrenResolution;

class CLI {
    /** If set to true, the after the next command is parsed, stop listening
     * and return control to the calling function. */
    bool exiting_;
    /** Points to the current Ent of focus. */
    Ent* focusPtr;
    /** Points to the Tree Currently being explored.*/
    Tree* treePtr;
    /** The EntsFile corresponding to the currently explored tree.*/
    EntsFile* entsFile;

    void listChildren(Ent* entPtr);
    
    void listParents(Ent* entPtr);
    
    void listAncestors(Ent* entPtr);
    
    void listDescendents(Ent* entPtr);
    
    const bool isCommand(const string command, const string text, string *argument);
    
    EstrangedChildrenResolution checkForEstrangedChildren(Ent *parent);

    void parseCommand(string str);
    
    void printHelp();
    

public:


    CLI(EntsFile* entsFile);

    ~CLI();

    void listen();
    /**
     * Set the focus of the CLI listener to the given Ent.
     * @param ent_ptr   Points to the new focus.
     */
    inline void setFocus(Ent* entPtr_) {
        focusPtr = entPtr_;
    }
    /**
     * Sets the Tree to explore.
     */
    inline void setEntsFile(EntsFile* newEntsFile) {
        entsFile = newEntsFile;
        treePtr = newEntsFile->getTree();
        focusPtr = treePtr->getRoot();
        //TODO Tell the user which Tree is now being explored.
    }
    
    bool saveTree();
    
    bool queryTreeName(EntsFile* entsFile);
    
    bool queryFileName();

};



#endif /* CLI_H */

