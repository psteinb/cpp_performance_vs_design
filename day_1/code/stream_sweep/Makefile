CC = gcc
CFLAGS = -O2 -DNTIMES=50 

FF = g77
FFLAGS = -O2 -DNTIMES=50

NUMBERS=$(shell seq 0 128 4096) #L1
NUMBERS+= $(shell seq 4096 512 327680) #L2
NUMBERS+= $(shell seq 327680 1024 3932160)

LAST_NUMBER=3932160

all: stream_c.exe

stream_c.exe: stream.c
	$(CC) $(CFLAGS) stream.c -o stream_c.exe

sweep:
	@for i in $(NUMBERS);do \
	echo "compiling " $$i "/" $(LAST_NUMBER);\
	$(CC) $(CFLAGS) -DSTREAM_ARRAY_SIZE=$$i stream.c -o stream_c_$${i}_doubles.exe ; \
	done

run-sweep:
	@for i in $(NUMBERS);do \
	echo "running " $$i "/" $(LAST_NUMBER);\
	numactl -C 0 -m 0 ./stream_c_$${i}_doubles.exe > ./stream_c_$${i}_doubles.log 2>&1 ; \
	done

mt-sweep:
	@for i in $(NUMBERS);do \
	echo "compiling " $$i "/" $(LAST_NUMBER);\
	$(CC) $(CFLAGS) -fopenmp -DSTREAM_ARRAY_SIZE=$$i stream.c -o openmp_stream_c_$${i}_doubles.exe ; \
	done

run-mt-sweep:
	@for i in $(NUMBERS);do \
	echo "running " $$i "/" $(LAST_NUMBER);\
	./openmp_stream_c_$${i}_doubles.exe > ./openmp_stream_c_$${i}_doubles.log 2>&1 ; \
	done

clean:
	rm -f stream_c*.exe *.o openmp_stream_c*exe
