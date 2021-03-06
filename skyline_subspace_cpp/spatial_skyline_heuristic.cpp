//
// Test.cpp
//
// This is a direct port of the C version of the RTree test program.
//
#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include "RTree.h"
#include <vector>
#include <map>
#include <set>
#include <ctime>
#include <algorithm>
#include <string.h>
#include <bitset>
using namespace std;

const int BSIZE = 200;

typedef pair<int, int> PII;
typedef long long LL;
typedef bitset<BSIZE> BS;
/*
double sample[] = {
		0.26541439,  0.71765957,  0.1838978 ,  0.06014367,  0.35413377,
        0.33222497,  0.08287028,  0.35189886,  0.05193604,  0.26508891,
        0.28461378,  0.07238245,  0.40642035,  0.6507677 ,  0.07346683,
        0.89202127,  0.42845288,  0.89048428,  0.41553228,  0.38323407,
        0.62174905,  0.25006482,  0.75089282,  0.73239422,  0.42002889,
        0.15222028,  0.45636669,  0.6378672 ,  0.28589422,  0.25946748,
        0.42082049,  0.51695645,  0.35768963,  0.72065116,  0.48832032,
        0.33972814,  0.1749104 ,  0.02718974,  0.60117253,  0.38456728,
        0.77124105,  0.11294617,  0.9079478 ,  0.62486844,  0.12272032,
        0.07121628,  0.96794443,  0.91705506,  0.13270958,  0.84929916,
        0.92927164,  0.78060248,  0.13335809,  0.209921  ,  0.92257242,
        0.17484062,  0.75811196,  0.73474457,  0.92648959,  0.50207418,
        0.17164682,  0.00909255,  0.6503033 ,  0.87093972,  0.06100232,
        0.39877753,  0.15577371,  0.92551516,  0.36388657,  0.06756097,
        0.90458698,  0.33225038,  0.04922501,  0.41723956,  0.831911  ,
        0.20403531,  0.74221035,  0.26618987,  0.97115766,  0.93566033,
        0.26275375,  0.27001418,  0.91441143,  0.46832666,  0.9129339 ,
        0.64735306,  0.3496771 ,  0.52781609,  0.02283276,  0.40979401,
        0.45350805,  0.57090502,  0.62757193,  0.94845591,  0.26608795,
        0.09802528,  0.01323141,  0.36448934,  0.28460354,  0.14845612
};*/

double sample[] = {
		0.57581612,  0.92434388,  0.68543771,  0.94089058,  0.10271061,
        0.2606751 ,  0.956196  ,  0.82424025,  0.92726781,  0.65108394,
        0.43539372,  0.53620522,  0.83829153,  0.89173241,  0.45414002,
        0.93867441,  0.8174498 ,  0.82162721,  0.97457525,  0.7008915 ,
        0.52714995,  0.20270035,  0.49711097,  0.20048408,  0.69897604,
        0.42346773,  0.83181996,  0.7446606 ,  0.57339969,  0.7984472 ,
        0.5408443 ,  0.91011413,  0.71652843,  0.49898038,  0.48566627,
        0.36211279,  0.93512931,  0.3861863 ,  0.53813593,  0.55082693,
        0.35337416,  0.40355747,  0.97532437,  0.76573552,  0.28990968,
        0.17678709,  0.05427248,  0.31650965,  0.27398913,  0.96087779,
        0.42782542,  0.98431663,  0.82438854,  0.96939706,  0.38865115,
        0.49764794,  0.24785142,  0.80225116,  0.28500124,  0.58510292,
        0.21505904,  0.86698323,  0.27206238,  0.0172032 ,  0.61224887,
        0.04190118,  0.871479  ,  0.55758993,  0.99177575,  0.56286219,
        0.51429445,  0.97110511,  0.25812345,  0.60246122,  0.73362926,
        0.59927003,  0.69545572,  0.94034361,  0.67030085,  0.61712475,
        0.21097708,  0.65830778,  0.76833037,  0.79299837,  0.30623246,
        0.35748953,  0.24076896,  0.32524086,  0.33878216,  0.96022465,
        0.39480481,  0.33895839,  0.07490816,  0.19863642,  0.53295582,
        0.09875998,  0.77826083,  0.12723832,  0.24783772,  0.63533101,
        0.51723717,  0.86336676,  0.91522678,  0.5246165 ,  0.39292968,
        0.05088304,  0.65494659,  0.78734303,  0.99836489,  0.19498218,
        0.54930287,  0.94177074,  0.48853717,  0.7542381 ,  0.34180477,
        0.33264482,  0.2872597 ,  0.12129757,  0.18014821,  0.64441102,
        0.15844554,  0.7830521 ,  0.65362045,  0.99696097,  0.5234829 ,
        0.89389927,  0.84522173,  0.91034711,  0.60864609,  0.06042072,
        0.47283486,  0.101576  ,  0.38885835,  0.00959855,  0.35696115,
        0.67339573,  0.71814536,  0.8333387 ,  0.63088812,  0.46216469,
        0.75605166,  0.63957314,  0.70241927,  0.86465261,  0.73943006,
        0.31029116,  0.947731  ,  0.42243602,  0.62166655,  0.99805662,
        0.57371667,  0.72276847,  0.50078026,  0.35027668,  0.58845069,
        0.68056674,  0.93918482,  0.3230821 ,  0.66367147,  0.42816981,
        0.10351627,  0.46237167,  0.85596334,  0.19344879,  0.20067881,
        0.14369719,  0.11887754,  0.35922057,  0.42310757,  0.64961704,
        0.28895724,  0.59050577,  0.7390823 ,  0.26811864,  0.27386863,
        0.2787233 ,  0.60051536,  0.43317586,  0.93850168,  0.21249955,
        0.86798602,  0.66678703,  0.9679012 ,  0.1751029 ,  0.50884598,
        0.60491483,  0.43014359,  0.74955423,  0.1243433 ,  0.01422392,
        0.02037321,  0.33871384,  0.86221581,  0.20240617,  0.47122324,
        0.80032126,  0.49407773,  0.79032042,  0.8437122 ,  0.61296439,
        0.4433303 ,  0.14299566,  0.67981656,  0.012464  ,  0.14209262,
        0.28468348,  0.87176499,  0.32283373,  0.44057251,  0.67872072,
        0.53568592,  0.11858845,  0.56678096,  0.79693257,  0.02472939,
        0.02434025,  0.21628378,  0.51051109,  0.10216111,  0.71996161,
        0.02261692,  0.64809773,  0.49676676,  0.81418884,  0.30544631,
        0.46247348,  0.77125411,  0.41341357,  0.92486692,  0.31868224,
        0.46729787,  0.02896882,  0.40768403,  0.31314293,  0.42873392,
        0.08418868,  0.1393261 ,  0.29372265,  0.99067748,  0.98907665,
        0.38916967,  0.32077368,  0.90114146,  0.433362  ,  0.3036822 ,
        0.11843029,  0.55736426,  0.06878669,  0.02299206,  0.10866752,
        0.11057913,  0.97263408,  0.57260381,  0.09227106,  0.20389074,
        0.8126966 ,  0.74244336,  0.17722353,  0.01904563,  0.12386042,
        0.73080537,  0.66566993,  0.3638416 ,  0.40963631,  0.8352995 ,
        0.4694916 ,  0.10466907,  0.9668323 ,  0.24668287,  0.13219141,
        0.39808556,  0.44905952,  0.05170628,  0.65097736,  0.23002575,
        0.14240692,  0.34669915,  0.05684612,  0.74215994,  0.0802227 ,
        0.20151338,  0.18352813,  0.40711999,  0.81328825,  0.98407932,
        0.71000337,  0.26539731,  0.5300058 ,  0.5769054 ,  0.50825579,
        0.111985  ,  0.10826445,  0.65422501,  0.16685804,  0.67138012,
        0.33055482,  0.1687699 ,  0.91862157,  0.93786022,  0.55570835,
        0.26776673,  0.71272115,  0.55330541,  0.01290383,  0.96878121,
        0.53112435,  0.42074826,  0.42525375,  0.88071589,  0.75771052,
        0.2291754 ,  0.82156566,  0.0563345 ,  0.4147838 ,  0.73377909,
        0.52425718,  0.82055577,  0.46713132,  0.21323364,  0.26188599,
        0.69747629,  0.90853031,  0.52524853,  0.49811342,  0.15350851,
        0.88525625,  0.22023206,  0.44835473,  0.92264265,  0.89005922,
        0.64629858,  0.63976447,  0.85629686,  0.12075448,  0.66226607,
        0.42629318,  0.16827295,  0.56121142,  0.60107807,  0.66894089,
        0.46344456,  0.90378136,  0.17790259,  0.85280717,  0.03967885,
        0.16054629,  0.53511046,  0.70542396,  0.20495657,  0.72452881,
        0.39573819,  0.03441724,  0.30177627,  0.04421597,  0.31614049,
        0.0640442 ,  0.89875603,  0.95592033,  0.91330883,  0.77238509,
        0.85865322,  0.93435348,  0.56560398,  0.48871433,  0.40512944,
        0.51125497,  0.63609885,  0.82288601,  0.79879517,  0.43856611,
        0.34358071,  0.25532515,  0.57288529,  0.60781017,  0.9379104 ,
        0.84002808,  0.48702937,  0.87642426,  0.11647737,  0.30735832,
        0.15059849,  0.5062552 ,  0.27801077,  0.47740405,  0.95802259,
        0.54349179,  0.0644143 ,  0.49296642,  0.33269535,  0.37110626,
        0.89953402,  0.98187784,  0.66533112,  0.69637448,  0.5269574 ,
        0.28787249,  0.0760973 ,  0.42339915,  0.36204257,  0.06747287,
        0.24811883,  0.95979091,  0.7978943 ,  0.23806201,  0.70373424,
        0.60877977,  0.00472724,  0.84728406,  0.71933158,  0.28082184,
        0.77186022,  0.56602569,  0.53185446,  0.55367425,  0.59272306,
        0.8358393 ,  0.73460516,  0.283728  ,  0.91264241,  0.41610203,
        0.22071777,  0.29422493,  0.39649613,  0.5592091 ,  0.02618015,
        0.51730869,  0.21549122,  0.34747086,  0.78402227,  0.1775062 ,
        0.95354117,  0.80463252,  0.69865215,  0.1468581 ,  0.75855765,
        0.16227354,  0.06093615,  0.72142955,  0.4062941 ,  0.86079176,
        0.18892759,  0.96558276,  0.11382009,  0.86777477,  0.7952899 ,
        0.8471236 ,  0.43670182,  0.89581133,  0.25522993,  0.45276058,
        0.49819886,  0.42330113,  0.73840159,  0.58308616,  0.88700965,
        0.75777663,  0.0611357 ,  0.77254485,  0.8155311 ,  0.58309819,
        0.441644  ,  0.45806168,  0.6241094 ,  0.67986013,  0.83855616,
        0.75975364,  0.0116947 ,  0.00351329,  0.52017307,  0.51049578,
        0.3980947 ,  0.97941599,  0.88228575,  0.23695528,  0.72383961,
        0.97305585,  0.08519269,  0.12474733,  0.07378129,  0.08735447,
        0.93836623,  0.84525554,  0.95846629,  0.7411588 ,  0.73768811,
        0.70063791,  0.77451613,  0.80061379,  0.29955497,  0.35940336,
        0.21979785,  0.21534722,  0.55918144,  0.92130525,  0.5595433 ,
        0.5690163 ,  0.30733076,  0.36052179,  0.122913  ,  0.85862536,
        0.06422961,  0.93820383,  0.18582219,  0.38590593,  0.00249028,
        0.49206699,  0.45694111,  0.25130594,  0.40363659,  0.69768691,
        0.01605878,  0.99827599,  0.80877335,  0.09368839,  0.52090678,
        0.84557013,  0.12614923,  0.81341077,  0.48506253,  0.44799313,
        0.37927349,  0.50916713,  0.14894098,  0.92427938,  0.38487543,
        0.26826463,  0.75620124,  0.94138425,  0.13437825,  0.56095487,
        0.69870253,  0.39171631,  0.48938425,  0.46786139,  0.36537162,
        0.00335709,  0.2851244 ,  0.46886924,  0.15113705,  0.57058823,
        0.83734675,  0.46814724,  0.05606386,  0.38534957,  0.9480687 ,
        0.53981691,  0.58016612,  0.45938579,  0.40969128,  0.51242174,
        0.40364202,  0.96610984,  0.14226996,  0.27146183,  0.79749372,
        0.84634447,  0.54462263,  0.65710331,  0.76397897,  0.7847115 ,
        0.84803736,  0.50214052,  0.18345213,  0.75909917,  0.16672088,
        0.69226515,  0.09100664,  0.71712145,  0.57961435,  0.61858967,
        0.59235232,  0.72302368,  0.66531624,  0.63179427,  0.48722864,
        0.5405567 ,  0.86302166,  0.3680203 ,  0.11226196,  0.83019175,
        0.36425529,  0.40362428,  0.62687732,  0.94705387,  0.04780281,
        0.88476608,  0.78486162,  0.8418689 ,  0.11603603,  0.78448394,
        0.42645967,  0.96066755,  0.81710209,  0.54665674,  0.69845669,
        0.28347642,  0.27057205,  0.0368585 ,  0.80480799,  0.61965256,
        0.80824379,  0.74437398,  0.87302253,  0.95103813,  0.70520667,
        0.84741242,  0.79038731,  0.62335125,  0.7836699 ,  0.10442237,
        0.93220727,  0.84100827,  0.50917337,  0.00842234,  0.58934643,
        0.99341066,  0.93266632,  0.26759961,  0.57905141,  0.61733966,
        0.03976577,  0.96202902,  0.08288077,  0.20304774,  0.18801154,
        0.31788565,  0.49417339,  0.15079033,  0.13505309,  0.95415539,
        0.15705359,  0.70003089,  0.13796616,  0.04580131,  0.93275695,
        0.27969979,  0.09444574,  0.25071323,  0.62789775,  0.30127539,
        0.79294325,  0.61270528,  0.96436631,  0.41376013,  0.91397123,
        0.59147309,  0.48531043,  0.53086974,  0.42007558,  0.91891296,
        0.16922203,  0.32128791,  0.26709977,  0.8926996 ,  0.92386182,
        0.16912956,  0.74618038,  0.9711212 ,  0.95853326,  0.17967407,
        0.14701341,  0.96022961,  0.0566581 ,  0.64849481,  0.092434  ,
        0.41794984,  0.48972624,  0.80239197,  0.64230893,  0.67684707,
        0.33833233,  0.29052604,  0.43670181,  0.88924259,  0.24847577,
        0.08573053,  0.81346097,  0.66839192,  0.96889759,  0.82340065,
        0.34235049,  0.20595573,  0.9494843 ,  0.12202914,  0.27164406,
        0.49252544,  0.56996092,  0.41247298,  0.48964728,  0.9902567 ,
        0.81522401,  0.1114423 ,  0.68164245,  0.14150298,  0.21762686,
        0.32787932,  0.37559932,  0.40869326,  0.15902459,  0.84086472,
        0.66990512,  0.27695627,  0.43960395,  0.05873277,  0.42950535,
        0.78885489,  0.04461648,  0.67190991,  0.76444532,  0.08609266,
        0.27785908,  0.83795159,  0.39507171,  0.35414488,  0.78758227,
        0.39826919,  0.78750792,  0.68479777,  0.51823593,  0.35749688,
        0.71755626,  0.62327084,  0.26197272,  0.519001  ,  0.5105611 ,
        0.93702445,  0.95681769,  0.20567855,  0.45417624,  0.64149541,
        0.85930648,  0.95648481,  0.17398225,  0.15380249,  0.12036463,
        0.52943371,  0.75288741,  0.5323702 ,  0.59479948,  0.87020095,
        0.93176713,  0.10335543,  0.05128695,  0.77031359,  0.69609396,
        0.1692578 ,  0.99437607,  0.92000696,  0.55984704,  0.88206652,
        0.36344193,  0.87551891,  0.77741856,  0.11306648,  0.54509282,
        0.5135826 ,  0.77051476,  0.28966852,  0.7504198 ,  0.30907082,
        0.52395702,  0.58077083,  0.34645269,  0.74790819,  0.11606648,
        0.56600542,  0.96472849,  0.11669403,  0.16366389,  0.16559832,
        0.46898218,  0.60406294,  0.23591808,  0.77692074,  0.57768883,
        0.8900437 ,  0.00102398,  0.99669729,  0.02892563,  0.34423872,
        0.00283284,  0.34568979,  0.2479986 ,  0.98456947,  0.47427254,
        0.00523559,  0.35337255,  0.52145449,  0.17686293,  0.94582664,
        0.84385522,  0.66834209,  0.59695212,  0.14083377,  0.61584954,
        0.3473434 ,  0.19299344,  0.8040313 ,  0.80512371,  0.27542637,
        0.88779726,  0.20291757,  0.37857516,  0.64537776,  0.73361244,
        0.27570214,  0.29646636,  0.36942134,  0.93617949,  0.0320553 ,
        0.48804657,  0.00997533,  0.47164004,  0.03103744,  0.32395817,
        0.10571291,  0.61186283,  0.6530666 ,  0.65717212,  0.7714102 ,
        0.730296  ,  0.9503998 ,  0.13871651,  0.92741508,  0.59041586,
        0.28270437,  0.31062091,  0.9502005 ,  0.07025139,  0.0994071 ,
        0.94312643,  0.91948544,  0.93089209,  0.9716475 ,  0.60816745,
        0.55412642,  0.46011036,  0.65918892,  0.5645115 ,  0.12330294,
        0.13232582,  0.71282783,  0.5332322 ,  0.05676725,  0.32116746,
        0.9020334 ,  0.45926159,  0.87973899,  0.39583326,  0.38853243,
        0.52198879,  0.09481097,  0.62401638,  0.55795962,  0.72072175,
        0.19248799,  0.3229513 ,  0.28775797,  0.96081388,  0.7790109 ,
        0.07689107,  0.07669609,  0.51174233,  0.5634844 ,  0.81642189,
        0.62441096,  0.89846283,  0.72017458,  0.98191548,  0.33511066,
        0.18132   ,  0.72201126,  0.80451465,  0.04378388,  0.67881621,
        0.15628453,  0.47491621,  0.13456704,  0.04844063,  0.32692838,
        0.18039956,  0.9064367 ,  0.66162733,  0.38639547,  0.09112326,
        0.67310142,  0.43844553,  0.75213039,  0.89111693,  0.93420312,
        0.41173394,  0.2871271 ,  0.37229204,  0.07363273,  0.26566318,
        0.67168296,  0.91740914,  0.50073055,  0.7088928 ,  0.96528386,
        0.44257387,  0.96898468,  0.21671959,  0.28497811,  0.53013261,
        0.35780418,  0.36450556,  0.1115556 ,  0.39032182,  0.79396042,
        0.33275248,  0.82690228,  0.35195461,  0.28695769,  0.08555391,
        0.84387415,  0.2390295 ,  0.30401323,  0.94774295,  0.94109717,
        0.36059785,  0.57184142,  0.50410795,  0.04051212,  0.06512058,
        0.68239572,  0.78040114,  0.46482958,  0.28164266,  0.4443234 ,
        0.61659539,  0.38708706,  0.57626594,  0.70280571,  0.65697486,
        0.52284667,  0.96021308,  0.93182532,  0.23970618,  0.73915751,
        0.58901579,  0.01169265,  0.33150186,  0.82697564,  0.19586371,
        0.2788821 ,  0.59241909,  0.2697697 ,  0.05695803,  0.71165874,
        0.19738914,  0.50363791,  0.21844113,  0.7429265 ,  0.55869035,
        0.63687536,  0.04982039,  0.9264801 ,  0.88403054,  0.24510816,
        0.59109171,  0.70236267,  0.79466025,  0.033617  ,  0.91193   ,
        0.32724655,  0.75620062,  0.53859812,  0.73098442,  0.90213386,
        0.12806807,  0.57395083,  0.35547275,  0.81516194,  0.08103625,
        0.47194757,  0.2362484 ,  0.29504723,  0.02413762,  0.42093979,
        0.48068898,  0.00645261,  0.94953872,  0.31310201,  0.50358867,
        0.8881006 ,  0.10695378,  0.48207881,  0.74738072,  0.73111161,
        0.88539522,  0.6682441 ,  0.70436882,  0.0503947 ,  0.23963685,
        0.99719522,  0.82470079,  0.48511627,  0.25486263,  0.23270956
};

struct Rect
{
  Rect()  {}

  Rect(int a_minX, int a_minY, int a_maxX, int a_maxY)
  {
    min[0] = a_minX;
    min[1] = a_minY;

    max[0] = a_maxX;
    max[1] = a_maxY;
  }

  int min[2];
  int max[2];
};

struct Point {
	Point()  {}

	Point(int X, int Y) {
		min[0] = max[0] = X;
		min[1] = max[1] = Y;
	}

	int min[2];
	int max[2];
};


int N = 40000;
int M = 20;
const int MAXM = 700;
const int MAXN = 1000000;
const LL INF = 1000000000000000000LL;

vector<int> features[MAXN];
vector<int> skills[MAXM];
vector<int> Dradius;
vector<LL> L[MAXM + 1];
vector<Point> point_list;
map<LL, vector<PII> > candList;
LL NB[MAXN], NBE[MAXN];

LL cnt;
LL fv[MAXM];

RTree<int, int, 2, float> tree;

bool MySearchCallback(int id, void* arg) {
	Dradius.push_back(id);
	return true;
}

LL distSquare(int i, int j) {
	LL dx = point_list[i].min[0] - point_list[j].min[0];
	LL dy = point_list[i].min[1] - point_list[j].min[1];
	return dx*dx + dy*dy;
}

void getDhopValues(LL D, int source) {
	for (int i = 0; i < M; i++) {
		fv[i] = INF;
		for (int j = 0; j < skills[i].size(); j++) {
			int ind = skills[i][j];
			LL dis = distSquare(source, ind);
			if (dis < D * D && dis < fv[i]) {
				fv[i] = dis;
			}
		}

	}

	/*
	Rect search_rect(x - D, y - D, x + D, y + D);
	tree.Search(search_rect.min, search_rect.max, MySearchCallback, NULL);
	for (int i = 0; i < Dradius.size(); i++) {
		printf("%d %d\n", point_list[Dradius[i]].min[0], point_list[Dradius[i]].min[1]);
	}
	*/
}

void printVec() {
	
	int lcnt = 0;
	
    for (int i = 0; i < M; i++) {
        if (fv[i] < INF) {
            //printf("%lld ", fv[i]);
			//printf("%d ", i + 1);
			lcnt++;
        } else {
            //printf("_ ");
        }
    }
	
	if (lcnt >= 0) printf("%d\n", lcnt);
    //puts("");
}

void getPoints(int source, vector<PII>& ret) {
	LL D2 = fv[source];
	int D = sqrt((double)D2);
	for (int i = 0; i < skills[source].size(); i++) {
		int x = point_list[skills[source][i]].min[0];
		int y = point_list[skills[source][i]].min[1];
		Rect search_rect(x - D, y - D, x + D, y + D);
		Dradius.clear();
		tree.Search(search_rect.min, search_rect.max, MySearchCallback, NULL);
		//printf("%d\n", Dradius.size());
		for (int j = 0; j < Dradius.size(); j++) {
			LL dis = distSquare(Dradius[j], skills[source][i]);
			if (dis == D2) {
				ret.push_back(make_pair(Dradius[j], 0));
				NBE[Dradius[j]] |= cnt;
			} else if (dis < D2) {
				ret.push_back(make_pair(Dradius[j], 1));
				NB[Dradius[j]] |= cnt;
				NBE[Dradius[j]] |= cnt;
			}
		}
    }
	sort(ret.begin(), ret.end());
	ret.resize( std::distance(ret.begin(), unique(ret.begin(), ret.end()) ));
}

void getCandidates() {
    cnt = 1;
	memset(NB, 0, sizeof(NB));
    memset(NBE, 0, sizeof(NBE));
    for (int i = 0; i < M; i++) {
        if (fv[i] == INF) continue;
        getPoints(i, candList[cnt]);
		//printf("%d\n", candList[cnt].size());
		//for (int j = 0; j < candList[cnt].size(); j++) printf("(%d, %d) ", candList[cnt][j].first, candList[cnt][j].second); puts(";");
        cnt <<= 1;
    }

}

void neighbours(int source) {
	cnt = 1;
    for (int i = 0; i < M; i++) {
        if (fv[i] == INF) continue;
        vector<PII> tmp;
		set<pair<LL, LL> > mark;
		//mark.insert(make_pair(NB[source], NBE[source]));
        for (int j = 0; j < candList[cnt].size(); j++) {
            int ind = candList[cnt][j].first;
            if (!mark.count(make_pair(NB[ind], NBE[ind]))) {
				mark.insert(make_pair(NB[ind], NBE[ind]));
                tmp.push_back(candList[cnt][j]);
            }
        }
		//printf("size = %d\n", candList[cnt].size());
        candList[cnt] = tmp;
		//printf(" size = %d\n", candList[cnt].size());
		//for (int j = 0; j < tmp.size(); j++) printf("(%d, %d) ", tmp[j].first, tmp[j].second); puts("");
        cnt <<= 1;
    }
}

bool check(const vector<PII>& v) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i].second) return true;
    }
    return false;
}

void merge(const vector<PII>& a, const vector<PII>& b, vector<PII>& ret) {
    int i = 0, j = 0;
    // printf("%d %d\n", a.size(), b.size());

    while (i < a.size() && j < b.size()) {
        // printf("%d %d\n", i, j);
        if (a[i].first == b[j].first) {
            ret.push_back(make_pair(a[i].first, a[i].second | b[j].second));
            i++;
            j++;
        } else if (a[i].first < b[j].first) {
            i++;
        } else {
            j++;
        }
    }
}

void printBinary(int n) {
    while (n) {
        if (n & 1)
            putchar('^');
        else
            putchar(' ');
        putchar(' ');
        n >>= 1;
    }
    puts("");
}


void apriori() {
    L[1].clear();
    cnt = 1;

    int tt = 0;

    for (int i = 0; i < M; i++) {
        if (fv[i] == INF) continue;
        if (check(candList[cnt])) {
            L[1].push_back(cnt);
        } else {
            //printf("%lld\n", cnt);
            tt++;
        }
        cnt <<= 1;
    }

    int k = 2;

    while (L[k - 1].size() != 0) {
        LL st = 0;
        set<LL> preSet;
        for (int i = 0; i < L[k - 1].size(); i++) {
            st = st | L[k - 1][i];
            preSet.insert(L[k - 1][i]);
        }

        L[k].clear();
        for (int i = 0; i < L[k - 1].size(); i++) {
            for (LL j = 1; j <= st; j <<= 1) {
                if (L[k - 1][i] < j && (j & st)) {
                    LL p = j;
                    LL q = L[k - 1][i] | j;

                    bool flag = 0;

                    for (LL l = j; l > 0; l >>= 1) {
                        if (!(q & l)) continue;
                        if (!preSet.count(q - l)) {
                            flag = 1;
                            break;
                        }
                    }

                    if (flag) continue;

                    merge(candList[L[k - 1][i]], candList[p], candList[q]);

                    if (check(candList[q])) {
                        L[k].push_back(q);
                    } else {
                        //printBinary(q);
                        tt++;
                    }
                }
            }
        }

        k = k + 1;
    }
    //printf("tt = %d\n", tt);
    //printf("k = %d\n", L[k-2].size());
    /*
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < L[i].size(); j++) {
            for (int l = 0; l < L[i][j].size(); l++) {
                printf("%d ", L[i][j][l]);
            }
            puts("");
        }
    }
    */
}

int main(int argc, char *argv[]) {

	clock_t start;
    double duration;

	FILE *mapFile, *labelFile;
	mapFile = fopen("C:\\scratch\\jiaxingl\\yelp_map_data0.txt", "r");
	labelFile = fopen("C:\\scratch\\jiaxingl\\yelp_label_dataCat0.txt", "r");

	point_list.clear();

	int radius = 20000;

	if (argc == 2) {
		radius = atoi(argv[1]);
	}

	if (argc == 3) {
		mapFile = fopen(argv[1], "r");
		labelFile = fopen(argv[2], "r");
	}

	N = 0;
	int x, y;
    while (fscanf(mapFile, "%d %d", &x, &y) != EOF) {
		point_list.push_back(Point(x, y));
		tree.Insert(point_list[N].min, point_list[N].max, N);
		N++;
    }
	//printf("N = %d\n", N);
	M = 0;
	for (int i = 0; i < N; i++) {
		int k;
		fscanf(labelFile, "%d", &k);
		//if (i < 1000) printf("%d ", k);
        for (int j = 0; j < k; j++) {
            int l;
            fscanf(labelFile, "%d", &l);
            if (l > M) M = l;
            features[i].push_back(l);
            skills[l].push_back(i);
			//printf("%d\n", (int) skills[l].size());
        }
	}
	M++;
	//printf("M = %d\n", M);
	start = std::clock();
    for (int i = 0; i < 100; i++) {
		candList.clear();
		//printf("%d\n", (int) features[i].size());
		getDhopValues(radius, (int)(sample[i] * (N-1)));
        //printf("%d: ", (int)(sample[i] * (N-1)));
		//printVec();
		getCandidates();
        neighbours((int)(sample[i] * (N-1)));
        apriori();
    }
	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    printf("%lf\n", duration);

	//getchar(); // Wait for keypress on exit so we can read console output
}
