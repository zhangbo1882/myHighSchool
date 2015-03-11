#!/usr/bin/perl -w
use Net::Ping;
$remote_host = $ARGV[0];
$packet_size = $ARGV[1];
$proto = $ARGV[2];
for($i = 1; $i < $packet_size; $i = $i +1)
{
	$p = Net::Ping->new("$proto","5","$packet_size");
	if($p->ping("$remote_host"))	
	{
		print "$remote_host is alive when ping($proto) $i size packet\n";
		$p->close();
	}
	else
	{
		print "$remote_host is down  when ping($proto) $i size packet\n";
		$p->close();

	}
}
