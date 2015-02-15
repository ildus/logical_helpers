#include "postgres.h"
#include "fmgr.h"
#include "replication/logical.h"
#include "replication/logicalfuncs.h"
#include "utils/pg_lsn.h"
#include "utils/inval.h"

PG_MODULE_MAGIC;
PG_FUNCTION_INFO_V1(pg_logical_slot_confirm_lsn);

Datum
pg_logical_slot_confirm_lsn(PG_FUNCTION_ARGS)
{
    Name name = PG_GETARG_NAME(0);
    XLogRecPtr lsn = PG_GETARG_LSN(1);

    CheckLogicalDecodingRequirements();
    ReplicationSlotAcquire(NameStr(*name));
    LogicalConfirmReceivedLocation(lsn);

    ReplicationSlotRelease();
    InvalidateSystemCaches();

    PG_RETURN_LSN(lsn);
}