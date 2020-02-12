IMAGE ?= filefrog/k8s-hacks
TAG   ?= id

build:
	docker build . -t $(IMAGE):$(TAG)

push: build
	docker push $(IMAGE):$(TAG)

test: build
	docker run --rm -it $(IMAGE):$(TAG)
