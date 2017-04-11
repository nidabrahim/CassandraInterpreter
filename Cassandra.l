%{
  #include "Cassandra.h"
  #include <stdio.h>
  #include <string.h>
%}
%option yylineno
%option noyywrap
HEX 	 [0-9a-fA-F]
DIGIT 	 [0-9]

%%

"="				{return EQ_TOKEN;}
"!="				{return DIFF_TOKEN;}
">"				{return SUP_TOKEN;}
"<"				{return INF_TOKEN;}
"=>"				{return SUP_EQ_TOKEN;}
"=<"				{return INF_EQ_TOKEN;}
"+"				{return PLUS_TOKEN;}
"-"				{return MINUS_TOKEN;}
"/"				{return DIV_TOKEN;}
"=="				{return EQEQ_TOKEN;}
";"				{return PVIRG_TOKEN;}
"("				{return POPEN_TOKEN;}
")"				{return PCLOSE_TOKEN;}
"{"				{return AOPEN_TOKEN;}
"}"				{return ACLOSE_TOKEN;}
"["				{return CROPEN_TOKEN;}
"]"				{return CRCLOSE_TOKEN;}
","				{return VIRG_TOKEN;}
"."				{return POINT_TOKEN;}
"*"				{return ETOILE_TOKEN;}
"add"				{return ADD_TOKEN;}
"alter"				{return ALTER_TOKEN;}
"and"				{return AND_TOKEN;}
"apply"				{return APPLY_TOKEN;}
"begin"				{return BATCH_TOKEN;}
"batch"				{return BEGIN_TOKEN;}
"clustering"			{return CLUSTERING_TOKEN;}
"columnfamily"			{return COLUMNFAMILY_TOKEN;}
"compact"			{return COMPACT_TOKEN;}
"create"			{return CREATE_TOKEN;}
"custom"			{return CUSTOM_TOKEN;}
"delete"			{return DELETE_TOKEN;}
"drop"				{return DROP_TOKEN;}
"exists"			{return EXISTS_TOKEN;}
"false"				{return FALSE_TOKEN;}
"from"				{return FROM_TOKEN;}
"if"				{return IF_TOKEN;}
"in"				{return IN_TOKEN;}
"index"				{return INDEX_TOKEN;}
"insert"			{return INSERT_TOKEN;}
"into"				{return INTO_TOKEN;}
"key"				{return KEY_TOKEN;}
"keyspace"			{return KEYSPACE_TOKEN;}
"list"				{return LIST_TOKEN;}
"map"				{return MAP_TOKEN;}
"not"				{return NOT_TOKEN;}
"on"				{return ON_TOKEN;}
"option"			{return OPTIONS_TOKEN;}
"order"				{return ORDER_TOKEN;}
"primary"			{return PRIMARY_TOKEN;}
"select"			{return SELECT_TOKEN;}
"set"				{return SET_TOKEN;}
"static"			{return STATIC_TOKEN;}
"storage"			{return STORAGE_TOKEN;}
"table"				{return TABLE_TOKEN;}
"true"				{return TRUE_TOKEN;}
"truncate"			{return TRUNCATE_TOKEN;}
"ttl"				{return TTL_TOKEN;}
"type"				{return TYPE_TOKEN;}
"unlogger"			{return UNLOGGED_TOKEN;}
"update"			{return UPDATE_TOKEN;}
"use"				{return USE_TOKEN;}
"using"				{return USING_TOKEN;}
"values"			{return VALUES_TOKEN;}
"where"				{return WHERE_TOKEN;}
"with"				{return WITH_TOKEN;}
"count"				{return COUNT_TOKEN;}
"?"				{return PINTERROGATION_TOKEN;}
":"				{return DEUX_POINT_TOKEN;}
"ascii"				{return ASCII_TYPE_TOKEN;}
"bigint"			{return BIGINT_TYPE_TOKEN;}
"blob"				{return BLOB_TYPE_TOKEN;}
"boolean"			{return BOOLEAN_TYPE_TOKEN;}
"counter"			{return COUNTER_TYPE_TOKEN;}
"decimal"			{return DECIMAL_TYPE_TOKEN;}
"double"			{return DOUBLE_TYPE_TOKEN;}
"float"				{return FLOAT_TYPE_TOKEN;}
"inet"				{return INET_TYPE_TOKEN;}
"int"				{return INT_TYPE_TOKEN;}
"text"				{return TEXT_TYPE_TOKEN;}
"timestamp"			{return TIMESTAMP_TYPE_TOKEN;}
"timeuuid"			{return TIMEUUID_TYPE_TOKEN;}
"uuid"				{return UUID_TYPE_TOKEN;}
"varchar"			{return VARCHAR_TYPE_TOKEN;}
"varint"			{return VARINT_TYPE_TOKEN;}
[a-zA-Z_][a-zA-Z0-9_]*							{ curIdf = (char*) malloc(50*sizeof(char)); strcpy(curIdf,yytext); return IDF_TOKEN;}
"-"?[0-9]+								{ typeRight = 0; rightTerm = (char*) malloc(50*sizeof(char)); strcpy(rightTerm,yytext); return INTEGER_TOKEN;}
"-"?[0-9]+("."[0-9]*)?(E[+-]?[0-9]+)?|"NaN"|"Infinity"			{return FLOAT_TOKEN;}
HEX(8)'-'HEX(4)'-'HEX(4)'-'HEX(4)'-'HEX(12)				{return UUID_TOKEN;}
'0'X(HEX)+								{return BLOB_TOKEN;}
"\'"[a-zA-Z0-9_-][a-zA-Z0-9_-]*"\'"					{ typeRight = 1;  rightTerm = (char*) malloc(50*sizeof(char)); strcpy(rightTerm,yytext); return STRING_TOKEN;}

[ \t\r\n]								{;}
.									{return ERREUR;}
%%
