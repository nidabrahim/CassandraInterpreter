#include "Cassandra.h"
#include "json.h"

#define CQL_PATH "\\DB\\"

/*===============================*
  *   LES ERREURS SEMANTIQUES    *
 *===============================*/

//TYPES ERREURS SEMANTIQUES
typedef enum { REPLICATIONERROR_IDF , REPLICATIONERROR_CONST , DURABLE_WRITESERROR_NOTBOOL, INVALIDKEYSPACEPROPERTY , INVALIDKEYSPACETERM ,
                INVALIDKEYSPACEFIRSTTERM , INVALIDKEYSPACESTRATEGY , REPLICATIONFACTOR_NEEDED , INVALIDSIMPLESTRATEGY , INVALID_DATACENTER,
                INVALID_DATACENTER_FACTOR, INVALID_REPLICATION_FACTORVALUE , COMMENTVALUE_NOTCOMPATIBLE , READREPAIRVALUE_NOTCOMPATIBLE ,
                DCLOCALREADVALUE_NOTCOMPATIBLE , BLOOMFILTERVALUE_NOTCOMPATIBLE , GCGRACEVALUE_NOTCOMPATIBLE , TIMETOLIVEVALUE_NOTCOMPATIBLE , COMPRESSIONVALUE_NOTCOMPATIBLE ,
                CACHINGVALUE_NOTCOMPATIBLE , COMPACTIONVALUE_NOTCOMPATIBLE , INVALIDTABLEOPTIONS , PLUSPRIMARYKEY , STATICWITHPRIMARYKEY ,
                UNKNOWNCOLUMN , TABLENAMEFOUND , TABLENAMEINVALID , KEYSPACENAMENOTFOUND , TABLENOTFOUND , COLONNENOTFOUND  , KEYSPACENAMEFOUND , COLUMNNAMENOTFOUND } OptionsErrorType;

//STRUCTURE D'ERREURS SEMANTIQUES
typedef struct {
    int linenumdecl;
    OptionsErrorType errort;
} optionsError;

//NOMBRE D'ERREUR
extern int nbrErrSm;

//TABLE DES ERREURS
optionsError * tableErr[100];

//CREER SM ERREUR
optionsError * creer_optionsError(OptionsErrorType et, int line);
//INSERER SM ERREUR DANS LA TABLE DES ERREURS
void inserer_optionsError(OptionsErrorType et, int line);
//AFFICHAGE D'UNE ERREUR
void afficher_optionsError(OptionsErrorType et, int line);
//AFFICHAGE DE LA LISTE D'ERREURS
void afficher_listeOptionsError();


/*==================================================*
  *   STOCKAGE DE KEYSPACE POUR LES VERIFICATION    *
 *==================================================*/

//PROPERTY_NAME soit replication ou durable_writes
typedef enum { replication , durable_writes } type_propname;

//LISTE DES TERMES DE MAP
typedef struct listTerm{
  char * termLeft;
  int typeLeft;
  char * termRight;
  int typeRight;
  struct listTerm * next;
} replicNode;
replicNode * mapValue;

typedef struct{
  type_propname propName;           //soit replication ou durable_writes
  union{
    //si propName = replication
    replicNode * mapVal;
    //si propName = durable_writes
    boolean boolVal;
  } node;
} propertyNode;

//Liste des property : properties
typedef struct List_propertyNode{
  propertyNode prop;                  //PROPERTY
  struct List_propertyNode * next;           //LES SUIVANTS DE PROPERTY
} listPropertiesType;

//STRUCTURE DE KEYSPACE
typedef struct{
  char * keyspaceName;                //NOM DE KEYSPACE
  listPropertiesType * listProp;      //LISTE DES PROPERTY
} keyspaceNode;

keyspaceNode * Nkeyspace;

/*==========================================*
  *   FONCTIONS ASSOCIE A KEYSPACE NODE     *
 *==========================================*/

//CREER KEYSPACE NODE
void creer_keyspaceNode(char* nomKeyspace, listPropertiesType * properties);
//INSERER TERME DANS MAP
void inserer_mapTerm(char * leftTerm, int typeLeft, char * rightTerm, int typeRight);
//CREER UN NOEUD POUR LA PROPRIETY REPLICATION
propertyNode * creer_propertyNode_replication(replicNode* mapValue);
//CREER UN NOEUD POUR LA PROPRIETY DURABLE WRITES
propertyNode * creer_propertyNode_durableWrites(boolean boolValue);
//INSERER UNE PROPRIETY DANS LA LISTE
void inserer_propertyNode(propertyNode proprietyValue);
//INSERER LA PROPRIETY Replication DANS LA LISTE
void inserer_propertyNode_replication(replicNode* mapValue);
//INSERER LA PROPRIETY Durable_writes DANS LA LISTE
void inserer_propertyNode_durableWrites(boolean boolValue);
//LES ERREURS DE MAP
void map_error();
//AFFICHAGE KEYSPACE VALUES
void afficher_keyspace_values();
//VERIFIER SI LES OPTIONS DU TABLE SONT VALIDE
void isTableOptionsValid(int yylineno);


/*===================================================*
  *   STOCKAGE DES COLONNES POUR LES VERIFICATION    *
 *===================================================*/

//TABLE
typedef struct{
  char * nomVar;
  //typeClmTable typeClm;
  boolean staticc;
  boolean primaryKey;
  int line;
} NColumn;

//NOMBRE COLONNES DECLAREES
extern int nbrColDecl;

NColumn * columnTable[20];

/*=========================================*
  *   FONCTIONS ASSOCIE A COLONNE NODE     *
 *=========================================*/

//CREER CULOMN
NColumn * creer_columnNode(char* nomVar/*, typeClmTable typeClm*/, boolean staticc, boolean primaryKey, int line);
//INSERER COLUNM
void inserer_columnNode(char* nomVar/*, typeClmTable typeClm*/, boolean staticc, boolean primaryKey, int line);
//AFFICHAGE D'UNE COLONNE
void afficher_columnNode(char* nomVar/*, typeClmTable typeClm*/, boolean staticc, boolean primaryKey, int line);
//AFFICHAGE DE LA LISTE DES COLONNES DECLAREES
void afficher_columnsTable();
//VERIFIER SI LES COLONNES DE TABLE SONT VALIDE
void isTableColumnValid();
//VERIFIER SI PRIMARY KEY EST VALIDE (EXISTE ET N'EST PAS STATIC)
void isPrimaryKeyValid(char* var, int line);



/*========================================================+*
 *   REPRESENTATION INTERMEDIAIRE DE LA TABLE ET KEYSPACE  *
 *========================================================+*/
 /*==================================+*
  *       STRUCTURES  VALEUR MAPS     *
  *==================================+*/
 typedef struct listTermes{
   char termGauche[30];
   int typeGauche;
   char termDroite[30];
   int typeDroite;
   struct listTermes * suiv;
 } valeurMaps;

 typedef valeurMaps* ValeurMaps;
 ValeurMaps valrMaps;

 /*==================================+*
  *       STRUCTURES  PROPRIETES      *
  *==================================+*/

 typedef struct
 {
    ValeurMaps valeurMaps;
    int ValeurBoolean;
    char valeurString[30];
    float valeurFloat;
    int ValeurInt;
 } ValeurPropriete;

 typedef struct properties
 {
   char Nom_propriete[30];
   ValeurPropriete valeurPropriete;
   struct properties *suiv;
 }property;

 typedef property* Properties;

 /*==================================+*
  *       STRUCTURES  KEYSPACES       *
  *==================================+*/
 typedef struct keyspaces
 {
 	char Nom_keyspace[30];
 	Properties proprietes;	//liste des proprietes keyspaces
 	struct keyspaces *suiv;
 }keyspace;

 typedef keyspace* Keyspace;
 //LA LISTE DES TABLE
 Keyspace listeKeyspace;
 //LA TABLE DE LA REQUETE
 Keyspace keyspaceRI;

 /*===========================================+*
  *       STRUCTURES  LISTE COLONNE TABLE      *
  *===========================================+*/
 typedef struct listColonnes{
   char nom_colonne[30];
   int type_colonne;
   int valeurStatic;
   int valeurPrimary;
   struct listColonnes * suiv;
 } colonneDefinitions;

 typedef colonneDefinitions* ColonneDefinitions;


 /*==================================+*
  *       STRUCTURES  TABLES          *
  *==================================+*/
 typedef struct tables
 {
 	char Nom_table[30];
 	char Nom_keyspace[30];
 	ColonneDefinitions colonneDefs;	//liste des colonnes tables
 	Properties proprietes;	//liste des proprietes tables
 	struct tables *suiv;
 }table;

 typedef table* Table;
//LA LISTE DES TABLE
Table listeTable;
//LA TABLE DE LA REQUETE
Table tableRI;

 /*==============================*
  *       PROTOTYPES TABLE RI    *
  *==============================*/
//LISTE COLONNES
void ajout_colonneDef(ColonneDefinitions *debut,char *nomColonne,int typeColonne,int valeurStatic,int valeurPrimaryKey); //  &(tableRI->colonneDefs)
void insert_colonneDef(ColonneDefinitions *debut,ColonneDefinitions col);
void creer_tableRI(char* nom_table, char * nom_keyspace); //colonneDefs = NULL; proprietes = NULL;
ColonneDefinitions recherche_Nom_column(ColonneDefinitions debut , char *nom_colonne );
void supprimer_colonne(ColonneDefinitions * debut , ColonneDefinitions colonne);
//AFFICHAGE RI
void afficher_colonne(char* nomVar, int typeClm, int staticc, int primaryKey);
void afficher_colonnes_tableRI( ColonneDefinitions debut );
void afficher_tableRI();
void afficher_liste_table();
//LISTE OPTIONS
void ajout_Proprietes(Properties *debut,char *Nom_propriete,ValeurMaps valeurMaps,int ValeurBoolean,char* valeurString,float valeurFloat,int valeurInt);
void insert_Proprietes(Properties *debut,Properties props); // &(tableRI->proprietes)
void ajout_valeurMaps(ValeurMaps *debut,char *termGauche,int typeGauche,char *termDroite,int typeDroite);
void insert_termeDef(ValeurMaps *debut,ValeurMaps valTerm);

//LES MOT CLES
int nomTableInvalid(char * nomTable);

/*=================================*
 *       PROTOTYPES KEYSPACE RI    *
 *=================================*/
 void creer_keyspaceRI(char* nom_keyspace); //proprietes = NULL;
 void insert_Keyspace(Keyspace *debut,Keyspace kspace);
 void ajout_Keyspace(Keyspace *debut,char *Nom_keyspace,Properties props);
 int recherche_Nom_Keyspace( Keyspace debut ,char *nomkeyspace);
void modifier_keyspace(Keyspace keyspaceRI);
Keyspace get_keyspace( Keyspace debut , char * nom_keyspace);

/*====================================*
 *      INTERPRETEUR REQUETE TABLE    *
 *====================================*/
int recherche_Nom_table( Table debut ,char *nomtable,char *nomkeyspace);
void insert_Table(Table *debut,Table tab);
void modifier_table(Table tableRI, int typeAlter , int nligne);
Table get_table( Table debut ,char *nomtable ,char *nomkeyspace);
void supprimer_table(Table * debut , Table tableRI);


/*===================================================================*
*                          INTERPRETEUR INSERT                         *
 *===================================================================*/
/*==================================+*
 *       STRUCTURES  RI INSERT       *
 *==================================+*/
typedef struct listLigneTable{
  ValeurMaps valeurMaps;
  struct listLigneTable * suiv;
}ligneTable;

typedef ligneTable* LigneTable;

typedef struct{
  char nom_table[30];
  char nom_keyspace[30];
  LigneTable lignes;
}valLigneTable;

//NOMBRE DE TABLE
extern int nbrValTable;
//TABLEAU DES TABLES
valLigneTable * listValTable[20];


/*==============================================================*
*  CREATION DES FICHIERS POUR LES TABLES DE LA BASE DE DONNEES  *
*===============================================================*/
void creer_table_dbfile(Table tab);

/*==============================================================================================*
*  CREATION DES DOSSIERS POUR LES KEYSPACES QUI VONT CONTENIR DES TABLES DE LA BASE DE DONNEES  *
*===============================================================================================*/
void creer_keyspace_dbFolder(char * Nom_keyspace);

/*=====================================================*
*  INSERTION DE LA RI INSERT DANS LA LISTE DES TABLES  *
*======================================================*/
void inserer_ligne_enqueue(LigneTable * debut, LigneTable val);
void inserer_ligne_table(char * nom_table, char * nom_keyspace, ValeurMaps debut);

/*================================*
*  INTERPRETEUR INSERT INTO TABLE *
*=================================*/
int inserer_colonne_value(ValeurMaps *debut, char * valeur);

/*===============================================*
*                LECTURE DES LIGNES DB           *
*================================================*/
/*================================*
*  CHARGEMENT DEPUIS JSON FILES   *
*=================================*/
static void print_depth_shift(int depth);
static LigneTable process_object(json_value* value, int depth);
static void process_array(json_value* value, int depth, LigneTable * lignes);
static void process_value(json_value* value, int depth, LigneTable * lignes);

/*================================================================================*
*  PARCOURS DES DOSSIERS ET CHARGEMENT DE CONTENUE DES TABLES DEPUIS JSON FILES   *
*=================================================================================*/
LigneTable get_ligne_table(char * nom_table, char * nom_keyspace);
valLigneTable * creer_val_ligne_table(char * nom_table, char * nom_keyspace);
void lire_DB_file();

/*===============================================*
*                ECRITURE DES LIGNES DB          *
*================================================*/
void ecrire_DB_file();
void sauvegarder_lignes_table(int table, LigneTable lignes);


    /*===================================================================*
  *                          INTERPRETEUR SELECT                            *
     *===================================================================*/
/*===========================================*
*  INTERPRETEUR SELECT * FROM keyspace.table *
*============================================*/
void get_tous_lignes_table(char * nomTable, char * nomKeyspace);
/*=======================================================*
*  AFFICHAGE DE RESULTAT DE SELECT * FROM keyspace.table *
*========================================================*/
void afficher_lignes_table( LigneTable lignes);
/*===========================================*
* AFFICHAGE DE CONTENUE DE TOUTES LES TABLES *
*============================================*/
void afficher_toutes_tables();


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

 void sauvegarderListeTable();

 /*===========================================+*
  *     SAUVEGARDER LA LISTE DES COLONNES      *
  *===========================================+*/

 void sauvColonnes(FILE* fileTables , ColonneDefinitions listeCln);

 /*===========================================+*
  *     SAUVEGARDER LA LISTE DES PROPRIETY     *
  *===========================================+*/

 void sauvProprietes(FILE* fileTables , Properties listeProp);

 /*=========================================++++++++==+*
  *     SAUVEGARDER LA LISTE DES VALEURS PROPRIETY     *
  *==========================================++++++++=+*/

 void sauvValPropriete(FILE* fileTables , ValeurPropriete vp);

 /*==============================================+*
  *     SAUVEGARDER LA LISTE DES VALEURS MAPS     *
  *==============================================+*/

 void sauvValeurMaps(FILE* fileTables , ValeurMaps listeVal);

 /*============================================+*
  *     SAUVEGARDER LA LISTE DES KEYSPACES      *
  *============================================+*/

 void sauvegarderListeKeyspaces();

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

 void chargerListeTable();


 /*===========================================+*
  *  CHARGEMENT DES COLONNES D'UNE TABLE       *
  *===========================================+*/

 ColonneDefinitions chargerColonnes(FILE* fileTables);


 /*===========================================+*
  *  CHARGEMENT DES PROPRIETES D'UNE TABLE     *
  *===========================================+*/

 Properties chargerProprietes(FILE* fileTables);


 /*===========================================+*
  *  CHARGEMENT DES VALEURS DES PROPRIETES     *
  *===========================================+*/

 ValeurPropriete chargerValPropriete(FILE* fileTables);


 /*===========================================+*
  *     CHARGEMENT DES VALEURS DE MAPS         *
  *===========================================+*/

 ValeurMaps chargerValeurMaps(FILE* fileTables);
