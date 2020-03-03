IMAGE ?= filefrog/k8s-hacks
TAG   ?= logx

build:
	docker build . -t $(IMAGE):$(TAG)

push: build
	docker push $(IMAGE):$(TAG)

test: build
	@echo "testing a single run"
	docker run --rm -i $(IMAGE):$(TAG) 128 1 || true
