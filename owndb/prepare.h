#ifndef DB_PREPARE_H
#define DB_PREPARE_H

#include "statement.h"
#include "stringbuffer.h"

enum Prepare
{
	OK_PREPARE,
	ERR_INVALID_STATEMENT,
	ERR_SYNTAX_ERROR
};

typedef enum Prepare PrepareResult;

PrepareResult
prepare_statement(StringBuffer* input, Statement* statement);

#endif