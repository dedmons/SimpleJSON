# Created by DJ Edmonson
#   dedmons@g.clemson.edu

# Warnings frequently signal eventual errors:
CXXFLAGS=-g -W -Wall -Weffc++ -Wextra -pedantic -O0
# Linker flags for both OS X and Linux
LDFLAGS=

# Generates list of object files from all the
#   source files in directory
OBJS = $(addsuffix .o, $(basename $(shell find *.cpp)))
DEPS = $(OBJS:.o=.d)

# Set executable name
EXEC = run

SCAN_BUILD = $(shell which scan-build)
ifeq "$(SCAN_BUILD)" ""
SCAN_BUILD="./checker-271/scan-build"
endif


# Declare the phony targets
.PHONY: echo clean r clang gcc \
  setclang setgcc vg lint csa sbsetup sbclean sb

# Phony targets to run dependencies in order
clang: | setclang $(EXEC)
gcc: | setgcc $(EXEC)
gcc48: | setgcc48 $(EXEC)

# Uses cppcheck for more static analysys
lint:
	cppcheck ./*.h ./*.cpp

# Run the executable
r:
	./$(EXEC)

# Clean all the created files
clean:
	rm -rf $(OBJS)
	rm -rf $(DEPS)
	rm -rf $(EXEC)
	rm -rf *.d.*

# Phony target to use clang for compile and linking
setclang:
	@echo "Setting clang"
	$(eval CXX = clang++)
	$(eval CXX_LINK = clang++)
	$(eval CXXFLAGS = $(CXXFLAGS) -stdlib=libc++)

# Phony target to use g++ for compile and linking
setgcc48:
	@echo "Setting g++"
	$(eval CXX = g++-4.8)
	$(eval CXX_LINK = g++-4.8)
	$(eval CXXFLAGS = $(CXXFLAGS) -std=c++11)

# Phony target to use g++ for compile and linking
setgcc:
	@echo "Setting g++"
	$(eval CXX = g++)
	$(eval CXX_LINK = g++)
	$(eval CXXFLAGS = $(CXXFLAGS))

# $< refers to the first dependency
# Uses static pattern rule to keep from compiling all
#   objects every time.
$(OBJS): %.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Static pattern to build dependencies
$(DEPS): %.d: %.cpp
	@echo "Generating "$@
	@set -e; rm -f $@; \
      g++ -MM $(CPPFLAGS) $< > $@.$$$$; \
      sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
      rm -f $@.$$$$

# Link all the object files together into exicutible
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

include $(DEPS)