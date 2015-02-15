PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
MODULES = logical_helpers
include $(PGXS)