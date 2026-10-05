/**************************************
 *
 * University of Haifa
 *
 * Theory of compilation
 *
 * P machine compiler - code generation project
 *
 * Yosi Ben Asher
 * Email: yosibenasher@gmail.com
 *
 * Mariah Akree
 * Email: mariah.uni.haifa@gmail.com
 *
 **************************************/


#include "main.h"

///////////////////////////////////////
int StackAdd = 5;
int RightSonConst = 0;
int LeftSonVar = 0;
int Addval = 0;
int BackFromRightSonConst = 0;
int OpGlobal = 0;
int IfElseCounter = 1;
int IfElseTemp;
int ElseCon = 0;
int loopCounter = 1;
int switchNum = 1;
int casecount = 1;
int nestedlevel = -1;
int parameter_Send = 1;
int parameter_Send2 = 1;
int parameter_Send3 = 1;
int parameter_Send4 = 1;
int save_switch = 1;
//hw2 var
string varNm = "var";
string parentNm = "parent";
int recFlag = 0;
int ofst = 0;
int Add_no_need_to_print = 0;
int sz = 0;
int recref = 0;
int recref2 = 0;
int newst = 0;
string lastVar = "";
int AddRef = 0;
int firstAddressOnly = 0;
int prFirstAdd = 0;
int assignflagForRec = 0;
int recbegin = 0;
int ArraySz = 0;
int arrayf = 0;
int prevdim = 0;
string arraytp = "";
int arrayref_retname = 0;
string arrayNm = "";
int dimsflag = 0;
string Dimsof = "";
int arrayfromassign = 0;
int recinrec = 0;
int assign_flag_array = 0;
int random_Var_to_print = 0;
int dont_print_ind_for_record = 0;
int writeST = 0;
int backfromrecord = 0;
int backfromarray = 0;
int recEntry = 0;
int addvalcounter = 0;
int tempaddval = 0;
//hw3
string PrntFunction = "";
string CurrFunction = "";
string WayOfPassing = "byvalue";
int Parameters_size = 0;
int Declaration_begin_flag = 0;
int MST_counter = -1;
string calFunc = "";
int par_counter = 0;
int funcType = 0;
string real_or_not_procedure = "fake";
int expression_par_falg = 0;
int passing_parameters = 0;
string record_fielnd = "";






///////////////////////
/*

*/
extern int yydebug;
SymbolTable SymTab;
Funcs Functions_List;

void writeAST(Object* r, fstream& file)
{
    //Perform recursive tree print
    r->print(file);
}
void Pcode(Object* r, fstream& file)
{
    //Perform recursive tree print
    r->pcodegen(file);

}

Object* getTree(char* progFile)
{

    yydebug = 1;
    assert(progFile);

    // yyin is an external variable that been used in yyparse as pointer to the source file.
    yyin = fopen(progFile, "r");
    if (!yyin) {
        cerr << "Error: file " << progFile << " does not exst. Aborting ..." << endl;;
        exit(1);
    }
    assert(yyin);

    // yyparse is yacc function that parse the program, checks syntax and builds the program AST.
    yyparse();

    fclose(yyin);

    // root was initialized in yyparse while it was building the tree.
    // root is the pointer of the returning tree.
    assert(root);
    return(root);
}



int main(int argc, char* argv[])
{
    CodeGenerator codeGen;

    //check input arguments.
    if (argc < 2) {
        cerr << endl << "Input file is missing. Aborting ..." << endl;
        exit(1);
    }

    Object* theProgram = getTree(argv[1]);
    assert(theProgram == root);

    fstream treeFile(TREE_OUTPUT_TEXT_FILE, ios::out);
    fstream pcodeFile(OUTPUT_CODE_TEXT, ios::out);
    treeFile << AST_FILE_HEADER << endl;
    //pcodeFile << AST_FILE_HEADER << endl;
    writeAST(theProgram, treeFile);
    Pcode(theProgram, pcodeFile);
    treeFile.close();
    return (0);
}


