CC = gcc
CFLAGS = -O2

FF = g77
FFLAGS = -O2

all: stream_c.exe

stream_c.exe: stream.c
	$(CC) $(CFLAGS) stream.c -o stream_c.exe

sweep:
	@for i in $$(seq 512 1024 3932160);do \
	XTAG=$$((i-512)); \
	XTAG=$$((XTAG/1024)); \
	$(CC) $(CFLAGS) -DSTREAM_ARRAY_SIZE=$$i stream.c -o stream_c_$$XTAG.exe;\
	done

mt-sweep:
	@for i in $$(seq 512 1024 3932160);do \
	XTAG=$$(( (i-512) )); \
	XTAG=$$(( XTAG/1024 )); \
	$(CC) $(CFLAGS) -fopenmp -DSTREAM_ARRAY_SIZE=$$i stream.c -o openmp_stream_c_$$XTAG.exe;\
	done

clean:
	rm -f stream_c*.exe *.o openmp_stream_c*exe
