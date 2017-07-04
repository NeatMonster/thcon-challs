IMG = pwn-neatmonster-heapboard
CTN = heapboard

image:
	docker build -t $(IMG) .

build: image

run:
	docker run -d -p 5555:5555 --name $(CTN) $(IMG)

logs:
	docker logs -f $(CTN)

stop:
	docker stop $(CTN)

export:
	mkdir -p export
	docker run --rm --entrypoint cat $(IMG) /home/chall/heapboard > export/heapboard

clean: stop
	docker rm $(CTN)
	rm -rf export

clean-all:
	docker rmi $(IMG)

.PHONY: image build run logs stop export clean clean-all
