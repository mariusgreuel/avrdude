/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
