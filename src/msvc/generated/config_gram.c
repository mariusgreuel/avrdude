/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 21 "config_gram.y"


#include "ac_cfg.h"

#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "avrdude.h"
#include "libavrdude.h"
#include "config.h"

#if defined(WIN32NATIVE)
#define strtok_r( _s, _sep, _lasts ) \
    ( *(_lasts) = strtok( (_s), (_sep) ) )
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

int yylex(void);
int yyerror(char * errmsg, ...);
int yywarning(char * errmsg, ...);

static int assign_pin(int pinno, TOKEN * v, int invert);
static int assign_pin_list(int invert);
static int which_opcode(TOKEN * opcode);
static int parse_cmdbits(OPCODE * op);

static int pin_name;

#line 102 "config_gram.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_CONFIG_GRAM_H_INCLUDED
# define YY_YY_CONFIG_GRAM_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    K_READ = 258,
    K_WRITE = 259,
    K_READ_LO = 260,
    K_READ_HI = 261,
    K_WRITE_LO = 262,
    K_WRITE_HI = 263,
    K_LOADPAGE_LO = 264,
    K_LOADPAGE_HI = 265,
    K_LOAD_EXT_ADDR = 266,
    K_WRITEPAGE = 267,
    K_CHIP_ERASE = 268,
    K_PGM_ENABLE = 269,
    K_MEMORY = 270,
    K_PAGE_SIZE = 271,
    K_PAGED = 272,
    K_BAUDRATE = 273,
    K_BS2 = 274,
    K_BUFF = 275,
    K_CHIP_ERASE_DELAY = 276,
    K_CONNTYPE = 277,
    K_DEDICATED = 278,
    K_DEFAULT_BITCLOCK = 279,
    K_DEFAULT_PARALLEL = 280,
    K_DEFAULT_PROGRAMMER = 281,
    K_DEFAULT_SAFEMODE = 282,
    K_DEFAULT_SERIAL = 283,
    K_DESC = 284,
    K_FAMILY_ID = 285,
    K_DEVICECODE = 286,
    K_STK500_DEVCODE = 287,
    K_AVR910_DEVCODE = 288,
    K_EEPROM = 289,
    K_ERRLED = 290,
    K_FLASH = 291,
    K_ID = 292,
    K_IO = 293,
    K_LOADPAGE = 294,
    K_MAX_WRITE_DELAY = 295,
    K_MCU_BASE = 296,
    K_MIN_WRITE_DELAY = 297,
    K_MISO = 298,
    K_MOSI = 299,
    K_NUM_PAGES = 300,
    K_NVM_BASE = 301,
    K_OCD_BASE = 302,
    K_OCDREV = 303,
    K_OFFSET = 304,
    K_PAGEL = 305,
    K_PARALLEL = 306,
    K_PARENT = 307,
    K_PART = 308,
    K_PGMLED = 309,
    K_PROGRAMMER = 310,
    K_PSEUDO = 311,
    K_PWROFF_AFTER_WRITE = 312,
    K_RDYLED = 313,
    K_READBACK_P1 = 314,
    K_READBACK_P2 = 315,
    K_READMEM = 316,
    K_RESET = 317,
    K_RETRY_PULSE = 318,
    K_SERIAL = 319,
    K_SCK = 320,
    K_SIGNATURE = 321,
    K_SIZE = 322,
    K_USB = 323,
    K_USBDEV = 324,
    K_USBSN = 325,
    K_USBPID = 326,
    K_USBPRODUCT = 327,
    K_USBVENDOR = 328,
    K_USBVID = 329,
    K_TYPE = 330,
    K_VCC = 331,
    K_VFYLED = 332,
    K_NO = 333,
    K_YES = 334,
    K_TIMEOUT = 335,
    K_STABDELAY = 336,
    K_CMDEXEDELAY = 337,
    K_HVSPCMDEXEDELAY = 338,
    K_SYNCHLOOPS = 339,
    K_BYTEDELAY = 340,
    K_POLLVALUE = 341,
    K_POLLINDEX = 342,
    K_PREDELAY = 343,
    K_POSTDELAY = 344,
    K_POLLMETHOD = 345,
    K_MODE = 346,
    K_DELAY = 347,
    K_BLOCKSIZE = 348,
    K_READSIZE = 349,
    K_HVENTERSTABDELAY = 350,
    K_PROGMODEDELAY = 351,
    K_LATCHCYCLES = 352,
    K_TOGGLEVTG = 353,
    K_POWEROFFDELAY = 354,
    K_RESETDELAYMS = 355,
    K_RESETDELAYUS = 356,
    K_HVLEAVESTABDELAY = 357,
    K_RESETDELAY = 358,
    K_SYNCHCYCLES = 359,
    K_HVCMDEXEDELAY = 360,
    K_CHIPERASEPULSEWIDTH = 361,
    K_CHIPERASEPOLLTIMEOUT = 362,
    K_CHIPERASETIME = 363,
    K_PROGRAMFUSEPULSEWIDTH = 364,
    K_PROGRAMFUSEPOLLTIMEOUT = 365,
    K_PROGRAMLOCKPULSEWIDTH = 366,
    K_PROGRAMLOCKPOLLTIMEOUT = 367,
    K_PP_CONTROLSTACK = 368,
    K_HVSP_CONTROLSTACK = 369,
    K_ALLOWFULLPAGEBITSTREAM = 370,
    K_ENABLEPAGEPROGRAMMING = 371,
    K_HAS_JTAG = 372,
    K_HAS_DW = 373,
    K_HAS_PDI = 374,
    K_HAS_UPDI = 375,
    K_HAS_TPI = 376,
    K_IDR = 377,
    K_IS_AT90S1200 = 378,
    K_IS_AVR32 = 379,
    K_RAMPZ = 380,
    K_SPMCR = 381,
    K_EECR = 382,
    K_FLASH_INSTR = 383,
    K_EEPROM_INSTR = 384,
    TKN_COMMA = 385,
    TKN_EQUAL = 386,
    TKN_SEMI = 387,
    TKN_TILDE = 388,
    TKN_LEFT_PAREN = 389,
    TKN_RIGHT_PAREN = 390,
    TKN_NUMBER = 391,
    TKN_NUMBER_REAL = 392,
    TKN_STRING = 393
  };
#endif
/* Tokens.  */
#define K_READ 258
#define K_WRITE 259
#define K_READ_LO 260
#define K_READ_HI 261
#define K_WRITE_LO 262
#define K_WRITE_HI 263
#define K_LOADPAGE_LO 264
#define K_LOADPAGE_HI 265
#define K_LOAD_EXT_ADDR 266
#define K_WRITEPAGE 267
#define K_CHIP_ERASE 268
#define K_PGM_ENABLE 269
#define K_MEMORY 270
#define K_PAGE_SIZE 271
#define K_PAGED 272
#define K_BAUDRATE 273
#define K_BS2 274
#define K_BUFF 275
#define K_CHIP_ERASE_DELAY 276
#define K_CONNTYPE 277
#define K_DEDICATED 278
#define K_DEFAULT_BITCLOCK 279
#define K_DEFAULT_PARALLEL 280
#define K_DEFAULT_PROGRAMMER 281
#define K_DEFAULT_SAFEMODE 282
#define K_DEFAULT_SERIAL 283
#define K_DESC 284
#define K_FAMILY_ID 285
#define K_DEVICECODE 286
#define K_STK500_DEVCODE 287
#define K_AVR910_DEVCODE 288
#define K_EEPROM 289
#define K_ERRLED 290
#define K_FLASH 291
#define K_ID 292
#define K_IO 293
#define K_LOADPAGE 294
#define K_MAX_WRITE_DELAY 295
#define K_MCU_BASE 296
#define K_MIN_WRITE_DELAY 297
#define K_MISO 298
#define K_MOSI 299
#define K_NUM_PAGES 300
#define K_NVM_BASE 301
#define K_OCD_BASE 302
#define K_OCDREV 303
#define K_OFFSET 304
#define K_PAGEL 305
#define K_PARALLEL 306
#define K_PARENT 307
#define K_PART 308
#define K_PGMLED 309
#define K_PROGRAMMER 310
#define K_PSEUDO 311
#define K_PWROFF_AFTER_WRITE 312
#define K_RDYLED 313
#define K_READBACK_P1 314
#define K_READBACK_P2 315
#define K_READMEM 316
#define K_RESET 317
#define K_RETRY_PULSE 318
#define K_SERIAL 319
#define K_SCK 320
#define K_SIGNATURE 321
#define K_SIZE 322
#define K_USB 323
#define K_USBDEV 324
#define K_USBSN 325
#define K_USBPID 326
#define K_USBPRODUCT 327
#define K_USBVENDOR 328
#define K_USBVID 329
#define K_TYPE 330
#define K_VCC 331
#define K_VFYLED 332
#define K_NO 333
#define K_YES 334
#define K_TIMEOUT 335
#define K_STABDELAY 336
#define K_CMDEXEDELAY 337
#define K_HVSPCMDEXEDELAY 338
#define K_SYNCHLOOPS 339
#define K_BYTEDELAY 340
#define K_POLLVALUE 341
#define K_POLLINDEX 342
#define K_PREDELAY 343
#define K_POSTDELAY 344
#define K_POLLMETHOD 345
#define K_MODE 346
#define K_DELAY 347
#define K_BLOCKSIZE 348
#define K_READSIZE 349
#define K_HVENTERSTABDELAY 350
#define K_PROGMODEDELAY 351
#define K_LATCHCYCLES 352
#define K_TOGGLEVTG 353
#define K_POWEROFFDELAY 354
#define K_RESETDELAYMS 355
#define K_RESETDELAYUS 356
#define K_HVLEAVESTABDELAY 357
#define K_RESETDELAY 358
#define K_SYNCHCYCLES 359
#define K_HVCMDEXEDELAY 360
#define K_CHIPERASEPULSEWIDTH 361
#define K_CHIPERASEPOLLTIMEOUT 362
#define K_CHIPERASETIME 363
#define K_PROGRAMFUSEPULSEWIDTH 364
#define K_PROGRAMFUSEPOLLTIMEOUT 365
#define K_PROGRAMLOCKPULSEWIDTH 366
#define K_PROGRAMLOCKPOLLTIMEOUT 367
#define K_PP_CONTROLSTACK 368
#define K_HVSP_CONTROLSTACK 369
#define K_ALLOWFULLPAGEBITSTREAM 370
#define K_ENABLEPAGEPROGRAMMING 371
#define K_HAS_JTAG 372
#define K_HAS_DW 373
#define K_HAS_PDI 374
#define K_HAS_UPDI 375
#define K_HAS_TPI 376
#define K_IDR 377
#define K_IS_AT90S1200 378
#define K_IS_AVR32 379
#define K_RAMPZ 380
#define K_SPMCR 381
#define K_EECR 382
#define K_FLASH_INSTR 383
#define K_EEPROM_INSTR 384
#define TKN_COMMA 385
#define TKN_EQUAL 386
#define TKN_SEMI 387
#define TKN_TILDE 388
#define TKN_LEFT_PAREN 389
#define TKN_RIGHT_PAREN 390
#define TKN_NUMBER 391
#define TKN_NUMBER_REAL 392
#define TKN_STRING 393

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CONFIG_GRAM_H_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  22
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   409

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  139
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  45
/* YYNRULES -- Number of rules.  */
#define YYNRULES  185
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  427

#define YYUNDEFTOK  2
#define YYMAXUTOK   393


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   214,   214,   220,   224,   225,   229,   230,   235,   237,
     239,   245,   251,   257,   262,   273,   306,   316,   338,   396,
     406,   429,   430,   435,   436,   440,   441,   445,   468,   470,
     472,   474,   476,   481,   490,   494,   504,   512,   516,   517,
     518,   522,   529,   535,   536,   543,   550,   560,   575,   588,
     590,   594,   596,   600,   602,   606,   608,   613,   615,   619,
     619,   620,   620,   621,   621,   622,   622,   623,   623,   624,
     624,   625,   625,   626,   626,   627,   627,   628,   628,   632,
     633,   634,   635,   636,   637,   638,   639,   640,   641,   642,
     643,   648,   649,   654,   654,   658,   658,   662,   662,   666,
     673,   680,   687,   695,   702,   709,   720,   727,   758,   789,
     819,   849,   855,   861,   867,   877,   883,   889,   895,   901,
     907,   913,   919,   925,   931,   937,   943,   949,   955,   961,
     967,   973,   979,   985,   991,   997,  1003,  1009,  1015,  1021,
    1027,  1033,  1039,  1045,  1055,  1065,  1075,  1085,  1095,  1105,
    1115,  1125,  1135,  1141,  1147,  1153,  1159,  1165,  1171,  1177,
    1183,  1193,  1212,  1236,  1235,  1260,  1287,  1287,  1292,  1293,
    1298,  1304,  1311,  1317,  1323,  1329,  1335,  1341,  1347,  1353,
    1360,  1366,  1372,  1378,  1384,  1391
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "K_READ", "K_WRITE", "K_READ_LO",
  "K_READ_HI", "K_WRITE_LO", "K_WRITE_HI", "K_LOADPAGE_LO",
  "K_LOADPAGE_HI", "K_LOAD_EXT_ADDR", "K_WRITEPAGE", "K_CHIP_ERASE",
  "K_PGM_ENABLE", "K_MEMORY", "K_PAGE_SIZE", "K_PAGED", "K_BAUDRATE",
  "K_BS2", "K_BUFF", "K_CHIP_ERASE_DELAY", "K_CONNTYPE", "K_DEDICATED",
  "K_DEFAULT_BITCLOCK", "K_DEFAULT_PARALLEL", "K_DEFAULT_PROGRAMMER",
  "K_DEFAULT_SAFEMODE", "K_DEFAULT_SERIAL", "K_DESC", "K_FAMILY_ID",
  "K_DEVICECODE", "K_STK500_DEVCODE", "K_AVR910_DEVCODE", "K_EEPROM",
  "K_ERRLED", "K_FLASH", "K_ID", "K_IO", "K_LOADPAGE", "K_MAX_WRITE_DELAY",
  "K_MCU_BASE", "K_MIN_WRITE_DELAY", "K_MISO", "K_MOSI", "K_NUM_PAGES",
  "K_NVM_BASE", "K_OCD_BASE", "K_OCDREV", "K_OFFSET", "K_PAGEL",
  "K_PARALLEL", "K_PARENT", "K_PART", "K_PGMLED", "K_PROGRAMMER",
  "K_PSEUDO", "K_PWROFF_AFTER_WRITE", "K_RDYLED", "K_READBACK_P1",
  "K_READBACK_P2", "K_READMEM", "K_RESET", "K_RETRY_PULSE", "K_SERIAL",
  "K_SCK", "K_SIGNATURE", "K_SIZE", "K_USB", "K_USBDEV", "K_USBSN",
  "K_USBPID", "K_USBPRODUCT", "K_USBVENDOR", "K_USBVID", "K_TYPE", "K_VCC",
  "K_VFYLED", "K_NO", "K_YES", "K_TIMEOUT", "K_STABDELAY", "K_CMDEXEDELAY",
  "K_HVSPCMDEXEDELAY", "K_SYNCHLOOPS", "K_BYTEDELAY", "K_POLLVALUE",
  "K_POLLINDEX", "K_PREDELAY", "K_POSTDELAY", "K_POLLMETHOD", "K_MODE",
  "K_DELAY", "K_BLOCKSIZE", "K_READSIZE", "K_HVENTERSTABDELAY",
  "K_PROGMODEDELAY", "K_LATCHCYCLES", "K_TOGGLEVTG", "K_POWEROFFDELAY",
  "K_RESETDELAYMS", "K_RESETDELAYUS", "K_HVLEAVESTABDELAY", "K_RESETDELAY",
  "K_SYNCHCYCLES", "K_HVCMDEXEDELAY", "K_CHIPERASEPULSEWIDTH",
  "K_CHIPERASEPOLLTIMEOUT", "K_CHIPERASETIME", "K_PROGRAMFUSEPULSEWIDTH",
  "K_PROGRAMFUSEPOLLTIMEOUT", "K_PROGRAMLOCKPULSEWIDTH",
  "K_PROGRAMLOCKPOLLTIMEOUT", "K_PP_CONTROLSTACK", "K_HVSP_CONTROLSTACK",
  "K_ALLOWFULLPAGEBITSTREAM", "K_ENABLEPAGEPROGRAMMING", "K_HAS_JTAG",
  "K_HAS_DW", "K_HAS_PDI", "K_HAS_UPDI", "K_HAS_TPI", "K_IDR",
  "K_IS_AT90S1200", "K_IS_AVR32", "K_RAMPZ", "K_SPMCR", "K_EECR",
  "K_FLASH_INSTR", "K_EEPROM_INSTR", "TKN_COMMA", "TKN_EQUAL", "TKN_SEMI",
  "TKN_TILDE", "TKN_LEFT_PAREN", "TKN_RIGHT_PAREN", "TKN_NUMBER",
  "TKN_NUMBER_REAL", "TKN_STRING", "$accept", "number_real",
  "configuration", "config", "def", "prog_def", "prog_decl", "part_def",
  "part_decl", "string_list", "num_list", "prog_parms", "prog_parm",
  "prog_parm_type", "prog_parm_type_id", "prog_parm_conntype",
  "prog_parm_conntype_id", "prog_parm_usb", "usb_pid_list",
  "pin_number_non_empty", "pin_number", "pin_list_element",
  "pin_list_non_empty", "pin_list", "prog_parm_pins", "$@1", "$@2", "$@3",
  "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "opcode", "part_parms",
  "reset_disposition", "parallel_modes", "retry_lines", "part_parm",
  "$@11", "yesno", "mem_specs", "mem_spec", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393
};
# endif

#define YYPACT_NINF (-264)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -5,   -97,   -96,   -63,   -60,   -59,    22,    23,    76,    -5,
    -264,   -55,   -11,   -54,    77,  -123,   -45,   -44,   -51,   -43,
     -41,   -33,  -264,  -264,  -264,   -52,   -20,   -19,   -18,   -14,
     -12,   -10,    -9,    -2,    -1,     0,     1,     2,     3,     6,
       7,    13,    14,    15,    18,    19,   -11,    -6,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,    -3,    20,    21,    24,    25,
      38,    39,    51,    78,    79,    80,    94,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   120,
     122,   123,   125,   126,   127,   129,   130,   131,   132,   133,
     134,   135,   137,   140,   141,   142,   143,   144,   145,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,    77,   159,  -264,  -264,   160,   161,   162,  -264,  -264,
     163,   164,  -264,  -264,   -16,  -264,     5,    16,  -264,    70,
    -264,  -264,  -264,  -264,  -264,  -264,   167,   168,    17,   169,
     170,   173,     4,  -264,  -264,   166,  -264,  -264,   174,   175,
     176,   177,   180,   181,   182,   183,   184,   186,   187,   188,
     189,   -48,   -13,   -50,   -51,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   221,   -51,   -51,   -51,
     -51,   -51,   -51,   -51,   222,   -51,   -51,   223,   224,   225,
     221,   221,    70,   230,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,   -87,  -264,  -264,  -264,  -264,  -264,   -66,  -264,   233,
     -66,   -66,   -66,   -66,   -66,   -66,  -264,  -264,  -264,   234,
    -264,  -264,  -264,  -264,  -264,  -264,   -87,   -66,  -264,   210,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,   229,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,   236,   236,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,   236,
     236,   233,  -264,   -81,  -264,  -264,  -264,   237,  -264,   232,
    -264,  -264,   231,  -264,  -264,  -264,  -264,  -264,  -264,   235,
    -264,  -264,   239,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   210,   256,
     257,   258,   221,  -264,   -87,  -264,  -264,   259,   -51,   260,
     261,   262,   263,   -51,   264,   265,   266,   267,   268,   269,
     270,   271,    70,   276,  -264,  -264,  -264,   -78,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,   233,  -264,  -264
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     0,     0,     0,     0,    19,    16,     0,     5,
       6,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,     7,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    15,     0,    28,    31,
      30,    29,     9,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    18,     0,     2,     3,     0,     0,     0,   167,   166,
       0,     0,    20,    17,     0,    61,     0,     0,    71,     0,
      69,    67,    75,    73,    63,    65,     0,     0,     0,     0,
       0,     0,     0,    59,    77,     0,    25,   163,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    91,    13,    11,    10,    14,    12,
      33,    58,    38,    39,    40,    37,    32,    52,    21,    27,
      52,    52,    52,    52,    52,    52,    41,    44,    47,    43,
      46,    45,    42,    36,    35,    34,    58,    52,    26,     0,
     113,   111,   100,   101,   102,   103,   104,    99,   156,   157,
     158,   159,   112,    96,   161,    95,    93,    94,   114,    97,
      98,   162,   160,     0,   106,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   142,   135,   136,   137,   138,
     139,   140,   141,    23,   107,   108,   150,   151,   143,   144,
     145,   146,   147,   152,   148,   149,   153,   154,   155,   109,
     110,   165,    92,     0,    49,    53,    55,    57,    62,     0,
      51,    72,     0,    70,    68,    76,    74,    64,    66,     0,
      60,    78,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   164,     0,
       0,     0,     0,    50,     0,    22,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   168,   105,    24,     0,    56,   172,
     170,   176,   175,   173,   174,   177,   178,   179,   171,   184,
     180,   181,   182,   183,   185,   169,    54
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -264,  -264,  -264,  -264,   281,  -264,  -264,  -264,  -264,  -231,
    -214,  -264,    90,  -264,  -264,  -264,  -264,  -264,  -264,  -237,
    -151,   -85,  -264,    34,  -264,  -264,  -264,  -264,  -264,  -264,
    -264,  -264,  -264,  -264,  -264,  -263,  -264,  -264,  -264,  -264,
     278,  -264,  -181,  -264,   -65
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,   135,     8,     9,    10,    11,    12,    13,    14,   249,
     324,    46,    47,    48,   265,    49,   245,    50,   259,   350,
     351,   346,   347,   348,    51,   266,   241,   254,   255,   251,
     250,   247,   253,   252,   267,   130,   131,   288,   284,   291,
     132,   269,   140,   378,   379
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
     285,   341,   325,   292,   345,   263,   377,    25,   283,    26,
     286,    27,   289,   133,   134,   290,   339,   340,    28,     1,
       2,     3,     4,     5,    29,   287,    30,   138,   139,   345,
     138,   139,    31,    32,    15,    16,   326,   327,   328,   329,
     330,   331,   332,    33,   334,   335,   343,    34,     6,   344,
       7,    35,   381,   382,    36,   383,   242,   426,    37,    38,
      39,    40,    41,    42,    43,    44,    45,   349,    17,   243,
     344,    18,    19,   244,    20,    21,    22,    24,    52,   144,
      53,    54,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,   136,   137,   141,    66,   142,    67,   353,
     354,   355,   356,   357,   358,   143,    68,    69,    70,    71,
      72,   145,   146,   147,    73,   377,   361,   148,    74,   149,
     240,   150,   151,    75,    76,    77,   166,    78,    79,   152,
     153,   154,   155,   156,   157,   167,   165,   158,   159,    80,
      81,    82,   264,    83,   160,   161,   162,   345,    84,   163,
     164,   168,   169,   258,   246,   170,   171,    85,    86,    87,
      88,    89,    90,    91,    92,    93,    94,    95,   407,   172,
     173,   424,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   174,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   410,   248,   175,
     176,   177,   415,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,   178,   362,   363,   179,   180,
     181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,   200,
     364,   201,   365,   202,   203,   366,   204,   205,   206,   367,
     207,   208,   209,   210,   211,   212,   213,   368,   214,   369,
     370,   215,   216,   217,   218,   219,   220,   371,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
      23,   234,   235,   236,   237,   238,   239,   372,   268,   408,
     360,   373,   374,   375,   376,   256,   257,   260,   261,   262,
     270,   271,     0,   403,   272,   273,   274,   275,   276,     0,
     278,   277,   279,   280,   281,   282,   293,   294,   295,   296,
     297,   298,   299,   300,   301,   302,   303,   304,   305,   306,
     307,   308,   309,   310,   311,   312,     0,   313,   314,   315,
     316,   317,   318,   319,   320,   321,   322,   323,   333,   336,
     337,   338,   342,   352,   359,   380,   381,   384,   383,   385,
     387,   386,   388,   389,   390,   391,   392,   393,   394,   395,
     396,   397,   398,   399,   400,   401,   402,     0,   404,     0,
       0,     0,     0,   405,   406,   409,   411,   412,   413,   414,
     416,   417,   418,   419,   420,   421,   422,   423,   425,   233
};

static const yytype_int16 yycheck[] =
{
     181,   232,   216,   184,   241,     1,   269,    18,    56,    20,
      23,    22,    62,   136,   137,    65,   230,   231,    29,    24,
      25,    26,    27,    28,    35,    38,    37,    78,    79,   266,
      78,    79,    43,    44,   131,   131,   217,   218,   219,   220,
     221,   222,   223,    54,   225,   226,   133,    58,    53,   136,
      55,    62,   130,   134,    65,   136,    51,   135,    69,    70,
      71,    72,    73,    74,    75,    76,    77,   133,   131,    64,
     136,   131,   131,    68,    52,    52,     0,   132,   132,   131,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,   138,   138,   138,    19,   138,    21,   250,
     251,   252,   253,   254,   255,   138,    29,    30,    31,    32,
      33,   131,   131,   131,    37,   378,   267,   131,    41,   131,
     136,   131,   131,    46,    47,    48,   132,    50,    51,   131,
     131,   131,   131,   131,   131,   138,    46,   131,   131,    62,
      63,    64,   138,    66,   131,   131,   131,   384,    71,   131,
     131,   131,   131,   136,   138,   131,   131,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,   382,   131,
     131,   402,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,   131,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   388,   138,   131,
     131,   131,   393,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   131,    16,    17,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
      40,   131,    42,   131,   131,    45,   131,   131,   131,    49,
     131,   131,   131,   131,   131,   131,   131,    57,   131,    59,
      60,   131,   131,   131,   131,   131,   131,    67,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
       9,   132,   132,   132,   132,   132,   132,    87,   132,   384,
     266,    91,    92,    93,    94,   138,   138,   138,   138,   136,
     136,   136,    -1,   378,   138,   138,   136,   136,   136,    -1,
     136,   138,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,    -1,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   132,   130,   130,   136,   130,   130,   136,   138,
     131,   136,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,    -1,   132,    -1,
      -1,    -1,    -1,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   132,   131
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    24,    25,    26,    27,    28,    53,    55,   141,   142,
     143,   144,   145,   146,   147,   131,   131,   131,   131,   131,
      52,    52,     0,   143,   132,    18,    20,    22,    29,    35,
      37,    43,    44,    54,    58,    62,    65,    69,    70,    71,
      72,    73,    74,    75,    76,    77,   150,   151,   152,   154,
     156,   163,   132,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    19,    21,    29,    30,
      31,    32,    33,    37,    41,    46,    47,    48,    50,    51,
      62,    63,    64,    66,    71,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     174,   175,   179,   136,   137,   140,   138,   138,    78,    79,
     181,   138,   138,   138,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   151,   132,   138,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   179,   132,   132,   132,   132,   132,   132,
     136,   165,    51,    64,    68,   155,   138,   170,   138,   148,
     169,   168,   172,   171,   166,   167,   138,   138,   136,   157,
     138,   138,   136,     1,   138,   153,   164,   173,   132,   180,
     136,   136,   138,   138,   136,   136,   136,   138,   136,   136,
     136,   136,   136,    56,   177,   181,    23,    38,   176,    62,
      65,   178,   181,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   149,   149,   181,   181,   181,   181,
     181,   181,   181,   136,   181,   181,   136,   136,   136,   149,
     149,   148,   132,   133,   136,   158,   160,   161,   162,   133,
     158,   159,   130,   159,   159,   159,   159,   159,   159,   130,
     162,   159,    16,    17,    40,    42,    45,    49,    57,    59,
      60,    67,    87,    91,    92,    93,    94,   174,   182,   183,
     136,   130,   134,   136,   130,   138,   136,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   183,   132,   136,   136,   149,   160,   136,
     181,   136,   136,   136,   136,   181,   136,   136,   136,   136,
     136,   136,   136,   136,   148,   132,   135
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   139,   140,   140,   141,   141,   142,   142,   143,   143,
     143,   143,   143,   143,   143,   144,   145,   145,   146,   147,
     147,   148,   148,   149,   149,   150,   150,   151,   151,   151,
     151,   151,   151,   151,   152,   153,   153,   154,   155,   155,
     155,   156,   156,   156,   156,   156,   156,   157,   157,   158,
     158,   159,   159,   160,   160,   161,   161,   162,   162,   164,
     163,   165,   163,   166,   163,   167,   163,   168,   163,   169,
     163,   170,   163,   171,   163,   172,   163,   173,   163,   174,
     174,   174,   174,   174,   174,   174,   174,   174,   174,   174,
     174,   175,   175,   176,   176,   177,   177,   178,   178,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   179,   179,   179,   179,   179,   179,   179,
     179,   179,   179,   180,   179,   179,   181,   181,   182,   182,
     183,   183,   183,   183,   183,   183,   183,   183,   183,   183,
     183,   183,   183,   183,   183,   183
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     0,     1,     1,     2,     2,     2,
       4,     4,     4,     4,     4,     2,     1,     3,     2,     1,
       3,     1,     3,     1,     3,     2,     3,     3,     1,     1,
       1,     1,     3,     3,     3,     1,     1,     3,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     1,     3,     1,
       2,     1,     0,     1,     4,     1,     3,     1,     0,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     5,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     3,     1,     1,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 214 "config_gram.y"
            {
    yyval = yyvsp[0];
    /* convert value to real */
    yyval->value.number_real = yyval->value.number;
    yyval->value.type = V_NUM_REAL;
  }
#line 1926 "config_gram.c"
    break;

  case 3:
#line 220 "config_gram.y"
                  {
    yyval = yyvsp[0];
  }
#line 1934 "config_gram.c"
    break;

  case 10:
#line 239 "config_gram.y"
                                                     {
    strncpy(default_programmer, yyvsp[-1]->value.string, MAX_STR_CONST);
    default_programmer[MAX_STR_CONST-1] = 0;
    free_token(yyvsp[-1]);
  }
#line 1944 "config_gram.c"
    break;

  case 11:
#line 245 "config_gram.y"
                                                   {
    strncpy(default_parallel, yyvsp[-1]->value.string, PATH_MAX);
    default_parallel[PATH_MAX-1] = 0;
    free_token(yyvsp[-1]);
  }
#line 1954 "config_gram.c"
    break;

  case 12:
#line 251 "config_gram.y"
                                                 {
    strncpy(default_serial, yyvsp[-1]->value.string, PATH_MAX);
    default_serial[PATH_MAX-1] = 0;
    free_token(yyvsp[-1]);
  }
#line 1964 "config_gram.c"
    break;

  case 13:
#line 257 "config_gram.y"
                                                    {
    default_bitclock = yyvsp[-1]->value.number_real;
    free_token(yyvsp[-1]);
  }
#line 1973 "config_gram.c"
    break;

  case 14:
#line 262 "config_gram.y"
                                              {
    if (yyvsp[-1]->primary == K_YES)
      default_safemode = 1;
    else if (yyvsp[-1]->primary == K_NO)
      default_safemode = 0;
    free_token(yyvsp[-1]);
  }
#line 1985 "config_gram.c"
    break;

  case 15:
#line 274 "config_gram.y"
    {
      PROGRAMMER * existing_prog;
      char * id;
      if (lsize(current_prog->id) == 0) {
        yyerror("required parameter id not specified");
        YYABORT;
      }
      if (current_prog->initpgm == NULL) {
        yyerror("programmer type not specified");
        YYABORT;
      }
      id = ldata(lfirst(current_prog->id));
      existing_prog = locate_programmer(programmers, id);
      if (existing_prog) {
        { /* temporarly set lineno to lineno of programmer start */
          int temp = lineno; lineno = current_prog->lineno;
          yywarning("programmer %s overwrites previous definition %s:%d.",
                id, existing_prog->config_file, existing_prog->lineno);
          lineno = temp;
        }
        lrmv_d(programmers, existing_prog);
        pgm_free(existing_prog);
      }
      PUSH(programmers, current_prog);
//      pgm_fill_old_pins(current_prog); // TODO to be removed if old pin data no longer needed
//      pgm_display_generic(current_prog, id);
      current_prog = NULL;
    }
#line 2018 "config_gram.c"
    break;

  case 16:
#line 307 "config_gram.y"
    { current_prog = pgm_new();
      if (current_prog == NULL) {
        yyerror("could not create pgm instance");
        YYABORT;
      }
      strcpy(current_prog->config_file, infile);
      current_prog->lineno = lineno;
    }
#line 2031 "config_gram.c"
    break;

  case 17:
#line 317 "config_gram.y"
    {
      struct programmer_t * pgm = locate_programmer(programmers, yyvsp[0]->value.string);
      if (pgm == NULL) {
        yyerror("parent programmer %s not found", yyvsp[0]->value.string);
        free_token(yyvsp[0]);
        YYABORT;
      }
      current_prog = pgm_dup(pgm);
      if (current_prog == NULL) {
        yyerror("could not duplicate pgm instance");
        free_token(yyvsp[0]);
        YYABORT;
      }
      strcpy(current_prog->config_file, infile);
      current_prog->lineno = lineno;
      free_token(yyvsp[0]);
    }
#line 2053 "config_gram.c"
    break;

  case 18:
#line 339 "config_gram.y"
    { 
      LNODEID ln;
      AVRMEM * m;
      AVRPART * existing_part;

      if (current_part->id[0] == 0) {
        yyerror("required parameter id not specified");
        YYABORT;
      }

      /*
       * perform some sanity checking, and compute the number of bits
       * to shift a page for constructing the page address for
       * page-addressed memories.
       */
      for (ln=lfirst(current_part->mem); ln; ln=lnext(ln)) {
        m = ldata(ln);
        if (m->paged) {
          if (m->page_size == 0) {
            yyerror("must specify page_size for paged memory");
            YYABORT;
          }
          if (m->num_pages == 0) {
            yyerror("must specify num_pages for paged memory");
            YYABORT;
          }
          if (m->size != m->page_size * m->num_pages) {
            yyerror("page size (%u) * num_pages (%u) = "
                    "%u does not match memory size (%u)",
                    m->page_size,
                    m->num_pages,
                    m->page_size * m->num_pages,
                    m->size);
            YYABORT;
          }

        }
      }

      existing_part = locate_part(part_list, current_part->id);
      if (existing_part) {
        { /* temporarly set lineno to lineno of part start */
          int temp = lineno; lineno = current_part->lineno;
          yywarning("part %s overwrites previous definition %s:%d.",
                current_part->id,
                existing_part->config_file, existing_part->lineno);
          lineno = temp;
        }
        lrmv_d(part_list, existing_part);
        avr_free_part(existing_part);
      }
      PUSH(part_list, current_part); 
      current_part = NULL; 
    }
#line 2112 "config_gram.c"
    break;

  case 19:
#line 397 "config_gram.y"
    {
      current_part = avr_new_part();
      if (current_part == NULL) {
        yyerror("could not create part instance");
        YYABORT;
      }
      strcpy(current_part->config_file, infile);
      current_part->lineno = lineno;
    }
#line 2126 "config_gram.c"
    break;

  case 20:
#line 407 "config_gram.y"
    {
      AVRPART * parent_part = locate_part(part_list, yyvsp[0]->value.string);
      if (parent_part == NULL) {
        yyerror("can't find parent part");
        free_token(yyvsp[0]);
        YYABORT;
      }

      current_part = avr_dup_part(parent_part);
      if (current_part == NULL) {
        yyerror("could not duplicate part instance");
        free_token(yyvsp[0]);
        YYABORT;
      }
      strcpy(current_part->config_file, infile);
      current_part->lineno = lineno;

      free_token(yyvsp[0]);
    }
#line 2150 "config_gram.c"
    break;

  case 21:
#line 429 "config_gram.y"
             { ladd(string_list, yyvsp[0]); }
#line 2156 "config_gram.c"
    break;

  case 22:
#line 430 "config_gram.y"
                                   { ladd(string_list, yyvsp[0]); }
#line 2162 "config_gram.c"
    break;

  case 23:
#line 435 "config_gram.y"
             { ladd(number_list, yyvsp[0]); }
#line 2168 "config_gram.c"
    break;

  case 24:
#line 436 "config_gram.y"
                                { ladd(number_list, yyvsp[0]); }
#line 2174 "config_gram.c"
    break;

  case 27:
#line 445 "config_gram.y"
                             {
    {
      TOKEN * t;
      char *s;
      int do_yyabort = 0;
      while (lsize(string_list)) {
        t = lrmv_n(string_list, 1);
        if (!do_yyabort) {
          s = dup_string(t->value.string);
          if (s == NULL) {
            do_yyabort = 1;
          } else {
            ladd(current_prog->id, s);
          }
        }
        /* if do_yyabort == 1 just make the list empty */
        free_token(t);
      }
      if (do_yyabort) {
        YYABORT;
      }
    }
  }
#line 2202 "config_gram.c"
    break;

  case 32:
#line 476 "config_gram.y"
                              {
    strncpy(current_prog->desc, yyvsp[0]->value.string, PGM_DESCLEN);
    current_prog->desc[PGM_DESCLEN-1] = 0;
    free_token(yyvsp[0]);
  }
#line 2212 "config_gram.c"
    break;

  case 33:
#line 481 "config_gram.y"
                                  {
    {
      current_prog->baudrate = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
  }
#line 2223 "config_gram.c"
    break;

  case 35:
#line 494 "config_gram.y"
                    {
  const struct programmer_type_t * pgm_type = locate_programmer_type(yyvsp[0]->value.string);
    if (pgm_type == NULL) {
        yyerror("programmer type %s not found", yyvsp[0]->value.string);
        free_token(yyvsp[0]); 
        YYABORT;
    }
    current_prog->initpgm = pgm_type->initpgm;
    free_token(yyvsp[0]); 
}
#line 2238 "config_gram.c"
    break;

  case 36:
#line 505 "config_gram.y"
{
        yyerror("programmer type must be written as \"id_type\"");
        YYABORT;
}
#line 2247 "config_gram.c"
    break;

  case 38:
#line 516 "config_gram.y"
                    { current_prog->conntype = CONNTYPE_PARALLEL; }
#line 2253 "config_gram.c"
    break;

  case 39:
#line 517 "config_gram.y"
                    { current_prog->conntype = CONNTYPE_SERIAL; }
#line 2259 "config_gram.c"
    break;

  case 40:
#line 518 "config_gram.y"
                    { current_prog->conntype = CONNTYPE_USB; }
#line 2265 "config_gram.c"
    break;

  case 41:
#line 522 "config_gram.y"
                                {
    {
      strncpy(current_prog->usbdev, yyvsp[0]->value.string, PGM_USBSTRINGLEN);
      current_prog->usbdev[PGM_USBSTRINGLEN-1] = 0;
      free_token(yyvsp[0]);
    }
  }
#line 2277 "config_gram.c"
    break;

  case 42:
#line 529 "config_gram.y"
                                {
    {
      current_prog->usbvid = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
  }
#line 2288 "config_gram.c"
    break;

  case 44:
#line 536 "config_gram.y"
                               {
    {
      strncpy(current_prog->usbsn, yyvsp[0]->value.string, PGM_USBSTRINGLEN);
      current_prog->usbsn[PGM_USBSTRINGLEN-1] = 0;
      free_token(yyvsp[0]);
    }
  }
#line 2300 "config_gram.c"
    break;

  case 45:
#line 543 "config_gram.y"
                                   {
    {
      strncpy(current_prog->usbvendor, yyvsp[0]->value.string, PGM_USBSTRINGLEN);
      current_prog->usbvendor[PGM_USBSTRINGLEN-1] = 0;
      free_token(yyvsp[0]);
    }
  }
#line 2312 "config_gram.c"
    break;

  case 46:
#line 550 "config_gram.y"
                                    {
    {
      strncpy(current_prog->usbproduct, yyvsp[0]->value.string, PGM_USBSTRINGLEN);
      current_prog->usbproduct[PGM_USBSTRINGLEN-1] = 0;
      free_token(yyvsp[0]);
    }
  }
#line 2324 "config_gram.c"
    break;

  case 47:
#line 560 "config_gram.y"
             {
    {
      /* overwrite pids, so clear the existing entries */
      ldestroy_cb(current_prog->usbpid, free);
      current_prog->usbpid = lcreat(NULL, 0);
    }
    {
      int *ip = malloc(sizeof(int));
      if (ip) {
        *ip = yyvsp[0]->value.number;
        ladd(current_prog->usbpid, ip);
      }
      free_token(yyvsp[0]);
    }
  }
#line 2344 "config_gram.c"
    break;

  case 48:
#line 575 "config_gram.y"
                                    {
    {
      int *ip = malloc(sizeof(int));
      if (ip) {
        *ip = yyvsp[0]->value.number;
        ladd(current_prog->usbpid, ip);
      }
      free_token(yyvsp[0]);
    }
  }
#line 2359 "config_gram.c"
    break;

  case 49:
#line 588 "config_gram.y"
             { if(0 != assign_pin(pin_name, yyvsp[0], 0)) YYABORT;  }
#line 2365 "config_gram.c"
    break;

  case 50:
#line 590 "config_gram.y"
                       { if(0 != assign_pin(pin_name, yyvsp[0], 1)) YYABORT; }
#line 2371 "config_gram.c"
    break;

  case 52:
#line 596 "config_gram.y"
              { pin_clear_all(&(current_prog->pin[pin_name])); }
#line 2377 "config_gram.c"
    break;

  case 54:
#line 602 "config_gram.y"
                                                    { if(0 != assign_pin_list(1)) YYABORT; }
#line 2383 "config_gram.c"
    break;

  case 58:
#line 615 "config_gram.y"
              { pin_clear_all(&(current_prog->pin[pin_name])); }
#line 2389 "config_gram.c"
    break;

  case 59:
#line 619 "config_gram.y"
                     {pin_name = PPI_AVR_VCC;  }
#line 2395 "config_gram.c"
    break;

  case 61:
#line 620 "config_gram.y"
                     {pin_name = PPI_AVR_BUFF; }
#line 2401 "config_gram.c"
    break;

  case 63:
#line 621 "config_gram.y"
                     {pin_name = PIN_AVR_RESET;}
#line 2407 "config_gram.c"
    break;

  case 64:
#line 621 "config_gram.y"
                                                            { free_token(yyvsp[-3]); }
#line 2413 "config_gram.c"
    break;

  case 65:
#line 622 "config_gram.y"
                     {pin_name = PIN_AVR_SCK;  }
#line 2419 "config_gram.c"
    break;

  case 66:
#line 622 "config_gram.y"
                                                            { free_token(yyvsp[-3]); }
#line 2425 "config_gram.c"
    break;

  case 67:
#line 623 "config_gram.y"
                     {pin_name = PIN_AVR_MOSI; }
#line 2431 "config_gram.c"
    break;

  case 69:
#line 624 "config_gram.y"
                     {pin_name = PIN_AVR_MISO; }
#line 2437 "config_gram.c"
    break;

  case 71:
#line 625 "config_gram.y"
                     {pin_name = PIN_LED_ERR;  }
#line 2443 "config_gram.c"
    break;

  case 73:
#line 626 "config_gram.y"
                     {pin_name = PIN_LED_RDY;  }
#line 2449 "config_gram.c"
    break;

  case 75:
#line 627 "config_gram.y"
                     {pin_name = PIN_LED_PGM;  }
#line 2455 "config_gram.c"
    break;

  case 77:
#line 628 "config_gram.y"
                     {pin_name = PIN_LED_VFY;  }
#line 2461 "config_gram.c"
    break;

  case 99:
#line 667 "config_gram.y"
    {
      strncpy(current_part->id, yyvsp[0]->value.string, AVR_IDLEN);
      current_part->id[AVR_IDLEN-1] = 0;
      free_token(yyvsp[0]);
    }
#line 2471 "config_gram.c"
    break;

  case 100:
#line 674 "config_gram.y"
    {
      strncpy(current_part->desc, yyvsp[0]->value.string, AVR_DESCLEN);
      current_part->desc[AVR_DESCLEN-1] = 0;
      free_token(yyvsp[0]);
    }
#line 2481 "config_gram.c"
    break;

  case 101:
#line 681 "config_gram.y"
    {
      strncpy(current_part->family_id, yyvsp[0]->value.string, AVR_FAMILYIDLEN);
      current_part->family_id[AVR_FAMILYIDLEN] = 0;
      free_token(yyvsp[0]);
    }
#line 2491 "config_gram.c"
    break;

  case 102:
#line 687 "config_gram.y"
                                    {
    {
      yyerror("devicecode is deprecated, use "
              "stk500_devcode instead");
      YYABORT;
    }
  }
#line 2503 "config_gram.c"
    break;

  case 103:
#line 695 "config_gram.y"
                                        {
    {
      current_part->stk500_devcode = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
  }
#line 2514 "config_gram.c"
    break;

  case 104:
#line 702 "config_gram.y"
                                        {
    {
      current_part->avr910_devcode = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
  }
#line 2525 "config_gram.c"
    break;

  case 105:
#line 709 "config_gram.y"
                                                         {
    {
      current_part->signature[0] = yyvsp[-2]->value.number;
      current_part->signature[1] = yyvsp[-1]->value.number;
      current_part->signature[2] = yyvsp[0]->value.number;
      free_token(yyvsp[-2]);
      free_token(yyvsp[-1]);
      free_token(yyvsp[0]);
    }
  }
#line 2540 "config_gram.c"
    break;

  case 106:
#line 720 "config_gram.y"
                               {
    {
      current_part->usbpid = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
  }
#line 2551 "config_gram.c"
    break;

  case 107:
#line 727 "config_gram.y"
                                       {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      current_part->ctl_stack_type = CTL_STACK_PP;
      nbytes = 0;
      ok = 1;

      memset(current_part->controlstack, 0, CTL_STACK_SIZE);
      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < CTL_STACK_SIZE)
	  {
	    current_part->controlstack[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  yywarning("too many bytes in control stack");
        }
    }
  }
#line 2586 "config_gram.c"
    break;

  case 108:
#line 758 "config_gram.y"
                                         {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      current_part->ctl_stack_type = CTL_STACK_HVSP;
      nbytes = 0;
      ok = 1;

      memset(current_part->controlstack, 0, CTL_STACK_SIZE);
      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < CTL_STACK_SIZE)
	  {
	    current_part->controlstack[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  yywarning("too many bytes in control stack");
        }
    }
  }
#line 2621 "config_gram.c"
    break;

  case 109:
#line 789 "config_gram.y"
                                   {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      nbytes = 0;
      ok = 1;

      memset(current_part->flash_instr, 0, FLASH_INSTR_SIZE);
      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < FLASH_INSTR_SIZE)
	  {
	    current_part->flash_instr[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  yywarning("too many bytes in flash instructions");
        }
    }
  }
#line 2655 "config_gram.c"
    break;

  case 110:
#line 819 "config_gram.y"
                                    {
    {
      TOKEN * t;
      unsigned nbytes;
      int ok;

      nbytes = 0;
      ok = 1;

      memset(current_part->eeprom_instr, 0, EEPROM_INSTR_SIZE);
      while (lsize(number_list)) {
        t = lrmv_n(number_list, 1);
	if (nbytes < EEPROM_INSTR_SIZE)
	  {
	    current_part->eeprom_instr[nbytes] = t->value.number;
	    nbytes++;
	  }
	else
	  {
	    ok = 0;
	  }
        free_token(t);
      }
      if (!ok)
	{
	  yywarning("too many bytes in EEPROM instructions");
        }
    }
  }
#line 2689 "config_gram.c"
    break;

  case 111:
#line 850 "config_gram.y"
    {
      current_part->chip_erase_delay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2698 "config_gram.c"
    break;

  case 112:
#line 856 "config_gram.y"
    {
      current_part->pagel = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2707 "config_gram.c"
    break;

  case 113:
#line 862 "config_gram.y"
    {
      current_part->bs2 = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2716 "config_gram.c"
    break;

  case 114:
#line 868 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_DEDICATED)
        current_part->reset_disposition = RESET_DEDICATED;
      else if (yyvsp[0]->primary == K_IO)
        current_part->reset_disposition = RESET_IO;

      free_tokens(2, yyvsp[-2], yyvsp[0]);
    }
#line 2729 "config_gram.c"
    break;

  case 115:
#line 878 "config_gram.y"
    {
      current_part->timeout = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2738 "config_gram.c"
    break;

  case 116:
#line 884 "config_gram.y"
    {
      current_part->stabdelay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2747 "config_gram.c"
    break;

  case 117:
#line 890 "config_gram.y"
    {
      current_part->cmdexedelay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2756 "config_gram.c"
    break;

  case 118:
#line 896 "config_gram.y"
    {
      current_part->hvspcmdexedelay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2765 "config_gram.c"
    break;

  case 119:
#line 902 "config_gram.y"
    {
      current_part->synchloops = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2774 "config_gram.c"
    break;

  case 120:
#line 908 "config_gram.y"
    {
      current_part->bytedelay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2783 "config_gram.c"
    break;

  case 121:
#line 914 "config_gram.y"
    {
      current_part->pollvalue = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2792 "config_gram.c"
    break;

  case 122:
#line 920 "config_gram.y"
    {
      current_part->pollindex = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2801 "config_gram.c"
    break;

  case 123:
#line 926 "config_gram.y"
    {
      current_part->predelay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2810 "config_gram.c"
    break;

  case 124:
#line 932 "config_gram.y"
    {
      current_part->postdelay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2819 "config_gram.c"
    break;

  case 125:
#line 938 "config_gram.y"
    {
      current_part->pollmethod = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2828 "config_gram.c"
    break;

  case 126:
#line 944 "config_gram.y"
    {
      current_part->hventerstabdelay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2837 "config_gram.c"
    break;

  case 127:
#line 950 "config_gram.y"
    {
      current_part->progmodedelay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2846 "config_gram.c"
    break;

  case 128:
#line 956 "config_gram.y"
    {
      current_part->latchcycles = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2855 "config_gram.c"
    break;

  case 129:
#line 962 "config_gram.y"
    {
      current_part->togglevtg = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2864 "config_gram.c"
    break;

  case 130:
#line 968 "config_gram.y"
    {
      current_part->poweroffdelay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2873 "config_gram.c"
    break;

  case 131:
#line 974 "config_gram.y"
    {
      current_part->resetdelayms = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2882 "config_gram.c"
    break;

  case 132:
#line 980 "config_gram.y"
    {
      current_part->resetdelayus = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2891 "config_gram.c"
    break;

  case 133:
#line 986 "config_gram.y"
    {
      current_part->hvleavestabdelay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2900 "config_gram.c"
    break;

  case 134:
#line 992 "config_gram.y"
    {
      current_part->resetdelay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2909 "config_gram.c"
    break;

  case 135:
#line 998 "config_gram.y"
    {
      current_part->chiperasepulsewidth = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2918 "config_gram.c"
    break;

  case 136:
#line 1004 "config_gram.y"
    {
      current_part->chiperasepolltimeout = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2927 "config_gram.c"
    break;

  case 137:
#line 1010 "config_gram.y"
    {
      current_part->chiperasetime = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2936 "config_gram.c"
    break;

  case 138:
#line 1016 "config_gram.y"
    {
      current_part->programfusepulsewidth = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2945 "config_gram.c"
    break;

  case 139:
#line 1022 "config_gram.y"
    {
      current_part->programfusepolltimeout = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2954 "config_gram.c"
    break;

  case 140:
#line 1028 "config_gram.y"
    {
      current_part->programlockpulsewidth = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2963 "config_gram.c"
    break;

  case 141:
#line 1034 "config_gram.y"
    {
      current_part->programlockpolltimeout = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2972 "config_gram.c"
    break;

  case 142:
#line 1040 "config_gram.y"
    {
      current_part->synchcycles = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 2981 "config_gram.c"
    break;

  case 143:
#line 1046 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_YES)
        current_part->flags |= AVRPART_HAS_JTAG;
      else if (yyvsp[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_JTAG;

      free_token(yyvsp[0]);
    }
#line 2994 "config_gram.c"
    break;

  case 144:
#line 1056 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_YES)
        current_part->flags |= AVRPART_HAS_DW;
      else if (yyvsp[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_DW;

      free_token(yyvsp[0]);
    }
#line 3007 "config_gram.c"
    break;

  case 145:
#line 1066 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_YES)
        current_part->flags |= AVRPART_HAS_PDI;
      else if (yyvsp[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_PDI;

      free_token(yyvsp[0]);
    }
#line 3020 "config_gram.c"
    break;

  case 146:
#line 1076 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_YES)
        current_part->flags |= AVRPART_HAS_UPDI;
      else if (yyvsp[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_UPDI;

      free_token(yyvsp[0]);
    }
#line 3033 "config_gram.c"
    break;

  case 147:
#line 1086 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_YES)
        current_part->flags |= AVRPART_HAS_TPI;
      else if (yyvsp[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_HAS_TPI;

      free_token(yyvsp[0]);
    }
#line 3046 "config_gram.c"
    break;

  case 148:
#line 1096 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_YES)
        current_part->flags |= AVRPART_IS_AT90S1200;
      else if (yyvsp[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_IS_AT90S1200;

      free_token(yyvsp[0]);
    }
#line 3059 "config_gram.c"
    break;

  case 149:
#line 1106 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_YES)
        current_part->flags |= AVRPART_AVR32;
      else if (yyvsp[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_AVR32;

      free_token(yyvsp[0]);
    }
#line 3072 "config_gram.c"
    break;

  case 150:
#line 1116 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_YES)
        current_part->flags |= AVRPART_ALLOWFULLPAGEBITSTREAM;
      else if (yyvsp[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_ALLOWFULLPAGEBITSTREAM;

      free_token(yyvsp[0]);
    }
#line 3085 "config_gram.c"
    break;

  case 151:
#line 1126 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_YES)
        current_part->flags |= AVRPART_ENABLEPAGEPROGRAMMING;
      else if (yyvsp[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_ENABLEPAGEPROGRAMMING;

      free_token(yyvsp[0]);
    }
#line 3098 "config_gram.c"
    break;

  case 152:
#line 1136 "config_gram.y"
    {
      current_part->idr = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3107 "config_gram.c"
    break;

  case 153:
#line 1142 "config_gram.y"
    {
      current_part->rampz = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3116 "config_gram.c"
    break;

  case 154:
#line 1148 "config_gram.y"
    {
      current_part->spmcr = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3125 "config_gram.c"
    break;

  case 155:
#line 1154 "config_gram.y"
    {
      current_part->eecr = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3134 "config_gram.c"
    break;

  case 156:
#line 1160 "config_gram.y"
    {
      current_part->mcu_base = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3143 "config_gram.c"
    break;

  case 157:
#line 1166 "config_gram.y"
    {
      current_part->nvm_base = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3152 "config_gram.c"
    break;

  case 158:
#line 1172 "config_gram.y"
    {
      current_part->ocd_base = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3161 "config_gram.c"
    break;

  case 159:
#line 1178 "config_gram.y"
    {
      current_part->ocdrev = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3170 "config_gram.c"
    break;

  case 160:
#line 1184 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_YES)
        current_part->flags |= AVRPART_SERIALOK;
      else if (yyvsp[0]->primary == K_NO)
        current_part->flags &= ~AVRPART_SERIALOK;

      free_token(yyvsp[0]);
    }
#line 3183 "config_gram.c"
    break;

  case 161:
#line 1194 "config_gram.y"
    {
      if (yyvsp[0]->primary == K_YES) {
        current_part->flags |= AVRPART_PARALLELOK;
        current_part->flags &= ~AVRPART_PSEUDOPARALLEL;
      }
      else if (yyvsp[0]->primary == K_NO) {
        current_part->flags &= ~AVRPART_PARALLELOK;
        current_part->flags &= ~AVRPART_PSEUDOPARALLEL;
      }
      else if (yyvsp[0]->primary == K_PSEUDO) {
        current_part->flags |= AVRPART_PARALLELOK;
        current_part->flags |= AVRPART_PSEUDOPARALLEL;
      }


      free_token(yyvsp[0]);
    }
#line 3205 "config_gram.c"
    break;

  case 162:
#line 1213 "config_gram.y"
    {
      switch (yyvsp[0]->primary) {
        case K_RESET :
          current_part->retry_pulse = PIN_AVR_RESET;
          break;
        case K_SCK :
          current_part->retry_pulse = PIN_AVR_SCK;
          break;
      }

      free_token(yyvsp[-2]);
    }
#line 3222 "config_gram.c"
    break;

  case 163:
#line 1236 "config_gram.y"
    {
      current_mem = avr_new_memtype();
      if (current_mem == NULL) {
        yyerror("could not create mem instance");
        free_token(yyvsp[0]);
        YYABORT;
      }
      strncpy(current_mem->desc, yyvsp[0]->value.string, AVR_MEMDESCLEN);
      current_mem->desc[AVR_MEMDESCLEN-1] = 0;
      free_token(yyvsp[0]);
    }
#line 3238 "config_gram.c"
    break;

  case 164:
#line 1248 "config_gram.y"
    { 
      AVRMEM * existing_mem;

      existing_mem = avr_locate_mem(current_part, current_mem->desc);
      if (existing_mem != NULL) {
        lrmv_d(current_part->mem, existing_mem);
        avr_free_mem(existing_mem);
      }
      ladd(current_part->mem, current_mem); 
      current_mem = NULL; 
    }
#line 3254 "config_gram.c"
    break;

  case 165:
#line 1260 "config_gram.y"
                               {
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode(yyvsp[-2]);
      if (opnum < 0) YYABORT;
      op = avr_new_opcode();
      if (op == NULL) {
        yyerror("could not create opcode instance");
        free_token(yyvsp[-2]);
        YYABORT;
      }
      if(0 != parse_cmdbits(op)) YYABORT;
      if (current_part->op[opnum] != NULL) {
        /*yywarning("operation redefined");*/
        avr_free_opcode(current_part->op[opnum]);
      }
      current_part->op[opnum] = op;

      free_token(yyvsp[-2]);
    }
  }
#line 3282 "config_gram.c"
    break;

  case 170:
#line 1299 "config_gram.y"
    {
      current_mem->paged = yyvsp[0]->primary == K_YES ? 1 : 0;
      free_token(yyvsp[0]);
    }
#line 3291 "config_gram.c"
    break;

  case 171:
#line 1305 "config_gram.y"
    {
      current_mem->size = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3300 "config_gram.c"
    break;

  case 172:
#line 1312 "config_gram.y"
    {
      current_mem->page_size = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3309 "config_gram.c"
    break;

  case 173:
#line 1318 "config_gram.y"
    {
      current_mem->num_pages = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3318 "config_gram.c"
    break;

  case 174:
#line 1324 "config_gram.y"
    {
      current_mem->offset = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3327 "config_gram.c"
    break;

  case 175:
#line 1330 "config_gram.y"
    {
      current_mem->min_write_delay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3336 "config_gram.c"
    break;

  case 176:
#line 1336 "config_gram.y"
    {
      current_mem->max_write_delay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3345 "config_gram.c"
    break;

  case 177:
#line 1342 "config_gram.y"
    {
      current_mem->pwroff_after_write = yyvsp[0]->primary == K_YES ? 1 : 0;
      free_token(yyvsp[0]);
    }
#line 3354 "config_gram.c"
    break;

  case 178:
#line 1348 "config_gram.y"
    {
      current_mem->readback[0] = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3363 "config_gram.c"
    break;

  case 179:
#line 1354 "config_gram.y"
    {
      current_mem->readback[1] = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3372 "config_gram.c"
    break;

  case 180:
#line 1361 "config_gram.y"
    {
      current_mem->mode = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3381 "config_gram.c"
    break;

  case 181:
#line 1367 "config_gram.y"
    {
      current_mem->delay = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3390 "config_gram.c"
    break;

  case 182:
#line 1373 "config_gram.y"
    {
      current_mem->blocksize = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3399 "config_gram.c"
    break;

  case 183:
#line 1379 "config_gram.y"
    {
      current_mem->readsize = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3408 "config_gram.c"
    break;

  case 184:
#line 1385 "config_gram.y"
    {
      current_mem->pollindex = yyvsp[0]->value.number;
      free_token(yyvsp[0]);
    }
#line 3417 "config_gram.c"
    break;

  case 185:
#line 1391 "config_gram.y"
                               {
    { 
      int opnum;
      OPCODE * op;

      opnum = which_opcode(yyvsp[-2]);
      if (opnum < 0) YYABORT;
      op = avr_new_opcode();
      if (op == NULL) {
        yyerror("could not create opcode instance");
        free_token(yyvsp[-2]);
        YYABORT;
      }
      if(0 != parse_cmdbits(op)) YYABORT;
      if (current_mem->op[opnum] != NULL) {
        /*yywarning("operation redefined");*/
        avr_free_opcode(current_mem->op[opnum]);
      }
      current_mem->op[opnum] = op;

      free_token(yyvsp[-2]);
    }
  }
#line 3445 "config_gram.c"
    break;


#line 3449 "config_gram.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 1417 "config_gram.y"


#if 0
static char * vtypestr(int type)
{
  switch (type) {
    case V_NUM : return "INTEGER";
    case V_NUM_REAL: return "REAL";
    case V_STR : return "STRING";
    default:
      return "<UNKNOWN>";
  }
}
#endif


static int assign_pin(int pinno, TOKEN * v, int invert)
{
  int value;

  value = v->value.number;
  free_token(v);

  if ((value < PIN_MIN) || (value > PIN_MAX)) {
    yyerror("pin must be in the range " TOSTRING(PIN_MIN) "-"  TOSTRING(PIN_MAX));
    return -1;
  }

  pin_set_value(&(current_prog->pin[pinno]), value, invert);

  return 0;
}

static int assign_pin_list(int invert)
{
  TOKEN * t;
  int pin;
  int rv = 0;

  current_prog->pinno[pin_name] = 0;
  while (lsize(number_list)) {
    t = lrmv_n(number_list, 1);
    if (rv == 0) {
      pin = t->value.number;
      if ((pin < PIN_MIN) || (pin > PIN_MAX)) {
        yyerror("pin must be in the range " TOSTRING(PIN_MIN) "-"  TOSTRING(PIN_MAX));
        rv = -1;
      /* loop clears list and frees tokens */
      }
      pin_set_value(&(current_prog->pin[pin_name]), pin, invert);
    }
    free_token(t);
  }
  return rv;
}

static int which_opcode(TOKEN * opcode)
{
  switch (opcode->primary) {
    case K_READ        : return AVR_OP_READ; break;
    case K_WRITE       : return AVR_OP_WRITE; break;
    case K_READ_LO     : return AVR_OP_READ_LO; break;
    case K_READ_HI     : return AVR_OP_READ_HI; break;
    case K_WRITE_LO    : return AVR_OP_WRITE_LO; break;
    case K_WRITE_HI    : return AVR_OP_WRITE_HI; break;
    case K_LOADPAGE_LO : return AVR_OP_LOADPAGE_LO; break;
    case K_LOADPAGE_HI : return AVR_OP_LOADPAGE_HI; break;
    case K_LOAD_EXT_ADDR : return AVR_OP_LOAD_EXT_ADDR; break;
    case K_WRITEPAGE   : return AVR_OP_WRITEPAGE; break;
    case K_CHIP_ERASE  : return AVR_OP_CHIP_ERASE; break;
    case K_PGM_ENABLE  : return AVR_OP_PGM_ENABLE; break;
    default :
      yyerror("invalid opcode");
      return -1;
      break;
  }
}


static int parse_cmdbits(OPCODE * op)
{
  TOKEN * t;
  int bitno;
  char ch;
  char * e;
  char * q;
  int len;
  char * s, *brkt = NULL;
  int rv = 0;

  bitno = 32;
  while (lsize(string_list)) {

    t = lrmv_n(string_list, 1);

    s = strtok_r(t->value.string, " ", &brkt);
    while (rv == 0 && s != NULL) {

      bitno--;
      if (bitno < 0) {
        yyerror("too many opcode bits for instruction");
        rv = -1;
        break;
      }

      len = strlen(s);

      if (len == 0) {
        yyerror("invalid bit specifier \"\"");
        rv = -1;
        break;
      }

      ch = s[0];

      if (len == 1) {
        switch (ch) {
          case '1':
            op->bit[bitno].type  = AVR_CMDBIT_VALUE;
            op->bit[bitno].value = 1;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case '0':
            op->bit[bitno].type  = AVR_CMDBIT_VALUE;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'x':
            op->bit[bitno].type  = AVR_CMDBIT_IGNORE;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'a':
            op->bit[bitno].type  = AVR_CMDBIT_ADDRESS;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = 8*(bitno/8) + bitno % 8;
            break;
          case 'i':
            op->bit[bitno].type  = AVR_CMDBIT_INPUT;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          case 'o':
            op->bit[bitno].type  = AVR_CMDBIT_OUTPUT;
            op->bit[bitno].value = 0;
            op->bit[bitno].bitno = bitno % 8;
            break;
          default :
            yyerror("invalid bit specifier '%c'", ch);
            rv = -1;
            break;
        }
      }
      else {
        if (ch == 'a') {
          q = &s[1];
          op->bit[bitno].bitno = strtol(q, &e, 0);
          if ((e == q)||(*e != 0)) {
            yyerror("can't parse bit number from \"%s\"", q);
            rv = -1;
            break;
          }
          op->bit[bitno].type = AVR_CMDBIT_ADDRESS;
          op->bit[bitno].value = 0;
        }
        else {
          yyerror("invalid bit specifier \"%s\"", s);
          rv = -1;
          break;
        }
      }

      s = strtok_r(NULL, " ", &brkt);
    } /* while */

    free_token(t);

  }  /* while */

  return rv;
}
