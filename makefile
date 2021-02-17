preprocesing:preprocesing.o private_meth.o stage1.o stage2.o 
	gcc -g -ansi -Wall -pedantic preprocesing.o private_meth.o stage1.o stage2.o -o preprocesing -lm
	
preprocesing.o: preprocesing.c preprocesing.h
	gcc -c -ansi -Wall -pedantic  preprocesing.c -o preprocesing.o -lm
	
private_meth.o: private_meth.c 
	gcc -c -ansi -Wall -pedantic  private_meth.c -o private_meth.o
	
stage1.o: stage1.c stages.h
	gcc -c -ansi -Wall -pedantic stage1.c -o stage1.o -lm
	
stage2.o: stage2.c stages.h
	gcc -c -ansi -Wall -pedantic stage2.c -o stage2.o -lm


