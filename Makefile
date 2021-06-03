all:


test: cpp pvs

cpp: $(OUT_CPP)

pvs: clean
	./pvs.sh

%.cpp: %.c
	cppcheck --quiet --enable=all --force --inconclusive $< 2>> output.cppOut

cleanTest:
	rm output.cppOut report.tasks

.PHONY:  all clean cleanTest cpp test pvs
