#Logical decoding helper functions

## pg_logical_slot_confirm_lsn

Removes (confirms) all records from logical slot until specified LSN

### Installing

```
make 
sudo make install
```

### Using

```
dlr=# create function confirm_lsn(cstring, pg_lsn) returns pg_lsn as 'logical_helpers.so', 'pg_logical_slot_confirm_lsn' language c strict;
CREATE FUNCTION
dlr=# insert into test1 values (46, 'bb');
INSERT 0 1
dlr=# insert into test1 values (47, 'bb');
INSERT 0 1
dlr=# select * from pg_logical_slot_peek_changes('custom_slot', NULL, NULL, 'include_transaction', 'on');
 location  | xid  |                         data                         
-----------+------+------------------------------------------------------
 0/2E8BF90 | 3568 | begin
 0/2E8BF90 | 3568 | {"a":0,"d":{"id":46,"name":"bb"},"r":"public.test1"}
 0/2E8C078 | 3568 | commit
 0/2E8C078 | 3569 | begin
 0/2E8C078 | 3569 | {"a":0,"d":{"id":47,"name":"bb"},"r":"public.test1"}
 0/2E8C148 | 3569 | commit
(6 rows)

dlr=# select confirm_lsn('custom_slot', '0/2E8C148');
 confirm_lsn 
-------------
 0/2E8C148
(1 row)

dlr=# select * from pg_logical_slot_peek_changes('custom_slot', NULL, NULL, 'include_transaction', 'on');
 location | xid | data 
----------+-----+------
(0 rows)
```
