filefrog/k8s-hacks:falldown
===========================

This image pretends to do some work (and indeed, the entrypoint
process continues to execute) until a certain number of seconds
have elapsed, at which point it simulates a crash and exits
non-zero.

This is great for playing with probes, testing resurrection logic,
etc., or (and this is why I originally wrote this) demonstrating
why just managing Pods in Kubernetes, raw, is a Bad Idea™.

The entrypoing, called `/waiting...` expects an optional
positional argument indicating how many seconds to "run" before
crashing.  This defaults to 30.

To run this in your local Docker daemon:

    docker run --rm -it filefrog/k8s-hacks:falldown

To specify a shorter or longer time frame:

    docker run --rm -it filefrog/k8s-hacks:falldown 5    # 5s
    docker run --rm -it filefrog/k8s-hacks:falldown 300  # 5m

The Makefile handles building pushing.  For jhunt's:

    make push

Is all that's needed for release.  If you want to build it
locally, you can instead use:

    make build

If you want to tag it to your own Dockerhub username:

    IMAGE=you-at-dockerhub/k8s-hacks make build push

By default, the image is tagged as `falldown`, since I abuse the
naming scheme of Docker Images to build a single image for the
entire `k8s-hacks` project.  You can change that by setting the
`TAG` environment variable:

   IMAGE=... TAG=latest make build push

Happy Hacking!
