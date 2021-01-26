#!/usr/bin/python

import sqlite3

con = sqlite3.connect('lan.db')

f = open('cods.txt')
fd = f.readlines()

for item in fd:
    i = 0
    while item[i] == '0':
        i = i + 1
    if len(item) > 1:
        print(item[i:-1])
        cur = con.cursor()
        t = (item[i:-1],)
        cur.execute('SELECT cod FROM item WHERE cod=?',t)
        rows = cur.fetchall()
        for row in rows:
            print('Find:',row)

con.close()
