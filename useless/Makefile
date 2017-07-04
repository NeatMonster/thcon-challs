IMG = web-neatmonster-useless
CTN = useless

image:
	docker build -t $(IMG) .

build: image

run:
	docker run --privileged=true -d -p 8080:8080 --name $(CTN) $(IMG)

logs:
	docker logs -f $(CTN)

stop:
	docker stop $(CTN)

clean: stop
	docker rm $(CTN)

clean-all:
	docker rmi $(IMG)

.PHONY: image build run logs stop clean clean-all
