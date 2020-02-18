filefrog/k8s-hacks:pause
===========================

This image does nothing.  Quite literally.  It pauses,
indefinitely, handles some signals, but otherwise does nothing at
all.  Great for those use cases (like the [aikido hack][2]) where
you mostly just want an initContainer, not real containers.

[See it on Docker Hub!][1]


Running it on Docker
--------------------

To run this in your local Docker daemon:

    docker run --rm -it filefrog/k8s-hacks:pause


Running it on Kubernetes
------------------------

I wrote this image to make the [aikdio hack][2] work without
relying on unvetted code from upstream.  If you want to see this
image in action, go check out that little bit of DaemonSet-fu.


Building (and Publishing) to Docker Hub
---------------------------------------

The Makefile handles building pushing.  For jhunt's:

    make push

Is all that's needed for release.  If you want to build it
locally, you can instead use:

    make build

If you want to tag it to your own Dockerhub username:

    IMAGE=you-at-dockerhub/k8s-hacks make build push

By default, the image is tagged as `pause`, since I abuse the
naming scheme of Docker Images to build a single image for the
entire `k8s-hacks` project.  You can change that by setting the
`TAG` environment variable:

   IMAGE=... TAG=latest make build push

Happy Hacking!


[1]: https://hub.docker.com/r/filefrog/k8s-hacks/tags?page=1&name=pause
[2]: https://github.com/jhunt/k8s-hacks/tree/master/kubelet-aikido
