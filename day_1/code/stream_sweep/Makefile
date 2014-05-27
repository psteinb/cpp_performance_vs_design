CC = gcc
CFLAGS = -O2 -DNTIMES=50 

FF = g77
FFLAGS = -O2 -DNTIMES=50

NUMBERS=$(shell seq 0 128 4096) #L1
NUMBERS+=$(shell seq 4096 512 327680) #L2
NUMBERS+=$(shell seq 327680 1024 3932160)

all: stream_c.exe

stream_c.exe: stream.c
	$(CC) $(CFLAGS) stream.c -o stream_c.exe

sweep:
	@for i in $(NUMBERS);do \
	$(CC) $(CFLAGS) -DSTREAM_ARRAY_SIZE=$$i stream.c -o stream_c_$$i_doubles.exe;\
	done

run-sweep:
	@for i in $(NUMBERS);do \
	FILE=./stream_c_$$i_doubles.exe; numactl -l -C 0 -m 0 ./$$FILE > $$(FILE/.exe/.log); \
	done

mt-sweep:
	@for i in $(NUMBERS);do \
	$(CC) $(CFLAGS) -fopenmp -DSTREAM_ARRAY_SIZE=$$i stream.c -o openmp_stream_c_$$i_doubles.exe; \
	done

run-mt-sweep:
	@for i in $(NUMBERS);do \
	FILE=./openmp_stream_c_$$i_doubles.exe; ./$$FILE > $$(FILE/.exe/.log); \
	done

clean:
	rm -f stream_c*.exe *.o openmp_stream_c*exe
