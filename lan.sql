CREATE TABLE attr_descr(id integer primary key autoincrement, type int, name text, active int default 0, bd date, descr text, flag int default 0);
CREATE TABLE attr_link(id integer primary key autoincrement, i_id int, a_id int, type int, bd date, ld date, active int default 0, descr text, d_id int default 0, open datetime, close datetime);
CREATE TABLE item(id integer primary key autoincrement, cod text unique, name text, note text);
CREATE TABLE document(id integer primary key autoincrement, data blob);
CREATE TABLE tickets(id integer primary key autoincrement, i_id int, tm timestamp, title text, message text);
CREATE TABLE item_moves(i_id int, t_id int, prev int, next int, dt date);
