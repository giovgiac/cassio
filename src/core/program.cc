/**
 * @file program.cc
 * @brief
 *
 * ...
 *
 */

#include <core/program.h>
#include <analyzer/semantic_analyzer.h>

namespace cassio {

std::unique_ptr<Program> Program::Construct(std::list<Token> &tokens) {
  std::unique_ptr<Program> result = std::make_unique<Program>();

  if (tokens.front().GetType() != TokenType::DATA) throw std::runtime_error("Syntax Error");
  tokens.pop_front();
  result->declaration_= std::move(Declaration::Construct(tokens));

  if (tokens.front().GetType() != TokenType::CODE) throw std::runtime_error("Syntax Error");
  tokens.pop_front();
  result->function_ = std::move(Function::Construct(tokens));

  return result;
}

std::string Program::Generate() {
  std::ostringstream oss;

  // Add Headers
  oss << "format ELF64 executable 3\n"
         "entry cassio\n\n";
  oss << "; Macro Section:\n"
         "; ======================================================================\n";
  oss << "macro Elf32_Sym name,value,size,bind,type,other,shndx\n"
         "{\n"
         " dd name+0\n"
         " dd value+0\n"
         " dd size+0\n"
         " db (bind+0) shl 4 + (type+0)\n"
         " db other+0\n"
         " dw shndx+0\n"
         "}\n"
         "\n"
         "virtual at 0\n"
         " Elf32_Sym\n"
         " sizeof.Elf32_Sym = $\n"
         "end virtual\n"
         "\n"
         "macro Elf32_Rel offset,symbol,type\n"
         "{\n"
         "  dd offset+0\n"
         "  dd (symbol+0) shl 8 + (type+0)\n"
         "}\n"
         "\n"
         "virtual at 0\n"
         " Elf32_Rel\n"
         " sizeof.Elf32_Rel = $\n"
         "end virtual\n"
         "\n"
         "macro Elf32_Rela offset,symbol,type,addend\n"
         "{\n"
         "  dd offset+0\n"
         "  dd (symbol+0) shl 8 + (type+0)\n"
         "  dd addend+0\n"
         "}\n"
         "\n"
         "virtual at 0\n"
         " Elf32_Rela\n"
         " sizeof.Elf32_Rela = $\n"
         "end virtual\n"
         "\n"
         "macro Elf64_Sym name,value,size,bind,type,other,shndx\n"
         "{\n"
         " dd name+0\n"
         " db (bind+0) shl 4 + (type+0)\n"
         " db other+0\n"
         " dw shndx+0\n"
         " dq value+0\n"
         " dq size+0\n"
         "}\n"
         "\n"
         "virtual at 0\n"
         " Elf64_Sym\n"
         " sizeof.Elf64_Sym = $\n"
         "end virtual\n"
         "\n"
         "macro Elf64_Rel offset,symbol,type\n"
         "{\n"
         "  dq offset+0\n"
         "  dq (symbol+0) shl 32 + (type+0)\n"
         "}\n"
         "\n"
         "virtual at 0\n"
         " Elf64_Rel\n"
         " sizeof.Elf64_Rel = $\n"
         "end virtual\n"
         "\n"
         "macro Elf64_Rela offset,symbol,type,addend\n"
         "{\n"
         "  dq offset+0\n"
         "  dq (symbol+0) shl 32 + (type+0)\n"
         "  dq addend+0\n"
         "}\n"
         "\n"
         "virtual at 0\n"
         " Elf64_Rela\n"
         " sizeof.Elf64_Rela = $\n"
         "end virtual\n"
         "\n"
         "DT_NULL    = 0\n"
         "DT_NEEDED  = 1\n"
         "DT_HASH    = 4\n"
         "DT_STRTAB  = 5\n"
         "DT_SYMTAB  = 6\n"
         "DT_RELA    = 7\n"
         "DT_RELASZ  = 8\n"
         "DT_RELAENT = 9\n"
         "DT_STRSZ   = 10\n"
         "DT_SYMENT  = 11\n"
         "DT_REL\t   = 17\n"
         "DT_RELSZ   = 18\n"
         "DT_RELENT  = 19\n"
         "\n"
         "STB_LOCAL  = 0\n"
         "STB_GLOBAL = 1\n"
         "STB_WEAK   = 2\n"
         "\n"
         "STT_NOTYPE  = 0\n"
         "STT_OBJECT  = 1\n"
         "STT_FUNC    = 2\n"
         "STT_SECTION = 3\n"
         "STT_FILE    = 4\n"
         "\n"
         "R_386_NONE     = 0\n"
         "R_386_32       = 1\n"
         "R_386_PC32     = 2\n"
         "R_386_GOT32    = 3\n"
         "R_386_PLT32    = 4\n"
         "R_386_COPY     = 5\n"
         "R_386_GLOB_DAT = 6\n"
         "R_386_JMP_SLOT = 7\n"
         "R_386_RELATIVE = 8\n"
         "R_386_GOTOFF   = 9\n"
         "R_386_GOTPC    = 10\n"
         "\n"
         "R_X86_64_NONE\t   = 0\n"
         "R_X86_64_64\t   = 1\n"
         "R_X86_64_PC32\t   = 2\n"
         "R_X86_64_GOT32\t   = 3\n"
         "R_X86_64_PLT32\t   = 4\n"
         "R_X86_64_COPY\t   = 5\n"
         "R_X86_64_GLOB_DAT  = 6\n"
         "R_X86_64_JUMP_SLOT = 7\n"
         "R_X86_64_RELATIVE  = 8\n"
         "R_X86_64_GOTPCREL  = 9\n"
         "R_X86_64_32\t   = 10\n"
         "R_X86_64_32S\t   = 11\n"
         "R_X86_64_16\t   = 12\n"
         "R_X86_64_PC16\t   = 13\n"
         "R_X86_64_8\t   = 14\n"
         "R_X86_64_PC8\t   = 15\n"
         "R_X86_64_DPTMOD64  = 16\n"
         "R_X86_64_DTPOFF64  = 17\n"
         "R_X86_64_TPOFF64   = 18\n"
         "R_X86_64_TLSGD\t   = 19\n"
         "R_X86_64_TLSLD\t   = 20\n"
         "R_X86_64_DTPOFF32  = 21\n"
         "R_X86_64_GOTTPOFF  = 22\n"
         "R_X86_64_TPOFF32   = 23\n"
         "R_X86_64_PC64\t   = 24\n"
         "R_X86_64_GOTOFF64  = 25\n"
         "R_X86_64_GOTPC32   = 26\n"
         "\n"
         "macro interpreter [library]\n"
         "{\n"
         " segment interpreter readable\n"
         " db library,0\n"
         "}\n"
         "\n"
         "macro needed [library]\n"
         "{\n"
         " local str\n"
         " match needed,needed@dynamic \\{ define needed@dynamic needed,str:library \\}\n"
         " match ,needed@dynamic \\{ define needed@dynamic str:library \\}\n"
         "}\n"
         "define needed@dynamic\n"
         "\n"
         "macro import [name]\n"
         "{\n"
         " common\n"
         "  local strtab,strsz,symtab,rel,relsz,hash\n"
         "  segment dynamic readable\n"
         "  match needed,needed@dynamic\n"
         "  \\{ irp item,needed \\\\{ match str:library,item \\\\\\{ dq DT_NEEDED,str-strtab \\\\\\} \\\\} \\}\n"
         "  dq DT_STRTAB,strtab\n"
         "  dq DT_STRSZ,strsz\n"
         "  dq DT_SYMTAB,symtab\n"
         "  dq DT_SYMENT,sizeof.Elf64_Sym\n"
         "  dq DT_RELA,rela\n"
         "  dq DT_RELASZ,relasz\n"
         "  dq DT_RELAENT,sizeof.Elf64_Rela\n"
         "  dq DT_HASH,hash\n"
         "  dq DT_NULL,0\n"
         "  segment readable writeable\n"
         "  symtab: Elf64_Sym\n"
         " forward\n"
         "  local fstr\n"
         "  Elf64_Sym fstr-strtab,0,0,STB_GLOBAL,STT_FUNC,0,0\n"
         " common\n"
         "  rela:\n"
         "  local counter\n"
         "  counter = 1\n"
         " forward\n"
         "   Elf64_Rela name,counter,R_X86_64_64\n"
         "   counter = counter+1\n"
         " common\n"
         "  relasz = $-rela\n"
         "  hash:\n"
         "  dd 1,counter\n"
         "  dd 0\n"
         "  repeat counter\n"
         "   if %=counter\n"
         "    dd 0\n"
         "   else\n"
         "    dd %\n"
         "   end if\n"
         "  end repeat\n"
         "  strtab db 0\n"
         " forward\n"
         "  fstr db `name,0\n"
         " common\n"
         "  match needed,needed@dynamic\n"
         "  \\{ irp item,needed \\\\{ match str:library,item \\\\\\{ str db library,0 \\\\\\} \\\\} \\}\n"
         "  strsz = $-strtab\n"
         " forward\n"
         "  name dq 0\n"
         "}\n\n";

  // Add Struct Code
  oss << "macro struct name\n"
         " { virtual at 0\n"
         "   define @struct\n"
         "   field@struct equ name\n"
         "   match child parent, name \\{ restore field@struct\n"
         "\t\t\t       field@struct equ child,fields@\\#parent \\}\n"
         "   sub@struct equ\n"
         "   struc db [val] \\{ \\common define field@struct .,db,<val> \\}\n"
         "   struc dw [val] \\{ \\common define field@struct .,dw,<val> \\}\n"
         "   struc du [val] \\{ \\common define field@struct .,du,<val> \\}\n"
         "   struc dd [val] \\{ \\common define field@struct .,dd,<val> \\}\n"
         "   struc dp [val] \\{ \\common define field@struct .,dp,<val> \\}\n"
         "   struc dq [val] \\{ \\common define field@struct .,dq,<val> \\}\n"
         "   struc dt [val] \\{ \\common define field@struct .,dt,<val> \\}\n"
         "   struc rb count \\{ define field@struct .,db,count dup (?) \\}\n"
         "   struc rw count \\{ define field@struct .,dw,count dup (?) \\}\n"
         "   struc rd count \\{ define field@struct .,dd,count dup (?) \\}\n"
         "   struc rp count \\{ define field@struct .,dp,count dup (?) \\}\n"
         "   struc rq count \\{ define field@struct .,dq,count dup (?) \\}\n"
         "   struc rt count \\{ define field@struct .,dt,count dup (?) \\}\n"
         "   macro db [val] \\{ \\common \\local anonymous\n"
         "\t\t     define field@struct anonymous,db,<val> \\}\n"
         "   macro dw [val] \\{ \\common \\local anonymous\n"
         "\t\t     define field@struct anonymous,dw,<val> \\}\n"
         "   macro du [val] \\{ \\common \\local anonymous\n"
         "\t\t     define field@struct anonymous,du,<val> \\}\n"
         "   macro dd [val] \\{ \\common \\local anonymous\n"
         "\t\t     define field@struct anonymous,dd,<val> \\}\n"
         "   macro dp [val] \\{ \\common \\local anonymous\n"
         "\t\t     define field@struct anonymous,dp,<val> \\}\n"
         "   macro dq [val] \\{ \\common \\local anonymous\n"
         "\t\t     define field@struct anonymous,dq,<val> \\}\n"
         "   macro dt [val] \\{ \\common \\local anonymous\n"
         "\t\t     define field@struct anonymous,dt,<val> \\}\n"
         "   macro rb count \\{ \\local anonymous\n"
         "\t\t     define field@struct anonymous,db,count dup (?) \\}\n"
         "   macro rw count \\{ \\local anonymous\n"
         "\t\t     define field@struct anonymous,dw,count dup (?) \\}\n"
         "   macro rd count \\{ \\local anonymous\n"
         "\t\t     define field@struct anonymous,dd,count dup (?) \\}\n"
         "   macro rp count \\{ \\local anonymous\n"
         "\t\t     define field@struct anonymous,dp,count dup (?) \\}\n"
         "   macro rq count \\{ \\local anonymous\n"
         "\t\t     define field@struct anonymous,dq,count dup (?) \\}\n"
         "   macro rt count \\{ \\local anonymous\n"
         "\t\t     define field@struct anonymous,dt,count dup (?) \\}\n"
         "   macro union \\{ field@struct equ ,union,<\n"
         "\t\t  sub@struct equ union \\}\n"
         "   macro struct \\{ field@struct equ ,substruct,<\n"
         "\t\t  sub@struct equ substruct \\} }\n"
         "\n"
         "macro ends\n"
         " { match , sub@struct \\{ restruc db,dw,du,dd,dp,dq,dt\n"
         "\t\t\t restruc rb,rw,rd,rp,rq,rt\n"
         "\t\t\t purge db,dw,du,dd,dp,dq,dt\n"
         "\t\t\t purge rb,rw,rd,rp,rq,rt\n"
         "\t\t\t purge union,struct\n"
         "\t\t\t irpv fields,field@struct \\\\{ restore field@struct\n"
         "\t\t\t\t\t\t      \\\\common define fields@struct fields \\\\}\n"
         "\t\t\t match name tail,fields@struct, \\\\{ if $\n"
         "\t\t\t\t\t\t\t    display 'Error: definition of ',\\\\`name,' contains illegal instructions.',0Dh,0Ah\n"
         "\t\t\t\t\t\t\t    err\n"
         "\t\t\t\t\t\t\t    end if \\\\}\n"
         "\t\t\t match name=,fields,fields@struct \\\\{ restore @struct\n"
         "\t\t\t\t\t\t\t      make@struct name,fields\n"
         "\t\t\t\t\t\t\t      define fields@\\\\#name fields \\\\}\n"
         "\t\t\t end virtual \\}\n"
         "   match any, sub@struct \\{ tmp@struct equ field@struct\n"
         "\t\t\t    restore field@struct\n"
         "\t\t\t    field@struct equ tmp@struct> \\}\n"
         "   restore sub@struct }\n"
         "\n"
         "macro make@struct name,[field,type,def]\n"
         " { common\n"
         "    local define\n"
         "    define equ name\n"
         "   forward\n"
         "    local sub\n"
         "    match , field \\{ make@substruct type,name,sub def\n"
         "\t\t     define equ define,.,sub, \\}\n"
         "    match any, field \\{ define equ define,.#field,type,<def> \\}\n"
         "   common\n"
         "    match fields, define \\{ define@struct fields \\} }\n"
         "\n"
         "macro define@struct name,[field,type,def]\n"
         " { common\n"
         "    virtual\n"
         "    db `name\n"
         "    load initial@struct byte from 0\n"
         "    if initial@struct = '.'\n"
         "    display 'Error: name of structure should not begin with a dot.',0Dh,0Ah\n"
         "    err\n"
         "    end if\n"
         "    end virtual\n"
         "    local list\n"
         "    list equ\n"
         "   forward\n"
         "    if ~ field eq .\n"
         "     name#field type def\n"
         "     sizeof.#name#field = $ - name#field\n"
         "    else\n"
         "     label name#.#type\n"
         "     rb sizeof.#type\n"
         "    end if\n"
         "    local value\n"
         "    match any, list \\{ list equ list, \\}\n"
         "    list equ list <value>\n"
         "   common\n"
         "    sizeof.#name = $\n"
         "    restruc name\n"
         "    match values, list \\{\n"
         "    struc name value \\\\{ \\\\local \\\\..base\n"
         "    match , @struct \\\\\\{ define field@struct .,name,<values> \\\\\\}\n"
         "    match no, @struct \\\\\\{ label \\\\..base\n"
         "   forward\n"
         "     match , value \\\\\\\\{ field type def \\\\\\\\}\n"
         "     match any, value \\\\\\\\{ field type value\n"
         "\t\t\t    if ~ field eq .\n"
         "\t\t\t     rb sizeof.#name#field - ($-field)\n"
         "\t\t\t    end if \\\\\\\\}\n"
         "   common label . at \\\\..base \\\\\\}\n"
         "   \\\\}\n"
         "    macro name value \\\\{\n"
         "    match , @struct \\\\\\{ \\\\\\local anonymous\n"
         "\t\t\t\t  define field@struct anonymous,name,<values> \\\\\\}\n"
         "    match no, @struct \\\\\\{\n"
         "   forward\n"
         "     match , value \\\\\\\\{ type def \\\\\\\\}\n"
         "     match any, value \\\\\\\\{ \\\\\\\\local ..field\n"
         "\t\t\t   ..field = $\n"
         "\t\t\t   type value\n"
         "\t\t\t   if ~ field eq .\n"
         "\t\t\t    rb sizeof.#name#field - ($-..field)\n"
         "\t\t\t   end if \\\\\\\\}\n"
         "   common \\\\\\} \\\\} \\} }\n"
         "\n"
         "macro enable@substruct\n"
         " { macro make@substruct substruct,parent,name,[field,type,def]\n"
         "    \\{ \\common\n"
         "\t\\local define\n"
         "\tdefine equ parent,name\n"
         "       \\forward\n"
         "\t\\local sub\n"
         "\tmatch , field \\\\{ match any, type \\\\\\{ enable@substruct\n"
         "\t\t\t\t\t       make@substruct type,parent,sub def\n"
         "\t\t\t\t\t       purge make@substruct\n"
         "\t\t\t\t\t       define equ define,.,sub, \\\\\\} \\\\}\n"
         "\tmatch any, field \\\\{ define equ define,.\\#field,type,<def> \\\\}\n"
         "       \\common\n"
         "\tmatch fields, define \\\\{ define@\\#substruct fields \\\\} \\} }\n"
         "\n"
         "enable@substruct\n"
         "\n"
         "macro define@union parent,name,[field,type,def]\n"
         " { common\n"
         "    virtual at parent#.#name\n"
         "   forward\n"
         "    if ~ field eq .\n"
         "     virtual at parent#.#name\n"
         "      parent#field type def\n"
         "      sizeof.#parent#field = $ - parent#field\n"
         "     end virtual\n"
         "     if sizeof.#parent#field > $ - parent#.#name\n"
         "      rb sizeof.#parent#field - ($ - parent#.#name)\n"
         "     end if\n"
         "    else\n"
         "     virtual at parent#.#name\n"
         "      label parent#.#type\n"
         "      type def\n"
         "     end virtual\n"
         "     label name#.#type at parent#.#name\n"
         "     if sizeof.#type > $ - parent#.#name\n"
         "      rb sizeof.#type - ($ - parent#.#name)\n"
         "     end if\n"
         "    end if\n"
         "   common\n"
         "    sizeof.#name = $ - parent#.#name\n"
         "    end virtual\n"
         "    struc name [value] \\{ \\common\n"
         "    label .\\#name\n"
         "    last@union equ\n"
         "   forward\n"
         "    match any, last@union \\\\{ virtual at .\\#name\n"
         "\t\t\t       field type def\n"
         "\t\t\t      end virtual \\\\}\n"
         "    match , last@union \\\\{ match , value \\\\\\{ field type def \\\\\\}\n"
         "\t\t\t   match any, value \\\\\\{ field type value \\\\\\} \\\\}\n"
         "    last@union equ field\n"
         "   common rb sizeof.#name - ($ - .\\#name) \\}\n"
         "    macro name [value] \\{ \\common \\local ..anonymous\n"
         "\t\t\t  ..anonymous name value \\} }\n"
         "\n"
         "macro define@substruct parent,name,[field,type,def]\n"
         " { common\n"
         "    virtual at parent#.#name\n"
         "   forward\n"
         "    local value\n"
         "    if ~ field eq .\n"
         "     parent#field type def\n"
         "     sizeof.#parent#field = $ - parent#field\n"
         "    else\n"
         "     label parent#.#type\n"
         "     rb sizeof.#type\n"
         "    end if\n"
         "   common\n"
         "    sizeof.#name = $ - parent#.#name\n"
         "    end virtual\n"
         "    struc name value \\{\n"
         "    label .\\#name\n"
         "   forward\n"
         "     match , value \\\\{ field type def \\\\}\n"
         "     match any, value \\\\{ field type value\n"
         "\t\t\t  if ~ field eq .\n"
         "\t\t\t   rb sizeof.#parent#field - ($-field)\n"
         "\t\t\t  end if \\\\}\n"
         "   common \\}\n"
         "    macro name value \\{ \\local ..anonymous\n"
         "\t\t\t..anonymous name \\} }\n\n";

  // Add Data Section
  oss << "; Data Section:\n"
         "; ======================================================================\n"
         "segment readable writeable\n";
  oss << "\tprint_integer_fmt\t\tdb \"%u\", 10, 13, 0";
  oss << "\n";
  oss << "\tprint_string_fmt\t\tdb \"%s\", 10, 13, 0";
  oss << "\n";
  oss << "\tscanf_integer_fmt\t\tdb \"%u\", 0";
  oss << "\n";
  oss << "\tscanf_string_fmt\t\tdb \"%s\", 0";
  oss << "\n";
  for (auto &e : SemanticAnalyzer::literals_) {
    auto lt = e.second;
    oss << "\tstring" << lt.id_ << "\t\t\t\tdb " << "\"" << lt.string_ << "\", 0";
    oss << "\n";
  }
  oss << "\n";

  // Add BSS Section
  oss << "; BSS Section:\n"
         "; ======================================================================\n"
         "segment readable writeable\n";
  oss << "\tscanf_read\t\tdq ?";
  oss << "\n\n";
  if (declaration_) {
    oss << declaration_->Generate();
    oss << "\n\n";
  }

  // Add Code Section
  oss << "; Code Section:\n"
         "; ======================================================================\n"
         "segment readable executable\n\n";

  if (function_) {
    oss << function_->Generate();
  }

  // Add Library Linking
  oss << "; Library Section:\n"
         "; ===============================================\n"
         "interpreter '/lib64/ld-linux-x86-64.so.2'\n"
         "needed 'libc.so.6'\n"
         "import printf, scanf, exit\n"
         "; ===============================================\n";

  return oss.str();
}

void Program::Semanticate() {
  if (declaration_)
    declaration_->Semanticate();

  if (function_)
    function_->Semanticate();
}

}
