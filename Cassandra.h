#ifndef Cassandra_H
#define Cassandra_H


typedef enum{false=0,true=1} boolean;

//LES TYPES DES TERMES
typedef enum { string , integer } type_term;

//VARIABLE COURANTE
char * curIdf;
char * curPropName;
boolean currBool;
int typeLeft;
int typeRight;
int reqt;   //REQUETE
int nbrPK;  //NOMBRE DES PRIMARY KEY()
char * nameKeyspace;
char * nomTableForInsrt;
char * nomKeyspaceForInsrt;
int typeAlter;

//prototype des fonctions si vous voulez qu'on ulitise le C ou BIZON
boolean _native_type (); /*TYPE NATIVE */
boolean _collection_type();
int _liretoken();
boolean _data_type();
boolean _constant();
boolean _variable();
boolean _keyspace_name();
boolean _property_name();
boolean _property_value();
boolean _property();
boolean _LIST_PROPERTY_AUX();
boolean _LIST_PROPERTY();
boolean _properties();
boolean _LIST_TERM_AUX();
boolean _LIST_TERM();
boolean _set();
boolean _list();
boolean _function();
boolean _LIST_TERM_MAP_AUX();
boolean _LIST_TERM_MAP();
boolean _map();
boolean _collection();
boolean _term();
boolean _if_not_exists();
boolean _if_exists();
boolean _LIST_COLUMN_NAME_AUX();
boolean _LIST_COLUMN_NAME();
boolean _primary_key();
boolean _partition_key();
boolean _column_type();
boolean _column_name();
boolean _table_name();
boolean _table_option();
boolean _LIST_TABLE_OPTION_AUX();
boolean _LIST_TABLE_OPTION();
boolean _table_options();
boolean _LIST_COLUMN_DEFINITION_AUX();
boolean _column_definitions();
boolean _column_definition();
boolean _create_table_stmt();
boolean _LIST_COLUMN_DEFINITION();
boolean _LIST_DELETE_SELECTION();
boolean _delete_selection();
boolean _LIST_COLUMN_NAME_AUX();
boolean _LIST_COLUMN_NAME();
boolean _LIST_COLUMN_VALUE();
boolean _LIST_COLUMN_NAME_PRIMARY_KEY_AUX();
boolean _LIST_COLUMN_NAME_PRIMARY_KEY();
boolean _LIST_DELETE_SELECTION_AUX();
boolean _LIST_DELETE_SELECTION();
boolean _delete_selections();
boolean _delete_condition();
boolean _delete_selection();
boolean _LIST_RELATION_AUX();
boolean _LIST_RELATION();
boolean _relation();
boolean _delete_stmt();
boolean _LIST_DELETE_CONDITION_AUX();
boolean _LIST_DELETE_CONDITION();
boolean _delete_conditions();
boolean _truncate_table_stmt();
boolean _upsert_options();
boolean _LIST_UPSERT_OPTION();
boolean _upsert_options();
boolean _upsert_option();
boolean _index_class();
boolean _index_name();
boolean _use_stmt();
boolean _create_keyspace_stmt();
boolean _drop_table_stmt();
boolean _alter_keyspace_stmt();
boolean _drop_keyspace_stmt();
boolean _insert_stmt();
boolean _LIST_STATEMENT();
boolean _statement();
boolean _statement_keyspace();
boolean _statement_table();
boolean _update_stmt();
boolean _update_assignment();
boolean _update_condition();
boolean _LIST_UPDATE_ASSIGNMENT();
boolean _LIST_UPDATE_ASSIGNMENT_AUX();
boolean _update_assignments();
boolean _update_conditions();
boolean _LIST_UPDATE_CONDITION();
boolean _LIST_UPDATE_CONDITION_AUX();
boolean _alter_table_instruction();
boolean _alter_table_stmt();
boolean _SELECT_CLAUSE();
boolean _SELECT_CLAUSE_AUX();
void fin();
void affichage_resultat();
void syntaxique_erreur(char * msgErr);
#endif
	/*==========*
	 *TERMINAUX  *
	 *===========*/
#define IDF_TOKEN 1
#define STRING_TOKEN 2
#define INTEGER_TOKEN 3
#define FLOAT_TOKEN 4
#define UUID_TOKEN 5
#define BLOB_TOKEN 6
#define ADD_TOKEN 7
#define ALTER_TOKEN 8
#define AND_TOKEN 9
#define APPLY_TOKEN 10
#define BATCH_TOKEN 11
#define BEGIN_TOKEN 12
#define CLUSTERING_TOKEN 13
#define COLUMNFAMILY_TOKEN 14
#define COMPACT_TOKEN 15
#define CREATE_TOKEN 17
#define CUSTOM_TOKEN 18
#define DELETE_TOKEN 19
#define DROP_TOKEN 20
#define EXISTS_TOKEN 21
#define FALSE_TOKEN 22
#define FROM_TOKEN 23
#define IF_TOKEN 24
#define IN_TOKEN 25
#define INDEX_TOKEN 26
#define INSERT_TOKEN 27
#define INTO_TOKEN 28
#define KEY_TOKEN 29
#define KEYSPACE_TOKEN 30
#define NOT_TOKEN 31
#define ON_TOKEN 32
#define OPTIONS_TOKEN 33
#define ORDER_TOKEN 34
#define PRIMARY_TOKEN 35
#define SELECT_TOKEN 36
#define SET_TOKEN 37
#define STATIC_TOKEN 38
#define STORAGE_TOKEN 39
#define TABLE_TOKEN 40
#define TRUE_TOKEN 42
#define TRUNCATE_TOKEN 43
#define TTL_TOKEN 44
#define TYPE_TOKEN 45
#define UNLOGGED_TOKEN 46
#define UPDATE_TOKEN 47
#define USE_TOKEN 48
#define USING_TOKEN 49
#define VALUES_TOKEN 50
#define WHERE_TOKEN 51
#define WITH_TOKEN 52
#define ASCII_TYPE_TOKEN 53
#define BIGINT_TYPE_TOKEN 54
#define BLOB_TYPE_TOKEN 55
#define COUNTER_TYPE_TOKEN 56
#define DECIMAL_TYPE_TOKEN 57
#define DOUBLE_TYPE_TOKEN 58
#define FLOAT_TYPE_TOKEN 59
#define INET_TYPE_TOKEN 60
#define INT_TYPE_TOKEN 61
#define TEXT_TYPE_TOKEN 62
#define TIMESTAMP_TYPE_TOKEN 63
#define TIMEUUID_TYPE_TOKEN 64
#define UUID_TYPE_TOKEN 65
#define VARCHAR_TYPE_TOKEN 66
#define VARINT_TYPE_TOKEN 67
#define BOOLEAN_TYPE_TOKEN 68
#define EQ_TOKEN 69
#define PLUS_TOKEN 70
#define MINUS_TOKEN 71
#define MULT_TOKEN 72
#define DIV_TOKEN 73
#define EQEQ_TOKEN 74
#define PVIRG_TOKEN 75
#define POPEN_TOKEN 76
#define PCLOSE_TOKEN 77
#define VIRG_TOKEN 78
#define ETOILE_TOKEN 79
#define DIFF_TOKEN 80
#define SUP_TOKEN 81
#define INF_TOKEN 82
#define SUP_EQ_TOKEN 83
#define INF_EQ_TOKEN 84
#define AOPEN_TOKEN 85
#define ACLOSE_TOKEN 86
#define CROPEN_TOKEN 87
#define CRCLOSE_TOKEN 88
#define PINTERROGATION_TOKEN 89
#define DEUX_POINT_TOKEN 90
#define LIST_TOKEN 91
#define MAP_TOKEN 92
#define POINT_TOKEN 93
#define COUNT_TOKEN 94
#define ERREUR 555
#define couleur(param) printf("\33[%sm",param);
#define clean() printf("\33[H\033[2J");
