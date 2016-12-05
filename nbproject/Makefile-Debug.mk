#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Algorithms/EntsAlgorithms.o \
	${OBJECTDIR}/src/CLI/CLI.o \
	${OBJECTDIR}/src/Core/Ent.o \
	${OBJECTDIR}/src/Core/Root.o \
	${OBJECTDIR}/src/Core/Tree.o \
	${OBJECTDIR}/src/Interface/EntX.o \
	${OBJECTDIR}/src/Interface/EntsInterface.o \
	${OBJECTDIR}/src/Interface/Tests.o \
	${OBJECTDIR}/src/Interface/TreeInstance.o \
	${OBJECTDIR}/src/Network/EntsClient.o \
	${OBJECTDIR}/src/Network/EntsServer.o \
	${OBJECTDIR}/src/Util/EntsFile.o \
	${OBJECTDIR}/src/Util/IO.o \
	${OBJECTDIR}/src/Util/Prime.o \
	${OBJECTDIR}/src/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=/usr/lib64/libboost_system.so.1.60.0 /usr/lib64/libpthread.so.0

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ents

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ents: /usr/lib64/libboost_system.so.1.60.0

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ents: /usr/lib64/libpthread.so.0

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ents: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	g++ -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ents ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/Algorithms/EntsAlgorithms.o: src/Algorithms/EntsAlgorithms.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Algorithms
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Algorithms/EntsAlgorithms.o src/Algorithms/EntsAlgorithms.cpp

${OBJECTDIR}/src/CLI/CLI.o: src/CLI/CLI.cpp
	${MKDIR} -p ${OBJECTDIR}/src/CLI
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/CLI/CLI.o src/CLI/CLI.cpp

${OBJECTDIR}/src/Core/Ent.o: src/Core/Ent.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Core
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Core/Ent.o src/Core/Ent.cpp

${OBJECTDIR}/src/Core/Root.o: src/Core/Root.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Core
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Core/Root.o src/Core/Root.cpp

${OBJECTDIR}/src/Core/Tree.o: src/Core/Tree.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Core
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Core/Tree.o src/Core/Tree.cpp

${OBJECTDIR}/src/Interface/EntX.o: src/Interface/EntX.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Interface
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Interface/EntX.o src/Interface/EntX.cpp

${OBJECTDIR}/src/Interface/EntsInterface.o: src/Interface/EntsInterface.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Interface
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Interface/EntsInterface.o src/Interface/EntsInterface.cpp

${OBJECTDIR}/src/Interface/Tests.o: src/Interface/Tests.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Interface
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Interface/Tests.o src/Interface/Tests.cpp

${OBJECTDIR}/src/Interface/TreeInstance.o: src/Interface/TreeInstance.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Interface
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Interface/TreeInstance.o src/Interface/TreeInstance.cpp

${OBJECTDIR}/src/Network/EntsClient.o: src/Network/EntsClient.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Network
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Network/EntsClient.o src/Network/EntsClient.cpp

${OBJECTDIR}/src/Network/EntsServer.o: src/Network/EntsServer.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Network
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Network/EntsServer.o src/Network/EntsServer.cpp

${OBJECTDIR}/src/Util/EntsFile.o: src/Util/EntsFile.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Util
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Util/EntsFile.o src/Util/EntsFile.cpp

${OBJECTDIR}/src/Util/IO.o: src/Util/IO.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Util
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Util/IO.o src/Util/IO.cpp

${OBJECTDIR}/src/Util/Prime.o: src/Util/Prime.cpp
	${MKDIR} -p ${OBJECTDIR}/src/Util
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Util/Prime.o src/Util/Prime.cpp

${OBJECTDIR}/src/main.o: src/main.cpp
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.cc) -g -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/main.o src/main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} -r ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libpthread.so.0 ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libboost_system.so.1.60.0
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ents

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
