
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys\stat.h>
#include <sys\types.h>
#include <unistd.h>
#include <fcntl.h>
#include <direct.h>
#include <io.h>
#include <sys/stat.h>
//#include <windows.h>
#include "CassandraErreur.h"



/*===========================*
 *  LES ERREURS SEMANTIQUES  *
 *===========================*/

//NOMBRE D'ERREUR SEMANTIQUE
nbrErrSm = 0;
//NOMBRE DES COLONNES DECLAREES
nbrColDecl = 0;
//NOMBRE DE TABLE
nbrValTable = 0;

//CREER SM ERREUR
optionsError * creer_optionsError(OptionsErrorType et, int line){

	optionsError * e = (optionsError*) malloc(sizeof (optionsError) );
		e->linenumdecl = line;
		e->errort = et;

  return e;
}

//INSERER SM ERREUR DANS LA TABLE DES ERREURS
void inserer_optionsError(OptionsErrorType et, int line)
{
	tableErr[nbrErrSm] = creer_optionsError(et, line);
  nbrErrSm++;
}

//AFFICHAGE D'UNE ERREUR
void afficher_optionsError(OptionsErrorType et, int line)
{
  printf("CQL> Ligne %d :", line);
	switch (et)
	{
	  case REPLICATIONERROR_IDF: 			    	printf(" TYPE INCOMPATIBLE : Expected MAP after 'Replication = ' not IDF \n"); break;
	  case REPLICATIONERROR_CONST: 	     		printf(" TYPE INCOMPATIBLE : Expected MAP after 'Replication = ' not CONSTANTE \n"); break;
	  case DURABLE_WRITESERROR_NOTBOOL: 		printf(" TYPE INCOMPATIBLE : Expected boolean after 'Durable_writes = ' TRUE or FALSE \n"); break;
		case INVALIDKEYSPACEPROPERTY:					printf(" PROPERTY INVALID : Expected 'Replication' or 'Durable_writes' after WITH \n"); break;
		case INVALIDKEYSPACETERM:							printf(" TERM INVALID : Expected CONSTANT terms \n"); break;
		case INVALIDKEYSPACEFIRSTTERM:				printf(" TERM INVALID : Expected 'class' after '{' \n"); break;
		case INVALIDKEYSPACESTRATEGY:					printf(" TERM INVALID : Invalid strategy \n"); break;
		case REPLICATIONFACTOR_NEEDED:				printf(" TERM INVALID : Simple strategy needs replication_factor \n"); break;
		case INVALIDSIMPLESTRATEGY:						printf(" TERM INVALID : Simple strategy supports only replication_factor \n"); break;
		case INVALID_DATACENTER:							printf(" DATACENTER INVALID : Datacenters must be String not Integer \n"); break;
		case INVALID_DATACENTER_FACTOR:				printf(" DATACENTER FACTOR INVALID : Datacenter factor must be Integer not String \n"); break;
		case INVALID_REPLICATION_FACTORVALUE: printf(" REPLICATION FACTOR INVALID : Replication_factor value must be Integer \n"); break;
		case COMMENTVALUE_NOTCOMPATIBLE:			printf(" TYPE INCOMPATIBLE : COMMENT Option must be String \n"); break;
		case READREPAIRVALUE_NOTCOMPATIBLE:		printf(" TYPE INCOMPATIBLE : Read_repair_chance Option must be Float \n"); break;
		case DCLOCALREADVALUE_NOTCOMPATIBLE:	printf(" TYPE INCOMPATIBLE : Dclocal_read_repair_chance Option must be Float \n"); break;
		case BLOOMFILTERVALUE_NOTCOMPATIBLE:	printf(" TYPE INCOMPATIBLE : Bloom_filter_fp_chance Option must be Float \n"); break;
		case GCGRACEVALUE_NOTCOMPATIBLE:			printf(" TYPE INCOMPATIBLE : Gc_grace_seconds Option must be Integer \n"); break;
		case TIMETOLIVEVALUE_NOTCOMPATIBLE:		printf(" TYPE INCOMPATIBLE : Default_time_to_live Option must be Integer \n"); break;
		case COMPRESSIONVALUE_NOTCOMPATIBLE:	printf(" TYPE INCOMPATIBLE : COMPRESSION Option must be Map \n"); break;
		case CACHINGVALUE_NOTCOMPATIBLE:			printf(" TYPE INCOMPATIBLE : CACHING Option must be Map \n"); break;
		case COMPACTIONVALUE_NOTCOMPATIBLE:		printf(" TYPE INCOMPATIBLE : COMPACTION Option must be Map \n"); break;
		case INVALIDTABLEOPTIONS:							printf(" PROPERTY INVALID : Table option invalid \n"); break;
		case PLUSPRIMARYKEY:									printf(" PRIMARY KEY INVALID : We must have one primary key \n"); break;
		case STATICWITHPRIMARYKEY:						printf(" COLUMN INVALID : Static column must not be primary key \n"); break;
		case UNKNOWNCOLUMN:										printf(" COLUMN UNKNOWN : A column must be declared \n"); break;
		case TABLENAMEFOUND:									printf(" TABLE NAME INVALID : Table name already existe \n"); break;
		case TABLENAMEINVALID: 								printf(" TABLE NAME INVALID : Table name must not be a keyname  \n"); break;
		case KEYSPACENAMENOTFOUND:						printf(" KEYSPACE NAME INVALID : Keyspace doesn't existe  \n"); break;
		case TABLENOTFOUND:										printf(" TABLE NAME INVALID : Table doesn't existe  \n"); break;
		case COLONNENOTFOUND:									printf(" COLUMN INVALID : Column doesn't existe  \n"); break;
		case KEYSPACENAMEFOUND:								printf(" KEYSPACE NAME INVALID : Keyspace already existe  \n"); break;
		case COLUMNNAMENOTFOUND:							printf(" COLUMN NAME NOT FOUND : You must add a column name with columns after table name  \n"); break;

	}
}

//AFFICHAGE DE LA LISTE D'ERREURS
void afficher_listeOptionsError()
{
	int i = 0;
  if( nbrErrSm != 0 )  printf("\nCQL> ERREURS :\n");
	while (i < nbrErrSm)
	{
	       afficher_optionsError(tableErr[i]->errort, tableErr[i]->linenumdecl);
	       i++;
	}

}

/*=====================================*
 *  		 ERREURS DES KEYSPACES				 *
 *=====================================*/

//CREER KEYSPACE NODE
void creer_keyspaceNode(char* nomKeyspace, listPropertiesType * properties)
{
	Nkeyspace = (keyspaceNode*) malloc(sizeof (keyspaceNode) );
		Nkeyspace->keyspaceName = (char*) malloc(strlen(nomKeyspace) );
		strcpy(Nkeyspace->keyspaceName,nomKeyspace);
		Nkeyspace->listProp = properties;
}

//INSERER TERME DANS MAP
void inserer_mapTerm(char * leftTerme, int typeLeft, char * rightTerme, int typeRight)
{
	replicNode * liste = (replicNode *) malloc(sizeof(replicNode));
  	liste->termLeft = (char*) malloc(strlen(leftTerme) );
		strcpy(liste->termLeft,leftTerme);
		liste->termRight = (char*) malloc(strlen(rightTerme) );
		strcpy(liste->termRight,rightTerme);
		liste->typeLeft = typeLeft;
		liste->typeRight = typeRight;
  	liste->next = NULL;

  if (mapValue == NULL) {
    mapValue = liste;
  }else
  {
    replicNode * pliste = mapValue;

    while(pliste->next != NULL){
      pliste = pliste->next;
    }

    pliste->next = liste;
  }

}

//CREER UN NOEUD POUR LA PROPRIETY REPLICATION
propertyNode * creer_propertyNode_replication(replicNode* mapValue)
{
	propertyNode * propNode = (propertyNode*) malloc(sizeof (propertyNode) );
		propNode->propName = replication;
		propNode->node.mapVal = mapValue;

	return propNode;
}

//CREER UN NOEUD POUR LA PROPRIETY DURABLE WRITES
propertyNode * creer_propertyNode_durableWrites(boolean boolValue)
{
	propertyNode * propNode = (propertyNode*) malloc(sizeof (propertyNode) );
		propNode->propName = durable_writes;
		propNode->node.boolVal = boolValue;

	return propNode;
}

//INSERER UNE PROPRIETY DANS LA LISTE
void inserer_propertyNode(propertyNode proprietyValue)
{
	listPropertiesType * liste = (listPropertiesType *) malloc(sizeof(listPropertiesType));
  liste->prop = proprietyValue;
  liste->next = NULL;

  if (Nkeyspace->listProp == NULL) {
    Nkeyspace->listProp = liste;
  }else
  {
    listPropertiesType * pliste = Nkeyspace->listProp;

    while(pliste->next != NULL){
      pliste = pliste->next;
    }

    pliste->next = liste;
  }
}

//INSERER LA PROPRIETY Replication DANS LA LISTE
void inserer_propertyNode_replication(replicNode* mapValue)
{
	propertyNode * propNode = creer_propertyNode_replication(mapValue);
	inserer_propertyNode(*propNode);
}

//INSERER LA PROPRIETY Durable_writes DANS LA LISTE
void inserer_propertyNode_durableWrites(boolean boolValue)
{
	propertyNode * propNode = creer_propertyNode_durableWrites(boolValue);
	inserer_propertyNode(*propNode);
}

//LES ERREURS DE MAP
void map_error()
{

	listPropertiesType * pp = Nkeyspace->listProp;		//LE NOM DU KEYSPACE
	while( pp != NULL){																//POUR CHAQUE PROPRIETY

		 if(pp->prop.propName == replication){					//OPTION REPLICATION

			 replicNode * p = pp->prop.node.mapVal;				//MAP : REPLICATION VALUE

			 if(p != NULL)
			 {

			 //LE 1ER TERME LEFT DOIT ETRE 'CLASS'
			 if( strcmp(p->termLeft,"'class'") != 0 ) inserer_optionsError(INVALIDKEYSPACEFIRSTTERM,2);
			 else{

				 	if( strcmp(p->termRight,"'NetworkTopologyStrategy'") == 0 ){

						 //LE CAS DU NetworkTopologyStrategy QUI DOIT ETRE SUIVIE PAR DATACENTER NAME
						 replicNode * pnextt = p->next;
						 while(pnextt != NULL)
						 {
							 //on vérifie le type left et right
							 if( pnextt->typeLeft == 0 ) inserer_optionsError(INVALID_DATACENTER,2);
							 if( pnextt->typeRight == 1 ) inserer_optionsError(INVALID_DATACENTER_FACTOR,2);
							 pnextt = pnextt->next;
						 }

					}else{

						//LE CAS DU SIMPLE STRATEGY QUI DOIT ETRE SUIVIE PAR REPLICATION_FACTOR
						if( strcmp(p->termRight,"'SimpleStratgy'") == 0 ){

							replicNode * pnext = p->next;

							if( pnext == NULL )
							{
								inserer_optionsError(REPLICATIONFACTOR_NEEDED,2);
							}else
							{
								//L'OPTION REPLICATION_FACTOR IS NEEDED
								if(  strcmp(pnext->termLeft,"'replication_factor'") != 0 ) inserer_optionsError(REPLICATIONFACTOR_NEEDED,2);
								else{
										//On suppose que pnext->termRight est un Integer
										if( pnext->typeRight == 1 ) inserer_optionsError(INVALID_REPLICATION_FACTORVALUE,2);
										if( pnext->next != NULL ) inserer_optionsError(INVALIDSIMPLESTRATEGY,2);
								}
							}

						}else{

									//STRATEGY INVALIDE
									inserer_optionsError(INVALIDKEYSPACESTRATEGY,2);
								}

					}

			 }
		 }
		 }
		 pp = pp->next;
 }

}

//AFFICHAGE KEYSPACE VALUES
void afficher_keyspace_values()
{
	 printf("\n keyspace : %s ",Nkeyspace->keyspaceName);

	 listPropertiesType * pp = Nkeyspace->listProp;
	 while( pp != NULL){

		 	if(pp->prop.propName == durable_writes){
	 			printf("\n type : %d ",(pp->prop.node.boolVal == true)?1:0);
			}
			else{

	 			replicNode * p = pp->prop.node.mapVal;
	 			while(p != NULL)
	 			{
	 				printf("\n left : %s(%d) : right : %s(%d) ",p->termLeft, p->typeLeft, p->termRight,p->typeRight);
					p = p->next;
				}

			}
			pp = pp->next;
	}
}


/*=====================================*
 *  		 		ERREURS DES TABLES				 *
 *=====================================*/

//VERIFIER SI LES OPTIONS DU TABLE SONT VALIDE
void isTableOptionsValid(int yylineno){

	if( reqt==2 && strcmp(curPropName,"comment") != 0
							&& strcmp(curPropName,"read_repair_chance") != 0
						 	&& strcmp(curPropName,"dclocal_read_repair_chance") != 0
							&& strcmp(curPropName,"gc_grace_seconds") != 0
							&& strcmp(curPropName,"bloom_filter_fp_chance") != 0
							&& strcmp(curPropName,"default_time_to_live") != 0
							&& strcmp(curPropName,"compaction") != 0
							&& strcmp(curPropName,"compression") != 0
							&& strcmp(curPropName,"caching") != 0	)
	{
		//Créer une erreurs sémantique lorsque curPropName est invalide
		inserer_optionsError(INVALIDTABLEOPTIONS,yylineno);
	}

}

//TABLE COLUMNS

//CREER CULOMN
NColumn * creer_columnNode(char* nomVar/*, typeClmTable typeClm*/, boolean staticc, boolean primaryKey, int line){

	NColumn * e = (NColumn*) malloc(sizeof (NColumn) );
		e->nomVar = (char*) malloc(strlen(nomVar) );
		strcpy(e->nomVar,nomVar);
		e->staticc = staticc;
		e->primaryKey = primaryKey;
		e->line = line;

		return e;

}
//INSERER COLUNM
void inserer_columnNode(char* nomVar/*, typeClmTable typeClm*/, boolean staticc, boolean primaryKey, int line){

	columnTable[nbrColDecl] = creer_columnNode(nomVar/*,typeClm*/,staticc,primaryKey,line);
  nbrColDecl++;

}
//AFFICHAGE D'UNE COLONNE
void afficher_columnNode(char* nomVar/*, typeClmTable typeClm*/, boolean staticc, boolean primaryKey, int line){

	printf("Ligne %d :\nVar : %s	,	Static : %s	, PrimaryKey : %s	\n\n",line,nomVar,(staticc==true)?"True":"false",(primaryKey==true)?"True":"false");

}
//AFFICHAGE DE LA LISTE DES COLONNES DECLAREES
void afficher_columnsTable(){

	int i = 0;
  if( nbrColDecl != 0 )  printf("\n * COLONNES :\n\n");
	while (i < nbrColDecl)
	{
	       afficher_columnNode(columnTable[i]->nomVar/*, columnTable[i]->typeClm*/, columnTable[i]->staticc, columnTable[i]->primaryKey, columnTable[i]->line);
	       i++;
	}

}

//VERIFIER SI LES COLONNES DE TABLE SONT VALIDE
void isTableColumnValid(){

	int i = 0, nbrPK = 0, iPK = -1;
	while (i < nbrColDecl && nbrPK != 2)
	{
			if( columnTable[i]->primaryKey == true )
			{
				nbrPK++;		//NOMBRE DE PRIMARY KEY
				iPK = i;		//INDEX
			}
	    i++;
	}
	//PLUSIEURS PRIMARY KEY
	if( nbrPK == 2 ) inserer_optionsError(PLUSPRIMARYKEY, columnTable[i-1]->line);
	else{
		//SI ON A UN SEULE PRIMARY KEY QU4EST STATIC EN MEME TEMPS : ERREUR
		if( nbrPK == 1)
		{
			if(columnTable[iPK]->staticc == true) inserer_optionsError(STATICWITHPRIMARYKEY, columnTable[iPK]->line);
		}
	}

}

//VERIFIER SI PRIMARY KEY EST VALIDE (EXISTE ET N'EST PAS STATIC)
void isPrimaryKeyValid(char* var, int line){

	int i = 0;
	while (i < nbrColDecl && strcmp(columnTable[i]->nomVar,var) != 0 ) i++;

	if( i < nbrColDecl ) {
		if( columnTable[i]->staticc == true ) inserer_optionsError(STATICWITHPRIMARYKEY, line);
	}
	else inserer_optionsError(UNKNOWNCOLUMN, line);

}


//=========================================//
//					REPRESENTATION TABLE
//=========================================//
/*================================*
 *  FONCTIONS SAISIE COLONNES    *
 *==============================*/
void ajout_colonneDef(ColonneDefinitions *debut,char *nomColonne,int typeColonne,int valeurStatic,int valeurPrimaryKey)
{
   	ColonneDefinitions p=(ColonneDefinitions)malloc(sizeof(colonneDefinitions));
	strcpy(p->nom_colonne,nomColonne);
	p->type_colonne=typeColonne;
	p->valeurStatic=valeurStatic;
	p->valeurPrimary=valeurPrimaryKey;
        p->suiv=NULL;
        insert_colonneDef(debut,p);

}

/*==================================*
 *   FONCTIONS INSERTION COLONNES  *
 *================================*/

void insert_colonneDef(ColonneDefinitions *debut,ColonneDefinitions col)
{
	ColonneDefinitions prec,succ;
		prec=*debut;
    if( prec == NULL ){ //SI LA LISTE DES COLONNES EST VIDE
      *debut = col;
      col->suiv = NULL;
    }
    else{
		        succ=prec->suiv;
		        while(succ!=NULL)
		        {
			           prec=succ;
			           succ=prec->suiv;
		        }
		        prec->suiv=col;
		        col->suiv=succ;
    }
}


/*==================================*
 *   FONCTIONS CREATION RI TABLE   *
 *================================*/

void creer_tableRI(char* nom_table, char * nom_keyspace){ //colonneDefs = NULL; proprietes = NULL;

	tableRI = (table*) malloc(sizeof (table) );
		//NOM DE LA TABLE
		strcpy(tableRI->Nom_table,nom_table);
		//NOM DE KEYSPACE
		strcpy(tableRI->Nom_keyspace,nom_keyspace);

		tableRI->colonneDefs = NULL;
		tableRI->proprietes = NULL;

}



/*=================================*
  *   INTERPRETEUR CREATE TABLE   *
 *=================================*/

void insert_Table(Table *debut,Table tab)
{
		Table prec,succ;
		prec=*debut;

    if( prec == NULL ){ //SI LA LISTE DES TABLE EST VIDE
      *debut = tab;
      tab->suiv = NULL;
    }
    else{

		      succ=prec->suiv;
		      while(succ!=NULL)
		      {
			         prec=succ;
			         succ=prec->suiv;
		      }
		      prec->suiv=tab;
		      tab->suiv=succ;
  }

	//CREATION DB TABLE
	if( nbrErrSm == 0 ) {
			creer_table_dbfile(tab);
			printf("\nCQL> La table %s est cree",tab->Nom_table);
		}

}

/*==============================================================*
*  CREATION DES FICHIERS POUR LES TABLES DE LA BASE DE DONNEES  *
*===============================================================*/
void creer_table_dbfile(Table tab){

	char path[200];

	snprintf(path , sizeof(path) , "%s%s\\%s.json" ,CQL_PATH , tab->Nom_keyspace , tab->Nom_table);
	//printf("%s",path);
	int table = _open(path, _O_CREAT );
	close(table);

}

/*=================================*
  *   INTERPRETEUR ALTER TABLE    *
 *=================================*/

void modifier_table(Table tableRI, int typeAlter, int nligne ){

	Table table = NULL;
	ColonneDefinitions colonne = NULL;

			switch (typeAlter) {

				case 1:		table = get_table( listeTable ,tableRI->Nom_table ,tableRI->Nom_keyspace);
									colonne = recherche_Nom_column(table->colonneDefs ,tableRI->colonneDefs->nom_colonne );
									if( colonne != NULL ) colonne->type_colonne = tableRI->colonneDefs->type_colonne;
									else inserer_optionsError(COLONNENOTFOUND, nligne);

									break;

				case 2:   table = get_table( listeTable ,tableRI->Nom_table ,tableRI->Nom_keyspace);
									colonne = recherche_Nom_column(table->colonneDefs ,tableRI->colonneDefs->nom_colonne );
									if( colonne == NULL ) ajout_colonneDef(&(table->colonneDefs),tableRI->colonneDefs->nom_colonne,tableRI->colonneDefs->type_colonne,0,0);

									break;

				case 3:		table = get_table( listeTable ,tableRI->Nom_table ,tableRI->Nom_keyspace);
									colonne = recherche_Nom_column(table->colonneDefs ,tableRI->colonneDefs->nom_colonne );
								/*	if( colonne != NULL ) supprimer_colonne(&(table->colonneDefs),colonne);
									else inserer_optionsError(COLONNENOTFOUND, nligne);*/

									break;

			  case 4:		table = get_table( listeTable ,tableRI->Nom_table ,tableRI->Nom_keyspace);
									if( table != NULL ) table->proprietes = tableRI->proprietes;
									break;

			}

			sauvegarderListeTable();


}


/*=================================*
 * 			RECHERHCER COLONNE         *
 *=================================*/
ColonneDefinitions  recherche_Nom_column(ColonneDefinitions debut , char *nom_colonne ){

 	ColonneDefinitions p;
 	p=debut;
 	while(p!=NULL && strcmp(p->nom_colonne,nom_colonne)!=0){

 		p = p->suiv;

 		}

 	return p;
 }

 /*=================================*
   *   INTERPRETEUR DROP COLONNE   *
  *=================================*/
void supprimer_colonne(ColonneDefinitions * debut , ColonneDefinitions colonne){

ColonneDefinitions *prev;
ColonneDefinitions *q;
prev = debut;

if( prev == &colonne ){

	debut = &(*prev)->suiv;
	free(prev);

}
else{

	q = &(*prev)->suiv;

	while( q != NULL && q != &colonne ){
		prev = q;
		q = &(*q)->suiv;
	}

	(*prev)->suiv = (*q)->suiv;
	free(q);

}

}

//AFFICHAGE D'UNE COLONNE
void afficher_colonne(char* nomVar, int typeClm, int staticc, int primaryKey){

	printf("\nVar : %s	,	type : %d , Static : %d	, PrimaryKey : %d	\n\n",nomVar,typeClm,staticc,primaryKey);

}
//AFFICHAGE DE LA LISTE DES COLONNES DECLAREES
void afficher_colonnes_tableRI( ColonneDefinitions debut ){

	ColonneDefinitions p = debut;
  if( debut != NULL ){
				printf("\n * COLONNES :\n\n");
				while (p != NULL)
				{
	       			afficher_colonne(p->nom_colonne, p->type_colonne, p->valeurStatic, p->valeurPrimary);
	       			p = p->suiv;
				}
	}

}
//AFFICHAGE TABLERI
void afficher_tableRI(){

	printf("\n\n TABLE RI \n\n");
	printf(" Nom table : %s \n Nom keyspace : %s\n",tableRI->Nom_table,tableRI->Nom_keyspace);
	afficher_colonnes_tableRI( tableRI->colonneDefs );

}

//AFFICHAGE DE LA LISTE DES TABLES
void afficher_liste_table(){

	Keyspace keyspace = listeKeyspace;
	Table table;
	if( listeTable != NULL ){

		printf("\n\tKEYSPACES	\t\t LES TABLES  \n");
		printf("\n\t=========	\t\t ==========  \n");
		while( keyspace != NULL ){

			printf("\n\t%s\n",keyspace->Nom_keyspace);
			table = listeTable;
			while( table != NULL ){
				if( strcmp(table->Nom_keyspace,keyspace->Nom_keyspace) == 0)
							printf("\t\t\t\t\t%s\n",table->Nom_table);

				table = table->suiv;
			}
			printf("\n");

			keyspace = keyspace->suiv;
		}

		printf("\n\tdefaultKeyspace\n");
		table = listeTable;
		while( table != NULL ){
			if( strcmp(table->Nom_keyspace,"defaultKeyspace") == 0)
						printf("\t\t\t\t\t%s\n",table->Nom_table);

			table = table->suiv;
		}
		printf("\n");


	}


}


/*=========================*
  *   LISTES PROPRIETES   *
 *=========================*/

/*=================================*
 *  FONCTIONS SAISIE PROPRIETES    *
 *=================================*/
void ajout_Proprietes(Properties *debut,char *Nom_propriete,ValeurMaps valeurMaps,int ValeurBoolean,char* valeurString,float valeurFloat,int valeurInt)
{
   	Properties p=(Properties)malloc(sizeof(property));
	strcpy(p->Nom_propriete,Nom_propriete);
	strcpy((p->valeurPropriete).valeurString,valeurString);
	(p->valeurPropriete).valeurMaps=valeurMaps;
	(p->valeurPropriete).ValeurBoolean=ValeurBoolean;
	(p->valeurPropriete).valeurFloat=valeurFloat;
	(p->valeurPropriete).ValeurInt=valeurInt;
	 p->suiv=NULL;

        insert_Proprietes(debut,p);

}

/*==================================*
 *  FONCTIONS  INSERTION PROPRIETES *
 *==================================*/

void insert_Proprietes(Properties *debut,Properties props)
{
		Properties prec,succ;
		prec=*debut;

		if( prec == NULL ){ //SI LA LISTE EST VIDE
      *debut = props;
      props->suiv = NULL;
    }
    else{

				succ=prec->suiv;
				while(succ!=NULL)
				{
					prec=succ;
					succ=prec->suiv;
				}
				prec->suiv=props;
				props->suiv=succ;
		}
}

/*=======================*
  *  	LISTES TERMES     *
 *=======================*/
/*===========================*
 *  FONCTIONS SAISIE MAPS    *
 *===========================*/
void ajout_valeurMaps(ValeurMaps *debut,char *termGauche,int typeGauche,char *termDroite,int typeDroite)
{
   	ValeurMaps p=(ValeurMaps)malloc(sizeof(valeurMaps));
	strcpy(p->termGauche,termGauche);
	strcpy(p->termDroite,termDroite);
	p->typeGauche=typeGauche;
	p->typeDroite=typeDroite;
	p->suiv=NULL;

        insert_termeDef(debut,p);

}

/*==============================*
 *  FONCTIONS  INSERTION TERME  *
 *==============================*/

void insert_termeDef(ValeurMaps *debut,ValeurMaps valTerm)
{
	ValeurMaps prec,succ;
		prec=*debut;

	if(prec == NULL){
			*debut = valTerm;
			valTerm->suiv = NULL;
	}
	else{
				succ=prec->suiv;
				while(succ!=NULL)
				{
					prec=succ;
					succ=prec->suiv;
				}
				prec->suiv=valTerm;
				valTerm->suiv=succ;
			}
}

//VERIFIER SI LE NOM DE LA TABLE CORRESPONT A UN MOT CLES
int nomTableInvalid(char * nomTable){

	if(  strcmp(nomTable,"table") == 0  ||
			 strcmp(nomTable,"keyspace") == 0  ||
			  strcmp(nomTable,"add") == 0  ||
				 strcmp(nomTable,"alter") == 0  ||
				  strcmp(nomTable,"and") == 0  ||
					 strcmp(nomTable,"apply") == 0  ||
					  strcmp(nomTable,"begin") == 0  ||
						 strcmp(nomTable,"batch") == 0  ||
						  strcmp(nomTable,"clustering") == 0  ||
							 strcmp(nomTable,"columnfamily") == 0  ||
							  strcmp(nomTable,"create") == 0  ||
								 strcmp(nomTable,"custom") == 0  ||
								  strcmp(nomTable,"delete") == 0  ||
									 strcmp(nomTable,"drop") == 0  ||
									  strcmp(nomTable,"exists") == 0  ||
										 strcmp(nomTable,"false") == 0  ||
										  strcmp(nomTable,"from") == 0  ||
											 strcmp(nomTable,"if") == 0  ||
											  strcmp(nomTable,"in") == 0  ||
												 strcmp(nomTable,"index") == 0  ||
												  strcmp(nomTable,"insert") == 0  ||
													 strcmp(nomTable,"into") == 0  ||
													  strcmp(nomTable,"key") == 0  ||
														 strcmp(nomTable,"keyspace") == 0  ||
														  strcmp(nomTable,"list") == 0  ||
															 strcmp(nomTable,"map") == 0  ||
															  strcmp(nomTable,"not") == 0  ||
																 strcmp(nomTable,"on") == 0  ||
																  strcmp(nomTable,"option") == 0  ||
																	 strcmp(nomTable,"order") == 0  ||
																	  strcmp(nomTable,"primary") == 0  ||
																		 strcmp(nomTable,"select") == 0  ||
																		  strcmp(nomTable,"set") == 0  ||
																			 strcmp(nomTable,"static") == 0  ||
																			  strcmp(nomTable,"storage") == 0  ||
																				 strcmp(nomTable,"true") == 0  ||
																				  strcmp(nomTable,"truncate") == 0  ||
																					 strcmp(nomTable,"ttl") == 0  ||
																					  strcmp(nomTable,"type") == 0  ||
																						 strcmp(nomTable,"unlogger") == 0  ||
																						  strcmp(nomTable,"update") == 0  ||
																							 strcmp(nomTable,"use") == 0  ||
																							  strcmp(nomTable,"using") == 0  ||
																								 strcmp(nomTable,"values") == 0  ||
																								  strcmp(nomTable,"where") == 0  ||
																									 strcmp(nomTable,"with") == 0  ||
																									 strcmp(nomTable,"boolean") == 0  ||
																										strcmp(nomTable,"counter") == 0  ||
																										 strcmp(nomTable,"decimal") == 0  ||
																											strcmp(nomTable,"double") == 0  ||
																											 strcmp(nomTable,"float") == 0  ||
																												strcmp(nomTable,"inet") == 0  ||
																												 strcmp(nomTable,"int") == 0  ||
																													strcmp(nomTable,"text") == 0  ||
 																													strcmp(nomTable,"timestamp") == 0 	)			return 1;

		else
					return -1;
}

/*=======================*
 *       RI KEYSPACE     *
 *=======================*/

 void creer_keyspaceRI(char* nom_keyspace){

	keyspaceRI = (keyspace*) malloc(sizeof (keyspace) );
		//NOM DE LA TABLE
		strcpy(keyspaceRI->Nom_keyspace,nom_keyspace);

		keyspaceRI->proprietes = NULL;

}


 /*==================================*
  *  INTERPRETER CREATE KEYSPACE     *
  *==================================*/
 void ajout_Keyspace(Keyspace *debut,char *Nom_keyspace,Properties props)
 {
    	Keyspace p=(Keyspace)malloc(sizeof(keyspace));
		 	strcpy(p->Nom_keyspace,Nom_keyspace);
		 	p->proprietes=props;
		 	p->suiv=NULL;

      insert_Keyspace(debut,p);

			if( nbrErrSm == 0 ) creer_keyspace_dbFolder(Nom_keyspace);

 }

 /*==============================================================================================*
 *  CREATION DES DOSSIERS POUR LES KEYSPACES QUI VONT CONTENIR DES TABLES DE LA BASE DE DONNEES  *
 *===============================================================================================*/
 void creer_keyspace_dbFolder(char * Nom_keyspace){

 	char path[100];

 	snprintf(path , sizeof(path) , "%s%s" ,CQL_PATH , Nom_keyspace);

 	if( _mkdir(path) == 0 ) printf("\nCQL> Keyspace %s est cree",Nom_keyspace);
	else printf("\n - Problem creating directory \n" );

 }

 /*=================================*
 *		Fonction rechercher keyspace	*
 *==============================++==*/

 int recherche_Nom_Keyspace( Keyspace debut ,char *nomkeyspace){

	Keyspace p;
 	p=debut;
 	while(p!=NULL && strcmp(p->Nom_keyspace,nomkeyspace)!=0){
 		p=p->suiv;
 }
 if(p!=NULL) return 1; else return -1;
 }


 /*==================================*
  *  	INTERPRETEUR ALTER KEYSPACE    *
  *==================================*/

void modifier_keyspace(Keyspace keyspaceRI){

printf("%s\n",keyspaceRI->Nom_keyspace );
	Keyspace keyspace = get_keyspace( listeKeyspace , keyspaceRI->Nom_keyspace);

		if( keyspace != NULL ) keyspace->proprietes = keyspaceRI->proprietes;

			sauvegarderListeKeyspaces();

}

/*==========================*
 *  	RECUPERER KEYSPACE    *
 *==========================*/

Keyspace get_keyspace( Keyspace debut , char * nom_keyspace){

	Keyspace p;
	p=debut;

	while(p!=NULL && strcmp(p->Nom_keyspace,nom_keyspace)!=0){
		p=p->suiv;
	}

	return p;


}

 /*=======================*
  *  FONCTIONS  INSERTION *
  *=======================*/

 void insert_Keyspace(Keyspace *debut,Keyspace kspace)
 {
 	Keyspace prec,succ;
 		prec=*debut;
		if(prec == NULL){
				*debut = kspace;
				kspace->suiv = NULL;
		}else{
 			succ=prec->suiv;
 			while(succ!=NULL)
 			{
 				prec=succ;
 				succ=prec->suiv;
 			}
 			prec->suiv=kspace;
 			kspace->suiv=succ;
 		}

		if( nbrErrSm == 0 ) creer_keyspace_dbFolder(kspace->Nom_keyspace);

}


/*================================*
*		Fonction rechercher nom table *
*=================================*/

int recherche_Nom_table( Table debut ,char *nomtable ,char *nomkeyspace){

	Table p;
	p=debut;
	int k = -1;
	while( p!=NULL  ){

		if( strcmp(p->Nom_keyspace,nomkeyspace) == 0 && strcmp(p->Nom_table,nomtable) == 0  )  k = 1;

		p=p->suiv;
}

return k;

}


/*=============================*
*Fonction rechercher nom table *
*=============================*/
Table get_table( Table debut ,char *nomtable ,char *nomkeyspace){

	Table p,q;
	p=debut;
	int k = -1;
	while( p!=NULL  ){

		if( strcmp(p->Nom_keyspace,nomkeyspace) == 0 && strcmp(p->Nom_table,nomtable) == 0  )
		{
			 k = 1;
			 q = p;
		}

		p=p->suiv;
}

return q;

}


/*=========================*
*  INTERPRETEUR DROP TABLE *
*==========================*/
void supprimer_table(Table * debut , Table tableRI){


	Table p,pred;

	if( (*debut) != NULL && strcmp((*debut)->Nom_table,tableRI->Nom_table) == 0 && strcmp((*debut)->Nom_keyspace,tableRI->Nom_keyspace) == 0 )
	{
				p = *debut;
				(*debut) = (*debut)->suiv;
				free(p);
	}
	else{

		pred = *debut;
		p = pred->suiv;
		while( p!=NULL && ( strcmp(p->Nom_table,tableRI->Nom_table) != 0 || strcmp(p->Nom_keyspace,tableRI->Nom_keyspace) != 0 ) )
		{
			pred = p;
			p = pred->suiv;
		}
		if( p != NULL ){
			pred->suiv = p->suiv;
			free(p);
		}

	}

	sauvegarderListeTable();

}

/*===================================================================*
*                          INTERPRETEUR INSERT                         *
 *===================================================================*/
 /*=====================================================*
 *  INSERTION DE LA RI INSERT DANS LA LISTE DES TABLES  *
 *======================================================*/
void inserer_ligne_enqueue(LigneTable * debut, LigneTable val)
{
	  LigneTable prec,succ;
		prec = * debut;
    if( prec == NULL ){ //SI LA LISTE EST VIDE
      *debut = val;
      val->suiv = NULL;
    }
    else{
		        succ = prec->suiv;
		        while(succ!=NULL)
		        {
			           prec = succ;
			           succ = prec->suiv;
		        }
		        prec->suiv=val;
		        val->suiv=succ;
    }
}

void inserer_ligne_table(char * nom_table,  char * nom_keyspace, ValeurMaps debut){

  //NOEUD LIGNE A INSERER
  LigneTable ligne = (LigneTable) malloc(sizeof(ligneTable));
  ligne->valeurMaps = debut;
  ligne->suiv=NULL;
	//NOM DE LA TABLE+.json
	char tabname[30];
	snprintf(tabname,sizeof(tabname),"%s.json",nom_table);
  //RECHERCHE DE LA TABLE CONCERNEE
  int i=0;
  while( i < nbrValTable && ( strcmp(listValTable[i]->nom_table,tabname) != 0 || strcmp(listValTable[i]->nom_keyspace,nom_keyspace) != 0 ) ) i++;

  if( i < nbrValTable ) inserer_ligne_enqueue(&(listValTable[i]->lignes),ligne);

}

/*================================*
*  INTERPRETEUR INSERT INTO TABLE *
*=================================*/
int inserer_colonne_value(ValeurMaps *debut, char * valeur){

		int err = 1;
		ValeurMaps p;
		p = *debut;

		while( p != NULL && p->typeDroite != 0) p = p-> suiv;

		if( p != NULL ){

			p->typeDroite = 1;
			strcpy(p->termDroite,valeur);

		}
		else err = -1;

		return err;

}

/*===============================================*
*                LECTURE DES LIGNES DB           *
*================================================*/
/*================================*
*  CHARGEMENT DEPUIS JSON FILES   *
*=================================*/
static void process_value(json_value* value, int depth, LigneTable * lignes);

static void print_depth_shift(int depth)
{
        int j;
        for (j=0; j < depth; j++) {
                printf(" ");
        }
}
//CHARGEMENT DES COLONNES POUR CHAQUE LIGNE
static LigneTable process_object(json_value* value, int depth)
{
				LigneTable oneLigne = (LigneTable) malloc(sizeof (ligneTable) );
				oneLigne->suiv = NULL;
				oneLigne->valeurMaps = NULL;

        int length, x;
        if (value == NULL) {
                return NULL;
        }
        length = value->u.object.length;
				//chaque colonne termGauche : termDroite
        for (x = 0; x < length; x++) {

						ajout_valeurMaps(&oneLigne->valeurMaps, value->u.object.values[x].name, 1, value->u.object.values[x].value->u.string.ptr, 1);

        }
				return oneLigne;
}
//CHARGEMENT DES LIGNES POUR CHAQUE TABLE
static void process_array(json_value* value, int depth, LigneTable * lignes)
{
				//NOEUD LIGNE
				LigneTable plignes;

        int length, x;
        if (value == NULL) {
                return;
        }
        length = value->u.array.length;
				//POUR CHAQUE LIGNE TROUVEE
        for (x = 0; x < length; x++) { //chaque ligne {}
								//ON RECUPERE UNE LIGNE
                plignes = process_object(value->u.array.values[x], depth);
								//ON L'INSERE DANS LA LISTE DES LIGNES DE LA TABLE
								inserer_ligne_enqueue(lignes, plignes);

        }
}

static void process_value(json_value* value, int depth, LigneTable * lignes)
{
        int j;
        if (value == NULL) {
                return;
        }
        if (value->type != json_object) {
                print_depth_shift(depth);
        }
        switch (value->type) {
                case json_none:
                        printf("none\n");
                        break;
                /*case json_object:
                        process_object(value, depth+1);
                        break;*/
                case json_array: //********************************//
                        process_array(value, depth+1, lignes);
                        break;
                case json_integer:
                        printf("int: %10" PRId64 "\n", value->u.integer);
                        break;
                case json_double:
                        printf("double: %f\n", value->u.dbl);
                        break;
                case json_string:
                        printf("string: %s\n", value->u.string.ptr);
                        break;
                case json_boolean:
                        printf("bool: %d\n", value->u.boolean);
                        break;
        }
}

/*================================================================================*
*  PARCOURS DES DOSSIERS ET CHARGEMENT DE CONTENUE DES TABLES DEPUIS JSON FILES   *
*=================================================================================*/
LigneTable get_ligne_table(char * nom_table, char * nom_keyspace){


	LigneTable lignes = NULL;

	FILE *fp;
	int file_size;
	char* file_contents;
	json_value* value;
	char filename[200];//char* filename;
	struct stat filestatus;

	snprintf(filename, sizeof(filename), "%s%s\\%s" , CQL_PATH, nom_keyspace, nom_table);

	stat(filename, &filestatus);
	file_size = filestatus.st_size;
	file_contents = (char*)malloc(filestatus.st_size);
	fp = fopen(filename, "rt");
	fread(file_contents, file_size, 1, fp);
	fclose(fp);

	value = json_parse(file_contents,file_size);
	process_value(value, 0, &lignes);

	json_value_free(value);
	free(file_contents);

	return lignes;

}

valLigneTable * creer_val_ligne_table(char * nom_table, char * nom_keyspace){

		valLigneTable * e = (valLigneTable*) malloc(sizeof (valLigneTable) );
		strcpy(e->nom_table , nom_table);//printf(" %s : %s ",nom_table,nom_keyspace);
		strcpy(e->nom_keyspace , nom_keyspace);
		//liste des valeurs
		e->lignes = get_ligne_table(nom_table, nom_keyspace);



  return e;
}

void lire_DB_file()
{
	//ON POINTE SUR DB, ON BOUCLE SUR LES KEYSPACES
	char pathKeyspaces[100];
	snprintf(pathKeyspaces , sizeof(pathKeyspaces), "%s\\..\\DB" , CQL_PATH);
	DIR *dir = opendir(pathKeyspaces);
	struct dirent* entry;
	//ON RECUPERE LE NOM DE CHAQUE KEYSPACE
	while( (entry = readdir(dir)) != NULL)
	{
			//SAUF LE DOSSIER COURANT ET LE PRECEDENT
			if(strcmp(entry->d_name , "..") != 0 && strcmp(entry->d_name , ".") != 0)
			{
					//ON EST DANS UN KEYSPACE, ON PARCOURS TOUS SES TABLES
					char pathTables[200];
					snprintf(pathTables , sizeof(pathTables), "%s%s" , CQL_PATH, entry->d_name);
					DIR *rep = opendir(pathTables);
					struct dirent* fichierLu;
					while( (fichierLu = readdir(rep)) != NULL){

							if(strcmp(fichierLu->d_name , "..") != 0 && strcmp(fichierLu->d_name , ".") != 0)
							{
								//ON CREE UNE TABLE : NOM DE LA TABLE, NOM DE KEYSPACE ET LA LISTE DES LIGNES DE LA TABLE
								listValTable[nbrValTable] = creer_val_ligne_table(fichierLu->d_name, entry->d_name);
							  nbrValTable++;
							}

					}

			}
	}

}

/*===============================================*
*                ECRITURE DES LIGNES DB          *
*================================================*/
void ecrire_DB_file(){

	char path[200];
	int i=0;
	for(i=0;i<nbrValTable;i++){

			snprintf(path, sizeof(path), "%s%s\\%s" , CQL_PATH, listValTable[i]->nom_keyspace, listValTable[i]->nom_table);
			//printf("%s",path);

			int table = _open(path, _O_WRONLY );

			sauvegarder_lignes_table(table, listValTable[i]->lignes);

			close(table);

	}


}

void sauvegarder_lignes_table(int table, LigneTable lignes){

	//[
	write(table,"[",sizeof(char));

	LigneTable pligne = lignes;
	while(pligne != NULL){

				//{
				write(table,"{",sizeof(char));

				ValeurMaps p = pligne->valeurMaps;
				while(p!=NULL){

					//valgauche : valdroite
					char term[30];
					snprintf(term, sizeof(term), "\"%s\"" , p->termGauche);
					write(table,term,strlen(p->termGauche)+2);

					write(table,":",sizeof(char));

					snprintf(term, sizeof(term), "\"%s\"" , p->termDroite);
					write(table,term,strlen(p->termDroite)+2);

					p=p->suiv;

					if( p != NULL ) //,
						write(table,",",sizeof(char));
				}
				pligne = pligne->suiv;

				//}
				write(table,"}",sizeof(char));
				if( pligne != NULL ) //,
					write(table,",",sizeof(char));
	}

	//]
	write(table,"]",sizeof(char));

}

	/*======================================================================*
 *                          INTERPRETEUR SELECT                   				  *
 	 *======================================================================*/
/*===========================================*
*  INTERPRETEUR SELECT * FROM keyspace.table *
*============================================*/
void get_tous_lignes_table(char * nomTable, char * nomKeyspace){

	int i=0;
	char tabname[30];
	snprintf(tabname,sizeof(tabname),"%s.json",nomTable);
	//PARCOURIR LA LISTE DES TABLES EN CHERCHANT LA TABLE CONCERNEE
  while( i < nbrValTable && ( strcmp(listValTable[i]->nom_table,tabname) != 0 || strcmp(listValTable[i]->nom_keyspace,nomKeyspace) != 0 ) ) i++;

  if( i < nbrValTable ) afficher_lignes_table(listValTable[i]->lignes);


}

/*=======================================================*
*  AFFICHAGE DE RESULTAT DE SELECT * FROM keyspace.table *
*========================================================*/
void afficher_lignes_table( LigneTable lignes){

	LigneTable pp = lignes;
	if( pp == NULL ){
		//AU CAS OU LA TABLE NE CONTIENT AUCUNE LIGNES
		printf("\nCQL> aucune ligne \n");

	}
	else{

		ValeurMaps col = pp->valeurMaps;

		printf("\n*===================================================================*\n");

		while( col != NULL ){

			printf("\t%s\t|",col->termGauche);
			col = col->suiv;

		}
		printf("\n*===================================================================*\n");

		while( pp != NULL ){

					ValeurMaps p = pp->valeurMaps;

					while( p != NULL ){
						printf("\t%s\t|",p->termDroite);
						p=p->suiv;
					}
					pp = pp->suiv;
					printf("\n*-----------------------------------------------------------------*\n");
		}

	}

}

/*===========================================*
* AFFICHAGE DE CONTENUE DE TOUTES LES TABLES *
*============================================*/
void afficher_toutes_tables(){

	int k=0;
	for(k=0;k<nbrValTable;k++){

			printf("\n - %s : %s \n",listValTable[k]->nom_table,listValTable[k]->nom_keyspace);

			LigneTable pp = listValTable[k]->lignes;
			while(pp != NULL){

						ValeurMaps p = pp->valeurMaps;
						while(p!=NULL){
							printf("* %s : %s \n",p->termGauche,p->termDroite);
							p=p->suiv;
						}
						pp = pp->suiv;
			}
	}

}


/*=**==**********************************==**=+*
 *  			LES FONCTIONS D'ENREGISTREMENT       *
 *=**==**********************************==**=+*/

/*
 * INDICATEUR : UNE VARIABLE QUI VA NOUS PERMETTRE DE SAVOIR SI UNE VARIABLE EXITE OU PAS
 *							-1 DONC LA VARIABLE = NULL
 *							 1 DONC LA VARIABLE = L'ELEMENT SUIVANT
 *
 * SEPARATEUR : AFIN DE SEPARER LES ELEMENTS
 *								+ CONTINUE A CHARGER
 *								. ON A PLUS D'ELEMENT
 *
 */

 /*===========================================+*
  *     SAUVEGARDER LA LISTE DES TABLES      *
  *===========================================+*/

void sauvegarderListeTable(){

Table p = NULL;       //NOEUD DE PARCOURS
char fin = '.',separateur = '+';

//FLUX DE FICHIER
FILE* fileTables = fopen("listeTables.dta","wb");
//FLUX EST VIDE
if( fileTables == NULL )
{
    printf("\n Impossible d'ouvrir le fichier. \n ");
    exit(0);
}
//DEBUT DE LA LISTE
p = listeTable;
//PARCOURS DE LA LISTE
while( p != NULL ){
  //SAUVEGARDE DES CHAMPS
  fwrite(p->Nom_table,30*sizeof(char),1,fileTables);
  fwrite(p->Nom_keyspace,30*sizeof(char),1,fileTables);
  sauvColonnes(fileTables,p->colonneDefs);
  sauvProprietes(fileTables,p->proprietes);

  //LES SEPARATEURS
  if( p->suiv == NULL ) fwrite(&fin,sizeof(char),1,fileTables);
  else
      fwrite(&separateur,sizeof(char),1,fileTables);

  p = p->suiv;

}

//FERMER LE FICHIER
fclose(fileTables);

}

/*===========================================+*
 *     SAUVEGARDER LA LISTE DES COLONNES      *
 *===========================================+*/

void sauvColonnes(FILE* fileTables , ColonneDefinitions listeCln){

ColonneDefinitions c = NULL;       //NOEUD DE PARCOURS
char fin = '.',separateur = '+';

//DEBUT DE LA LISTE
c = listeCln;
//PARCOURS DE LA LISTE
while( c != NULL ){
 //SAUVEGARDE DES CHAMPS
 fwrite(c->nom_colonne,30*sizeof(char),1,fileTables);
 fwrite(&c->type_colonne,sizeof(int),1,fileTables);
 fwrite(&c->valeurStatic,sizeof(int),1,fileTables);
 fwrite(&c->valeurPrimary,sizeof(int),1,fileTables);

 //LES SEPARATEURS
 if( c->suiv == NULL ) fwrite(&fin,sizeof(char),1,fileTables);
 else
     fwrite(&separateur,sizeof(char),1,fileTables);

 c = c->suiv;

}


}



/*===========================================+*
 *     SAUVEGARDER LA LISTE DES PROPRIETY     *
 *===========================================+*/

void sauvProprietes(FILE* fileTables , Properties listeProp){

Properties p = NULL;                  //NOEUD DE PARCOURS
char fin = '.',separateur = '+';
int ind = 1, indnull = 0;
//ON MET 0 DANS LE CAS OU LA LISTE EST VIDE
if( listeProp == NULL ){

  fwrite(&indnull,sizeof(int),1,fileTables);

}else{
//SINON ON MET 1 AVANT DE COMMENCER A SAUVEGARDER
fwrite(&ind,sizeof(int),1,fileTables);
//DEBUT DE LA LISTE
p = listeProp;
//PARCOURS DE LA LISTE
while( p != NULL ){
 //SAUVEGARDE DES CHAMPS
 fwrite(p->Nom_propriete,30*sizeof(char),1,fileTables);
 sauvValPropriete(fileTables,p->valeurPropriete);

 //LES SEPARATEURS
 if( p->suiv == NULL ) fwrite(&fin,sizeof(char),1,fileTables);
 else
     fwrite(&separateur,sizeof(char),1,fileTables);

 p = p->suiv;

}

}

}


/*=========================================++++++++==+*
 *     SAUVEGARDER LA LISTE DES VALEURS PROPRIETY     *
 *==========================================++++++++=+*/

void sauvValPropriete(FILE* fileTables , ValeurPropriete vp){

int ind = 1, indnull = -1;

//ON SAUVEGARDE -1 SI LA VALEUR MAPS EST NULL
if( vp.valeurMaps == NULL ) fwrite(&indnull,sizeof(int),1,fileTables);
else{
      //SINON ON MET 1 ET LA VALEUR DE MAPS
      fwrite(&ind,sizeof(int),1,fileTables);
      sauvValeurMaps(fileTables,vp.valeurMaps);
    }
//SAUVEGARDE DE BOOLEAN
fwrite(&vp.ValeurBoolean,sizeof(int),1,fileTables);
//-1 DANS LE CAS OU STRING EST NULL
if( /*vp.valeurString == NULL*/ vp.valeurString[0] == '\0') fwrite(&indnull,sizeof(int),1,fileTables);
else{
      //SINON ON MET 1 EN PLUS DE SA VALEUR
      fwrite(&ind,sizeof(int),1,fileTables);
      fwrite(vp.valeurString,30*sizeof(char),1,fileTables);
    }
//ON SAUVEGARDE FLOAT ET INT
fwrite(&vp.valeurFloat,sizeof(float),1,fileTables);
fwrite(&vp.ValeurInt,sizeof(int),1,fileTables);


}



/*==============================================+*
 *     SAUVEGARDER LA LISTE DES VALEURS MAPS     *
 *==============================================+*/

void sauvValeurMaps(FILE* fileTables , ValeurMaps listeVal){

ValeurMaps v = NULL;	                //NOEUD DE PARCOURS
char fin = '.',separateur = '+';

//DEBUT DE LA LISTE
v = listeVal;
//PARCOURS DE LA LISTE
while( v != NULL ){
 //SAUVEGARDE DES CHAMPS
 fwrite(v->termGauche,30*sizeof(char),1,fileTables);
 fwrite(&v->typeGauche,sizeof(int),1,fileTables);
 fwrite(v->termDroite,30*sizeof(char),1,fileTables);
 fwrite(&v->typeDroite,sizeof(int),1,fileTables);

 //LES SEPARATEURS
 if( v->suiv == NULL ) fwrite(&fin,sizeof(char),1,fileTables);
 else
     fwrite(&separateur,sizeof(char),1,fileTables);

 v = v->suiv;

}


}


/*============================================+*
 *     SAUVEGARDER LA LISTE DES KEYSPACES      *
 *============================================+*/

void sauvegarderListeKeyspaces(){

Keyspace p = NULL;       //NOEUD DE PARCOURS
char fin = '.',separateur = '+';

//FLUX DE FICHIER
FILE* fileKeyspace = fopen("listeKeyspaces.dta","wb");
//FLUX EST VIDE
if( fileKeyspace == NULL )
{
	 printf("\n Impossible d'ouvrir le fichier. \n ");
	 exit(0);
}
//DEBUT DE LA LISTE
p = listeKeyspace;
//PARCOURS DE LA LISTE
while( p != NULL ){
 //SAUVEGARDE DES CHAMPS
 fwrite(p->Nom_keyspace,30*sizeof(char),1,fileKeyspace);
 sauvProprietes(fileKeyspace,p->proprietes);

 //LES SEPARATEURS
 if( p->suiv == NULL ) fwrite(&fin,sizeof(char),1,fileKeyspace);
 else
		 fwrite(&separateur,sizeof(char),1,fileKeyspace);

 p = p->suiv;

}

//FERMER LE FICHIER
fclose(fileKeyspace);

}

/*=**==**********************************==**=+*
 *  			LES FONCTIONS DE CHARGEMENT          *
 *=**==**********************************==**=+*/

/*
 * INDICATEUR : UNE VARIABLE QUI VA NOUS PERMETTRE DE SAVOIR SI UNE VARIABLE EXITE OU PAS
 *							-1 DONC LA VARIABLE = NULL
 *							 1 DONC LA VARIABLE = L'ELEMENT SUIVANT
 *
 * SEPARATEUR : AFIN DE SEPARER LES ELEMENTS
 *								+ CONTINUE A CHARGER
 *								. ON A PLUS D'ELEMENT
 *
 */

/*===========================================+*
 *     CHARGEMENT DE LA LISTE DES TABLES      *
 *===========================================+*/

void chargerListeTable(){

	Table p = NULL;						//NOEUD TABLE COURANT
	char separateur[1];					//LA FIN DU FICHIER
	char point_sep[] = ".";
	listeTable = NULL;							//LA LISTE DES TABLES FINALE

	//FLUX DE FICHIER
	FILE* fileTables = fopen("listeTables.dta","rb");
	//FLUX EST VIDE
	if( fileTables == NULL )
	{
			printf("\n Impossible d'ouvrir le fichier. \n ");
			exit(0);
	}

do{
	//L'ALLOCATION D'UN NOEUD TABLE
	p = (table*) malloc(1*sizeof(table));
	//LIRE LE NOM D'UNE TABLE
	fread(p->Nom_table,30*sizeof(char),1,fileTables);
	//LIRE LE NOM D'UNE KEYSPACE
	fread(p->Nom_keyspace,30*sizeof(char),1,fileTables);
	//RECUPERER LA LISTE DES COLONNES
	p->colonneDefs = chargerColonnes(fileTables);
	//RECUPERER LA LISTE DES PROPRIETEES
	p->proprietes = chargerProprietes(fileTables);
	//SUIVANT (NULL AU DEBUT)
	p->suiv = listeTable;
	//MET LE AU DEBUT : LA LISTE SERA INVERSEE
	listeTable = p;
	//LIRE LE SEPARATEUR : ON MET UN SEPARATEUR + ENTRE LES TABLES ET A LA FIN .
	size_t len = fread(separateur,sizeof(char),1,fileTables);
	separateur[len] = '\0';

}while( strcmp(separateur,point_sep) != 0 );
	//ON REPETE TANT QU'ON EST PAS ARRIVER A LA FIN

//FERMER LE FICHIER
fclose(fileTables);

}


/*===========================================+*
 *  CHARGEMENT DES COLONNES D'UNE TABLE       *
 *===========================================+*/

ColonneDefinitions chargerColonnes(FILE* fileTables){

	ColonneDefinitions c = NULL;						//NOEUD COLONNE COURANT
	char separateur[1];
	char point_sep[] = ".";											//LA FIN DE LA LISTE DES COLONNES
	ColonneDefinitions listeCln = NULL;							//LA LISTE DES COLONNES FINALE

do{
	//L'ALLOCATION D'UN NOEUD COLONNE
	c = (colonneDefinitions*) malloc(1*sizeof(colonneDefinitions));
	//LIRE LE NOM D'UNE COLONNE
	fread(c->nom_colonne,30*sizeof(char),1,fileTables);
	//LIRE LE TYPE
	fread(&c->type_colonne,sizeof(int),1,fileTables);
	//LIRE LA VALEUR STATIC
	fread(&c->valeurStatic,sizeof(int),1,fileTables);
	//LIRE LA VALEUR PRIMARY KEY
	fread(&c->valeurPrimary,sizeof(int),1,fileTables);
	//SUIVANT (NULL AU DEBUT)
	c->suiv = listeCln;
	//MET LE AU DEBUT : LA LISTE SERA INVERSEE
	listeCln = c;
	//LIRE LE SEPARATEUR : ON MET UN SEPARATEUR + ENTRE LES COLONNES ET A LA FIN .
	size_t len = fread(separateur,sizeof(char),1,fileTables);
	separateur[len] = '\0';

}while( strcmp(separateur,point_sep) != 0 );
	//ON REPETE TANT QU'ON EST PAS ARRIVER A LA FIN

return listeCln;

}


/*===========================================+*
 *  CHARGEMENT DES PROPRIETES D'UNE TABLE     *
 *===========================================+*/

Properties chargerProprietes(FILE* fileTables){

	Properties p = NULL;						//NOEUD COLONNE COURANT
	char separateur[1];
	char point_sep[] = ".";												//LA FIN DE LA LISTE DES COLONNES
	Properties listeProp = NULL;							//LA LISTE DES COLONNES FINALE
  int x;                                  //INDIQUE SI LA LISTE SERA VIDE OU PAS

fread(&x,sizeof(int),1,fileTables);
if( x != 0 ){

do{
	//L'ALLOCATION D'UN NOEUD PROPRIETY
	p = (property*) malloc(1*sizeof(property));
	//LIRE LE NOM D'UNE PROPRIETY
	fread(p->Nom_propriete,30*sizeof(char),1,fileTables);
	//RECUPERER LA valeurPropriete
	p->valeurPropriete = chargerValPropriete(fileTables);
	//SUIVANT (NULL AU DEBUT)
	p->suiv = listeProp;
	//MET LE AU DEBUT : LA LISTE SERA INVERSEE
	listeProp = p;
	//LIRE LE SEPARATEUR : ON MET UN SEPARATEUR + ENTRE LES COLONNES ET A LA FIN .
	size_t len = fread(separateur,sizeof(char),1,fileTables);
	separateur[len] = '\0';

}while( strcmp(separateur,point_sep) != 0 );
	//ON REPETE TANT QU'ON EST PAS ARRIVER A LA FIN

}//FIN IF

return listeProp;

}


/*===========================================+*
 *  CHARGEMENT DES VALEURS DES PROPRIETES     *
 *===========================================+*/

ValeurPropriete chargerValPropriete(FILE* fileTables){

	ValeurPropriete vp;						//NOEUD VALEUR PROPRIETE
	int ind;											//Indicateur

	//LIRE L'INDICATEUR
	fread(&ind,sizeof(int),1,fileTables);
	//MAPS EXISTE OU PAS
	if(ind == -1) vp.valeurMaps = NULL;
	else{
					//RECUPERER LA valeurMaps
					vp.valeurMaps = chargerValeurMaps(fileTables);
			}

	//LIRE LA VALEUR BOOLEAN
	fread(&vp.ValeurBoolean,sizeof(int),1,fileTables);
	//STRING EXISTE OU PAS
	fread(&ind,sizeof(int),1,fileTables);
	//valeurString EXISTE OU PAS
	if(ind == -1) vp.valeurString[0] = '\0';
	else{
					//LIRE LE STRING
					fread(vp.valeurString,30*sizeof(char),1,fileTables);
					//vp.valeurString[len] = '\0';
			}
	//LIRE FLOAT
	fread(&vp.valeurFloat,sizeof(float),1,fileTables);
	//LIRE INT
	fread(&vp.ValeurInt,sizeof(int),1,fileTables);


return vp;

}


/*===========================================+*
 *     CHARGEMENT DES VALEURS DE MAPS         *
 *===========================================+*/

ValeurMaps chargerValeurMaps(FILE* fileTables){

	ValeurMaps v = NULL;										//NOEUD VALEUR MAPS
	char separateur[1];
	char point_sep[] = ".";												//LA FIN DE LA LISTE DES VALEURS
	ValeurMaps listeVal = NULL;							//LA LISTE DES VALEURS FINALE

do{
	//L'ALLOCATION D'UN NOEUD VALEUR MAPS
	v = (valeurMaps*) malloc(1*sizeof(valeurMaps));
	//LIRE LE TERM GAUCHE
	fread(v->termGauche,30*sizeof(char),1,fileTables);
	//LIRE LE TYPE GAUCHE
	fread(&v->typeGauche,sizeof(int),1,fileTables);
	//LIRE LE TERM DROITE
	fread(v->termDroite,30*sizeof(char),1,fileTables);
	//LIRE LE TYPE DROITE
	fread(&v->typeDroite,sizeof(int),1,fileTables);
	//SUIVANT (NULL AU DEBUT)
	v->suiv = listeVal;
	//MET LE AU DEBUT : LA LISTE SERA INVERSEE
	listeVal = v;
	//LIRE LE SEPARATEUR : ON MET UN SEPARATEUR + ENTRE LES VALEURS ET A LA FIN .
	size_t len = fread(separateur,sizeof(char),1,fileTables);
	separateur[len] = '\0';

}while( strcmp(separateur,point_sep) != 0 );
	//ON REPETE TANT QU'ON EST PAS ARRIVER A LA FIN

return listeVal;

}


/*=============================================+*
 *     CHARGEMENT DE LA LISTE DES KEYSPACES     *
 *=============================================+*/

void chargerListeKeyspace(){

	Keyspace p = NULL;						//NOEUD TABLE COURANT
	char separateur[1];					//LA FIN DU FICHIER
	char point_sep[] = ".";
	listeKeyspace = NULL;							//LA LISTE DES TABLES FINALE

	//FLUX DE FICHIER
	FILE* fileKeyspace = fopen("listeKeyspaces.dta","rb");
	//FLUX EST VIDE
	if( fileKeyspace == NULL )
	{
			printf("\n Impossible d'ouvrir le fichier. \n ");
			exit(0);
	}

do{
	//L'ALLOCATION D'UN NOEUD TABLE
	p = (keyspace*) malloc(1*sizeof(keyspace));
	//LIRE LE NOM D'UNE TABLE
	fread(p->Nom_keyspace,30*sizeof(char),1,fileKeyspace);
	//RECUPERER LA LISTE DES PROPRIETEES
	p->proprietes = chargerProprietes(fileKeyspace);
	//SUIVANT (NULL AU DEBUT)
	p->suiv = listeKeyspace;
	//MET LE AU DEBUT : LA LISTE SERA INVERSEE
	listeKeyspace = p;
	//LIRE LE SEPARATEUR : ON MET UN SEPARATEUR + ENTRE LES TABLES ET A LA FIN .
	size_t len = fread(separateur,sizeof(char),1,fileKeyspace);
	separateur[len] = '\0';

}while( strcmp(separateur,point_sep) != 0 );
	//ON REPETE TANT QU'ON EST PAS ARRIVER A LA FIN

//FERMER LE FICHIER
fclose(fileKeyspace);

}
