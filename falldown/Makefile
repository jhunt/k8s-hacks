IMAGE ?= filefrog/k8s-hacks
TAG   ?= falldown

build:
	docker build . -t $(IMAGE):$(TAG)

push: build
	docker push $(IMAGE):$(TAG)

test: build
	@echo "testing with a 10s nap"
	docker run --rm -it $(IMAGE):$(TAG) 10 || true
