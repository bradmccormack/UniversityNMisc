#!/usr/bin/env perl

use warnings;
use strict;
use LWP::Simple;
use XML::RSS;
use Data::Dumper;
use Text::Wrap;
use HTML::Scrubber;
use DateTime;



#Takes a hashset of parsed URL data and prints it to STDout 80 cols wide
sub WriteSTDout{
	my $rssdata = $_[0];

	$Text::Wrap::columns = 80;
	
	my $scrub = HTML::Scrubber->new;
	$scrub->default(0);
	
	#iterate through all items in the rss hash 
	for my $ii (@{$rssdata->{items}}) {
		#print the content formated to col width of 80
		print wrap('', '', $ii->{title}),"\n";
		print "*" x 80 , "\n";
	
		print wrap('','', $scrub->scrub($ii->{description}));
		
		print "-" x 80 , "\n";
		if(exists $ii->{pubDate}) {
			print $ii->{pubDate}, ;
		}
		#assume the publish date is now as the RSS source didn't specify
		else {
			print DateTime->now;
		}
		#if author key exists use it else use dublin core else don't print it
		if(exists $ii->{author}) {
			print wrap('', '', $ii->{author}),") \n";
		}
		elsif(exists $ii->{"dc:creator"}) {
			print wrap('', '', $ii->{"dc:creator"}),") \n";
		}
		else
		{
			print "\n" x 3;
		}
	}
}

#Takes a reference to a subroutine which can write to txt,xml,html or stdout
#any of these implemented subroutines will all have the same args
sub WriteContent{
	#first arg is the function that does the writing
	my $func = $_[0];
	my $writefunction = \&$func;
	#second arg is the hashset to write
	my $urlhashes = $_[1];
	
	#call write function with the hashset
	&$writefunction($urlhashes);
}

#Takes a URL and returns hashref of parsed RSS
sub FetchURL{
	#Attempt to get the feed at the specified URL. Only parse it if successful.
	my $rss = XML::RSS->new();
	$rss->parse(get($_[0]));
	die "Couldn't download the feed sorry! Check your network connection.!" unless defined $rss->{items};
	return $rss;
}	

#Call writecontent with a reference to the WriteSTDout subroutine along with a parsed RSS feed
eval {
	if($#ARGV == -1 or $#ARGV >1) {
		print "Usage: reader url\n";
		die;
	}
	WriteContent(\&WriteSTDout, FetchURL($ARGV[0]));
} or do {
	print "Failure to download and/or parse the RSS feed !\n";
}




	
	
	
