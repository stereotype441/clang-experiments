CXXFLAGS=$(shell llvm-config --cxxflags) -fno-rtti
LDFLAGS=$(shell llvm-config --ldflags)

#	g++ $(LDFLAGS) -lLLVMSupport -lLLVMSystem -lLLVMBitReader -lLLVMBitWriter -lclangDriver -o $@ $^ -lclangFrontend -lclangBasic
test: clang_test.o
	g++ -o $@ $(LDFLAGS) $^ -lclangFrontend -lclang -lclangLex -lclangBasic


%.o: %.cpp
	g++ $(CXXFLAGS) -c $^ -o $@
