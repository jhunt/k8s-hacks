aikido - Managing Kubelets VIA Kubelets
=======================================

This little hack / experiment shows what is possible when you use
an initContainer to affect local kubelet state, via a DaemonSet
with tolerations that will let it run everywhere (including on
control nodes that are normally NoSchedule-tainted).

So far, we've run the following experiments:

toy.yml - Show What We Can Do
-----------------------------

The original proof-of-concept, `toy.yml` is a DaemonSet that puts
a file on each kubelet host, with the name of the pod inside of
it.  This works great for demos / initial exploration into this
pattern.

named-admin.yml - Provision a root-like SSH Account
---------------------------------------------------

The initial impetus for this pattern was to be able to put my
named `jhunt` user on managed Kubernetes clusters like Linode's
LKE, so that I could get dmesg output from the kernel ring buffer.

Since then, it's proven itself quite useful.  Remember to swap in
**YOUR INFORMATION** for mine, unless you are trying to give me
unfettered access to your k8s clusters...

sysctl.yml - Kernel Tuning via DaemonSet
----------------------------------------

I did this for a colleague, and ended up blogging about it.  This
particular feat of cleverness does not require a host mount at
all, but it does need to be privileged as it writes to `/proc`
when it calls `sysctl`.



Happy Hacking!
