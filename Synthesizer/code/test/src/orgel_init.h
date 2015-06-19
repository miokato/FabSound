//Arduino + Sound WS
//
//2011.11.26-27
//
//Orgel Sound Init


extern const unsigned char onkai_d[];
extern const unsigned char onkai_f[];
extern const unsigned char sineTable[];
extern const unsigned char envelopeTable[];

#define C_1		5
#define C_1s	        6
#define D_1		7
#define D_1s	        8
#define E_1		9
#define F_1		10
#define F_1s	        11
#define G_1		12
#define G_1s	        13
#define A_1		14
#define A_1s	        15
#define H_1		16

#define C_2		17
#define C_2s	        18
#define D_2		19
#define D_2s	        20
#define E_2		21
#define F_2		22
#define F_2s	        23
#define G_2		24
#define G_2s	        25
#define A_2		26
#define A_2s	        27
#define H_2		28

#define C_3		29
#define C_3s	        30
#define D_3		31
#define D_3s	        32
#define E_3		33
#define F_3		34
#define F_3s	        35
#define G_3		36
#define G_3s	        37
#define A_3		38
#define A_3s	        39
#define H_3		40

#define C_4		41
#define C_4s	        42
#define D_4		43
#define D_4s	        44
#define E_4		45
#define F_4		46
#define F_4s	        47
#define G_4		48
#define G_4s	        49
#define A_4		50
#define A_4s	        51
#define H_4		52

#define C_5		53
#define C_5s	        54
#define D_5		55
#define D_5s	        56
#define E_5		57
#define F_5		58
#define F_5s	        59
#define G_5		60
#define G_5s	        61
#define A_5		62
#define A_5s	        63
#define H_5		64

#define C_6		65
#define C_6s	        66

#define D_6		55
#define D_6s	        56
#define E_6		57
#define F_6	  	58
#define F_6s	        59
#define G_6		60
#define G_6s	        61
#define A_6		62
#define A_6s	        63
#define H_6		64

#define d_16	        4
#define d_3		5
#define d_16f	        6
#define d_8		8
#define d_8f	        12
#define d_4		16
#define d_4f	        24
#define d_2		32
#define d_2f	        48
#define d_0		0

#define k_16	        4
#define k_16f	        6
#define k_8		8
#define k_8f	        12
#define k_4		16
#define k_4f	        24
#define k_2		32
#define k_2f	        48




