#Logical decoding helper functions

## pg_logical_slot_confirm_lsn

Removes (confirms) all records from logical slot before specified LSN

### Installing

```
make 
sudo make install
```

### Using

```
dlr=# create function confirm_lsn(cstring, pg_lsn) returns int as 'logical_helpers.so', 'pg_logical_slot_confirm_lsn' language c strict;
CREATE FUNCTION
dlr=# insert into test1 values (41, 'bb');
INSERT 0 1
dlr=# insert into test1 values (42, 'bb');
INSERT 0 1
dlr=# select * from pg_logical_slot_peek_changes('custom_slot', NULL, NULL);
 location  | xid  |                         data                         
-----------+------+------------------------------------------------------
 0/2E79368 | 3560 | {"a":0,"r":"public.test1","d":{"id":39,"name":"bb"}}
 0/2E815B0 | 3563 | {"a":0,"r":"public.test1","d":{"id":41,"name":"bb"}}
 0/2E82048 | 3564 | {"a":0,"r":"public.test1","d":{"id":42,"name":"bb"}}
(3 rows)

dlr=# select confirm_lsn('custom_slot', '0/2E82048');
 confirm_lsn 
-------------
 0/2E82048
(1 row)

dlr=# select * from pg_logical_slot_peek_changes('custom_slot', NULL, NULL);
 location  | xid  |                         data                         
-----------+------+------------------------------------------------------
 0/2E82048 | 3564 | {"a":0,"r":"public.test1","d":{"id":42,"name":"bb"}}
(1 row)
```
