#!/usr/bin/perl -w
use Expect;
use Proc::Simple;

sub ssh{
	my $expect = Expect->new();
	$exp = Expect->spawn("ssh  10.103.10.90");
	$exp->expect(5,"User");
	$exp->send("admin\n");
	$exp->expect(5,"Password");
	$exp->send("password\n");
	$exp->expect(5, "admin");
	$exp->send("exit\n");
	$exp->expect(5,"EOF");
}
	my $proc = Proc::Simple->new();
	for(my $i = 0;$i < 1024 ;$i++)
	{
		$proc->start(sub {ssh("10.103.10.96")});
		$proc->start(sub {ssh("10.103.10.97")});

	}
