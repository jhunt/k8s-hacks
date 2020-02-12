#!/usr/bin/env perl
use strict;
use warnings;
use Dancer;

$SIG{TERM} = $SIG{INT} = sub {
	print STDERR "signal caught; terminating...\n";
	exit 0;
};

get '/' => sub {
	print STDERR "handling request for / ...\n";
	"Hi!  My name is $ENV{HOSTNAME}\n";
};

dance;
