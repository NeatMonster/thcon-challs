IMG=misc-neatmonster-regexpress
CTN=regexpress

image:
	docker build -t $(IMG) .

build: image

run:
	docker run -d -p 5555:5555 --name $(CTN) $(IMG)

logs:
	docker logs -f $(CTN)

stop:
	docker stop $(CTN)

clean: stop
	docker rm $(CTN)

clean-all:
	docker rmi $(IMG)
