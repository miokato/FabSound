const unsigned char onkai_d[] = {
    2,    2,    2,    2,    3,    3,    3,    3,    3,    4,    4,    4,    5,    5,    5,    5,
    6,    6,    7,    7,    7,    8,    8,    9,   10,   10,   11,   11,   12,   13,   14,   15,
   15,   16,   17,   18,   20,   21,   22,   23,   25,   26,   28,   30,   31,   33,   35,   37,
   40,   42,   45,   47,   50,   53,   56,   60,   63,   67,   71,   75,   80,   85,   90,   95,
  101,  107,  113,  120,  127,  135,  143};

const unsigned char onkai_f[] = {
  131,  169,  209,  252,   42,   90,  141,  195,  252,   57,  121,  189,    5,   81,  162,  248,
   83,  179,   25,  133,  248,  113,  241,  121,    9,  162,   68,  240,  165,  102,   50,   10,
  239,  225,  226,  242,   18,   68,  136,  223,   74,  203,   99,   19,  221,  193,  195,  228,
   36,  135,   15,  189,  147,  149,  197,   37,  185,  130,  134,  199,  72,    14,    29, 121,
   38,   42,  137,   73,  113,    4,   12};
  

const unsigned char envelopeTable[] = {
  127,  124,  121,  119,  116,  113,  111,  109,  106,  104,  102,  100,   97,   95,   93,   91,
   89,   87,   85,   84,   82,   80,   78,   77,   75,   73,   72,   70,   69,   67,   66,   64,
   63,   62,   60,   59,   58,   56,   55,   54,   53,   52,   51,   50,   48,   47,   46,   45,
   44,   43,   42,   42,   41,   40,   39,   38,   37,   36,   36,   35,   34,   33,   33,   32,
   31,   31,   30,   29,   29,   28,   27,   27,   26,   26,   25,   25,   24,   23,   23,   22,
   22,   21,   21,   21,   20,   20,   19,   19,   18,   18,   18,   17,   17,   16,   16,   16,
   15,   15,   15,   14,   14,   14,   13,   13,   13,   13,   12,   12,   12,   11,   11,   11,
   11,   10,   10,   10,   10,   10,    9,    9,    9,    9,    9,    8,    8,    8,    8,    8,
   7,     7,    7,    7,    7,    7,    6,    6,    6,    6,    6,    6,    6,    5,    5,    5,
   5,     5,    5,    5,    5,    5,    4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
   3,     3,    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,    2,    2,    2,
   2,     2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,    2,
   1,     1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
   1,     1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
   0,     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   0,     0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0
};

const unsigned char sineTable[]={
  127,  130,  133,  136,  139,  142,  145,  148,  152,  155,  158,  161,  164,  167,  170,  173,
  176,  179,  181,  184,  187,  190,  193,  195,  198,  200,  203,  206,  208,  210,  213,  215,
  217,  219,  222,  224,  226,  228,  230,  231,  233,  235,  237,  238,  240,  241,  242,  244,
  245,  246,  247,  248,  249,  250,  251,  252,  252,  253,  253,  254,  254,  254,  254,  254,
  254,  254,  254,  254,  254,  253,  253,  252,  252,  251,  250,  250,  249,  248,  247,  246,
  244,  243,  242,  240,  239,  237,  236,  234,  232,  231,  229,  227,  225,  223,  221,  218,
  216,  214,  212,  209,  207,  204,  202,  199,  197,  194,  191,  188,  186,  183,  180,  177,
  174,  171,  168,  165,  162,  159,  156,  153,  150,  147,  144,  141,  138,  134,  131,  128,
  125,  122,  119,  115,  112,  109,  106,  103,  100,   97,   94,   91,   88,   85,   82,   79,
   76,   73,   70,   67,   65,   62,   59,   56,   54,   51,   49,   46,   44,   41,   39,   37,
   35,   32,   30,   28,   26,   24,   22,   21,   19,   17,   16,   14,   13,   11,   10,    9,
    7,    6,    5,    4,    3,    3,    2,    1,    1,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    1,    1,    2,    3,    4,    5,    6,    7,    8,
    9,   11,   12,   13,   15,   16,   18,   20,   22,   23,   25,   27,   29,   31,   34,   36,
   38,   40,   43,   45,   47,   50,   53,   55,   58,   60,   63,   66,   69,   72,   74,   77,
   80,   83,   86,   89,   92,   95,   98,  101,  105,  108,  111,  114,  117,  120,  123,  126
 };

