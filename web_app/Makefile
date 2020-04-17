LDFLAGS = -lcppcms -lbooster
CXXFLAGS = -Wall -Werror -std=c++14
FILE = app.cc main.cc page.cc
CXX = g++

all: page_tmpl app

page_tmpl: page.tmpl content.h
	cppcms_tmpl_cc page.tmpl -o page.cc

app: $(FILE)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(FILE) -o app

clean:
	-@ rm app page.cc
