filefrog/k8s-hacks:env
======================

This image provides a small web server that just spits back its
hostname to whoever requests `/`.  I wrote this to investigate
round-robin policies and load balancing in Kubernetes.

[See it on Docker Hub!][1]

Running it on Docker
--------------------

To run this in your local Docker daemon:

    docker run --rm -it -p 3000:3000 filefrog/k8s-hacks:id

The webserver _always_ listens on TCP/3000, so you'll need to
port-forward accordingly, via `-p`.


Running it on Kubernetes
------------------------

Here's an example Kubernetes `k8s.yml` resource spec that provides
a bunch of different environment variables and methods of
specifying them, to illustrate how useful this image can be.

    kubectl apply -n a-namespace -f k8s.yml

This will spin up three pods in a deployment, behind a NodePort
service (unless you change it, which you should, if you want to).

Here's what happens when I curl my local installation:

    → for x in $(seq 1 10); do curl http://██.██.██.███:3████/; done
    Hi!  My name is env-6747476d74-65wtd
    Hi!  My name is env-6747476d74-tg7jf
    Hi!  My name is env-6747476d74-dzvpz
    Hi!  My name is env-6747476d74-65wtd
    Hi!  My name is env-6747476d74-65wtd
    Hi!  My name is env-6747476d74-65wtd
    Hi!  My name is env-6747476d74-65wtd
    Hi!  My name is env-6747476d74-65wtd
    Hi!  My name is env-6747476d74-dzvpz
    Hi!  My name is env-6747476d74-tg7jf

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


[1]: https://hub.docker.com/r/filefrog/k8s-hacks/tags?page=1&name=id
