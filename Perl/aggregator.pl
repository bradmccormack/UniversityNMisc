#!/usr/bin/env perl

use warnings;
use strict;
use LWP::Simple;
use XML::RSS;
use Data::Dumper;
use Text::Wrap;
use HTML::Scrubber;
use DateTime;



#Take an XML:RSS object and makes sure all of it's items contain applicable author/dub-core and publish date
sub RSSConformFields{
	for my $item (@{$_[0]->{items}}) {
		if(not exists $item->{pubDate}) {
			$item->pubDate = DateTime->now;
		}
		
		if(not exists $item->{author} and not exists $item->{'dc:creator'}) {
			$item->{author} = "Author Unknown";
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
	my $stream = get($_[0]) or die "Couldn't download the stream from ",$_[0];
	$rss->parse($stream) or die "Stream downloaded OK but failed to parse."; 
	return $rss;
}	


#Takes a hashset of parsed URL data and prints it to STDout 80 cols wide
sub WriteSTDout{
	my $rssdata = $_[0];

	#Set up text formatting objects
	$Text::Wrap::columns = 80;	
	my $scrub = HTML::Scrubber->new;
	$scrub->default(0);
	
	#Make sure author/dublin-core and pubdate are applicable
	RSSConformFields($rssdata);
	
	#iterate through all items in the rss hashref and print
	for my $item (@{$rssdata->{items}}) {
		#print the content formated to col width of 80
		print wrap('', '', $item->{title}),"\n";
		print "*" x 80 , "\n";
		print wrap('','', $scrub->scrub($item->{description}));
		print "-" x 80 , "\n";
		print $item->{pubDate}, ;
		print wrap('', '', " (", $item->{author})," )"," \n" x 3;
	}
}



sub WriteHTML{
	#open the url and setup rss engine
	my $rss = FetchURL($_[1]);
	
	#Make sure author/dublin-core and pubdate are applicable
	RSSConformFields($rss);
	
	open FILE, '>:encoding(utf8)', $_[0] or die $!;
	select FILE;
	
	print <<HTML;
<table bgcolor="#0000AA" align="center" border="1" width="80%"><tr><td>
<TABLE CELLSPACING="1" CELLPADDING="4" BGCOLOR="#EEEEEE" BORDER=0 width="100%">
  <tr>
  <td valign="middle" align="center" bgcolor="#EEEEEE">
  <font color="#000000" face="Arial,Helvetica"><B><a href="$rss->{'channel'}->{'link'}">$rss->{'channel'}->{'title'}</a></B></font>
  </td>
  </tr>
  <tr><td>
HTML

    # print image
    if ($rss->{'image'}->{'link'}) {
	print <<HTML;
<center>
<p><a href="$rss->{'image'}->{'link'}"><img src="$rss->{'image'}->{'url'}" alt="$rss->{'image'}->{'title'}" border="1"
HTML
    print " width=\"$rss->{'image'}->{'width'}\""
	if $rss->{'image'}->{'width'};  print " height=\"$rss->{'image'}->{'height'}\""
	if $rss->{'image'}->{'height'}; print "></a></center><p>\n";
    }
    
	#print data
    foreach my $feedrow (@{$rss->{'items'}}) {
	next unless defined($feedrow->{'title'}) && defined($feedrow->{'link'});
	print "<li><a href=\"$feedrow->{'link'}\">$feedrow->{'title'}</a><BR>\n";
    }

    print <<HTML;
</td>
</TR>
</TABLE>
</td></tr></table>
HTML

	close FILE;
	select STDOUT;
}

sub WriteXML{
	#open the url and setup rss engine
	my $rss = FetchURL($_[1]);
	$rss ->{output} = "2.0";
	
	#Make sure author/dublin-core and pubdate are applicable
	RSSConformFields($rss);
	
	open FILE, '>:encoding(utf8)', $_[0] or die $!;
	#append to the file passed in the RSS as 2.0 
	print FILE $rss->as_string();
	close FILE;
}

sub WriteTXT{	
	#open the first arg as output
	open FILE, '>:encoding(utf8)', $_[0] or die $!;
	#redirect print to the file and reuse WriteSTDOUT
	select FILE;
	WriteContent(\&WriteSTDout, FetchURL($_[1]));
	close FILE;
	select STDOUT;
}



eval {
	if($#ARGV == -1 or $#ARGV != 1) {
		die "Usage: aggregator inputfile outputfile[.txt | .xml | .html]";
	}
	
	if(not -e $ARGV[0]) {
		die $ARGV[0]," does not exist !";

	}
	
	#read in the list of urls for processing
	open(FILE, $ARGV[0]) or die "Can't read file ", $ARGV[0],[$!]," \n";
	my @urls = <FILE>;
	close FILE;
	
	#Set the subroutine to use for writing based upon file extension
	my $writer;
	#use a bare block to emulate switch
	SWITCHEXT: {
		substr($ARGV[1], -3) eq "txt" && do {$writer = \&WriteTXT; last SWITCHEXT; };
		substr($ARGV[1], -3) eq "xml" && do {$writer = \&WriteXML; last SWITCHEXT; };
		substr($ARGV[1], -3) eq "htm" || substr($ARGV[1], -4) eq "html" &&
			do {$writer = \&WriteHTML; last SWITCHEXT; };
		die "Output file extension not supported !\n";
	}
	
	#merge all RSS feeds together
	print "Processing URLS ..";
	
	#anon aggregated hash
	my $aggFeed = {};
	for my $url (@urls) {
		my $feed =  FetchURL($url);
		
		#make a intermediary hash of the feed and aggregated feed then reassign the aggfeed after merge
		@$aggFeed{keys %$feed} = values %$feed;
	}

	#cleanup the fields author/pubdate etc
	#RSSConformFields($aggFeed);

	
	#TODO sort all items in the aggregated feed
	
	#write to the appropriate output format the agg feed
	#&$writer($ARGV[1], $aggFeed);
	
	print "RSS Aggregation complete. Output written to ", $ARGV[1],"\n" x 2;
	

} or do {
	print "Failure occurred - " , $@ , ")";
}

