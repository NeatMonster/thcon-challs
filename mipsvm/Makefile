IMG=reverse-neatmonster-mipsvm

export:
	mkdir -p export; docker build -t $(IMG) .
	docker run --rm --entrypoint cat $(IMG) /home/build/bin/unpack > export/unpack

FLAG=THC{test_flag_please_ignore}
LFSR_KEY=F11EDEC1A551F1ED
CHACHA_KEY=3201ScottBlvdSantaClaraCA95054US

build: check utils payload challenge mipsvm unpack

PREFIX=mipsel-elf
CC=$(PREFIX)-gcc
AS=$(PREFIX)-as
LD=$(PREFIX)-ld
STRIP=$(PREFIX)-strip
OBJDUMP=$(PREFIX)-objdump
OBJCOPY=$(PREFIX)-objcopy

STATIC=-static -nostdlib -nostartfiles -nodefaultlibs -nostdinc -ffreestanding
INCLUDE=-I bin/ -I lib/ -I src/
MIPSFLAGS=$(STATIC) $(INCLUDE) -mips1 -Wl,-T,src/linker.ld
i386FLAGS=$(STATIC) $(INCLUDE) -Wall -O2 -D STATIC

check:
	@which $(CC) > /dev/null
	@which $(AS) > /dev/null
	@which $(LD) > /dev/null
	@which $(STRIP) > /dev/null
	@which $(OBJDUMP) > /dev/null
	@which $(OBJCOPY) > /dev/null

utils:
	mkdir -p bin
	gcc lib/elf_util.c -o bin/elf_util
	gcc lib/lfsr_util.c -o bin/lfsr_util
	gcc lib/chacha_util.c lib/chacha.c -o bin/chacha_util
	gcc lib/lz4_util.c lib/lz4.c -o bin/lz4_util

payload:
	echo "$(FLAG)" > bin/flag.txt
	cd bin; zip payload.zip flag.txt
	dd if=/dev/zero of=bin/payload.zip bs=1 count=1 seek=8192

challenge:
	bin/lfsr_util $(LFSR_KEY) bin/payload.zip bin/payload
	cd bin; xxd -i payload > payload.c
	sed -i -e 's/unsigned int \(\w\+\) = \(\w\+\);/#define \1 \2/g' bin/payload.c
	
	$(CC) $(MIPSFLAGS) src/challenge.c src/libmips.c -o bin/challenge.elf
	$(OBJCOPY) -O binary -j .text -j .rodata -j .data bin/challenge.elf bin/challenge
	dd if=/dev/zero of=bin/challenge bs=1 count=1 seek=65536

mipsvm:
	bin/chacha_util $(CHACHA_KEY) bin/challenge bin/memory
	cd bin; xxd -i memory > memory.c
	sed -i -e 's/unsigned int \(\w\+\) = \(\w\+\);/#define \1 \2/g' bin/memory.c

	echo "#define CHACHA_KEY \"$(CHACHA_KEY)\"" >> bin/memory.c
	gcc $(i386FLAGS) src/mipsvm.c src/mipsvm_handlers.c src/libi386.c src/start.s lib/chacha.c -o bin/mipsvm.elf
	objcopy -j .text -j .rodata -j .data -j .bss bin/mipsvm.elf bin/mipsvm
	strip bin/mipsvm

unpack:
	bin/elf_util bin/mipsvm bin/segments.c
	echo -n "#define main_addr 0x" >> bin/segments.c
	readelf -s bin/mipsvm.elf | grep main | awk '{print $$2}' >> bin/segments.c

	gcc $(i386FLAGS) -Wl,-z,max-page-size=0x10000,-Ttext-segment=0x10000 \
		src/unpack.c src/libi386.c src/start.s lib/lz4.c -o bin/unpack
	objcopy -R '.note.gnu.build-id' -R '.comment' bin/unpack
	strip bin/unpack

clean:
	rm -f bin/*
