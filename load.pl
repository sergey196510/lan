#!/usr/bin/perl

use DBI;

my $dbfile = "lan.db";

my $dbh = DBI->connect("dbi:SQLite:dbname=$dbfile","","", {AutoCommit => 0});

$dbh->do("DROP TABLE attr_descr");
$dbh->do("CREATE TABLE attr_descr(id integer primary key autoincrement, type int, name text, active int default 0, bd date, descr text)");

$dbh->do("DROP TABLE attr_link");
$dbh->do("CREATE TABLE attr_link(id integer primary key autoincrement, i_id int, a_id int, type int, bd date, ld date, active int default 0, descr text)");

$dbh->do("DROP TABLE item");
$dbh->do("CREATE TABLE item(id integer primary key autoincrement, cod text unique, name text)");

sub insert_item
{
    my $cod = $_[0];
    my $name = $_[1];

    $sth = $dbh->prepare("INSERT INTO item(cod,name) VALUES(?,?)");
    $sth->execute($cod,$name) or die("Error");

    my $sth = $dbh->prepare("SELECT MAX(id) FROM item");
    $sth->execute() or die("Error");
    my @row = $sth->fetchrow_array;
    return $row[0];
}

sub insert_link
{
    my $iid = $_[0];
    my $aid = $_[1];
    my $type = $_[2];

    my $sth = $dbh->prepare("INSERT INTO attr_link(i_id, a_id, type, active) VALUES(?,?,?,1)");
    $sth->execute($iid, $aid, $type) or die("Error");
}

sub insert_descr
{
    my $name = $_[0];
    my $type = $_[1];

    my $sth = $dbh->prepare("INSERT INTO attr_descr(name,type) VALUES(?,?)");
    $sth->execute($name,$type) or die("Error");
    return get_descr($name, $type);
}

sub get_descr
{
    my $name = $_[0];
    my $type = $_[1];

    my $sth = $dbh->prepare("SELECT id FROM attr_descr WHERE name = ? AND type = ?");
    $sth->execute($name, $type) or die("Error");
    if (my @row = $sth->fetchrow_array) {
	return $row[0];
    }

    return insert_descr($name, $type);
}

sub add_descr
{
    my $id = $_[0];
    my $name = $_[1];
    my $type = $_[2];

    $pid = 0;
    if ($name) {
	$pid = get_descr($name, $type);
    }
    if ($id && $pid) {
	insert_link($id, $pid, $type);
    }
}

my $attr;

while (<>) {
    chomp;
    my @arr = split(/;/);
    $arr[1] =~ s/\"//g;
    $arr[2] =~ s/\"//g;
    $arr[3] =~ s/\"//g;
    $arr[4] =~ s/\"//g;
    $arr[5] =~ s/\"//g;
    $arr[11] =~ s/\"//g;

    my $id = insert_item($arr[2],$arr[1]);

    $type = 1; # user
    add_descr($id, $arr[11], $type);
    $type = 2; #address
    add_descr($id, $arr[4], $type);
    $type = 3; #mol
    add_descr($id, $arr[3], $type);
    $type = 4; #schet
    add_descr($id, $arr[5], $type);
}

$dbh->commit;
$dbh->disconnect;
