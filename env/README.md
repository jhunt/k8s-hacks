filefrog/k8s-hacks:env
======================

This image is a baked wrapper around `/bin/sh -s env`, for
exploring Kubernetes pod environments.

[See it on Docker Hub!][1]

Running it on Docker
--------------------

To run this in your local Docker daemon:

    docker run --rm -it filefrog/k8s-hacks:env

To set some environment variables and see them in action:

    docker run --rm -it -e FOO=BAR filefrog/k8s-hacks:env
    docker run --rm -it -e FOO=BAR -e OUTER=$(hostname -f) filefrog/k8s-hacks:env


Running it on Kubernetes
------------------------

Here's an example Kubernetes `k8s.yml` resource spec that provides
a bunch of different environment variables and methods of
specifying them, to illustrate how useful this image can be.

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

By default, the image is tagged as `env`, since I abuse the
naming scheme of Docker Images to build a single image for the
entire `k8s-hacks` project.  You can change that by setting the
`TAG` environment variable:

   IMAGE=... TAG=latest make build push

Happy Hacking!


[1]: https://hub.docker.com/r/filefrog/k8s-hacks/tags?page=1&name=env
