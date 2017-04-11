# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "Cassandra.h"
# include "CassandraErreur.h"

extern int yylex();
extern char* yytext;
int yylineno;
int token;
boolean follow_token=false;
int type;

boolean isError = false;
extern char * term="";
extern char * rightTerm="";



	/*=================================================================================*
	 *                              token : VAL                                        *
	 *=================================================================================*/

int _liretoken()
{
	if (follow_token)
	{
	 follow_token = false; // RAZ du marqueur de sur-lecture
	 return token; // renvoie du token déjà lu !
	}else
	{
	 return yylex();
	}
}

	/*======================================================================================================*
	 * native_type : 'ascii'| 'bigint'| 'blob'| 'boolean'| 'counter'|  'decimal'| 'double'  		*
         *		 |'float'| 'inet'| 'int'| 'text'| 'timestamp'| 'timeuuid' | 'uuid'| 'varchar'| 'varint' *
	 *======================================================================================================*/

boolean _native_type ()
{
	boolean result;

	switch(token)
	{
	  case ASCII_TYPE_TOKEN:
		result=true;
		break;
	  case BIGINT_TYPE_TOKEN:
		result=true;
		break;
	  case BLOB_TYPE_TOKEN:
		result=true;
		break;
	  case BOOLEAN_TYPE_TOKEN:
		result=true;
		break;
	  case DECIMAL_TYPE_TOKEN:
		result=true;
		break;
	  case COUNTER_TYPE_TOKEN:
		result=true;
		break;
	  case DOUBLE_TYPE_TOKEN:
		result=true;
		break;
	  case FLOAT_TYPE_TOKEN:
		result=true;
		break;
	  case INET_TYPE_TOKEN:
		result=true;
		break;
	  case INT_TYPE_TOKEN:
		result=true;
		break;
	  case TEXT_TYPE_TOKEN:
		result=true;
		break;
	  case TIMESTAMP_TYPE_TOKEN:
		result=true;
		break;
	  case TIMEUUID_TYPE_TOKEN:
		result=true;
		break;
	  case UUID_TYPE_TOKEN:
		result=true;
		break;
	  case VARCHAR_TYPE_TOKEN:
		result=true;
		break;
	  case VARINT_TYPE_TOKEN:
		result=true;
		break;
	  default:
		result=false;
	}
    return result;
}

	/*=================================================================================*
	 *		constant : STRING | INTEGER | FLOAT | bool | UUID | BLOB           *
	 *=================================================================================*/
boolean _constant()
{
	boolean result;

	switch(token)
	{
	  case STRING_TOKEN:
				//Créer une erreurs sémantique lorsque curPropName = durable_writes ( car il attend soit true ou false )
				if( reqt==1 && strcmp(curPropName,"durable_writes") == 0 ) inserer_optionsError(DURABLE_WRITESERROR_NOTBOOL,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = read_repair_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"read_repair_chance") == 0 ) inserer_optionsError(READREPAIRVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = dclocal_read_repair_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"dclocal_read_repair_chance") == 0 ) inserer_optionsError(DCLOCALREADVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = bloom_filter_fp_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"bloom_filter_fp_chance") == 0 ) inserer_optionsError(BLOOMFILTERVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = gc_grace_seconds  ( car il attend int )
    		if( reqt == 2 && strcmp(curPropName,"gc_grace_seconds") == 0 ) inserer_optionsError(GCGRACEVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = default_time_to_live   ( car il attend int )
    		if( reqt == 2 && strcmp(curPropName,"default_time_to_live") == 0 ) inserer_optionsError(TIMETOLIVEVALUE_NOTCOMPATIBLE,yylineno);
        //Marquer le type
				typeRight = 1;
				result=true;
		break;

	  case INTEGER_TOKEN:
				//Créer une erreurs sémantique lorsque curPropName = durable_writes ( car il attend soit true ou false )
				if( reqt==1 && strcmp(curPropName,"durable_writes") == 0 ) inserer_optionsError(DURABLE_WRITESERROR_NOTBOOL,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = comment ( car il attend string )
    		if( reqt == 2 && strcmp(curPropName,"comment") == 0 ) inserer_optionsError(COMMENTVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = read_repair_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"read_repair_chance") == 0 ) inserer_optionsError(READREPAIRVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = dclocal_read_repair_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"dclocal_read_repair_chance") == 0 ) inserer_optionsError(DCLOCALREADVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = bloom_filter_fp_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"bloom_filter_fp_chance") == 0 ) inserer_optionsError(BLOOMFILTERVALUE_NOTCOMPATIBLE,yylineno);

				typeRight = 0;
				result=true;
		break;

	  case FLOAT_TOKEN:
			//Créer une erreurs sémantique lorsque curPropName = durable_writes ( car il attend soit true ou false )
			if( reqt==1 && strcmp(curPropName,"durable_writes") == 0 ) inserer_optionsError(DURABLE_WRITESERROR_NOTBOOL,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = comment ( car il attend string )
  		if( reqt == 2 && strcmp(curPropName,"comment") == 0 ) inserer_optionsError(COMMENTVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = gc_grace_seconds  ( car il attend int )
  		if( reqt == 2 && strcmp(curPropName,"gc_grace_seconds") == 0 ) inserer_optionsError(GCGRACEVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = default_time_to_live   ( car il attend int )
  		if( reqt == 2 && strcmp(curPropName,"default_time_to_live") == 0 ) inserer_optionsError(TIMETOLIVEVALUE_NOTCOMPATIBLE,yylineno);

			isError = true;
			result=true;
		break;

		case TRUE_TOKEN:
      //Créer une erreurs sémantique lorsque curPropName = comment ( car il attend string )
      if( reqt == 2 && strcmp(curPropName,"comment") == 0 ) inserer_optionsError(COMMENTVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = read_repair_chance ( car il attend float )
  		if( reqt == 2 && strcmp(curPropName,"read_repair_chance") == 0 ) inserer_optionsError(READREPAIRVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = dclocal_read_repair_chance ( car il attend float )
  		if( reqt == 2 && strcmp(curPropName,"dclocal_read_repair_chance") == 0 ) inserer_optionsError(DCLOCALREADVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = bloom_filter_fp_chance ( car il attend float )
  		if( reqt == 2 && strcmp(curPropName,"bloom_filter_fp_chance") == 0 ) inserer_optionsError(BLOOMFILTERVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = gc_grace_seconds  ( car il attend int )
  		if( reqt == 2 && strcmp(curPropName,"gc_grace_seconds") == 0 ) inserer_optionsError(GCGRACEVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = default_time_to_live   ( car il attend int )
  		if( reqt == 2 && strcmp(curPropName,"default_time_to_live") == 0 ) inserer_optionsError(TIMETOLIVEVALUE_NOTCOMPATIBLE,yylineno);

			currBool = true;
			isError = true;
			result=true;
		break;

		case FALSE_TOKEN:
      //Créer une erreurs sémantique lorsque curPropName = comment ( car il attend string )
      if( reqt == 2 && strcmp(curPropName,"comment") == 0 ) inserer_optionsError(COMMENTVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = read_repair_chance ( car il attend float )
  		if( reqt == 2 && strcmp(curPropName,"read_repair_chance") == 0 ) inserer_optionsError(READREPAIRVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = dclocal_read_repair_chance ( car il attend float )
  		if( reqt == 2 && strcmp(curPropName,"dclocal_read_repair_chance") == 0 ) inserer_optionsError(DCLOCALREADVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = bloom_filter_fp_chance ( car il attend float )
  		if( reqt == 2 && strcmp(curPropName,"bloom_filter_fp_chance") == 0 ) inserer_optionsError(BLOOMFILTERVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = gc_grace_seconds  ( car il attend int )
  		if( reqt == 2 && strcmp(curPropName,"gc_grace_seconds") == 0 ) inserer_optionsError(GCGRACEVALUE_NOTCOMPATIBLE,yylineno);
      //Créer une erreurs sémantique lorsque curPropName = default_time_to_live   ( car il attend int )
  		if( reqt == 2 && strcmp(curPropName,"default_time_to_live") == 0 ) inserer_optionsError(TIMETOLIVEVALUE_NOTCOMPATIBLE,yylineno);

			currBool = false;
			isError = true;
			result=true;
		break;

	  case UUID_TOKEN:
				//Créer une erreurs sémantique lorsque curPropName = durable_writes ( car il attend soit true ou false )
				if( reqt==1 && strcmp(curPropName,"durable_writes") == 0 ) inserer_optionsError(DURABLE_WRITESERROR_NOTBOOL,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = comment ( car il attend string )
    		if( reqt == 2 && strcmp(curPropName,"comment") == 0 ) inserer_optionsError(COMMENTVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = read_repair_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"read_repair_chance") == 0 ) inserer_optionsError(READREPAIRVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = dclocal_read_repair_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"dclocal_read_repair_chance") == 0 ) inserer_optionsError(DCLOCALREADVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = bloom_filter_fp_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"bloom_filter_fp_chance") == 0 ) inserer_optionsError(BLOOMFILTERVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = gc_grace_seconds  ( car il attend int )
    		if( reqt == 2 && strcmp(curPropName,"gc_grace_seconds") == 0 ) inserer_optionsError(GCGRACEVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = default_time_to_live   ( car il attend int )
    		if( reqt == 2 && strcmp(curPropName,"default_time_to_live") == 0 ) inserer_optionsError(TIMETOLIVEVALUE_NOTCOMPATIBLE,yylineno);

				isError = true;
				result=true;
		break;

	  case BLOB_TOKEN:
				//Créer une erreurs sémantique lorsque curPropName = durable_writes ( car il attend soit true ou false )
				if( reqt==1 && strcmp(curPropName,"durable_writes") == 0 ) inserer_optionsError(DURABLE_WRITESERROR_NOTBOOL,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = comment ( car il attend string )
    		if( reqt == 2 && strcmp(curPropName,"comment") == 0 ) inserer_optionsError(COMMENTVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = read_repair_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"read_repair_chance") == 0 ) inserer_optionsError(READREPAIRVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = dclocal_read_repair_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"dclocal_read_repair_chance") == 0 ) inserer_optionsError(DCLOCALREADVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = bloom_filter_fp_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"bloom_filter_fp_chance") == 0 ) inserer_optionsError(BLOOMFILTERVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = gc_grace_seconds  ( car il attend int )
    		if( reqt == 2 && strcmp(curPropName,"gc_grace_seconds") == 0 ) inserer_optionsError(GCGRACEVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = default_time_to_live   ( car il attend int )
    		if( reqt == 2 && strcmp(curPropName,"default_time_to_live") == 0 ) inserer_optionsError(TIMETOLIVEVALUE_NOTCOMPATIBLE,yylineno);

				isError = true;
				result=true;
		break;

	  default:
		result=false;
	}
    return result;
}

	/*=================================================================================*
	 *		data_type : native_type | collection_type | STRING                 *
	 *=================================================================================*/
boolean _data_type()
{
	boolean result;
	if(_native_type())
	{
	  result=true;
	}else
	{
	     if(token==STRING_TOKEN)
	     {
	       result=true;
	     }else
	     {
	          if(_collection_type())
		  {
			result=true;
		  }else
		  {
		  	result=false;
		  }
	      }
	}
     return result;
}

	/*======================================================================================================================*
	 *collection_type : 'list' '<' native_type '>'| 'set' '<' native_type '>'| 'map' '<' native_type ',' native_type '>'    *
	 *======================================================================================================================*/
boolean _collection_type()
{
	boolean result;
	if(token==LIST_TOKEN)
	{
		  token=_liretoken();
		  if(token==INF_TOKEN)
		  {
		     	  token=_liretoken();
			  if(_native_type())
			  {
			     	  token=_liretoken();
				  if(token==SUP_TOKEN)
				  {
				     result=true;

				  }else
				  {
				     result=false;
				  }
			  }else
			  {
			     result=false;
			  }
		  }else
		  {
		     result=false;
		  }
	}else
	{
	     if(token==SET_TOKEN)
	     {
	          token=_liretoken();
		  if(token==INF_TOKEN)
		  {
		     	  token=_liretoken();
			  if(_native_type())
			  {
			     	  token=_liretoken();
				  if(token==SUP_TOKEN)
				  {
				     result=true;

				  }else
				  {
				     result=false;
				  }
			  }else
			  {
			     result=false;
			  }
		  }else
		  {
		     result=false;
		  }
	     }else
	     {
	          if(token==MAP_TOKEN)
		  {
			  token=_liretoken();
			  if(token==INF_TOKEN)
			  {
			     	  token=_liretoken();
				  if(_native_type())
				  {
				     	  token=_liretoken();
					  if(token==VIRG_TOKEN)
					  {
						  token=_liretoken();
						  if(_native_type())
						  {
						     	  token=_liretoken();
							  if(token==SUP_TOKEN)
							  {
							     result=true;
							  }else
							  {
							     result=false;
							  }
						  }else
						  {
						     result=false;
						  }
					  }else
					  {
					     result=false;
					  }
				  }else
				  {
				     result=false;
				  }
			  }else
			  {
			     result=false;
			  }
		  }else
		  {
		  	result=false;
		  }
	      }
	}
     return result;
}

	/*=================================================================================*
	 *				property_name : IDENTIFIER  		           *
	 *=================================================================================*/
boolean _property_name()
{
	boolean result;
	if(token==IDF_TOKEN)
	{
	  result=true;
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *		property_value : IDENTIFIER | constant | map  		           *
	 *=================================================================================*/
boolean _property_value()
{
	boolean result;
	if(token==IDF_TOKEN)
	{

		//Creer une erreurs sémantique lorsque curPropName = replication ( car il attend MAP et non pas IDF )
		if( reqt==1 && strcmp(curPropName,"replication") == 0 ) inserer_optionsError(REPLICATIONERROR_IDF,yylineno);
		//Créer une erreurs sémantique lorsque curPropName = durable_writes ( car il attend soit true ou false )
		if( reqt==1 && strcmp(curPropName,"durable_writes") == 0 ) inserer_optionsError(DURABLE_WRITESERROR_NOTBOOL,yylineno);
    //Créer une erreurs sémantique lorsque curPropName = comment ( car il attend string )
		if( reqt == 2 && strcmp(curPropName,"comment") == 0 ) inserer_optionsError(COMMENTVALUE_NOTCOMPATIBLE,yylineno);
    //Créer une erreurs sémantique lorsque curPropName = read_repair_chance ( car il attend float )
		if( reqt == 2 && strcmp(curPropName,"read_repair_chance") == 0 ) inserer_optionsError(READREPAIRVALUE_NOTCOMPATIBLE,yylineno);
    //Créer une erreurs sémantique lorsque curPropName = dclocal_read_repair_chance ( car il attend float )
		if( reqt == 2 && strcmp(curPropName,"dclocal_read_repair_chance") == 0 ) inserer_optionsError(DCLOCALREADVALUE_NOTCOMPATIBLE,yylineno);
    //Créer une erreurs sémantique lorsque curPropName = bloom_filter_fp_chance ( car il attend float )
		if( reqt == 2 && strcmp(curPropName,"bloom_filter_fp_chance") == 0 ) inserer_optionsError(BLOOMFILTERVALUE_NOTCOMPATIBLE,yylineno);
    //Créer une erreurs sémantique lorsque curPropName = gc_grace_seconds  ( car il attend int )
		if( reqt == 2 && strcmp(curPropName,"gc_grace_seconds") == 0 ) inserer_optionsError(GCGRACEVALUE_NOTCOMPATIBLE,yylineno);
    //Créer une erreurs sémantique lorsque curPropName = default_time_to_live   ( car il attend int )
		if( reqt == 2 && strcmp(curPropName,"default_time_to_live") == 0 ) inserer_optionsError(TIMETOLIVEVALUE_NOTCOMPATIBLE,yylineno);
    //Créer une erreurs sémantique lorsque curPropName = compression ( car il attend map )
		if( reqt == 2 && strcmp(curPropName,"compression") == 0 ) inserer_optionsError(COMPRESSIONVALUE_NOTCOMPATIBLE,yylineno);
    //Créer une erreurs sémantique lorsque curPropName = caching  ( car il attend map )
		if( reqt == 2 && strcmp(curPropName,"caching") == 0 ) inserer_optionsError(CACHINGVALUE_NOTCOMPATIBLE,yylineno);
    //Créer une erreurs sémantique lorsque curPropName = compaction   ( car il attend map )
		if( reqt == 2 && strcmp(curPropName,"compaction") == 0 ) inserer_optionsError(COMPACTIONVALUE_NOTCOMPATIBLE,yylineno);

	  result=true;
	}else
	{
	     if(_constant())
	     {

				 //Creer une erreurs sémantique lorsque curPropName = replication ( car il attend MAP et non pas CONSTANT )
	 			if( reqt==1 && strcmp(curPropName,"replication") == 0 ) inserer_optionsError(REPLICATIONERROR_CONST,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = compression ( car il attend map )
    		if( reqt == 2 && strcmp(curPropName,"compression") == 0 ) inserer_optionsError(COMPRESSIONVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = caching  ( car il attend map )
    		if( reqt == 2 && strcmp(curPropName,"caching") == 0 ) inserer_optionsError(CACHINGVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = compaction   ( car il attend map )
    		if( reqt == 2 && strcmp(curPropName,"compaction") == 0 ) inserer_optionsError(COMPACTIONVALUE_NOTCOMPATIBLE,yylineno);


				if( reqt==2 && strcmp(curPropName,"comment")== 0 )
				{
						//INSERER LA PROPRIETY DANS LA LISTE PROPERTIES TABLERI
						ajout_Proprietes(&(tableRI->proprietes),curPropName,NULL,0,yytext,0,0);


				}
				if( reqt==2 && ( strcmp(curPropName,"gc_grace_seconds")== 0 || strcmp(curPropName,"default_time_to_live")== 0 )  )
				{
						//INSERER LA PROPRIETY DANS LA LISTE PROPERTIES TABLERI
						ajout_Proprietes(&(tableRI->proprietes),curPropName,NULL,0,"\0",0,atoi(yytext));


				}

				if( reqt==2 && ( strcmp(curPropName,"read_repair_chance")== 0 || strcmp(curPropName,"dclocal_read_repair_chance")== 0 || strcmp(curPropName,"bloom_filter_fp_chance")== 0 )  )
				{
						//INSERER LA PROPRIETY DANS LA LISTE PROPERTIES TABLERI
						ajout_Proprietes(&(tableRI->proprietes),curPropName,NULL,0,"\0",atoi(yytext),0);

				}
				if( reqt==1 && strcmp(curPropName,"durable_writes")== 0 )
				{
						//INSERER LA PROPRIETY DANS LA LISTE PROPERTIES TABLERI
							ajout_Proprietes(&(keyspaceRI->proprietes),curPropName,NULL,atoi(yytext),"\0",0,0);

				}

	       result=true;
	     }else
	     {

				 	//MAP EST VIDE
 					mapValue = NULL;
					valrMaps = NULL;

	      if(_map())
		  {

				//Créer une erreurs sémantique lorsque curPropName = durable_writes ( car il attend soit true ou false )
				if( reqt==1 && strcmp(curPropName,"durable_writes") == 0 ) inserer_optionsError(DURABLE_WRITESERROR_NOTBOOL,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = comment ( car il attend string )
    		if( reqt == 2 && strcmp(curPropName,"comment") == 0 ) inserer_optionsError(COMMENTVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = read_repair_chance ( car il attend float )
        if( reqt == 2 && strcmp(curPropName,"read_repair_chance") == 0 ) inserer_optionsError(READREPAIRVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = dclocal_read_repair_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"dclocal_read_repair_chance") == 0 ) inserer_optionsError(DCLOCALREADVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = bloom_filter_fp_chance ( car il attend float )
    		if( reqt == 2 && strcmp(curPropName,"bloom_filter_fp_chance") == 0 ) inserer_optionsError(BLOOMFILTERVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = gc_grace_seconds  ( car il attend int )
    		if( reqt == 2 && strcmp(curPropName,"gc_grace_seconds") == 0 ) inserer_optionsError(GCGRACEVALUE_NOTCOMPATIBLE,yylineno);
        //Créer une erreurs sémantique lorsque curPropName = default_time_to_live   ( car il attend int )
    		if( reqt == 2 && strcmp(curPropName,"default_time_to_live") == 0 ) inserer_optionsError(TIMETOLIVEVALUE_NOTCOMPATIBLE,yylineno);


				if( reqt==1 && strcmp(curPropName,"replication") == 0 )
				{
						//INSERER LA PROPRIETY Durable_writes DANS LA LISTE
						inserer_propertyNode_replication(mapValue);
						ajout_Proprietes(&(keyspaceRI->proprietes),curPropName,valrMaps,0,"\0",0,0);
				}

				if( reqt==2 && ( strcmp(curPropName,"compaction")== 0 || strcmp(curPropName,"compression")== 0 || strcmp(curPropName,"caching")== 0 ) )
				{
						//INSERER LA PROPRIETY DANS LA LISTE PROPERTIES TABLERI
						ajout_Proprietes(&(tableRI->proprietes),curPropName,valrMaps,0,"\0",0,0);

				}


			result=true;
		  }else
		  {
		  	result=false;
		  }
	      }
	}
     return result;
}

	/*=================================================================================*
	 *		property : property_name '=' property_value  		           *
	 *=================================================================================*/
boolean _property()
{
	boolean result;
	if(_property_name())
	{
	    token=_liretoken();
		  if(token==EQ_TOKEN)
		  {
						//Le nom de la PROPERTY_NAME :
						curPropName = (char*) malloc(50*sizeof(char));
						//Récuperer PROPERTY_NAME : replication ou durable_writes dans curPropName
						strcpy(curPropName, curIdf);


						if( reqt==1 && strcmp(curPropName,"replication") != 0 && strcmp(curPropName,"durable_writes") != 0 )
						{
							//Créer une erreurs sémantique lorsque curPropName != durable_writes et replication
							inserer_optionsError(INVALIDKEYSPACEPROPERTY,yylineno);
						}

            //VERIFIER SI LES OPTIONS DU TABLE SONT VALIDE
            if(reqt == 2) isTableOptionsValid(yylineno);


		     	  token=_liretoken();

			  if(_property_value())
			  {

					if( reqt==1 && strcmp(curPropName,"durable_writes") == 0 )
					{
							//INSERER LA PROPRIETY Durable_writes DANS LA LISTE
							inserer_propertyNode_durableWrites(currBool);
					}

			    result=true;

			  }else
			  {
			     result=false;
			  }
		  }else
		  {
		     result=false;
		  }
	}else
	{
	  result=false;
	}
   return result;
}

	/*=================================================================================*
	 *		LIST_PROPERTY_AUX : K_AND LIST_PROPERTY | epsilone		   *
	 *=================================================================================*/
boolean _LIST_PROPERTY_AUX()
{
 boolean result;
	if(token == PVIRG_TOKEN || token == APPLY_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == AND_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_PROPERTY())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *			LIST_PROPERTY : property LIST_PROPERTY_AUX		   *
	 *=================================================================================*/
boolean _LIST_PROPERTY()
{
 boolean result;
	if(_property())
	{
	token=_liretoken();
	result=_LIST_PROPERTY_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *				properties : LIST_PROPERTY		  	   * FOLOW : K_APPLY | ';'
	 *=================================================================================*/
boolean _properties()
{
boolean result;
	if(_LIST_PROPERTY())
	{
	result=true;
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *			variable : '?' | ':' IDENTIFIER  		           *
	 *=================================================================================*/
boolean _variable()
{
	boolean result;
	if(token==PINTERROGATION_TOKEN)
	{
	  result=true;
	}else
	{
	     if(token==DEUX_POINT_TOKEN)
	     {
		  token=_liretoken();
	          if(token==IDF_TOKEN)
		  {
			result=true;
		  }else
		  {
		  	result=false;
		  }
	     }else
	     {
	        result=false;
	     }
	}
     return result;
}


	/*=================================================================================*
	 *		term : constant | collection | variable | function 		   *
	 *=================================================================================*/
boolean _term()
{
	boolean result;
	if(_constant())
	{
		//TERMS KEYSPACE
		if(isError) {
										inserer_optionsError(INVALIDKEYSPACETERM,yylineno);
										isError = false;
								}

	  result=true;
	}else
	{
			 //TERMS KEYSPACE ERROR
			 if( reqt == 1 && strcmp(curPropName,"replication") == 0 )
			 {
				 //Créer une erreurs sémantique lorsque curPropName == replication et les termes ne sont pas des constantes
				 inserer_optionsError(INVALIDKEYSPACETERM,yylineno);
			 }

	     if(_variable())
	     {
	       result=true;
	     }else
	     {
	          if(_collection())
		  {
			result=true;
		  }else
		  {
		  	  if(_function())
			  {
				result=true;
			  }else
			  {
			  	result=false;
			  }
		  }
	      }
	}
     return result;
}

	/*=================================================================================*
	 *			collection : map | set | list 				   *
	 *=================================================================================*/
boolean _collection()
{
	boolean result;
	if(_map())
	{
	  result=true;
	}else
	{
	     if(_set())
	     {
	       result=true;
	     }else
	     {
	          if(_list())
		  {
			result=true;
		  }else
		  {
			result=false;
		  }
	      }
	}
     return result;
}
	/*=================================================================================*
	 *			LIST_TERM_AUX : ',' LIST_TERM | epsilone		   *
	 *=================================================================================*/
boolean _LIST_TERM_AUX()
{
 boolean result;
	if(token == ACLOSE_TOKEN || token == PCLOSE_TOKEN || token == CRCLOSE_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == VIRG_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_TERM())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *			LIST_TERM : term LIST_TERM_AUX				   *
	 *=================================================================================*/
boolean _LIST_TERM()
{
 boolean result;
	if(_term())
	{
	token=_liretoken();
	result=_LIST_TERM_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *				set : '{' (LIST_TERM)? '}'		  	   * FOLOW : '}'
	 *=================================================================================*/
boolean _set()
{
boolean result;
	if(token == AOPEN_TOKEN)
	{
		token=_liretoken();
		if(token == ACLOSE_TOKEN)
		{
		result=true;
		}else
		{
			if(_LIST_TERM())
			{
				token=_liretoken();
				if(token == ACLOSE_TOKEN)
				{
				result = true;
				}else
				{
				result = false;
				}
			}else
			{
			result = false;
			}
		}
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *				list : '[' (LIST_TERM)? ']'		  	   * FOLOW : ' ]'
	 *=================================================================================*/
boolean _list()
{
boolean result;
	if(token == CROPEN_TOKEN)
	{
		token=_liretoken();
		if(token == CRCLOSE_TOKEN)
		{
		result=true;
		}else
		{
			if(_LIST_TERM())
			{
				token=_liretoken();
				if(token == CRCLOSE_TOKEN)
				{
				result = true;
				}else
				{
				result = false;
				}
			}else
			{
			result = false;
			}
		}
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *			function : IDENTIFIER '(' (LIST_TERM)? ')'  		   * FOLOW : ' )'
	 *=================================================================================*/
boolean _function()
{
boolean result;
    if(token == IDF_TOKEN)
    {
	token=_liretoken();
	if(token == POPEN_TOKEN)
	{
		token=_liretoken();
		if(token == PCLOSE_TOKEN)
		{
		result=true;
		}else
		{
			if(_LIST_TERM())
			{
				token=_liretoken();
				if(token == PCLOSE_TOKEN)
				{
				result = true;
				}else
				{
				result = false;
				}
			}else
			{
			result = false;
			}
		}
	}else
	{
	result = false;
	}
   }else
   {
      result=false;
   }
 return result;
}

	/*=================================================================================*
	 *			LIST_TERM_MAP_AUX : ',' LIST_TERM_MAP | epsilone	   *
	 *=================================================================================*/
boolean _LIST_TERM_MAP_AUX()
{
 boolean result;
	if(token == ACLOSE_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == VIRG_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_TERM_MAP())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *			LIST_TERM_MAP : term ':' term  LIST_TERM_MAP_AUX	   *
	 *=================================================================================*/
boolean _LIST_TERM_MAP()
{
 boolean result;
	if(_term())
	{
		if(strcmp(rightTerm,"") !=0){
			//TERM LEFT MAP KEYSPACE PROPRIETY
			term = (char*) malloc(strlen(rightTerm) );
			strcpy(term,rightTerm);
			typeLeft = typeRight;
		}

		token=_liretoken();
		if(token==DEUX_POINT_TOKEN)
		{
			token=_liretoken();
			if(_term())
			{
				//TERM RIGHT
				if(strcmp(term,"") != 0 && strcmp(rightTerm,"") != 0){

						inserer_mapTerm(term,typeLeft,rightTerm,typeRight);
						ajout_valeurMaps(&valrMaps,term,typeLeft,rightTerm,typeRight);
				}

			token=_liretoken();
			result=_LIST_TERM_MAP_AUX();
			}else
			{
			result = false;
			}
		}else
		{
		result = false;
		}
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *				map : '{' ( LIST_TERM_MAP)? '}'		  	   * FOLOW : '}'
	 *=================================================================================*/
boolean _map()
{
  boolean result;
	if(token == AOPEN_TOKEN)
	{
		token=_liretoken();
		if(token == ACLOSE_TOKEN)
		{
		result=true;
		}else
		{

			if(_LIST_TERM_MAP())
			{
				token=_liretoken();
				if(token == ACLOSE_TOKEN)
				{
				result = true;
				}else
				{
				result = false;
				}
			}else
			{
			result = false;
			}
		}
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *				keyspace_name : IDENTIFIER  		           *
	 *=================================================================================*/
boolean _keyspace_name()
{
	boolean result;
	if(token==IDF_TOKEN)
	{
	  result=true;
	}else
	{
	  result=false;
	}
     return result;
}


	/*=================================================================================*
	 *				if_exists : K_IF K_EXISTS  		           *
	 *=================================================================================*/
boolean _if_exists()
{
	boolean result;
	if(token==IF_TOKEN)
	{
		token=_liretoken();
		if(token==EXISTS_TOKEN)
		{
		  result=true;
		}else
		{
		  result=false;
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *			if_not_exists : K_IF K_NOT K_EXISTS  		           *
	 *=================================================================================*/
boolean _if_not_exists()
{
	boolean result;
	if(token==IF_TOKEN)
	{
		token=_liretoken();
		if(token==NOT_TOKEN)
		{
			token=_liretoken();
			if(token==EXISTS_TOKEN)
			{
			  result=true;
			}else
			{
			  result=false;
			}
		}else
		{
		  result=false;
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*========================================================================================================*
	 * partition_key : column_name | '('LIST_COLUMN_NAME ')' <==> partition_key : column_name | primary_key   *
	 *========================================================================================================*/
boolean _partition_key()
{
	boolean result;
	if(_column_name())
	{
	  result=true;
	}else
	{
	     if(_primary_key())
	     {
	       result=true;
	     }else
	     {
	       result=false;
	     }
	}
     return result;
}

	/*=================================================================================================*
	 *		LIST_COLUMN_NAME_PRIMARY_KEY_AUX : ',' LIST_COLUMN_NAME_PRIMARY_KEY | epsilone	   *
	 *=================================================================================================*/
boolean _LIST_COLUMN_NAME_PRIMARY_KEY_AUX()
{
 boolean result;
	if(token == PCLOSE_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == VIRG_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_COLUMN_NAME_PRIMARY_KEY())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=========================================================================================================*
	 *			LIST_COLUMN_NAME_PRIMARY_KEY : column_name LIST_COLUMN_NAME_PRIMARY_KEY_AUX	   *
	 *=========================================================================================================*/
boolean _LIST_COLUMN_NAME_PRIMARY_KEY()
{
 boolean result;
	if(_column_name())
	{
    //VERIFIER SI PRIMARY KEY EST VALIDE (EXISTE ET N'EST PAS STATIC)
    if(reqt == 2) isPrimaryKeyValid(curIdf,yylineno);

	token=_liretoken();
	result=_LIST_COLUMN_NAME_PRIMARY_KEY_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*===================================================================================*
	 *		  primary_key : '(' LIST_COLUMN_NAME_PRIMARY_KEY ')'   		     * FOLOW : ')'
	 *===================================================================================*/
boolean _primary_key()
{
  boolean result;
	if(token == POPEN_TOKEN)
	{
		token=_liretoken();
		if(_LIST_COLUMN_NAME_PRIMARY_KEY())
		{
			token=_liretoken();
			if(token == PCLOSE_TOKEN)
			{
			result=true;
			}else
			{
			result = false;
			}
		}else
		{
		result = false;
		}
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *				column_type : data_type  		           *
	 *=================================================================================*/
boolean _column_type()
{
	boolean result;
	if(_data_type())
	{
	  result=true;
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *	LIST_COLUMN_DEFINITION_AUX : ',' LIST_COLUMN_DEFINITION |epsilon	   *
	 *=================================================================================*/
boolean _LIST_COLUMN_DEFINITION_AUX()
{
 boolean result;
	if(token == PCLOSE_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == VIRG_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_COLUMN_DEFINITION())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *	LIST_COLUMN_DEFINITION : column_definition LIST_COLUMN_DEFINITION_AUX	   *
	 *=================================================================================*/
boolean _LIST_COLUMN_DEFINITION()
{
 boolean result;
	if(_column_definition())
	{
	token=_liretoken();
	result=_LIST_COLUMN_DEFINITION_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *		column_definitions : '(' LIST_COLUMN_DEFINITION ')'	  	   * FOLOW : ')'
	 *=================================================================================*/
boolean _column_definitions()
{
boolean result;
	if(token == POPEN_TOKEN)
	{
		token=_liretoken();
		if(_LIST_COLUMN_DEFINITION())
		{
			token=_liretoken();
			if(token == PCLOSE_TOKEN)
			{
			result=true;
			}else
			{
			result = false;
			}
		}else
		{
		result = false;
		}
	}else
	{
	result = false;
	}
 return result;
}


	/*=================================================================================*
	 *		LIST_TABLE_OPTION_AUX: K_AND LIST_TABLE_OPTION | epsilone	   *
	 *=================================================================================*/
boolean _LIST_TABLE_OPTION_AUX()
{
 boolean result;
	if(token == PVIRG_TOKEN || token == APPLY_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == AND_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_TABLE_OPTION())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *		LIST_TABLE_OPTION : table_option LIST_TABLE_OPTION_AUX		   *
	 *=================================================================================*/
boolean _LIST_TABLE_OPTION()
{
 boolean result;
	if(_table_option())
	{
	token=_liretoken();
	result=_LIST_TABLE_OPTION_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *			table_options : LIST_TABLE_OPTION		  	   * FOLOW : ";" | K_APPLY
	 *=================================================================================*/
boolean _table_options()
{
boolean result;
	if(_LIST_TABLE_OPTION())
	{
	result=true;
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *	table_option : property | K_COMPACT K_STORAGE | K_CLUSTERING K_ORDER 	   *
	 *=================================================================================*/
boolean _table_option()
{
	boolean result;
	if(token == COMPACT_TOKEN)
	{
	  	  token=_liretoken();
		  if(token == STORAGE_TOKEN)
		  {
			result=true;
		  }else
		  {
			result=false;
		  }
	}else
	{
	     if(token == CLUSTERING_TOKEN)
	     {
	          token=_liretoken();
		  if(token == ORDER_TOKEN)
		  {
			result=true;
		  }else
		  {
			result=false;
		  }
	     }else
	     {
	          if(_property())
		  {
			result=true;
		  }else
		  {
			result=false;
		  }
	      }
	}
     return result;
}

	/*======================================================================================================================*
	 *	column_definition : column_name column_type (K_STATIC)? (K_PRIMARY K_KEY)? | K_PRIMARY K_KEY primary_key  	*
	 *======================================================================================================================*/
boolean _column_definition()
{
	boolean result;
	if(token==PRIMARY_TOKEN)
	{
	    token=_liretoken();
		  if(token==KEY_TOKEN)
		  {     //VERIFIER SI ON A PLUSIEURS PRIMARY KEY()
            if( nbrPK == 1 ) inserer_optionsError(PLUSPRIMARYKEY, yylineno);
            else nbrPK = 1;

		     	  token=_liretoken();
			  if(_primary_key())
			  {

			     result=true;
			  }else
			  {
			     result=false;
			  }
		  }else
		  {
		     result=false;
		  }
	}else
	{
	  	if(_column_name())
		{
		     	token=_liretoken();
			if(_column_type())
			{
					//TYPE DE COLONNE
					int curType = atoi(yytext);

			   	token=_liretoken();
				if(token == PCLOSE_TOKEN || token ==VIRG_TOKEN)
				{
           //INSERER COLONNES
           inserer_columnNode(curIdf/*, typeClmTable typeClm*/,false, false,yylineno);
					 //COLONNE TABLE RI
					 ajout_colonneDef(&(tableRI->colonneDefs),curIdf,curType,0,0);

				   follow_token=true;
				   result = true;
				}else
				     if (token == STATIC_TOKEN)
				     {
					        token=_liretoken();
					        if(token == PCLOSE_TOKEN|| token == VIRG_TOKEN)
						{
               //INSERER COLONNES
               inserer_columnNode(curIdf/*, typeClmTable typeClm*/,true, false,yylineno);
							 //COLONNE TABLE RI
							 ajout_colonneDef(&(tableRI->colonneDefs),curIdf,curType,1,0);

						   follow_token=true;
						   result = true;
						}else
						     if (token == PRIMARY_TOKEN)
						     {
							     token=_liretoken();
							     if (token == KEY_TOKEN)
							     {
                            //INSERER COLONNES
                            inserer_columnNode(curIdf/*, typeClmTable typeClm*/,true,true,yylineno);
														//COLONNE TABLE RI
								 					 ajout_colonneDef(&(tableRI->colonneDefs),curIdf,curType,1,1);

								            result = true;
							     }else
							     {
								result = false;
							     }
						     }else
						     {
							result = false;
						     }
				     }else
				     {
						     if (token == PRIMARY_TOKEN)
						     {
							     token=_liretoken();
							     if (token == KEY_TOKEN)
							     {
                        //INSERER COLONNES
                        inserer_columnNode(curIdf/*, typeClmTable typeClm*/,false, true,yylineno);
												//COLONNE TABLE RI
						 					 	ajout_colonneDef(&(tableRI->colonneDefs),curIdf,curType,0,1);

								        result = true;
							     }else
							     {
								result = false;
							     }
						     }else
						     {
							result = false;
						     }
				     }
			}else
			{
			   result=false;
			}

		}else
		{
		     result=false;
		}
	}
   return result;
}


	/*=================================================================================*
	 *				column_name : IDENTIFIER  		           *
	 *=================================================================================*/
boolean _column_name()
{
	boolean result;
	if(token == IDF_TOKEN)
	{
	  result=true;
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *			table_name : (keyspace_name '.')? IDENTIFIER 		   *
	 *=================================================================================*/
boolean _table_name()
{

	boolean result;
	boolean isKeyspc = false;
	nameKeyspace = (char*) malloc(50*sizeof(char));
	char * isKeyspace = (char*) malloc(50*sizeof(char));

	if(token==IDF_TOKEN)
	{
		strcpy(isKeyspace,yytext);

	  token=_liretoken();
	  if(token == POPEN_TOKEN || token == WHERE_TOKEN || token == USING_TOKEN || token == PVIRG_TOKEN || token == SET_TOKEN || token == ALTER_TOKEN || token == ADD_TOKEN || token == DROP_TOKEN || token == WITH_TOKEN)
	  {

			strcpy(nameKeyspace,"defaultKeyspace");

		follow_token=true;
		result = true;
	  }else
		if (token == POINT_TOKEN)
		{

			token=_liretoken();
			if (token == IDF_TOKEN)
			{
				strcpy(nameKeyspace,isKeyspace);

				result = true;
			}else
			{
				result = false;
			}
		}else
		{
			result = false;
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *			batch_option : K_TIMESTAMP INTEGER  		           *
	 *=================================================================================*/
boolean _batch_option()
{
	boolean result;
	if(token==TIMESTAMP_TYPE_TOKEN)
	{
		token=_liretoken();
		if(token==INTEGER_TOKEN)
		{
		  result=true;
		}else
		{
		  result=false;
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *		LIST_DELETE_SELECTION_AUX : ',' LIST_DELETE_SELECTION | epsilon	   *
	 *=================================================================================*/
boolean _LIST_DELETE_SELECTION_AUX()
{
 boolean result;
	if(token == FROM_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == VIRG_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_DELETE_SELECTION())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *	LIST_DELETE_SELECTION : delete_selection LIST_DELETE_SELECTION_AUX	   *
	 *=================================================================================*/
boolean _LIST_DELETE_SELECTION()
{
 boolean result;
	if(_delete_selection())
	{
	token=_liretoken();
	result=_LIST_DELETE_SELECTION_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *			delete_selections : LIST_DELETE_SELECTION		   * FOLLOW :K_FROM
	 *=================================================================================*/
boolean _delete_selections()
{
boolean result;
	if(_LIST_DELETE_SELECTION())
	{
	result=true;
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *	LIST_DELETE_CONDITION_AUX : K_AND LIST_DELETE_CONDITION | epsilone	   *
	 *=================================================================================*/
boolean _LIST_DELETE_CONDITION_AUX()
{
 boolean result;
	if(token == PVIRG_TOKEN || token == APPLY_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == AND_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_DELETE_CONDITION())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *	LIST_DELETE_CONDITION : delete_condition LIST_DELETE_CONDITION_AUX	   *
	 *=================================================================================*/
boolean _LIST_DELETE_CONDITION()
{
 boolean result;
	if(_delete_condition())
	{
	token=_liretoken();
	result=_LIST_DELETE_CONDITION_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *	delete_conditions : K_IF ( K_EXISTS | LIST_DELETE_CONDITION )		   *  FOLLOW :K_APPLY | ';'
	 *=================================================================================*/
boolean _delete_conditions()
{
boolean result;
	if(token==IF_TOKEN)
	{
		token=_liretoken();
		if(token==EXISTS_TOKEN)
		{
		result=true;
		}else
		{
			if(_LIST_DELETE_CONDITION())
			{
			result=true;
			}else
			{
			result = false;
			}
		}
	}else
	{
	result = false;
	}
 return result;
}
	/*=================================================================================*
	 *		delete_condition : IDENTIFIER ('[' term ']')? '=' term		   *
	 *=================================================================================*/
boolean _delete_condition()
{
	boolean result;
	if(token==IDF_TOKEN)
	{
	  	token=_liretoken();
	  	if (token == EQ_TOKEN)
		{
			token=_liretoken();
			if (_term())
			{
				result = true;
			}else
			{
				result = false;
			}
		}else
		{
			if (token == CROPEN_TOKEN)
			{
				token=_liretoken();
				if (_term())
				{
					token=_liretoken();
					if (token == CRCLOSE_TOKEN)
					{
						token=_liretoken();
						if (token == EQ_TOKEN)
						{
							token=_liretoken();
							if (_term())
							{
								result = true;
							}else
							{
								result = false;
							}
						}else
						{
							result = false;
						}
					}else
					{
						result = false;
					}
				}else
				{
					result = false;
				}
			}else
			{
				result = false;
			}
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *			delete_selection : IDENTIFIER ('[' term ']')? 		   *
	 *=================================================================================*/
boolean _delete_selection()
{
	boolean result;
	if(token==IDF_TOKEN)
	{
	  token=_liretoken();
	  if(token == FROM_TOKEN || token == VIRG_TOKEN)
	  {
		follow_token=true;
		result = true;
	  }else
		if (token == CROPEN_TOKEN)
		{
			token=_liretoken();
			if (_term())
			{
				token=_liretoken();
				if (token == CRCLOSE_TOKEN)
				{
					result = true;
				}else
				{
					result = false;
				}
			}else
			{
				result = false;
			}
		}else
		{
			result = false;
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *		LIST_COLUMN_NAME_AUX : ',' LIST_COLUMN_NAME | epsilone		   *
	 *=================================================================================*/
boolean _LIST_COLUMN_NAME_AUX()
{
 boolean result;
	if(token == PCLOSE_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == VIRG_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_COLUMN_NAME())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *		LIST_COLUMN_NAME : column_name LIST_COLUMN_NAME_AUX		   *
	 *=================================================================================*/
boolean _LIST_COLUMN_NAME()
{
 boolean result;
	if(_column_name())
	{
			ajout_valeurMaps(&valrMaps,yytext,0,"\0",0);

			token=_liretoken();
			result=_LIST_COLUMN_NAME_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *			column_names : '(' LIST_COLUMN_NAME ')'	 	 	   * FOLOW : ')'
	 *=================================================================================*/
boolean _column_names()
{
boolean result;
	if(token == POPEN_TOKEN)
	{
		token=_liretoken();
		if(_LIST_COLUMN_NAME())
		{
			token=_liretoken();
			if(token == PCLOSE_TOKEN)
			{
			result=true;
			}else
			{
			result = false;
			}
		}else
		{
		result = false;
		}
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *		LIST_COLUMN_VALUE_AUX : ',' LIST_COLUMN_VALUE | epsilone	   *
	 *=================================================================================*/
boolean _LIST_COLUMN_VALUE_AUX()
{
 boolean result;
	if(token == PCLOSE_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == VIRG_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_COLUMN_VALUE())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *		LIST_COLUMN_VALUE : term LIST_COLUMN_VALUE_AUX			   *
	 *=================================================================================*/
boolean _LIST_COLUMN_VALUE()
{
 boolean result;
	if(_term())
	{
			//INSERER LA VALEUR D4UNE COLONNE
			if( inserer_colonne_value(&valrMaps, yytext) == -1 ) inserer_optionsError(COLUMNNAMENOTFOUND, yylineno);

			token=_liretoken();
			result=_LIST_COLUMN_VALUE_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *			column_values :'(' LIST_COLUMN_VALUE ')' 	 	   * FOLOW : ')'
	 *=================================================================================*/
boolean _column_values()
{
boolean result;
	if(token == POPEN_TOKEN)
	{
		token=_liretoken();
		if(_LIST_COLUMN_VALUE())
		{
			token=_liretoken();
			if(token == PCLOSE_TOKEN)
			{
			result=true;
			}else
			{
			result = false;
			}
		}else
		{
		result = false;
		}
	}else
	{
	result = false;
	}
 return result;
}


	/*================================================================================================================================*
	 * create_table_stmt : K_CREATE (K_TABLE | K_COLUMNFAMILY) if_not_exists? table_name column_definitions (K_WITH table_options)?   *
	 *================================================================================================================================*/
boolean _create_table_stmt()
{
  reqt = 2;   //REQUETE CREATE TABLE
	boolean result;
	if(token==CREATE_TOKEN)
	{
		token=_liretoken();
		if(token==TABLE_TOKEN || token==COLUMNFAMILY_TOKEN)
		{
		  	token=_liretoken();
			if(token==IF_TOKEN)
			{
				token=_liretoken();
				if(token==NOT_TOKEN)
				{
					token=_liretoken();
					if(token==EXISTS_TOKEN)
					{
						token=_liretoken();
						if(_table_name())
						{
							token=_liretoken();
							if(_column_definitions())
							{
								token=_liretoken();
							  	if(token == PVIRG_TOKEN)
								{
								   follow_token=true;
								   result = true;
								}else
								     if (token == WITH_TOKEN)
								     {
									     token=_liretoken();
									     if (_table_options())
									     {
										result = true;
									     }else
									     {
										result = false;
									     }
								     }else
								     {
									result = false;
								     }
							}else
							{
							  result=false;
							}
						}else
						{
						  result=false;
						}
					}else
					{
					  result=false;
					}
				}else
				{
				  result=false;
				}
			}else
			{
						if(_table_name())
						{
							token=_liretoken();
							if(_column_definitions())
							{
								token=_liretoken();
							  	if(token == PVIRG_TOKEN)
								{
								   follow_token=true;
								   result = true;
								}else
								     if (token == WITH_TOKEN)
								     {
									     token=_liretoken();
									     if (_table_options())
									     {
									             token=_liretoken();
										     if (token == PVIRG_TOKEN)
										     {
											result = true;

										     }else
										     {
											result = false;
										     }

									     }else
									     {
										result = false;
									     }
								     }else
								     {
									result = false;
								     }
							}else
							{
							  result=false;
							}
						}else
						{
						  result=false;
						}
			}
		}else
		{
		  result=false;
		}
	}else
	{
	  result=false;
	}
     return result;
}


	/*=================================================================================*
	 *		LIST_RELATION_AUX : K_AND LIST_RELATION | epsilone		   *
	 *=================================================================================*/
boolean _LIST_RELATION_AUX()
{
 boolean result;
	if(token == PVIRG_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == AND_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_RELATION())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *			LIST_RELATION : relation LIST_RELATION_AUX		   *
	 *=================================================================================*/
boolean _LIST_RELATION()
{
 boolean result;
	if(_relation())
	{
	token=_liretoken();
	result=_LIST_RELATION_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *				where_clause : LIST_RELATION		  	   * FOLOW : ";" | K_APPLY
	 *=================================================================================*/
boolean _where_clause()
{
boolean result;
	if(_LIST_RELATION())
	{
	result=true;
	}else
	{
	result = false;
	}
 return result;
}

	/*==============================================================================================================*
	 *	relation : column_name '=' term | column_name K_IN '(' (term (',' term)*)? ')' | column_name K_IN '?'   *
	 *==============================================================================================================*/
						//(term (',' term)*)=LIST_TERM
boolean _relation()
{
	boolean result;
	if(_column_name())
	{
		token=_liretoken();
		if(token==EQ_TOKEN)
		{
			token=_liretoken();
			if(_term())
			{
			  result = true;
			}else
			{
			  result = false;
			}
		}else
		{
		  	if(token==IN_TOKEN)
			{
				token=_liretoken();
				if(token==PINTERROGATION_TOKEN)
				{
				  result=true;
				}else
				{
				 	if(token == POPEN_TOKEN)
					{
						token=_liretoken();
						if(token == PCLOSE_TOKEN)
						{
						result=true;
						}else
						{
							if(_LIST_TERM())
							{
								token=_liretoken();
								if(token == PCLOSE_TOKEN)
								{
								result = true;
								}else
								{
								result = false;
								}
							}else
							{
							result = false;
							}
						}
					}else
					{
					  result = false;
					}
				}
			}else
			{
			  result=false;
			}
		}
	}else
	{
	  result=false;
	}
     return result;
}

    /*=======================================================================================================================================*
     *	delete_stmt : K_DELETE delete_selections? K_FROM table_name (K_USING K_TIMESTAMP INTEGER)? K_WHERE where_clause delete_conditions?   *
     *=======================================================================================================================================*/
boolean _delete_stmt()
{
	boolean result;
	if(token==DELETE_TOKEN)
	{
		token=_liretoken();
		if(token==FROM_TOKEN)
		{
			token=_liretoken();
			if(_table_name())
			{
				token=_liretoken();
				if(token==WHERE_TOKEN)
				{
				  	token=_liretoken();
					if(_where_clause())
					{
						token=_liretoken();
						if(token == PVIRG_TOKEN)
						{
						result=true;
						}else
						{
							if(_delete_conditions())
							{
							result=true;
							}else
							{
							result = false;
							}
						}
					}else
					{
					    result=false;
					}
				}else
				{
					if(token==USING_TOKEN)
					{
					  	token=_liretoken();
						if(token==TIMESTAMP_TYPE_TOKEN)
						{
							token=_liretoken();
							if(token==INTEGER_TOKEN)
							{
								token=_liretoken();
								if(token==WHERE_TOKEN)
								{
								  	token=_liretoken();
									if(_where_clause())
									{
										token=_liretoken();
										if(token == PVIRG_TOKEN)
										{
										result=true;
										}else
										{
											if(_delete_conditions())
											{
											result=true;
											}else
											{
											result = false;
											}
										}
									}else
									{
									    result=false;
									}
								}else
								{
								  result=false;
								}
							}else
							{
							  result=false;
							}
						}else
						{
						  result=false;
						}
					}else
					{
					  result=false;
					}
				}
			}else
			{
			  result=false;
			}
		}else
		{
		  	if(_delete_selections())
			{
				token=_liretoken();
				if(token==FROM_TOKEN)
				{
				  	token=_liretoken();
					if(_table_name())
					{
						token=_liretoken();
						if(token==WHERE_TOKEN)
						{
						  	token=_liretoken();
							if(_where_clause())
							{
								token=_liretoken();
								if(token == PVIRG_TOKEN)
								{
								result=true;
								}else
								{
									if(_delete_conditions())
									{
									result=true;
									}else
									{
									result = false;
									}
								}
							}else
							{
							    result=false;
							}
						}else
						{
							if(token==USING_TOKEN)
							{
							  	token=_liretoken();
								if(token==TIMESTAMP_TYPE_TOKEN)
								{
									token=_liretoken();
									if(token==INTEGER_TOKEN)
									{
										token=_liretoken();
										if(token==WHERE_TOKEN)
										{
										  	token=_liretoken();
											if(_where_clause())
											{
												token=_liretoken();
												if(token == PVIRG_TOKEN)
												{
												result=true;
												}else
												{
													if(_delete_conditions())
													{
													result=true;
													}else
													{
													result = false;
													}
												}
											}else
											{
											    result=false;
											}
										}else
										{
										  result=false;
										}
									}else
									{
									  result=false;
									}
								}else
								{
								  result=false;
								}
							}else
							{
							  result=false;
							}
						}
					}else
					{
					  result=false;
					}
				}else
				{
				  result=false;
				}
			}else
			{
			  result=false;
			}
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *			truncate_table_stmt : K_TRUNCATE table_name		   *
	 *=================================================================================*/
boolean _truncate_table_stmt()
{
	boolean result;
	if(token==TRUNCATE_TOKEN)
	{
		token=_liretoken();
		if(_table_name())
		{
		  result=true;
		}else
		{
		  result=false;
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *		drop_table_stmt : K_DROP K_TABLE if_exists? table_name		   *
	 *=================================================================================*/
boolean _drop_table_stmt()
{
	boolean result;
	if(token==DROP_TOKEN)
	{
		token=_liretoken();
		if(token==TABLE_TOKEN)
		{
			token=_liretoken();
			if(token==IF_TOKEN)
			{
				token=_liretoken();
				if(token==EXISTS_TOKEN)
				{
					token=_liretoken();
					if(_table_name())
					{
					  result=true;
					}else
					{
					  result=false;
					}
				}else
				{
				  result=false;
				}
			}else
			{
				if(_table_name())
				{
				  result=true;
				}else
				{
				  result=false;
				}
			}
		}else
		{
		  result=false;
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *		LIST_UPSERT_OPTION_AUX: K_AND LIST_UPSERT_OPTION | epsilone	   *
	 *=================================================================================*/
boolean _LIST_UPSERT_OPTION_AUX()
{
 boolean result;
	if(token == SET_TOKEN || token == PVIRG_TOKEN || token == APPLY_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == AND_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_UPSERT_OPTION())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *		LIST_UPSERT_OPTION : upsert_option LIST_UPSERT_OPTION_AUX	   *
	 *=================================================================================*/
boolean _LIST_UPSERT_OPTION()
{
 boolean result;
	if(_upsert_option())
	{
	token=_liretoken();
	result=_LIST_UPSERT_OPTION_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *			upsert_options : K_USING LIST_UPSERT_OPTION		   * folow :K_SET | ';' | K_APPLY
	 *=================================================================================*/
boolean _upsert_options()
{
boolean result;
	if(token==USING_TOKEN)
	{
		token=_liretoken();
		if(_LIST_UPSERT_OPTION())
		{
		result=true;
		}else
		{
		result = false;
		}
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *		upsert_option : K_TIMESTAMP INTEGER | K_TTL INTEGER		   *
	 *=================================================================================*/
boolean _upsert_option()
{
	boolean result;
	if(token==TIMESTAMP_TYPE_TOKEN)
	{
		token=_liretoken();
		if(token==INTEGER_TOKEN)
		{
		  result=true;
		}else
		{
		  result=false;
		}
	}else
	{
	  	if(token==TTL_TOKEN)
		{
			token=_liretoken();
			if(token==INTEGER_TOKEN)
			{
			  result=true;
			}else
			{
			  result=false;
			}
		}else
		{
		  result=false;
		}
	}
     return result;
}


	/*=================================================================================*
	 *				index_name : IDENTIFIER			  	   *
	 *=================================================================================*/
boolean _index_name()
{
boolean result;
	if(token==IDF_TOKEN)
	{
	result=true;
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *				index_class : STRING			  	   *
	 *=================================================================================*/
boolean _index_class()
{
boolean result;
	if(token==STRING_TOKEN)
	{
	result=true;
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *			use_stmt : K_USE keyspace_name			  	   *
	 *=================================================================================*/
boolean _use_stmt()
{
boolean result;
	if(token==USE_TOKEN)
	{
		token=_liretoken();
		if(_keyspace_name())
		{
		result=true;
		}else
		{
		result = false;
		}
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *	drop_keyspace_stmt : K_DROP K_KEYSPACE if_exists? keyspace_name		   *
	 *=================================================================================*/
boolean _drop_keyspace_stmt()
{
	boolean result;
	if(token==DROP_TOKEN)
	{
		token=_liretoken();
		if(token==KEYSPACE_TOKEN)
		{
			token=_liretoken();
			if(token==IF_TOKEN)
			{
				token=_liretoken();
				if(token==EXISTS_TOKEN)
				{
					token=_liretoken();
					if(_keyspace_name())
					{
					  result=true;
					}else
					{
					  result=false;
					}
				}else
				{
				  result=false;
				}
			}else
			{
				if(_keyspace_name())
				{
				  result=true;
				}else
				{
				  result=false;
				}
			}
		}else
		{
		  result=false;
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*==================================================================================================*
	 *	create_keyspace_stmt : K_CREATE K_KEYSPACE if_not_exists? keyspace_name K_WITH properties   *
	 *==================================================================================================*/
boolean _create_keyspace_stmt()
{
	boolean result;
	if(token==CREATE_TOKEN)
	{
    reqt = 1;   //REQUETE CREATE KEYSPACE
		token=_liretoken();
		if(token==KEYSPACE_TOKEN)
		{
			token=_liretoken();
			if(token==IF_TOKEN)
			{
				token=_liretoken();
				if(token==EXISTS_TOKEN)
				{
					token=_liretoken();
					if(_keyspace_name())
					{
						//CREER KEYSPACE NODE
						creer_keyspaceNode(curIdf, NULL);
						creer_keyspaceRI(curIdf);

						token=_liretoken();
						if(token==WITH_TOKEN)
						{
							token=_liretoken();
							if(_properties())
							{
							  result=true;
							}else
							{
							  result=false;
							}
						}else
						{
						  result=false;
						}
					}else
					{
					  result=false;
					}
				}else
				{
				  result=false;
				}
			}else
			{
				if(_keyspace_name())
				{
					//CREER KEYSPACE NODE
					creer_keyspaceNode(curIdf, NULL);
					creer_keyspaceRI(curIdf);

				  	token=_liretoken();
					if(token==WITH_TOKEN)
					{
						token=_liretoken();
						if(_properties())
						{
						  result=true;
						}else
						{
						  result=false;
						}
					}else
					{
					  result=false;
					}
				}else
				{
				  result=false;
				}
			}
		}else
		{
		  result=false;
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*=================================================================================*
	 *	alter_keyspace_stmt : K_ALTER K_KEYSPACE keyspace_name K_WITH properties   *
	 *=================================================================================*/
boolean _alter_keyspace_stmt()
{
	boolean result;
	if(token==ALTER_TOKEN)
	{
    reqt = 1;   //REQUETE ALTER KEYSPACE
		token=_liretoken();
		if(token==KEYSPACE_TOKEN)
		{
			token=_liretoken();
			if(_keyspace_name())
			{
				//CREER KEYSPACE NODE
				creer_keyspaceNode(curIdf, NULL);
				creer_keyspaceRI(curIdf);

				token=_liretoken();
				if(token==WITH_TOKEN)
				{
					token=_liretoken();
					if(_properties())
					{
					  result=true;
					}else
					{
					  result=false;
					}
				}else
				{
				  result=false;
				}
			}else
			{
			  result=false;
			}
		}else
		{
		  result=false;
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*====================================================================================================================*
	 *	insert_stmt : K_INSERT K_INTO table_name column_names K_VALUES column_values if_not_exists? upsert_options?   *
	 *====================================================================================================================*/
boolean _insert_stmt()
{
	boolean result;
	if(token==INSERT_TOKEN)
	{
		token=_liretoken();
		if(token==INTO_TOKEN)
		{
			token=_liretoken();
			if(_table_name())
			{
				token=_liretoken();
				if(_column_names())
				{
					token=_liretoken();
					if(token==VALUES_TOKEN)
					{
						token=_liretoken();
						if(_column_values())
						{
							token=_liretoken();
							if(token == PVIRG_TOKEN)
							{
							   follow_token=true;
							   result = true;
							}else
							     	if(token==IF_TOKEN)
								{
									token=_liretoken();
								  	if(token==NOT_TOKEN)
									{
										token=_liretoken();
									  	if(token==EXISTS_TOKEN)
										{
											token=_liretoken();
										  	if(token == PVIRG_TOKEN || token == APPLY_TOKEN)
											{
											   follow_token=true;
											   result = true;
											}else
											     if (_upsert_options())
											     {
												result=true;
											     }else
											     {
												result = false;
											     }
										}else
										{
										  result=false;
										}
									}else
									{
									  result=false;
									}
								}else
								{
									if(_upsert_options())
									{
									  result=true;
									}else
									{
									  result=false;
									}
								}

						}else
						{
						  result=false;
						}
					}else
					{
					  result=false;
					}
				}else
				{
				  result=false;
				}
			}else
			{
			  result=false;
			}
		}else
		{
		  result=false;
		}
	}else
	{
	  result=false;
	}
     return result;
}

	/*==============================================================================================================================*
	 *		statement_table : create_table_stmt | drop_table_stmt | truncate_table_stmt | insert_stmt | delete_stmt      *
	 *==============================================================================================================================*/
boolean _statement_table()
{
	boolean result;
	if(_create_table_stmt())
	{
	  result=true;
	}else
	{
	     if(_drop_table_stmt())
	     {
	       result=true;
	     }else
	     {
	          if(_truncate_table_stmt())
		  {
			result=true;
		  }else
		  {
		  	  if(_insert_stmt())
			  {
				result=true;
			  }else
			  {
			  	  if(_delete_stmt())
				  {
					result=true;
				  }else
				  {
				  	  if(_update_stmt())
					  {
						result=true;
					  }else
					  {
					  	  if(_alter_table_stmt())
						  {
							result=true;
						  }else
						  {
						  	result=false;
						  }
					  }
				  }
			  }
		  }
	      }
	}
     return result;
}
	/*==============================================================================================================================*
	 *		statement_keyspace : drop_keyspace_stmt | create_keyspace_stmt | alter_keyspace_stmt | use_stmt		        *
	 *==============================================================================================================================*/
boolean _statement_keyspace()
{
	boolean result;
	if(_use_stmt())
	{
		  token=_liretoken();
	  	  if(token==PVIRG_TOKEN)
		  {
			result=true;
		  }else
		  {
		  	result=false;
		  }
	}else
	{
	     if(_drop_keyspace_stmt())
	     {
	       	  token=_liretoken();
	  	  if(token==PVIRG_TOKEN)
		  {
			result=true;
		  }else
		  {
		  	result=false;
		  }
	     }else
	     {
	          if(_create_keyspace_stmt())
		  {

			  token=_liretoken();
		  	  if(token==PVIRG_TOKEN)
			  {
				result=true;
			  }else
			  {
			  	result=false;
			  }
		  }else
		  {
		  	  if(_alter_keyspace_stmt())
			  {
				  token=_liretoken();
			  	  if(token==PVIRG_TOKEN)
				  {
					result=true;
				  }else
				  {
				  	result=false;
				  }
			  }else
			  {
			  result=false;
			  }
		  }
	      }
	}
     return result;
}

	/*=================================================================================*
	 *	LIST_UPDATE_CONDITION_AUX : K_AND LIST_UPDATE_CONDITION | epsilone	   *
	 *=================================================================================*/
boolean _LIST_UPDATE_CONDITION_AUX()
{
 boolean result;
	if(token == PVIRG_TOKEN || token == APPLY_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == AND_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_UPDATE_CONDITION())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *	LIST_UPDATE_CONDITION : update_condition LIST_UPDATE_CONDITION_AUX	   *
	 *=================================================================================*/
boolean _LIST_UPDATE_CONDITION()
{
 boolean result;
	if(_update_condition())
	{
	token=_liretoken();
	result=_LIST_UPDATE_CONDITION_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *			update_conditions : K_IF LIST_UPDATE_CONDITION		   * FOLLOW : ';' | K_APPLY
	 *=================================================================================*/
boolean _update_conditions()
{
boolean result;
	if(token==USING_TOKEN)
	{
		token=_liretoken();
		if(_LIST_UPDATE_CONDITION())
		{
		result=true;
		}else
		{
		result = false;
		}
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *	LIST_UPDATE_ASSIGNMENT_AUX : ',' LIST_UPDATE_ASSIGNMENT | epsilone	   *
	 *=================================================================================*/
boolean _LIST_UPDATE_ASSIGNMENT_AUX()
{
 boolean result;
	if(token == WHERE_TOKEN)
	{
	   follow_token=true;
	   result = true;
	}else
	     if (token == VIRG_TOKEN)
             {
		     token=_liretoken();
		     if (_LIST_UPDATE_ASSIGNMENT())
		     {
			result = true;
		     }else
		     {
			result = false;
		     }
	     }else
	     {
		result = false;
	     }

 return result;
}

	/*=================================================================================*
	 *	LIST_UPDATE_ASSIGNMENT : update_assignment LIST_UPDATE_ASSIGNMENT_AUX	   *
	 *=================================================================================*/
boolean _LIST_UPDATE_ASSIGNMENT()
{
 boolean result;
	if(_update_assignment())
	{
	token=_liretoken();
	result=_LIST_UPDATE_ASSIGNMENT_AUX();
	}else
	{
	result = false;
	}
 return result;
}

	/*=================================================================================*
	 *			update_assignments : LIST_UPDATE_ASSIGNMENT		   * follow : K_WHERE
	 *=================================================================================*/
boolean _update_assignments()
{
boolean result;
	if(_LIST_UPDATE_ASSIGNMENT())
	{
	result=true;
	}else
	{
	result = false;
	}

 return result;
}


	/*=================================================================================*
	 *    update_condition : IDENTIFIER '=' term | IDENTIFIER '[' term ']' '=' term	   *
	 *=================================================================================*/
boolean _update_condition()
{
boolean result;
	token=_liretoken();
	if(token==IDF_TOKEN)
	{
		token=_liretoken();
		if(token==EQ_TOKEN)
		{
			token=_liretoken();
			if(_term())
			{
			result=true;
			}else
			{
			result = false;
			}
		}else
		{
			if(token==CROPEN_TOKEN)
			{
				token=_liretoken();
				if(_term())
				{
					token=_liretoken();
					if(token==CRCLOSE_TOKEN)
					{
						token=_liretoken();
						if(token==EQ_TOKEN)
						{
							token=_liretoken();
							if(_term())
							{
							result=true;
							}else
							{
							result = false;
							}
						}else
						{
						result = false;
						}
					}else
					{
					result = false;
					}
				}else
				{
				result = false;
				}
			}else
			{
			result = false;
			}
		}
	}else
	{
	result = false;
	}

 return result;
}

	/*=================================================================================================================*
	 *	update_assignment : column_name '=' term | column_name '=' column_name ('+' | '-') (INTEGER | set | list)  *
	 *                          | column_name '=' column_name '+' map | column_name '[' term ']' '=' term		   *
	 *=================================================================================================================*/
boolean _update_assignment()
{
boolean result;
	if(_column_name())
	{
		token=_liretoken();
		if(token==EQ_TOKEN)
		{
			token=_liretoken();
			if(_column_name())
			{
				token=_liretoken();
				if(token==PLUS_TOKEN)
				{
						token=_liretoken();
						if(token==INTEGER_TOKEN)
						{
						result=true;
						}else
						{
							if(token==AOPEN_TOKEN)
							{
								token=_liretoken();
								if(token==ACLOSE_TOKEN)
								{
								 result=true;
								}else
								if(_term())
								{
									token=_liretoken();
									if(token==DEUX_POINT_TOKEN)
									{
										token=_liretoken();
										if(_LIST_TERM_MAP_AUX)
										{
											token=_liretoken();
											if(token==ACLOSE_TOKEN)
											{
											result=true;
											}else
											{
											result = false;
											}
										}else
										{
										result = false;
										}
									}else
									{
										if(token==VIRG_TOKEN)
										{
											token=_liretoken();
											if(_LIST_TERM_AUX)
											{
												token=_liretoken();
												if(token==ACLOSE_TOKEN)
												{
												result=true;
												}else
												{
												result = false;
												}
											}else
											{
											result = false;
											}
										}else
										{
										result = false;
										}
									}
								}else
								{
								result = false;
								}
							}else
							{
								if(token==CROPEN_TOKEN)
								{

									token=_liretoken();
									if(token==CRCLOSE_TOKEN)
									{
								 	result=true;
									}else
									if(_LIST_TERM())
									{
										token=_liretoken();
										if(token==CRCLOSE_TOKEN)
										{
										result=true;
										}else
										{
										result = false;
										}
									}else
									{
									result = false;
									}
								}else
								{
								result = false;
								}
							}
						}
				}else
				{
					if(token==MINUS_TOKEN)
					{
						token=_liretoken();
						if(token==INTEGER_TOKEN)
						{
						result=true;
						}else
						{
							if(token==AOPEN_TOKEN)
							{
								token=_liretoken();
								if(token==ACLOSE_TOKEN)
								{
								 result=true;
								}else
								if(_LIST_TERM())
								{
									token=_liretoken();
									if(token==ACLOSE_TOKEN)
									{
									result=true;
									}else
									{
									result = false;
									}
								}else
								{
								result = false;
								}
							}else
							{
								if(token==CROPEN_TOKEN)
								{
									token=_liretoken();
									if(token==CRCLOSE_TOKEN)
									{
								 	result=true;
									}else
									if(_LIST_TERM())
									{
										token=_liretoken();
										if(token==CRCLOSE_TOKEN)
										{
										result=true;
										}else
										{
										result = false;
										}
									}else
									{
									result = false;
									}
								}else
								{
								result = false;
								}
							}
						}
					}else
					{
					result = false;
					}
				}
			}else
			{
				if(_term())
				{
				result=true;
				}else
				{
				result = false;
				}
			}
		}else
		{
			if(token==CROPEN_TOKEN)
			{
				token=_liretoken();
				if(_term())
				{
					token=_liretoken();
					if(token==CRCLOSE_TOKEN)
					{
						token=_liretoken();
						if(token==EQ_TOKEN)
						{
							token=_liretoken();
							if(_term())
							{
							result=true;
							}else
							{
							result = false;
							}
						}else
						{
						result = false;
						}
					}else
					{
					result = false;
					}
				}else
				{
				result = false;
				}
			}else
			{
			result = false;
			}
		}
	}else
	{
	result = false;
	}

 return result;
}

	/*=========================================================================================================================*
	 *    update_stmt : K_UPDATE table_name upsert_options? K_SET update_assignments K_WHERE where_clause update_conditions?   *
	 *=========================================================================================================================*/

boolean _update_stmt()
{
boolean result;
	if(token==UPDATE_TOKEN)
	{
		token=_liretoken();
		if(_table_name())
		{
			token=_liretoken();
			if(token==SET_TOKEN)
			{
				token=_liretoken();
				if(_update_assignments())
				{
					token=_liretoken();
					if(token==WHERE_TOKEN)
					{
					 	token=_liretoken();
						if(_where_clause())
						{
							token=_liretoken();
							if(token == PVIRG_TOKEN)
							{
							   follow_token=true;
							   result = true;
							}else
							     if (_update_conditions())
							     {
								result=true;
							     }else
							     {
								result = false;
							     }
						}else
						{

						}

					}else
					{
					result = false;
					}
				}else
				{
				result = false;
				}
			}else
			{
				if(_upsert_options())
				{
				    token=_liretoken();
				    if(token==SET_TOKEN)
				    {
					token=_liretoken();
					if(_update_assignments())
					{
						token=_liretoken();
						if(token==WHERE_TOKEN)
						{
						 	token=_liretoken();
							if(_where_clause())
							{
								token=_liretoken();
								if(token == PVIRG_TOKEN)
								{
								   follow_token=true;
								   result = true;
								}else
								     if (_update_conditions())
								     {
									result=true;
								     }else
								     {
									result = false;
								     }
							}else
							{
							 result = false;
							}

						}else
						{
						result = false;
						}
					}else
					{
					result = false;
					}
				    }else
				    {
				    result=false;
				    }
				}else
				{
				result = false;
				}
			}
		}else
		{
		result = false;
		}
	}else
	{
	result = false;
	}
 return result;
}

/*===============================================================================================================================================*
 * alter_table_instruction : K_ALTER column_name K_TYPE column_type | K_ADD column_name column_type | K_DROP column_name | K_WITH table_options  *
 *===============================================================================================================================================*/
boolean _alter_table_instruction()
{
boolean result;
	if(token==ALTER_TOKEN)
	{
    reqt = 2;     //REQUETE ALTER TABLE
		token=_liretoken();
		if(_column_name())
		{
			token=_liretoken();
			if(token==TYPE_TOKEN)
			{
				token=_liretoken();
				if(_column_type())
				{
					//TYPE ALTER
					typeAlter = 1;
					ajout_colonneDef(&(tableRI->colonneDefs),curIdf,atoi(yytext),0,0);

				result=true;
				}else
				{
				result = false;
				}
			}else
			{
			result = false;
			}
		}else
		{
		result = false;
		}
	}else
	{
		if(token==ADD_TOKEN)
		{
			token=_liretoken();
			if(_column_name())
			{
				token=_liretoken();
				if(_column_type())
				{

					//TYPE ADD
					typeAlter = 2;
					ajout_colonneDef(&(tableRI->colonneDefs),curIdf,atoi(yytext),0,0);

				result=true;
				}else
				{
				result = false;
				}
			}else
			{
			result = false;
			}
		}else
		{
			if(token==DROP_TOKEN)
			{
				token=_liretoken();
				if(_column_name())
				{

					//TYPE DROP
					typeAlter = 3;

				result=true;
				}else
				{
				result = false;
				}
			}else
			{
				if(token==WITH_TOKEN)
				{
					token=_liretoken();
					if(_table_options())
					{

						//TYPE WITH
						typeAlter = 4;

					result=true;
					}else
					{
					result = false;
					}
				}else
				{
				result = false;
				}
			}
		}
	}
 return result;
}

	/*=================================================================================================*
	 *	alter_table_stmt : K_ALTER (K_TABLE | K_COLUMNFAMILY) table_name alter_table_instruction   *
	 *=================================================================================================*/
boolean _alter_table_stmt()
{
	boolean result;
	if(token==ALTER_TOKEN)
	{
		token=_liretoken();
		if(token==TABLE_TOKEN || token==COLUMNFAMILY_TOKEN)
		{
			token=_liretoken();
			if(_table_name())
			{
				token=_liretoken();
				if(_alter_table_instruction())
				{
					token=_liretoken();
					if(token==PVIRG_TOKEN || token==APPLY_TOKEN)
					{
					result=true;
					}else
					{
					  result=false;
					}
				}else
				{
				  result=false;
				}
			}else
			{
			  result=false;
			}
		}else
		{
		  result=false;
		}
	}else
	{
	  result=false;
	}
     return result;
}



/*
STATEMENT : STATEMENT_KEYSPACE | STATEMENT_TABLE
*/
/*
boolean _statement(){

	boolean result;

	if( _statement_keyspace() )
	{
		result = true;
	}
	else if( _statement_table() )
        {
          result = true;
        }
        else result = false;

	return result;
}
*/

/*
STATEMENT
*/


/*=========================================================================================*
									SELECT_CLAUSE : column_name SELECT_CLAUSE_AUX
*=========================================================================================*/
boolean _SELECT_CLAUSE(){

	boolean result;
	if(_column_name()){

		token=_liretoken();
		result=_SELECT_CLAUSE_AUX();

	}else
	{
		result = false;
	}
	return result;
}

/*=========================================================================================*
									SELECT_CLAUSE_AUX : ',' SELECT_CLAUSE | epsilone
*=========================================================================================*/
boolean _SELECT_CLAUSE_AUX(){

	boolean result;
	if(token == FROM_TOKEN){

		follow_token=true;
		result = true;
	}else
	{
		if (token == VIRG_TOKEN){

			token=_liretoken();
			if(_SELECT_CLAUSE()){
				result = true;
			}else
			{
				result = false;
			}
		}else
		{
			result = false;
		}
	}
	return result;
}

/*=========================================================================================*
	 *statement : drop_keyspace_stmt | create_keyspace_stmt | alter_keyspace_stmt | use_stmt   *
	 *   |create_table_stmt | alter_table_stmt | drop_table_stmt | truncate_table_stmt	   *
    	 *   | create_index_stmt| drop_index_stmt | insert_stmt | update_stmt | delete_stmt	   *
	 *   | batch_stmt									   *
	 *=========================================================================================*/
boolean _statement()
{
	boolean result;
	if(token==CREATE_TOKEN)
	{
		token=_liretoken();
		if(token==TABLE_TOKEN || token==COLUMNFAMILY_TOKEN)
		{

			reqt = 2;   //REQUETE CREATE TABLE
			token=_liretoken();
			if(token==IF_TOKEN)
			{
			token=_liretoken();
			if(token==NOT_TOKEN)
			{
				token=_liretoken();
				if(token==EXISTS_TOKEN)
				{
					token=_liretoken();
					if(_table_name())
					{
						if( recherche_Nom_table(listeTable,curIdf,nameKeyspace) == 1 ) inserer_optionsError(TABLENAMEFOUND, yylineno);
						//if( nomTableInvalid(curIdf) == 1 ) inserer_optionsError(TABLENAMEINVALID, yylineno);

						//CREER TABLERI
						creer_tableRI(curIdf, nameKeyspace);

						//VERIFIER SI LE KEYSPACE EXISTE DEJA
						if( strcmp(nameKeyspace,"defaultKeyspace") != 0 ){

								if( recherche_Nom_Keyspace( listeKeyspace , nameKeyspace ) == -1  ) inserer_optionsError(KEYSPACENAMENOTFOUND, yylineno);

						}

						token=_liretoken();
						if(_column_definitions())
						{
							token=_liretoken();
								if(token == PVIRG_TOKEN)
							{

									affichage_resultat();
									//INTERPRETER CREATE TABLE
									if(	nbrErrSm == 0 ) { 					insert_Table(&listeTable,tableRI);
																									sauvegarderListeTable();

																			}

								 follow_token=true;
								 result = true;
							}else
									 if (token == WITH_TOKEN)
									 {
										 token=_liretoken();
										 if (_table_options())
										 {

											 affichage_resultat();
											 //INTERPRETER CREATE TABLE
		 									if(	nbrErrSm == 0 ) { 					insert_Table(&listeTable,tableRI);
		 																									sauvegarderListeTable();
		 																			}

											result = true;

										 }else
										 {
											 syntaxique_erreur("Les options de la table manquantes\n");
											 result = false;
										 }
									 }else
									 {
										 	syntaxique_erreur("';' ou 'WITH' manquante\n");
										 	result = false;
									 }
						}else
						{
							syntaxique_erreur("'COLONNE DEFINITIONS' manquante\n");
							result=false;
						}
					}else
					{
						syntaxique_erreur("Le nom de la table manquant\n");
						result=false;
					}
				}else
				{
					syntaxique_erreur("'EXISTS' manquante\n");
					result=false;
				}
			}else
			{
				syntaxique_erreur("'NOT' manquante\n");
				result=false;
			}
		}else
		{
					if(_table_name())
					{

						if( recherche_Nom_table(listeTable,curIdf,nameKeyspace) == 1 ) inserer_optionsError(TABLENAMEFOUND, yylineno);

						//CREER TABLERI
						creer_tableRI(curIdf, nameKeyspace);

						//VERIFIER SI LE KEYSPACE EXISTE DEJA
						if( strcmp(nameKeyspace,"defaultKeyspace") != 0 ){

								if( recherche_Nom_Keyspace( listeKeyspace , nameKeyspace ) == -1  ) inserer_optionsError(KEYSPACENAMENOTFOUND, yylineno);

						}

						token=_liretoken();
						if(_column_definitions())
						{
							token=_liretoken();
								if(token == PVIRG_TOKEN)
							{
								affichage_resultat();
								//INTERPRETER CREATE TABLE
								if(	nbrErrSm == 0 ) { 					insert_Table(&listeTable,tableRI);
																								sauvegarderListeTable();
																		}

								 follow_token=true;
								 result = true;
							}else
									 if (token == WITH_TOKEN)
									 {

										 token=_liretoken();

										 if (_table_options())
										 {
											 token=_liretoken();
											 if (token == PVIRG_TOKEN)
											 {
												 affichage_resultat();
												 //INTERPRETER CREATE TABLE
												 if(	nbrErrSm == 0 ) { 					insert_Table(&listeTable,tableRI);
																												 sauvegarderListeTable();
																						 }

										    result = true;

											 }else
											 {
												 syntaxique_erreur("Les options de la table manquantes\n");
												 result = false;
											 }

										 }else
										 {
											 syntaxique_erreur("';' ou 'WITH' manquante\n");
											 result = false;
										 }
									 }else
									 {
										 syntaxique_erreur("'WITH' manquante\n");
										 result = false;
									 }
						}else
						{
							syntaxique_erreur("La definitions des colonnes manquante\n");
							result=false;
						}
					}else
					{
						syntaxique_erreur("Le nom de la table manquant\n");
						result=false;
					}
		}

		}
		else{
			if(token==INDEX_TOKEN)
			{
				affichage_resultat();
				result=true;
			}else
			{
				if(token==KEYSPACE_TOKEN)
				{


								reqt = 1;   //REQUETE CREATE KEYSPACE
								token=_liretoken();
								if(token==IF_TOKEN)
								{
									token=_liretoken();
									if(token==EXISTS_TOKEN)
									{
										token=_liretoken();
										if(_keyspace_name())
										{
											//CREER KEYSPACE NODE
											creer_keyspaceNode(curIdf, NULL);
											creer_keyspaceRI(curIdf);

											if( recherche_Nom_Keyspace( listeKeyspace , curIdf ) == 1 ) inserer_optionsError(KEYSPACENAMEFOUND, yylineno);

											token=_liretoken();
											if(token==WITH_TOKEN)
											{
												token=_liretoken();
												if(_properties())
												{
													affichage_resultat();
												  result=true;
												}else
												{
													syntaxique_erreur("Les proprieties manquantes\n");
												  result=false;
												}
											}else
											{
												syntaxique_erreur("'WITH' manquante\n");
											  result=false;
											}
										}else
										{
											syntaxique_erreur("Le nom de keyspace manquant\n");
										  result=false;
										}
									}else
									{
										syntaxique_erreur("'EXISTS' manquante\n");
									  result=false;
									}
								}else
								{
									if(_keyspace_name())
									{
										//CREER KEYSPACE NODE
										creer_keyspaceNode(curIdf, NULL);
										creer_keyspaceRI(curIdf);

											if( recherche_Nom_Keyspace( listeKeyspace , curIdf ) == 1 ) inserer_optionsError(KEYSPACENAMEFOUND, yylineno);


									  	token=_liretoken();
										if(token==WITH_TOKEN)
										{
											token=_liretoken();
											if(_properties())
											{
												affichage_resultat();
											  result=true;
											}else
											{
												syntaxique_erreur("Les proprieties manquantes\n");
											  result=false;
											}
										}else
										{
											syntaxique_erreur("'WITH' manquante\n");
										  result=false;
										}
									}else
									{
										syntaxique_erreur("Le nom de keyspace ou 'IF' manquante\n");
									  result=false;
									}
								}



				}
			else{
				syntaxique_erreur("'TABLE' ou 'INDEX' ou 'KEYSPACE' manquante\n");
				result=false;
				}
			}
		}
	}else
	{
		if(token==DROP_TOKEN)
		{
			token=_liretoken();
			if(token==TABLE_TOKEN)
			{
				token=_liretoken();
				if(token==IF_TOKEN)
				{
					token=_liretoken();
					if(token==EXISTS_TOKEN)
					{
						token=_liretoken();
						if(_table_name())
						{

							if( recherche_Nom_table(listeTable,curIdf,nameKeyspace) != 1 ) inserer_optionsError(TABLENOTFOUND, yylineno);

							//CREER TABLERI
							creer_tableRI(curIdf, nameKeyspace);

							//VERIFIER SI LE KEYSPACE EXISTE DEJA
							if( strcmp(nameKeyspace,"defaultKeyspace") != 0 ){

									if( recherche_Nom_Keyspace( listeKeyspace , nameKeyspace ) == -1  ) inserer_optionsError(KEYSPACENAMENOTFOUND, yylineno);

							}


							affichage_resultat();
							if( nbrErrSm == 0 ) supprimer_table(&listeTable,tableRI);

						  result=true;

						}else
						{
						  result=false;
						}
					}else
					{
					  result=false;
					}
				}else
				{
					if(_table_name())
					{



						if( recherche_Nom_table(listeTable,curIdf,nameKeyspace) != 1 ) inserer_optionsError(TABLENOTFOUND, yylineno);

						//CREER TABLERI
						creer_tableRI(curIdf, nameKeyspace);

						//VERIFIER SI LE KEYSPACE EXISTE DEJA
						if( strcmp(nameKeyspace,"defaultKeyspace") != 0 ){

								if( recherche_Nom_Keyspace( listeKeyspace , nameKeyspace ) == -1  ) inserer_optionsError(KEYSPACENAMENOTFOUND, yylineno);

						}


						affichage_resultat();
						if( nbrErrSm == 0 ) supprimer_table(&listeTable,tableRI);

					  result=true;

					}else
					{
					  result=false;
					}
				}
			}else
			{
				if(token==INDEX_TOKEN)
				{
					affichage_resultat();
					result=true;

				}else
				{
					if(token==KEYSPACE_TOKEN)
					{
						token=_liretoken();
						if(token==IF_TOKEN)
						{
							token=_liretoken();
							if(token==EXISTS_TOKEN)
							{
								token=_liretoken();
								if(_keyspace_name())
								{
									affichage_resultat();
								  result=true;
								}else
								{
								  result=false;
								}
							}else
							{
							  result=false;
							}
						}else
						{
							if(_keyspace_name())
							{
								affichage_resultat();
							  result=true;
							}else
							{
							  result=false;
							}
						}
					}else
					{
					result=false;
					}
				}
			}
		}else
		{
			if(token==ALTER_TOKEN)
			{

				token=_liretoken();
				if(token==TABLE_TOKEN || token==COLUMNFAMILY_TOKEN)
				{

					reqt = 2;   //REQUETE ALTER TABLE
					token=_liretoken();
					if(_table_name())
					{


						//VERIFIER SI LE KEYSPACE EXISTE DEJA
						if( strcmp(nameKeyspace,"defaultKeyspace") != 0 ){

								if( recherche_Nom_Keyspace( listeKeyspace , nameKeyspace ) == -1  ) inserer_optionsError(KEYSPACENAMENOTFOUND, yylineno);

						}

						if( recherche_Nom_table(listeTable,curIdf,nameKeyspace) != 1 ) inserer_optionsError(TABLENOTFOUND, yylineno);

						//CREER TABLERI
						creer_tableRI(curIdf, nameKeyspace);

						token=_liretoken();
						if(_alter_table_instruction())
						{
							token=_liretoken();
							if(token==PVIRG_TOKEN || token==APPLY_TOKEN)
							{
								affichage_resultat();
								if( nbrErrSm == 0 ) modifier_table(tableRI, typeAlter ,yylineno);

								result=true;

							}else
							{
								result=false;
							}
						}else
						{
							result=false;
						}
					}else
					{
						result=false;
					}

				}else
				{
					if(token==KEYSPACE_TOKEN)
					{

						reqt = 1;   //REQUETE ALTER KEYSPACE
						token=_liretoken();
						if(_keyspace_name())
						{
							//CREER KEYSPACE NODE
							creer_keyspaceNode(curIdf, NULL);
							creer_keyspaceRI(curIdf);

							if( recherche_Nom_Keyspace( listeKeyspace , curIdf ) != 1 ) inserer_optionsError(KEYSPACENAMENOTFOUND, yylineno);

							token=_liretoken();
							if(token==WITH_TOKEN)
							{
								token=_liretoken();
								if(_properties())
								{

									affichage_resultat();
									if( nbrErrSm == 0 ) modifier_keyspace(keyspaceRI);

									result=true;

								}else
								{
									result=false;
								}
							}else
							{
								result=false;
							}
						}else
						{
							result=false;
						}

					}else
					{
						result=false;
					}
				}
			}else
			{
				if(token==INSERT_TOKEN)					/* INSERT INTO <table_name> ... */
				{
					token=_liretoken();
					if(token==INTO_TOKEN)
					{
						token=_liretoken();
						if(_table_name())
						{

							//VERIFIER SI LE KEYSPACE EXISTE DEJA
							if( strcmp(nameKeyspace,"defaultKeyspace") != 0 ){

									if( recherche_Nom_Keyspace( listeKeyspace , nameKeyspace ) == -1  ) inserer_optionsError(KEYSPACENAMENOTFOUND, yylineno);

							}
							//RECUPERER LE NOM DE KEYSPACE
							nomKeyspaceForInsrt = (char*) malloc(50*sizeof(char));
							strcpy(nomKeyspaceForInsrt,nameKeyspace);

							if( recherche_Nom_table(listeTable,curIdf,nameKeyspace) != 1 ) inserer_optionsError(TABLENOTFOUND, yylineno);

							//RECUPERER LE NOM DE LA TABLE
							nomTableForInsrt = (char*) malloc(50*sizeof(char));
							strcpy(nomTableForInsrt,curIdf);

							valrMaps = NULL;

							token=_liretoken();
							if(_column_names())
							{
								token=_liretoken();
								if(token==VALUES_TOKEN)
								{
									token=_liretoken();
									if(_column_values())
									{
										token=_liretoken();
										if(token == PVIRG_TOKEN)
										{

											affichage_resultat();

											 inserer_ligne_table(nomTableForInsrt,nomKeyspaceForInsrt, valrMaps);
											 if( nbrErrSm == 0 ) {
												 											ecrire_DB_file();
																							printf("\nCQL> La ligne est inseree (%s.%s)",nomKeyspaceForInsrt,nomTableForInsrt);
																						}

										   follow_token=true;
										   result = true;
										}else
										     	if(token==IF_TOKEN)
											{
												token=_liretoken();
											  	if(token==NOT_TOKEN)
												{
													token=_liretoken();
												  	if(token==EXISTS_TOKEN)
													{
														token=_liretoken();
													  	if(token == PVIRG_TOKEN || token == APPLY_TOKEN)
														{

															 affichage_resultat();
														   follow_token=true;
														   result = true;
														}else
														     if (_upsert_options())
														     {
																	 	affichage_resultat();
																	 	result=true;
														     }else
														     {
															result = false;
														     }
													}else
													{
													  result=false;
													}
												}else
												{
												  result=false;
												}
											}else
											{
												if(_upsert_options())
												{
													affichage_resultat();
												  result=true;
												}else
												{
													syntaxique_erreur("';' manquante\n");
												  result=false;
												}
											}

									}else
									{
										syntaxique_erreur("La ligne manquante\n");
									  result=false;
									}
								}else
								{
									syntaxique_erreur("'VALUES' manquante\n");
								  result=false;
								}
							}else
							{
								syntaxique_erreur("Les colonnes manquantes\n");
							  result=false;
							}
						}else
						{
							syntaxique_erreur("Le nom de la table manquant\n");
						  result=false;
						}
					}else
					{
						syntaxique_erreur("'INTO' manquante\n");
					  result=false;
					}
				}else
				{
					if(token==UPDATE_TOKEN)
					{
						token=_liretoken();
						if(_table_name())
						{
							token=_liretoken();
							if(token==SET_TOKEN)
							{
								token=_liretoken();
								if(_update_assignments())
								{
									token=_liretoken();
									if(token==WHERE_TOKEN)
									{
									 	token=_liretoken();
										if(_where_clause())
										{
											token=_liretoken();
											if(token == PVIRG_TOKEN)
											{
											   follow_token=true;
											   result = true;
												 affichage_resultat();

											}else
											     if (_update_conditions())
											     {
														 	result=true;
															affichage_resultat();

											     }else
											     {
												result = false;
											     }
										}else
										{

										}

									}else
									{
									result = false;
									}
								}else
								{
								result = false;
								}
							}else
							{
								if(_upsert_options())
								{
								    token=_liretoken();
								    if(token==SET_TOKEN)
								    {
									token=_liretoken();
									if(_update_assignments())
									{
										token=_liretoken();
										if(token==WHERE_TOKEN)
										{
										 	token=_liretoken();
											if(_where_clause())
											{
												token=_liretoken();
												if(token == PVIRG_TOKEN)
												{
												   follow_token=true;
												   result = true;
													 affichage_resultat();

												}else
												     if (_update_conditions())
												     {
															 		result=true;
																	affichage_resultat();

												     }else
												     {
													result = false;
												     }
											}else
											{
											 result = false;
											}

										}else
										{
										result = false;
										}
									}else
									{
									result = false;
									}
								    }else
								    {
								    result=false;
								    }
								}else
								{
								result = false;
								}
							}
						}else
						{
						result = false;
						}
					}else
					{
						if(token==DELETE_TOKEN)
						{
							token=_liretoken();
							if(token==FROM_TOKEN)
							{
								token=_liretoken();
								if(_table_name())
								{
									token=_liretoken();
									if(token==WHERE_TOKEN)
									{
									  	token=_liretoken();
										if(_where_clause())
										{
											token=_liretoken();
											if(token == PVIRG_TOKEN)
											{
													result=true;
													affichage_resultat();

											}else
											{
												if(_delete_conditions())
												{
														result=true;
														affichage_resultat();

												}else
												{
													syntaxique_erreur("';' ou 'DELETE CONDITIONS' manquante\n");
													result = false;
												}
											}
										}else
										{
												syntaxique_erreur("'WHERE CLAUSE' manquante\n");
										    result=false;
										}
									}else
									{
										if(token==USING_TOKEN)
										{
										  	token=_liretoken();
											if(token==TIMESTAMP_TYPE_TOKEN)
											{
												token=_liretoken();
												if(token==INTEGER_TOKEN)
												{
													token=_liretoken();
													if(token==WHERE_TOKEN)
													{
													  	token=_liretoken();
														if(_where_clause())
														{
															token=_liretoken();
															if(token == PVIRG_TOKEN)
															{
																	result=true;
																	affichage_resultat();

															}else
															{
																if(_delete_conditions())
																{
																		result=true;
																		affichage_resultat();
																}else
																{
																	syntaxique_erreur("';'ou 'DELETE CONDITIONS' manquante\n");
																	result = false;
																}
															}
														}else
														{
																syntaxique_erreur("'WHERE CLAUSE' manquante\n");
														    result=false;
														}
													}else
													{
														syntaxique_erreur("'WHERE' manquante\n");
													  result=false;
													}
												}else
												{
													syntaxique_erreur("'INTEGER' manquante\n");
												  result=false;
												}
											}else
											{
												syntaxique_erreur("'TIMESTAMP TYPE' manquante\n");
											  result=false;
											}
										}else
										{
											syntaxique_erreur("'WHERE' ou 'USING' manquante\n");
										  result=false;
										}
									}
								}else
								{
									syntaxique_erreur("Le nom de la table manquant\n");
								  result=false;
								}
							}else
							{
							  	if(_delete_selections())
								{
									token=_liretoken();
									if(token==FROM_TOKEN)
									{
									  	token=_liretoken();
										if(_table_name())
										{
											token=_liretoken();
											if(token==WHERE_TOKEN)
											{
											  	token=_liretoken();
												if(_where_clause())
												{
													token=_liretoken();
													if(token == PVIRG_TOKEN)
													{
															result=true;
															affichage_resultat();

													}else
													{
														if(_delete_conditions())
														{
																result=true;
																affichage_resultat();

														}else
														{
															syntaxique_erreur("';'ou 'DELETE CONDITIONS' manquante\n");
														result = false;
														}
													}
												}else
												{
														syntaxique_erreur("'WHERE CLAUSE' manquante\n");
												    result=false;
												}
											}else
											{
												if(token==USING_TOKEN)
												{
												  	token=_liretoken();
													if(token==TIMESTAMP_TYPE_TOKEN)
													{
														token=_liretoken();
														if(token==INTEGER_TOKEN)
														{
															token=_liretoken();
															if(token==WHERE_TOKEN)
															{
															  	token=_liretoken();
																if(_where_clause())
																{
																	token=_liretoken();
																	if(token == PVIRG_TOKEN)
																	{
																			result=true;
																			affichage_resultat();

																	}else
																	{
																		if(_delete_conditions())
																		{
																				result=true;
																				affichage_resultat();

																		}else
																		{
																			syntaxique_erreur("';' ou 'DELETE CONDITIONS' manquante\n");
																			result = false;
																		}
																	}
																}else
																{
																		syntaxique_erreur("'WHERE CLAUSE' manquante\n");
																    result=false;
																}
															}else
															{
																syntaxique_erreur("'WHERE' manquante\n");
															  result=false;
															}
														}else
														{
															syntaxique_erreur("'INTEGER' manquante\n");
														  result=false;
														}
													}else
													{
														syntaxique_erreur("'TIMESTAMP' manquante\n");
													  result=false;
													}
												}else
												{
													syntaxique_erreur("'WHERE' ou 'USING' manquante\n");
												  result=false;
												}
											}
										}else
										{
											syntaxique_erreur("Le nom de la table manquant\n");
										  result=false;
										}
									}else
									{
										syntaxique_erreur("'FROM' manquante\n");
									  result=false;
									}
								}else
								{
									syntaxique_erreur("'FROM' ou 'Delete selections' manquante\n");
								  result=false;
								}
							}
						}else
						{
							if(token==TRUNCATE_TOKEN)
							{
								token=_liretoken();
								if(_table_name())
								{
								  result=true;
									affichage_resultat();
								}else
								{
									syntaxique_erreur("Le nom de la table manquant\n");
								  result=false;
								}
							}else
							{
								if(token==USE_TOKEN)
								{
									token=_liretoken();
									if(_keyspace_name())
									{
											result=true;
											affichage_resultat();
									}else
									{
										syntaxique_erreur("Le nom de keyspace manquant\n");
										result = false;
									}
								}else
								{
									if(token==BATCH_TOKEN)
									{
										result=true;
										affichage_resultat();
									}else
									{

										if( token == SELECT_TOKEN ){

											token=_liretoken();
											if( token == ETOILE_TOKEN ){ //SELECT '*'

												token=_liretoken();
												if( token == FROM_TOKEN ){

													token=_liretoken();
													if( _table_name() ){

														//VERIFIER SI LE KEYSPACE EXISTE DEJA
														if( strcmp(nameKeyspace,"defaultKeyspace") != 0 ){

																if( recherche_Nom_Keyspace( listeKeyspace , nameKeyspace ) == -1  ) inserer_optionsError(KEYSPACENAMENOTFOUND, yylineno);

														}
														//RECUPERER LE NOM DE KEYSPACE
														nomKeyspaceForInsrt = (char*) malloc(50*sizeof(char));
														strcpy(nomKeyspaceForInsrt,nameKeyspace);

														if( recherche_Nom_table(listeTable,curIdf,nameKeyspace) != 1 ) inserer_optionsError(TABLENOTFOUND, yylineno);

														//RECUPERER LE NOM DE LA TABLE
														nomTableForInsrt = (char*) malloc(50*sizeof(char));
														strcpy(nomTableForInsrt,curIdf);

														token=_liretoken();
														if( token == PVIRG_TOKEN ){

															affichage_resultat();

															//INTERPRER SELECT * FROM keyspace.table
															if( nbrErrSm == 0 ) get_tous_lignes_table(nomTableForInsrt, nomKeyspaceForInsrt);

															result = true;

														}
														else {
															syntaxique_erreur("';' manquante\n");
															result = false;
														}

													}else{
														syntaxique_erreur(" Le nom de la table manquante\n");
														result = false;
													}
												}
												else{
													syntaxique_erreur("'FROM' manquante\n");
													result = false;
												}

											}
											else{

												if( token == COUNT_TOKEN ){ //SELECT COUNT(*)

													token=_liretoken();
													if( token == POPEN_TOKEN ){

														token=_liretoken();
														if( token == ETOILE_TOKEN ){

															token=_liretoken();
															if( token == PCLOSE_TOKEN ){

																token=_liretoken();
																if( token == FROM_TOKEN ){

																	token=_liretoken();
																	if( _table_name() ){

																		token=_liretoken();
																		if( token == PVIRG_TOKEN ){

																			result = true;
																			affichage_resultat();

																		}
																		else {
																			syntaxique_erreur("';' manquante\n");
																			result = false;
																		}

																	}else{
																		syntaxique_erreur("Le nom de la table manquante\n");
																		result = false;
																	}
																}
																else{
																	syntaxique_erreur("'FROM' manquante\n");
																	result = false;
																}

															}
															else {
																syntaxique_erreur("')' manquante\n");
																result = false;
															}

														}
														else {
															syntaxique_erreur("'*' manquante\n");
															result = false;
														}

													}
													else {
														syntaxique_erreur("'(' manquante\n");
														result = false;
													}

												}
												else{

													if( _SELECT_CLAUSE() ){ //SELECT <colonne_name>,...

														token=_liretoken();
														if( token == FROM_TOKEN ){

															token=_liretoken();
															if( _table_name() ){

																token=_liretoken();
																if( token == PVIRG_TOKEN ){

																	result = true;
																	affichage_resultat();

																}
																else {
																	syntaxique_erreur("';' manquante\n");
																	result = false;
																}

															}else{
																syntaxique_erreur("Le nom de la table manquant\n");
																result = false;
															}
														}
														else{
															syntaxique_erreur("'FROM' manquante\n");
															result = false;
														}

													}
													else{
														syntaxique_erreur("'SELECT_CLAUSE' manquante\n");
														result = false;
													}
												}
											}


										}else{
											syntaxique_erreur("Requete invalide\n");
											result=false;
										}

									}
								}
							}
						}
					}
				}
			}
		}
	}

  return result;
}



void affichage_resultat(){

	printf("\n\nCQL> RESULTAT :\n") ;
	printf("CQL> 0 Erreurs lexicales\n");
	printf("CQL> 0 Erreurs syntaxiques\n");
	if(reqt == 1) map_error();               					//TRAITEMENT DES ERREURS POUR LES REQUETE DE KEYSPACE
	if(reqt == 2) isTableColumnValid();      					//TRAITEMENT DES ERREURS AU NIVAUX DES COLONNES LORS DES REQUETES DE TABLE
	printf("CQL> %d Erreurs semantiques\n",nbrErrSm);
	afficher_listeOptionsError();											//AFFICHAR DES ERREURS SEMANTIQUES

}

void syntaxique_erreur(char * msgErr)
{
		printf("\nCQL> Erreurs syntaxiques : %s \n",msgErr);

}

//=============MAIN :fonction principale=========
int main(int argc, char * argv)
{

system("cls");

/*listeTable = NULL;
listeKeyspace = NULL;*/
chargerListeTable();			//CHARGER LE DICTIONNAIRE DE DONNEES DES TABLES
chargerListeKeyspace();		//CHARGER LE DICTIONNAIRE DE DONNEES DES KEYSPACES
lire_DB_file();						//CHARGER LE CONTENUE LES LIGNES DE TOUTES LES TABLES DE LA BASE DE DONNEES


		token = _liretoken();

		if (_statement()==true)
		{

			//if(reqt ==2) afficher_tableRI();

			if( reqt==1 && nbrErrSm == 0 ) {	//INTERPRETATION DES REQUETES DE CREATION DES KEYSPACES
																				insert_Keyspace(&listeKeyspace,keyspaceRI);
																				sauvegarderListeKeyspaces();
																			}


//AFFICHAGE DE TOUTES LES TABLES AVEC LES LIGNES INSEREES
//afficher_toutes_tables();



			//if( reqt == 1 && nbrErrSm == 0 ) afficher_keyspace_values();   //KEYSPACE
      //if( reqt == 2 ) afficher_columnsTable();

		}

 printf("\n\nCQL> Tapez <ENTRER> pour quitter\n");
 getch();
}
