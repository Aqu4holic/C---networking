flags = -g -Wall -Wextra -DBlackWhite -O2 -std=c++20
linkers_flags = -lws2_32
lib_path = ""
linkers_path = ""

src_path = src
proc_path = bin
src_ext = .cpp
proc_ext = .exe

SOURCES = $(wildcard $(src_path)/*$(src_ext))
EXECUTABLES = $(patsubst $(src_path)/%$(src_ext), $(proc_path)/%$(proc_ext), $(SOURCES))

all: $(EXECUTABLES)

$(EXECUTABLES): $(proc_path)/%$(proc_ext): $(src_path)/%$(src_ext)
#	g++ $(flags) -I $(lib_path) -L $(linkers_path) $< -o $@ $(linkers_flags)
	g++ $(flags) $< -o $@ $(linkers_flags)

clean:
	rm -f $(EXECUTABLES)

build_all: clean all