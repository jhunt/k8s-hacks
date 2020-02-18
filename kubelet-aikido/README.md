aikido - Managing Kubelets VIA Kubelets
=======================================

This little hack / experiment shows what is possible when you use
an initContainer to affect local kubelet state, via a DaemonSet
with tolerations that will let it run everywhere (including on
control nodes that are normally NoSchedule-tainted).

Happy Hacking!
