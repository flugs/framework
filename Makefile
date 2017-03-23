NUMBER_OF_PROCESSORS ?= 1
NPROCS:=$(NUMBER_OF_PROCESSORS)
OS:=$(shell uname -s)

ifeq ($(OS),Linux)
	NPROCS := $(shell grep -c ^processor /proc/cpuinfo)
else ifeq ($(OS),Darwin)
	NPROCS := $(shell sysctl hw.ncpu | awk '{print $$2}')
endif

.PHONY: all
all:
	mkdir -p .build ; mkdir -p install
	cd .build ; cmake .. -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=Profile && make -j$(NPROCS)

.PHONY: clazy
clazy:
	mkdir -p .build/clazy ; mkdir -p install/clazy
	cd .build/clazy ; cmake ../.. -DCMAKE_CXX_COMPILER=clazy -DCMAKE_INSTALL_PREFIX=../../install/clazy -DCMAKE_BUILD_TYPE=Profile && make -j1 && make install

.PHONY: scan-build
scan-build:
	scan-build -o doc/scan-build -enable-checker security.FloatLoopCounter -enable-checker security.insecureAPI.rand -enable-checker security.insecureAPI.strcpy -enable-checker alpha.cplusplus.VirtualCall make -j1

.PHONY: test
test: all
	mkdir -p doc ; mkdir -p .build ; lcov -b . -d .build/ --zerocounters
	cd .build ; ctest -T test --no-compress-output || true

.PHONY: coverage
coverage: test
	lcov -b . -d .build/ -c -o .build/coverage.info
	lcov --remove .build/coverage.info "/usr*" -o .build/coverage.info           # remove output for external libraries
	lcov --remove .build/coverage.info ".build*" -o .build/coverage.info         # remove output for build directory
	lcov --remove .build/coverage.info "*/.build*" -o .build/coverage.info       # remove output for build directory
	lcov --remove .build/coverage.info "*/3rdparty/*" -o .build/coverage.info    # remove output for 3rdparty directory
	lcov --remove .build/coverage.info "*/tests/*test.*" -o .build/coverage.info # remove output for tests directory
	genhtml -o doc/coverage -t "Flugs test coverage" --num-spaces 4 .build/coverage.info
	python3 ./scripts/gcovr -r . -e .build -e tests --xml > doc/coverage.xml

.PHONY: doc
doc:
	mkdir -p doc/api
	doxygen

.PHONY: mkdocs
mkdocs:
	pushd doc ; mkdocs serve ; popd

.PHONY: pmd
pmd:
	mkdir -p doc ; scripts/pmd-cpd.sh > doc/pmd.xml

.PHONY: cppcheck
cppcheck:
	mkdir -p doc ; scripts/cppcheck.sh 2> doc/cppcheck.xml

.PHONY: sloccount
sloccount:
	mkdir -p doc ; ./scripts/sloccount.sh | tee doc/sloccount.sc

.PHONY: style
style:
	./scripts/codingstyle.sh

.PHONY: clean
clean:
	find . -iname *~ -exec rm {} \;
	find . -iname .DS_Store -exec rm {} \;
	rm -rf doc/scan-build
	rm -rf install
	rm -rf .build
	rm -rf build

.PHONY: install
install:
	cd .build && make install

