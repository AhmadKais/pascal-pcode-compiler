/******
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
 ******/
/*   PROGRAM = 258,
     BBEGIN = 259,
     END = 260,
     DECLARE = 261,
     PROCEDURE = 262,
     FUNCTION = 263,
     LABEL = 264,
     INTEGER = 265,
     REAL = 266,
     RECORD = 267,
     BOOLEAN = 268,
     ARRAY = 269,
     OF = 270,
     ASSIGN = 271,
     LC = 272,
     RC = 273,
     IF = 274,
     THEN = 275,
     ELSE = 276,
     WHILE = 277,
     REPEAT = 278,
     FI = 279,
     DO = 280,
     OD = 281,
     READ = 282,
     WRITE = 283,
     TRUE = 284,
     FALSE = 285,
     ADD = 286,
     MIN = 287,
     MUL = 288,
     DIV = 289,
     GOTO = 290,
     MOD = 291,
     LES = 292,
     LEQ = 293,
     EQU = 294,
     NEQ = 295,
     GRE = 296,
     GEQ = 297,
     AND = 298,
     OR = 299,
     NOT = 300,
     CASE = 301,
     FOR = 302,
     FIN = 303,
     IDENTICAL = 304,
     FROM = 305,
     BY = 306,
     TO = 307,
     NEW = 308,
     INTCONST = 309,
     IDE = 310,
     REALCONST = 311,
     STRING = 312,
     DUMMY = 313*/

#ifndef AST_H
#define AST_H

#include <iostream>
#include <assert.h>
#include <string>
#include <sstream>
#include <iostream>
#include <typeinfo>
#include <iomanip>
using namespace std;


extern int StackAdd;
extern int LeftSonVar;
extern int RightSonConst;
extern int BackFromRightSonConst;
extern int Addval;
extern int OpGlobal;
extern int IfElseCounter;
extern int IfElseTemp;
extern int ElseCon;
extern int loopCounter;
extern int switchNum;
extern int casecount;
extern int nestedlevel;
extern int parameter_Send;
extern int parameter_Send2;
extern int parameter_Send3;
extern int parameter_Send4;
extern int save_switch;
extern  string varNm;
extern  string parentNm;
extern  int recFlag;
extern int ofst;
extern int Add_no_need_to_print;
extern int sz;
extern int recref;
extern int recref2;
extern int newst;
extern string lastVar;
extern int prFirstAdd;
extern int assignflagForRec;
extern int recbegin;
extern int ArraySz;
extern int arrayf;
extern int prevdim;
extern string arraytp;
extern int arrayref_retname;
extern string arrayNm;
extern int dimsflag;
extern string Dimsof;
extern int assign_flag_array;
extern int random_Var_to_print;
extern int dont_print_ind_for_record ;
extern int writeST;
extern int backfromrecord;
extern int backfromarray;
extern int recEntry;
extern int addvalcounter;
extern int tempaddval;
// hw3 variables
extern string PrntFunction;
extern string CurrFunction;
extern string WayOfPassing;
extern int Parameters_size;
extern int Declaration_begin_flag;
extern int MST_counter;
extern string calFunc;
extern int par_counter;
extern int funcType;
extern string real_or_not_procedure;
extern int expression_par_falg;
extern int passing_parameters;
extern string record_fielnd;



//sybol table that i created
class function{
public:
    string funcname = "";
    string parent_func = "";
    string func_type ="funORpro";
    string real_or_not = "fake";
    int parameter_number = 0;
    int parsize = -1; // parsize also means calculates the sum of variable sizes
    int parameters_only_size = -1;
    function* next;
    function() {
        this->next = NULL;
    }
    function(string name) {
        this->funcname = name;
        this->next = NULL;
    }
    friend class Funcs;

};
class Funcs{
public:
    function* f_head;
    Funcs(){
        this->f_head = NULL;
    }
    void insert(string func_name){
        function* newf = new function(func_name);
        if(this->f_head == NULL){
            this->f_head = newf;
        }
        else{
            function* itr = this->f_head;
            while(itr->next != NULL)
                itr = itr->next;
            itr->next = newf;
        }
    }
    int find(string func){
        function* itr = this->f_head;
        if(itr != NULL) {
            while (itr->next != NULL && itr->funcname != func)
                itr = itr->next;
            if(itr->funcname == func)
                return 1;
        }
        return -1;
    }
    void update_fake_or_real(string fname, string fake_or_real){
        function* itr = this->f_head;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        itr->real_or_not = fake_or_real;
    }
    string ret_fake_or_real(string fname){
        function* itr = this->f_head;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        return itr->real_or_not;
    }
    void updateFparent(string fname,string Pname){
        function* itr = this->f_head;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        itr->parent_func = Pname;
    }
    void updateparnumber(string fname,int Psize){
        function* itr = this->f_head;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        itr->parameter_number = Psize;
    }
    int returnparameter_number(string fname){
        function* itr = this->f_head;
        string name = itr->funcname;
        int PS = itr->parameter_number;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        return itr->parameter_number;
    }
    string returnFparent(string fname){
        function* itr = this->f_head;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        return itr->parent_func;
    }
    void updateFPsize(string fname,int Psize){
        function* itr = this->f_head;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        itr->parsize = Psize;
    }
    int isthere(string func){
        function* itr = this->f_head;
        while(itr->next != NULL ) {
            if (itr->funcname == func)
                return 1;
            itr = itr->next;
        }
        return -1;
    }
    int retFPsize(string fname){
        function* itr = this->f_head;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        return itr->parsize;
    }
    void updateFtype(string fname,string type){
        function* itr = this->f_head;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        itr->func_type = type;
    }
    string retFtype(string fname){
        function* itr = this->f_head;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        return itr->func_type;
    }
    void update_Parameters_only_size(string fname,int size){
        function* itr = this->f_head;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        itr->parameters_only_size = size;
    }
    int ret_Parameters_Size_only(string fname){
        function* itr = this->f_head;
        while(itr->next != NULL && itr->funcname != fname)
            itr = itr->next;
        return itr->parameters_only_size;
    }
    int  calc_MST(string curr,string called){
        int counter = 1;
        if(curr == called) {
            return 1;
        }
        else if(returnFparent(called) == curr){
            return 0;
        }
        else if(returnFparent(curr) == called){
            return 2;
        }
        else {
            string parent = curr;
            while (parent != called && retFtype(parent) != "Main Program") {
                function *itr = this->f_head;
                while (itr != NULL && itr->funcname == parent) {
                    itr = itr->next;
                }
                counter++;
                parent = returnFparent(parent);
            }
        }
        return counter;
    }
    void Print(ostream& os){
        function* itr = this->f_head;
        os<<endl;
        os<<endl;
        os<<endl;
        os<<endl;
        os<<"*********************************************************"<<endl;
        os<<"*********************************************************"<<endl;
        os<<"*********************************************************"<<endl;
        while(itr != NULL){
            os<<"function name: " << itr->funcname << endl;
            os<<"parent function name: " << itr->parent_func << endl;
            os<<"parameters only : " << itr->parameters_only_size << endl;
            os<<"parameter + var size: " << itr->parsize << endl;
            os<<"function type : " << itr->func_type << endl;
            os<<"number of parameters : "<<itr->parameter_number<<endl;
            os<<"Fake Or Real : "<< itr->real_or_not<<endl;
            os<<"*********************************************************"<<endl;
            itr = itr->next;
        }
    }
    friend class SymbolTable;
};
extern Funcs Functions_List;

class Dims {
public:
    int h;
    int l;
    int len;
    int ixa = 1;
    Dims* next;

    Dims() {
        this->next = NULL;
    }
    Dims(int high, int low) {
        this->h = high;
        this->l = low;
        this->len = high - low + 1;
        this->next = NULL;
    }
    friend class Variable;
};

class Variable
{
public:
    string name;
    string type;
    string parent;
    string pointedAt; // only in case we are a pointer
    int size = 1;
    int address;
    int offset;
    int subpart = -1;
    string function_name = "";
    string WayOfPassing = "byvalue";
    Dims* Dimentions;
    Variable* next;

    Variable()
    {
        next = NULL;
    }

    Variable(string name, int address)
    {
        this->name = name;
        this->address = address;
        next = NULL;
        Dimentions = NULL;
    }
    void AddDims(int high, int low) {
        if (this->Dimentions == NULL) {
            Dims* dim = new Dims(high, low);
            this->Dimentions = dim;
        }
        else {
            Dims* dim = new Dims(high, low);
            Dims* itr = this->Dimentions;
            while (itr->next != NULL) {
                itr = itr->next;
            }
            itr->next = dim;
        }
    }
    friend class SymbolTable;
};

class SymbolTable
{

    /* Think! what can you add to  symbol_table */
    Variable* head;

public:
    SymbolTable()
    {
        head = NULL;
    }

    // Function to find an identifier
    int find(string id)
    {
        Variable* start = head;

        if (start == NULL)
            return -1;

        while (start != NULL)
        {

            if (start->name == id)
            {
                return start->address;
            }

            start = start->next;
        }

        return -1; // not found
    }

    // Function to insert an identifier
    void insert(string id, int address)
    {
        Variable* p = new Variable(id, address);
        Variable* newHead = p;
        p->next = NULL;
        if(this->head == NULL){//this ST is empty
            this->head = p;
        }
        else{
            Variable* itr = this->head;
            while(itr->next != NULL)
                itr=itr->next;
            itr->next = p;
        }
    }
    void updateType(string id, string type) {
        Variable* itr = head;
        while (itr->name != id && itr != NULL)
            itr = itr->next;
        if (itr->name == id) {
            itr->type = type;
        }
    }
    string retType(string id) {
        Variable* itr = head;
        if(itr != NULL) {
            while (itr->name != id && itr->next != NULL)
                itr = itr->next;
            if (itr->name == id) {
                return itr->type;
            }
            else {
                return "";
            }
        }
        return "";

    }
    void updateOffSet(string id, int OffSet) {
        Variable* itr = head;
        while (itr->name != id && itr != NULL)
            itr = itr->next;
        if (itr->name == id) {
            itr->offset = OffSet;
        }
    }
    void updateSize(string id, int sz) {
        Variable* itr = head;
        while (itr->name != id && itr != NULL)
            itr = itr->next;
        if (itr->name == id) {
            itr->size = sz;
        }
    }
    int retSize(string id) {
        Variable* itr = head;
        while (itr->name != id && itr != NULL)
            itr = itr->next;
        if (itr->name == id) {
            return itr->size;
        }
        else return -1;
    }
    int retSubPart(string id) {
        Variable* itr = head;
        while (itr->name != id && itr != NULL)
            itr = itr->next;
        if (itr->name == id) {
            return itr->subpart;
        }
        else return -1;
    }
    int retoffset(string id) {
        Variable* itr = head;
        while (itr->name != id && itr != NULL)
            itr = itr->next;
        if (itr->name == id) {
            return itr->offset;
        }
        else return -1;
    }
    void updateparent(string id, string parent) {
        Variable* itr = head;
        while (itr->name != id && itr != NULL)
            itr = itr->next;
        if (itr->name == id) {
            itr->parent = parent;
        }
    }
    void updatePointedAt(string id, string PointedAt) {
        Variable* itr = head;
        while (itr->name != id && itr != NULL)
            itr = itr->next;
        if (itr->name == id) {
            itr->pointedAt = PointedAt;
        }
    }
    string retPointedAt(string id) {
        Variable* itr = head;
        while (itr->name != id && itr != NULL)
            itr = itr->next;
        if (itr->name == id) {
            return itr->pointedAt;
        }
        else { return "no"; }
    }
    void updateoffset(string id, int offset) {
        Variable* itr = head;
        while (itr->name != id && itr != NULL)
            itr = itr->next;
        if (itr->name == id) {
            itr->offset = offset;
        }
    }
    Variable* returnVar(string id) {
        Variable* itr = head;
        while (itr->name != id && itr != NULL)
            itr = itr->next;
        if (itr->name == id) {
            return itr;
        }
        else return NULL;
    }
    void updateSubPart(string id) {
        Variable* itr = returnVar(id);
        if (itr == NULL) return;
        int TypeSz = 1;
        if (itr != NULL) {
            string TP = itr->type;
            if (TP != "Integer" && TP != "Real" && TP != "Boolean") {
                Variable* itrator = returnVar(itr->type);
                if (itrator == NULL) {
                    return;
                }
                TypeSz = itrator->size;
            }
            Dims* di = itr->Dimentions;
            if (di->next == NULL) {
                itr->subpart = (di->l) * TypeSz;
            }
            else {
                int Subp = 0;
                while (di->next != NULL) {
                    int Sp = 1;
                    if (di->next == NULL) {
                        itr->subpart = (di->l) * TypeSz;
                        break;
                    }
                    else {
                        Dims* innerdi = di;
                        while (innerdi->next != NULL) {
                            innerdi = innerdi->next;
                            Sp = Sp * (innerdi->len);
                        }
                        Subp = Subp + Sp * (di->l);
                        di = di->next;
                    }
                }
                Subp = Subp + (di->l);
                itr->subpart = Subp * TypeSz;
            }
        }
    }
    void updateIxa(string id) {
        Variable* itr = returnVar(id);
        if (itr == NULL) return;
        int TypeSz = 1;
        if (itr != NULL) {
            string TP = itr->type;
            if (TP != "Integer" && TP != "Real" && TP != "Boolean") {
                Variable* itrator = returnVar(TP);
                if (itrator == NULL) {
                    return;
                }
                TypeSz = itrator->size;
            }
            Dims* di = itr->Dimentions;
            if (di->next == NULL) {
                di->ixa = TypeSz;
            }
            while (di->next != NULL) {
                int ixaVar = 1;
                if (di->next == NULL) {//this means that wew are in the last dim
                    di->ixa = TypeSz;
                    break;
                }
                else {
                    Dims* innerdi = di;
                    while (innerdi->next!= NULL) {
                        innerdi = innerdi->next;
                        ixaVar = ixaVar * (innerdi->len);
                    }
                    di->ixa = ixaVar * TypeSz;
                    di = di->next;
                }
                di->ixa = TypeSz;
            }
        }
    }
    string RetWayOfPassingByindex(string funcName, int index){
        Variable* itr = this->head;
        int new_index = index;
        while(itr->function_name != funcName && itr->next != NULL){
            itr = itr->next;
        }
        //maybe i need to print that
        if(Functions_List.retFtype(funcName) == "func"){
            itr = itr->next;
        }
        if(itr->function_name == funcName){
            while(new_index != 0){
                itr = itr->next;
                new_index--;
            }
            return itr->WayOfPassing;
        }
        return "";
    }
    void printST(ostream& os) {
        Variable* itr = head;
        os<<endl;
        os<<endl;
        os<<endl;
        os << "**************************************************************************" << endl;
        os << "**************************************************************************" << endl;
        os << "**************************************************************************" << endl;
        os << "**************************************************************************" << endl;
        os << "The Symbol Table :" << endl;
        if (itr == NULL) {
            os << "SymTab is empty" << endl;
            return;
        }

        while (itr != NULL) {
            os << "------------------------------------" << endl;
            os << "name:   " << itr->name << endl;
            os << "type:   " << itr->type << endl;
            os << "Address:  " << itr->address << endl;
            os << "Size:  " << itr->size << endl;
            os << "parent:  " << itr->parent << endl;
            os << "offset:  " << itr->offset << endl;
            os << "PointedAt:  " << itr->pointedAt << endl;
            os << "subpart :  " << itr->subpart << endl;
            os << "Function belongs to:  " << itr->function_name << endl;
            os << "WayOfPassing :  " << itr->WayOfPassing << endl;
            if (itr->Dimentions != NULL) {
                Dims* itr2 = itr->Dimentions;
                while (itr2 != NULL) {
                    os << "Dimensiond :" << "    high : " << itr2->h << "    low : " << itr2->l;
                    os<< "    len:  " << itr2->len << "    ixa : " << itr2->ixa<< endl;
                    itr2 = itr2->next;
                }
            }
            itr = itr->next;
        }
    }
    void updatefunction(string id, string func) {
        Variable* itr = head;
        while (itr->name != id && itr->next != NULL)
            itr = itr->next;
        if (itr->name == id) {
            itr->function_name = func;
        }
    }
    string retFuncName(string id) {
        Variable* itr = head;
        while (itr->name != id && itr->next != NULL)
            itr = itr->next;
        if (itr->name == id) {
            return itr->function_name;
        }
        else return "Variable has no function";
    }
    void updateWayOfPassing(string id, string WayofPs) {
        Variable* itr = head;
        while (itr->name != id && itr->next != NULL)
            itr = itr->next;
        if (itr->name == id) {
            itr->WayOfPassing = WayofPs;
        }
    }
    string retWayOfPs(string id) {
        Variable* itr = head;
        while (itr->name != id && itr->next != NULL)
            itr = itr->next;
        if (itr->name == id) {
            return itr->WayOfPassing;
        }
        else return "Variable has no WayOfPassing";
    }
    int  Calc_Print_LDA(string calling_function , string variable){
        string curfunc = calling_function;
        int address = find(variable);
        int relative = 0;
        string variables_function = retFuncName(variable);
        if(calling_function == variables_function){
            return 0;
        }
        else{
            string parentfunc = Functions_List.returnFparent(curfunc);
            relative++;
            while(parentfunc != variables_function){
                parentfunc = Functions_List.returnFparent(parentfunc);
                relative++;
            }
            return relative;
        }
    }

};
extern SymbolTable SymTab;
static Dims* DimsPtr = NULL;




/*
end of what i have added*/

/**
 * classes
 */
//I am adding a symbol table implementation
// base class for tree nodes
class Object {
public:
    virtual void print(ostream& os) = 0;
    virtual void pcodegen(ostream& os) = 0;
    virtual Object* clone() const { return NULL; }
    virtual ~Object() {}
};

class Expr : public Object {
public:
    // Unary operations
    Expr(int op, Object* atom) : op_(op), atom_(atom), left_(NULL), right_(NULL), unary_(true) {}
    // Binary operations
    Expr(int op, Object* left, Object* right) : op_(op), left_(left), right_(right), atom_(NULL), unary_(false) {}

    Expr(const Expr& exp) {
        unary_ = exp.unary_;
        op_ = exp.op_;
        left_ = exp.left_->clone();
        right_ = exp.right_->clone();
        atom_ = exp.atom_->clone();
    }

    virtual ~Expr() {
        if (left_) delete left_;
        if (right_) delete right_;
        if (atom_) delete atom_;
    }


    void print(ostream& os) {
        os << " Node name : Expr" << endl;
        assert(op_);
        if (unary_) {
            os << " Unary op is : " << op_;
            assert(atom_);
            atom_->print(os);
        }
        else {
            os << " Binary op is : " << op_;
            assert(left_ && right_);
            left_->print(os);
            right_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(op_);
        if (unary_) {
            assert(atom_);
            if (op_ == 287) {
                atom_->pcodegen(os);
                os << "neg" << endl;
            }
            else if (op_ == 286) {
                os << "inc";
                RightSonConst = 1;
                atom_->pcodegen(os);
            }
                // NOT = 300,
            else if (op_ == 300) {
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                atom_->pcodegen(os);
                os << "not" << endl;
            }
        }
        else {
            assert(left_ && right_);//add
            if (op_ == 286) {// Addval 0 with LDC only : adress but with 1 this means i need also the ind
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                OpGlobal = op_;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 1;
                OpGlobal = op_;
                left_->pcodegen(os);
                if (BackFromRightSonConst != 0)
                    os << "add" << endl;
                BackFromRightSonConst = 1;

            }
            else if (op_ == 287) {//0 with LDC // sub
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                OpGlobal = op_;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 1;
                OpGlobal = op_;
                left_->pcodegen(os);
                if (BackFromRightSonConst != 0)
                    os << "sub" << endl;
                BackFromRightSonConst = 1;

            }
            else if (op_ == 288) {//mul
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                left_->pcodegen(os);
                os << "mul" << endl;
            }
            else if (op_ == 289) {//div
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                left_->pcodegen(os);
                os << "div" << endl;
            }
            else if (op_ == 298) {//and
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                left_->pcodegen(os);
                os << "and" << endl;
            }
            else if (op_ == 299) {//or
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                left_->pcodegen(os);
                os << "or" << endl;
            }
            else if (op_ == 292) {// LES = 292,
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                left_->pcodegen(os);
                os << "les" << endl;
            }
            else if (op_ == 293) {//LEQ = 293,
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                left_->pcodegen(os);
                os << "leq" << endl;
            }
            else if (op_ == 294) {//  EQU = 294,
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                left_->pcodegen(os);
                os << "equ" << endl;
            }
            else if (op_ == 295) {//NEQ = 295,
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                left_->pcodegen(os);
                os << "neq" << endl;
            }
            else if (op_ == 296) {// GRE = 296,
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                left_->pcodegen(os);
                os << "grt" << endl;
            }
            else if (op_ == 297) {// GEQ = 297,
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                right_->pcodegen(os);
                Addval = 1;
                assignflagForRec = 1;
                assign_flag_array = 1;
                RightSonConst = 0;
                left_->pcodegen(os);
                os << "geq" << endl;
            }
        }
    }
    virtual Object* clone() const { return new Expr(*this); }

private:
    bool unary_;
    int op_;
    Object* left_;
    Object* right_;
    Object* atom_;
};

class ExprList : public Object {
public:
    ExprList(Object* expr) : expr_(expr), expr_list_(NULL) { assert(expr_); }
    ExprList(Object* expr, Object* expr_list) : expr_(expr), expr_list_(expr_list) { assert(expr_ && expr_list_); }

    ExprList(const ExprList& exp) {
        expr_ = exp.expr_->clone();
        expr_list_ = exp.expr_list_->clone();
    }

    virtual ~ExprList() {
        if (expr_) delete expr_;
        if (expr_list_) delete expr_list_;
    }

    void print(ostream& os) {
        os << " Node name : ExprList";
        assert(expr_);
        expr_->print(os);
        if (expr_list_) {
            expr_list_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(expr_);
        expr_->pcodegen(os);
        if (expr_list_) {
            expr_list_->pcodegen(os);
        }
        //os << "xepresion list" << endl;
    }
    virtual Object* clone() const { return new ExprList(*this); }

private:
    Object* expr_;
    Object* expr_list_;
};

class Dim : public Object {
public:
    Dim(Object* exp) : exp_(exp), dim_(NULL) { assert(exp_); }
    Dim(Object* exp, Object* dim) : exp_(exp), dim_(dim) { assert(exp_ && dim_); }

    Dim(const Dim& d) {
        exp_ = d.exp_->clone();
        dim_ = d.dim_->clone();
    }

    virtual ~Dim() {
        if (exp_) delete exp_;
        if (dim_) delete dim_;
    }

    void print(ostream& os) {
        os << " Node name : Dim" << endl;
        assert(exp_);
        exp_->print(os);
        if (dim_) {
            dim_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(exp_);
        if(addvalcounter == 0){//this means that this is the first time we enter this array
            tempaddval = assign_flag_array;
            addvalcounter++;
        }
        exp_->pcodegen(os);
        os << "ixa " << DimsPtr->ixa << endl;
        if (DimsPtr->next != NULL) {
            DimsPtr = DimsPtr->next;
            if (dim_)
                dim_->pcodegen(os);
        }
        else{
            os << "dec " << SymTab.retSubPart(Dimsof) << endl;
            string Tp = SymTab.retType(Dimsof);
            if (Tp != "Integer" && Tp != "Real" && Tp != "Boolean" && Tp != "AddressType" ) {
                Variable* moh = SymTab.returnVar(Tp);
                Dimsof = moh->name;
                DimsPtr = moh->Dimentions;
                if (dim_)
                    dim_->pcodegen(os);
            }
            else {
                if((tempaddval == 1 || writeST == 1) && !(dim_) && SymTab.find(Tp) ==-1) {
                    os << "ind" << endl;
                }
                addvalcounter = 0;
            }
        }
    }
    virtual Object* clone() const { return new Dim(*this); }

private:
    Object* exp_;
    Object* dim_;
};

class Atom : public Object {
};

class IntConst : public Atom {
public:
    IntConst(const int i) : i_(i) {}
    IntConst(const IntConst& in) : i_(in.i_) {}

    void print(ostream& os) {
        os << " Node name : IntConst. Value is :" << i_ << endl;
    }
    void pcodegen(ostream& os) {
        if (RightSonConst == 1) {
            if (OpGlobal == 286) {
                OpGlobal = 0;
                os << "inc " << i_ << endl;;
                BackFromRightSonConst = 0;
            }
            else if (OpGlobal == 287) {
                OpGlobal = 0;
                os << "dec " << i_ << endl;;
                BackFromRightSonConst = 0;
            }
            else {
                BackFromRightSonConst = 1;
                os << "ldc " << i_ << endl;
            }
        }
        if (RightSonConst == 0) {
            BackFromRightSonConst = 1;
            os << "ldc " << i_ << endl;
        }
    }
    virtual Object* clone() const { return new IntConst(*this); }

private:
    const int i_;
};

class RealConst : public Atom {
public:
    RealConst(const double r) : r_(r) {}
    RealConst(const RealConst& in) : r_(in.r_) {}

    void print(ostream& os) {
        os << " Node name : RealConst. Value is :" << r_ << endl;
    }
    void pcodegen(ostream& os) {
        if (RightSonConst == 1) {
            if (OpGlobal == 286) {
                OpGlobal = 0;
                os << "inc " << fixed << setprecision(1) << r_ << endl;
                BackFromRightSonConst = 0;
            }
            else if (OpGlobal == 287) {
                OpGlobal = 0;
                os << "dec " << r_ << endl;;
                BackFromRightSonConst = 0;
            }
            else {
                BackFromRightSonConst = 1;
                os << "ldc " << fixed << setprecision(1) << r_ << endl;
            }
        }
        if (RightSonConst == 0) {
            BackFromRightSonConst = 1;
            os << "ldc " << fixed << setprecision(1) << r_ << endl;
        }

    }
    virtual Object* clone() const { return new RealConst(*this); }

private:
    const double r_;
};

class True : public Atom {
public:
    void print(ostream& os) {
        os << " Node name : trueConst. Value is true" << endl;
    }
    void pcodegen(ostream& os) {
        os << "ldc 1" << endl;
    }
    virtual Object* clone() const { return new True(); }

};

class False : public Atom {
public:
    void print(ostream& os) {
        os << " Node name : trueConst. Value is false" << endl;
    }
    void pcodegen(ostream& os) {
        os << "ldc 0" << endl;
    }
    virtual Object* clone() const { return new False(); }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//most of the code below till Symbole table was added by me
class Var : public Atom {
};

class ArrayRef : public Var {
public:
    ArrayRef(Object* var, Object* dim) : var_(var), dim_(dim) { assert(var_ && dim_); }
    ArrayRef(const ArrayRef& arr) {
        var_ = arr.var_->clone();
        dim_ = arr.dim_->clone();
    }

    virtual ~ArrayRef() {
        if (var_) delete var_;
        if (dim_) delete dim_;
    }

    void print(ostream& os) {
        os << " Node name : ArrayRef" << endl;
        assert(var_ && dim_);
        var_->print(os);
        dim_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(var_ && dim_);
        backfromarray = 1;
        arrayref_retname = 1;
        var_->pcodegen(os);
        arrayref_retname = 0;
        //need to take the size of the type of the arrays
        dim_->pcodegen(os);
        arrayref_retname = 0;
    }
    virtual Object* clone() const { return new ArrayRef(*this); }

private:
    Object* var_;
    Object* dim_;
};

class RecordRef : public Var {
public:
    RecordRef(Object* varExt, Object* varIn) : varExt_(varExt), varIn_(varIn) { assert(varExt_ && varIn_); }
    RecordRef(const RecordRef& rec) {
        varExt_ = rec.varExt_->clone();
        varIn_ = rec.varIn_->clone();
    }

    virtual ~RecordRef() {
        if (varExt_) delete varExt_;
        if (varIn_) delete varIn_;
    }

    void print(ostream& os) {
        os << " Node name : RecordRef" << endl;
        assert(varExt_ && varIn_);
        varExt_->print(os);
        varIn_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(varExt_ && varIn_);
        if (assignflagForRec == 0) {
            if (newst == 1 && prFirstAdd == 0) { prFirstAdd = 1; recref = 0; }
            recEntry = 1;
            varExt_->pcodegen(os);
            recref2 = 1;
            recref = 1;
            recEntry = 0;
            varIn_->pcodegen(os);
            recref = 0;
        }
        if (assignflagForRec == 1) {
            Addval = 0;
            RightSonConst = 0;
            if (newst == 1 && prFirstAdd == 0) { prFirstAdd = 1; recref = 0; }
            varExt_->pcodegen(os);
            recref2 = 1;
            recref = 1;
            varIn_->pcodegen(os);
            recref = 0;
            backfromrecord = 1;
        }
    }
    virtual Object* clone() const { return new RecordRef(*this); }

private:
    Object* varExt_;
    Object* varIn_;
};

class AddressRef : public Var {
public:
    AddressRef(Object* var) : var_(var) { assert(var_); }
    AddressRef(const AddressRef& addre) {
        var_ = addre.var_->clone();
    }

    virtual ~AddressRef() {
        if (var_) delete var_;
    }

    void print(ostream& os) {
        os << " Node name : AddressRef" << endl;
        assert(var_);
        var_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(var_);
        var_->pcodegen(os);
        os << "ind" << endl;
       // SymTab.printST(os);
        if(passing_parameters == 1){//this means that we are passing a pointer to something
            int size = SymTab.retSize(SymTab.retPointedAt(record_fielnd));
            if(size > 1){
                os<<"movs "<< size <<endl;
            }
        }
    }
    virtual Object* clone() { return new AddressRef(*this); }

private:
    Object* var_;
};

class Statement : public Object {
};

class NewStatement : public Statement {
public:
    NewStatement(Object* var) : var_(var) { assert(var_); }
    NewStatement(const NewStatement& ns) {
        var_ = ns.var_->clone();
    }

    virtual ~NewStatement() {
        if (var_) delete var_;
    }

    void print(ostream& os) {
        os << " Node name : NewStatement";
        assert(var_);
        var_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(var_);
        newst = 1;
        var_->pcodegen(os);
        newst = 0;
        recref2 = 0;
        string P_At = SymTab.retPointedAt(lastVar);
        os << "ldc " << SymTab.retSize(P_At) << endl;
        os << "new" << endl;
        prFirstAdd = 0;
    }
    virtual Object* clone() { return new NewStatement(*this); }

private:
    Object* var_;
};

class WriteStrStatement : public Statement {
public:
    WriteStrStatement(const char* str) {
        str_ = new string(str);
    }

    WriteStrStatement(const WriteStrStatement& ns) {
        str_ = new string(*ns.str_);
    }

    virtual ~WriteStrStatement() {
        if (str_) delete str_;
    }
    void print(ostream& os) {
        os << " Node name : WriteStrStatement";
        assert(str_);
        os << "Str statement is: " << str_ << endl;
    }
    void pcodegen(ostream& os) {
        assert(str_);
        os << "print" << endl;

    }
    virtual Object* clone() { return new WriteStrStatement(*this); }

private:
    string* str_;
};

class WriteVarStatement : public Statement {
public:
    WriteVarStatement(Object* exp) : exp_(exp) { assert(exp_); }

    WriteVarStatement(const WriteVarStatement& ex) {
        exp_ = ex.clone();
    }

    virtual ~WriteVarStatement() {
        if (exp_) delete exp_;
    }

    void print(ostream& os) {
        os << " Node name : WriteVarStatement";
        assert(exp_);
        exp_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(exp_);
        Addval = 1;
        assignflagForRec = 1;
        assign_flag_array = 1;
        writeST = 1;
        exp_->pcodegen(os);
        writeST = 0;
        Addval = 0;
        assignflagForRec = 0;
        assign_flag_array = 0;
        os << "print" << endl;

    }
    virtual Object* clone() const { return new WriteVarStatement(*this); }

private:
    Object* exp_;
};

class ProcedureStatement : public Statement {
public:
    ProcedureStatement(const char* str) {
        str_ = new string(str);
    }

    ProcedureStatement(Object* expr_list, const char* str) : expr_list_(expr_list) {
        assert(expr_list_);
        str_ = new string(str);
    }

    ProcedureStatement(const ProcedureStatement& ps) {
        expr_list_ = ps.expr_list_->clone();
        str_ = new string(*ps.str_);
    }

    virtual ~ProcedureStatement() {
        if (str_) delete str_;
        if (expr_list_) delete expr_list_;
    }

    void print(ostream& os) {
        os << " Node name : ProcedureStatement. Proc name : " << *str_ << endl;
        if (expr_list_) {
            expr_list_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        if(Functions_List.find(SymTab.retType(*str_))== 1){//this means that i am calling a function that was passed by parameter
            os<<"mstf "<<SymTab.Calc_Print_LDA(CurrFunction,*str_) <<" "<< SymTab.find(*str_)<<endl;
            funcType = 1;
        }
        else {
            os << "mst " << Functions_List.calc_MST(CurrFunction, *str_) << endl;
        }
        MST_counter = 0;
        calFunc = *str_;
        if (expr_list_) {
            passing_parameters = 1;
            expr_list_->pcodegen(os);
            passing_parameters = 0;
        }
        MST_counter = -1;
        if(funcType == 1){
            os<<"smp "<<Functions_List.ret_Parameters_Size_only(*str_)<<endl;
            os<<"cupi "<<SymTab.Calc_Print_LDA(CurrFunction,*str_) <<" "<< SymTab.find(*str_)<<endl;
            funcType = 0;
        }
        else
            os<<"cup " << Functions_List.ret_Parameters_Size_only(*str_) << " "<<*str_<<endl;
    }
    virtual Object* clone() const { return new ProcedureStatement(*this); }

private:
    Object* expr_list_;
    string* str_;
};

class Case : public Object {
public:
    Case(Object* stat_list, int val) : leafChild_(NULL), stat_list_(stat_list) {
        // note the special treatment in miny.y for this case (makenode)
        leafChild_ = new IntConst(val);
        assert(stat_list_);
    }

    Case(const Case& c) {
        stat_list_ = c.stat_list_->clone();
        leafChild_ = c.leafChild_->clone();
    }

    virtual ~Case() {
        if (stat_list_) delete stat_list_;
        if (leafChild_) delete leafChild_;
    }

    void print(ostream& os) {
        os << " Node name : Case";
        assert(stat_list_);
        stat_list_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(stat_list_);
        int curr_switch = parameter_Send2;
        int curr_case = parameter_Send3;
        os << "case_" << curr_case << "_" << curr_switch << ":" << endl;
        stat_list_->pcodegen(os);
        os << "ujp end_switch_" << curr_switch << endl;
    }
    virtual Object* clone() const { return new Case(*this); }

private:
    Object* stat_list_;
    Object* leafChild_;
};


class CaseList : public Object {
public:
    CaseList(Object* ccase) : case_(ccase), case_list_(NULL) { assert(case_); }
    CaseList(Object* ccase, Object* case_list) : case_(ccase), case_list_(case_list) { assert(case_ && case_list_); }

    CaseList(const CaseList& cl) {
        case_ = cl.case_->clone();
        case_list_ = cl.case_list_->clone();
    }

    virtual ~CaseList() {
        if (case_) delete case_;
        if (case_list_) delete case_list_;
    }

    void print(ostream& os) {
        os << " Node name : CaseList";
        assert(case_);
        case_->print(os);
        if (case_list_) {
            case_list_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(case_);
        int curr_switch = save_switch;
        int curr_case = casecount;
        parameter_Send2 = curr_switch;
        parameter_Send3 = curr_case;
        case_->pcodegen(os);
        if (case_list_) {
            casecount++;
            case_list_->pcodegen(os);
        }
        os << "ujp case_" << curr_case << "_" << curr_switch << endl;
    }
    virtual Object* clone() const { return new CaseList(*this); }

private:
    Object* case_;
    Object* case_list_;
};

class CaseStatement : public Statement {
public:
    CaseStatement(Object* exp, Object* case_list) : exp_(exp), case_list_(case_list) { assert(exp_ && case_list_); }

    CaseStatement(const CaseStatement& cs) {
        exp_ = cs.exp_->clone();
        case_list_ = cs.case_list_->clone();
    }

    virtual ~CaseStatement() {
        if (exp_) delete exp_;
        if (case_list_) delete case_list_;
    }

    void print(ostream& os) {
        os << " Node name : CaseStatement";
        assert(exp_ && case_list_);
        exp_->print(os);
        case_list_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(exp_ && case_list_);
        Addval = 1;
        assignflagForRec = 1;
        assign_flag_array = 1;
        exp_->pcodegen(os);
        int curr_switch = switchNum;
        switchNum++;
        int curr_case = casecount;
        casecount = 1;
        save_switch = curr_switch;
        parameter_Send = save_switch;
        int save_ss = save_switch;
        os << "neg" << endl;
        os << "ixj end_switch_" << curr_switch << endl;
        case_list_->pcodegen(os);
        casecount = curr_case;
        save_switch = save_ss - 1;
        os << "end_switch_" << curr_switch << ":" << endl;

        //switchNum--;
    }
    virtual Object* clone() const { return new CaseStatement(*this); }

private:
    Object* exp_;
    Object* case_list_;
};

class LoopStatement : public Statement {
public:
    LoopStatement(Object* exp, Object* stat_list) : exp_(exp), stat_list_(stat_list) { assert(exp_ && stat_list_); }

    LoopStatement(const LoopStatement& ls) {
        exp_ = ls.exp_->clone();
        stat_list_ = ls.stat_list_->clone();
    }

    virtual ~LoopStatement() {
        if (exp_) delete exp_;
        if (stat_list_) delete stat_list_;
    }

    void print(ostream& os) {
        os << " Node name : LoopStatement";
        assert(exp_ && stat_list_);
        exp_->print(os);
        stat_list_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(exp_ && stat_list_);
        int TempLoopC = loopCounter;
        os << "loop_" << loopCounter << ":" << endl;
        exp_->pcodegen(os);
        os << "fjp end_loop_" << loopCounter << endl;
        loopCounter++;
        stat_list_->pcodegen(os);
        os << "ujp loop_" << TempLoopC << endl;
        os << "end_loop_" << TempLoopC << ":" << endl;
    }
    virtual Object* clone() const { return new LoopStatement(*this); }

private:
    Object* exp_;
    Object* stat_list_;
};


class ConditionalStatement : public Statement {
public:
    ConditionalStatement(Object* exp, Object* stat_list_if) : exp_(exp), stat_list_if_(stat_list_if), stat_list_else_(NULL) { assert(exp_ && stat_list_if_); }
    ConditionalStatement(Object* exp, Object* stat_list_if, Object* stat_list_else) : exp_(exp), stat_list_if_(stat_list_if), stat_list_else_(stat_list_else) { assert(exp_ && stat_list_if_ && stat_list_else_); }

    ConditionalStatement(const ConditionalStatement& cs) {
        exp_ = cs.exp_->clone();
        stat_list_if_ = cs.stat_list_if_->clone();
        stat_list_else_ = cs.stat_list_else_->clone();
    }

    virtual ~ConditionalStatement() {
        if (exp_) delete exp_;
        if (stat_list_if_) delete stat_list_if_;
        if (stat_list_else_) delete stat_list_else_;
    }

    void print(ostream& os) {
        os << " Node name : ConditionalStatement";
        assert(exp_ && stat_list_if_);
        exp_->print(os);
        stat_list_if_->print(os);
        if (stat_list_else_) {
            stat_list_else_->print(os);
        }
    }
    void pcodegen(ostream& os) {

        assert(exp_ && stat_list_if_);
        exp_->pcodegen(os);
        int temp = IfElseCounter;
        IfElseCounter++;
        if (stat_list_else_) {
            os << "fjp else_if_" << temp << endl;
            stat_list_if_->pcodegen(os);
            ElseCon = 0;
            os << "ujp " << "end_if_" << temp << endl;
            os << "else_if_" << temp << ":" << endl;
            ElseCon = 1;
            stat_list_else_->pcodegen(os);
        }
        else {
            os << "fjp end_if_" << temp << endl;
            stat_list_if_->pcodegen(os);
        }
        os << "end_if_" << temp << ":" << endl;


    }
    virtual Object* clone() const { return new ConditionalStatement(*this); }

private:
    Object* exp_;
    Object* stat_list_if_;
    Object* stat_list_else_;
};


class Assign : public Statement {
public:
    Assign(Object* var, Object* exp) : var_(var), exp_(exp) { assert(var_ && exp_); }

    Assign(const Assign& as) {
        var_ = as.var_->clone();
        exp_ = as.exp_->clone();
    }

    virtual ~Assign() {
        if (exp_) delete exp_;
        if (var_) delete var_;
    }

    void print(ostream& os) {
        os << " Node name : Assign";
        assert(var_ && exp_);
        exp_->print(os);
        var_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(var_ && exp_);
        Addval = 0;
        assignflagForRec = 0;
        assign_flag_array = 0;
        RightSonConst = 0;
        //sAdd_no_need_to_print = 1;
        exp_->pcodegen(os);
        //Addval = 0;
        Addval = 1;
        RightSonConst = 0;
        assignflagForRec = 1;
        assign_flag_array = 1;
        //
        recbegin = 1;
        //
        var_->pcodegen(os);
        if(backfromrecord == 1 && assign_flag_array != 1){
            os << "ind" << endl;
            backfromrecord = 0;
        }
        Addval = 0;
        Add_no_need_to_print = 0;
        assignflagForRec = 0;
        assign_flag_array=0;
        os << "sto" << endl;
    }
    virtual Object* clone() const { return new Assign(*this); }

private:
    Object* var_;
    Object* exp_;
};

class StatementList : public Object {
public:
    StatementList(Object* stat) : stat_list_(NULL), stat_(stat) { assert(stat_); }
    StatementList(Object* stat_list, Object* stat) : stat_list_(stat_list), stat_(stat) { assert(stat_list_ && stat); }

    StatementList(const StatementList& sl) {
        stat_ = sl.stat_->clone();
        stat_list_ = sl.stat_list_->clone();
    }

    virtual ~StatementList() {
        if (stat_) delete stat_;
        if (stat_list_) delete stat_list_;
    }

    void print(ostream& os) {
        os << " Node name : StatementList" << endl;
        if (stat_list_) {
            stat_list_->print(os);
        }
        assert(stat_);
        stat_->print(os);
    }
    void pcodegen(ostream& os) {
       if(random_Var_to_print == 0) {
           random_Var_to_print++;
       }
       if(Functions_List.retFPsize(CurrFunction) == -1){
           Functions_List.updateFPsize(CurrFunction,Parameters_size+5);
           os<<CurrFunction<<":"<<endl;
           os<<"ssp "<<Functions_List.retFPsize(CurrFunction)<<endl;
           os<<"sep 50"<<endl;
           os<<"ujp "<<CurrFunction<<"_begin"<<endl;
       }
       if(Declaration_begin_flag == 0) {
           os << CurrFunction << "_begin:" << endl;
           Declaration_begin_flag++;
       }
        if (stat_list_) {
            stat_list_->pcodegen(os);
        }
        assert(stat_);
        stat_->pcodegen(os);
    }
    virtual Object* clone() const { return new StatementList(*this); }

private:
    Object* stat_;
    Object* stat_list_;
};

class RecordList : public Object {
public:
    RecordList(Object* var_decl) : record_list_(NULL), var_decl_(var_decl) { assert(var_decl_); }
    RecordList(Object* record_list, Object* var_decl) : record_list_(record_list), var_decl_(var_decl) { assert(record_list_ && var_decl); }

    RecordList(const RecordList& li) {
        var_decl_ = li.var_decl_->clone();
        record_list_ = li.record_list_->clone();
    }

    virtual ~RecordList() {
        if (var_decl_) delete var_decl_;
        if (record_list_) delete record_list_;
    }

    void print(ostream& os) {
        os << " Node name : RecordList" << endl;
        if (record_list_) {
            record_list_->print(os);
        }
        assert(var_decl_);
        var_decl_->print(os);
    }
    void pcodegen(ostream& os) {

        if (record_list_) {
            record_list_->pcodegen(os);
        }
        assert(var_decl_);
        var_decl_->pcodegen(os);
    }
    virtual Object* clone() const { return new RecordList(*this); }

private:
    Object* var_decl_;
    Object* record_list_;
};

class Type : public Object {
};

class SimpleType : public Type {
public:
    SimpleType(const char* name) {
        name_ = new string(name);
    }

    virtual ~SimpleType() {
        if (name_)delete name_;
    }

    SimpleType(const SimpleType& s) {
        name_ = new string(*s.name_);
    }

    void print(ostream& os) {
        os << " Node name : SimpleType" << endl;
        os << "Type is : " << (*name_) << endl;
    }
    void pcodegen(ostream& os) {
        //*name is the name of the type
        if (arrayf != 1) {
            SymTab.insert(varNm, StackAdd++); // maybe i need to reduce all these line to one line
            SymTab.updateType(varNm, *name_);
            SymTab.updateSize(varNm, 1);
            SymTab.updateparent(varNm, "");
            SymTab.updateoffset(varNm, -1);
            /////////////////////new for HW3
            Parameters_size++;
            SymTab.updatefunction(varNm,CurrFunction);
            SymTab.updateWayOfPassing(varNm,WayOfPassing);
        }
        if (arrayf == 1) { // this means that we are declaring an array of type simple type
            arrayf = 0;
            //ArraySz will be the same because simple type equals 1
            SymTab.updateSize(varNm, ArraySz);
            Parameters_size+= ArraySz;
            SymTab.updatefunction(varNm,CurrFunction);
            SymTab.updateWayOfPassing(varNm,WayOfPassing);
            SymTab.updateType(varNm,*name_);
            Variable* vr = SymTab.returnVar(varNm);
            if (vr != NULL) {
                //os << "suiiiiiiiiiiiiiiiiiiiiiii"<< varNm << endl;
                SymTab.updateIxa(varNm);
                SymTab.updateSubPart(varNm);
                StackAdd = StackAdd + ArraySz;
            }
        }
    }
    virtual Object* clone() const { return new SimpleType(*this); }

private:
    string* name_;
};

class IdeType : public Type {
public:
    IdeType(const char* name) {
        name_ = new string(name);
    }

    virtual ~IdeType() {
        if (name_) delete name_;
    }

    IdeType(const IdeType& s) {
        name_ = new string(*s.name_);
    }

    void print(ostream& os) {
        os << " Node name : IdeType" << endl;
        os << " Name of IdeType :: " << *name_ << endl;
    }
    void pcodegen(ostream& os) {
        if(SymTab.find(varNm)==-1){
            SymTab.insert(varNm,StackAdd);
            if(Functions_List.isthere(*name_)== -1) {
                SymTab.updateSize(varNm, SymTab.retSize(*name_));
                Parameters_size += SymTab.retSize((*name_));
                SymTab.updatefunction(varNm, CurrFunction);
                SymTab.updateWayOfPassing(varNm, WayOfPassing);
                SymTab.updateType(varNm,*name_);
                StackAdd = StackAdd + SymTab.retSize(*name_);
            }
            else{ // we want to declae a new variable of type function
                //update ll the fields with the same field of the type function
                //we basicly inserted the function to both the SymTab and Functions_List
                Functions_List.insert(varNm);
                Functions_List.updateFparent(varNm,Functions_List.returnFparent(*name_));
                Functions_List.updateFPsize(varNm,Functions_List.retFPsize(*name_));
                Functions_List.updateFtype(varNm,Functions_List.retFtype(*name_));
                Functions_List.updateparnumber(varNm,Functions_List.returnparameter_number(*name_));
                Functions_List.update_Parameters_only_size(varNm,Functions_List.ret_Parameters_Size_only(*name_));
                SymTab.updateSize(varNm, 2); //because we pass the function descriptor (size 2)
                SymTab.updateType(varNm,*name_);
                Parameters_size += 2;
                SymTab.updatefunction(varNm, CurrFunction);
                SymTab.updateWayOfPassing(varNm, WayOfPassing);//i dont think the this is relevant its a function type
                StackAdd = StackAdd + 2;
                return;
            }
        }
            if (arrayf == 0) {
                if (Add_no_need_to_print == 1 && recref == 0) {//this means that we are in a pointer
                    SymTab.updateparent(varNm, "");
                    SymTab.updateoffset(varNm, -1);
                    SymTab.updateSize(varNm, 1);
                    //Parameters_size++;
                    SymTab.updatefunction(varNm,CurrFunction);
                    SymTab.updateWayOfPassing(varNm,WayOfPassing);
                    SymTab.updateType(varNm, "AddressType");
                    SymTab.updatePointedAt(varNm, *name_);
                }
                if (Add_no_need_to_print == 0 && recref == 0 && newst == 0 && recFlag == 0) {
                        if (Addval == 0 ) {
                            if (Functions_List.find(*name_) == 1 &&( CurrFunction != *name_ || passing_parameters == 1)) {
                                //this means that we are in a function calling another function ( pasing parameters )
                                string realorfake = Functions_List.ret_fake_or_real(*name_);
                                if(realorfake == "real") {
                                    os << "ldc " << *name_ << endl;
                                    os << "lda " << Functions_List.calc_MST(CurrFunction, *name_) << " "
                                       << "0"
                                       << endl;
                                }
                                else {
                                    os << "lda " << SymTab.Calc_Print_LDA(CurrFunction, *name_) << " "
                                       << SymTab.find(*name_)
                                       << endl;
                                    os<<"movs 2"<<endl;
                                }
                            } else if(expression_par_falg != 1){
                                os << "lda " << SymTab.Calc_Print_LDA(CurrFunction, *name_) << " "
                                   << SymTab.find(*name_)
                                   << endl;
                                if (MST_counter > -1) {
                                    if(Functions_List.find(SymTab.retType(calFunc)) != -1){
                                        string of_type_func = SymTab.retType(calFunc);
                                        if(SymTab.RetWayOfPassingByindex(of_type_func, MST_counter) != "byref" && passing_parameters == 1){
                                            os<<"ind"<<endl;
                                        }
                                    }
                                    else if(SymTab.RetWayOfPassingByindex(calFunc, MST_counter) != "byref" && passing_parameters ==1){
                                            if(SymTab.retSize(*name_) == 1 && recEntry != 1 ) {
                                                os << "ind" << endl;
                                            }
                                            else if(recEntry != 1){
                                                os<<"movs "<< SymTab.retSize(*name_)<<endl;
                                            }
                                    }
                                    MST_counter++;
                                }
                            }
                        }
                        else if (Addval == 1) {
                            if (writeST == 1) {
                                os << "lda " << SymTab.Calc_Print_LDA(CurrFunction, *name_) << " "
                                   << SymTab.find(*name_)
                                   << endl;
                                os<<"ind"<<endl;
                            } else {
                                BackFromRightSonConst = 1;
                                os << "lda " << SymTab.Calc_Print_LDA(CurrFunction, *name_) << " "
                                   << SymTab.find(*name_)
                                   << endl;
                                if (MST_counter > -1) {
                                    if (SymTab.RetWayOfPassingByindex(calFunc, MST_counter) == "byref") {
                                        os << "ind" << endl;
                                    }
                                    MST_counter--;
                                }
                                if (arrayref_retname != 1 && recEntry != 1) {
                                    if(passing_parameters == 1 && SymTab.retSize(*name_) > 1){
                                        os<<"movs "<< SymTab.retSize(*name_) << endl;
                                    }
                                    else {
                                        os << "ind" << endl;
                                    }
                                }
                            }

                        }
                        if (SymTab.retWayOfPs(*name_) == "byref") {
                            os << "ind" << endl;
                        }
                }
                if (recref == 1) {
                    os << "inc " << SymTab.retoffset(*name_) << endl;
                    record_fielnd = *name_;
                    string tpe = SymTab.retType(*name_);
                    if((assignflagForRec == 1 ||writeST == 1) && ( tpe == "Integer" ||tpe== "Boolean" || tpe == "Real" )){
                        os << "ind" << endl;
                    }
                }
                if (newst == 1 && prFirstAdd == 0) {
                    os << "lda " <<SymTab.Calc_Print_LDA(CurrFunction,*name_)<<" "<<SymTab.find(*name_) << endl;
                    lastVar = (*name_);
                }
                if (newst == 1 && prFirstAdd == 1) {
                    os << "lda " <<SymTab.Calc_Print_LDA(CurrFunction,*name_)<<" "<<SymTab.find(*name_) << endl;
                    lastVar = (*name_);
                    prFirstAdd++;
                }
                if (newst == 1 && prFirstAdd > 1) {
                    lastVar = (*name_);
                }
                Add_no_need_to_print = 0;

            }
            if (arrayf == 1) {
                if(recFlag == 1){
                    SymTab.updateparent(varNm,*name_);
                }
                arrayf = 0;
                int SizeOfType = SymTab.retSize(*name_);
                SymTab.updateSize(varNm, SizeOfType * ArraySz);
                Parameters_size+= SizeOfType*ArraySz;
                SymTab.updatefunction(varNm,CurrFunction);
                SymTab.updateWayOfPassing(varNm,WayOfPassing);
                SymTab.updateType(varNm, *name_);
                SymTab.updateIxa(varNm);
                SymTab.updateSubPart(varNm);
                StackAdd = StackAdd + (SymTab.retSize(varNm));

            }
            if (arrayref_retname == 1) {
                Variable* tempvar = SymTab.returnVar(*name_);
                if(tempvar->Dimentions != NULL ) {
                    arrayNm = *name_;
                    Dimsof = *name_;
                    Variable *arr = SymTab.returnVar(*name_);
                    DimsPtr = arr->Dimentions;
                }

            }
    }
    virtual Object* clone() const { return new IdeType(*this); }

private:
    string* name_;
};

class ArrayType : public Type {
public:
    ArrayType(int l, int u, Object* type) : low_(l), up_(u), type_(type) { assert(type_); }

    ArrayType(const ArrayType& a) : low_(a.low_), up_(a.up_) {
        type_ = a.type_->clone();
    }

    virtual ~ArrayType() {
        if (type_) delete type_;
    }

    void print(ostream& os) {
        os << " Node name : ArrayType: low bound is: " << low_ << ", up bound is: " << up_ << endl;
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(type_);
        if (SymTab.find(varNm) == -1) {
            SymTab.insert(varNm, StackAdd);
        }
        Variable* Vr = SymTab.returnVar(varNm);
        if (Vr == NULL) {
            os << "we fucked up" << endl;
            return;
        }
        Vr->AddDims(up_, low_);
        arrayf = 1; //falg to know that we are in an array
        prevdim = (up_ - low_ + 1);
        if (ArraySz == 0) {
            ArraySz = (up_ - low_ + 1);
        }
        else {
            ArraySz = ArraySz*(up_ - low_ + 1);
        }
        type_->pcodegen(os);

    }
    virtual Object* clone() const { return new ArrayType(*this); }

private:
    Object* type_;
    int low_, up_;
};

class RecordType : public Type {
public:
    RecordType(Object* record_list) : record_list_(record_list) { assert(record_list_); }

    RecordType(const RecordType& y) {
        record_list_ = y.record_list_->clone();
    }

    virtual ~RecordType() {
        if (record_list_) delete record_list_;
    }

    void print(ostream& os) {
        os << " Node name : RecordType" << endl;
        assert(record_list_);
        record_list_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(record_list_);
        SymTab.insert(varNm, StackAdd++);
        StackAdd--;
        SymTab.updateType(varNm, "RecordType");
        recFlag = 1;
        parentNm = varNm;
        ofst = 0;
        int RecSize = 0;
        sz = RecSize;
        //here we go the the fields in the record
        record_list_->pcodegen(os);
        recFlag = 0;
        SymTab.updateSize(parentNm, sz);
        //Parameters_size+=sz;
        SymTab.updatefunction(parentNm,CurrFunction);
        SymTab.updateWayOfPassing(parentNm,WayOfPassing);
    }
    virtual Object* clone() const { return new RecordType(*this); }

private:
    Object* record_list_;
};


class AddressType : public Type {
public:
    AddressType(Object* type) : type_(type) { assert(type_); }

    AddressType(const AddressType& t) {
        type_ = t.type_->clone();
    }

    virtual ~AddressType() {
        if (type_) delete type_;
    }

    void print(ostream& os) {
        os << " Node name : AddressType" << endl;
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(type_);
        SymTab.insert(varNm, StackAdd++);
        SymTab.updateparent(varNm, "");
        SymTab.updateoffset(varNm, -1);
        SymTab.updateSize(varNm, 1);
        Parameters_size++;
        SymTab.updatefunction(varNm,CurrFunction);
        SymTab.updateWayOfPassing(varNm,WayOfPassing);
        SymTab.updateType(varNm, "AddressType");
        Add_no_need_to_print = 1;
        type_->pcodegen(os);
        Add_no_need_to_print = 0;
    }
    virtual Object* clone() const { return new AddressType(*this); }

private:
    Object* type_;
};


class Declaration : public Object {
};

class VariableDeclaration : public Declaration {
public:
    VariableDeclaration(Object* type, const char* str) : type_(type) {
        assert(type_);
        name_ = new string(str);
    }

    VariableDeclaration(const VariableDeclaration& p) {
        type_ = p.type_->clone();
        name_ = new string(*p.name_);
    }

    virtual ~VariableDeclaration() {
        if (type_) delete type_;
        delete name_;
    }

    void print(ostream& os) {
        os << " Node name : VariableDeclaration. Var name is: " << *name_ << endl;
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {

        assert(type_);
        varNm = *name_;
        ArraySz = 0;
        type_->pcodegen(os);
        //we are  in a record
        if (recFlag == 1) {
            string str = SymTab.retType(varNm);
            if(str == "Integer" || str == "Real" || str == "Boolean" || "AddressType") {
                SymTab.updateoffset(*name_, ofst);
                ofst = ofst + SymTab.retSize(*name_);
                SymTab.updateparent(*name_, parentNm);
                sz = sz + SymTab.retSize(*name_);
            }
            else{
                SymTab.updateSize(varNm,SymTab.retSize(str));
                Parameters_size+=SymTab.retSize(str) ;
                SymTab.updatefunction(varNm,CurrFunction);
                SymTab.updateWayOfPassing(varNm,WayOfPassing);
                int recsize = SymTab.retSize(varNm);
                SymTab.updateoffset(varNm, ofst);
                ofst = ofst + recsize;
                SymTab.updateparent(varNm, parentNm);
                sz = sz + SymTab.retSize(*name_);
                StackAdd = StackAdd + recsize;
            }
        }
    }
    virtual Object* clone() const { return new VariableDeclaration(*this); }

private:
    Object* type_;
    string* name_;
};

class Parameter : public Object {
public:
    Parameter(Object* type, const char* name) : type_(type) {
        assert(type_);
        name_ = new string(name);
    }

    Parameter(const Parameter& p) {
        type_ = p.type_->clone();
        name_ = new string(*p.name_);
    }

    virtual ~Parameter() {
        if (type_) delete type_;
        delete name_;
    }

    void print(ostream& os) {
        printWayOfPassing(os);
        os << "Parameter name :" << *name_ << endl;
        assert(type_);
        type_->print(os);
    }
    void pcodegen(ostream& os) {
        printWayOfPassing(os);
        assert(type_);
        par_counter++;
        varNm = *name_;
        type_->pcodegen(os);
    }
protected:
    virtual void printWayOfPassing(ostream& os) const = 0;

private:
    Object* type_;
    string* name_;
};

class ByReferenceParameter : public Parameter {
public:
    ByReferenceParameter(Object* type, const char* name) : Parameter(type, name) {}
    virtual Object* clone() const { return new ByReferenceParameter(*this); }
protected:
    void printWayOfPassing(ostream& os) const {
        WayOfPassing = "byref";
        //os << " Node name : ByReferenceParameter "<<endl;
    }
};

class ByValueParameter : public Parameter {
public:
    ByValueParameter(Object* type, const char* name) : Parameter(type, name) {}
    virtual Object* clone() const { return new ByValueParameter(*this); }
protected:
    void printWayOfPassing(ostream& os) const {
        WayOfPassing = "byvalue";
        //os << " Node name : ByValueParameter "<<endl;
    }
};

class ParameterList : public Object {
public:
    ParameterList(Object* formal) : formal_(formal), formal_list_(NULL) { assert(formal_); }
    ParameterList(Object* formal, Object* formal_list) : formal_(formal), formal_list_(formal_list) { assert(formal_ && formal_list_); }

    ParameterList(const ParameterList& pl) {
        formal_ = pl.formal_->clone();
        formal_list_ = pl.formal_list_->clone();
    }

    virtual ~ParameterList() {
        if (formal_) delete formal_;
        if (formal_list_) delete formal_list_;
    }

    void print(ostream& os) {
        os << " Node name : ParameterList" << endl;
        assert(formal_);
        formal_->print(os);
        if (formal_list_) {
            formal_list_->print(os);
        }
    }
    void pcodegen(ostream& os) {
        assert(formal_);
        formal_->pcodegen(os);
        if (formal_list_) {
            formal_list_->pcodegen(os);
        }
    }
    virtual Object* clone() const { return new ParameterList(*this); }

private:
    Object* formal_;
    Object* formal_list_;
};

class FunctionDeclaration : public Declaration {
public:
    FunctionDeclaration(Object* type, Object* block, const char* name) : type_(type), block_(block), formal_list_(NULL) {
        assert(type_ && block_);
        name_ = new string(name);
    }

    FunctionDeclaration(Object* type, Object* formal_list, Object* block, const char* name) : type_(type), formal_list_(formal_list), block_(block) {
        assert(type_ && formal_list_ && block_);
        name_ = new string(name);
    }

    virtual ~FunctionDeclaration() {
        if (type_) delete type_;
        if (block_) delete block_;
        if (formal_list_) delete formal_list_;
        if (name_) delete name_;
    }

    FunctionDeclaration(const FunctionDeclaration& fd) {
        type_ = fd.type_->clone();
        block_ = fd.block_->clone();
        formal_list_ = fd.formal_list_->clone();
        name_ = new string(*fd.name_);
    }

    void print(ostream& os) {
        os << " Node name : FunctionDeclaration. Func name is: " << *name_ << endl;
        assert(type_ && block_);

        type_->print(os);
        if (formal_list_) {
            formal_list_->print(os);
        }
        block_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(type_ && block_);
        if(Functions_List.retFPsize(CurrFunction) == -1){
            Functions_List.updateFPsize(CurrFunction,Parameters_size+5);
            /////////////////printing labesl
            os<<CurrFunction<<":"<<endl;
            os<<"ssp "<<Functions_List.retFPsize(CurrFunction)<<endl;
            os<<"sep 50"<<endl;
            os<<"ujp "<<CurrFunction<<"_begin"<<endl;
        }
        //os<<"check whether it enters the function declaration"<<endl;
        Declaration_begin_flag = 0;
        int StackAddBackUp = StackAdd;
        string CurrFunctionBackUp = CurrFunction;
        string CurrParentBackUP = PrntFunction;
        Functions_List.insert(*name_);
        Functions_List.update_fake_or_real(*name_,"real");
        Functions_List.updateFtype(*name_,"func");
        Functions_List.updateFparent(*name_,PrntFunction);
        CurrFunction = *name_;
        PrntFunction = *name_;
        int prevSA = StackAdd;
        StackAdd = 0;
        varNm = *name_;
        type_->pcodegen(os);
        Parameters_size = 0;
        StackAdd = prevSA;
        StackAdd = 5;
        par_counter = 0;
        if (formal_list_) {
            expression_par_falg = 1;
            formal_list_->pcodegen(os);
            expression_par_falg = 0;
        }
        Functions_List.update_Parameters_only_size(*name_,Parameters_size);
        Functions_List.updateparnumber(*name_,par_counter);
        block_->pcodegen(os);
        os<<"retf"<<endl;
        CurrFunction = CurrFunctionBackUp;
        PrntFunction = CurrParentBackUP;
        StackAdd = StackAddBackUp;
        Declaration_begin_flag = 0;
    }
    virtual Object* clone() const { return new FunctionDeclaration(*this); }

private:
    Object* type_;
    Object* block_;
    Object* formal_list_;
    string* name_;
};

class ProcedureDeclaration : public Declaration {
public:
    ProcedureDeclaration(Object* block, const char* name) : formal_list_(NULL), block_(block) {
        assert(block_);
        name_ = new string(name);
    }

    ProcedureDeclaration(Object* formal_list, Object* block, const char* name) : formal_list_(formal_list), block_(block) {
        assert(formal_list_ && block_);
        name_ = new string(name);
    }

    virtual ~ProcedureDeclaration() {
        if (block_) delete block_;
        if (formal_list_) delete formal_list_;
        if (name_) delete name_;
    }

    ProcedureDeclaration(const ProcedureDeclaration& pd) {
        block_ = pd.block_->clone();
        formal_list_ = pd.formal_list_->clone();
        name_ = new string(*pd.name_);
    }

    void print(ostream& os) {
        os << " Node name : ProcedureDeclaration. Proc name is: " << *name_ << endl;
        assert(block_);
        if (formal_list_) {
            formal_list_->print(os);
        }
        block_->print(os);
    }
    void pcodegen(ostream& os) {
        assert(block_);
        //before entering the prc or func declaration know we have collected all the functions vars and parameters
        if(Functions_List.retFPsize(CurrFunction) == -1){
            Functions_List.updateFPsize(CurrFunction,Parameters_size+5);
            /////////////////printing labesl
            os<<CurrFunction<<":"<<endl;
            os<<"ssp "<<Functions_List.retFPsize(CurrFunction)<<endl;
            os<<"sep 50"<<endl;
            os<<"ujp "<<CurrFunction<<"_begin"<<endl;
        }
        Declaration_begin_flag = 0;
        int StackAddBackUp = StackAdd;
        StackAdd = 5;
        string CurrFunctionBackUp = CurrFunction;
        string CurrParentBackUP = PrntFunction;
        Functions_List.insert(*name_);
        Functions_List.update_fake_or_real(*name_,"real");
        Functions_List.updateFtype(*name_,"proc");
        Functions_List.updateFparent(*name_,PrntFunction);
        Parameters_size = 0;
        CurrFunction = *name_;
        PrntFunction = *name_;
        par_counter = 0;
        if (formal_list_) {
            expression_par_falg = 1;
            formal_list_->pcodegen(os);
            expression_par_falg = 0;
        }
        Functions_List.update_Parameters_only_size(*name_,Parameters_size);
        Functions_List.updateparnumber(*name_,par_counter);
        block_->pcodegen(os);
        os<<"retp"<<endl;
        CurrFunction = CurrFunctionBackUp;
        PrntFunction = CurrParentBackUP;
        StackAdd = StackAddBackUp;
        Declaration_begin_flag = 0;
    }
    virtual Object* clone() const { return new ProcedureDeclaration(*this); }

private:
    Object* block_;
    Object* formal_list_;
    string* name_;
};

class DeclarationList : public Object {
public:
    DeclarationList(Object* decl) : decl_(decl), decl_list_(NULL) { assert(decl_); }
    DeclarationList(Object* decl_list, Object* decl) : decl_list_(decl_list), decl_(decl) { assert(decl_list_ && decl); }

    DeclarationList(const DeclarationList& dl) {
        decl_ = dl.decl_->clone();
        decl_list_ = dl.decl_list_->clone();
    }

    virtual ~DeclarationList() {
        if (decl_) delete decl_;
        if (decl_list_) delete decl_list_;
    }

    void print(ostream& os) {
        os << " Node name : DeclarationList" << endl;
        if (decl_list_) {
            decl_list_->print(os);
        }
        assert(decl_);
        decl_->print(os);
    }
    void pcodegen(ostream& os) {
        if (decl_list_) {
            decl_list_->pcodegen(os);
        }
        assert(decl_);
        decl_->pcodegen(os);
    }
    virtual Object* clone() const { return new DeclarationList(*this); }

private:
    Object* decl_;
    Object* decl_list_;
};

class Block : public Object {
public:
    Block(Object* stat_seq) : stat_seq_(stat_seq), decl_list_(NULL) { assert(stat_seq_); }
    Block(Object* decl_list, Object* stat_seq) : decl_list_(decl_list), stat_seq_(stat_seq) { assert(decl_list_ && stat_seq_); }

    Block(const Block& b) {
        decl_list_ = b.decl_list_->clone();
        stat_seq_ = b.stat_seq_->clone();
    }

    virtual ~Block() {
        if (stat_seq_) delete stat_seq_;
        if (decl_list_) delete decl_list_;
    }

    void print(ostream& os) {
        os << " Node name : Begin" << endl;
        if (decl_list_) {
            decl_list_->print(os);
        }
        assert(stat_seq_);
        stat_seq_->print(os);
    }
    void pcodegen(ostream& os) {
        if (decl_list_) {
            decl_list_->pcodegen(os);
        }
        assert(stat_seq_);
        stat_seq_->pcodegen(os);
    }

    virtual Object* clone() const { return new Block(*this); }

private:
    Object* decl_list_;
    Object* stat_seq_;
};

class Program : public Object {
public:
    Program(Object* block, const char* str) : block_(NULL) {
        block_ = dynamic_cast<Block*>(block);
        assert(block_);
        name_ = new string(str);
    }

    Program(const Program& prog) {
        block_ = dynamic_cast<Block*>(prog.block_->clone());
        assert(block_);
        name_ = new string(*prog.name_);
    }

    virtual ~Program() {
        if (block_) delete block_;
        delete name_;
    }

    void print(ostream& os) {
        os << " Node name : Root/Program. Program name is: " << *name_ << endl;
        assert(block_);
        block_->print(os);
    }
    void pcodegen(ostream& os) {
        Functions_List.insert(*name_);
        Functions_List.updateFtype(*name_,"Main Program") ;
        CurrFunction = *name_;
        PrntFunction = *name_;
        assert(block_);
        block_->pcodegen(os);
        os<<"stp"<<endl;
    }
    virtual Object* clone() const { return new Program(*this); }

private:
    Block* block_;
    string* name_;
};

#endif //AST_H