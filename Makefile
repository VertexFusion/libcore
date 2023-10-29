# Paths
PATH_CORE = src/core
PATH_BUILD = build
PATH_BIN = bin
PATH_TEST = test

PATH_ZLIB = 3rdparty/zlib

# Which compiler should be used?
CXX = clang

UNAME_S := $(shell uname -s)

#####################################################################
# macOS
#####################################################################
ifeq ($(UNAME_S),Darwin)

   C__ = clang
   ZLIBFLAGS = -O3 -DHAVE_HIDDEN -mmacosx-version-min=10.12

   CXX = clang++
   CFLAGS = -g -Wall -pedantic -Wextra -Wno-long-long -fPIC -O3  -mmacosx-version-min=10.12 -I$(PATH_SRC)
   TESTFLAGS = -framework CoreFoundation -framework CoreServices
   LFLAGS = -dynamiclib -current_version 1.3 $(TESTFLAGS)  -mmacosx-version-min=10.12
   LIB_NAME = libjameo.dylib

endif

#####################################################################
# Linux
#####################################################################
ifeq ($(UNAME_S),Linux)

   C__ =clang
   ZLIBFLAGS = -O3 -DHAVE_HIDDEN -fPIC -Wno-everything
   CXX= clang++
   CFLAGS = -g -Wall -pedantic -Wextra -Wno-long-long -fPIC -O3 -std=c++11
   TESTFLAGS = -pthread -ldl
   LFLAGS = -shared -pthread -ldl
   LIB_NAME = libcore.so

endif

#####################################################################
# BELOW THIS LINE THERE IS NO OS DEPENDENT CODE
#####################################################################

SOURCES =\
 $(PATH_CORE)/AutoreleasePool.cpp\
 $(PATH_CORE)/Character.cpp\
 $(PATH_CORE)/Charset.cpp\
 $(PATH_CORE)/CharsetDecoder.cpp\
 $(PATH_CORE)/Colour.cpp\
 $(PATH_CORE)/CRC.cpp\
 $(PATH_CORE)/Date.cpp\
 $(PATH_CORE)/DateFormatter.cpp\
 $(PATH_CORE)/Deflater.cpp\
 $(PATH_CORE)/Diff.cpp\
 $(PATH_CORE)/DiffBacktrace.cpp\
 $(PATH_CORE)/DiffDiag.cpp\
 $(PATH_CORE)/DiffDistance.cpp\
 $(PATH_CORE)/DiffInfo.cpp\
 $(PATH_CORE)/Exception.cpp\
 $(PATH_CORE)/Extents.cpp\
 $(PATH_CORE)/File.cpp\
 $(PATH_CORE)/Hashtable.cpp\
 $(PATH_CORE)/MacRomanDecoder.cpp\
 $(PATH_CORE)/Math.cpp\
 $(PATH_CORE)/Matrix.cpp\
 $(PATH_CORE)/Object.cpp\
 $(PATH_CORE)/String.cpp\
 $(PATH_CORE)/StringTokenizer.cpp\
 $(PATH_CORE)/Mutex.cpp\
 $(PATH_CORE)/System.cpp\
 $(PATH_CORE)/Test.cpp\
 $(PATH_CORE)/TestVector.cpp\
 $(PATH_CORE)/UTF8Decoder.cpp\
 $(PATH_CORE)/Vector.cpp\
 $(PATH_CORE)/Vertex2.cpp\
 $(PATH_CORE)/Vertex3.cpp\
 $(PATH_CORE)/Windows1252Decoder.cpp\
 $(PATH_CORE)/Serializer.cpp\
 $(PATH_CORE)/Thread.cpp\
 $(PATH_CORE)/Properties.cpp\
 $(PATH_CORE)/I18nBundle.cpp\
 $(PATH_CORE)/Inflater.cpp\
 $(PATH_CORE)/Iterator.cpp\
 $(PATH_CORE)/UTF16Decoder.cpp\
 $(PATH_CORE)/Stream.cpp\
 $(PATH_CORE)/MemoryStream.cpp\
 $(PATH_CORE)/Integer.cpp\
 $(PATH_CORE)/Document.cpp\
 $(PATH_CORE)/UndoChange.cpp\
 $(PATH_CORE)/UndoManager.cpp\
 $(PATH_CORE)/UndoStep.cpp\
 $(PATH_CORE)/Property.cpp\
 $(PATH_CORE)/LinkedList.cpp\
 $(PATH_CORE)/Geometry.cpp\
 $(PATH_CORE)/NURBS.cpp\
 $(PATH_CORE)/PaintingBackend.cpp\
 $(PATH_CORE)/Transform.cpp

ZLIB =\
 $(PATH_ZLIB)/adler32.c\
 $(PATH_ZLIB)/crc32.c\
 $(PATH_ZLIB)/deflate.c\
 $(PATH_ZLIB)/infback.c\
 $(PATH_ZLIB)/inffast.c\
 $(PATH_ZLIB)/inflate.c\
 $(PATH_ZLIB)/inftrees.c\
 $(PATH_ZLIB)/trees.c\
 $(PATH_ZLIB)/zutil.c\
 $(PATH_ZLIB)/compress.c\
 $(PATH_ZLIB)/uncompr.c\
 $(PATH_ZLIB)/gzclose.c\
 $(PATH_ZLIB)/gzlib.c\
 $(PATH_ZLIB)/gzread.c\
 $(PATH_ZLIB)/gzwrite.c

OBJECTS = $(ZLIB:.c=.o) $(SOURCES:.cpp=.o)

# Liste der Testdateien
TEST =\
 $(PATH_TEST)/Main.cpp\
 $(PATH_TEST)/core/GeometryTest.cpp\
 $(PATH_TEST)/core/HashtableTest.cpp\
 $(PATH_TEST)/core/LinkedListTest.cpp\
 $(PATH_TEST)/core/MathTest.cpp\
 $(PATH_TEST)/core/DateTest.cpp\
 $(PATH_TEST)/core/StringTest.cpp\
 $(PATH_TEST)/core/VertexTest.cpp\
 $(PATH_TEST)/core/StringTokenizerTest.cpp\
 $(PATH_TEST)/core/MatrixTest.cpp\
 $(PATH_TEST)/core/DeflateTest.cpp\
 $(PATH_TEST)/core/UndoManagerTest.cpp


TESTOBJECTS = $(ZLIB:.c=.o) $(SOURCES:.cpp=.o) $(TEST:.cpp=.o)

# Wo finde ich die Header-Dateien?
INCLUDE = -Iinclude -I3rdparty -Iprec

# Target = ALL
Debug: $(OBJECTS)
	$(CXX) $(LFLAGS) -o $(LIB_NAME) $(OBJECTS)
	mkdir -p $(PATH_BIN)
	ar rcs libvxf.a $(OBJECTS)
	mv $(LIB_NAME) $(PATH_BIN)/$(LIB_NAME)
	mv libvxf.a $(PATH_BIN)/libvxf.a

test: $(TESTOBJECTS)
	$(CXX) $(CFLAGS) $(INCLUDE) $(TESTFLAGS) -o test.app $(TESTOBJECTS)

prec/Precompiled.pch: prec/Precompiled.h
	$(CXX) $(CFLAGS) $(INCLUDE) prec/Precompiled.h -o prec/Precompiled.pch

%.o: %.c
	mkdir -p $(PATH_BUILD)
	$(C__) $(ZLIBFLAGS) -c $< -o $@

%.o: %.cpp prec/Precompiled.pch
	$(CXX) $(CFLAGS) $(INCLUDE) -include-pch prec/Precompiled.pch -c $< -o $@

clean:
	rm -f $(TESTOBJECTS) prec/Precompiled.pch
	rm -Rf $(PATH_BIN)/*


# DO NOT DELETE
