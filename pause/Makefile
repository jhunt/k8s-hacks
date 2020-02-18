IMAGE ?= filefrog/k8s-hacks
TAG   ?= pause

build:
	docker build . -t $(IMAGE):$(TAG)

push: build
	docker push $(IMAGE):$(TAG)

test: build
	@echo "testing with a 5s nap"
	timeout 5s docker run --rm $(IMAGE):$(TAG) || true
