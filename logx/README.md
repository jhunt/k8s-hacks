filefrog/k8s-hacks:logx
=======================

This image generates a fixed-size chunk of standard error output
once a second.  You can specify how big these chunks are via the
first argument to the container.  By default, output is generated
_ad infinitum_, but you can place an upper limit on the number of
runs with a second (numeric) parameter.

[See it on Docker Hub!][1]

I wrote this to stress test some Kubernetes clusters and their
logging configuration.  I had a sneaking suspicion that one of the
clusters I was evaluating wasn't placing resource usage limits on
container logs, and I needed a way to make this incredibly
apparent.

Don't run this on a cluster you care about.

Do run this on a cluster you _want_ to care about.


Running it on Docker
--------------------

To run this in your local Docker daemon:

    docker run --rm -it filefrog/k8s-hacks:logx

To change the default output size (emitted _once per second_):

    docker run --rm -it filefrog/k8s-hacks:logx 65536    # 64Ki

To limit the number of times the image sleeps-and-loops:

    docker run --rm -it filefrog/k8s-hacks:logx 8192 100

Running it on Kubernetes
------------------------

My initial reason for building this image was to quickly point out
misconfigured Kubernetes clusters.  To that end, the repo comes
with a `k8s.yml` resource spec that defines a single-container pod
that emits logging nonsense at 100Ki/s.

    kubectl apply -n a-namespace -f k8s.yml


Building (and Publishing) to Docker Hub
---------------------------------------

The Makefile handles building pushing.  For jhunt's:

    make push

Is all that's needed for release.  If you want to build it
locally, you can instead use:

    make build

If you want to tag it to your own Dockerhub username:

    IMAGE=you-at-dockerhub/k8s-hacks make build push

By default, the image is tagged as `logx`, since I abuse the
naming scheme of Docker Images to build a single image for the
entire `k8s-hacks` project.  You can change that by setting the
`TAG` environment variable:

   IMAGE=... TAG=latest make build push

Happy Hacking!


[1]: https://hub.docker.com/r/filefrog/k8s-hacks/tags?page=1&name=logx
