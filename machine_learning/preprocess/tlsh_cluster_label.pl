#!/usr/bin/perl

##############################################################
# (C) Copyright Trend Micro
#       written by Jon Oliver
##############################################################

use strict;

my $verbose             = 0;
my $warning		= 0;

sub read_file()
{
        my $file = shift;

        my $line;
        my @lines;

        open(FILE, "<$file") or die "cannot open $file\n";
        while($line = <FILE>)
        {
                chomp($line);
                push(@lines, $line);
        }
        close(FILE);
        return(@lines);
}

sub tlsh_cluster_label($$$)
{
        my $file	= shift;
        my $cluster_file = shift;
        my $voption	= shift;

	my %cluster_hash;
	my %single_hash;

        my @cluster_lines = &read_file($cluster_file);
        my $ncluster = scalar(@cluster_lines);
	my $nsingle = 0;
	my $group = -1;
	my $ngroup = 0;
	my $ntlsh = 0;
	my $start_singletons = 0;
        for (my $li=0; $li<$ncluster; $li++) {
                my $line = $cluster_lines[$li];
		my $ldone = 0;
		my $match = ($line =~ m#^Group ([0-9]*)\t#);
		if ($match) {
			$group = int($1);
			if ($verbose >= 2) {
				print "found Group $group\n";
			}
			$ngroup ++;
			$ldone = 1;
		}
		if ($ldone == 0) {
			my $match = ($line =~ m#^([0-9ABCDEF]{70})\t#);
			if ($match) {
				if ($start_singletons) {
					die "error: found Group after n_singletons= line\n";
				}
				my $tlsh = $1;
				if ($verbose >= 2) {
					print "$tlsh	Group $group\n";
				}
				if (defined($cluster_hash{$tlsh})) {
					print "hash($tlsh) already defined\n";
				} else {
					$cluster_hash{$tlsh} = $group;
					$ntlsh ++;
				}
				$ldone = 1;
			}
		}
		if ($ldone == 0) {
			my $match = ($line =~ m#^n_singletons=#);
			if ($match) {
				$start_singletons = 1;
				$ldone = 1;
			}
		}
		if ($ldone == 0) {
			my $match = ($line =~ m#^([0-9ABCDEF]{70})$#);
			if ($match) {
				if ($start_singletons == 0) {
					die "error: found singleton before n_singletons= line\n";
				}
				my $tlsh = $1;
				if ($verbose >= 2) {
					print "$tlsh	Singleton $nsingle\n";
				}
				if (defined($single_hash{$tlsh})) {
					print "single($tlsh) already defined\n";
				} else {
					$single_hash{$tlsh} = $nsingle;
					$nsingle ++;
				}
				$ldone = 1;
			}
		}
	}
	if ($verbose) {
		print "read in $ngroup groups\n";
		print "read in $ntlsh TLSH in groups\n";
		print "read in $nsingle singletons\n";
	}

        my @tmp_lines = &read_file($file);
        my $ntmp = scalar(@tmp_lines);

        for (my $li=0; $li<$ntmp; $li++) {
                my $line = $tmp_lines[$li];
		my @cols = split("\t", $line);
		my $ncols = scalar(@cols);
		$group  = -1;
		my $single = -1;
		for (my $ci=0; $ci<$ncols; $ci++) {
			my $val = uc($cols[$ci]);
			if (defined($cluster_hash{$val})) {
				$group = $cluster_hash{$val};
				$ci = $ncols;
			}
			if (defined($single_hash{$val})) {
				$single = $single_hash{$val};
				$ci = $ncols;
			}
		}
		if ($group != -1) {
			print "Group\t" . $group  . "\t" . $line . "\n";
		} elsif ($single != -1) {
			print "Sing\t"  . $single . "\t" . $line . "\n";
		} else {
			print "NULL" . "\t" . $line . "\n";
		}
	}
}

#####################################
##       MAIN
######################################

my $file		= "";
my $cluster_file		= "";
my $voption		= 0;

sub usage()
{
        print "tlsh_cluster_label.pl [-v] -c cluster_file -f datafile\n";
        print "	add a column with the group # in each row of datafile\n";
        die;
}

my $ARGC = scalar(@ARGV);
for (my $ai=0; $ai<$ARGC; $ai++) {
        if ($ARGV[$ai] eq "-f") {
                if ($ai + 1 < $ARGC) {
                        $file = $ARGV[$ai+1];
                        $ai ++;
                } else {
                        usage();
                }
        } elsif ($ARGV[$ai] eq "-c") {
                if ($ai + 1 < $ARGC) {
                        $cluster_file = $ARGV[$ai+1];
                        $ai ++;
                } else {
                        usage();
                }
        } elsif ($ARGV[$ai] eq "-v") {
                $voption = 1;
        } else {
                print "unknown option $ARGV[$ai]\n";
                usage();
        }
}

# check file
if ($file eq "") {
        usage();
}
if (! -f $file) {
        die "cannot open file: $file\n";
}
# check cluster_file
if ($cluster_file eq "") {
        usage();
}
if (! -f $cluster_file) {
        die "cannot open cluster_file: $cluster_file\n";
}

tlsh_cluster_label($file, $cluster_file, $voption);

