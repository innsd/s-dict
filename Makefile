cc = g++
prom = sdict
obj = s_dict.o analyzer.o interpretation.o iohandler.o
pre = ./include/analyzer.h ./include/exceptions.h ./include/interpretation.h ./include/iohandler.h ./include/libsql.h ./include/def.h
$(prom):$(obj)
	$(cc) -o $(prom) $(obj) -l sqlite3
s_dict.o: s_dict.cpp $(pre)
	$(cc) -c s_dict.cpp
analyzer.o: ./lib/analyzer.cpp $(pre)
	$(cc) -c ./lib/analyzer.cpp
interpretation.o: ./lib/interpretation.cpp $(pre)
	$(cc) -c ./lib/interpretation.cpp
iohandler.o: ./lib/iohandler.cpp $(pre)
	$(cc) -c ./lib/iohandler.cpp
.PHONY:clean
clean:
	-rm $(obj)